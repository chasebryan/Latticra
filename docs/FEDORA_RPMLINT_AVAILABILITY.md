# Fedora rpmlint Availability Lane

Status: active tool availability lane
Scope: verify that rpmlint is available in a Fedora Linux environment.

## Purpose

This lane prepares the next packaging validation step without linting the package draft yet.

The current goal is only to prove that `rpmlint` can be installed and invoked inside the Fedora compatibility environment.

## Files

```text
docs/FEDORA_RPMLINT_AVAILABILITY.md
scripts/test-fedora-rpmlint-availability.sh
.github/workflows/fedora-rpmlint-availability.yml
```

## Checks

This lane checks:

```text
Fedora environment marker exists
dnf is available
rpmlint installs
rpmlint command is available
rpmlint version command can run
static RPM validation lane remains green
```

## Boundary

This lane does not lint the Latticra spec yet.

It does not run rpmbuild or mock.

It does not create package artifacts.

## Next slice

Recommended next slice:

```text
Add rpmlint static spec lane
```

That future lane may run `rpmlint packaging/fedora/latticra.spec` and capture expected local-only draft findings.

## Validation

Run inside Fedora:

```sh
sh scripts/test-fedora-rpmlint-availability.sh
```

Expected output:

```text
fedora_rpmlint_availability: ok
```
