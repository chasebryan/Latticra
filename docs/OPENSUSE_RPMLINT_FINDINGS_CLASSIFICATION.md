# openSUSE rpmlint Findings Classification

Status: active findings classification record
Scope: classify expected and unexpected `rpmlint` findings for the local-only openSUSE spec draft without promoting package-readiness claims.

## Purpose

This record defines how `rpmlint` output from the openSUSE static spec lane should be interpreted while `packaging/opensuse/latticra.spec` remains a local-only draft.

The goal is to separate expected draft findings from findings that must block package promotion.

This record is classification only. It does not require a clean `rpmlint` result, run `rpmbuild`, run `osc build`, create package artifacts, publish to Open Build Service, submit Latticra to openSUSE, install Latticra, or claim package readiness.

## Inputs

The classification applies to:

```text
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
scripts/test-opensuse-rpmlint-static-spec-lane.sh
scripts/test-opensuse-source-archive-reproducibility-contract.sh
scripts/test-opensuse-source-archive-fixture-lane.sh
scripts/test-opensuse-rpm-topdir-handoff-lane.sh
scripts/test-opensuse-local-rpm-build-gate-contract.sh
scripts/test-opensuse-local-rpm-build-environment-contract.sh
scripts/test-opensuse-rpm-artifact-naming-contract.sh
scripts/test-opensuse-rpm-payload-inspection-contract.sh
scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
```

## Expected Draft Finding Classes

These finding classes are expected while the package remains local-only:

```text
placeholder_version_or_release
local_only_release_marker
placeholder_license_expression
missing_real_source_archive
limited_payload_surface
draft_doc_payload_mapping
local_only_changes_record
```

Expected draft findings do not unblock package readiness. They only explain why a local-only draft may produce `rpmlint` output before source archive, license, and maintenance evidence mature.

## Unexpected Finding Classes

These finding classes must be treated as blockers until separately reviewed:

```text
service_installation
systemd_mutation
kernel_module_payload
boot_path_payload
etc_path_payload
privileged_helper_payload
network_fetch_during_build
host_mutation_during_build
unreviewed_scriptlet
unowned_or_unsafe_file_path
license_claim_promotion
opensuse_official_status_claim
obs_publication_claim
suse_endorsement_claim
```

Unexpected findings do not automatically mean the package is unsafe; they mean the local-only draft has crossed a boundary that needs a separate review lane before promotion.

## Classification Output Shape

A future accepted `rpmlint` findings transcript should record:

```text
rpmlint_invocation
rpmlint_exit_status
rpmlint_output_present
expected_draft_findings_count
unexpected_findings_count
package_artifact_created
osc_build_run
obs_publication_claimed
package_readiness_claimed
classification_decision
```

Current classification baseline:

```text
opensuse_rpmlint_findings_classification_present=1
opensuse_rpmlint_static_spec_lane_present=1
expected_draft_finding_classes_recorded=1
unexpected_finding_classes_recorded=1
accepted_rpmlint_transcript_present=0
expected_draft_findings_count_recorded=0
unexpected_findings_count_recorded=0
classification_decision=blocked-pending-reviewed-rpmlint-output
package_artifact_created=0
osc_build_run=0
obs_publication_claimed=0
package_readiness_claimed=0
```

## Promotion Rule

Package promotion remains blocked unless all of these are true:

```text
accepted_rpmlint_transcript_present=1
unexpected_findings_count=0
license_expression_reviewed=1
source_archive_reproducible=1
osc_build_transcript_present=1
install_remove_transcript_present=1
obs_publication_claimed=0
opensuse_official_package_claimed=0
suse_endorsement_claimed=0
```

Until those conditions are met, `rpmlint` output is evidence for maintenance review only, not package readiness.

## Boundary

This record does not:

```text
run rpmlint
run rpmbuild
run osc build
run spec-cleaner
create package artifacts
publish to Open Build Service
submit Latticra to openSUSE
install Latticra on a host
claim official openSUSE package status
claim SUSE endorsement
claim production readiness
```

## Next Slice

Completed follow-on source archive contract:

```text
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
scripts/test-opensuse-source-archive-reproducibility-contract.sh
.github/workflows/opensuse-source-archive-reproducibility-contract.yml
```

Completed follow-on source archive fixture:

```text
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
scripts/test-opensuse-source-archive-fixture-lane.sh
.github/workflows/opensuse-source-archive-fixture-lane.yml
```

Completed follow-on RPM topdir handoff lane:

```text
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
scripts/test-opensuse-rpm-topdir-handoff-lane.sh
.github/workflows/opensuse-rpm-topdir-handoff-lane.yml
```

Completed follow-on local RPM build gate contract:

```text
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
scripts/test-opensuse-local-rpm-build-gate-contract.sh
.github/workflows/opensuse-local-rpm-build-gate-contract.yml
```

Completed follow-on local RPM build environment contract:

```text
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
scripts/test-opensuse-local-rpm-build-environment-contract.sh
.github/workflows/opensuse-local-rpm-build-environment-contract.yml
```

Completed follow-on RPM artifact naming contract:

```text
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
scripts/test-opensuse-rpm-artifact-naming-contract.sh
.github/workflows/opensuse-rpm-artifact-naming-contract.yml
```

Completed follow-on RPM payload inspection contract:

```text
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
scripts/test-opensuse-rpm-payload-inspection-contract.sh
.github/workflows/opensuse-rpm-payload-inspection-contract.yml
```

Completed follow-on RPM install/remove transcript contract:

```text
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
.github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
```

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial contract before any local build lane can open.
```

That future lane should define how build evidence intake is refused until the blocker matrix opens, while keeping RPM builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-opensuse-rpmlint-findings-classification.sh
```

Expected output:

```text
opensuse_rpmlint_findings_classification: ok
```
