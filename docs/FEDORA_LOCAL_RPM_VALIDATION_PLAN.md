# Fedora Local RPM Validation Plan

Status: planning record
Scope: local validation steps for the Latticra RPM draft skeleton.

## Purpose

This plan defines the validation path before the local RPM skeleton is allowed to become a real build lane.

The goal is to make package validation repeatable while keeping the current RPM spec clearly local-only.

## Current prerequisites

The following records and files should already exist:

```text
docs/FEDORA_READINESS_PLAN.md
docs/FEDORA_PACKAGE_METADATA_PLAN.md
docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
packaging/fedora/latticra.spec
scripts/test-fedora-local-rpm-spec-skeleton.sh
```

## Validation stages

Recommended validation order:

```text
1. Static spec skeleton guard
2. Fedora container guard
3. rpmlint availability check
4. source archive policy check
5. source RPM dry-run plan
6. local mock build plan
7. installed file inspection plan
```

## Static validation

The static guard should continue checking:

```text
local-only draft marker
Name field
Version field
Release field
Summary field
License placeholder
URL field
Source0 placeholder
BuildRequires fields
required RPM sections
current guard commands
```

## rpmlint plan

A later implementation lane may install and run:

```sh
rpmlint packaging/fedora/latticra.spec
```

This plan does not require rpmlint output yet.

## Source RPM plan

A later implementation lane may create a temporary source archive and run a source RPM build dry run.

Required unresolved decisions before that lane:

```text
version tag policy
source archive naming
license expression
license files
installed file list
```

## Mock build plan

A later implementation lane may run a local mock build only after the source RPM lane is stable.

Mock validation should record:

```text
mock config used
source RPM path
build result
logs location
known failures
```

## Installed file inspection plan

After a local binary RPM exists, inspect:

```text
installed docs
installed license files
installed binaries
file ownership
file permissions
uninstall behavior
```

## Boundary

This is a validation plan only.

It does not run rpmbuild, rpmlint, or mock. It does not produce RPM artifacts.

## Next slice

Recommended next slice after this plan:

```text
Add local RPM static validation lane
```

That future slice should extend the current static spec skeleton guard without creating package artifacts.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-local-rpm-validation-plan.sh
```

Expected output:

```text
fedora_local_rpm_validation_plan: ok
```
