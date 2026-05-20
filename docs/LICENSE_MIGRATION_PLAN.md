# Latticra License Migration Plan

Status: active migration planning record
Scope: path-by-path transition planning after the open ecosystem policy.

## Purpose

This plan defines how Latticra should move from a repository-wide Apache-2.0 default toward the open ecosystem direction without silently relicensing files.

The goal is to keep Latticra open, auditable, transparent, and community-improvable while preserving a clear legal trail for each migration step.

## Current state

Current canonical root license text:

```text
LICENSE: Apache-2.0
```

Current policy direction:

```text
new software work: AGPL-3.0-or-later
existing files: current license until intentionally migrated
branding: separate trademark and identity policy
```

Related records:

```text
docs/OPEN_ECOSYSTEM_POLICY.md
docs/LICENSE_POLICY.md
CONTRIBUTING.md
TRADEMARK_POLICY.md
LICENSES/README.md
```

## Migration principles

Migration must be:

```text
explicit
path-scoped
reviewed
SPDX-marked
compatible with contributor rights
recorded before release
```

No file should be relicensed silently.

## Phase 1: governance baseline

Status: complete

Scope:

```text
docs/OPEN_ECOSYSTEM_POLICY.md
docs/LICENSE_POLICY.md
CONTRIBUTING.md
TRADEMARK_POLICY.md
LICENSES/README.md
scripts/test-open-ecosystem-policy.sh
.github/workflows/open-ecosystem-policy.yml
```

Purpose:

```text
declare open ecosystem direction
preserve existing license state
add contribution and identity policy
add governance guard
```

## Phase 2: SPDX planning guard

Status: this plan

Scope:

```text
docs/LICENSE_MIGRATION_PLAN.md
scripts/test-license-migration-plan.sh
.github/workflows/license-migration-plan.yml
```

Purpose:

```text
record migration phases
require new-source SPDX direction to stay discoverable
define first migration candidate paths
avoid accidental whole-repository relicensing
```

## Phase 3: first source SPDX migration candidates

Recommended first candidate group:

```text
include/latticra/kernel*.h
src/kernel*.c
tests/kernel*.c
tools/kernel*.c
```

Reason:

```text
These files are kernel/core oriented and closely match the open ecosystem reciprocal direction.
```

The first source migration PR should:

```text
1. add SPDX-License-Identifier headers;
2. document affected paths;
3. update or add a guard for SPDX coverage;
4. avoid mixing license migration with behavior changes;
5. preserve existing code behavior and tests.
```

## Phase 4: system/bootstrap/core source candidates

Recommended second candidate group:

```text
include/latticra/system_bootstrap.h
src/system_bootstrap.c
tests/system_bootstrap.c
tools/system_bootstrap_report.c
```

Reason:

```text
These files are core system surfaces and should be reviewed after kernel/core paths.
```

## Phase 5: non-core path review

Review separately:

```text
Lat language tooling
L-UI tooling
LIR tooling
runtime-boundary support
scripts
examples
fixtures
documentation
assets
```

Do not assume all non-core paths should use the same license immediately.

## Documentation license decision

Documentation license remains undecided in this plan.

Candidates for later review:

```text
AGPL-3.0-or-later with project software
CC BY-SA 4.0 for standalone docs
Apache-2.0 for legacy docs until migrated
```

A documentation license decision should be made in a separate PR.

## Release checklist impact

Before any public release artifact, verify:

```text
root license state
file-level SPDX state
third-party notices
source-offer requirements
trademark use
release artifact license notes
```

## Non-legal-advice boundary

This plan is project guidance and not legal advice.

Formal relicensing, commercial distribution, dual licensing, or release review should receive qualified legal review.