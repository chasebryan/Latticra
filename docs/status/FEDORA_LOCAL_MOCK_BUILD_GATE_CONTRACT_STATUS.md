# Fedora Local Mock Build Gate Contract Status

Status: local-mock-build-gate/status alignment
Date: 2026-05-27
Scope: status record for the no-effect Fedora local mock-build gate contract.

## Summary

Latticra now has a no-effect Fedora local mock-build gate contract.

The contract records the evidence required before any future Fedora `rpmbuild`, `mock`, or `dnf builddep` command can run.

It keeps the gate closed by default.

It does not stage a source archive or spec file.

It does not write a mock configuration.

It does not initialize a mock chroot.

It does not run `rpmbuild` or `mock`.

It does not create RPM artifacts.

It does not install packages or mutate a host.

## Current classification

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

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-local-mock-build-gate-contract.sh
```

Expected output:

```text
fedora_local_mock_build_gate_contract: ok
```

## Next recommended lane

```text
Add a Fedora RPM install/remove transcript contract before any RPM install evidence can be accepted.
```

## Non-claims

This status record is not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
