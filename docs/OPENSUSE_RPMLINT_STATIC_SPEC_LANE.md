# openSUSE rpmlint Static Spec Lane

Status: active static spec lint lane
Scope: run `rpmlint` against the local-only openSUSE spec draft and capture findings without promoting package-readiness claims.

## Purpose

This lane advances the openSUSE local RPM validation stack from tool availability to a static spec lint pass.

The current goal is conservative: prove that `rpmlint` can inspect the local draft spec file in an openSUSE environment and produce a reportable result.

This lane does not require a clean `rpmlint` result yet because the spec remains a local-only draft and still has source-archive and package-readiness metadata to review.

## Files

```text
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
scripts/test-opensuse-rpmlint-static-spec-lane.sh
scripts/test-opensuse-rpmlint-findings-classification.sh
scripts/test-opensuse-source-archive-reproducibility-contract.sh
scripts/test-opensuse-source-archive-fixture-lane.sh
scripts/test-opensuse-rpm-topdir-handoff-lane.sh
scripts/test-opensuse-local-rpm-build-gate-contract.sh
scripts/test-opensuse-local-rpm-build-environment-contract.sh
scripts/test-opensuse-rpm-artifact-naming-contract.sh
scripts/test-opensuse-rpm-payload-inspection-contract.sh
scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
.github/workflows/opensuse-rpmlint-static-spec-lane.yml
.github/workflows/opensuse-rpmlint-findings-classification.yml
.github/workflows/opensuse-source-archive-reproducibility-contract.yml
.github/workflows/opensuse-source-archive-fixture-lane.yml
.github/workflows/opensuse-rpm-topdir-handoff-lane.yml
.github/workflows/opensuse-local-rpm-build-gate-contract.yml
.github/workflows/opensuse-local-rpm-build-environment-contract.yml
.github/workflows/opensuse-rpm-artifact-naming-contract.yml
.github/workflows/opensuse-rpm-payload-inspection-contract.yml
.github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
packaging/opensuse/latticra.spec
```

## Checks

This lane checks:

```text
openSUSE environment marker exists
zypper is available
rpmlint installs
rpmlint command is available
rpmlint can inspect packaging/opensuse/latticra.spec
rpmlint output is captured for audit
previous rpmlint and osc availability lane remains green
```

## Expected Draft Findings

The current local-only spec may still report findings related to draft metadata, including:

```text
local-only release marker
placeholder version
AGPL-3.0-or-later AND CC-BY-4.0 package license expression
missing source archive for a real package build
limited installed file set
openSUSE maintenance metadata still local-only
```

Those findings are expected at this stage and are not package-readiness failures yet.

The purpose of this lane is visibility, not package promotion.

## Boundary

This lane does not run `rpmbuild`.

It does not run `osc build`.

It does not run `spec-cleaner`.

It does not create package artifacts.

It does not create an Open Build Service project, publish to Open Build Service, submit Latticra to openSUSE, install on a host, or claim package readiness.

It does not claim official openSUSE package status, SUSE endorsement, product readiness, operating-system readiness, runtime authority, kernel authority, or security-hardening completion.

## Next Slice

Completed follow-on classification lane:

```text
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
scripts/test-opensuse-rpmlint-findings-classification.sh
.github/workflows/opensuse-rpmlint-findings-classification.yml
```

Completed follow-on source archive lanes:

```text
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
scripts/test-opensuse-source-archive-reproducibility-contract.sh
scripts/test-opensuse-source-archive-fixture-lane.sh
scripts/test-opensuse-rpm-topdir-handoff-lane.sh
scripts/test-opensuse-local-rpm-build-gate-contract.sh
scripts/test-opensuse-local-rpm-build-environment-contract.sh
scripts/test-opensuse-rpm-artifact-naming-contract.sh
scripts/test-opensuse-rpm-payload-inspection-contract.sh
scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
.github/workflows/opensuse-source-archive-reproducibility-contract.yml
.github/workflows/opensuse-source-archive-fixture-lane.yml
.github/workflows/opensuse-rpm-topdir-handoff-lane.yml
.github/workflows/opensuse-local-rpm-build-gate-contract.yml
.github/workflows/opensuse-local-rpm-build-environment-contract.yml
.github/workflows/opensuse-rpm-artifact-naming-contract.yml
.github/workflows/opensuse-rpm-payload-inspection-contract.yml
.github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
```

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial contract before any local build lane can open.
```

That future lane should define how build evidence intake is refused until the blocker matrix opens, while keeping RPM builds and readiness blocked.

## Validation

Run inside openSUSE:

```sh
sh scripts/test-opensuse-rpmlint-static-spec-lane.sh
```

Expected output:

```text
opensuse_rpmlint_static_spec_lane: ok
```
