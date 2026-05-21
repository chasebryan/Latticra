# Fedora Host Install Decision Gate

Status: active host-install decision gate
Scope: define explicit conditions before running Latticra Fedora install lanes directly on a developer host.

## Purpose

This gate prevents accidental host-level package testing before the Fedora packaging path has enough evidence.

The current Latticra Fedora RPM is local-only and documentation-only. The preferred local testing path remains disposable Fedora CI or a Fedora container.

Host-level installation is not the default path.

## Current package truth

The current expected installed payload is:

```text
/usr/share/doc/latticra/README.md
```

The current package must not install:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
kernel modules
bootloader files
SELinux policy files
runtime configuration
```

Absence of those surfaces is positive evidence at this stage.

## Hard stop conditions

Do not run host-level install testing if any of these are true:

```text
system is bootc-managed or otherwise read-only
system is production or daily-driver critical
working tree is dirty
local Fedora container lanes have not passed
local install smoke lane has not passed in disposable Fedora
installed-state report lane has not passed in disposable Fedora
package payload contains command, service, kernel, boot, SELinux, or runtime surfaces
user does not explicitly accept temporary RPM database modification
```

## Required evidence before host install

Before host-level testing is allowed, all of these must be true:

```text
source archive fixture lane passed
local binary RPM build lane passed
RPM payload inspection report lane passed
local install smoke lane passed in disposable Fedora
installed-state report lane passed in disposable Fedora
local testing guide has been read
host is mutable Fedora, not bootc/read-only Fedora
host is disposable or intentionally selected for package testing
current package remains documentation-only
post-removal cleanup check is known
```

## Required host preflight checks

A future host preflight script may check:

```sh
test -r /etc/fedora-release
! command -v bootc >/dev/null 2>&1 || ! bootc status >/dev/null 2>&1
git status --short
rpm -q latticra || true
```

If the host is bootc/read-only, use the container workflow instead.

## Host install consent text

Before host-level install testing, the operator should explicitly understand:

```text
This test will temporarily modify the host RPM database.
It will install the local-only latticra RPM.
It should install only /usr/share/doc/latticra/README.md.
It should remove the package after verification.
It is not a Fedora-approved package.
It is not a product-readiness claim.
It is not a runtime, service, kernel, boot, or SELinux integration.
```

## Safe default recommendation

Use this default unless there is a specific reason not to:

```text
Run Fedora packaging install tests in containers or disposable CI.
Do not install directly on bootc/read-only Fedora hosts.
Do not install directly on daily-driver hosts.
```

## Command smoke boundary

Host install testing does not imply command smoke readiness.

Do not expect these yet:

```sh
command -v latticra
latticra --version
latticra check
```

Those belong to a future CLI/runtime package lane after Latticra intentionally installs a stable command surface.

## Boundary

This gate does not run `rpmbuild`.

It does not run `mock`.

It does not create RPM artifacts.

It does not install Latticra.

It does not modify the host RPM database.

It does not publish package artifacts.

It does not upload release artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora host install preflight plan
```

That future slice should define a non-installing preflight check that classifies whether the current host is eligible for host-level install testing.

## Validation

This gate is guarded by:

```sh
sh scripts/test-fedora-host-install-decision-gate.sh
```

Expected output:

```text
fedora_host_install_decision_gate: ok
```