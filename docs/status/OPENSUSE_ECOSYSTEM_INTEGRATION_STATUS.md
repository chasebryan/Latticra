# openSUSE Ecosystem Integration Status

Status: openSUSE integration and maintenance status record
Date: 2026-05-26

## Summary

Latticra now has an openSUSE-facing compatibility and maintenance lane for development, Panel prerequisites, and a local-only RPM packaging draft.

This track has the same purpose as the Fedora and Ubuntu tracks, except its scope is openSUSE integration and maintenance.

This is an ecosystem integration checkpoint, not a production readiness claim.

## Current Evidence

```text
opensuse_developer_workflow_present=1
opensuse_panel_prerequisites_documented=1
opensuse_quickstart_documented=1
opensuse_local_rpm_draft_present=1
opensuse_local_rpm_static_validation_present=1
opensuse_changes_file_present=1
opensuse_maintenance_lane_present=1
opensuse_rpmlint_osc_availability_lane_present=1
opensuse_rpmlint_static_spec_lane_present=1
opensuse_rpmlint_findings_classification_present=1
rpm_artifact_created=0
rpm_installed_on_host=0
osc_build_run=0
accepted_rpmlint_transcript_present=0
expected_draft_findings_count_recorded=0
unexpected_findings_count_recorded=0
classification_decision=blocked-pending-reviewed-rpmlint-output
spec_cleaner_run=0
rpmlint_package_readiness_claimed=0
opensuse_obs_publication_claimed=0
opensuse_official_package_claimed=0
suse_endorsement_claimed=0
opensuse_distribution_ready=0
production_installer_ready=0
daily_driver_install_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/OPENSUSE_READINESS_PLAN.md
docs/OPENSUSE_DEVELOPER_WORKFLOW.md
docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
packaging/opensuse/README.md
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
scripts/test-opensuse-developer-workflow.sh
scripts/test-opensuse-local-rpm-static-validation.sh
scripts/test-opensuse-rpmlint-osc-availability.sh
scripts/test-opensuse-rpmlint-static-spec-lane.sh
scripts/test-opensuse-rpmlint-findings-classification.sh
.github/workflows/opensuse-developer-workflow.yml
.github/workflows/opensuse-local-rpm-static-validation.yml
.github/workflows/opensuse-rpmlint-osc-availability.yml
.github/workflows/opensuse-rpmlint-static-spec-lane.yml
.github/workflows/opensuse-rpmlint-findings-classification.yml
```

## Public Entry Points

openSUSE setup and package posture are linked from:

```text
README.md
docs/QUICK_START_CHEATSHEET.md
installer/README.md
docs/status/README.md
```

## Current Boundary

The openSUSE lane does not publish an RPM, create an Open Build Service project, submit Latticra to openSUSE, claim official package readiness, claim SUSE endorsement, install a root service, change systemd, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local openSUSE RPM draft records package shape and maintenance posture only. The `.changes` file is a local maintenance record, not accepted Open Build Service submit-request history.

The openSUSE `rpmlint` and `osc` availability lane verifies tooling in an openSUSE environment only. It does not run `rpmlint` against the Latticra spec yet, run `osc build`, create package artifacts, publish to Open Build Service, or install Latticra on a host.

The openSUSE `rpmlint` static spec lane runs `rpmlint` against the local-only openSUSE spec for audit output only. It does not require a clean lint result, create package artifacts, run `osc build`, publish to Open Build Service, install Latticra, or claim package readiness.

The openSUSE `rpmlint` findings classification record separates expected local-only draft findings from unexpected blockers. It does not accept a transcript, clear findings, create artifacts, or promote package readiness.

## Next Recommended Lane

```text
Add openSUSE source archive reproducibility contract before accepting package build evidence.
```
