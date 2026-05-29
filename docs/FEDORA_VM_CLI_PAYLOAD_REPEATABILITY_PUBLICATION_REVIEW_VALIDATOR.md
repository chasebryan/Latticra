# Fedora VM CLI Payload Repeatability Publication Review Validator

Status: no-effect publication review validator
Evidence level: 9 repeatability target, validator only
Scope: validate a supplied Fedora VM CLI payload repeatability publication review candidate without approving, writing, or publishing evidence.

## Purpose

This validator checks a supplied future operator publication review candidate after a real disposable Fedora VM repeatability transcript and evidence status candidate have been validated and reviewed.

It does not run the repeatability runner.

It does not validate a live transcript.

It does not write an evidence status record.

It does not approve publication by itself.

It does not publish repeatability evidence.

It does not mutate a host.

```text
fedora_vm_cli_payload_repeatability_publication_review_template_present=1
fedora_vm_cli_payload_repeatability_publication_review_validator_present=1
publication_review_validation_mode=no-effect-validation
publication_review_candidate_valid=0
publication_review_reviewed=0
publication_review_approved_by_validator=0
evidence_status_written_by_validator=0
repeatability_evidence_published_by_validator=0
promotion_allowed_by_publication_review_validator_alone=0
operator_publication_review_completed=0
repeatability_evidence_publication_approved=0
repeatability_evidence_status_published=0
repeatability_transcript_accepted=0
evidence_status_written=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Command

```sh
sh scripts/fedora-vm-cli-payload-repeatability-publication-review.sh --review <path>
```

## Required source records

The validator depends on:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
scripts/fedora-vm-cli-payload-repeatability-publication-review-template.sh
scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh
README.md
```

## Accepted candidate requirements

A supplied candidate must contain the future publication review shape from the template:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW
publication_review_status=approved-for-publication
transcript_review_output_attached=1
evidence_status_review_output_attached=1
transcript_checksum_matches_status=1
source_revision_matches_status=1
status_candidate_validator_passed=1
publication_gate_reviewed=1
non_claims_reviewed=1
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
repeatability_evidence_status_published=1
evidence_status_written=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

The validator rejects placeholder values for:

```text
publication_review_date
operator_reviewer
published_status_path
```

## Validator output

For a valid candidate, the validator prints:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION
review_validation_status=ok
fedora_vm_cli_payload_repeatability_publication_review_validator_present=1
publication_review_validation_mode=no-effect-validation
publication_review_candidate_valid=1
publication_review_placeholder_values_absent=1
publication_review_required_markers_present=1
publication_review_value_fields_validated=1
publication_review_reviewed=1
candidate_operator_publication_review_completed=1
candidate_repeatability_evidence_publication_approved=1
candidate_repeatability_evidence_status_published=1
publication_review_approved_by_validator=0
evidence_status_written_by_validator=0
repeatability_evidence_published_by_validator=0
promotion_allowed_by_publication_review_validator_alone=0
host_mutation_performed=0
```

## Validation

This validator is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-publication-review-validator.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_publication_review_validator: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, then validate the filled publication review candidate
```

## Non-claims

This validator is not repeatability evidence, not a completed transcript, not an accepted evidence status record, not a published evidence status record, not an operator approval by itself, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
