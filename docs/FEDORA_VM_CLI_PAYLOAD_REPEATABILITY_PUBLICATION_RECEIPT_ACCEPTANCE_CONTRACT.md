# Fedora VM CLI Payload Repeatability Publication Receipt Acceptance Contract

Status: receipt acceptance contract
Evidence level: 9 repeatability target, contract only
Scope: define the future acceptance rule for a validated Fedora VM CLI payload repeatability publication receipt.

## Purpose

This contract defines the exact fields required before a Fedora VM CLI payload repeatability publication receipt can be treated as accepted.

It does not run the repeatability runner.

It does not validate a live transcript.

It does not validate a publication receipt candidate.

It does not write an evidence status record.

It does not approve publication.

It does not publish repeatability evidence.

It does not write or accept a receipt by itself.

It does not mutate a host.

## Required source records

The acceptance contract depends on:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md
scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh
scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh
README.md
```

## Required future acceptance prerequisites

A future accepted receipt record requires all of these prerequisites:

```text
publication_receipt_candidate_valid=1
publication_receipt_placeholder_values_absent=1
publication_receipt_required_markers_present=1
publication_receipt_value_fields_validated=1
publication_receipt_reviewed=1
candidate_publication_review_validated=1
candidate_repeatability_evidence_status_published=1
candidate_publication_receipt_written=1
publication_receipt_accepted=1
```

## Future accepted receipt record

The future accepted receipt record must include:

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

## Current acceptance gate state

The current repository state is still blocked:

```text
fedora_vm_cli_payload_repeatability_publication_receipt_validator_present=1
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_contract_present=1
publication_receipt_candidate_valid=0
publication_receipt_reviewed=0
publication_receipt_accepted_by_validator=0
publication_receipt_accepted=0
publication_receipt_written_by_validator=0
publication_receipt_written=0
publication_receipt_attached=0
repeatability_evidence_published_by_validator=0
promotion_allowed_by_publication_receipt_validator_alone=0
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

## Acceptance rule

A publication receipt can only be accepted after a receipt candidate validates, an operator confirms the publication review and evidence status references, and the receipt remains attached to the same published evidence status.

The receipt acceptance contract alone cannot accept a receipt.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_contract: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, validate publication review and receipt candidates, then perform operator receipt acceptance review
```

## Non-claims

This contract is not repeatability evidence, not a completed transcript, not an accepted evidence status record, not a published evidence status record, not an accepted publication receipt, not an operator approval, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
