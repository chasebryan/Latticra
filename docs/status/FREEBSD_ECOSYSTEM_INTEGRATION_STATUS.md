# FreeBSD Ecosystem Integration Status

Status: FreeBSD integration status record
Date: 2026-05-26

## Current Evidence

```text
freebsd_port_draft_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_source_archive_fixture_lane_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
temporary_freebsd_port_input_staged=1
temporary_freebsd_distfile_staged=1
freebsd_distinfo_file_written=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
portlint_run=0
poudriere_build_run=0
package_artifact_created=0
freebsd_ports_tree_submission_claimed=0
freebsd_official_port_claimed=0
production_installer_ready=0
```

The FreeBSD lane stages temporary package inputs only. It does not write `distinfo`, create packages, run portlint, install on a host, or accept ports-tree evidence.
