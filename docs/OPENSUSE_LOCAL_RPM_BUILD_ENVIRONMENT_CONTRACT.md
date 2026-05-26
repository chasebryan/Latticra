# openSUSE Local RPM Build Environment Contract

Status: active local RPM build environment contract
Scope: document required disposable validation environments for openSUSE local RPM build lanes without running `rpmbuild` or `osc build`.

## Purpose

This contract documents the minimum environment evidence required before any future openSUSE local RPM build lane can ask to open the build gate.

The goal is narrow: describe clean/disposable validation environments, required transcript fields, toolchain metadata, RPM input binding, and host-effect boundaries before any package build command can run.

This contract is documentation-only and static. It does not provision a VM or container, run `rpmbuild`, run `osc build`, run `spec-cleaner`, create source RPMs, create binary RPMs, install Latticra, publish to Open Build Service, or claim package readiness.

## Current Environment State

```text
opensuse_local_rpm_build_environment_contract_present=1
opensuse_rpm_artifact_naming_contract_present=1
opensuse_rpm_build_environment_contract_state=specified-no-effect
opensuse_rpm_artifact_naming_contract_state=specified-no-effect
opensuse_rpm_build_gate_state=closed-no-effect
opensuse_clean_build_environment_documented=1
opensuse_target_distribution_documented=1
osc_build_environment_documented=1
opensuse_build_environment_provisioned=0
osc_build_environment_provisioned=0
explicit_operator_build_authorization=0
disposable_validation_environment_required=1
disposable_validation_environment_provisioned=0
environment_transcript_present=0
toolchain_version_capture_required=1
rpm_input_digest_binding_required=1
rpmbuild_command_allowed=0
osc_build_command_allowed=0
rpmbuild_run=0
osc_build_run=0
spec_cleaner_run=0
rpm_artifact_created=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_installed_on_host=0
package_readiness_claimed=0
```

## Local RPM Environment Contract

A future local RPM build lane must use a disposable openSUSE validation environment before `rpmbuild` can run.

Required local RPM environment evidence:

```text
opensuse_clean_build_environment_documented=1
opensuse_container_or_vm_required=1
opensuse_target_distribution_record_required=1
opensuse_architecture_record_required=1
opensuse_repository_state_record_required=1
opensuse_build_dependency_resolution_transcript_required=1
rpmbuild_toolchain_versions_required=1
source_archive_digest_required=1
rpm_topdir_input_path_required=1
rpmbuild_run=0
rpmbuild_ba_run=0
rpmbuild_bb_run=0
rpmbuild_bs_run=0
```

The local RPM environment contract does not choose between an openSUSE Tumbleweed container, an openSUSE Leap container, a disposable VM, or another clean openSUSE build host. A future effect-bearing proposal must name the exact environment and keep the build gate closed until operator authorization and all package prerequisites exist.

## osc Build Environment Contract

A future `osc build` lane must use a disposable and documented openSUSE build context before `osc build` can run.

Required `osc build` environment evidence:

```text
osc_build_environment_documented=1
osc_local_build_context_required=1
osc_config_scope_record_required=1
osc_target_project_record_required=1
osc_target_repository_record_required=1
osc_build_root_policy_required=1
osc_toolchain_versions_required=1
osc_build_run=0
osc_commit_run=0
obs_publication_claimed=0
```

The `osc` environment contract does not create an Open Build Service project, run `osc build`, run `osc commit`, submit Latticra to openSUSE, or publish package artifacts.

## Shared Transcript Requirements

A future environment transcript must record:

```text
environment_identifier
environment_lifecycle
host_or_vm_class
operating_system_name
operating_system_version
opensuse_target_distribution
architecture
repository_state
toolchain_versions
source_archive_name
source_archive_sha256
rpm_topdir_path
rpm_spec_path
rpm_output_directory
network_policy
host_mount_policy
cleanup_policy
operator_authorization_reference
```

The transcript must be reviewed before a local RPM build lane can claim that the environment is acceptable.

## Current Blockers

RPM builds remain blocked because the current repository still has:

```text
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
unexpected_findings_count_recorded=0
license_expression_reviewed=1
package_notice_obligations_reviewed=0
buildrequires_reviewed=0
explicit_operator_build_authorization=0
rpm_artifact_naming_contract_present=1
rpm_payload_inspection_contract_present=0
rpm_install_remove_transcript_contract_present=0
obs_publication_non_claim_review_present=0
```

## Command Boundary

This contract does not:

```text
provision an openSUSE container
provision an openSUSE VM
run zypper install for build dependencies
run rpmbuild
run rpmbuild -ba
run rpmbuild -bb
run rpmbuild -bs
run osc build
run osc commit
run spec-cleaner
create source RPM artifacts
create binary RPM artifacts
install Latticra on a host
publish package artifacts
create an Open Build Service project
submit Latticra to openSUSE
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
```

The local RPM build gate remains closed. This environment contract only records what future disposable openSUSE validation environments must prove before a build lane can request authorization.

## Completed Follow-On Lane

Completed follow-on RPM artifact naming contract:

```text
Add openSUSE RPM artifact naming contract before any source RPM or binary RPM artifact can be created.
```

```text
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
scripts/test-opensuse-rpm-artifact-naming-contract.sh
.github/workflows/opensuse-rpm-artifact-naming-contract.yml
```

That lane defines source RPM and binary RPM names, output directories, checksum binding, retention rules, and Open Build Service non-claims while keeping `opensuse_rpm_build_gate_state=closed-no-effect`.

## Next Slice

Recommended next slice:

```text
Add openSUSE RPM payload inspection contract before any RPM artifact can be accepted.
```

That future lane should define how source RPM and binary RPM payloads are inspected after creation while keeping `opensuse_rpm_build_gate_state=closed-no-effect` until the remaining prerequisites are satisfied.

## Validation

Run:

```sh
sh scripts/test-opensuse-local-rpm-build-environment-contract.sh
```

Expected output:

```text
opensuse_local_rpm_build_environment_contract: ok
```
