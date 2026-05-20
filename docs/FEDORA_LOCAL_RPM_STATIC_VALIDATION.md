# Fedora Local RPM Static Validation

Status: active static validation lane
Scope: static checks for the local RPM spec skeleton.

## Purpose

This lane turns the local validation plan into a first executable check.

It checks the current local spec skeleton without building packages, producing artifacts, running mock, or requiring rpmlint output.

## Files

```text
docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
scripts/test-fedora-local-rpm-static-validation.sh
.github/workflows/fedora-local-rpm-static-validation.yml
```

## Checks

The static validation lane verifies:

```text
spec skeleton guard passes
validation plan guard passes
local-only draft marker exists
placeholder license remains explicit
local release marker remains explicit
required RPM sections exist
spec does not install binaries yet
spec does not define scriptlet sections yet
spec does not add service files yet
```

## Boundary

This lane is static validation only.

It does not run `rpmbuild`, `rpmlint`, or `mock`.

It does not create package artifacts.

## Next slice

Recommended next slice:

```text
Add rpmlint availability lane
```

That future lane should only check tool availability and static lint readiness before any source or binary package build is attempted.

## Validation

Run:

```sh
sh scripts/test-fedora-local-rpm-static-validation.sh
```

Expected output:

```text
fedora_local_rpm_static_validation: ok
```
