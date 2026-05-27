# Debian Ecosystem Integration Status

Status: Debian integration status record
Date: 2026-05-26

## Summary

Latticra now has a Debian-facing local deb packaging draft for the no-effect CLI payload.

This is an ecosystem integration checkpoint, not a production readiness claim.

## Current Evidence

```text
debian_local_deb_draft_present=1
debian_static_deb_validation_present=1
deb_artifact_created=0
deb_installed_on_host=0
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
debian_freebsd_openbsd_package_build_gate_contract_present=1
debian_freebsd_openbsd_package_build_environment_contract_present=1
debian_freebsd_openbsd_package_artifact_naming_contract_present=1
debian_freebsd_openbsd_package_payload_inspection_contract_present=1
debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1
debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1
debian_freebsd_openbsd_package_validation_promotion_blocker_matrix_contract_present=1
temporary_debian_source_input_staged=1
temporary_debian_orig_archive_staged=1
temporary_debian_debian_dir_overlay_staged=1
package_build_gate_state=closed-no-effect
package_build_environment_contract_state=specified-no-effect
artifact_naming_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
publication_non_claim_review_contract_state=specified-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
debian_build_allowed=0
debian_clean_build_environment_documented=1
debian_build_environment_provisioned=0
explicit_operator_build_authorization=0
disposable_validation_environment_required=1
environment_transcript_present=0
debian_artifact_name_pattern_recorded=1
debian_source_package_name=latticra_0.0.0-1local1.dsc
debian_binary_package_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.deb
package_artifact_output_directory_created=0
repository_package_artifact_write_allowed=0
debian_payload_expected_bin=usr/bin/latticra
debian_payload_expected_doc=usr/share/doc/latticra/README.md
debian_payload_inspection_run=0
package_payload_inspection_run=0
package_payload_accepted=0
debian_install_remove_transcript_required=1
debian_install_remove_transcript_present=0
debian_package_install_run=0
debian_package_remove_run=0
remove_on_host_run=0
publication_non_claim_review_present=1
debian_publication_non_claim_review_present=1
debian_package_publication_claimed=0
debian_source_upload_run=0
debian_mentors_upload_run=0
debian_archive_upload_run=0
debian_debsign_run=0
debian_dput_run=0
platform_build_evidence_accepted=0
debian_validation_promotion_blocked=1
debian_platform_build_evidence_accepted=0
package_validation_result_promoted=0
debian_validation_result_promoted=0
source_archive_policy_recorded=1
source_archive_created=0
source_archive_sha256_recorded=0
source_archive_accepted_for_build=0
dpkg_buildpackage_run_required=0
debuild_run_required=0
lintian_run_required=0
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
package_artifact_created=0
package_artifact_sha256_recorded=0
install_on_host_run=0
lintian_transcript_present=0
debian_archive_ready=0
debian_mentors_upload_claimed=0
debian_sponsorship_claimed=0
debian_ftp_master_acceptance_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
packaging/debian/README.md
packaging/debian/debian/control
packaging/debian/debian/rules
packaging/debian/debian/changelog
packaging/debian/debian/copyright
packaging/debian/debian/install
packaging/debian/debian/source/format
scripts/test-debian-local-deb-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-gate-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-environment-contract.sh
scripts/test-debian-freebsd-openbsd-package-artifact-naming-contract.sh
scripts/test-debian-freebsd-openbsd-package-payload-inspection-contract.sh
scripts/test-debian-freebsd-openbsd-package-install-remove-transcript-contract.sh
scripts/test-debian-freebsd-openbsd-package-publication-non-claim-review-contract.sh
scripts/test-debian-freebsd-openbsd-package-validation-promotion-blocker-matrix-contract.sh
.github/workflows/debian-local-deb-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-gate-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-environment-contract.yml
.github/workflows/debian-freebsd-openbsd-package-artifact-naming-contract.yml
.github/workflows/debian-freebsd-openbsd-package-payload-inspection-contract.yml
.github/workflows/debian-freebsd-openbsd-package-install-remove-transcript-contract.yml
.github/workflows/debian-freebsd-openbsd-package-publication-non-claim-review-contract.yml
.github/workflows/debian-freebsd-openbsd-package-validation-promotion-blocker-matrix-contract.yml
```

## Current Boundary

The Debian lane does not publish a package, upload to mentors.debian.net, submit to Debian, claim Debian archive readiness, claim Debian sponsorship, claim ftp-master acceptance, install a root service, change init/systemd state, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local deb metadata now records Apache-2.0 for existing-code defaults, AGPL-3.0-or-later for the no-effect CLI payload, and CC-BY-4.0 for documentation while source archive and notice obligations remain under review.

The source archive contract records the expected `latticra_0.0.0.orig.tar.gz` boundary while keeping archive creation, checksum acceptance, source package creation, and build transcript promotion blocked.

The package-build gate is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md`. It keeps `package_build_gate_state=closed-no-effect`, `debian_build_allowed=0`, `dpkg_buildpackage_run=0`, `debuild_run=0`, and `lintian_run=0` until source, checksum, license, notice, clean build environment, operator authorization, payload inspection, install/remove transcript, and publication non-claim evidence exists.

The package-build environment contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md`. It documents the Debian clean build environment requirement while keeping `debian_build_environment_provisioned=0`, `explicit_operator_build_authorization=0`, `environment_transcript_present=0`, and all Debian package build commands disabled.

The package artifact naming contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md`. It records future Debian source and binary artifact names while keeping `package_artifact_created=0`, `repository_package_artifact_write_allowed=0`, and `package_artifact_sha256_recorded=0`.

The package payload inspection contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md`. It records the expected Debian payload paths while keeping `debian_payload_inspection_run=0`, `package_payload_accepted=0`, and `package_artifact_created=0`.

The package install/remove transcript contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md`. It records future disposable install/remove transcript requirements while keeping `debian_package_install_run=0`, `debian_package_remove_run=0`, and `install_on_host_run=0`.

The package publication non-claim review contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md`. It records local-only Debian publication non-claims while keeping `debian_package_publication_claimed=0`, `debian_dput_run=0`, and package validation promotion blocked.

The package validation promotion blocker matrix is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md`. It ties Debian source, environment, artifact, payload, install/remove, and publication non-claim blockers together while keeping `debian_platform_build_evidence_accepted=0` and `debian_validation_result_promoted=0`.

## Next Recommended Lane

```text
Add a Debian package build-evidence intake denial contract before any Debian build lane can open.
```
