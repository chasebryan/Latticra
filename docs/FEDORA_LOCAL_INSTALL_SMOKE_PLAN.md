# Fedora Local Install Smoke Plan

Status: planning record
Scope: define a future fresh Fedora install smoke lane for the local-only Latticra RPM without installing artifacts in this slice.

## Purpose

This plan advances the Fedora integration path from local RPM payload inspection toward an installed-state proof.

The goal is conservative: define how a future Fedora lane will install the locally built RPM inside a disposable Fedora environment, prove package ownership and verification, then remove it.

This plan does not install Latticra. It does not publish the RPM. It does not submit Latticra to Fedora.

## Current package truth

The current package remains documentation-only.

Expected installed payload:

```text
/usr/share/doc/latticra/README.md
```

Expected absent installed surfaces:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
kernel modules
bootloader files
SELinux policy files
runtime configuration
```

These absence checks are positive evidence at this stage.

## Future install smoke inputs

A future install smoke lane should use:

```text
local temporary Source0 archive
local temporary binary RPM
fresh Fedora container or disposable Fedora environment
rpm package manager tools
rpm query and verification tools
```

The RPM should be built in the same lane or handed off only through temporary CI workspace state, not committed artifacts.

## Future install smoke procedure

The future implementation lane should perform:

```text
1. create temporary RPM workspace
2. create temporary source archive
3. run local binary RPM build
4. locate exactly one latticra RPM
5. install that RPM in the disposable Fedora environment
6. query the package with rpm -q latticra
7. list installed files with rpm -ql latticra
8. verify installed files with rpm -V latticra
9. verify README exists under /usr/share/doc/latticra/README.md
10. verify no command, config, service, kernel, boot, SELinux, or runtime payload exists
11. remove the package
12. confirm rpm -q latticra reports the package as removed
13. remove all temporary build output
```

## Expected future command shape

The future install lane may use commands like:

```sh
rpm -Uvh <generated-rpm>
rpm -q latticra
rpm -ql latticra
rpm -V latticra
test -r /usr/share/doc/latticra/README.md
test ! -e /usr/bin/latticra
test ! -d /etc/latticra
test ! -e /usr/lib/systemd/system/latticra.service
rpm -e latticra
! rpm -q latticra
```

The future implementation should choose `dnf install ./<generated-rpm>` only if dependency solving becomes necessary. The current documentation-only RPM should not require external runtime dependencies beyond RPM metadata basics.

## Pass conditions

The future install smoke lane should pass only if:

```text
local RPM builds successfully
exactly one latticra RPM is produced
RPM installs in a disposable Fedora environment
rpm -q latticra succeeds after install
rpm -ql latticra lists the README payload
rpm -V latticra has no unexpected verification output
README is readable at the installed documentation path
premature runtime surfaces are absent
rpm -e latticra removes the package
rpm -q latticra fails after removal
all temporary output is cleaned up
```

## Relationship to command smoke checks

Command smoke checks must wait until a real command entrypoint exists.

Do not add these yet:

```sh
command -v latticra
latticra --version
latticra check
```

Those belong to a future CLI/runtime package lane after Latticra intentionally installs `/usr/bin/latticra` or another stable command surface.

## Boundary

This plan does not run `rpmbuild`.

It does not run `mock`.

It does not create RPM artifacts.

It does not install Latticra.

It does not remove Latticra from the host.

It does not publish package artifacts.

It does not upload release artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora local install smoke lane
```

That future slice may install and remove the local RPM only inside a disposable Fedora CI environment.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-local-install-smoke-plan.sh
```

Expected output:

```text
fedora_local_install_smoke_plan: ok
```