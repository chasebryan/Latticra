# Fedora VM CLI Payload Repeatability Publication Receipt Acceptance Validator

Status: no-effect publication receipt acceptance validator
Evidence level: 9 repeatability target, validator only
Scope: validate a supplied Fedora VM CLI payload repeatability publication receipt acceptance candidate without accepting, writing, or publishing evidence.

## Purpose

This validator checks a supplied future receipt acceptance candidate after a publication receipt candidate has already been validated and reviewed by a separate operator-controlled process.

It does not run the repeatability runner.

It does not validate a live transcript.

It does not validate a publication receipt candidate.

It does not write an evidence status record.

It does not approve publication.

It does not publish repeatability evidence.

It does not write or accept a receipt by itself.

It does not mutate a host.

```text
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_template_present=1
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator_present=1
publication_receipt_acceptance_validation_mode=no-effect-validation
publication_receipt_acceptance_candidate_valid=0
publication_receipt_acceptance_reviewed=0
publication_receipt_accepted_by_acceptance_validator=0
publication_receipt_written_by_acceptance_validator=0
repeatability_evidence_published_by_acceptance_validator=0
promotion_allowed_by_publication_receipt_acceptance_validator_alone=0
publication_receipt_candidate_valid=0
publication_receipt_reviewed=0
publication_receipt_accepted=0
publication_receipt_written=0
publication_receipt_attached=0
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
sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance.sh --acceptance <path>
```

## Required source records

The validator depends on:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_TEMPLATE.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_TEMPLATE_STATUS.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md
scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-template.sh
scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh
README.md
```

## Accepted candidate requirements

A supplied candidate must contain the future acceptance shape from the template:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE
publication_receipt_acceptance_status=accepted
publication_receipt_candidate_valid=1
publication_receipt_placeholder_values_absent=1
publication_receipt_required_markers_present=1
publication_receipt_value_fields_validated=1
publication_receipt_reviewed=1
publication_receipt_accepted=1
publication_receipt_written=1
publication_receipt_attached=1
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

The validator rejects placeholder values such as:

```text
<required-after-status-publication>
<required-after-operator-review>
<placeholder>
TODO
TBD
```

## Validator output

For a valid candidate, the validator prints:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION
acceptance_validation_status=ok
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator_present=1
publication_receipt_acceptance_validation_mode=no-effect-validation
publication_receipt_acceptance_candidate_valid=1
publication_receipt_acceptance_placeholder_values_absent=1
publication_receipt_acceptance_required_markers_present=1
publication_receipt_acceptance_value_fields_validated=1
publication_receipt_acceptance_reviewed=1
candidate_publication_receipt_accepted=1
candidate_publication_receipt_written=1
candidate_publication_receipt_attached=1
candidate_repeatability_evidence_status_published=1
publication_receipt_accepted_by_acceptance_validator=0
publication_receipt_written_by_acceptance_validator=0
repeatability_evidence_published_by_acceptance_validator=0
promotion_allowed_by_publication_receipt_acceptance_validator_alone=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Validation

This validator is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-validator.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, validate publication review and receipt candidates, then submit a filled receipt acceptance candidate to this validator
```

## Non-claims

This validator is not repeatability evidence, not a completed transcript, not an accepted evidence status record, not a published evidence status record, not an accepted publication receipt, not an operator approval, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
