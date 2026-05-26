# FreeBSD Port Draft

Status: local-only port draft

This directory contains FreeBSD ports metadata experiments for Latticra.

The current port files are a local-only draft used by static guards and temporary package-input handoff checks. They are not a FreeBSD ports tree submission, not a Bugzilla PR, not committer review evidence, not a poudriere build, not a `make package` result, not a portlint result, and not package-readiness evidence.

## Current Boundary

```text
local_only_draft=1
freebsd_port_draft_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
temporary_freebsd_port_input_staged=1
temporary_freebsd_distfile_staged=1
freebsd_distinfo_file_written=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
package_artifact_created=0
freebsd_ports_tree_submission_claimed=0
freebsd_official_port_claimed=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
bin/latticra
%%DOCSDIR%%/README.md
```
