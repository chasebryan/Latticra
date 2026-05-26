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
docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md
```

## Preserved Boundary

```text
local_only_draft=1
deb_artifact_created=0
dpkg_buildpackage_run_required=0
debuild_run_required=0
lintian_run_required=0
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

Promote the Ubuntu package license expression only after documentation licensing and notice obligations are reviewed.

## Validation

Run:

```sh
sh scripts/test-ubuntu-local-deb-static-validation.sh
```

Expected output:

```text
ubuntu_local_deb_static_validation: ok
```
