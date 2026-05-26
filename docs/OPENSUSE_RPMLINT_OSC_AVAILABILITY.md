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

Recommended next slice:

```text
Add openSUSE rpmlint static spec lane for packaging/opensuse/latticra.spec with expected local-only draft findings classified separately.
```

That future lane may run `rpmlint packaging/opensuse/latticra.spec` inside openSUSE and capture expected findings without requiring a clean lint result or promoting the package.

## Validation

Run inside openSUSE:

```sh
sh scripts/test-opensuse-rpmlint-osc-availability.sh
```

Expected output:

```text
opensuse_rpmlint_osc_availability: ok
```
