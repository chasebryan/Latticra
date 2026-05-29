# Ubuntu Local Deb Build Transcript Contract

Status: no-effect transcript contract
Scope: evidence schema for a future reviewed local Ubuntu deb build transcript.

## Purpose

This contract defines the transcript fields required before a future Ubuntu local deb build can be treated as evidence.

It does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`. It does not create, install, publish, or upload a deb package.

## Required Transcript Header

```text
transcript_kind=ubuntu-local-deb-build
transcript_version=1
host_os_id=ubuntu
host_os_version_recorded=1
kernel_recorded=1
architecture_recorded=1
repo_commit_recorded=1
source_tree_dirty_state_recorded=1
```

## Required Tooling Evidence

```text
apt_get_available=1
cc_available=1
make_available=1
dpkg_buildpackage_available=1
debuild_available_recorded=1
lintian_available_recorded=1
debhelper_available_recorded=1
```

## Required Package Evidence

```text
local_deb_draft_present=1
debian_control_present=1
debian_rules_present=1
debian_changelog_present=1
debian_copyright_present=1
debian_install_present=1
rules_requires_root_no=1
license_expression_reviewed=1
license_expression_unresolved=0
```

The current repository state satisfies the package license-expression review, but this contract remains future evidence only because lintian, build, artifact, notice, and install/remove evidence are still blocked.

The current package license review checkpoint is:

```text
ubuntu_package_license_review_contract_present=1
ubuntu_package_license_review_status=resolved-license-expression-recorded
ubuntu_package_notice_inventory_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=resolved-cc-by-4.0
ubuntu_third_party_material_review_contract_present=1
ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review
ubuntu_notice_file_decision_contract_present=1
ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_lintian_static_metadata_contract_present=1
ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion
ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1
ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript
ubuntu_local_deb_install_remove_evidence_contract_present=1
ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-notice-review
license_expression_candidate_recorded=1
packaging_license_expression_updated=1
```

## Required Build Evidence

```text
dpkg_buildpackage_command_recorded=1
build_exit_status_recorded=1
deb_artifact_path_recorded=1
deb_artifact_digest_recorded=1
changes_file_digest_recorded=1
build_log_digest_recorded=1
lintian_command_recorded=1
lintian_exit_status_recorded=1
lintian_output_digest_recorded=1
expected_draft_findings_classified=1
unexpected_findings_classified=1
```

## Required Payload Evidence

```text
payload_listing_recorded=1
usr_bin_latticra_present=1
usr_share_doc_latticra_readme_present=1
systemd_service_present=0
kernel_module_present=0
boot_entry_present=0
etc_latticra_present=0
network_authority_present=0
root_installer_claim_present=0
```

## Required Non-Claims

```text
ppa_claimed=0
ubuntu_archive_ready=0
canonical_endorsement_claimed=0
production_installer_ready=0
daily_driver_install_ready=0
root_installer_ready=0
operating_system_replacement_claimed=0
```

## Current Status

```text
ubuntu_local_deb_build_transcript_contract_present=1
ubuntu_local_deb_build_transcript_present=0
local_deb_build_transcript_accepted=0
build_transcript_acceptance_gate_unblocked=0
deb_artifact_created=0
deb_artifact_installed=0
deb_removed_from_host=0
license_expression_reviewed=1
license_expression_unresolved=0
ubuntu_lintian_static_metadata_unblocked=0
```

## Acceptance Rule

A future transcript may only be accepted if all required fields are present, the license expression has been reviewed, lintian/static metadata is unblocked, expected draft findings are classified, unexpected findings are either absent or explicitly reviewed, the acceptance gate is unblocked, and all non-claims remain zero.

The Ubuntu local deb build transcript acceptance gate records that acceptance decision separately from this evidence schema.

The Ubuntu local deb install/remove evidence contract is downstream of this schema and remains blocked until a reviewed build transcript is accepted.

## Validation

Run:

```sh
sh scripts/test-ubuntu-local-deb-build-transcript-contract.sh
```

Expected output:

```text
ubuntu_local_deb_build_transcript_contract: ok
```
