# Ubuntu Debian Copyright Notice Mapping Contract

Status: no-effect Debian copyright notice mapping contract
Scope: define Debian copyright notice-mapping evidence required before the Ubuntu package notice review can be promoted.

## Purpose

This contract turns the Ubuntu local deb `packaging/ubuntu/debian/copyright` notice-mapping blocker into a concrete review checklist.

It does not update `packaging/ubuntu/debian/copyright`, replace `LicenseRef-Latticra-TBD`, create a `NOTICE` file, decide the documentation license, build a package, publish a package, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
package_scope=local-deb-draft
debian_copyright_file=packaging/ubuntu/debian/copyright
debian_copyright_present=1
debian_copyright_format_url_present=1
debian_copyright_license_ref_tbd=1
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
notice_file_present=0
ubuntu_package_notice_inventory_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_notice_file_decision_contract_present=1
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

The current Debian copyright file is a local-only draft. It intentionally keeps `LicenseRef-Latticra-TBD` until package source scope, documentation scope, third-party material, generated-artifact notices, NOTICE-file requirements, and notice mappings are formally reviewed.

## Required Mapping Before Promotion

```text
debian_copyright_notice_mapping_reviewed=1
debian_copyright_binary_payload_mapping_reviewed=1
debian_copyright_doc_payload_mapping_reviewed=1
debian_copyright_third_party_notice_mapping_reviewed=1
debian_copyright_generated_artifact_notice_mapping_reviewed=1
debian_copyright_notice_file_mapping_reviewed=1
debian_copyright_trademark_notice_boundary_reviewed=1
debian_copyright_license_ref_replaced_or_justified=1
debian_copyright_missing_notice_entries=0
```

## Current Decision

```text
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping
debian_copyright_notice_mapping_reviewed=0
debian_copyright_binary_payload_mapping_reviewed=0
debian_copyright_doc_payload_mapping_reviewed=0
debian_copyright_third_party_notice_mapping_reviewed=0
debian_copyright_generated_artifact_notice_mapping_reviewed=0
debian_copyright_notice_file_mapping_reviewed=0
debian_copyright_trademark_notice_boundary_reviewed=0
debian_copyright_license_ref_replaced_or_justified=0
debian_copyright_missing_notice_entries=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until the local deb payload has a reviewed Debian copyright notice mapping. That review must explain how binary payload, documentation payload, third-party material, generated artifacts, NOTICE-file requirements, and trademark notice boundaries are represented in `packaging/ubuntu/debian/copyright`.

The trademark notice boundary remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

The release artifact notice requirements remain separate, but they must also be resolved before the Ubuntu package notice review can be promoted.

This contract is scoped to the Ubuntu local deb draft. It is not a repository-wide license audit or a Debian Policy compliance claim.

## Non-Claims

This contract is not legal advice. It does not claim NOTICE compliance, license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-debian-copyright-notice-mapping-contract.sh
```

Expected output:

```text
ubuntu_debian_copyright_notice_mapping_contract: ok
```
