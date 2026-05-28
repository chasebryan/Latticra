# Fedora Source Archive Reproducibility Contract

Status: active source archive reproducibility contract
Scope: define the evidence required before a Fedora source archive can be accepted for mock build, package review, or production-readiness evidence.

## Purpose

This contract defines the source archive evidence required before Latticra accepts any Fedora mock build, package review, or production-readiness evidence.

The current goal is conservative: record the expected `Source0` archive shape, reproducibility requirements, transcript fields, and promotion blockers without creating an archive, running `rpmbuild`, running `mock`, creating RPM artifacts, installing packages, or mutating a host.

This contract sits after the Fedora `rpmlint` findings classification record and before accepted source archive, mock build, package review, or production-readiness evidence.

The no-effect transcript review validator is present as the next review step, but it does not accept source archive evidence by itself.

The no-effect source archive acceptance gate is present after transcript review, but it still does not accept source archive evidence or open mock build input by itself.

The no-effect accepted evidence status template is present, but it does not write source archive evidence status or open mock build input by itself.

The no-effect accepted evidence status review validator is present, but it does not write, accept, or open source archive evidence by itself.

The no-effect source archive accepted evidence acceptance gate is present, but it does not write, accept, or open source archive evidence by itself.

## Current Spec Inputs

The current local-only Fedora spec declares:

```text
Name:           latticra
Version:        0.0.0
Source0:        %{name}-%{version}.tar.gz
%autosetup -n %{name}-%{version}
```

For the current draft, the expected source archive shape is:

```text
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_matches_source0=1
source_archive_matches_autosetup_root=1
```

## Required Future Evidence

A future accepted source archive transcript must record:

```text
source_tree_revision
source_archive_command
source_archive_name
source_archive_root
source_archive_size_bytes
source_archive_sha256
source_archive_entry_count
source_archive_generated_twice
source_archive_repeated_sha256_match
source_archive_contains_spec
source_archive_contains_readme
source_archive_excludes_git_dir
source_archive_excludes_nested_archives
source_archive_excludes_build_outputs
source_archive_excludes_rpm_artifacts
source_archive_symlink_policy_checked
source_archive_path_safety_checked
```

## Acceptance Rule

A Fedora source archive remains unaccepted unless all of these are true:

```text
source_archive_transcript_present=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_sha256_recorded=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
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
```

Until those conditions are met, source archive evidence is a review input only, not mock build readiness, package review readiness, or production readiness.

## Current Baseline

```text
fedora_source_archive_reproducibility_contract_present=1
fedora_source_archive_transcript_review_validator_present=1
fedora_source_archive_acceptance_gate_present=1
fedora_source_archive_accepted_evidence_status_template_present=1
fedora_source_archive_accepted_evidence_status_review_validator_present=1
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
fedora_rpmlint_findings_classification_present=1
fedora_source_archive_fixture_lane_present=1
source_archive_policy_recorded=1
source_archive_name_expected=latticra-0.0.0.tar.gz
source_archive_root_expected=latticra-0.0.0/
source_archive_matches_source0_required=1
source_archive_matches_autosetup_required=1
source_archive_transcript_present=0
source_archive_transcript_candidate_valid=0
source_archive_transcript_reviewed=0
source_archive_accepted_by_transcript_validator=0
source_archive_written_by_transcript_validator=0
source_archive_accepted_for_build_by_transcript_validator_alone=0
source_archive_acceptance_gate_mode=no-effect-gate
source_archive_transcript_review_report_valid=0
source_archive_acceptance_requested=0
source_archive_accepted_by_acceptance_gate=0
source_archive_written_by_acceptance_gate=0
source_archive_accepted_for_build_by_acceptance_gate_alone=0
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
source_archive_created_by_contract=0
source_archive_sha256_recorded=0
source_archive_reproducible=0
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

## Boundary

This contract does not:

```text
create a source archive
run tar
run gzip
run rpmbuild
run mock
create source RPM artifacts
create binary RPM artifacts
submit Latticra to Fedora
install Latticra on a host
claim official Fedora package status
claim Fedora endorsement
claim Fedora distribution readiness
claim production installer readiness
claim production readiness
mutate a host
```

## Relationship To Fixture Lane

The temporary fixture lane remains a local shape check:

```text
docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
scripts/test-fedora-source-archive-fixture-lane.sh
```

The fixture lane may prove archive mechanics, but this contract keeps source archive acceptance closed until reviewed transcript evidence exists.

## Completed Follow-On Lane

Completed follow-on source archive transcript review validator:

```text
docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md
scripts/fedora-source-archive-transcript-review.sh
scripts/test-fedora-source-archive-transcript-review-validator.sh
.github/workflows/fedora-source-archive-transcript-review-validator.yml
```

The validator checks future transcript candidates without accepting source archive evidence.

Completed follow-on source archive acceptance gate:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE_STATUS.md
scripts/fedora-source-archive-acceptance-gate.sh
scripts/test-fedora-source-archive-acceptance-gate.sh
.github/workflows/fedora-source-archive-acceptance-gate.yml
```

The gate checks future transcript review reports without accepting source archive evidence or opening mock build input.

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
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-source-archive-reproducibility-contract.sh
```

Expected output:

```text
fedora_source_archive_reproducibility_contract: ok
```

## Non-claims

This contract is not a source archive transcript, not source archive acceptance, not rpmlint evidence, not mock build evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
