# Latticra Seal Architecture

Latticra Seal is organized around bounded evidence.

It does not begin with enforcement. It begins with describing what exists, measuring what exists, reporting what changed, and refusing to claim authority it does not yet have.

## Core model

```text
source tree
   |
   v
manifest / seal config
   |
   v
hash baseline
   |
   v
policy checks
   |
   v
report-only evidence
   |
   v
Panel / CLI / future runtime boundary handoff
```

## Primary components

### Manifest layer

The manifest layer defines what Seal is allowed to inspect.

Expected files may include:

```text
latticra.seal
latticra.seal.lock
```

The manifest should describe scope, included paths, excluded paths, policy expectations, and report behavior.

### Measurement layer

The measurement layer computes local evidence.

Initial measurement should remain read-only.

Expected behavior:

- read local files
- compute hashes
- compare against saved baseline
- record changed/missing/new files
- avoid mutation unless explicitly running an update/baseline command

### Policy layer

The policy layer decides whether the current state is acceptable.

Initial policy behavior should be conservative:

- fail closed on malformed policy
- fail closed on denied paths
- fail closed on unsupported authority claims
- report why a decision was denied

### Report layer

The report layer emits human-readable evidence.

Reports should clearly show:

- mode
- timestamp
- host OS
- prefix
- hash status
- policy status
- warnings
- failures
- non-authority declarations

### Panel bridge

The Panel bridge should expose Seal through a safe interface.

Panel should be able to:

- run report-only checks
- display Seal status
- show policy results
- show generated reports
- avoid granting runtime/root/network authority

### Future runtime-boundary handoff

Future runtime integration must remain gated.

Seal may eventually produce metadata for runtime-boundary decisions, but documentation must not claim runtime enforcement until the enforcement path exists and has tests.
