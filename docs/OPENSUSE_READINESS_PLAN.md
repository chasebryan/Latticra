# openSUSE Readiness Plan

Status: planning and maintenance record
Scope: preparing Latticra for openSUSE-friendly development, local validation, local-only RPM packaging, and maintenance review.

## Purpose

This plan gives the openSUSE track the same purpose as the Fedora and Ubuntu tracks: integrate Latticra with a real Linux ecosystem through bounded local validation, packaging-shape records, and maintenance evidence while preserving current non-claims.

This plan prepares Latticra for an openSUSE-facing path without claiming openSUSE acceptance, SUSE endorsement, Open Build Service publication, production installer readiness, or distribution status.

The near-term target is:

```text
Latticra builds cleanly on openSUSE after operator-installed prerequisites.
Latticra Panel can be run from source on openSUSE with documented zypper prerequisites.
Latticra has a local-only openSUSE RPM packaging draft for the no-effect CLI payload.
Latticra records openSUSE maintenance boundaries separately from Fedora and Ubuntu package lanes.
Latticra preserves its current non-claims.
```

## Terminology Boundary

Use:

```text
openSUSE readiness
openSUSE compatibility lane
openSUSE maintenance lane
local-only openSUSE RPM draft
Latticra on openSUSE
future Open Build Service review candidate
```

Avoid claiming:

```text
official openSUSE package
published Open Build Service package
SUSE endorsement
openSUSE derivative
openSUSE distribution
operating-system replacement
```

Those terms require separate package review, Open Build Service evidence, policy review, legal review, trademark review, and community review.

## openSUSE-Facing Requirements To Respect

Before Latticra can be proposed beyond a local RPM draft, it should be checked against openSUSE package and maintenance expectations:

```text
spec file hygiene
.changes maintenance record
license expression review
BuildRequires completeness
no bundled system libraries
valid file ownership
valid permissions
rpmlint output classification
spec-cleaner review where appropriate
osc local build evidence
Open Build Service project metadata review
install/remove behavior evidence
```

## Current Latticra Posture

Current Latticra evidence is still early-stage and report-oriented.

Known current posture:

```text
opensuse_developer_workflow_present=1
opensuse_panel_prerequisites_documented=1
opensuse_local_rpm_draft_present=1
opensuse_local_rpm_static_validation_present=1
opensuse_changes_file_present=1
opensuse_rpmlint_osc_availability_lane_present=1
opensuse_obs_publication_claimed=0
opensuse_official_package_claimed=0
suse_endorsement_claimed=0
opensuse_distribution_ready=0
production_installer_ready=0
daily_driver_install_ready=0
root_installer_ready=0
```

The first openSUSE target is development, local validation, and package-maintenance shape. It is not an official openSUSE package, Open Build Service publication, image, distribution, or replacement operating system.

## Phase 1: openSUSE Developer Workflow

The openSUSE developer workflow gives local zypper commands for toolchain setup, Panel prerequisites, and the same guarded no-effect validation loop used by the other Linux tracks.

Current guarded files:

```text
docs/OPENSUSE_DEVELOPER_WORKFLOW.md
scripts/test-opensuse-developer-workflow.sh
.github/workflows/opensuse-developer-workflow.yml
```

## Phase 2: Panel Prerequisites Lane

The Panel remains user-local on openSUSE. The zypper prerequisites support local Rust/egui development and desktop metadata refresh without adding root-installed Latticra services.

Current public entry points:

```text
README.md
docs/QUICK_START_CHEATSHEET.md
installer/README.md
```

## Phase 3: Local openSUSE RPM Draft Lane

Packaging metadata is present as a local-only openSUSE draft. It records package shape, a separate maintenance changes file, and static validation boundaries.

Current guarded files:

```text
packaging/opensuse/README.md
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
scripts/test-opensuse-local-rpm-static-validation.sh
.github/workflows/opensuse-local-rpm-static-validation.yml
```

The first openSUSE RPM draft is only a packaging-shape and maintenance record until lint/build/install evidence is added.

## Phase 4: Open Build Service Readiness Lane

The first Open Build Service readiness slice is tool availability only.

Current guarded files:

```text
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
scripts/test-opensuse-rpmlint-osc-availability.sh
.github/workflows/opensuse-rpmlint-osc-availability.yml
```

Before any Open Build Service publication or submit request can be claimed, the lane needs evidence for:

```text
osc availability
rpmlint availability
spec-cleaner review posture
local osc build transcript
source archive reproducibility
package artifact inspection
install/remove behavior transcript
```

## Non-Claims

This plan does not:

```text
publish an RPM package
create an Open Build Service project
submit Latticra to openSUSE
claim official openSUSE package readiness
claim SUSE endorsement
install a root service
modify systemd
modify the kernel
claim production readiness
claim operating-system completeness
```

## Recommended Next Slice

Recommended next slice:

```text
Add openSUSE rpmlint static spec lane for packaging/opensuse/latticra.spec with expected local-only draft findings classified separately.
```

That should preserve the local-only openSUSE maintenance posture while the package path matures beyond tool availability.

## Validation

Run:

```sh
sh scripts/test-opensuse-developer-workflow.sh
sh scripts/test-opensuse-local-rpm-static-validation.sh
sh scripts/test-opensuse-rpmlint-osc-availability.sh
```

Expected output:

```text
opensuse_developer_workflow: ok
opensuse_local_rpm_static_validation: ok
opensuse_rpmlint_osc_availability: ok
```
