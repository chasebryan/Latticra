# Latticra Phase1 Import Rule

Status: initial import rule
Scope: how Phase1, Base1, Fyr, and Optics concepts may enter Latticra.

## Purpose

Latticra should not absorb every Phase1 idea automatically.

Phase1 is allowed to explore and simulate. Latticra is allowed to implement only after an idea has evidence, boundaries, and a clear real-system purpose.

## Import rule

A concept may be imported from Phase1 into Latticra only when it has:

1. a named source in Phase1;
2. a written purpose;
3. a documented non-claim boundary;
4. at least one fixture, test, or validation artifact;
5. a clear Latticra destination;
6. a failure or denial model;
7. an effect boundary.

## Import packet

Every imported concept should start with an import packet:

```text
name:
source:
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

## Approved early import candidates

### Phase universe state model

Source: Phase1 Optics / Phase movement design.

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

### Trilateral Phase Movement

Source: Phase1 Trilateral Phase Movement design.

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

### Fyr native language path

Source: Phase1 Fyr toolchain and language track.

Initial Latticra target:

```text
read-only scripting candidate
state inspection candidate
assertion language candidate
```

Boundary:

```text
no production runtime claim
no live system mutation
no privileged execution
no automatic promotion
```

### Base1 evidence path

Source: Base1 docs and validation tracks in Phase1.

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

Do not import a concept when:

- it is only a name;
- it has no non-claims;
- it depends on hidden mutation;
- it implies hardware readiness without hardware evidence;
- it would confuse simulation with implementation;
- it bypasses the evidence ladder;
- it expands claims beyond what Phase1 proved.

## Naming rule

Imported concepts may keep their source name as internal vocabulary, but Latticra should use implementation-level names when the concept becomes a real component.

Example:

```text
Phase1 concept: Trilateral Phase Movement
Latticra component candidate: lattice transition engine
```

## Current status

No Phase1 concept is currently imported as a real-system capability.

This document only defines the import gate.
