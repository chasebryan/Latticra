# Fedora Live Read-Only Snapshot Adapter

Status: implementation record
Scope: live read-only host fact capture for Fedora install preflight.
Evidence level: 3

## Purpose

This implementation adds the first live host adapter for the Fedora install preflight path.

The adapter performs bounded read-only probes and forwards the collected facts into the existing Fedora install preflight snapshot capture API.

This is real implementation work, but it is not a host-install mutation lane.

## Public API

Primary header:

```text
include/latticra/fedora_live_snapshot_adapter.h
```

Primary source:

```text
src/fedora_live_snapshot_adapter.c
```

The main entry points are:

```text
latticra_fedora_live_snapshot_adapter_capture
latticra_fedora_live_snapshot_adapter_report
latticra_fedora_live_snapshot_adapter_status_label
```

## Live read-only probes

The adapter may perform these bounded read-only actions:

```text
read os-release text from the configured path
probe command presence through PATH
probe local RPM readability
probe immutable Fedora marker existence
record effective root status
```

The default os-release path is:

```text
/etc/os-release
```

Tests use fixture paths and fake PATH commands so CI does not depend on the runner being Fedora.

## Report surface

The report begins with:

```text
FEDORA LIVE READ-ONLY SNAPSHOT ADAPTER
```

Required report fields include:

```text
adapter_status=captured
live_probe_performed=1
os_release_read_attempted=1
command_probe_performed=1
local_rpm_probe_performed=1
ostree_marker_probe_performed=1
id_probe_performed=1
capture_status=captured
classifier_classification=ready-local-rpm
snapshot_forwarded_to_classifier=1
sudo_validation_allowed=0
install_command_allowed=0
package_build_allowed=0
network_allowed=0
host_mutation_performed=0
host_install_performed=0
no_effect=1
evidence_level=3
```

## Failure behavior

The adapter fails closed.

If os-release text cannot be read, the adapter records a partial capture and forwards the snapshot to the classifier. The classifier blocks unknown or non-Fedora hosts instead of assuming eligibility.

If the local RPM path is missing or unreadable, the classifier blocks the install candidate.

If the host is immutable Fedora, the classifier future-gates the lane.

If a network-dependent path is requested, the classifier blocks it.

## Validation

This implementation is guarded by:

```sh
sh scripts/test-fedora-live-snapshot-adapter.sh
```

Expected output:

```text
fedora_live_snapshot_adapter: ok
```

The implementation document guard is:

```sh
sh scripts/test-fedora-live-snapshot-adapter-docs.sh
```

Expected output:

```text
fedora_live_snapshot_adapter_docs: ok
```

## Non-claims

This implementation does not install Latticra, mutate the host, validate sudo, create package artifacts, build packages, install packages, open the network, start services, change boot entries, load kernel modules, claim Fedora approval, or claim production installer readiness.
