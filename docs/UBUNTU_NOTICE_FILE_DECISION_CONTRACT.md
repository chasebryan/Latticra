# Ubuntu NOTICE File Decision Contract

Status: no-effect NOTICE file decision contract
Scope: define NOTICE file decision evidence required before the Ubuntu local deb notice review can be promoted.

## Purpose

This contract turns the Ubuntu local deb `NOTICE` file blocker into a concrete review checklist.

It does not create a `NOTICE` file, decide that one is required or unnecessary, update `packaging/ubuntu/debian/copyright`, build a package, publish a package, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
package_scope=local-deb-draft
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
notice_file_present=0
license_policy_present=1
third_party_material_policy_present=1
generated_artifact_notice_policy_present=1
ubuntu_package_notice_inventory_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

The current repository has no root `NOTICE` file and no reviewed package decision saying whether one is required for the Ubuntu local deb draft.

## Required Decision Before Promotion

```text
notice_file_decision_recorded=1
notice_file_required_decision_recorded=1
notice_file_content_requirements_recorded=1
notice_file_install_path_reviewed=1
notice_file_packaging_mapping_reviewed=1
notice_file_absence_justification_recorded=1
notice_file_missing_required_entries=0
```

## Current Decision

```text
ubuntu_notice_file_decision_contract_present=1
ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision
notice_file_present=0
notice_file_decision_recorded=0
notice_file_required_decision_recorded=0
notice_file_content_requirements_recorded=0
notice_file_install_path_reviewed=0
notice_file_packaging_mapping_reviewed=0
notice_file_absence_justification_recorded=0
notice_file_missing_required_entries=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until the package has a reviewed `NOTICE` file decision. That decision may later require a file or record why no file is required, but this contract does not make that decision.

The Debian copyright notice mapping review remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

This contract is scoped to the Ubuntu local deb draft. It is not a repository-wide release notice decision.

## Non-Claims

This contract is not legal advice. It does not claim NOTICE compliance, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-notice-file-decision-contract.sh
```

Expected output:

```text
ubuntu_notice_file_decision_contract: ok
```
