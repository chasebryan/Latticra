# Ubuntu Readiness Plan

Status: planning and compatibility record
Scope: preparing Latticra for Ubuntu-friendly development, local validation, and local-only deb packaging.

## Purpose

This plan prepares Latticra for an Ubuntu-facing path without claiming Ubuntu archive acceptance, Canonical endorsement, PPA readiness, production installer readiness, or distribution status.

The near-term target is:

```text
Latticra builds cleanly on Ubuntu Linux.
Latticra Panel can be run from source on Ubuntu with documented apt prerequisites.
Latticra has a local-only deb packaging draft for the no-effect CLI payload.
Latticra preserves its current non-claims.
```

## Terminology Boundary

Use:

```text
Ubuntu readiness
Ubuntu compatibility lane
Ubuntu local deb draft
Latticra on Ubuntu
local-only deb packaging draft
```

Avoid claiming:

```text
official Ubuntu package
Ubuntu archive package
PPA release
Canonical endorsement
Ubuntu flavor
Ubuntu derivative
operating-system replacement
```

Those terms require separate packaging, policy, legal, trademark, and community review.

## Ubuntu-Facing Requirements To Respect

Before Latticra can be proposed beyond a local deb draft, it should be checked against Ubuntu/Debian package expectations:

```text
source package layout
debian/control hygiene
debian/copyright accuracy
license expression review
Build-Depends completeness
Rules-Requires-Root posture
no maintainer scripts without review
no systemd service installation without review
no root-owned host mutation without review
lintian output classification
pbuilder/sbuild or equivalent build evidence
install/remove behavior evidence
```

## Current Latticra Posture

Current Latticra evidence is still early-stage and report-oriented.

Known current posture:

```text
ubuntu_build_lane_present=1
ubuntu_panel_prerequisites_documented=1
ubuntu_local_deb_draft_present=1
ubuntu_lintian_availability_present=1
ubuntu_package_license_review_contract_present=1
ubuntu_package_license_review_status=blocked-pending-formal-review
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
ubuntu_third_party_material_review_contract_present=1
ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review
ubuntu_notice_file_decision_contract_present=1
ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-license-prerequisites
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review
ubuntu_local_deb_build_transcript_contract_present=1
ubuntu_local_deb_build_transcript_present=0
deb_artifact_created=0
ppa_claimed=0
ubuntu_archive_ready=0
production_installer_ready=0
daily_driver_install_ready=0
root_installer_ready=0
```

The first Ubuntu target is development and local validation. It is not an Ubuntu archive package, PPA package, image, flavor, distribution, or replacement operating system.

## Phase 1: Ubuntu Build Lane

The Ubuntu build lane proves the current guarded project foundation compiles with Ubuntu toolchains.

Current guarded files:

```text
scripts/test-ubuntu-build-lane.sh
.github/workflows/ubuntu-build-lane.yml
docs/UBUNTU_DEVELOPER_WORKFLOW.md
scripts/test-ubuntu-lintian-availability.sh
.github/workflows/ubuntu-lintian-availability.yml
```

Initial checks remain conservative:

```text
C compiler available
project C guards compile
kernel lifecycle guards compile
no-effect CLI status surface present
no external authority claims added
```

## Phase 2: Panel Prerequisites Lane

The Panel remains user-local on Ubuntu. The apt prerequisites support local Rust/egui development and desktop metadata refresh without adding root-installed Latticra services.

Current guarded files:

```text
README.md
docs/QUICK_START_CHEATSHEET.md
installer/README.md
docs/UBUNTU_DEVELOPER_WORKFLOW.md
```

## Phase 3: Local Deb Draft Lane

Packaging metadata is present as a local-only draft after the Ubuntu build lane.

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
.github/workflows/ubuntu-local-deb-static-validation.yml
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
docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md
docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md
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
scripts/test-ubuntu-package-license-review-contract.sh
scripts/test-ubuntu-package-notice-review-contract.sh
scripts/test-ubuntu-local-deb-build-transcript-contract.sh
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

The first deb draft is only a packaging-shape record until lint/build/install evidence is added.

## Non-Claims

This plan does not:

```text
publish a deb package
create a PPA
submit Latticra to Ubuntu
claim Ubuntu archive readiness
claim Canonical endorsement
install a root service
modify systemd
modify the kernel
claim production readiness
claim operating-system completeness
```

## Recommended Next Slice

Recommended next slice:

```text
Review the Ubuntu package license promotion gate contract, then advance lintian/static metadata only after package notice and package license prerequisites are reviewed.
```

That should preserve the current no-artifact, no-submission, local-only Ubuntu package posture while the local deb path matures.
