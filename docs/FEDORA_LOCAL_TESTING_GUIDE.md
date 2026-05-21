# Fedora Local Testing Guide

Status: active local testing guide
Scope: document safe local testing for Latticra's Fedora packaging lanes, especially on bootc/read-only Fedora systems.

## Purpose

This guide explains how to test the Fedora packaging path locally without confusing container testing, CI testing, and host installation.

The current Latticra Fedora package is local-only and documentation-only. It is suitable for container and CI install-smoke validation, but it is not a Fedora submission, Fedora-approved package, production package, operating-system image, runtime install, service install, kernel integration, boot integration, or SELinux policy deployment.

## Current package truth

The current RPM payload is expected to install only:

```text
/usr/share/doc/latticra/README.md
```

The current RPM payload must not install:

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

## Branch selection

If the Fedora stack has not yet landed on `main`, test the branch that contains the lane you need.

For the full local install/report stack:

```sh
git fetch origin
git switch -C fedora-installed-report origin/fedora-installed-report
```

For the local install smoke lane only:

```sh
git fetch origin
git switch -C fedora-install-lane origin/fedora-install-lane
```

For source archive fixture testing only:

```sh
git fetch origin
git switch -C fedora-archive origin/fedora-archive
```

Always confirm the scripts exist before running them:

```sh
ls scripts/test-fedora-source-archive-fixture-lane.sh
ls scripts/test-fedora-local-binary-rpm-build-lane.sh
ls scripts/test-fedora-rpm-payload-inspection-report.sh
ls scripts/test-fedora-local-install-smoke-lane.sh
ls scripts/test-fedora-installed-state-report-lane.sh
```

## bootc/read-only Fedora systems

If Fedora reports something like:

```text
this bootc system is configured to be read-only
```

then do not try to force host package installation with `dnf`.

Use a Fedora container for local testing instead.

## Recommended container workflow

From the repository root:

```sh
podman run --rm -it \
  -v "$PWD":/work:Z \
  -w /work \
  registry.fedoraproject.org/fedora:latest \
  bash
```

Inside the container:

```sh
dnf -y install git tar gzip rpm-build gcc make
```

Then run the lanes in order:

```sh
sh scripts/test-fedora-source-archive-fixture-lane.sh
sh scripts/test-fedora-local-binary-rpm-build-lane.sh
sh scripts/test-fedora-rpm-payload-inspection-report.sh
sh scripts/test-fedora-local-install-smoke-lane.sh
sh scripts/test-fedora-installed-state-report-lane.sh
```

Expected final success markers include:

```text
fedora_source_archive_fixture_lane: ok
fedora_local_binary_rpm_build_lane: ok
fedora_rpm_payload_inspection_report: ok
fedora_local_install_smoke_lane: ok
fedora_installed_state_report_lane: ok
```

## Lane safety levels

Non-installing lanes:

```text
source archive fixture lane
local binary RPM build lane
RPM payload inspection report lane
```

Those create temporary build output and inspect it.

Installing lanes:

```text
local install smoke lane
installed-state report lane
```

Those install and remove the local RPM. Run them inside disposable Fedora CI or a Fedora container first.

## Host testing guidance

On a normal mutable Fedora host, direct host testing may be reasonable only after the container lanes pass.

On a bootc/read-only Fedora host, continue using containers.

Do not run the install-smoke or installed-state report lanes directly on a host unless you intentionally accept that the script will modify the host RPM database by temporarily installing and removing the local `latticra` package.

## Post-test cleanup check

After install-smoke testing, verify the package was removed:

```sh
rpm -q latticra
```

Expected output:

```text
package latticra is not installed
```

## Command smoke boundary

Command smoke checks are not valid yet because the current RPM is documentation-only.

Do not expect these to work yet:

```sh
command -v latticra
latticra --version
latticra check
```

Those checks belong to a future CLI/runtime package lane after Latticra intentionally installs a stable command surface.

## Boundary

This guide does not run `rpmbuild`.

It does not run `mock`.

It does not create RPM artifacts.

It does not install Latticra.

It does not publish package artifacts.

It does not upload release artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora host install decision gate
```

That future slice should define explicit conditions before anyone runs host-level install tests outside a disposable container or CI environment.

## Validation

This guide is guarded by:

```sh
sh scripts/test-fedora-local-testing-guide.sh
```

Expected output:

```text
fedora_local_testing_guide: ok
```