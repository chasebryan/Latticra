# LOCAL-ONLY openSUSE DRAFT
# Upstream packaging experiment for Latticra.
# This spec is maintained separately from the Fedora draft until openSUSE review evidence exists.

%global debug_package %{nil}

Name:           latticra
Version:        0.0.0
Release:        0.local
Summary:        Contract-first systems architecture and language project

License:        LicenseRef-Latticra-TBD
URL:            https://github.com/Bryforge/Latticra
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make

%description
Latticra is an early-stage contract-first systems architecture and language
project. This local openSUSE draft records package shape and maintenance
posture only.

%prep
%autosetup -n %{name}-%{version}

%build
sh scripts/test-state-lattice.sh
sh scripts/test-system-bootstrap.sh
sh scripts/test-kernel.sh
sh scripts/test-kernel-lifecycle.sh
sh scripts/test-latticra-no-effect-cli-status-surface.sh
mkdir -p build
cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra

%install
mkdir -p %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_docdir}/%{name}
install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra
install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md

%files
%{_bindir}/latticra
%doc %{_docdir}/%{name}/README.md

%changelog
* Tue May 26 2026 Bryforge <noreply@example.invalid> - 0.0.0-0.local
- Add local-only openSUSE RPM draft for the no-effect CLI payload without claiming Open Build Service publication.
