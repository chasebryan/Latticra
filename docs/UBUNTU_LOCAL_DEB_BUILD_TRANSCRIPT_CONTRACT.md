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

The current repository state intentionally does not satisfy `license_expression_reviewed=1`, so this contract remains future evidence only.

The current package license review checkpoint is:

```text
ubuntu_package_license_review_contract_present=1
ubuntu_package_license_review_status=blocked-pending-formal-review
ubuntu_package_notice_inventory_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
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
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review
license_expression_candidate_recorded=1
packaging_license_expression_updated=0
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
deb_artifact_created=0
deb_artifact_installed=0
license_expression_reviewed=0
license_expression_unresolved=1
```

## Acceptance Rule

A future transcript may only be accepted if all required fields are present, the license expression has been reviewed, expected draft findings are classified, unexpected findings are either absent or explicitly reviewed, and all non-claims remain zero.

## Validation

Run:

```sh
sh scripts/test-ubuntu-local-deb-build-transcript-contract.sh
```

Expected output:

```text
ubuntu_local_deb_build_transcript_contract: ok
```
