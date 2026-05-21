# Fedora Local Install Smoke Lane

Status: active local install smoke lane
Scope: install and remove the locally built Latticra RPM inside a disposable Fedora CI environment.

## Purpose

This lane advances the Fedora integration path from RPM payload inspection to installed-state proof.

The goal is conservative: build the local-only RPM, install it in a disposable Fedora environment, prove package queryability and verification, prove the current documentation-only payload, verify no premature runtime surfaces appear, then remove the package.

This lane does not install Latticra on a developer host. It does not publish the RPM. It does not submit Latticra to Fedora.

## Current package truth

The current RPM payload remains documentation-only.

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

## Install smoke procedure

This lane performs the following in Fedora CI:

```text
1. verify Fedora environment
2. install local build tools
3. run the RPM payload inspection report guard first
4. create a temporary source archive
5. build exactly one local Latticra RPM
6. install the generated RPM in the disposable Fedora environment
7. query the package with rpm -q latticra
8. list installed files with rpm -ql latticra
9. verify installed files with rpm -V latticra
10. verify README is readable under /usr/share/doc/latticra/README.md
11. verify command, config, service, kernel, boot, SELinux, and runtime payloads are absent
12. remove the package with rpm -e latticra
13. confirm rpm -q latticra fails after removal
14. remove temporary RPM work output
```

## Commands used

The lane uses commands shaped like:

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

## Command smoke boundary

This lane still does not add command smoke tests.

Do not add these yet:

```sh
command -v latticra
latticra --version
latticra check
```

Those checks belong to a future CLI/runtime package lane after Latticra intentionally installs a stable command surface.

## Pass conditions

This lane passes only if:

```text
local RPM builds successfully
exactly one latticra RPM is produced
RPM installs in the disposable Fedora environment
rpm -q latticra succeeds after install
rpm -ql latticra lists the README payload
rpm -V latticra produces no unexpected verification output
README is readable at the installed documentation path
premature runtime surfaces are absent
rpm -e latticra removes the package
rpm -q latticra fails after removal
all temporary output is cleaned up
```

## Boundary

This lane runs a local binary RPM build in CI.

It installs and removes the local RPM only inside disposable Fedora CI.

It does not run `mock`.

It does not install Latticra on a developer host.

It does not publish package artifacts.

It does not upload release artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora installed-state report lane
```

That future slice should generate a deterministic report from the install, verify, and removal checks while preserving the current documentation-only posture.

## Validation

This lane is guarded by:

```sh
sh scripts/test-fedora-local-install-smoke-lane.sh
```

Expected output:

```text
fedora_local_install_smoke_lane: ok
```