# FreeBSD Port Draft

Status: local-only port draft

This directory contains FreeBSD ports metadata experiments for Latticra.

The current port files are a local-only draft used by static guards. They are not a FreeBSD ports tree submission, not a Bugzilla PR, not committer review evidence, not a poudriere build, not a `make package` result, not a portlint result, and not package-readiness evidence.

## Where This Fits

- Documentation hub: [`../../docs/README.md`](../../docs/README.md)
- FreeBSD status: [`../../docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md`](../../docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md)
- Current status: [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md)

Current guarded files:

```text
packaging/freebsd/README.md
packaging/freebsd/Makefile
packaging/freebsd/pkg-descr
packaging/freebsd/pkg-plist
docs/FREEBSD_PORT_STATIC_VALIDATION.md
docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-freebsd-port-static-validation.sh
.github/workflows/freebsd-port-static-validation.yml
```

The static lane preserves:

```text
local_only_draft=1
freebsd_port_draft_present=1
freebsd_port_static_validation_present=1
freebsd_ports_tree_submission_claimed=0
freebsd_bugzilla_pr_claimed=0
freebsd_committer_review_claimed=0
poudriere_build_run=0
make_package_run=0
portlint_run=0
package_artifact_created=0
freebsd_official_port_claimed=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
bin/latticra
%%DOCSDIR%%/README.md
```

The CLI reports no-effect status and disabled runtime behavior.
