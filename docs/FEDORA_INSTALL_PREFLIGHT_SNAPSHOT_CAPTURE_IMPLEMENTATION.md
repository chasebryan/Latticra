# Fedora Install Preflight Snapshot Capture Implementation

Status: implementation record
Scope: pure no-effect snapshot capture that feeds the Fedora host install preflight classifier.
Evidence level: 2

## Purpose

This implementation moves the Fedora install preflight snapshot lane beyond planning while preserving the host safety boundary.

It adds a pure C capture API that consumes caller-supplied read-only facts, parses bounded `/etc/os-release` text already provided by the caller, constructs a `latticra_fedora_host_install_preflight_snapshot_t`, and forwards that snapshot into the existing Fedora host install preflight classifier.

The implementation mutates repository code only. It does not mutate the host.

## Public API

Primary header:

```text
include/latticra/fedora_install_preflight_snapshot.h
```

Primary source:

```text
src/fedora_install_preflight_snapshot.c
```

The main entry points are:

```text
latticra_fedora_install_preflight_snapshot_capture
latticra_fedora_install_preflight_snapshot_report
latticra_fedora_snapshot_capture_status_label
```

## Capture input

The caller supplies a bounded input structure with fields such as:

```text
os_release_text
os_release_text_len
os_release_readable
host_install_requested
ostree_booted_marker_present
rpm_command_present
dnf_command_present
rpmbuild_command_present
rpmlint_command_present
local_rpm_path
local_rpm_path_len
local_rpm_readable
running_as_root
operator_privilege_assertion
network_required
package_is_doc_only
command_entrypoint_expected
```

The implementation does not read live files or probe live commands. It only consumes these supplied facts.

## What changed

The implementation adds:

```text
bounded os-release ID parsing
bounded os-release ID_LIKE parsing
local RPM path recording
immutable Fedora marker propagation
RPM tooling presence propagation
conservative root/operator privilege propagation
network-required propagation
current doc-only package posture propagation
classifier forwarding
snapshot capture report generation
```

## Report surface

The capture report begins with:

```text
FEDORA INSTALL PREFLIGHT SNAPSHOT CAPTURE
```

Required report fields include:

```text
snapshot_capture_status=captured
os_id=fedora
os_id_like=rhel fedora
classifier_classification=ready-local-rpm
classifier_denial=none
snapshot_forwarded_to_classifier=1
os_release_read_allowed=1
command_probe_allowed=1
local_rpm_probe_allowed=1
sudo_validation_allowed=0
install_command_allowed=0
package_build_allowed=0
network_allowed=0
host_mutation_performed=0
host_install_performed=0
no_effect=1
evidence_level=2
```

## Failure behavior

The capture path fails closed.

Unreadable or missing os-release text produces a partial capture and forwards an empty host identity into the classifier. The classifier then blocks the host as non-Fedora instead of assuming eligibility.

Network-required lanes remain blocked by the classifier.

Doc-only package posture blocks runtime-command expectations.

Immutable Fedora markers are forwarded as future-gated install lanes.

## Validation

This implementation is guarded by:

```sh
sh scripts/test-fedora-install-preflight-snapshot-capture.sh
```

Expected output:

```text
fedora_install_preflight_snapshot_capture: ok
```

The implementation document guard is:

```sh
sh scripts/test-fedora-install-preflight-snapshot-capture-docs.sh
```

Expected output:

```text
fedora_install_preflight_snapshot_capture_docs: ok
```

## Non-claims

This implementation does not install Latticra, perform host mutation, open the network, validate sudo, create package artifacts, perform package build behavior, perform package install behavior, start services, change boot entries, load kernel modules, claim Fedora package approval, or claim production installer readiness.
