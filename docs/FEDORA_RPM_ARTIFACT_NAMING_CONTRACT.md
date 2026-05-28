# Fedora RPM Artifact Naming Contract

Status: no-effect RPM artifact naming contract
Scope: define future Fedora source RPM and binary RPM artifact names and output boundaries without creating RPM artifacts, running build tools, installing packages, submitting to Fedora, or mutating a host.

## Purpose

This contract records the artifact names, output-directory rules, checksum binding, retention requirements, and Fedora publication non-claims required before any future Fedora local mock-build lane can create source RPM or binary RPM files.

The goal is narrow: RPM artifacts must have predictable names, be written only inside a disposable validation environment, bind back to the source archive digest, preserve the Fedora `%{?dist}` expansion as environment evidence, and remain non-published review outputs until separate payload inspection, install/remove, and Fedora package-review lanes exist.

This contract is documentation-only and static.

It does not run `rpmbuild`.

It does not run `mock`.

It does not run `dnf builddep`.

It does not create source RPM artifacts.

It does not create binary RPM artifacts.

It does not install packages.

It does not publish packages.

It does not submit Latticra to Fedora.

It does not mutate a host.

```text
fedora_rpm_artifact_naming_contract_present=1
fedora_local_mock_build_environment_contract_present=1
fedora_local_mock_build_gate_contract_present=1
rpm_artifact_naming_contract_present=1
fedora_rpm_artifact_naming_contract_state=specified-no-effect
fedora_mock_build_environment_contract_state=specified-no-effect
fedora_mock_build_gate_state=closed-no-effect
rpm_artifact_output_directory_required_under_disposable_environment=1
rpm_artifact_output_directory_created=0
repository_rpm_artifact_write_allowed=0
root_workspace_rpm_artifact_write_allowed=0
publication_directory_write_allowed=0
rpm_source_artifact_name_pattern_recorded=1
rpm_binary_artifact_name_pattern_recorded=1
rpm_dist_tag_token_required=1
rpm_binary_arch_token_required=1
rpm_artifact_created=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_artifact_published=0
fedora_mock_build_evidence_present=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Source RPM Artifact Name

Future source RPM artifact names must be derived from the current Fedora spec `Name`, `Version`, and `Release` values.

```text
rpm_source_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.src.rpm
rpm_source_archive_name=latticra-0.0.0.tar.gz
rpm_spec_name=latticra.spec
rpm_name_value=latticra
rpm_version_value=0.0.0
rpm_release_template=0.1.local%{?dist}
rpm_dist_tag_token_required=1
rpm_source_artifact_name_pattern_recorded=1
rpmbuild_bs_run=0
mock_buildsrpm_run=0
source_rpm_artifact_created=0
```

The `${FEDORA_DIST}` token must be resolved from the disposable Fedora environment transcript before any source RPM artifact can be accepted.

The source RPM name is a future local validation artifact only. It is not an accepted source package, Fedora package review attachment, Koji build, Copr build, Bodhi update, or publication claim.

## Binary RPM Artifact Name

Future binary RPM artifact names must be derived from the current Fedora spec `Name`, `Version`, `Release`, Fedora dist tag, and the build environment architecture.

```text
rpm_binary_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.${RPM_ARCH}.rpm
rpm_binary_arch_token_required=1
rpm_dist_tag_token_required=1
rpm_binary_artifact_name_pattern_recorded=1
rpmbuild_ba_run=0
rpmbuild_bb_run=0
mock_build_run=0
binary_rpm_artifact_created=0
```

The `${RPM_ARCH}` and `${FEDORA_DIST}` tokens must be resolved from the disposable Fedora environment transcript before any binary RPM artifact can be accepted.

## Output Boundary

Future RPM artifacts must be written only under disposable output directories inside a disposable validation environment. The repository itself remains a no-artifact workspace.

```text
artifact_output_root_under_disposable_environment=1
rpm_source_artifact_output_directory=fedora-rpm-input/SRPMS/
rpm_binary_artifact_output_directory_pattern=fedora-rpm-input/RPMS/${RPM_ARCH}/
mock_result_artifact_output_directory=mock-result/
repository_rpm_artifact_write_allowed=0
root_workspace_rpm_artifact_write_allowed=0
publication_directory_write_allowed=0
artifact_retention_policy_required=1
artifact_cleanup_policy_required=1
```

Any future RPM artifact transcript must bind each package file to:

```text
source_archive_sha256
rpm_input_archive_sha256
rpm_artifact_sha256
artifact_size_bytes
artifact_output_directory
artifact_generation_command
fedora_target_distribution
fedora_dist_tag
rpm_arch
environment_identifier
operator_authorization_reference
```

## Current Blockers

RPM artifact creation remains blocked because the current repository still has:

```text
fedora_mock_build_gate_state=closed-no-effect
source_archive_handoff_to_rpmbuild_allowed=0
source_archive_handoff_to_mock_allowed=0
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
unexpected_findings_count_recorded=0
explicit_operator_build_authorization=0
environment_transcript_present=0
fedora_build_environment_provisioned=0
fedora_mock_build_environment_provisioned=0
rpm_artifact_output_directory_created=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_created=0
```

## Command Boundary

This contract does not:

```text
run rpmbuild
run rpmbuild -ba
run rpmbuild -bb
run rpmbuild -bs
run mock --buildsrpm
run mock -r
run dnf builddep
create .src.rpm artifacts
create binary .rpm artifacts
install Latticra on a host
publish package artifacts
submit Latticra to Fedora
claim official Fedora package status
claim Fedora endorsement
claim Fedora package readiness
claim Fedora distribution readiness
claim production readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md
docs/status/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT_STATUS.md
docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md
docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md
packaging/fedora/latticra.spec
```

The local mock-build gate remains closed. This artifact naming contract only records the names and output boundaries future validation artifacts must use after separate source, lint, license, notice, BuildRequires, environment, authorization, payload inspection, install/remove, and Fedora package-review evidence exists.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-rpm-artifact-naming-contract.sh
```

Expected output:

```text
fedora_rpm_artifact_naming_contract: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Non-claims

This contract is not environment evidence, not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
