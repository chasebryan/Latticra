# Ubuntu Ecosystem Integration Status

Status: Ubuntu integration status record
Date: 2026-05-26

## Summary

Latticra now has an Ubuntu-facing compatibility lane for development, Panel prerequisites, and a local-only deb packaging draft.

This is an ecosystem integration checkpoint, not a production readiness claim.

## Current Evidence

```text
ubuntu_build_lane_present=1
ubuntu_developer_workflow_present=1
ubuntu_panel_prerequisites_documented=1
ubuntu_quickstart_documented=1
ubuntu_local_deb_draft_present=1
ubuntu_static_deb_validation_present=1
ubuntu_lintian_availability_present=1
ubuntu_local_deb_build_transcript_contract_present=1
ubuntu_local_deb_build_transcript_present=0
deb_artifact_created=0
deb_installed_on_host=0
ubuntu_package_license_review_contract_present=1
ubuntu_package_license_review_status=blocked-pending-formal-review
license_expression_candidate_recorded=1
license_expression_reviewed=0
license_expression_unresolved=1
packaging_license_expression_updated=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
ppa_claimed=0
ubuntu_archive_ready=0
canonical_endorsement_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/UBUNTU_READINESS_PLAN.md
docs/UBUNTU_DEVELOPER_WORKFLOW.md
docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
docs/UBUNTU_LINTIAN_AVAILABILITY.md
docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md
packaging/ubuntu/README.md
packaging/ubuntu/debian/control
packaging/ubuntu/debian/rules
packaging/ubuntu/debian/changelog
packaging/ubuntu/debian/copyright
packaging/ubuntu/debian/install
packaging/ubuntu/debian/source/format
scripts/test-ubuntu-build-lane.sh
scripts/test-ubuntu-developer-workflow.sh
scripts/test-ubuntu-local-deb-static-validation.sh
scripts/test-ubuntu-lintian-availability.sh
scripts/test-ubuntu-package-license-review-contract.sh
scripts/test-ubuntu-local-deb-build-transcript-contract.sh
```

## Public Entry Points

Ubuntu setup and package posture are now linked from:

```text
README.md
docs/QUICK_START_CHEATSHEET.md
installer/README.md
docs/status/README.md
```

## Current Boundary

The Ubuntu lane does not publish a package, create a PPA, claim Ubuntu archive readiness, install a root service, change systemd, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local deb build transcript contract is intentionally blocked from evidence promotion until the package license expression is reviewed.

The Ubuntu package license review contract now records the current source facts and candidate expression, but it keeps packaging metadata at `LicenseRef-Latticra-TBD` until formal review accepts the source and documentation scope.

## Next Recommended Lane

```text
Promote the Ubuntu package license expression only after documentation licensing and notice obligations are reviewed.
```
