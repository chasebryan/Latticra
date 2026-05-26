# Contributing to Latticra

Status: active contribution policy

## Purpose

Latticra welcomes contributions that support an open, auditable, transparent systems project.

Contributions should preserve the project direction:

```text
open source
auditable
transparent
security-conscious
evidence-bound
community-improvable
```

## License expectation

Contributions are accepted under the license declared by the files being modified.

New software source files should follow the current project license direction documented in:

```text
docs/OPEN_ECOSYSTEM_POLICY.md
docs/LICENSE_POLICY.md
```

New software source files should include an SPDX license identifier unless a documented exception exists.

## No proprietary relicensing CLA

This project does not adopt a proprietary relicensing contributor license agreement through this policy.

By contributing, contributors represent that they have the right to submit the contribution under the applicable project license terms.

## Developer Certificate of Origin direction

The project intends to use a Developer Certificate of Origin style contribution model.

A follow-up slice may add a formal `Signed-off-by` requirement and DCO guard.

## Contribution quality

Contributions should be:

```text
small enough to review
tested or guarded
evidence-bound
clear about effect boundaries
clear about non-claims
compatible with public project direction
```

Before changing safety guards, CI workflows, shell checks, or quality gates, run:

```sh
make quality-safety-guards
```

Before submitting broader code or installer changes, run:

```sh
make quality
```

## Documentation changes

Documentation changes should preserve reader-facing cohesion and current non-claims.

Before changing public status, estimates, platform readiness, installer authority, security wording, subsystem status, or top-level navigation, read:

```text
docs/README.md
docs/DOCUMENTATION_MAINTENANCE.md
```

For documentation-only changes, run the narrowest relevant guards from `docs/DOCUMENTATION_MAINTENANCE.md` and avoid changing source behavior, installer authority, package authority, runtime authority, workflow permissions, or security posture.

## Security-sensitive changes

Changes that affect runtime behavior, state mutation, external effects, command behavior, file behavior, network behavior, hardware behavior, boot behavior, recovery behavior, or security claims require explicit tests and documentation.

## Trademark and identity

Contribution rights do not grant permission to use the Latticra name, logos, marks, or Bryforge identity in a confusing way.

See:

```text
TRADEMARK_POLICY.md
```

## Legal note

This document is project guidance, not legal advice.
