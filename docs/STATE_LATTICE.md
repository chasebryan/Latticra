# Latticra State Lattice

Status: initial implementation contract
Scope: first C state fixture, invariant tests, report surface, and no-effect boundary.

## Purpose

The State Lattice is the first real Latticra implementation unit.

It provides a deterministic, fixed-size, no-effect C fixture that represents the starting state vocabulary inherited from the Phase1 evidence path and translated into Latticra architecture terms.

## Implementation files

```text
include/latticra/state_lattice.h
src/state_lattice.c
tests/state_lattice_invariants.c
scripts/test-state-lattice.sh
```

## Default fixture

The default state lattice fixture must preserve:

```text
origin=0/0
route=ROOT
axis=ROOT
path=ROOT>0/0
breadcrumb=ROOT
trace=trace-preview
safe_portal=planned
rollback=available
health=nominal
risk=low
lock=open
dark_phase=off
host_effect=none
external_effect=none
```

## Effect boundary

The initial state lattice fixture is no-effect.

It must not:

- mutate host state;
- use networking;
- touch hardware;
- perform boot behavior;
- perform recovery behavior;
- perform external effects;
- allocate hidden dynamic state;
- depend on server interaction.

## C policy

The first implementation uses C because the State Lattice is intended to become a portable low-level representation.

Rules:

- fixed-size fields;
- explicit enum values;
- no hidden allocation;
- no host-specific APIs;
- no network APIs;
- no hardware APIs;
- no file writes;
- deterministic report output.

## Public API

Initial API:

```text
latticra_state_lattice_default
latticra_effect_label
latticra_state_lattice_is_no_effect
latticra_state_lattice_report
```

## Test command

Run:

```sh
sh scripts/test-state-lattice.sh
```

The test builds the C fixture with a strict warning policy and runs invariant checks.

## Required invariants

The tests must verify:

- default labels match the contract;
- host effect is none;
- external effect is none;
- default fixture is no-effect;
- report output exposes operator-visible labels;
- bad report arguments are rejected;
- small report buffers are rejected.

## Current evidence level

This implementation is an L2 tested model for the initial state fixture.

It is not a runtime supervisor, transition engine, update engine, server client, boot component, hardware component, or recovery system.

## Next implementation step

The next implementation candidate after this fixture is:

```text
tri-plane transition model
```

That future work must remain pure and preview-only until evidence supports stronger behavior.

## Non-claims

This document and implementation do not claim live lattice movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
