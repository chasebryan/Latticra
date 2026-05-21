# LOCAL-ONLY DRAFT
# Upstream packaging experiment for Latticra.

Name:           latticra
Version:        0.0.0
Release:        0.1.local%{?dist}
Summary:        Contract-first systems architecture and language project

License:        LicenseRef-Latticra-TBD
URL:            https://github.com/Bryforge/Latticra
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make

%description
Latticra is an early-stage contract-first systems architecture and language
project. This local draft records packaging shape only.

%prep
%autosetup -n %{name}-%{version}

%build
sh scripts/test-state-lattice.sh
sh scripts/test-system-bootstrap.sh
sh scripts/test-kernel.sh
sh scripts/test-kernel-lifecycle.sh

%install
mkdir -p %{buildroot}%{_docdir}/%{name}
install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md

%files
%doc %{_docdir}/%{name}/README.md

%changelog
* Wed May 20 2026 Bryforge <noreply@example.invalid> - 0.0.0-0.1.local
- Add local-only RPM spec draft skeleton.
