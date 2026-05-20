# Fedora Local RPM Spec Draft Plan

Status: planning record
Scope: local-only RPM spec draft preparation before adding a spec file.

## Purpose

This plan defines what must be true before Latticra adds a local RPM spec draft.

The goal is to prepare carefully without creating packaging metadata too early.

Current order:

```text
Fedora readiness plan
Fedora build lane
Fedora developer workflow
Fedora package metadata plan
local RPM spec draft plan
local spec draft later
```

## Current prerequisites

The following records should already exist:

```text
docs/FEDORA_READINESS_PLAN.md
docs/FEDORA_DEVELOPER_WORKFLOW.md
docs/FEDORA_PACKAGE_METADATA_PLAN.md
scripts/test-fedora-build-lane.sh
```

## Draft spec path

The eventual local draft path should be:

```text
packaging/fedora/latticra.spec
```

Do not add that file in this planning slice.

## Spec draft inputs

Before the spec draft exists, collect:

```text
Name
Version
Release
Summary
License
URL
Source0
BuildRequires
Requires
%description
%prep
%build
%install
%files
%changelog
```

## Initial package intent

The first local spec draft should target development and evidence tooling only.

It should not install or claim:

```text
bootable system image
kernel replacement
runtime service
daemon
hardware authority
Fedora derivative
```

## Build command posture

The first draft should prefer existing guard scripts instead of inventing a new build system.

Initial candidate build/check commands:

```sh
sh scripts/test-fedora-build-lane.sh
sh scripts/test-kernel-lifecycle-report-runner.sh
sh scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
```

## File installation posture

The first local spec draft should install only reviewed artifacts.

Candidate install groups:

```text
license files
selected docs
optional report tools only after install path is reviewed
```

No install path is approved by this plan.

## License gate

Do not write the spec License field until the license expression is reviewed.

Required checks:

```text
root license state reviewed
file-level SPDX state reviewed
AGPL migration status reviewed
legacy Apache-2.0 paths reviewed
documentation license decision reviewed
```

## Local-only boundary

The future spec draft should be local-only until lint and local build validation are added.

This plan does not submit, publish, or claim package readiness.

## Next slice

Recommended next slice after this plan:

```text
Add local RPM spec draft skeleton
```

That future slice may add `packaging/fedora/latticra.spec` only if it is explicitly marked local-only and guarded by a static spec check.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-local-rpm-spec-draft-plan.sh
```

Expected output:

```text
fedora_local_rpm_spec_draft_plan: ok
```
