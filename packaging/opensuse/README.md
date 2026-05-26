# openSUSE Packaging Draft

Status: local-only packaging draft

This directory contains openSUSE-oriented packaging experiments and maintenance records for Latticra.

The current spec and `.changes` metadata are a local-only draft used by static guards. They are not an official openSUSE package, not SUSE endorsement evidence, not Open Build Service publication evidence, not a submit-request record, not a local `osc build` result, not a `rpmlint` result, and not package-readiness evidence.

Current guarded files:

```text
packaging/opensuse/README.md
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
docs/OPENSUSE_READINESS_PLAN.md
docs/OPENSUSE_DEVELOPER_WORKFLOW.md
docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-opensuse-developer-workflow.sh
scripts/test-opensuse-local-rpm-static-validation.sh
scripts/test-opensuse-rpmlint-osc-availability.sh
.github/workflows/opensuse-developer-workflow.yml
.github/workflows/opensuse-local-rpm-static-validation.yml
.github/workflows/opensuse-rpmlint-osc-availability.yml
```

The static lane preserves:

```text
local_only_draft=1
opensuse_maintenance_lane_present=1
opensuse_rpmlint_osc_availability_lane_present=1
rpm_artifact_created=0
rpmbuild_run_required=0
osc_build_run=0
rpmlint_run=0
spec_cleaner_run=0
opensuse_obs_publication_claimed=0
opensuse_official_package_claimed=0
suse_endorsement_claimed=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
/usr/bin/latticra
/usr/share/doc/packages/latticra/README.md
```

The CLI reports no-effect status and disabled runtime behavior.

The `.changes` file records local-only openSUSE maintenance history. It is not accepted Open Build Service history, package submission evidence, or production maintenance evidence.
