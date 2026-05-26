# Debian Packaging Draft

Status: local-only packaging draft

This directory contains Debian-oriented packaging experiments for Latticra.

The current debian metadata is a local-only draft used by static guards. It is not a Debian archive package, not a mentors.debian.net upload, not sponsorship evidence, not ftp-master acceptance evidence, not a local `dpkg-buildpackage` result, not a lintian result, and not package-readiness evidence.

## Where This Fits

- Documentation hub: [`../../docs/README.md`](../../docs/README.md)
- Debian status: [`../../docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md`](../../docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md)
- Current status: [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md)

Current guarded files:

```text
packaging/debian/README.md
packaging/debian/debian/control
packaging/debian/debian/rules
packaging/debian/debian/changelog
packaging/debian/debian/copyright
packaging/debian/debian/install
packaging/debian/debian/source/format
docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-debian-local-deb-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
.github/workflows/debian-local-deb-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
```

The static lane preserves:

```text
local_only_draft=1
debian_local_deb_draft_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
temporary_debian_source_input_staged=1
temporary_debian_orig_archive_staged=1
temporary_debian_debian_dir_overlay_staged=1
debian_static_deb_validation_present=1
deb_artifact_created=0
deb_installed_on_host=0
debian_freebsd_openbsd_source_archive_contract_present=1
source_archive_policy_recorded=1
source_archive_created=0
source_archive_sha256_recorded=0
source_archive_accepted_for_build=0
dpkg_buildpackage_run_required=0
debuild_run_required=0
lintian_run_required=0
lintian_transcript_present=0
debian_archive_ready=0
debian_mentors_upload_claimed=0
debian_sponsorship_claimed=0
debian_ftp_master_acceptance_claimed=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
usr/bin/latticra
usr/share/doc/latticra/README.md
```

The CLI reports no-effect status and disabled runtime behavior.

The source archive contract records the expected `latticra_0.0.0.orig.tar.gz` boundary, but it does not create an archive, run `dpkg-source`, run `dpkg-buildpackage`, or accept Debian build evidence.
