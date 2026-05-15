# Latticra Real-System Contract

Status: initial contract
Scope: project identity, implementation boundary, evidence rules, and relationship to Phase1.

## Purpose

Latticra is the real-system implementation track for the Base1 / Phase1 / Fyr architecture.

It is built to separate formal implementation from simulation and prototype work.

Phase1 may explore. Latticra must prove.

## Identity

Latticra means a lattice-oriented real-system architecture: a computing environment built from explicit state spaces, grids, matrices, movement rules, safety gates, and evidence-backed promotion.

The name should communicate:

- structured state;
- software universes;
- embedded real-system direction;
- formal implementation;
- simulation-to-reality promotion;
- professional computer-science grounding.

## Relationship to Phase1

Phase1 is the proving environment.

Latticra is the implementation environment.

```text
Phase1 responsibility:
- simulate concepts;
- prototype command surfaces;
- test feasibility;
- preserve evidence;
- discover design constraints;
- prevent premature real-system claims.

Latticra responsibility:
- import proven concepts;
- formalize state contracts;
- implement narrow real components;
- validate hardware paths;
- record promotion evidence;
- keep real-system boundaries clear.
```

## Relationship to Base1

Base1 is the boot, recovery, and hardware evidence lineage that informs Latticra.

Latticra should not reuse the Base1 name as the repository identity because Base1 already has a specific architectural role.

Base1-derived work may enter Latticra only when it is evidence-backed and clearly scoped.

## Relationship to Fyr

Fyr is the native Phase1 language and future Latticra control/programming language candidate.

Fyr-related work in Latticra must remain bounded until the language has implementation, safety, runtime, and validation evidence.

## Required rule

No capability may enter Latticra as a real-system feature unless it has:

1. a written contract;
2. a non-claims section;
3. tests or validation evidence;
4. an import source from Phase1 or direct Latticra design;
5. a failure model;
6. a rollback or recovery boundary when mutation is involved;
7. an operator-visible status surface.

## Current non-execution boundary

This contract does not authorize:

- kernel implementation;
- boot image generation;
- installer behavior;
- disk mutation;
- recovery execution;
- network mutation;
- hardware mutation;
- production runtime claims;
- sandbox claims;
- security boundary claims.

## Development mode

Latticra starts in contract-first mode.

The first implementation work should be models, fixtures, tests, validation reports, and import rules. Live or mutating work comes later.
