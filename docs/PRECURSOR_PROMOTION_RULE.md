# Latticra Precursor Promotion Rule

Status: initial promotion rule
Scope: how prior research, prototypes, experiments, and external lessons may become Latticra work.

## Purpose

Latticra should not absorb every prior idea automatically.

Precursor work may inform Latticra, but Latticra should only promote an idea after it has evidence, boundaries, tests, and a clear implementation purpose.

This document keeps the project self-contained while still allowing useful lessons from earlier research and prototypes to be formalized.

## Promotion rule

A concept may enter Latticra only when it has:

1. a clear technical purpose;
2. a documented non-claim boundary;
3. at least one fixture, test, or validation artifact;
4. a clear Latticra destination;
5. a failure or denial model;
6. an effect boundary;
7. a reviewable implementation path.

## Promotion packet

Every promoted concept should start with a promotion packet:

```text
name:
origin type: research|prototype|direct-design|external-standard|test-result
source evidence level:
Latticra target:
status:
operator-visible state:
mutation allowed: no|yes
host-effect: none|planned|gated|executed
external-effect: none|planned|gated|executed
rollback state:
non-claims:
required next evidence:
```

## Early promotion candidates

### State lattice model

Initial Latticra target:

```text
lattice state fixture
state labels
invariant tests
read-only reports
```

Boundary:

```text
no live movement
no origin mutation
no recovery execution
no host effect
no external effect
```

### Tri-plane transition model

Initial Latticra target:

```text
pure transition model
spatial plane
state plane
safety plane
denial reasons
```

Boundary:

```text
preview-only
pure function
no hardware effect
no hidden state mutation
```

### Lat language path

Initial Latticra target:

```text
read-only source declarations
state inspection candidate
assertion language candidate
future controlled programming language
```

Boundary:

```text
no production runtime claim
no live system mutation
no privileged execution
no automatic promotion
```

### Hardware evidence path

Initial Latticra target:

```text
hardware target profiles
evidence templates
read-only validation reports
VM evidence gates
real-device read-only gates
```

Boundary:

```text
no installer claim
no bootable release claim
no recovery execution claim
no disk mutation claim
```

## Rejection rules

Do not promote a concept when:

- it is only a name;
- it has no non-claims;
- it depends on hidden mutation;
- it implies hardware readiness without hardware evidence;
- it would confuse research with implementation;
- it bypasses the evidence ladder;
- it expands claims beyond what tests support.

## Naming rule

Promoted concepts should use Latticra implementation-level names once they become public architecture.

Example:

```text
research concept: multi-plane movement check
Latticra component candidate: tri-plane transition model
```

## Current status

No precursor concept is automatically a real-system capability.

This document only defines the promotion gate.
