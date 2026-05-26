# openSUSE Local RPM Static Validation

Status: active static validation lane
Scope: static checks for the local-only openSUSE RPM packaging draft and maintenance changes file.

## Purpose

This lane turns the openSUSE packaging and maintenance draft into an executable static check.

It checks the current local openSUSE RPM spec and `.changes` record without building packages, producing artifacts, running `osc`, running `rpmlint`, or claiming Open Build Service publication.

## Files

```text
docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
docs/OPENSUSE_READINESS_PLAN.md
docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
packaging/opensuse/README.md
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
scripts/test-opensuse-local-rpm-static-validation.sh
.github/workflows/opensuse-local-rpm-static-validation.yml
```

## Checks

The static validation lane verifies:

```text
local-only openSUSE draft marker exists
local packaging README records non-claims
placeholder license remains explicit
local release marker remains explicit
required RPM sections exist
.changes maintenance record exists
no service files are installed
no scriptlet sections are defined
no boot, kernel, systemd, SELinux, or etc paths are added
no Open Build Service publication claim is made
```

## Boundary

This lane is static validation only.

It does not run `rpmbuild`, `osc build`, `rpmlint`, `spec-cleaner`, or `zypper install`.

It does not create package artifacts, publish to Open Build Service, submit to openSUSE, install on a host, or claim production readiness.

## Next Slice

Completed follow-on availability lane:

```text
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
scripts/test-opensuse-rpmlint-osc-availability.sh
scripts/test-opensuse-rpmlint-static-spec-lane.sh
scripts/test-opensuse-rpmlint-findings-classification.sh
.github/workflows/opensuse-rpmlint-osc-availability.yml
.github/workflows/opensuse-rpmlint-static-spec-lane.yml
.github/workflows/opensuse-rpmlint-findings-classification.yml
```

Recommended next slice:

```text
Add openSUSE source archive reproducibility contract before accepting package build evidence.
```

That future lane should keep source archive, license, and build evidence separate from `rpmlint` output so the openSUSE package path remains reviewable.

## Validation

Run:

```sh
sh scripts/test-opensuse-local-rpm-static-validation.sh
```

Expected output:

```text
opensuse_local_rpm_static_validation: ok
```
