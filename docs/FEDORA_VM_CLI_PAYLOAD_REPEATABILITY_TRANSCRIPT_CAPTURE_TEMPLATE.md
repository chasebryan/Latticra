# Fedora VM CLI Payload Repeatability Transcript Capture Template

Status: no-effect repeatability transcript capture template
Evidence level: 9 repeatability target, template only
Scope: future transcript capture shape for the second disposable Fedora VM validation run of the no-effect CLI RPM payload.

## Purpose

This template defines the transcript shape an operator should attach after a real disposable Fedora VM repeatability run.

It is a capture template only.

It does not run the repeatability runner.

It does not build an RPM.

It does not install or remove an RPM.

It does not mutate a host.

It does not mark repeatability evidence present.

```text
fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1
repeatability_transcript_template_mode=no-effect-template
repeatability_transcript_template_decision=blocked-template-only-no-vm-execution
repeatability_transcript_template_complete=0
repeatability_runner_executed=0
rpm_build_performed=0
rpm_install_performed=0
rpm_removal_performed=0
host_mutation_performed=0
repeatability_transcript_attached=0
repeatability_transcript_reviewed=0
repeatability_transcript_accepted=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
```

## Command

```sh
sh scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh
```

The command emits a deterministic transcript capture template to stdout.

It validates that the repeatability transcript contract, repeatability runner plan, evidence review gate, prior CLI payload evidence status, and repeatability runner are present before printing the template.

The review validator companion is:

```sh
sh scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh --transcript <path>
```

It checks a supplied transcript candidate for required markers and rejects placeholder values without accepting evidence by itself.

## Required operator context

The future transcript must be captured from:

```text
target_required=disposable-fedora-vm
operator_review_required=1
clean_snapshot_required=1
recovery_path_required=1
prior_cli_payload_evidence_required=1
runner_path=scripts/run-fedora-vm-cli-payload-repeatability-lane.sh
```

## Required future transcript fields

The capture template includes these required transcript sections:

```text
[transcript_header]
[prior_evidence]
[runner_report_required_fields]
[review_gate]
[non_claims]
```

The future accepted transcript must replace placeholder values for:

```text
source_tree_revision
fedora_kernel_version
spec_checksum
source_archive_checksum
rpm_nevra
```

Review validator:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md
scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh
```

## Current template state

```text
fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1
fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1
repeatability_transcript_template_mode=no-effect-template
repeatability_transcript_template_complete=0
repeatability_transcript_candidate_valid=0
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

## Validation

This template is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_transcript_template: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate the transcript candidate, and then add reviewed evidence status
```

## Non-claims

This template is not repeatability evidence, not a completed transcript, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
