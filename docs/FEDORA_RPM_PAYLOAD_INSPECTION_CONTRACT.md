# Fedora RPM Payload Inspection Contract

Status: no-effect RPM payload inspection contract
Scope: define future Fedora source RPM and binary RPM payload inspection evidence without creating, inspecting, installing, publishing, or accepting RPM artifacts.

## Purpose

This contract records the RPM payload inspection evidence required before any future Fedora source RPM or binary RPM artifact can be accepted as validation evidence.

The goal is narrow: a future Fedora RPM artifact must prove that it contains only the intended no-effect CLI payload, documentation payload, and expected RPM source inputs, with no services, privileged helpers, init files, kernel files, network authority, scriptlets, or host mutation hooks.

This contract is documentation-only and static.

It does not run `rpmbuild`.

It does not run `mock`.

It does not run `rpm`.

It does not run `rpm2cpio`.

It does not run `cpio`.

It does not create RPM artifacts.

It does not inspect RPM artifacts.

It does not install packages.

It does not publish packages.

It does not submit Latticra to Fedora.

It does not mutate a host.

```text
fedora_rpm_payload_inspection_contract_present=1
fedora_rpm_artifact_naming_contract_present=1
fedora_local_mock_build_environment_contract_present=1
rpm_payload_inspection_contract_present=1
payload_inspection_contract_present=1
fedora_rpm_payload_inspection_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
fedora_rpm_artifact_naming_contract_state=specified-no-effect
fedora_mock_build_gate_state=closed-no-effect
rpm_artifact_created=0
rpm_payload_inspection_run=0
source_rpm_payload_inspection_run=0
binary_rpm_payload_inspection_run=0
rpm_payload_accepted=0
rpm_artifact_sha256_recorded=0
rpm_payload_listing_sha256_recorded=0
source_rpm_payload_listing_sha256_recorded=0
binary_rpm_payload_listing_sha256_recorded=0
fedora_mock_build_evidence_present=0
rpm_installed_on_host=0
rpm_removed_from_host=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Expected Payload

All future Fedora RPM artifacts must preserve the current intentionally narrow payload:

```text
rpm_payload_cli_path_required=1
rpm_payload_doc_readme_required=1
rpm_payload_service_files_allowed=0
rpm_payload_systemd_units_allowed=0
rpm_payload_init_files_allowed=0
rpm_payload_kernel_files_allowed=0
rpm_payload_privileged_helper_allowed=0
rpm_payload_network_authority_allowed=0
rpm_payload_host_mutation_hooks_allowed=0
rpm_payload_scriptlets_allowed=0
```

The no-effect CLI payload must remain the only executable binary payload.

## Source RPM Payload Inspection

Future source RPM payload inspection must verify:

```text
source_rpm_expected_spec=packaging/fedora/latticra.spec
source_rpm_expected_source_archive=latticra-0.0.0.tar.gz
source_rpm_payload_listing_required=1
source_rpm_metadata_inspection_required=1
source_rpm_unexpected_archive_count=0
source_rpm_unexpected_patch_count=0
source_rpm_payload_inspection_run=0
rpm2cpio_source_inspection_run=0
source_rpm_metadata_inspection_run=0
```

The future source RPM inspection transcript must bind the payload listing to:

```text
rpm_source_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.src.rpm
source_rpm_artifact_sha256
source_rpm_payload_listing_sha256
fedora_dist_tag
environment_identifier
```

## Binary RPM Payload Inspection

Future binary RPM payload inspection must verify:

```text
rpm_payload_expected_bin=/usr/bin/latticra
rpm_payload_expected_doc=/usr/share/doc/latticra/README.md
rpm_payload_listing_required=1
rpm_metadata_inspection_required=1
rpm_scriptlet_absence_required=1
rpm_systemd_unit_absence_required=1
rpm_init_script_absence_required=1
rpm_privileged_helper_absence_required=1
rpm_kernel_file_absence_required=1
rpm_network_authority_absence_required=1
rpm_host_mutation_hook_absence_required=1
rpm_payload_unexpected_file_count=0
binary_rpm_payload_inspection_run=0
rpm_query_payload_inspection_run=0
rpm_query_metadata_inspection_run=0
rpm_query_scriptlet_inspection_run=0
rpm2cpio_binary_listing_run=0
```

The future binary RPM inspection transcript must bind the payload listing to:

```text
rpm_binary_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.${RPM_ARCH}.rpm
binary_rpm_artifact_sha256
binary_rpm_payload_listing_sha256
fedora_dist_tag
rpm_arch
environment_identifier
```

## Inspection Transcript Requirements

A future RPM payload inspection transcript must record:

```text
rpm_artifact_name
rpm_artifact_sha256
rpm_artifact_size_bytes
payload_listing_command
payload_listing_sha256
expected_payload_paths_present
unexpected_payload_paths_absent
service_files_absent
systemd_units_absent
init_files_absent
scriptlets_absent
kernel_files_absent
privileged_helpers_absent
network_authority_absent
host_mutation_hooks_absent
fedora_target_distribution
fedora_dist_tag
rpm_arch
environment_identifier
operator_authorization_reference
```

The transcript must be reviewed before an RPM artifact can be accepted as payload-correct.

## Current Blockers

RPM payload acceptance remains blocked because the current repository still has:

```text
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_inspection_run=0
environment_transcript_present=0
explicit_operator_build_authorization=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
fedora_mock_build_evidence_present=0
```

## Command Boundary

This contract does not:

```text
run rpm -qlp
run rpm -qip
run rpm -qp --scripts
run rpm2cpio
run cpio
create .src.rpm artifacts
create binary .rpm artifacts
inspect RPM artifacts
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
docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/status/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT_STATUS.md
docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md
docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md
docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
packaging/fedora/latticra.spec
```

The local mock-build gate remains closed. This payload inspection contract only defines the evidence future RPM artifacts must provide after they exist in a disposable validation environment.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-rpm-payload-inspection-contract.sh
```

Expected output:

```text
fedora_rpm_payload_inspection_contract: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not environment evidence, not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not RPM payload evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
