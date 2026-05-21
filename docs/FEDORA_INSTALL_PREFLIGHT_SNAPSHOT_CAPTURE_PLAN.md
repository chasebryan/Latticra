# Fedora Install Preflight Snapshot Capture Plan

Status: planning record
Scope: define how a future caller may capture read-only host facts before invoking the Fedora host install preflight classifier.

## Purpose

The Fedora host install preflight classifier now accepts a caller-supplied snapshot and classifies whether a host may be considered for a later local RPM install lane.

This plan defines how that snapshot should be collected without turning preflight into installation.

The goal is to keep the capture lane conservative, deterministic, bounded, and auditable before any implementation reads host files or probes commands.

## Capture boundary

Snapshot capture is read-only.

It may collect facts needed by the classifier, but it must not install, remove, update, enable, start, stop, or configure anything.

The capture lane must not run:

```text
dnf install
dnf remove
dnf upgrade
dnf update
rpm -i
rpm -U
rpm -e
rpmbuild
rpmlint
systemctl enable
systemctl start
grubby
bootctl
restorecon
semodule
modprobe
```

It must also not open the network, create package artifacts, write host files, change privilege state, or validate sudo by refreshing credentials.

## Snapshot source map

A future capture implementation may fill the classifier snapshot from these read-only facts:

| Snapshot field | Allowed source | Rule |
| --- | --- | --- |
| `os_id` | `/etc/os-release` `ID=` | Read bounded text only. |
| `os_id_like` | `/etc/os-release` `ID_LIKE=` | Read bounded text only. |
| `host_install_requested` | explicit caller/operator request | Must default to false. |
| `immutable_host` | `/run/ostree-booted` existence or `rpm-ostree` marker | Detect only; do not run `rpm-ostree install`. |
| `rpm_available` | `command -v rpm` | Probe command presence only. |
| `dnf_available` | `command -v dnf` | Probe command presence only. |
| `rpmbuild_available` | `command -v rpmbuild` | Probe command presence only. |
| `rpmlint_available` | `command -v rpmlint` | Probe command presence only. |
| `local_rpm_present` | explicit local RPM path | Check existence/readability only. |
| `root_or_sudo_available` | `id -u` equals `0` or explicit operator assertion | Do not run `sudo -v`. |
| `network_required` | caller-supplied lane setting | Must default to false for local-only preflight. |
| `package_is_doc_only` | package metadata from the current Fedora package lane | Current default remains true. |
| `command_entrypoint_expected` | caller expectation | Must default to false while the package is doc-only. |

## Read-only command allowance

The first capture implementation may use read-only probes such as:

```sh
command -v rpm
command -v dnf
command -v rpmbuild
command -v rpmlint
id -u
test -r /etc/os-release
test -e /run/ostree-booted
test -r "$LOCAL_RPM"
```

Those commands may classify the host, but they must not install or mutate.

## Privilege rule

Privilege capture must be conservative.

Allowed:

```text
record root_or_sudo_available=1 when id -u is 0
record root_or_sudo_available=0 when id -u is not 0 and no explicit operator-supplied privilege fact is provided
```

Not allowed in the first capture lane:

```text
sudo -v
sudo -n true
sudo dnf install
sudo rpm -i
```

The reason is simple: preflight capture should not refresh credentials, change sudo timestamp state, or perform a privileged dry run.

## Immutable Fedora rule

If `/run/ostree-booted` exists or the caller identifies the host as rpm-ostree/image-based, capture should set:

```text
immutable_host=1
```

The classifier should then return a future-gated lane rather than treating the host like a mutable Fedora RPM target.

Immutable Fedora work must remain separate because rpm-ostree/image-based systems need their own design, rollback, and safety model.

## Local RPM rule

The local RPM fact must come from an explicit path chosen by the caller.

The capture lane may check that the file exists and is readable. It must not install it, query remote repositories, or build a replacement artifact.

If no explicit local RPM path is provided, capture should set:

```text
local_rpm_present=0
```

## Current package posture rule

The current Fedora package path remains documentation/package-shape oriented.

Until the package installs a stable runtime command, capture should set:

```text
package_is_doc_only=1
command_entrypoint_expected=0
```

If a caller expects a command while the package remains doc-only, the classifier must block with:

```text
denial=runtime-entrypoint-not-present
```

## Future report fields

A later implementation may emit a capture report with fields such as:

```text
FEDORA INSTALL PREFLIGHT SNAPSHOT CAPTURE
snapshot_capture_status=planned
os_release_read_allowed=1
command_probe_allowed=1
local_rpm_probe_allowed=1
sudo_validation_allowed=0
install_command_allowed=0
package_build_allowed=0
network_allowed=0
host_mutation_performed=0
host_install_performed=0
snapshot_forwarded_to_classifier=1
```

## Failure behavior

Capture should fail closed.

If `/etc/os-release` is unreadable, command probes are unavailable, the local RPM path is missing, or the caller requests a network-dependent path, the capture lane should still produce a deterministic snapshot and allow the classifier to return a blocked or report-only result.

Failure to capture facts must not trigger installation, package building, network fallback, or privileged fallback.

## Implementation sequence

Recommended order:

```text
1. Add a small snapshot-capture contract/API.
2. Add bounded os-release parsing for ID and ID_LIKE.
3. Add command-presence probes for rpm, dnf, rpmbuild, and rpmlint.
4. Add explicit local RPM path probing.
5. Add immutable-host marker probing.
6. Add deterministic capture report fields.
7. Forward the captured snapshot into the existing classifier.
8. Add tests for mutable Fedora, immutable Fedora, non-Fedora, missing local RPM, and missing tooling paths.
```

## Validation

This planning slice is guarded by:

```sh
sh scripts/test-fedora-install-preflight-snapshot-capture-plan.sh
```

Expected output:

```text
fedora_install_preflight_snapshot_capture_plan: ok
```

## Non-claims

This plan does not implement snapshot capture.

It does not install Latticra, run `dnf`, run mutating `rpm` commands, run `rpmbuild`, run `rpmlint`, create RPM artifacts, validate sudo, mutate the host, open the network, claim Fedora package approval, or claim production installer readiness.
