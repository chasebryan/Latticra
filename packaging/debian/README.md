# Debian Packaging Draft

Status: local-only packaging draft

This directory contains Debian-oriented packaging experiments for Latticra.

The current debian metadata is a local-only draft used by static guards and temporary package-input handoff checks. It is not a Debian archive package, not a mentors.debian.net upload, not sponsorship evidence, not ftp-master acceptance evidence, not a local `dpkg-buildpackage` result, not a lintian result, and not package-readiness evidence.

## Current Boundary

```text
local_only_draft=1
debian_local_deb_draft_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
temporary_debian_source_input_staged=1
temporary_debian_orig_archive_staged=1
temporary_debian_debian_dir_overlay_staged=1
dpkg_source_run=0
dpkg_buildpackage_run=0
deb_artifact_created=0
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
