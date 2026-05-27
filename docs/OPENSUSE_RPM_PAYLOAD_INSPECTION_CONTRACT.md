# openSUSE RPM Payload Inspection Contract

Status: active RPM payload inspection contract
Scope: define future openSUSE source RPM and binary RPM payload inspection evidence without creating or inspecting RPM artifacts.

## Purpose

This contract records the RPM payload inspection evidence required before any future openSUSE source RPM or binary RPM artifact can be accepted as validation evidence.

The goal is narrow: a future RPM artifact must prove that it contains only the intended no-effect CLI payload, documentation payload, and expected RPM source inputs, with no services, privileged helpers, init files, kernel files, network authority, or host mutation hooks.

This contract is documentation-only and static. It does not run `rpmbuild`, run `osc build`, run `rpm`, run `rpm2cpio`, run `cpio`, create RPM artifacts, inspect RPM artifacts, install Latticra, publish packages, create an Open Build Service project, submit Latticra to openSUSE, or claim package readiness.

## Current Payload Inspection State

```text
opensuse_rpm_payload_inspection_contract_present=1
opensuse_rpm_install_remove_transcript_contract_present=1
opensuse_obs_publication_non_claim_review_contract_present=1
rpm_payload_inspection_contract_present=1
obs_publication_non_claim_review_present=1
publication_non_claim_review_present=1
payload_inspection_contract_present=1
opensuse_rpm_payload_inspection_contract_state=specified-no-effect
opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
opensuse_rpm_build_gate_state=closed-no-effect
opensuse_rpm_artifact_naming_contract_state=specified-no-effect
rpm_artifact_created=0
rpm_payload_inspection_run=0
source_rpm_payload_inspection_run=0
binary_rpm_payload_inspection_run=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
rpm_validation_result_promoted=0
rpm_artifact_sha256_recorded=0
rpm_installed_on_host=0
rpm_removed_from_host=0
package_readiness_claimed=0
```

## Expected Payload

All future openSUSE RPM artifacts must preserve the current intentionally narrow payload:

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
```

The no-effect CLI payload must remain the only executable binary payload.

## Source RPM Payload Inspection

Future source RPM payload inspection must verify:

```text
source_rpm_expected_spec=packaging/opensuse/latticra.spec
source_rpm_expected_changes=packaging/opensuse/latticra.changes
source_rpm_expected_source_archive=latticra-0.0.0.tar.gz
source_rpm_payload_listing_required=1
source_rpm_metadata_inspection_required=1
source_rpm_unexpected_archive_count=0
source_rpm_payload_inspection_run=0
rpm2cpio_source_inspection_run=0
source_rpm_metadata_inspection_run=0
```

The future source RPM inspection transcript must bind the payload listing to:

```text
rpm_source_package_name=latticra-0.0.0-0.local.src.rpm
source_rpm_artifact_sha256
source_rpm_payload_listing_sha256
```

## Binary RPM Payload Inspection

Future binary RPM payload inspection must verify:

```text
rpm_payload_expected_bin=/usr/bin/latticra
rpm_payload_expected_doc=/usr/share/doc/packages/latticra/README.md
rpm_payload_listing_required=1
rpm_metadata_inspection_required=1
rpm_scriptlet_absence_required=1
rpm_systemd_unit_absence_required=1
rpm_init_script_absence_required=1
rpm_privileged_helper_absence_required=1
rpm_payload_unexpected_file_count=0
binary_rpm_payload_inspection_run=0
rpm_query_payload_inspection_run=0
rpm_query_scriptlet_inspection_run=0
rpm2cpio_binary_listing_run=0
```

The future binary RPM inspection transcript must bind the payload listing to:

```text
rpm_binary_package_name_pattern=latticra-0.0.0-0.local.${RPM_ARCH}.rpm
binary_rpm_artifact_sha256
binary_rpm_payload_listing_sha256
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
scriptlets_absent
privileged_helpers_absent
host_mutation_hooks_absent
environment_identifier
operator_authorization_reference
```

The transcript must be reviewed before an RPM artifact can be accepted as payload-correct.

## Current Blockers

RPM payload acceptance remains blocked because the current repository still has:

```text
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
environment_transcript_present=0
explicit_operator_build_authorization=0
rpm_install_remove_transcript_contract_present=1
obs_publication_non_claim_review_present=1
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
create an Open Build Service project
submit Latticra to openSUSE
claim official openSUSE package status
claim SUSE endorsement
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
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
```

The local RPM build gate remains closed. This payload inspection contract only defines the evidence future RPM artifacts must provide after they exist in a disposable validation environment.

## Next Slice

Completed follow-on RPM install/remove transcript contract:

```text
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
.github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
```

That lane defines disposable install/remove transcript evidence without installing or removing RPM packages.

Completed follow-on OBS publication non-claim review contract:

```text
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
.github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
```

That lane records Open Build Service, submit-request, official-package, and SUSE endorsement non-claims without publishing packages.

Recommended next slice:

```text
Add openSUSE RPM validation promotion blocker matrix before any package validation result can be accepted.
```

That future lane should tie source, environment, artifact, payload, install/remove, and OBS non-claim records together while keeping RPM builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-opensuse-rpm-payload-inspection-contract.sh
```

Expected output:

```text
opensuse_rpm_payload_inspection_contract: ok
```
