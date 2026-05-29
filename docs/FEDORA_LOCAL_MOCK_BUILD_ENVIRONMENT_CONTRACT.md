# Fedora Local Mock Build Environment Contract

Status: no-effect local mock-build environment contract
Scope: document required disposable Fedora validation environments for future `rpmbuild` and `mock` lanes without provisioning environments, running package tools, creating RPM artifacts, installing packages, submitting to Fedora, or mutating a host.

## Purpose

This contract documents the minimum environment evidence required before any future Fedora local mock-build lane can ask to open the build gate.

The goal is narrow: describe clean/disposable Fedora validation environments, required transcript fields, toolchain metadata, RPM input binding, mock policy, result paths, and host-effect boundaries before any package build command can run.

This contract is documentation-only and static.

It does not choose a Fedora release.

It does not provision a container.

It does not provision a VM.

It does not run `dnf builddep`.

It does not run `rpmbuild`.

It does not run `mock`.

It does not create source RPM or binary RPM artifacts.

It does not install packages.

It does not submit Latticra to Fedora.

It does not mutate a host.

```text
fedora_local_mock_build_environment_contract_present=1
fedora_local_mock_build_gate_contract_present=1
fedora_mock_build_environment_contract_state=specified-no-effect
fedora_mock_build_gate_state=closed-no-effect
fedora_clean_build_environment_documented=1
fedora_mock_target_documented=1
fedora_target_distribution_documented=1
fedora_build_environment_provisioned=0
fedora_mock_build_environment_provisioned=0
explicit_operator_build_authorization=0
disposable_validation_environment_required=1
disposable_validation_environment_provisioned=0
environment_transcript_present=0
toolchain_version_capture_required=1
rpm_input_digest_binding_required=1
mock_chroot_lifecycle_documented=1
mock_network_policy_documented=1
mock_result_directory_documented=1
source_rpm_output_path_documented=1
binary_rpm_output_path_documented=1
transcript_retention_path_documented=1
rpmbuild_command_allowed=0
mock_build_command_allowed=0
dnf_builddep_command_allowed=0
rpmbuild_allowed=0
mock_build_allowed=0
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

## Local Mock Environment Contract

A future Fedora mock-build lane must use a disposable Fedora validation environment before `rpmbuild`, `mock`, or `dnf builddep` can run.

Required local mock environment evidence:

```text
fedora_clean_build_environment_documented=1
fedora_container_or_vm_required=1
fedora_target_distribution_record_required=1
fedora_architecture_record_required=1
fedora_repository_state_record_required=1
fedora_build_dependency_resolution_transcript_required=1
rpmbuild_toolchain_versions_required=1
mock_toolchain_versions_required=1
source_archive_digest_required=1
rpm_input_path_required=1
mock_target_record_required=1
mock_config_scope_record_required=1
mock_chroot_policy_required=1
mock_network_policy_required=1
mock_result_directory_required=1
rpmbuild_run=0
rpmbuild_bs_run=0
rpmbuild_ba_run=0
rpmbuild_bb_run=0
mock_build_run=0
mock_buildsrpm_run=0
dnf_builddep_run=0
```

The local mock environment contract does not choose between a Fedora container, disposable Fedora VM, mock chroot on a disposable host, or another clean Fedora build context. A future effect-bearing proposal must name the exact target release, architecture, mock target, repository state, and cleanup policy while keeping the build gate closed until operator authorization and all package prerequisites exist.

## Shared Transcript Requirements

A future environment transcript must record:

```text
environment_identifier
environment_lifecycle
host_or_vm_class
operating_system_name
operating_system_version
fedora_target_distribution
architecture
repository_state
toolchain_versions
rpmbuild_version
mock_version
source_archive_name
source_archive_sha256
rpm_input_path
rpm_spec_path
mock_target
mock_config_scope
mock_chroot_policy
mock_network_policy
mock_result_directory
source_rpm_output_path
binary_rpm_output_path
transcript_retention_path
host_mount_policy
cleanup_policy
operator_authorization_reference
```

The transcript must be reviewed before a local Fedora mock-build lane can claim that the environment is acceptable.

## Current Blockers

Fedora local package builds remain blocked because the current repository still has:

```text
fedora_mock_build_gate_state=closed-no-effect
source_archive_handoff_to_rpmbuild_allowed=0
source_archive_handoff_to_mock_allowed=0
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
unexpected_findings_count_recorded=0
license_expression_reviewed=1
package_notice_obligations_reviewed=1
buildrequires_reviewed=1
explicit_operator_build_authorization=0
environment_transcript_present=0
fedora_build_environment_provisioned=0
fedora_mock_build_environment_provisioned=0
```

## Command Boundary

This contract does not:

```text
provision a Fedora container
provision a Fedora VM
initialize a mock chroot
run dnf builddep
run rpmbuild
run rpmbuild -ba
run rpmbuild -bb
run rpmbuild -bs
run mock --buildsrpm
run mock -r
create source RPM artifacts
create binary RPM artifacts
install Latticra on a host
publish package artifacts
submit Latticra to Fedora
claim Fedora package readiness
claim Fedora distribution readiness
claim production readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md
docs/status/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT_STATUS.md
docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md
packaging/fedora/latticra.spec
```

The local mock-build gate remains closed. This environment contract only records what future disposable Fedora validation environments must prove before a build lane can request authorization.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-local-mock-build-environment-contract.sh
```

Expected output:

```text
fedora_local_mock_build_environment_contract: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not environment evidence, not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
