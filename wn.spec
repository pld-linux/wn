#
# Todo:
# bcond with digest and with ndbm authorization (Im not gonna do it)
#
%bcond_with	suexec	# enable suexec
%bcond_with	vhosts	# enable vhosts
%bcond_with	ssl	# enable ssl (not working)

Summary:	Secure and efficient HTTP server with advanced features
Summary(pl):	Bezpieczny i wydajny serwer HTTP z rozbudowanymi mo¿liwo¶ciami
Name:		wn
Version:	2.4.7
Release:	1
License:	GPL
Group:		Networking/Daemons
Source0:	http://www.wnserver.org/%{name}-%{version}.tar.gz
# Source0-md5:	c146f34444a1228e3a478ba7f6b9fdf1
Source1:	%{name}-Makefile
Source2:	%{name}-config.h
Source3:	%{name}.init
Patch0:		%{name}-build.patch
URL:		http://www.wnserver.org/
BuildRequires:	openssl-devel >= 0.9.7d
BuildRequires:	pam-devel
BuildRequires:	perl-base
BuildRequires:	rpmbuild(macros) >= 1.202
%{?with_vhosts:BuildRequires: sed >= 4.0}
Requires:	/etc/mime.types
Requires(pre):	/bin/id
Requires(pre):	/usr/bin/getgid
Requires(pre):	/usr/sbin/groupadd
Requires(pre):	/usr/sbin/useradd
Requires(postun):	/usr/sbin/groupdel
Requires(postun):	/usr/sbin/userdel
Requires(post,preun):	/sbin/chkconfig
Requires(post,postun):	/sbin/ldconfig
Requires(post):	fileutils
Provides:	group(http)
Provides:	httpd = %{version}
Provides:	user(http)
Provides:	webserver = %{version}
BuildRoot:	%{tmpdir}/%{name}-%{version}-root-%(id -u -n)

%description
WN is a server for the Hypertext Transfer Protocol (HTTP/1.1). Its
primary design goals are security and functionality usually available
only with complex CGI scripts without the necessity of writing or
using these scripts. This includes extensive security checks, full
text searching and conditionally served text.

Despite this extensive functionality the WN executable is
substantially smaller than the CERN or NCSA servers. Both a
stand-alone daemon and a version intended for use under inetd are
provided. The inetd version is designed to minimize the use of system
resources and it is appropriate for moderate or lightly loaded servers
which cannot be totally dedicated to Web serving.

WN's security model is based on the use of a small flat database in
each directory with information about the files in that directory.
Fields associated with a file include its title, and may include
keywords, expiration date and any user defined fields like author or
document id. Unlike other servers, the default action for WN is to
deny access to a file.A file can only be served if explicit permission
to do so has been granted by entering it in this database

%description -l pl
WN to serwer dla protoko³u HTTP w wersji 1.1. Jego g³ówn± zalet± jest
bezpieczeñstwo oraz wbudowana funkcjonalno¶æ, która z regu³y dostêpna
jestjedynie dziêki rozbudowanym skryptom CGI: ró¿norakie
zabezpieczenia, przeszukiwanie ca³ego tekstu oraz warunkowe
udostêpnianie tekstu.

Rozbudowane mo¿liwo¶ci nie wp³ynê³y jednak na rozmiar pliku
wykonywalnego serwera, który pozostaje mniejszy ni¿ serwery CERN lub
NCSA. Pakiet dostarcza zarówno wersji standalone jak i inetd serwera
WN. Ta druga zosta³a zoptymalizowana do zajmowania jak najmniejszej
liczby zasobów i jest zalecana dla serwerów z ma³ym b±d¼ ograniczonym
obci±¿eniem.

Model bezpieczeñstwa WN oparty jest na umieszczaniu w ka¿dym katalogu
ma³ych, kartotekowych baz danych zawieraj±cych informacje o plikach
w nim siê znajduj±cych. Pola zwi±zane z plikami to tytu³, s³owa
kluczowe, data wyga¶niêcia oraz dodatkowe zdefiniowane przez
u¿ytkownika np. autor. W przeciwieñstwie do innych serwerów WN
domy¶lnie nie daje dostêpu do pliku, plik mo¿e zostaæ udostêpniony
klientom HTTP tylko w przypadku zezwolenia na to w bazie danych.

%prep
%setup -q
%patch0 -p1

%build
%{__perl} configure <<_EOF_
_EOF_

install %{SOURCE1} ./Makefile
install %{SOURCE2} ./config.h


%if %{with vhosts}
sed -i -e "s/^#define USE_VIRTUAL_HOSTS.*/#define USE_VIRTUAL_HOSTS\t\(TRUE\)/" config.h
%endif

%if %{with suexec}
sed -e "s/^#define WN_SU_EXEC.*/#define WN_SU_EXEC\t\(TRUE\)/" config.h
%endif

%{__make} \
	CC="%{__cc}" \
	%{?with_suexec:SUEXEC=suexec} \
	CFLAGS="%{rpmcflags} -I../wn -I../md5"
cd docs
rm fdl* Gnu_License Makefile md5*
cd ../

%install
rm -rf $RPM_BUILD_ROOT
# create directories if necessary
install -d $RPM_BUILD_ROOT{%{_mandir}/man{1,3,8},%{_sbindir},%{_bindir}}

%{__make} install \
	SERVBINDIR=$RPM_BUILD_ROOT%{_sbindir} \
	BINDIR=$RPM_BUILD_ROOT%{_bindir}

install docs/man/man1/* $RPM_BUILD_ROOT%{_mandir}/man1/
install docs/man/man3/* $RPM_BUILD_ROOT%{_mandir}/man3/
install docs/man/man8/* $RPM_BUILD_ROOT%{_mandir}/man8/
# This breaks short-ciruit, but what the heck, the package is 500 kb
# you cand do a rebuild.
rm -rf docs/man

install -d $RPM_BUILD_ROOT%{_var}/log/wn
touch $RPM_BUILD_ROOT%{_var}/log/wn/wn_{access,error}.log

install -d $RPM_BUILD_ROOT/etc/rc.d/init.d
install %{SOURCE3} $RPM_BUILD_ROOT/etc/rc.d/init.d/wn

%clean
rm -rf $RPM_BUILD_ROOT

%pre
%groupadd -g 51 -r http
%useradd -u 51 -r -d /home/services/httpd -s /bin/false -c "HTTP User" -g http http

%post
/sbin/ldconfig
/sbin/chkconfig --add wn
umask 137
touch /var/log/wn/wn_{access,error}.log
if [ -f /var/lock/subsys/wn ]; then
	/etc/rc.d/init.d/wn restart 1>&2
else
	echo "Run \"/etc/rc.d/init.d/wn start\" to start wn HTTP daemon."
fi

%preun
if [ "$1" = "0" ]; then
	if [ -f /var/lock/subsys/wn ]; then
		/etc/rc.d/init.d/wn stop 1>&2
	fi
	/sbin/chkconfig --del wn
fi

%postun
/sbin/ldconfig
if [ "$1" = "0" ]; then
	%userremove http
	%groupremove http
fi


%files
%defattr(644,root,root,755)
%doc docs README.wnssl
%attr(754,root,root) /etc/rc.d/init.d/wn
%attr(755,root,root) %{_bindir}/md5
%attr(755,root,root) %{_bindir}/wn*
%attr(755,root,root) %{_sbindir}/wn*
%{_mandir}/man?/*
%attr(750,http,http) %dir %{_var}/log/wn
%attr(640,http,http) %{_var}/log/wn/*
