# Ubuntu Package Notice Inventory

Status: no-effect package notice inventory
Scope: deterministic inventory report for the current Ubuntu local deb draft payload.

## Purpose

This inventory records the current notice inputs for the Ubuntu local deb draft.

It does not create a `NOTICE` file, build a package, publish a package, submit to Ubuntu, or provide legal advice.

## Current Payload Inventory

```text
package_scope=local-deb-draft
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
binary_payload_spdx=AGPL-3.0-or-later
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
root_license_file=LICENSE
root_license_current=hybrid-license-overview
debian_copyright_file=packaging/ubuntu/debian/copyright
```

## Current Notice Posture

```text
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
third_party_material_inventory_recorded=1
third_party_material_inventory_reviewed=0
third_party_material_missing_entries=0
generated_artifact_notice_reviewed=0
notice_file_present=0
notice_file_decision_recorded=0
doc_payload_license_reviewed=1
doc_payload_license_unresolved=0
debian_copyright_notice_mapping_reviewed=0
packaging_license_expression_updated=1
ubuntu_package_notice_review_unblocked=0
```

## Report Command

Run:

```sh
sh scripts/ubuntu-package-notice-inventory.sh
```

Expected key lines include:

```text
UBUNTU PACKAGE NOTICE INVENTORY
inventory_status=ok
inventory_mode=no-effect
ubuntu_package_notice_review_unblocked=0
```

## Relationship To Notice Review

The inventory is a fact report. It does not promote the Ubuntu package notice review contract.

The notice review remains blocked until third-party notices, generated-artifact notices, trademark notice boundaries, and the remaining Debian copyright notice mapping are reviewed.

## Validation

Run:

```sh
sh scripts/test-ubuntu-package-notice-inventory.sh
```

Expected output:

```text
ubuntu_package_notice_inventory: ok
```
