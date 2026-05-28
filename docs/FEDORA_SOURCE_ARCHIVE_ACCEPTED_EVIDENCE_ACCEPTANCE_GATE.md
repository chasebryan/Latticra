# Fedora Source Archive Accepted Evidence Acceptance Gate

Status: no-effect source archive accepted evidence acceptance gate
Scope: classify a reviewed Fedora source archive accepted evidence status review report without writing evidence, accepting source archive evidence, opening mock build input, running RPM builds, or mutating a host.

## Purpose

This gate defines the boundary after the Fedora source archive accepted evidence status review validator.

It allows a future accepted evidence status review report to be checked as a prerequisite record.

It does not create a source archive.

It does not validate a live source archive transcript.

It does not run the source archive acceptance gate against a live report.

It does not attach source archive evidence.

It does not write source archive evidence status.

It does not accept source archive evidence by itself.

It does not open source archive evidence as mock build input by itself.

It does not run `tar` or `gzip`.

It does not run `rpmbuild`.

It does not run `mock`.

It does not create source RPM or binary RPM artifacts.

It does not install packages.

It does not submit Latticra to Fedora.

It does not mutate a host.

```text
fedora_source_archive_accepted_evidence_status_review_validator_present=1
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
source_archive_accepted_evidence_acceptance_gate_mode=no-effect-gate
source_archive_accepted_evidence_status_review_report_valid=0
source_archive_accepted_evidence_acceptance_requested=0
source_archive_accepted_evidence_status_candidate_valid=0
source_archive_accepted_evidence_status_reviewed=0
candidate_source_archive_accepted_evidence_status_written=0
candidate_source_archive_accepted_evidence_present=0
candidate_source_archive_accepted_for_build=0
candidate_fedora_mock_build_input_opened=0
source_archive_accepted_by_accepted_evidence_acceptance_gate=0
source_archive_accepted_evidence_status_written_by_acceptance_gate=0
source_archive_accepted_for_build_by_acceptance_gate_alone=0
fedora_mock_build_input_opened_by_acceptance_gate_alone=0
source_archive_accepted_evidence_status_written=0
source_archive_accepted_evidence_present=0
source_archive_accepted=0
source_archive_accepted_for_build=0
fedora_mock_build_input_opened=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Command

```sh
sh scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh --status-review <path>
```

## Required Source Records

The gate depends on:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md
scripts/fedora-source-archive-accepted-evidence-status-review.sh
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
packaging/fedora/latticra.spec
README.md
```

## Accepted Status Review Report Requirements

A supplied report must contain the no-effect output shape from the source archive accepted evidence status review validator:

```text
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS REVIEW
review_status=ok
fedora_source_archive_accepted_evidence_status_review_validator_present=1
source_archive_accepted_evidence_status_review_mode=no-effect-validation
source_archive_accepted_evidence_status_candidate_valid=1
source_archive_accepted_evidence_status_required_markers_present=1
source_archive_accepted_evidence_status_placeholder_values_absent=1
source_archive_accepted_evidence_status_value_fields_validated=1
source_archive_accepted_evidence_status_reviewed=1
candidate_source_archive_accepted_evidence_status_written=1
candidate_source_archive_accepted_evidence_present=1
candidate_source_archive_accepted_for_build=1
candidate_fedora_mock_build_input_opened=1
source_archive_accepted_evidence_status_accepted_by_validator=0
source_archive_accepted_evidence_status_written_by_validator=0
source_archive_accepted_for_build_by_status_validator_alone=0
fedora_mock_build_input_opened_by_status_validator_alone=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Gate Output

For a valid no-effect accepted evidence status review report, the gate prints:

```text
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE ACCEPTANCE GATE
acceptance_gate_status=blocked
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
source_archive_accepted_evidence_acceptance_gate_mode=no-effect-gate
source_archive_accepted_evidence_status_review_report_valid=1
source_archive_accepted_evidence_status_candidate_valid=1
source_archive_accepted_evidence_status_reviewed=1
candidate_source_archive_accepted_evidence_status_written=1
candidate_source_archive_accepted_evidence_present=1
candidate_source_archive_accepted_for_build=1
candidate_fedora_mock_build_input_opened=1
source_archive_accepted_evidence_acceptance_requested=0
source_archive_accepted_by_accepted_evidence_acceptance_gate=0
source_archive_accepted_evidence_status_written_by_acceptance_gate=0
source_archive_accepted_for_build_by_acceptance_gate_alone=0
fedora_mock_build_input_opened_by_acceptance_gate_alone=0
source_archive_accepted_evidence_status_written=0
source_archive_accepted_evidence_present=0
source_archive_accepted=0
source_archive_accepted_for_build=0
fedora_mock_build_input_opened=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Acceptance Rule

A passing accepted evidence status review report is only one source archive prerequisite.

The source archive accepted evidence acceptance gate alone cannot accept source archive evidence, write evidence, open mock build input, claim package review readiness, claim Fedora distribution readiness, or claim production readiness.

## Validation

This gate is guarded by:

```sh
sh scripts/test-fedora-source-archive-accepted-evidence-acceptance-gate.sh
```

Expected output:

```text
fedora_source_archive_accepted_evidence_acceptance_gate: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Non-claims

This gate is not a source archive transcript, not source archive acceptance, not written evidence status, not mock build evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
