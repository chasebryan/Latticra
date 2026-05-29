# Fedora Local Mock Build Gate Contract

Status: no-effect local mock-build gate contract
Scope: define the evidence required before Fedora `rpmbuild` or `mock` commands can run, without running build tools, creating RPM artifacts, installing packages, submitting to Fedora, or mutating a host.

## Purpose

This contract closes the Fedora local package build command gate after the source archive mock-build input handoff contract.

It records the prerequisites required before any future local Fedora package build lane can run `rpmbuild`, `mock`, or `dnf builddep`.

This contract is documentation-only and static.

It does not stage a source archive.

It does not stage `packaging/fedora/latticra.spec`.

It does not write a `mock` configuration.

It does not initialize a `mock` chroot.

It does not run `rpmbuild`.

It does not run `mock`.

It does not run package managers.

It does not create source RPM or binary RPM artifacts.

It does not install packages.

It does not submit Latticra to Fedora.

It does not mutate a host.

```text
fedora_local_mock_build_gate_contract_present=1
fedora_source_archive_mock_build_input_handoff_contract_present=1
fedora_mock_build_gate_state=closed-no-effect
fedora_mock_build_gate_open=0
fedora_mock_build_gate_opened_by_contract=0
mock_build_input_handoff_allowed=0
source_archive_handoff_to_rpmbuild_allowed=0
source_archive_handoff_to_mock_allowed=0
fedora_rpmbuild_sources_archive_staged=0
fedora_rpmbuild_specs_spec_staged=0
fedora_mock_config_written=0
fedora_mock_chroot_initialized=0
fedora_mock_chroot_mutated=0
rpmbuild_allowed=0
rpmbuild_bs_allowed=0
rpmbuild_ba_allowed=0
rpmbuild_bb_allowed=0
mock_build_allowed=0
mock_buildsrpm_allowed=0
dnf_builddep_allowed=0
rpmbuild_run=0
rpmbuild_bs_run=0
rpmbuild_ba_run=0
rpmbuild_bb_run=0
mock_build_run=0
mock_buildsrpm_run=0
dnf_builddep_run=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_created=0
fedora_mock_build_evidence_present=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Required Gate Inputs

The local mock-build gate cannot open unless all package input evidence has already passed and been reviewed:

```text
source_archive_handoff_to_rpmbuild_allowed=1
source_archive_handoff_to_mock_allowed=1
source_archive_accepted_for_build=1
source_archive_sha256_recorded=1
source_archive_reproducible=1
source_archive_path_safety_checked=1
source_archive_symlink_policy_checked=1
fedora_rpm_input_layout_documented=1
fedora_rpmbuild_sources_archive_staged=1
fedora_rpmbuild_specs_spec_staged=1
accepted_rpmlint_transcript_present=1
unexpected_findings_count=0
license_expression_reviewed=1
package_notice_obligations_reviewed=1
buildrequires_reviewed=1
fedora_clean_build_environment_documented=1
fedora_mock_target_documented=1
rpmbuild_toolchain_versions_recorded=1
mock_toolchain_versions_recorded=1
disposable_validation_environment=1
explicit_operator_build_authorization=1
```

Those future values are prerequisites, not current claims.

## Environment Prerequisites

Before any Fedora package build command can run, a future build lane must document:

```text
fedora_clean_build_environment_documented=1
fedora_mock_target_documented=1
fedora_target_distribution_documented=1
rpmbuild_toolchain_versions_recorded=1
mock_toolchain_versions_recorded=1
mock_chroot_lifecycle_documented=1
mock_network_policy_documented=1
mock_result_directory_documented=1
source_rpm_output_path_documented=1
binary_rpm_output_path_documented=1
transcript_retention_path_documented=1
explicit_operator_build_authorization=1
disposable_validation_environment=1
```

Those records must identify the exact disposable host or VM class, Fedora target, toolchain versions, source archive digest, spec path, mock target, result directory, transcript location, and cleanup expectations before a build can be attempted.

## Command Gate

All Fedora package build commands remain blocked while the current gate state is `closed-no-effect`.

Fedora build commands blocked by this contract:

```text
rpmbuild -bs
rpmbuild -ba
rpmbuild -bb
mock --buildsrpm
mock -r
dnf builddep
rpmdev-setuptree
```

Fedora package and publication effect commands blocked by this contract:

```text
rpm install local RPM artifact
dnf install local RPM artifact
install package on host
remove package from host
publish package artifact
submit package review
claim official Fedora package status
claim Fedora endorsement
claim production readiness
```

## Future Open Conditions

A future local Fedora package build lane may move `fedora_mock_build_gate_state=closed-no-effect` to `fedora_mock_build_gate_state=open-for-local-mock-build-validation` only after it records:

```text
source_archive_handoff_to_rpmbuild_allowed=1
source_archive_handoff_to_mock_allowed=1
source_archive_accepted_for_build=1
archive_sha256_bound_to_build=1
accepted_rpmlint_transcript_present=1
unexpected_findings_count=0
license_expression_reviewed=1
package_notice_obligations_reviewed=1
buildrequires_reviewed=1
fedora_clean_build_environment_documented=1
fedora_mock_target_documented=1
explicit_operator_build_authorization=1
disposable_validation_environment=1
transcript_retention_path_documented=1
```

Opening a local mock-build gate must not imply Fedora package review readiness, Fedora acceptance, host install readiness, Fedora distribution readiness, or production readiness.

## Current Non-Claims

```text
fedora_package_review_ready=0
fedora_official_package_claimed=0
fedora_distribution_ready=0
fedora_approval_claimed=0
fedora_endorsement_claimed=0
production_installer_ready=0
production_readiness_claimed=0
host_mutation_performed=0
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md
docs/status/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT_STATUS.md
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md
packaging/fedora/latticra.spec
```

The source archive mock-build input handoff contract keeps `SOURCES/`, `SPECS/`, `rpmbuild`, and `mock` input closed.

The `rpmlint` findings classification record keeps lint output from becoming package readiness evidence without review.

This build gate keeps package build execution closed until source acceptance, lint classification, license, notice, BuildRequires, environment, authorization, and transcript retention evidence exists.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-local-mock-build-gate-contract.sh
```

Expected output:

```text
fedora_local_mock_build_gate_contract: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
