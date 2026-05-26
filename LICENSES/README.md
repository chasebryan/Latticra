# Latticra License References

Status: active license reference index

## Purpose

This directory records license identifiers, local license texts, and policy references used by Latticra.

The root `LICENSE` file records the project hybrid licensing overview.

The detailed policy records are:

```text
docs/OPEN_ECOSYSTEM_POLICY.md
docs/LICENSE_POLICY.md
docs/DOCUMENTATION_LICENSE.md
CONTRIBUTING.md
TRADEMARK_POLICY.md
```

## Current identifiers

Current identifiers:

```text
AGPL-3.0-or-later
Apache-2.0
CC-BY-4.0
```

## Local license texts

Local copies of referenced license texts are stored at:

```text
LICENSES/AGPL-3.0-or-later.txt
LICENSES/Apache-2.0.txt
LICENSES/CC-BY-4.0.txt
```

## SPDX usage

New source files should include an SPDX license identifier.

Preferred new core software source identifier:

```text
SPDX-License-Identifier: AGPL-3.0-or-later
```

Preferred new adoption-facing helper source identifier:

```text
SPDX-License-Identifier: Apache-2.0
```

Preferred new documentation identifier:

```text
SPDX-License-Identifier: CC-BY-4.0
```

Existing files should not be silently re-tagged. Path-by-path migration should happen through reviewed PRs.

## Trademark boundary

Software and documentation licenses do not grant rights to use Latticra or Bryforge names, logos, marks, slogans, or identity in a confusing way.

See:

```text
TRADEMARK_POLICY.md
```
