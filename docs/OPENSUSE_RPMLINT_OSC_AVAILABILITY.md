# openSUSE rpmlint and osc Availability Lane

Status: active tool availability lane
Scope: verify that `rpmlint` and `osc` are available in an openSUSE Linux environment.

## Purpose

This lane prepares the next openSUSE packaging validation step without linting, building, publishing, or installing the Latticra package draft.

The current goal is only to prove that `rpmlint` and `osc` can be installed and invoked inside the openSUSE compatibility environment.

## Files

```text
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
scripts/test-opensuse-rpmlint-osc-availability.sh
.github/workflows/opensuse-rpmlint-osc-availability.yml
```

## Checks

This lane checks:

```text
openSUSE environment marker exists
zypper is available
rpmlint installs
rpmlint command is available
rpmlint invocation probe can run
osc installs
osc command is available
osc invocation probe can run
local openSUSE RPM static validation lane remains green
```

## Boundary

This lane does not lint the Latticra openSUSE spec yet.

It does not run `rpmbuild`, `osc build`, `spec-cleaner`, or `zypper install` against a Latticra artifact.

It does not create package artifacts, create an Open Build Service project, publish to Open Build Service, submit Latticra to openSUSE, install on a host, or claim package readiness.

## Next Slice

Completed follow-on static spec lane:

```text
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
scripts/test-opensuse-rpmlint-static-spec-lane.sh
scripts/test-opensuse-rpmlint-findings-classification.sh
.github/workflows/opensuse-rpmlint-static-spec-lane.yml
.github/workflows/opensuse-rpmlint-findings-classification.yml
```

Recommended next slice:

```text
Add openSUSE rpmlint findings classification report.
```

That future lane may classify expected local-only draft findings separately from unexpected spec findings while keeping the package local-only.

## Validation

Run inside openSUSE:

```sh
sh scripts/test-opensuse-rpmlint-osc-availability.sh
```

Expected output:

```text
opensuse_rpmlint_osc_availability: ok
```
