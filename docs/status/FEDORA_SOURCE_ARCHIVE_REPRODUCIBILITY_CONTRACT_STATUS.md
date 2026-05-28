# Fedora Source Archive Reproducibility Contract Status

Status: source-archive-reproducibility/status alignment
Date: 2026-05-27
Scope: status record for the Fedora source archive reproducibility contract.

## Summary

Latticra now has a Fedora source archive reproducibility contract for the local-only Fedora spec draft.

The contract defines the evidence required before a source archive can be accepted for mock build, package review, or Fedora production-readiness evidence.

It does not create a source archive.

It does not run `rpmbuild` or `mock`.

It does not create RPM artifacts.

It does not install packages or mutate a host.

It does not claim package readiness, Fedora distribution readiness, production installer readiness, or production readiness.

## Current classification

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

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-source-archive-reproducibility-contract.sh
```

Expected output:

```text
fedora_source_archive_reproducibility_contract: ok
```

## Next recommended lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This status record is not a source archive transcript, not source archive acceptance, not rpmlint evidence, not mock build evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
