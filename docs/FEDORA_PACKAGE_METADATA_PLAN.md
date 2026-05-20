# Fedora Package Metadata Plan

Status: planning record
Scope: metadata required before a Fedora-oriented package draft exists.

## Purpose

This plan defines the package metadata Latticra should collect before adding any RPM spec file.

The goal is to keep Fedora-facing work disciplined:

```text
build lane first
local developer workflow second
metadata plan third
spec draft later
```

## Current prerequisites

The following Fedora-facing records already exist:

```text
docs/FEDORA_READINESS_PLAN.md
docs/FEDORA_DEVELOPER_WORKFLOW.md
scripts/test-fedora-build-lane.sh
```

## Required metadata fields

A later package draft should define:

```text
package_name
summary
description
upstream_url
source_archive_policy
version_source
license_expression
license_files
build_requires
runtime_requires
installed_binaries
installed_docs
installed_license_files
changelog_policy
```

## Initial proposed values

Initial planning values:

```text
package_name=latticra
summary=Contract-first systems architecture and language project
description_scope=development and evidence tooling
upstream_url=https://github.com/Bryforge/Latticra
source_archive_policy=tagged upstream source archive only
version_source=upstream tag
license_expression=to-be-confirmed-before-spec
license_files=LICENSE plus reviewed file-level notices
build_requires=gcc, make
runtime_requires=none-confirmed-yet
installed_binaries=none-confirmed-yet
installed_docs=docs selected after review
installed_license_files=license files selected after audit
changelog_policy=derive from reviewed release notes
```

## License checkpoint

Before a package draft exists, resolve:

```text
root license state
file-level SPDX state
AGPL transition status
legacy Apache-2.0 files
documentation license decision
third-party material inventory
```

This must stay aligned with:

```text
docs/LICENSE_MIGRATION_PLAN.md
docs/OPEN_ECOSYSTEM_POLICY.md
```

## Packaging boundary

This plan does not add a spec file.

It only defines the metadata that a later spec file would need.

## Spec draft gate

Do not add `packaging/fedora/latticra.spec` until these are true:

```text
Fedora build lane is green
metadata plan is guarded
license expression is decided
source archive policy is decided
installed file list is known
```

## Next slice

Recommended next slice after this plan:

```text
Add local RPM spec draft plan
```

That should still be planning-only unless the metadata checklist is complete.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-package-metadata-plan.sh
```

Expected output:

```text
fedora_package_metadata_plan: ok
```
