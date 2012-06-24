Summary:	Secure and efficient http server with advanced features
Summary(pl):	Bezpieczny i wydajny serwer http z rozbudowanymi mo�liwo�ciami
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
WN to serwer dla protoko�u HTTP w wersji 1.1. Jego g��wn� zalet� jest
bezpiecze�stwo oraz wbudowana funkcjonalno��, kt�ra z regu�y dost�pna
jestjedynie dzi�ki rozbudowanym skryptom CGI: r�norakie 
zabezpieczenia, przeszukiwanie ca�ego tekstu oraz warunkowe 
udost�pnianie tekstu.

Rozbudowane mo�liwo�ci nie wp�yn�y jednak na rozmiar pliku 
wykonywalnego serwera, kt�ry pozostaje mniejszy ni� serwery CERN lub
NCSA. Pakiet dostarcza zar�wno wersji standalone jak i inetd serwera 
WN. Ta druga zosta�a zoptymalizowana do zajmowania jak najmniejszej 
liczby zasob�w i jest zalecana dla serwer�w z ma�ym b�d� ograniczonym 
obci��eniem.

Model bezpiecze�stwa WN oparty jest na umieszczaniu w ka�dym katalogu 
ma�ych, kartotekowych baz danych zawieraj�cych informacje o plikach 
w nim si� znajduj�cych. Pola zwi�zane z plikami to tytu�, s�owa 
kluczowe, data wyga�ni�cia oraz dodatkowe zdefiniowane przez 
u�ytkownika np. autor. W przeciwie�twie do innych serwer�w WN domy�lnie
nie daje dost�pu do pliku, plik mo�e zosta� udost�pniony klientom http 
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
