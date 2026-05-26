# Fedora rpmlint Static Spec Lane

Status: active static spec lint lane
Scope: run rpmlint against the local-only Fedora spec draft and capture findings without promoting package-readiness claims.

## Purpose

This lane advances the Fedora local RPM validation stack from tool availability to a static spec lint pass.

The current goal is conservative: prove that `rpmlint` can inspect the local draft spec file in a Fedora environment and produce a reportable result.

This lane does not require a clean rpmlint result yet because the spec remains a local-only draft and still has source-archive and package-readiness metadata to review.

## Files

```text
docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
scripts/test-fedora-rpmlint-static-spec-lane.sh
.github/workflows/fedora-rpmlint-static-spec-lane.yml
packaging/fedora/latticra.spec
```

## Checks

This lane checks:

```text
Fedora environment marker exists
dnf is available
rpmlint installs
rpmlint command is available
rpmlint can inspect packaging/fedora/latticra.spec
rpmlint output is captured for audit
previous rpmlint availability lane remains green
```

## Expected draft findings

The current local-only spec may still report findings related to draft metadata, including:

```text
local-only release marker
placeholder version
AGPL-3.0-or-later AND CC-BY-4.0 package license expression
missing source archive for a real package build
limited installed file set
```

Those findings are expected at this stage and are not package-readiness failures yet.

The purpose of this lane is visibility, not package promotion.

## Boundary

This lane does not run `rpmbuild`.

It does not run `mock`.

It does not create package artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add rpmlint findings classification report
```

That future lane may classify expected draft findings separately from unexpected spec findings while keeping the package local-only.

## Validation

Run inside Fedora:

```sh
sh scripts/test-fedora-rpmlint-static-spec-lane.sh
```

Expected output:

```text
fedora_rpmlint_static_spec_lane: ok
```
