# Fedora Source Archive Mock Build Input Handoff Contract Status

Status: mock-build-input-handoff-contract/status alignment
Date: 2026-05-27
Scope: status record for the Fedora source archive mock build input handoff contract.

## Summary

Latticra now has a no-effect Fedora source archive mock build input handoff contract.

The contract defines the future evidence required before accepted source archive evidence can become `rpmbuild` or `mock` input.

It does not stage a source archive under `SOURCES/`.

It does not stage a spec under `SPECS/`.

It does not write a `mock` configuration.

It does not run `rpmbuild` or `mock`.

It does not create RPM artifacts.

It does not install packages or mutate a host.

It does not claim package readiness, Fedora distribution readiness, production installer readiness, or production readiness.

## Current classification

```text
fedora_source_archive_mock_build_input_handoff_contract_present=1
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
source_archive_mock_build_input_handoff_contract_state=closed-no-effect
mock_build_input_handoff_allowed=0
source_archive_accepted_evidence_acceptance_gate_report_valid=0
source_archive_accepted_evidence_acceptance_gate_reviewed=0
source_archive_accepted_for_build_candidate_valid=0
candidate_source_archive_accepted_for_build=0
candidate_fedora_mock_build_input_opened=0
source_archive_handoff_to_rpmbuild_allowed=0
source_archive_handoff_to_mock_allowed=0
source_archive_handoff_written_by_contract=0
fedora_rpm_input_layout_documented=1
fedora_rpmbuild_sources_archive_staged=0
fedora_rpmbuild_specs_spec_staged=0
fedora_mock_build_input_opened_by_handoff_contract=0
rpmbuild_allowed=0
mock_build_allowed=0
rpmbuild_run=0
mock_build_run=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-source-archive-mock-build-input-handoff-contract.sh
```

Expected output:

```text
fedora_source_archive_mock_build_input_handoff_contract: ok
```

## Next recommended lane

```text
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Non-claims

This status record is not a source archive transcript, not source archive acceptance, not written evidence status, not mock build evidence, not source RPM evidence, not binary RPM evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
