# openSUSE rpmlint Static Spec Lane

Status: active static spec lint lane
Scope: run `rpmlint` against the local-only openSUSE spec draft and capture findings without promoting package-readiness claims.

## Purpose

This lane advances the openSUSE local RPM validation stack from tool availability to a static spec lint pass.

The current goal is conservative: prove that `rpmlint` can inspect the local draft spec file in an openSUSE environment and produce a reportable result.

This lane does not require a clean `rpmlint` result yet because the spec remains a local-only draft and still carries intentionally unresolved package metadata.

## Files

```text
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
scripts/test-opensuse-rpmlint-static-spec-lane.sh
.github/workflows/opensuse-rpmlint-static-spec-lane.yml
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
LicenseRef-Latticra-TBD
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

Recommended next slice:

```text
Add openSUSE rpmlint findings classification record before accepting any lint transcript as package readiness evidence.
```

That future lane should separate expected local-only draft findings from unexpected blockers.

## Validation

Run inside openSUSE:

```sh
sh scripts/test-opensuse-rpmlint-static-spec-lane.sh
```

Expected output:

```text
opensuse_rpmlint_static_spec_lane: ok
```
