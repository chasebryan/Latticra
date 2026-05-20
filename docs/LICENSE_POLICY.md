# Latticra License Policy

Status: active license transition policy
Scope: current Apache-2.0 repository license, open ecosystem transition, SPDX usage, branding, contributions, and future artifacts.

## Purpose

Latticra is intended to remain open, auditable, transparent, and community-improvable.

This policy explains the current repository license state and the intended transition toward a reciprocal open ecosystem licensing model.

See also:

```text
docs/OPEN_ECOSYSTEM_POLICY.md
CONTRIBUTING.md
TRADEMARK_POLICY.md
```

## Current repository license

The current canonical repository license file is:

```text
LICENSE
```

That file currently contains:

```text
Apache-2.0
```

Unless a file explicitly says otherwise, existing files remain under their current license state.

## Transition direction

The intended software licensing direction for new software work is:

```text
AGPL-3.0-or-later
```

This direction is meant to preserve open, auditable, transparent access to Latticra-derived software while the project grows into system, kernel, language, tool, and operator-facing components.

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

The preferred identifier for new software source files is:

```text
SPDX-License-Identifier: AGPL-3.0-or-later
```

Documented exceptions are allowed only when the exception is intentional and reviewed.

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
add a license guard for source paths
review docs license direction
review path-by-path migration from Apache-2.0
add release license checklist
add NOTICE if needed
```

## Non-claims

This policy is project guidance and not legal advice.

For commercial licensing strategy, patent strategy, trademark strategy, formal relicensing, or release review, obtain qualified legal review.