# Fedora Source Archive Transcript Review Validator

Status: no-effect source archive transcript review validator
Scope: validate a future Fedora source archive reproducibility transcript candidate without accepting source archive evidence, running archive commands, running RPM builds, or mutating a host.

## Purpose

This validator checks whether a supplied Fedora source archive transcript candidate contains the required reproducibility, path-safety, and prerequisite markers from the source archive reproducibility contract.

It is a review check only.

It does not create a source archive.

It does not write source archive evidence.

It does not accept source archive evidence for build input.

It does not run `tar` or `gzip`.

It does not run `rpmbuild`.

It does not run `mock`.

It does not create source RPM or binary RPM artifacts.

It does not install packages.

It does not submit Latticra to Fedora.

It does not claim Fedora package review readiness, Fedora distribution readiness, production installer readiness, or production readiness.

It does not mutate a host.

```text
fedora_source_archive_transcript_review_validator_present=1
source_archive_transcript_review_mode=no-effect-validation
source_archive_transcript_candidate_valid=0
source_archive_transcript_required_markers_present=0
source_archive_transcript_placeholder_values_absent=0
source_archive_transcript_value_fields_validated=0
source_archive_transcript_reviewed=0
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

## Command

```sh
sh scripts/fedora-source-archive-transcript-review.sh --transcript <path>
```

## Required Source Records

The validator depends on:

```text
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md
docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
packaging/fedora/latticra.spec
README.md
```

## Candidate Requirements

A filled transcript candidate must include:

```text
FEDORA SOURCE ARCHIVE REPRODUCIBILITY TRANSCRIPT
source_archive_transcript_present=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_sha256_recorded=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_contains_spec=1
source_archive_contains_readme=1
source_archive_excludes_git_dir=1
source_archive_excludes_nested_archives=1
source_archive_excludes_build_outputs=1
source_archive_excludes_rpm_artifacts=1
source_archive_symlink_policy_checked=1
source_archive_path_safety_checked=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
fedora_rpmlint_findings_classification_present=1
accepted_rpmlint_transcript_present=1
source_archive_reproducible=1
source_archive_accepted_for_build=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

The candidate must also include non-placeholder values for:

```text
source_tree_revision
source_archive_command
source_archive_name
source_archive_root
source_archive_size_bytes
source_archive_sha256
source_archive_entry_count
```

## Validator Output

For a valid candidate, the no-effect validator prints:

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

## Validation

This validator is guarded by:

```sh
sh scripts/test-fedora-source-archive-transcript-review-validator.sh
```

Expected output:

```text
fedora_source_archive_transcript_review_validator: ok
```

## Completed Follow-On Lane

Completed follow-on source archive acceptance gate:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
scripts/fedora-source-archive-acceptance-gate.sh
scripts/test-fedora-source-archive-acceptance-gate.sh
.github/workflows/fedora-source-archive-acceptance-gate.yml
```

## Next Recommended Lane

```text
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Non-claims

This validator is not a source archive transcript, not source archive acceptance, not rpmlint evidence, not mock build evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
