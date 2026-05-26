# Fedora VM CLI Payload Repeatability Evidence Review Gate

Status: review gate contract
Evidence level: 9 repeatability target, gate only
Scope: define the review gate before a second disposable Fedora VM CLI payload validation transcript can be accepted as repeatability evidence.

## Purpose

This gate prevents the manual repeatability runner from being treated as completed evidence until a real disposable Fedora VM transcript is attached and reviewed.

It does not run the repeatability runner.

It does not execute RPM commands.

It does not install or remove an RPM.

It does not mutate a host.

It does not mark repeatability evidence present.

## Required source records

The review gate depends on:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh
scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh
scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh
scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh
scripts/run-fedora-vm-cli-payload-repeatability-lane.sh
scripts/test-fedora-vm-cli-payload-repeatability-runner.sh
README.md
```

## Required attached transcript markers

A future accepted transcript must include:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_version=1
operator_review_required=1
repeatability_transcript_recorded_after_real_run=1
prior_cli_payload_evidence_recorded=1
FEDORA VM CLI PAYLOAD REPEATABILITY LANE
validation_status=ok
repeatability_validation_status=ok
source_tree_revision_recorded=1
source_tree_revision=
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
fedora_kernel_version=
spec_checksum_recorded=1
spec_checksum=
source_archive_checksum_recorded=1
source_archive_checksum=
rpm_nevra_recorded=1
rpm_nevra=
package_name=latticra
package_version=0.0.0
rpm_payload_listing_recorded=1
rpm_payload_matches_expected_cli_surfaces=1
unexpected_runtime_surface_absent=1
cli_status_output_recorded=1
cli_version_output_recorded=1
cli_report_output_recorded=1
cli_invalid_command_exit_recorded=1
validated_cli_mode_still_no_effect=1
validated_runtime_behavior_still_disabled=1
validated_non_claims_preserved=1
rpm_verify_completed=1
removal_validation_performed=1
post_removal_absence_verified=1
second_disposable_vm_cli_validation_completed=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
fedora_vm_cli_payload_repeatability_lane: ok
```

The value-bearing fields must not be placeholders in a future accepted transcript:

```text
source_tree_revision
fedora_kernel_version
spec_checksum
source_archive_checksum
rpm_nevra
```

## Current gate state

```text
fedora_vm_cli_payload_repeatability_evidence_review_gate_present=1
fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1
fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1
repeatability_transcript_template_mode=no-effect-template
repeatability_transcript_template_complete=0
repeatability_transcript_candidate_valid=0
repeatability_transcript_review_required=1
repeatability_transcript_attached=0
repeatability_transcript_reviewed=0
repeatability_transcript_accepted=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Review rule

The only acceptable promotion path is:

```text
1. Print scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh before the manual run.
2. Run scripts/run-fedora-vm-cli-payload-repeatability-lane.sh manually inside a disposable Fedora VM.
3. Attach the complete transcript using the capture template shape.
4. Validate the transcript candidate with scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh.
5. Review the transcript against this gate and the repeatability transcript contract.
6. Only then add an evidence status record with repeatability_transcript_accepted=1.
```

## Validation

This gate is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-review-gate.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_evidence_review_gate: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate the transcript candidate, and then add reviewed evidence status
```

## Non-claims

This gate is not repeatability evidence, not a completed transcript, not a second disposable Fedora VM validation run, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
