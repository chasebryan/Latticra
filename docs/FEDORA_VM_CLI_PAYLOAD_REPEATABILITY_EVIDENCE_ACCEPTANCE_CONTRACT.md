# Fedora VM CLI Payload Repeatability Evidence Acceptance Contract

Status: acceptance contract
Evidence level: 9 repeatability target, contract only
Scope: define the future evidence status record after a real Fedora VM repeatability transcript is validated and accepted.

## Purpose

This contract defines the exact fields required before Fedora VM CLI payload repeatability evidence can be written as accepted.

It does not run the repeatability runner.

It does not validate a live transcript.

It does not attach a transcript.

It does not write an evidence status record.

It does not accept repeatability evidence.

It does not mutate a host.

## Required source records

The acceptance contract depends on:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh
scripts/run-fedora-vm-cli-payload-repeatability-lane.sh
README.md
```

## Required future acceptance prerequisites

A future accepted evidence status record requires all of these prerequisites:

```text
repeatability_transcript_attached=1
repeatability_transcript_reviewed=1
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
repeatability_transcript_accepted=1
evidence_status_written=1
```

## Future evidence status record

The future accepted status record must include:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS
Status: evidence status alignment
source=operator disposable Fedora VM repeatability transcript
transcript_kind=disposable-vm-cli-payload-repeatability
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=1
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
source_tree_revision_recorded=1
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
spec_checksum_recorded=1
source_archive_checksum_recorded=1
rpm_nevra_recorded=1
rpm_payload_matches_expected_cli_surfaces=1
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
```

## Current acceptance gate state

The current repository state is still blocked:

```text
fedora_vm_cli_payload_repeatability_evidence_acceptance_contract_present=1
repeatability_transcript_attached=0
repeatability_transcript_reviewed=0
repeatability_transcript_candidate_valid=0
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

Repeatability evidence can only be accepted after a manual disposable Fedora VM run produces a complete transcript, the transcript validator accepts the candidate markers and values, and an operator review confirms the evidence review gate.

The acceptance contract alone cannot promote evidence.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-acceptance-contract.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_evidence_acceptance_contract: ok
```

## Next recommended lane

```text
Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript candidate, and write accepted repeatability evidence status
```

## Non-claims

This contract is not repeatability evidence, not a completed transcript, not a second disposable Fedora VM validation run, not an RPM build, not an RPM install, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
