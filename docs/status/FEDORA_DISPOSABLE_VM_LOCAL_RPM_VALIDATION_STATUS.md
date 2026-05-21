# Fedora Disposable VM Local RPM Validation Status

Status: status alignment
Date: 2026-05-21
Scope: public status record after the gated disposable Fedora VM local RPM validation lane landed on `main`.

## Summary

Latticra now has a manually gated disposable Fedora VM local RPM validation lane.

The lane defines and ships:

```text
docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md
scripts/run-fedora-disposable-vm-local-rpm-validation-lane.sh
scripts/test-fedora-disposable-vm-local-rpm-validation-lane-docs.sh
.github/workflows/fedora-vm-rpm-validation-lane-docs.yml
```

This is lane-readiness evidence only.

It does not prove that a disposable Fedora VM validation run has completed yet.

The validation runner remains manually gated and must not be auto-run by normal CI.

## Evidence recorded

```text
Fedora disposable VM local RPM validation lane
source=PR #223
validation_lane_documented=1
validation_runner_present=1
validation_lane_docs_guard_present=1
validation_lane_docs_workflow_present=1
runner_manual_only=1
ci_auto_vm_rpm_validation_allowed=0
disposable_vm_target_required=1
daily_driver_block_required=1
production_host_block_required=1
immutable_fedora_block_required=1
clean_snapshot_required=1
recovery_path_required=1
operator_consent_required=1
rpm_payload_listing_required=1
rpm_payload_documentation_only_required=1
unexpected_runtime_surface_absent_required=1
validation_report_schema_present=1
target_evidence_level=9
current_evidence_level=8
evidence_level_9_achieved=0
```

## Current readiness classification

```text
manual_host_dry_run_transcript_contract_present=1
disposable_vm_effect_gate_present=1
disposable_vm_effect_gate_classifier_present=1
disposable_vm_local_rpm_validation_lane_present=1
disposable_vm_local_rpm_validation_status=blocked-pending-real-vm-run
disposable_vm_validation_transcript_present=0
disposable_vm_validation_completed=0
live_host_validation_completed=0
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Boundary statement

This status alignment does not run the validation lane.

It does not install or remove an RPM.

It does not mutate a disposable VM, developer host, daily-driver Fedora host, immutable Fedora host, production host, boot entry, kernel module set, service registry, SELinux policy, firmware state, or network configuration.

The docs guard may run in CI.

The RPM validation runner must remain manual and gated by explicit disposable-VM evidence.

## Guard validation

The validation lane documentation is guarded by:

```sh
sh scripts/test-fedora-disposable-vm-local-rpm-validation-lane-docs.sh
```

This status alignment is guarded by:

```sh
sh scripts/test-fedora-disposable-vm-local-rpm-validation-status-alignment.sh
```

Expected output:

```text
fedora_disposable_vm_local_rpm_validation_lane_docs: ok
fedora_disposable_vm_local_rpm_validation_status_alignment: ok
```

## Next recommended Fedora lane

```text
Capture disposable Fedora VM local RPM validation transcript evidence
```

That lane should record the Fedora VM identity, clean snapshot evidence, recovery path evidence, package version, RPM payload listing, install transcript, removal transcript, post-removal absence proof, and emitted validation report.

## README overhaul hold

The root README should not claim install readiness yet.

The README overhaul remains blocked until real validation evidence exists for:

```text
disposable_vm_validation_transcript_present=1
disposable_vm_validation_completed=1
live_host_validation_completed=1
host_install_ready=1
```

## Non-claims

This status record is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, or a production installer claim.
