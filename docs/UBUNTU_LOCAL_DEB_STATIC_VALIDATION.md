# Ubuntu Local Deb Static Validation

Status: active static validation lane
Scope: static checks for the local-only Ubuntu deb packaging draft.

## Purpose

This lane checks that the Ubuntu packaging draft is present, narrow, and honest.

It verifies local packaging shape for the no-effect CLI payload, but it does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`, and it does not create package artifacts.

## Guarded Files

```text
packaging/ubuntu/README.md
packaging/ubuntu/debian/control
packaging/ubuntu/debian/rules
packaging/ubuntu/debian/changelog
packaging/ubuntu/debian/copyright
packaging/ubuntu/debian/install
packaging/ubuntu/debian/source/format
scripts/test-ubuntu-local-deb-static-validation.sh
docs/UBUNTU_LINTIAN_AVAILABILITY.md
docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md
docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md
docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md
docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md
docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md
docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md
docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md
docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md
docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md
docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md
```

## Preserved Boundary

```text
local_only_draft=1
deb_artifact_created=0
dpkg_buildpackage_run_required=0
debuild_run_required=0
lintian_run_required=0
package_notice_inventory_present=1
package_notice_inventory_report_present=1
doc_payload_license_review_contract_present=1
doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
documentation_license_decision_present=0
doc_payload_license_decision_recorded=0
third_party_material_review_contract_present=1
third_party_material_review_status=blocked-pending-third-party-material-review
third_party_material_inventory_recorded=1
third_party_material_inventory_reviewed=0
third_party_notice_requirements_recorded=0
generated_artifact_notice_review_contract_present=1
generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review
generated_artifact_notice_reviewed=0
generated_artifact_notice_requirements_recorded=0
notice_file_decision_contract_present=1
notice_file_decision_status=blocked-pending-notice-file-decision
notice_file_present=0
notice_file_decision_recorded=0
debian_copyright_notice_mapping_contract_present=1
debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping
debian_copyright_notice_mapping_reviewed=0
trademark_notice_boundary_contract_present=1
trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary
trademark_notice_boundary_recorded=0
release_artifact_notice_requirements_contract_present=1
release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements
release_artifact_notice_requirements_recorded=0
package_notice_promotion_gate_contract_present=1
package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
package_notice_promotion_gate_unblocked=0
package_license_promotion_gate_contract_present=1
package_license_promotion_gate_status=blocked-pending-package-license-prerequisites
package_license_promotion_gate_unblocked=0
ppa_claimed=0
ubuntu_archive_ready=0
production_readiness_claimed=0
```

## Package Intent

The local deb draft records only this initial payload shape:

```text
usr/bin/latticra
usr/share/doc/latticra/README.md
```

The CLI remains the no-effect status surface from:

```text
src/latticra_cli.c
```

## Explicit Non-Claims

This static lane does not:

```text
build a deb artifact
install a deb artifact
publish a PPA
submit to Ubuntu
claim Ubuntu archive readiness
install a systemd service
install kernel modules
write /etc/latticra
claim root installer readiness
claim production readiness
```

## Next Recommended Lane

Review the Ubuntu package license promotion gate before lintian/static metadata, build transcript evidence, or package license expression promotion advances.

## Validation

Run:

```sh
sh scripts/test-ubuntu-local-deb-static-validation.sh
```

Expected output:

```text
ubuntu_local_deb_static_validation: ok
```
