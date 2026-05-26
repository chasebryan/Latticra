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
opensuse_source_archive_reproducibility_contract_present=1
opensuse_source_archive_fixture_lane_present=1
opensuse_rpm_topdir_handoff_lane_present=1
temporary_rpm_topdir_handoff_lane_present=1
rpm_artifact_created=0
rpm_installed_on_host=0
osc_build_run=0
accepted_rpmlint_transcript_present=0
expected_draft_findings_count_recorded=0
unexpected_findings_count_recorded=0
classification_decision=blocked-pending-reviewed-rpmlint-output
source_archive_policy_recorded=1
source_archive_transcript_present=1
source_archive_created=1
source_archive_sha256_recorded=1
source_archive_reproducible=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_accepted_for_build=0
temporary_rpm_topdir_created=1
temporary_rpm_sources_archive_staged=1
temporary_rpm_specs_spec_staged=1
temporary_rpm_specs_changes_staged=1
temporary_rpm_source_sha256_preserved=1
temporary_rpm_source_listing_preserved=1
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
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
packaging/opensuse/README.md
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
scripts/test-opensuse-developer-workflow.sh
scripts/test-opensuse-local-rpm-static-validation.sh
scripts/test-opensuse-rpmlint-osc-availability.sh
scripts/test-opensuse-rpmlint-static-spec-lane.sh
scripts/test-opensuse-rpmlint-findings-classification.sh
scripts/test-opensuse-source-archive-reproducibility-contract.sh
scripts/test-opensuse-source-archive-fixture-lane.sh
scripts/test-opensuse-rpm-topdir-handoff-lane.sh
.github/workflows/opensuse-developer-workflow.yml
.github/workflows/opensuse-local-rpm-static-validation.yml
.github/workflows/opensuse-rpmlint-osc-availability.yml
.github/workflows/opensuse-rpmlint-static-spec-lane.yml
.github/workflows/opensuse-rpmlint-findings-classification.yml
.github/workflows/opensuse-source-archive-reproducibility-contract.yml
.github/workflows/opensuse-source-archive-fixture-lane.yml
.github/workflows/opensuse-rpm-topdir-handoff-lane.yml
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

The openSUSE source archive reproducibility contract records the expected `Source0` archive shape and evidence required before any package build transcript can be accepted.

The openSUSE source archive fixture lane creates two temporary archive fixtures, compares their SHA-256 values, and inspects the archive listing. It does not create persistent source RPM or binary RPM artifacts, run `rpmbuild`, run `osc build`, publish to Open Build Service, or claim package readiness.

The openSUSE RPM topdir handoff lane stages the verified temporary source archive and local-only spec files into a disposable RPM topdir. It does not run `rpmbuild`, run `osc build`, create source RPM or binary RPM artifacts, publish to Open Build Service, or claim package readiness.

## Next Recommended Lane

```text
Add openSUSE local RPM build evidence gate contract before any rpmbuild or osc build command can run.
```
