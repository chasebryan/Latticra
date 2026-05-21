# Fedora RPM Gate Classifier

Status: implementation record
Scope: pure Fedora local RPM gate classification after live read-only preflight evidence.
Evidence level: 4

## Purpose

This implementation adds the first Fedora RPM gate classifier after the local RPM gate contract.

The classifier evaluates the required evidence fields and reports whether the local RPM gate is allowed or denied.

It does not execute any host-changing action.

## Public API

Primary header:

```text
include/latticra/fedora_rpm_gate.h
```

Primary source:

```text
src/fedora_rpm_gate.c
```

The main entry points are:

```text
latticra_fedora_rpm_gate_classify
latticra_fedora_rpm_gate_report
latticra_fedora_rpm_gate_status_label
latticra_fedora_rpm_gate_denial_label
```

## Required allow evidence

The classifier reports `allowed` only when every required fact is present:

```text
fedora_host=1
mutable_fedora_host=1
immutable_host=0
local_rpm_present=1
root_or_sudo_available=1
network_required=0
operator_install_confirmation=1
dry_run_passed=1
rollback_or_remove_plan_present=1
preflight_classification=ready-local-rpm
preflight_denial=none
snapshot_captured=1
live_probe_performed=1
```

All other combinations report `denied`.

## Deterministic denial reasons

The classifier reports denial reasons including:

```text
not-fedora-host
immutable-fedora-host
local-rpm-missing
privilege-missing
network-required
operator-confirmation-missing
dry-run-missing
rollback-plan-missing
preflight-not-ready
preflight-denied
live-probe-missing
invalid-gate-input
```

## Report surface

The report begins with:

```text
FEDORA LOCAL RPM INSTALL MUTATION GATE
```

Required report fields include:

```text
install_gate_status=allowed
install_gate_denial=none
install_mutation_allowed=1
install_mutation_performed=0
host_mutation_performed=0
network_allowed=0
evidence_level=4
```

Denied reports preserve:

```text
install_mutation_allowed=0
install_mutation_performed=0
host_mutation_performed=0
network_allowed=0
```

## Validation

This implementation is guarded by:

```sh
sh scripts/test-fedora-rpm-gate-classifier.sh
```

Expected output:

```text
fedora_rpm_gate_classifier: ok
```

The implementation document guard is:

```sh
sh scripts/test-fedora-rpm-gate-classifier-docs.sh
```

Expected output:

```text
fedora_rpm_gate_classifier_docs: ok
```

## Boundary

This implementation is a classifier only.

It does not execute package actions, validate sudo, build packages, open the network, start services, change boot entries, load kernel modules, claim Fedora approval, or claim production installer readiness.
