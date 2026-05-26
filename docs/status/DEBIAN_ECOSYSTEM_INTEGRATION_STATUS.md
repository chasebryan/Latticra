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
temporary_debian_source_input_staged=1
temporary_debian_orig_archive_staged=1
temporary_debian_debian_dir_overlay_staged=1
package_build_gate_state=closed-no-effect
debian_build_allowed=0
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
.github/workflows/debian-local-deb-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-gate-contract.yml
```

## Current Boundary

The Debian lane does not publish a package, upload to mentors.debian.net, submit to Debian, claim Debian archive readiness, claim Debian sponsorship, claim ftp-master acceptance, install a root service, change init/systemd state, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local deb metadata keeps `LicenseRef-Latticra-TBD` until license, documentation, source archive, and notice obligations are reviewed.

The source archive contract records the expected `latticra_0.0.0.orig.tar.gz` boundary while keeping archive creation, checksum acceptance, source package creation, and build transcript promotion blocked.

The package-build gate is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md`. It keeps `package_build_gate_state=closed-no-effect`, `debian_build_allowed=0`, `dpkg_buildpackage_run=0`, `debuild_run=0`, and `lintian_run=0` until source, checksum, license, notice, clean build environment, operator authorization, payload inspection, install/remove transcript, and publication non-claim evidence exists.

## Next Recommended Lane

```text
Add a Debian package-build environment contract only after the package-build gate prerequisites are reviewed.
```
