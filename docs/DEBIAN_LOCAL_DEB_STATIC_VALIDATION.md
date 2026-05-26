# Debian Local Deb Static Validation

Status: active static validation lane
Scope: static checks for the local-only Debian deb packaging draft.

## Purpose

This lane checks that the Debian packaging draft is present, narrow, and honest.

It verifies local packaging shape for the no-effect CLI payload, but it does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`, and it does not create package artifacts.

## Guarded Files

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

## Preserved Boundary

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
upload to mentors.debian.net
submit to Debian
claim Debian archive readiness
claim Debian sponsorship
claim ftp-master acceptance
install a system service
install kernel modules
write /etc/latticra
claim root installer readiness
claim production readiness
```

## Next Recommended Lane

Add a Debian lintian availability and transcript contract only after the local deb license expression and source archive boundary are reviewed.

## Validation

Run:

```sh
sh scripts/test-debian-local-deb-static-validation.sh
```

Expected output:

```text
debian_local_deb_static_validation: ok
```
