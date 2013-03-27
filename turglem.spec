Summary: 	Turglem lemmatizer (english + russian)
Name: 		turglem
Version: 	0.1.0
Release: 	0%{?dist}
License: 	BSD
Source: 	turglem-%{version}.tar.gz
Group:		System Environment/Libraries
BuildRoot: 	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:	libcoda-devel libMAFSA-devel cmake gcc-c++

%package devel
Summary:	Header files and development documentation for %{name}
Group: 		Development/Libraries
Requires:	%{name} = %{version}-%{release}

%description
Turglem lemmatizer, binary dictionaries.
%description devel
Turglem lemmatizer header files.

This package contains the header files, static libraries and development
documentation for %{name}. If you like to develop programs using %{name},
you will need to install %{name}-devel.

%prep
%setup -q -n turglem-%{version}

%build
cmake -D SKIP_RELINK_RPATH=ON . -DCMAKE_INSTALL_PREFIX=/usr -DCFLAGS="${CFLAGS}" -DCXXFLAGS="${CXXFLAGS}"
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
mkdir %{buildroot}
make DESTDIR=%{buildroot} install

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_bindir}/*
%{_libdir}/*
/usr/share/turglem/*

%files devel
%defattr(-,root,root,-)
%{_includedir}/turglem

%changelog
* Wed Mar 27 2013 Alexander Pankov <pianist@usrsrc.ru> - 0.1.0-0
+ RPM package

