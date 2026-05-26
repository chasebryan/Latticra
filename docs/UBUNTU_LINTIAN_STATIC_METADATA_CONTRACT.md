# Ubuntu Lintian Static Metadata Contract

Status: no-effect lintian static metadata contract
Scope: define the static lintian metadata evidence required before Ubuntu local deb build transcript evidence can advance.

## Purpose

This contract turns the future Ubuntu lintian/static metadata lane into a guarded evidence schema.

It does not run `lintian`, `dpkg-buildpackage`, `debuild`, `sbuild`, or `pbuilder`. It does not create, install, publish, or upload a deb package.

## Required Inputs

```text
ubuntu_lintian_availability_present=1
ubuntu_local_deb_static_validation_present=1
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites
```

## Required Evidence Before Promotion

```text
debian_control_present=1
debian_rules_present=1
debian_changelog_present=1
debian_copyright_present=1
debian_install_present=1
debian_source_format_present=1
rules_requires_root_no=1
license_expression_reviewed=1
license_expression_unresolved=0
packaging_license_expression_updated=1
lintian_command_recorded=1
lintian_static_metadata_findings_classified=1
lintian_expected_draft_findings_classified=1
lintian_unexpected_findings_classified=1
ubuntu_lintian_static_metadata_unblocked=1
```

## Current State

```text
ubuntu_lintian_static_metadata_contract_present=1
ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion
ubuntu_lintian_availability_present=1
ubuntu_local_deb_static_validation_present=1
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites
lintian_static_metadata_run=0
lintian_command_recorded=0
lintian_static_metadata_findings_classified=0
lintian_expected_draft_findings_classified=0
lintian_unexpected_findings_classified=0
license_expression_reviewed=1
license_expression_unresolved=0
packaging_license_expression_updated=1
deb_artifact_created=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Build Evidence

The Ubuntu local deb build transcript contract may not accept build evidence until this static lintian metadata contract is unblocked and any lintian findings are recorded and classified.

This contract is deliberately static. It records the future evidence shape without running lintian or creating package artifacts.

## Non-Claims

This contract does not claim lintian success, Debian Policy compliance, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-lintian-static-metadata-contract.sh
```

Expected output:

```text
ubuntu_lintian_static_metadata_contract: ok
```
