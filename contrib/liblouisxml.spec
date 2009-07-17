Name:           liblouisxml
Version:        1.9.1
Release:        1%{?dist}
Summary:        Translate XML files into proper Braille

Group:          System Environment/Libraries
License:        LGPL3+
URL:            http://code.google.com/p/liblouisxml/
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

# BuildRequires:  
Requires:       liblouis

%description
liblouisxml is a software component which can be incorporated into
software packages to provide the capability of translating any file in
the computer lingua franca xml format into properly transcribed
braille. This includes translation into grade two, if desired,
mathematical codes, etc. It also includes formatting according to a
built-in style sheet which can be modified by the user. The first
program into which liblouisxml has been incorporated is xml2brl.
This program will translate an xml or text file into an embosser-ready
braille file. It is not necessary to know xml, because MSWord and
other word processors can export files in this format. If the word
processor has been used correctly xml2brl will produce an excellent
braille file.

%package        devel
Summary:        Development files for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}

%description    devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.


%prep
%setup -q


%build
./autogen.sh

%configure --disable-static
#make %{?_smp_mflags}
make


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
#find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%clean
rm -rf $RPM_BUILD_ROOT


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%doc doc/* README
%{_infodir}/liblouisxml.info.gz
%{_mandir}/man1/msword2brl.1.gz
%{_mandir}/man1/xml2brl.1.gz

%{_libdir}/pkgconfig/liblouisxml.pc
%{_libdir}/*
%{_bindir}/*
%dir /usr/share/liblouisxml
/usr/share/liblouisxml/*
%dir /usr/share/doc/liblouisxml
/usr/share/doc/liblouisxml/*

%files devel
%defattr(-,root,root,-)
%{_includedir}/*


%changelog
* Wed Apr 02 2008 lars@handytech.no
- Created.
