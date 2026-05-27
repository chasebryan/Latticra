# openSUSE RPM Topdir Handoff Lane

Status: active temporary RPM topdir handoff lane
Scope: stage the verified temporary openSUSE source archive into a disposable RPM topdir without running package builds, installing artifacts, or publishing to Open Build Service.

## Purpose

This lane advances the openSUSE packaging path from source archive fixture evidence into RPM build-input staging.

The goal is conservative: prove that the temporary `Source0` archive can be placed under `SOURCES/`, the local-only spec can be placed under `SPECS/`, and the staged archive keeps the same checksum and listing as the verified fixture.

This lane does not build a source RPM or binary RPM. It stages temporary RPM build inputs only.

## Temporary RPM Topdir Layout

The handoff creates this layout under a disposable temporary directory:

```text
rpmtop/BUILD/
rpmtop/BUILDROOT/
rpmtop/RPMS/
rpmtop/SOURCES/latticra-0.0.0.tar.gz
rpmtop/SPECS/latticra.spec
rpmtop/SPECS/latticra.changes
rpmtop/SRPMS/
```

The staged source archive name must match the resolved openSUSE spec inputs:

```text
Source0:        %{name}-%{version}.tar.gz
%autosetup -n %{name}-%{version}
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
```

## Handoff Checks

The lane verifies:

```text
opensuse_rpm_topdir_handoff_lane_present=1
opensuse_source_archive_fixture_lane_present=1
temporary_rpm_topdir_handoff_lane_present=1
temporary_rpm_topdir_created=1
temporary_rpm_sources_archive_staged=1
temporary_rpm_specs_spec_staged=1
temporary_rpm_specs_changes_staged=1
temporary_rpm_source_sha256_preserved=1
temporary_rpm_source_listing_preserved=1
temporary_rpm_source0_name_matched=1
temporary_rpm_autosetup_root_matched=1
rpm_build_dirs_created=1
source_archive_accepted_for_build=0
rpmbuild_run=0
osc_build_run=0
rpm_artifact_created=0
```

The handoff evidence is temporary package-input staging only. It does not promote the archive to accepted package-build input.

## Boundary

This lane does not run `rpmbuild`.

It does not run `osc build`.

It does not run `rpmlint`.

It does not run `spec-cleaner`.

It does not create source RPM artifacts.

It does not create binary RPM artifacts.

It does not install Latticra.

It does not publish package artifacts.

It does not create an Open Build Service project.

It does not submit Latticra to openSUSE.

It does not claim official openSUSE package status, SUSE endorsement, Open Build Service publication, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, policy readiness, or security-hardening completion.

## Next Slice

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

Completed follow-on OBS publication non-claim review contract:

```text
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
.github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
```

Recommended next slice:

```text
Add openSUSE RPM validation promotion blocker matrix before any package validation result can be accepted.
```

That future lane should tie source, environment, artifact, payload, install/remove, and OBS non-claim records together while keeping RPM builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-opensuse-rpm-topdir-handoff-lane.sh
```

Expected output:

```text
opensuse_rpm_topdir_handoff_lane: ok
```
