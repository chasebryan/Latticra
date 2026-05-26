# Ubuntu Debian Copyright Notice Mapping Contract

Status: no-effect Debian copyright notice mapping contract
Scope: define the Debian copyright notice-mapping evidence required before the Ubuntu local deb notice review can be promoted.

## Purpose

This contract turns the Ubuntu local deb `debian/copyright` notice-mapping blocker into a concrete review checklist.

It does not update `packaging/ubuntu/debian/copyright`, replace `LicenseRef-Latticra-TBD`, create a `NOTICE` file, build a package, publish a package, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
package_scope=local-deb-draft
debian_copyright_file=packaging/ubuntu/debian/copyright
debian_copyright_format_present=1
debian_copyright_license_ref_present=1
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
ubuntu_package_notice_inventory_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_notice_file_decision_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

The current Ubuntu local deb draft keeps `packaging/ubuntu/debian/copyright` at `LicenseRef-Latticra-TBD` until formal package license and notice review accepts the source, documentation, third-party material, generated-artifact, and NOTICE file scope.

## Required Mapping Before Promotion

```text
debian_copyright_format_reviewed=1
debian_copyright_source_stanza_reviewed=1
debian_copyright_binary_payload_mapping_reviewed=1
debian_copyright_doc_payload_mapping_reviewed=1
debian_copyright_third_party_mapping_reviewed=1
debian_copyright_generated_artifact_mapping_reviewed=1
debian_copyright_notice_mapping_reviewed=1
debian_copyright_notice_missing_entries=0
debian_copyright_license_ref_removed_or_justified=1
packaging_license_expression_updated=1
```

## Current Decision

```text
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping
debian_copyright_file_present=1
debian_copyright_format_reviewed=0
debian_copyright_source_stanza_reviewed=0
debian_copyright_binary_payload_mapping_reviewed=0
debian_copyright_doc_payload_mapping_reviewed=0
debian_copyright_third_party_mapping_reviewed=0
debian_copyright_generated_artifact_mapping_reviewed=0
debian_copyright_notice_mapping_reviewed=0
debian_copyright_notice_missing_entries=0
debian_copyright_license_ref_present=1
debian_copyright_license_ref_removed_or_justified=0
packaging_license_expression_updated=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until the Debian copyright mapping is reviewed for the binary payload, documentation payload, third-party material, generated artifacts, and NOTICE file decision.

This contract records the mapping checkpoint only. It does not decide the final package license expression and does not claim that Debian copyright metadata is complete.

## Non-Claims

This contract is not legal advice. It does not claim Debian copyright completeness, license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-debian-copyright-notice-mapping-contract.sh
```

Expected output:

```text
ubuntu_debian_copyright_notice_mapping_contract: ok
```
