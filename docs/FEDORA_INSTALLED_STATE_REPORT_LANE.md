# Fedora Installed-State Report Lane

Status: active installed-state report lane
Scope: generate a deterministic report from the Fedora local RPM install, verify, and removal smoke path.

## Purpose

This lane advances the Fedora integration path from install-smoke validation to audit-visible installed-state reporting.

The goal is conservative: build the local-only RPM, install it in disposable Fedora CI, capture package query/list/verify/remove evidence, write a deterministic report, then remove all temporary output.

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

These absence checks remain positive evidence at this stage.

## Report inputs

The generated report is based on:

```text
local temporary Source0 archive
local temporary binary RPM
rpm -q latticra
rpm -ql latticra
rpm -V latticra
README readability check
premature surface absence checks
rpm -e latticra
post-removal rpm -q latticra
```

## Report sections

The report should contain stable sections:

```text
Fedora Installed-State Report
Package identity
Install posture
Installed package query
Installed payload
Verification result
Payload policy checks
Removal result
Boundary
```

## Required report facts

The report should state:

```text
local RPM built: yes
installed in disposable Fedora CI: yes
README installed: yes
rpm verification clean: yes
command payload absent: yes
configuration payload absent: yes
systemd service payload absent: yes
kernel module payload absent: yes
boot payload absent: yes
SELinux policy payload absent: yes
runtime configuration payload absent: yes
package removed after smoke: yes
post-removal query failed: yes
```

## Relationship to future command checks

Command smoke checks must wait until a real command entrypoint exists.

Do not add these yet:

```sh
command -v latticra
latticra --version
latticra check
```

Those checks belong to a future CLI/runtime package lane after Latticra intentionally installs a stable command surface.

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
Add Fedora local testing guide
```

That future slice should document how developers can safely run the non-installing lanes and install-smoke lane inside containers, especially on bootc/read-only Fedora systems.

## Validation

This lane is guarded by:

```sh
sh scripts/test-fedora-installed-state-report-lane.sh
```

Expected output:

```text
fedora_installed_state_report_lane: ok
```