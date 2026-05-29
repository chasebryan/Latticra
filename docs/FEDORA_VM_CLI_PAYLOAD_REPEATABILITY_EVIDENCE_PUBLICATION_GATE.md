# Fedora VM CLI Payload Repeatability Evidence Publication Gate

Status: publication gate contract
Evidence level: 9 repeatability target, gate only
Scope: prevents a passing evidence status candidate review from being treated as published Fedora repeatability evidence.

## Purpose

This gate defines the final publication boundary after the transcript review validator and the evidence status review validator.

It does not run the repeatability runner.

It does not validate a live transcript.

It does not attach a transcript.

It does not write an evidence status record.

It does not publish repeatability evidence.

It does not mutate a host.

## Required source records

The publication gate depends on:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md
scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh
scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh
README.md
```

## Required future publication prerequisites

A future publication record requires all of these prerequisites:

```text
repeatability_transcript_attached=1
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=1
repeatability_evidence_status_candidate_valid=1
repeatability_evidence_status_reviewed=1
candidate_repeatability_transcript_accepted=1
candidate_cli_payload_repeatability_evidence_present=1
candidate_evidence_status_written=1
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
evidence_status_written=1
cli_payload_repeatability_evidence_present=1
```

The evidence status review validator alone cannot publish evidence:

```text
repeatability_evidence_status_accepted_by_validator=0
evidence_status_written_by_validator=0
promotion_allowed_by_status_validator_alone=0
```

## Current publication gate state

The current repository state is still blocked:

```text
fedora_vm_cli_payload_repeatability_evidence_publication_gate_present=1
fedora_vm_cli_payload_repeatability_evidence_status_review_validator_present=1
repeatability_evidence_status_candidate_valid=0
repeatability_evidence_status_reviewed=0
repeatability_evidence_status_accepted_by_validator=0
evidence_status_written_by_validator=0
promotion_allowed_by_status_validator_alone=0
repeatability_evidence_publication_requested=0
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

## Publication rule

The only acceptable publication path is:

```text
1. Run the manual disposable Fedora VM repeatability lane in a disposable Fedora VM.
2. Attach the complete transcript.
3. Validate the transcript candidate with scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh.
4. Fill the evidence status template from the reviewed transcript.
5. Validate the evidence status candidate with scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh.
6. Complete an operator publication review.
7. Only then write a published evidence status record.
```

## Validation

This gate is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-publication-gate.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_evidence_publication_gate: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, then complete operator publication review
```

## Non-claims

This gate is not repeatability evidence, not a completed transcript, not an accepted evidence status record, not a published evidence status record, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
