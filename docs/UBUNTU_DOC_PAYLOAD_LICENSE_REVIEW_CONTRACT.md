# Ubuntu Doc Payload License Review Contract

Status: no-effect documentation-license review contract
Scope: define the review evidence required before `README.md` can be treated as a resolved Ubuntu local deb documentation payload.

## Purpose

This contract records the Ubuntu local deb documentation-license decision and its package mapping checklist.

It does not publish a package, create a PPA, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
doc_payload_source_present=1
root_license_file=LICENSE
root_license_current=hybrid-license-overview
license_policy_present=1
license_migration_plan_present=1
documentation_license_decision_present=1
ubuntu_package_notice_inventory_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_notice_file_decision_contract_present=1
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

The current license migration plan records documentation licensing as decided.

Current package documentation license:

```text
candidate_doc_payload_license=CC-BY-4.0
candidate_doc_payload_license_applied_to_packaging=1
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
ubuntu_doc_payload_license_review_status=resolved-cc-by-4.0
doc_payload_license_reviewed=1
doc_payload_license_unresolved=0
documentation_license_decision_present=1
doc_payload_license_decision_recorded=1
doc_payload_license_compatible_with_package=1
debian_copyright_doc_payload_mapping_reviewed=1
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=1
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until this documentation payload license review is resolved and mapped into Debian copyright metadata.

The third-party material review remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

The generated-artifact notice review remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

The NOTICE file decision remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

The Debian copyright notice mapping remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

The trademark notice boundary remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

The release artifact notice requirements remain separate, but they must also be resolved before the Ubuntu package notice review can be promoted.

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
