# openSUSE Source Archive Reproducibility Contract

Status: active source archive reproducibility contract
Scope: define the evidence required before an openSUSE source archive can be accepted for package build evidence.

## Purpose

This contract defines the source archive evidence required before Latticra accepts any openSUSE package build transcript.

The current goal is conservative: record the expected `Source0` archive shape, reproducibility requirements, transcript fields, and promotion blockers without creating an archive or running a package build.

This contract sits after the `rpmlint` findings classification record and before the source archive fixture, `rpmbuild`, `osc build`, or Open Build Service publication evidence.

## Current Spec Inputs

The current local-only openSUSE spec declares:

```text
Name:           latticra
Version:        0.0.0
Source0:        %{name}-%{version}.tar.gz
%autosetup -n %{name}-%{version}
```

For the current draft, the expected source archive shape is:

```text
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_matches_source0=1
source_archive_matches_autosetup_root=1
```

## Required Future Evidence

A future accepted source archive transcript must record:

```text
source_tree_revision
source_archive_command
source_archive_name
source_archive_root
source_archive_size_bytes
source_archive_sha256
source_archive_entry_count
source_archive_generated_twice
source_archive_repeated_sha256_match
source_archive_contains_spec
source_archive_contains_changes
source_archive_contains_readme
source_archive_excludes_git_dir
source_archive_excludes_nested_archives
source_archive_excludes_build_outputs
source_archive_excludes_rpm_artifacts
source_archive_symlink_policy_checked
source_archive_path_safety_checked
```

## Acceptance Rule

An openSUSE source archive remains unaccepted unless all of these are true:

```text
source_archive_transcript_present=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_sha256_recorded=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_excludes_git_dir=1
source_archive_excludes_nested_archives=1
source_archive_excludes_build_outputs=1
source_archive_excludes_rpm_artifacts=1
source_archive_symlink_policy_checked=1
source_archive_path_safety_checked=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
```

Until those conditions are met, source archive evidence is a review input only, not package build readiness.

## Current Baseline

The current baseline includes the follow-on temporary fixture lane. The archive remains unaccepted for package build input until the remaining acceptance requirements are met.

```text
opensuse_source_archive_reproducibility_contract_present=1
opensuse_rpmlint_findings_classification_present=1
opensuse_source_archive_fixture_lane_present=1
opensuse_rpm_topdir_handoff_lane_present=1
opensuse_local_rpm_build_gate_contract_present=1
opensuse_local_rpm_build_environment_contract_present=1
opensuse_rpm_artifact_naming_contract_present=1
opensuse_rpm_payload_inspection_contract_present=1
opensuse_rpm_install_remove_transcript_contract_present=1
source_archive_policy_recorded=1
source_archive_name_expected=latticra-0.0.0.tar.gz
source_archive_root_expected=latticra-0.0.0/
source_archive_matches_source0_required=1
source_archive_matches_autosetup_required=1
source_archive_transcript_present=1
source_archive_created=1
source_archive_sha256_recorded=1
source_archive_reproducible=1
source_archive_accepted_for_build=0
rpmbuild_run=0
osc_build_run=0
rpm_artifact_created=0
obs_publication_claimed=0
package_readiness_claimed=0
```

## Boundary

This contract does not:

```text
create a source archive
run tar
run gzip
run rpmbuild
run osc build
run spec-cleaner
create source RPM artifacts
create binary RPM artifacts
publish to Open Build Service
submit Latticra to openSUSE
install Latticra on a host
claim official openSUSE package status
claim SUSE endorsement
claim production readiness
```

## Follow-On Handoff Lane

Completed follow-on fixture and handoff lanes:

```text
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
scripts/test-opensuse-source-archive-fixture-lane.sh
scripts/test-opensuse-rpm-topdir-handoff-lane.sh
scripts/test-opensuse-local-rpm-build-gate-contract.sh
scripts/test-opensuse-local-rpm-build-environment-contract.sh
scripts/test-opensuse-rpm-artifact-naming-contract.sh
scripts/test-opensuse-rpm-payload-inspection-contract.sh
scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
.github/workflows/opensuse-source-archive-fixture-lane.yml
.github/workflows/opensuse-rpm-topdir-handoff-lane.yml
.github/workflows/opensuse-local-rpm-build-gate-contract.yml
.github/workflows/opensuse-local-rpm-build-environment-contract.yml
.github/workflows/opensuse-rpm-artifact-naming-contract.yml
.github/workflows/opensuse-rpm-payload-inspection-contract.yml
.github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
.github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
```

Those lanes prove archive shape, reproducibility, temporary RPM topdir staging, build-gate closure, environment requirements, future artifact naming boundaries, payload inspection evidence requirements, install/remove transcript requirements, and OBS non-claim review while keeping package build and publication claims blocked.

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial contract before any local build lane can open.
```

## Validation

Run:

```sh
sh scripts/test-opensuse-source-archive-reproducibility-contract.sh
```

Expected output:

```text
opensuse_source_archive_reproducibility_contract: ok
```
