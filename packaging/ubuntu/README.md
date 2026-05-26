# Ubuntu Packaging Draft

Status: local-only packaging draft

This directory contains Ubuntu-oriented packaging experiments for Latticra.

The current debian metadata is a local-only draft used by static guards. It is not an Ubuntu archive package, not a PPA package, not Canonical approval evidence, not a Launchpad build record, not a lintian result, and not package-readiness evidence.

## Where this fits

- Documentation hub: [`../../docs/README.md`](../../docs/README.md)
- Ubuntu workflow: [`../../docs/UBUNTU_DEVELOPER_WORKFLOW.md`](../../docs/UBUNTU_DEVELOPER_WORKFLOW.md)
- Ubuntu readiness plan: [`../../docs/UBUNTU_READINESS_PLAN.md`](../../docs/UBUNTU_READINESS_PLAN.md)
- Current status: [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md)

Current guarded files:

```text
packaging/ubuntu/README.md
packaging/ubuntu/debian/control
packaging/ubuntu/debian/rules
packaging/ubuntu/debian/changelog
packaging/ubuntu/debian/copyright
packaging/ubuntu/debian/install
packaging/ubuntu/debian/source/format
scripts/test-ubuntu-local-deb-static-validation.sh
scripts/test-ubuntu-lintian-availability.sh
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
scripts/ubuntu-package-notice-inventory.sh
scripts/test-ubuntu-package-notice-inventory.sh
scripts/test-ubuntu-doc-payload-license-review-contract.sh
scripts/test-ubuntu-third-party-material-review-contract.sh
scripts/test-ubuntu-generated-artifact-notice-review-contract.sh
scripts/test-ubuntu-notice-file-decision-contract.sh
scripts/test-ubuntu-debian-copyright-notice-mapping-contract.sh
scripts/test-ubuntu-trademark-notice-boundary-contract.sh
scripts/test-ubuntu-release-artifact-notice-requirements-contract.sh
scripts/test-ubuntu-package-notice-promotion-gate-contract.sh
scripts/test-ubuntu-package-license-promotion-gate-contract.sh
scripts/test-ubuntu-package-notice-review-contract.sh
scripts/test-ubuntu-package-license-review-contract.sh
scripts/test-ubuntu-local-deb-build-transcript-contract.sh
.github/workflows/ubuntu-local-deb-static-validation.yml
.github/workflows/ubuntu-lintian-availability.yml
.github/workflows/ubuntu-package-notice-inventory.yml
.github/workflows/ubuntu-doc-payload-license-review-contract.yml
.github/workflows/ubuntu-third-party-material-review-contract.yml
.github/workflows/ubuntu-generated-artifact-notice-review-contract.yml
.github/workflows/ubuntu-notice-file-decision-contract.yml
.github/workflows/ubuntu-debian-copyright-notice-mapping-contract.yml
.github/workflows/ubuntu-trademark-notice-boundary-contract.yml
.github/workflows/ubuntu-release-artifact-notice-requirements-contract.yml
.github/workflows/ubuntu-package-notice-promotion-gate-contract.yml
.github/workflows/ubuntu-package-license-promotion-gate-contract.yml
.github/workflows/ubuntu-package-notice-review-contract.yml
.github/workflows/ubuntu-package-license-review-contract.yml
.github/workflows/ubuntu-local-deb-build-transcript-contract.yml
```

The static lane preserves:

```text
local_only_draft=1
deb_artifact_created=0
dpkg_buildpackage_run_required=0
debuild_run_required=0
lintian_run_required=0
lintian_availability_lane_present=1
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
package_license_review_contract_present=1
package_license_review_status=blocked-pending-formal-review
package_notice_review_contract_present=1
package_notice_review_status=blocked-pending-doc-license-and-notice-review
license_expression_candidate_recorded=1
packaging_license_expression_updated=0
local_deb_build_transcript_contract_present=1
local_deb_build_transcript_present=0
ppa_claimed=0
ubuntu_archive_ready=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
usr/bin/latticra
usr/share/doc/latticra/README.md
```

The CLI reports no-effect status and disabled runtime behavior.
