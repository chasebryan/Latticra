# Fedora VM CLI Payload Repeatability Publication Receipt Acceptance Promotion Gate

Status: no-effect receipt acceptance promotion gate
Evidence level: 9 repeatability target, promotion gate only
Scope: classify a validated Fedora VM CLI payload repeatability publication receipt acceptance report without promoting it to production installer readiness or Fedora distribution readiness.

## Purpose

This gate defines the boundary after the receipt acceptance validator.

It allows a future receipt acceptance validation report to be checked as a prerequisite record.

It does not run the repeatability runner.

It does not validate a live transcript.

It does not validate a publication receipt candidate.

It does not write an evidence status record.

It does not approve publication.

It does not publish repeatability evidence.

It does not write or accept a receipt.

It does not promote Latticra to production installer readiness.

It does not promote Latticra to Fedora distribution readiness.

It does not mutate a host.

```text
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator_present=1
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate_present=1
publication_receipt_acceptance_promotion_gate_mode=no-effect-gate
publication_receipt_acceptance_validation_report_valid=0
publication_receipt_acceptance_promotion_requested=0
publication_receipt_accepted_by_promotion_gate=0
publication_receipt_written_by_promotion_gate=0
repeatability_evidence_published_by_promotion_gate=0
promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0
production_installer_promotion_allowed=0
fedora_distribution_promotion_allowed=0
publication_receipt_acceptance_candidate_valid=0
publication_receipt_acceptance_reviewed=0
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
sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh --acceptance-validation <path>
```

## Required source records

The gate depends on:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR_STATUS.md
scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance.sh
docs/FEDORA_READINESS_PLAN.md
README.md
```

## Accepted validation report requirements

A supplied report must contain the no-effect output shape from the receipt acceptance validator:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION
acceptance_validation_status=ok
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

## Gate output

For a valid no-effect acceptance validation report, the gate prints:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE PROMOTION GATE
promotion_gate_status=blocked
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate_present=1
publication_receipt_acceptance_validation_report_valid=1
publication_receipt_acceptance_candidate_valid=1
publication_receipt_acceptance_reviewed=1
candidate_publication_receipt_accepted=1
candidate_publication_receipt_written=1
candidate_publication_receipt_attached=1
candidate_repeatability_evidence_status_published=1
publication_receipt_accepted_by_promotion_gate=0
publication_receipt_written_by_promotion_gate=0
repeatability_evidence_published_by_promotion_gate=0
promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0
production_installer_promotion_allowed=0
fedora_distribution_promotion_allowed=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Promotion rule

A passing receipt acceptance validation report is only one Fedora CLI payload repeatability prerequisite.

The receipt acceptance promotion gate alone cannot accept a receipt, publish evidence, claim production installer readiness, claim Fedora approval, or claim Fedora distribution readiness.

## Validation

This gate is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate: ok
```

## Next recommended lane

```text
Use a filled receipt acceptance validation report as one prerequisite input to a broader Fedora production-readiness evidence matrix, while keeping production installer and Fedora distribution promotion blocked until the non-CLI-payload evidence exists
```

## Non-claims

This gate is not repeatability evidence, not a completed transcript, not an accepted evidence status record, not a published evidence status record, not an accepted publication receipt, not an operator approval, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
