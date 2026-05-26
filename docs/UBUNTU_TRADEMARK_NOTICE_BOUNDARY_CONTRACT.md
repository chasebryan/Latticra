# Ubuntu Trademark Notice Boundary Contract

Status: no-effect trademark notice boundary contract
Scope: define trademark, identity, and endorsement-boundary evidence required before the Ubuntu package notice review can be promoted.

## Purpose

This contract turns the Ubuntu local deb trademark notice blocker into a concrete review checklist.

It does not update package metadata, change `packaging/ubuntu/debian/copyright`, create a `NOTICE` file, decide the documentation license, build a package, publish a package, submit to Ubuntu, grant trademark rights, or provide legal advice.

## Current Inputs

```text
package_scope=local-deb-draft
trademark_policy_present=1
project_identity_terms_recorded=1
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
debian_control_file=packaging/ubuntu/debian/control
debian_copyright_file=packaging/ubuntu/debian/copyright
ubuntu_package_notice_inventory_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_notice_file_decision_contract_present=1
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

The current package draft is local-only and makes no Ubuntu archive, PPA, Canonical endorsement, or production readiness claim.

## Required Boundary Before Promotion

```text
trademark_notice_boundary_recorded=1
trademark_policy_applied_to_package_notice=1
package_description_endorsement_boundary_reviewed=1
debian_copyright_trademark_notice_boundary_reviewed=1
documentation_trademark_boundary_reviewed=1
canonical_endorsement_boundary_reviewed=1
project_identity_downstream_use_boundary_recorded=1
trademark_notice_missing_required_entries=0
```

## Current Decision

```text
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary
trademark_notice_boundary_recorded=0
trademark_policy_applied_to_package_notice=0
package_description_endorsement_boundary_reviewed=0
debian_copyright_trademark_notice_boundary_reviewed=0
documentation_trademark_boundary_reviewed=0
canonical_endorsement_boundary_reviewed=0
project_identity_downstream_use_boundary_recorded=0
trademark_notice_missing_required_entries=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until the local deb payload has a reviewed trademark and endorsement boundary. That review must preserve the distinction between open-source license permissions and Latticra/Bryforge project identity rights.

This contract is scoped to the Ubuntu local deb draft. It is not a trademark registration, enforcement plan, Ubuntu archive claim, or downstream redistribution approval.

## Non-Claims

This contract is not legal advice. It does not claim trademark compliance, NOTICE compliance, license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-trademark-notice-boundary-contract.sh
```

Expected output:

```text
ubuntu_trademark_notice_boundary_contract: ok
```
