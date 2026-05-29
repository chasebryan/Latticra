# Fedora VM CLI Payload Repeatability Transcript Review Validator

Status: no-effect transcript review validator
Evidence level: 9 repeatability target, validator only
Scope: validate a supplied Fedora VM CLI payload repeatability transcript candidate without promoting evidence.

## Purpose

This validator checks a supplied transcript candidate before any repeatability evidence status can be written.

It verifies that required transcript markers are present.

It rejects placeholder values in required value-bearing fields.

It does not run the repeatability runner.

It does not build an RPM.

It does not install or remove an RPM.

It does not mutate a host.

It does not accept repeatability evidence by itself.

```text
fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1
repeatability_transcript_review_mode=no-effect-validation
repeatability_transcript_candidate_valid=0
repeatability_transcript_reviewed=0
repeatability_transcript_accepted=0
evidence_status_written=0
promotion_allowed_by_validator_alone=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
```

## Command

```sh
sh scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh --transcript <path>
```

The command reads the supplied transcript candidate and emits a no-effect review report.

The validator does not create or modify status files.

## Required value fields

The validator rejects missing or placeholder values for:

```text
source_tree_revision
fedora_kernel_version
spec_checksum
source_archive_checksum
rpm_nevra
```

It also checks that checksum fields are SHA-256-shaped, that the source revision is a hex revision, and that the RPM NEVRA is for the local Latticra package.

## Successful candidate report

A structurally valid supplied transcript produces:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT REVIEW
review_status=ok
fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1
repeatability_transcript_review_mode=no-effect-validation
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=0
evidence_status_written=0
promotion_allowed_by_validator_alone=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Current validator state

```text
fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1
repeatability_transcript_review_mode=no-effect-validation
repeatability_transcript_candidate_valid=0
repeatability_transcript_reviewed=0
repeatability_transcript_accepted=0
evidence_status_written=0
promotion_allowed_by_validator_alone=0
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

This validator is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_transcript_review_validator: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate the transcript candidate, and then add reviewed evidence status
```

## Non-claims

This validator is not repeatability evidence, not a completed transcript, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
