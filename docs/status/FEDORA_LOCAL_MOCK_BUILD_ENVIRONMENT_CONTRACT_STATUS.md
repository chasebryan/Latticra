# Fedora Local Mock Build Environment Contract Status

Status: local-mock-build-environment/status alignment
Date: 2026-05-27
Scope: status record for the no-effect Fedora local mock-build environment contract.

## Summary

Latticra now has a no-effect Fedora local mock-build environment contract.

The contract records the future disposable Fedora environment evidence required before any local `rpmbuild`, `mock`, or `dnf builddep` command can run.

It does not provision a VM or container.

It does not initialize a mock chroot.

It does not run `rpmbuild`, `mock`, or `dnf builddep`.

It does not create RPM artifacts.

It does not install packages or mutate a host.

## Current classification

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

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-local-mock-build-environment-contract.sh
```

Expected output:

```text
fedora_local_mock_build_environment_contract: ok
```

## Next recommended lane

```text
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Non-claims

This status record is not environment evidence, not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
