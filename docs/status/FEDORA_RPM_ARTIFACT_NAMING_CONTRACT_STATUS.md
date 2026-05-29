# Fedora RPM Artifact Naming Contract Status

Status: rpm-artifact-naming/status alignment
Date: 2026-05-27
Scope: status record for the no-effect Fedora RPM artifact naming contract.

## Summary

Latticra now has a no-effect Fedora RPM artifact naming contract.

The contract records future source RPM and binary RPM name patterns, output boundaries, checksum binding, and retention requirements.

It does not create output directories.

It does not run `rpmbuild`, `mock`, or `dnf builddep`.

It does not create RPM artifacts.

It does not publish packages, submit to Fedora, install packages, or mutate a host.

## Current classification

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

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-rpm-artifact-naming-contract.sh
```

Expected output:

```text
fedora_rpm_artifact_naming_contract: ok
```

## Next recommended lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This status record is not environment evidence, not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
