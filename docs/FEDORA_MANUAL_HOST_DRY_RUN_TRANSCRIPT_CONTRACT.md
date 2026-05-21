# Fedora Manual Host Dry-Run Transcript Contract

Status: contract record
Evidence level: 8 target, contract only
Scope: transcript schema for a future disposable Fedora VM validation review.

## Purpose

Latticra has a manual Fedora RC checklist and a no-effect RC decision classifier.

This contract defines the transcript fields required before a future disposable Fedora VM validation record can be reviewed.

This is an evidence schema only.

It does not execute anything.

## Required transcript header

```text
LATTICRA FEDORA MANUAL HOST DRY-RUN TRANSCRIPT
transcript_kind=dry-run
transcript_version=1
operator_review_required=1
host_change_performed=0
```

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
host_preflight_ready_local_rpm=1
rpm_gate_allowed=1
removal_rollback_ready=1
manual_host_rc_decision_classifier_present=1
```

## Required no-effect fields

```text
manual_host_dry_run_transcript_present=1
live_host_validation_completed=0
host_change_performed=0
sudo_invoked=0
rpm_invoked=0
dnf_invoked=0
network_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
kernel_operation_allowed=0
policy_operation_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Required review sections

```text
TARGET REVIEW
PACKAGE REVIEW
PRIOR EVIDENCE REVIEW
DRY-RUN DECISION REVIEW
NO-EFFECT BOUNDARY REVIEW
OPERATOR SIGNOFF PLACEHOLDER
NEXT ACTION REVIEW
```

## Dry-run decision states

```text
dry_run_transcript_status=accepted-for-review
dry_run_transcript_status=blocked
dry_run_transcript_status=invalid
```

`accepted-for-review` means the transcript is complete enough for review.

It does not mean live validation is complete.

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
prior_removal_evidence_missing=1
prior_preflight_evidence_missing=1
prior_gate_evidence_missing=1
prior_removal_rollback_evidence_missing=1
network_requirement_detected=1
service_boundary_detected=1
boot_boundary_detected=1
kernel_boundary_detected=1
policy_boundary_detected=1
```

## Validation

```sh
sh scripts/test-fedora-manual-host-dry-run-transcript-contract.sh
```

Expected output:

```text
fedora_manual_host_dry_run_transcript_contract: ok
```

## Next recommended Fedora lane

```text
Implement no-effect Fedora dry-run transcript classifier
```

## README overhaul hold

The root README should wait until real validation evidence exists for:

```text
manual_host_dry_run_transcript_present=1
live_host_validation_completed=1
host_install_ready=1
```

## Non-claims

This contract is not production readiness, Fedora approval, or Fedora distribution readiness.
