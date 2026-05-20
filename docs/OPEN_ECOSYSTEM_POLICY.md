# Latticra Open Ecosystem Policy

Status: active governance policy
Scope: project openness, auditability, transparency, contribution posture, and license transition planning.

## Purpose

Latticra is intended to remain open, auditable, transparent, and community-improvable.

The project should preserve the ability of users, researchers, maintainers, and downstream operators to inspect, modify, rebuild, and improve the system.

## Direction

The intended direction is:

```text
software license direction: AGPL-3.0-or-later for new software work
legacy repository default: Apache-2.0 until files are intentionally migrated
kernel/core direction: reciprocal open license coverage
branding: separate trademark and identity policy
```

## Transition rule

This policy does not silently relicense every existing file.

Existing files remain under their current license until a later migration PR updates them clearly.

New software source files should declare their license with an SPDX header.

## New source file rule

New software source files should use:

```text
SPDX-License-Identifier: AGPL-3.0-or-later
```

unless a documented exception exists.

## Contribution rule

Contributions are accepted under the license declared by the files they modify.

New software contributions should be compatible with the project license direction unless a documented exception is accepted.

## Identity rule

The code license does not grant rights to use the Latticra name, logo, marks, or Bryforge identity in a confusing way.

Forks may describe their relationship truthfully, but they must not imply they are the official project unless authorized.

## Legal review note

This document is project guidance, not legal advice.

Formal release, relicensing, commercial distribution, or dual-license decisions should receive qualified legal review.

## Follow-up work

Recommended follow-up slices:

```text
1. Add SPDX headers to new kernel and core source files.
2. Add a license guard for new source files.
3. Decide documentation license.
4. Add or update NOTICE and copyright ownership policy.
5. Review path-by-path migration from Apache-2.0 to AGPL-3.0-or-later.
6. Add a release checklist for license obligations.
```