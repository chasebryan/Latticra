# OpenBSD Port Draft

Status: local-only port draft

This directory contains OpenBSD ports metadata experiments for Latticra.

The current port files are a local-only draft used by static guards and temporary package-input handoff checks. They are not an OpenBSD ports tree submission, not a ports@ review thread, not maintainer acceptance evidence, not a `make package` result, not a bulk build result, not a portcheck result, and not package-readiness evidence.

## Current Boundary

```text
local_only_draft=1
openbsd_port_draft_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
temporary_openbsd_port_input_staged=1
temporary_openbsd_distfile_staged=1
openbsd_distinfo_file_written=0
permit_package_enabled=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
package_artifact_created=0
openbsd_ports_tree_submission_claimed=0
openbsd_official_port_claimed=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
bin/latticra
share/doc/latticra/README.md
```
