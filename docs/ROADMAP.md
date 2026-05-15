# Latticra Roadmap

Status: initial roadmap
Scope: design-first planning, implementation order, and promotion rules.

## Purpose

Latticra should be planned, refined, and documented before implementation code begins.

This roadmap keeps the project disciplined while preserving the ambition of building a real system from Phase1, Base1, and Fyr lessons.

## Roadmap principle

```text
contracts before code
fixtures before runtime
read-only before mutation
local before server
hosted before hardware
VM before real device
read-only device evidence before real execution
```

## Stage 0: Foundation planning

Goal:

```text
define the system before implementing it
```

Required documents:

- real-system contract;
- evidence ladder;
- Phase1 import rule;
- non-claims;
- architecture seed;
- naming system;
- language strategy;
- supervisor architecture;
- feature translation ledger;
- effect gates;
- L-UI direction;
- server interaction model;
- self-update model;
- host architecture targets;
- license policy.

Exit criteria:

- documents linked from README and foundation index;
- no implementation claim;
- first implementation target named.

## Stage 1: State lattice fixture

Goal:

```text
create the first real Latticra implementation unit
```

Scope:

- C header for state shape;
- deterministic fixture;
- no-effect invariant tests;
- report fixture;
- x86_64/ARM64-neutral structure policy.

Required labels:

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

Non-claims:

- no live movement;
- no host mutation;
- no hardware interaction;
- no update behavior;
- no server interaction.

## Stage 2: Tri-plane transition model

Goal:

```text
model movement safely before implementing live movement
```

Scope:

- pure transition function;
- spatial plane;
- state plane;
- safety plane;
- denial reasons;
- no-effect guarantee.

Exit criteria:

- accepted transition tests;
- denied transition tests;
- lock/risk/rollback tests;
- host/external effect remains none.

## Stage 3: Nucleus preview supervisor

Goal:

```text
introduce supervisor classification without real mutation
```

Scope:

- request classification;
- policy classification;
- effect classification;
- no-effect reports;
- evidence record fixture.

Non-claims:

- no task execution beyond preview/report;
- no server activity;
- no updates;
- no recovery behavior.

## Stage 4: L-Core draft

Goal:

```text
define native language contracts for state, policy, and assertions
```

Scope:

- grammar draft;
- example files;
- parser design;
- LIR draft;
- no execution beyond validation fixtures.

## Stage 5: L-UI report fixtures

Goal:

```text
declare terminal/operator surfaces before rendering engine work
```

Scope:

- state cards;
- operator rails;
- effect reports;
- denial reports;
- no-color and narrow-terminal constraints.

## Stage 6: Server and update fixtures

Goal:

```text
model network/update behavior without performing it
```

Scope:

- server request fixture;
- signed manifest fixture;
- update state fixture;
- rollback visibility fixture;
- denied network by default.

## Stage 7: Hosted reference implementation

Goal:

```text
run Latticra as a hosted reference process
```

Targets:

```text
x86_64-hosted
aarch64-hosted
```

Scope:

- local-only execution;
- no server by default;
- no hardware effects;
- no boot effects.

## Stage 8: VM evidence profiles

Goal:

```text
validate controlled profiles in QEMU or similar environments
```

Targets:

```text
x86_64-qemu
aarch64-qemu
```

Scope:

- reproducible commands;
- validation reports;
- evidence bundles;
- no real-device claim.

## Stage 9: Real-device read-only evidence

Goal:

```text
observe real targets without changing them
```

Scope:

- device identity;
- read-only checklists;
- reports;
- non-mutation evidence.

## Stage 10: Gated real-system experiments

Goal:

```text
consider narrow real-world actions after evidence supports them
```

Required before entry:

- tests;
- VM evidence;
- real-device read-only evidence;
- rollback model;
- failure behavior;
- operator confirmation;
- safety review.

## Current next step

After the planning documents are merged, the next PR should be:

```text
Add state lattice fixture and invariant tests
```

## Non-claims

This roadmap does not claim Latticra has implemented any runtime, supervisor, language, update system, server system, boot system, or hardware support.

It defines the sequence for disciplined implementation.
