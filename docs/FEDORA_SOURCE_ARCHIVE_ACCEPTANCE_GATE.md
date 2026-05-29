# Fedora Source Archive Acceptance Gate

Status: no-effect source archive acceptance gate
Scope: classify a validated Fedora source archive transcript review report without accepting source archive evidence, opening mock build input, running RPM builds, or mutating a host.

## Purpose

This gate defines the boundary after the Fedora source archive transcript review validator.

It allows a future transcript review report to be checked as a prerequisite record.

It does not create a source archive.

It does not write source archive evidence.

It does not accept source archive evidence.

It does not open source archive evidence as mock build input.

It does not run `tar` or `gzip`.

It does not run `rpmbuild`.

It does not run `mock`.

It does not create source RPM or binary RPM artifacts.

It does not install packages.

It does not submit Latticra to Fedora.

It does not claim Fedora package review readiness, Fedora distribution readiness, production installer readiness, or production readiness.

It does not mutate a host.

```text
fedora_source_archive_acceptance_gate_present=1
source_archive_acceptance_gate_mode=no-effect-gate
source_archive_transcript_review_report_valid=0
source_archive_acceptance_requested=0
source_archive_transcript_candidate_valid=0
source_archive_transcript_reviewed=0
candidate_source_archive_transcript_present=0
candidate_source_archive_reproducible=0
candidate_source_archive_repeated_sha256_match=0
candidate_source_archive_rpmlint_prerequisite_present=0
source_archive_accepted_by_acceptance_gate=0
source_archive_written_by_acceptance_gate=0
source_archive_accepted_for_build_by_acceptance_gate_alone=0
fedora_source_archive_accepted_evidence_status_template_present=1
fedora_source_archive_accepted_evidence_status_review_validator_present=1
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
source_archive_accepted_evidence_status_template_mode=no-effect-template
source_archive_accepted_evidence_status_template_complete=0
source_archive_accepted_evidence_status_review_mode=no-effect-validation
source_archive_accepted_evidence_status_candidate_valid=0
source_archive_accepted_evidence_status_reviewed=0
source_archive_accepted_evidence_status_accepted_by_validator=0
source_archive_accepted_evidence_status_written_by_validator=0
source_archive_accepted_for_build_by_status_validator_alone=0
fedora_mock_build_input_opened_by_status_validator_alone=0
source_archive_accepted_evidence_acceptance_gate_mode=no-effect-gate
source_archive_accepted_evidence_status_review_report_valid=0
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

## Command

```sh
sh scripts/fedora-source-archive-acceptance-gate.sh --transcript-review <path>
```

## Required Source Records

The gate depends on:

```text
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md
docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md
docs/status/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md
scripts/fedora-source-archive-transcript-review.sh
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
packaging/fedora/latticra.spec
README.md
```

## Accepted Transcript Review Report Requirements

A supplied report must contain the no-effect output shape from the source archive transcript review validator:

```text
FEDORA SOURCE ARCHIVE TRANSCRIPT REVIEW VALIDATION
source_archive_transcript_review_status=ok
fedora_source_archive_transcript_review_validator_present=1
source_archive_transcript_review_mode=no-effect-validation
source_archive_transcript_candidate_valid=1
source_archive_transcript_required_markers_present=1
source_archive_transcript_placeholder_values_absent=1
source_archive_transcript_value_fields_validated=1
candidate_source_archive_transcript_present=1
candidate_source_archive_reproducible=1
candidate_source_archive_repeated_sha256_match=1
candidate_source_archive_rpmlint_prerequisite_present=1
source_archive_transcript_reviewed=1
source_archive_accepted_by_transcript_validator=0
source_archive_written_by_transcript_validator=0
source_archive_accepted_for_build_by_transcript_validator_alone=0
source_archive_accepted_for_build=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Gate Output

For a valid no-effect transcript review report, the gate prints:

```text
FEDORA SOURCE ARCHIVE ACCEPTANCE GATE
source_archive_acceptance_gate_status=blocked
fedora_source_archive_acceptance_gate_present=1
source_archive_acceptance_gate_mode=no-effect-gate
source_archive_transcript_review_report_valid=1
source_archive_transcript_candidate_valid=1
source_archive_transcript_reviewed=1
candidate_source_archive_transcript_present=1
candidate_source_archive_reproducible=1
candidate_source_archive_repeated_sha256_match=1
candidate_source_archive_rpmlint_prerequisite_present=1
source_archive_acceptance_requested=0
source_archive_accepted_by_acceptance_gate=0
source_archive_written_by_acceptance_gate=0
source_archive_accepted_for_build_by_acceptance_gate_alone=0
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

A passing transcript review report is only one source archive prerequisite.

The source archive acceptance gate alone cannot accept source archive evidence, write evidence, open mock build input, claim package review readiness, claim Fedora distribution readiness, or claim production readiness.

## Validation

This gate is guarded by:

```sh
sh scripts/test-fedora-source-archive-acceptance-gate.sh
```

Expected output:

```text
fedora_source_archive_acceptance_gate: ok
```

## Completed Follow-On Lane

Completed follow-on source archive accepted evidence status template:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md
scripts/fedora-source-archive-accepted-evidence-status-template.sh
scripts/test-fedora-source-archive-accepted-evidence-status-template.sh
.github/workflows/fedora-source-archive-accepted-evidence-status-template.yml
```

The template prints the future accepted source archive evidence status shape without writing evidence or opening mock build input.

Completed follow-on source archive accepted evidence status review validator:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md
scripts/fedora-source-archive-accepted-evidence-status-review.sh
scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh
.github/workflows/fedora-source-archive-accepted-evidence-status-review-validator.yml
```

The validator checks a future accepted evidence status candidate without writing evidence or opening mock build input by itself.

Completed follow-on source archive accepted evidence acceptance gate:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md
docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE_STATUS.md
scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh
scripts/test-fedora-source-archive-accepted-evidence-acceptance-gate.sh
.github/workflows/fedora-source-archive-accepted-evidence-acceptance-gate.yml
```

The gate checks a future accepted evidence status review report without writing evidence or opening mock build input by itself.

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This gate is not a source archive transcript, not source archive acceptance, not rpmlint evidence, not mock build evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
