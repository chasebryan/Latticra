# Debian Ecosystem Integration Status

Status: Debian integration status record
Date: 2026-05-26

## Current Evidence

```text
debian_local_deb_draft_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_source_archive_fixture_lane_present=1
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
production_installer_ready=0
```

The Debian lane stages temporary package inputs only. It does not create source packages, binary packages, lintian evidence, install evidence, upload evidence, or archive-readiness evidence.
