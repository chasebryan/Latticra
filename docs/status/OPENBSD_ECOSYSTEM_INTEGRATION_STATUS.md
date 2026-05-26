# OpenBSD Ecosystem Integration Status

Status: OpenBSD integration status record
Date: 2026-05-26

## Current Evidence

```text
openbsd_port_draft_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_source_archive_fixture_lane_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
temporary_openbsd_port_input_staged=1
temporary_openbsd_distfile_staged=1
openbsd_distinfo_file_written=0
permit_package_enabled=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
portcheck_run=0
bulk_build_run=0
package_artifact_created=0
openbsd_ports_tree_submission_claimed=0
openbsd_official_port_claimed=0
production_installer_ready=0
```

The OpenBSD lane stages temporary package inputs only. It does not write `distinfo`, enable `PERMIT_PACKAGE=Yes`, create packages, run portcheck, install on a host, or accept ports-tree evidence.
