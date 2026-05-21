# Fedora Disposable VM Effect Gate

Status: gate record
Evidence level: 8 target, gate only
Scope: define the evidence boundary for a future Fedora disposable VM effect lane.

## Purpose

Latticra has installroot mutation evidence and Fedora transcript evidence contracts.

This gate defines when the project may consider a future disposable Fedora VM effect lane reviewable.

This is a gate record only.

It does not add runtime behavior.

## Required target evidence

```text
target_is_disposable_fedora_vm=1
target_is_daily_driver=0
target_is_production_host=0
target_is_immutable_fedora=0
target_has_clean_snapshot=1
target_has_recovery_path=1
operator_consent_recorded=1
```

## Required package evidence

```text
local_rpm_built_from_current_tree=1
rpm_name_is_latticra=1
rpm_version_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
```

## Required prior evidence

```text
installroot_lifecycle_evidence_present=1
post_removal_absence_evidence_present=1
manual_host_dry_run_transcript_contract_present=1
manual_host_rc_decision_classifier_present=1
rpm_gate_allowed=1
removal_rollback_ready=1
```

## Effect eligibility decision

The gate decision must be one of:

```text
disposable_vm_effect_gate_status=eligible
disposable_vm_effect_gate_status=blocked
disposable_vm_effect_gate_status=invalid
```

`eligible` means the evidence set is ready for review.

It does not mean production readiness.

## Boundary fields

```text
effect_gate_present=1
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_allowed=0
production_host_allowed=0
immutable_host_allowed=0
```

## Block conditions

```text
daily_driver_detected=1
production_host_detected=1
immutable_fedora_detected=1
snapshot_missing=1
recovery_path_missing=1
operator_consent_missing=1
rpm_payload_listing_missing=1
rpm_payload_not_documentation_only=1
unexpected_runtime_surface_present=1
prior_installroot_evidence_missing=1
prior_transcript_contract_missing=1
prior_decision_classifier_missing=1
prior_gate_evidence_missing=1
prior_removal_rollback_evidence_missing=1
```

## Validation

```sh
sh scripts/test-fedora-disposable-vm-effect-gate.sh
```

Expected output:

```text
fedora_disposable_vm_effect_gate: ok
```

## Next recommended Fedora lane

```text
Implement no-effect Fedora disposable VM effect gate classifier
```

That classifier should consume explicit evidence fields and report `eligible`, `blocked`, or `invalid`.

## README overhaul hold

The root README should not claim install readiness from this gate alone.

The README overhaul should wait until real validation evidence exists for:

```text
manual_host_dry_run_transcript_present=1
live_host_validation_completed=1
host_install_ready=1
```

## Non-claims

This gate is not production readiness, Fedora approval, or Fedora distribution readiness.
