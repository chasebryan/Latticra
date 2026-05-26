# Ubuntu Doc Payload License Review Contract

Status: no-effect documentation-license review contract
Scope: define the review evidence required before `README.md` can be treated as a resolved Ubuntu local deb documentation payload.

## Purpose

This contract turns the Ubuntu local deb documentation-license blocker into a concrete review checklist.

It does not decide the documentation license, relicense `README.md`, update `packaging/ubuntu/debian/copyright`, publish a package, create a PPA, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
doc_payload_source_present=1
root_license_file=LICENSE
root_license_current=Apache-2.0
license_policy_present=1
license_migration_plan_present=1
documentation_license_decision_present=0
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_review_contract_present=1
```

The current license migration plan records documentation licensing as undecided.

Current candidate language remains:

```text
candidate_doc_payload_license=Apache-2.0-or-docs-decision-pending
candidate_doc_payload_license_applied_to_packaging=0
```

## Required Review Before Promotion

```text
doc_payload_license_decision_recorded=1
doc_payload_license_expression_recorded=1
doc_payload_license_compatible_with_package=1
readme_embedded_material_reviewed=1
readme_generated_artifact_notice_reviewed=1
documentation_trademark_boundary_reviewed=1
documentation_notice_requirements_recorded=1
debian_copyright_doc_payload_mapping_reviewed=1
```

## Current Decision

```text
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
doc_payload_license_reviewed=0
doc_payload_license_unresolved=1
documentation_license_decision_present=0
doc_payload_license_decision_recorded=0
doc_payload_license_compatible_with_package=0
debian_copyright_doc_payload_mapping_reviewed=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until this documentation payload license review is resolved and mapped into Debian copyright metadata.

This contract is a guardrail for the current `README.md` package payload. It is not a general documentation relicensing decision for the whole repository.

## Non-Claims

This contract is not legal advice. It does not claim license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-doc-payload-license-review-contract.sh
```

Expected output:

```text
ubuntu_doc_payload_license_review_contract: ok
```
