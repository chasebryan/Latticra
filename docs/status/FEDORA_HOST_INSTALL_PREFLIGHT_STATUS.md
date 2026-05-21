# Fedora Host Install Preflight Status

Status: merged no-effect Fedora preflight classifier

This record tracks the Fedora host install preflight classifier slice.

Merged PR:

```text
#198 Add Fedora host install preflight classifier
```

Merged commit:

```text
bbcb42afce009a29b7ba5c0ea8b354a9bca93966
```

Primary files:

```text
include/latticra/fedora_host_install_preflight.h
src/fedora_host_install_preflight.c
tests/fedora_host_install_preflight.c
docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
scripts/test-fedora-host-install-preflight.sh
scripts/test-fedora-host-install-preflight-docs.sh
.github/workflows/fedora-host-install-preflight.yml
```

What it adds:

```text
Fedora host snapshot classifier
mutable Fedora host label
immutable Fedora future-gated label
local RPM candidate label
network-required denial
missing rpm/dnf denial
missing local RPM denial
missing privilege denial
doc-only runtime-entrypoint denial
no-effect install report fields
```

Report boundary:

```text
FEDORA HOST INSTALL PREFLIGHT
classification=ready-local-rpm
host_install_candidate=1
host_install_performed=0
host_mutation_performed=0
network_allowed=0
no_effect=1
evidence_level=1
```

Validation:

```sh
sh scripts/test-fedora-host-install-preflight.sh
sh scripts/test-fedora-host-install-preflight-docs.sh
```

Boundary: preflight classification only. No host install, dnf execution, rpm execution, rpmbuild execution, rpmlint execution, package artifact creation, host mutation, network opening, service installation, boot entry installation, kernel module installation, Fedora approval claim, or production installer readiness is added.

Recommended next slice:

```text
Add Fedora install preflight snapshot capture plan
```

That future slice should define how a caller may safely collect `/etc/os-release`, `rpm`, `dnf`, privilege, and local RPM facts before passing them into the classifier. It should remain read-only and should not install anything.
