Summary:	Secure and efficient http server with advanced features
Summary(pl):	Bezpieczny i wydajny serwer http z rozbudowanymi mo¿liwo¶ciami
Name:		wn	
Version:	2.4.6
Release:	1
License:	GPL
Group:		Networking/Daemons
Source0:	http://www.wnserver.org/%{name}-%{version}.tar.gz
# Source0-md5:	78a850d2a814962314a4adf9c7f0d8ae
##Patch0:		%{name}-what.patch
URL:		http://www.wnserver.org/
Requires:       /etc/mime.types

BuildRequires:	
PreReq:		-
Requires(pre,post):	-
Requires(preun):	-
Requires(postun):	-
Provides:       httpd = %{version}
Provides:       webserver = %{version}

Requires:	-
Provides:	-
Obsoletes:	-
Conflicts:	-
BuildRoot:	%{tmpdir}/%{name}-%{version}-root-%(id -u -n)

%description
WN is a server for the Hypertext Transfer Protocol (HTTP/1.1). Its 
primary design goals are security and functionality usually available
only with complex CGI scripts without the necessity of writing or 
using these scripts. This includes extensive security checks, full 
text searching and conditionally served text. 

Despite this extensive functionality the WN executable is 
substantially  smaller than the CERN or NCSA servers. Both a 
stand-alone daemon and a version intended for use under inetd are 
provided. The inetd version is designed to minimize the use of system
resources and it is appropriate for moderate or lightly loaded 
servers which cannot be totally dedicated to Web serving. 

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
u¿ytkownika np. autor. W przeciwieñ¶twie do innych serwerów WN domy¶lnie
nie daje dostêpu do pliku, plik mo¿e zostaæ udostêpniony klientom http 
tylko w przypadku zezwolenia na to w bazie danych.

#%%package subpackage
#Summary:	-
#ummary(pl):	-
#%Group:		-

#%%description subpackage

#%%description subpackage -l pl

%prep
%setup -q


%build
%{__gettextize}
%{__aclocal}
%{__autoconf}
%{__autoheader}
%{__automake}
%configure
%{__make}

%install
rm -rf $RPM_BUILD_ROOT
# create directories if necessary
#install -d $RPM_BUILD_ROOT

%{__make} install \
	DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%pre

%post

%preun

%postun

%files
%defattr(644,root,root,755)
%doc AUTHORS CREDITS ChangeLog NEWS README THANKS TODO
%attr(755,root,root) %{_bindir}/*
%{_datadir}/%{name}

%files subpackage
%defattr(644,root,root,755)
%doc extras/*.gz
%{_datadir}/%{name}-ext
