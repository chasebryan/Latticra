# Fedora RPM Payload Inspection Report

Status: active generated-report lane
Scope: generate a deterministic RPM metadata and payload inspection report from a local-only Fedora binary RPM without installing or publishing it.

## Purpose

This lane advances the Fedora local RPM path from build-only validation to audit-visible payload reporting.

The goal is conservative: after a local-only RPM is built in a disposable Fedora environment, capture the package metadata and file payload list into a deterministic report, then verify that the report reflects the current documentation-only package posture.

This lane does not install the RPM. It does not publish the RPM. It does not submit Latticra to Fedora.

## Report inputs

The generated report is based on:

```text
packaging/fedora/latticra.spec
local temporary Source0 archive
local temporary binary RPM
rpm -qpi <generated-rpm>
rpm -qpl <generated-rpm>
```

Because the current payload is documentation-only, this report lane keeps debug package generation disabled for the local build with:

```text
debug_package %{nil}
```

That keeps Fedora's debugsource machinery from producing an empty debugsource `%files` failure while there are no compiled payloads to inspect. Debug package behavior should be revisited once Latticra installs compiled files.

## Report sections

The report should contain stable sections:

```text
Fedora RPM Payload Inspection Report
Package identity
Build posture
RPM metadata
RPM payload
Payload policy checks
Boundary
```

## Current expected posture

The current RPM payload remains documentation-only.

Expected payload:

```text
/usr/share/doc/latticra/README.md
```

Unexpected payload at the current stage:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
kernel modules
bootloader files
SELinux policy files
runtime configuration
```

## Payload policy checks

The generated report should make these checks explicit:

```text
README payload present: yes
command payload absent: yes
configuration payload absent: yes
systemd service payload absent: yes
kernel module payload absent: yes
boot payload absent: yes
SELinux policy payload absent: yes
runtime configuration payload absent: yes
debug package generated: no
```

These absence checks are positive evidence at this stage. They show that the local RPM does not accidentally promote runtime, service, boot, kernel, policy, or command authority before the project has earned those surfaces.

## Relationship to install verification

This lane comes before an install smoke lane.

The correct order is:

```text
1. source archive fixture lane
2. local binary RPM build lane
3. RPM payload inspection report lane
4. fresh Fedora install smoke lane
5. command/runtime smoke checks only after a stable entrypoint exists
```

## Boundary

This lane builds a local-only binary RPM in CI for inspection.

It does not run `mock`.

It does not install Latticra.

It does not publish package artifacts.

It does not upload release artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora local install smoke plan
```

That future slice should plan a fresh Fedora install check using the locally built RPM while preserving the current documentation-only posture.

## Validation

This lane is guarded by:

```sh
sh scripts/test-fedora-rpm-payload-inspection-report.sh
```

Expected output:

```text
fedora_rpm_payload_inspection_report: ok
```