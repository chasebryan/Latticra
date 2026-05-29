# Latticra License Policy

Status: active hybrid license policy
Scope: hybrid software licensing, documentation licensing, SPDX usage, branding, contributions, and future artifacts.

## Purpose

Latticra is intended to remain open, auditable, transparent, and community-improvable.

This policy explains the current hybrid repository license state and the transition-aware rules for future work.

See also:

```text
docs/OPEN_ECOSYSTEM_POLICY.md
docs/DOCUMENTATION_LICENSE.md
CONTRIBUTING.md
TRADEMARK_POLICY.md
LICENSES/README.md
```

## Current repository posture

The root repository license overview is:

```text
LICENSE
```

Latticra uses this hybrid posture:

```text
core/runtime/security substrate: AGPL-3.0-or-later
SDKs/examples/packaging helpers/integration helpers: Apache-2.0
documentation/handbooks/policy notes: CC-BY-4.0
names/logos/identity: TRADEMARK_POLICY.md
```

Existing repository code remains Apache-2.0 unless a file-level SPDX identifier, path-level notice, or reviewed migration explicitly marks it otherwise.

## Edge labels and public listings

`v0.3.0edge` and `v0.4.0edge` are validation-posture labels. They do not create separate license listings, change the hybrid policy, mark a release artifact license review as complete, or silently relicense any path.

## Core software direction

The intended software licensing direction for new software work is:

```text
AGPL-3.0-or-later
```

This direction applies to core runtime, security-substrate, tool-boundary, runtime-gating, verification, and evidence-bound computing components.

It is meant to preserve open, auditable, transparent access to Latticra-derived core software while the project grows into system, kernel, language, tool, and operator-facing components.

## Adoption-facing software direction

The intended license for SDKs, examples, packaging helpers, installer glue, integration helpers, and other adoption-facing software is:

```text
Apache-2.0
```

This keeps integration surfaces commercially friendly and packaging friendly while preserving an express patent grant.

## Documentation direction

The documentation and handbook license decision is:

```text
CC-BY-4.0
```

See:

```text
docs/DOCUMENTATION_LICENSE.md
LICENSES/CC-BY-4.0.txt
```

## No silent relicensing

This policy does not silently relicense every existing file.

Existing files remain under their current license until a later migration PR updates them clearly and intentionally.

A file-level or path-level migration should include:

```text
SPDX license identifier update
reason for migration
affected paths
compatibility notes
review before release
```

## New source file rule

New software source files should declare their license with an SPDX identifier.

The preferred identifier for new core software source files is:

```text
SPDX-License-Identifier: AGPL-3.0-or-later
```

The preferred identifier for new adoption-facing helper source files is:

```text
SPDX-License-Identifier: Apache-2.0
```

Documented exceptions are allowed when the exception is intentional and reviewed.

## New documentation file rule

New documentation files may declare:

```text
SPDX-License-Identifier: CC-BY-4.0
```

Existing documentation is covered by the path-level decision in:

```text
docs/DOCUMENTATION_LICENSE.md
```

## Contributions

Contributions are accepted under the license declared by the files being modified.

New software contributions should follow the project direction documented in:

```text
docs/OPEN_ECOSYSTEM_POLICY.md
CONTRIBUTING.md
```

No proprietary relicensing contributor license agreement is adopted by this policy.

## Branding and trademarks

Software and documentation licenses do not grant trademark, branding, endorsement, or official-project identity rights.

Project names, logos, marks, and Bryforge/Latticra branding are handled separately.

See:

```text
TRADEMARK_POLICY.md
```

## Third-party material

Third-party material must include source, license, and compatibility notes before being added.

Required fields:

```text
name:
source:
license:
compatible with current path license: yes|no|unknown
purpose:
notes:
```

## Generated artifacts

Generated artifacts may need additional notices depending on source inputs, build process, and bundled dependencies.

No release artifact should be published until its licensing and notice requirements are reviewed.

## NOTICE file

A future `NOTICE` file may be added when Latticra has third-party notices, attribution requirements, or distribution notes to preserve.

## Future work

Recommended follow-up work:

```text
add SPDX headers to new software files
maintain hybrid license posture guard
review path-by-path migration from Apache-2.0
add release license checklist
add NOTICE if needed
```

## Non-claims

This policy is project guidance and not legal advice.

For commercial licensing strategy, patent strategy, trademark strategy, formal relicensing, or release review, obtain qualified legal review.
