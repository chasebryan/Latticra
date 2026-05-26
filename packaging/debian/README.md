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
docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-debian-local-deb-static-validation.sh
.github/workflows/debian-local-deb-static-validation.yml
```

The static lane preserves:

```text
local_only_draft=1
debian_local_deb_draft_present=1
debian_static_deb_validation_present=1
deb_artifact_created=0
deb_installed_on_host=0
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
