# Fedora Source Archive Accepted Evidence Status Review Validator

Status: no-effect source archive accepted evidence status review validator
Scope: validate a supplied Fedora source archive accepted evidence status candidate without writing evidence, accepting source archive evidence, opening mock build input, running RPM builds, or mutating a host.

## Purpose

This validator checks a supplied future source archive accepted evidence status candidate after a real source archive transcript, transcript review report, and acceptance gate report have been attached and reviewed.

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
fedora_source_archive_accepted_evidence_status_template_present=1
fedora_source_archive_accepted_evidence_status_review_validator_present=1
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
source_archive_accepted_evidence_status_review_mode=no-effect-validation
source_archive_accepted_evidence_status_candidate_valid=0
source_archive_accepted_evidence_status_required_markers_present=0
source_archive_accepted_evidence_status_placeholder_values_absent=0
source_archive_accepted_evidence_status_value_fields_validated=0
source_archive_accepted_evidence_status_reviewed=0
source_archive_accepted_evidence_status_accepted_by_validator=0
source_archive_accepted_evidence_status_written_by_validator=0
source_archive_accepted_for_build_by_status_validator_alone=0
fedora_mock_build_input_opened_by_status_validator_alone=0
source_archive_accepted_evidence_acceptance_gate_mode=no-effect-gate
source_archive_accepted_evidence_status_review_report_valid=0
source_archive_accepted_evidence_acceptance_requested=0
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
sh scripts/fedora-source-archive-accepted-evidence-status-review.sh --status <path>
```

## Required Source Records

The validator depends on:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
scripts/fedora-source-archive-accepted-evidence-status-template.sh
scripts/fedora-source-archive-acceptance-gate.sh
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
packaging/fedora/latticra.spec
README.md
```

## Accepted Candidate Requirements

A supplied candidate must contain the future accepted evidence status shape from the template:

```text
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS
Status: source archive evidence status alignment
source=operator Fedora source archive reproducibility transcript and acceptance gate report
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_transcript_present=1
source_archive_transcript_candidate_valid=1
source_archive_transcript_reviewed=1
source_archive_transcript_review_report_valid=1
source_archive_acceptance_gate_reviewed=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_reproducible=1
source_archive_repeated_sha256_match=1
source_archive_path_safety_checked=1
source_archive_symlink_policy_checked=1
fedora_rpmlint_findings_classification_present=1
accepted_rpmlint_transcript_present=1
source_archive_accepted_evidence_status_written=1
source_archive_accepted_evidence_present=1
source_archive_accepted=1
source_archive_accepted_for_build=1
fedora_mock_build_input_opened=1
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

The validator rejects placeholder values for:

```text
Date
source_archive_transcript_path
source_archive_transcript_review_report_path
source_archive_acceptance_gate_report_path
source_tree_revision
source_archive_command
source_archive_size_bytes
source_archive_sha256
source_archive_entry_count
```

## Validator Output

For a valid candidate, the validator prints:

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

## Validation

This validator is guarded by:

```sh
sh scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh
```

Expected output:

```text
fedora_source_archive_accepted_evidence_status_review_validator: ok
```

## Completed Follow-On Lane

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
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Non-claims

This validator is not a source archive transcript, not source archive acceptance, not written evidence status, not mock build evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
