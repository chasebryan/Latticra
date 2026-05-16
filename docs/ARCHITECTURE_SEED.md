# Latticra Architecture Seed

Status: initial architecture seed
Scope: vocabulary, first system layers, and implementation direction.

## Purpose

This document defines the initial architecture vocabulary for Latticra.

It is not a complete architecture specification. It is the seed from which implementation contracts, tests, models, and components can grow.

## Core metaphor

Latticra models real software systems as structured computational universes.

Those universes are composed of:

- lattices;
- grids;
- matrices;
- state planes;
- transition rules;
- execution domains;
- visibility rails;
- evidence gates;
- rollback surfaces;
- embedded system boundaries.

## Initial layers

```text
L0 Contract Layer
  Real-system contract, non-claims, evidence ladder, promotion rules.

L1 State Lattice Layer
  Explicit state cells, paths, axes, routes, origins, traces, breadcrumbs.

L2 Transition Layer
  Pure transition models and denial rules before live movement.

L3 Visibility Layer
  Operator-readable state reports, visibility rails, health/risk/lock surfaces.

L4 Language Layer
  Lat declarations, read-only source forms, and assertion candidates.

L5 Evidence Layer
  Validation reports, virtual-target evidence, read-only hardware evidence, promotion records.

L6 Embedded Implementation Layer
  Narrow real-system implementation candidates after evidence gates.
```

## Initial state vocabulary

Latticra begins with a compact state vocabulary but does not claim live movement yet.

```text
origin
route
axis
path
breadcrumb
trace
safe_portal
rollback
health
risk
lock
dark_phase
host_effect
external_effect
```

## First implementation candidate

The first implementation candidate should be a state lattice fixture.

Required properties:

```text
deterministic
serializable
read-only by default
effect-free
operator-visible
traceable
testable
```

Forbidden properties in the first implementation:

```text
live movement
origin mutation
recovery execution
host filesystem mutation
network mutation
hardware mutation
hidden state mutation
security claims
boot claims
```

## Lattice transition direction

A future transition engine should accept:

```text
current_state
transition_request
operator_intent
policy_context
```

and return:

```text
next_state
result
reason
effects
rollback_visibility
trace
```

The first transition engine must be pure and preview-only.

## Software universe direction

A Latticra software universe is not a fantasy world or game map.

It is a structured execution and state environment where every coordinate, route, transition, effect, and recovery surface has an inspectable contract.

The long-term goal is to make complex system behavior visible, navigable, testable, and eventually implementable on real machines.

## Early component candidates

```text
lattice-state
lattice-transition
lattice-report
promotion-packet
lat-assertion-candidate
hardware-profile-contract
evidence-record
promotion-record
```

## Near-term repository structure

Recommended future structure:

```text
docs/
  contracts/
  evidence/
  architecture/
  promotion/
  hardware/

src/
  lattice/
  transition/
  reports/

tests/
  docs/
  lattice/
  transition/

examples/
  fixtures/
```

Do not add this full structure until the first implementation slice requires it.

## North star

Latticra should become a formal, evidence-bound implementation of a lattice-oriented computing architecture.

It should remain academically serious, implementation-focused, evidence-bound, and safe to reason about.
