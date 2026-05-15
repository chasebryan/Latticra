# Latticra Language Strategy

Status: initial language strategy
Scope: C, Rust, L, L-UI, LIR, and implementation ordering.

## Purpose

Latticra needs a language strategy from the beginning.

The real system should not grow as an accidental collection of shell scripts, raw C files, ad-hoc config formats, and UI strings. Latticra should define which languages own which parts of the architecture before implementation begins.

## Language roles

| Language | Role |
| --- | --- |
| C | Low-level substrate, ABI surfaces, freestanding boundaries, embedded portability, hardware-adjacent components. |
| Rust | Tooling, validators, host-side builders, test harnesses, safe services, server-side utilities. |
| L | Native Latticra language for state, policy, orchestration, assertions, and controlled system expression. |
| L-UI | Terminal/operator UI declaration language or dialect. |
| LIR | Latticra Intermediate Representation for validating and lowering L-family documents. |

## L

The native language is planned as:

```text
L
```

Full descriptive name:

```text
The Latticra Language
```

L should begin as a controlled system language, not a general-purpose programming language.

Early L responsibilities:

- declare lattice state;
- declare policies;
- declare effect requirements;
- declare transition rules;
- declare assertions;
- describe supervisor orchestration plans;
- describe operator-visible state reports.

L should not initially provide:

- arbitrary host execution;
- unsafe memory access;
- network access;
- hardware mutation;
- self-update execution;
- production runtime claims.

## L-Core

L-Core is the first language target.

Purpose:

```text
state + policy + assertion + transition declaration
```

Example direction:

```text
state RootCell {
  origin = "0/0"
  route = "ROOT"
  axis = "ROOT"
  host_effect = none
  external_effect = none
}

transition move_right from RootCell {
  require lock == open
  require risk != high
  effect host = none
  effect external = none
}
```

This is example syntax only. It is not implemented yet.

## L-Orch

L-Orch is the future orchestration dialect for Nucleus.

Purpose:

```text
supervisor task planning + effect gates + recovery visibility + update staging
```

L-Orch must be explicit about:

- requested effect;
- required gate;
- rollback behavior;
- failure behavior;
- operator confirmation;
- server interaction;
- audit trail.

## L-UI

L-UI is the terminal/operator interface language or dialect.

Purpose:

```text
operator rails + state cards + reports + safe command surfaces
```

L-UI should be declarative, not a hidden imperative UI runtime.

## LIR

LIR is the Latticra Intermediate Representation.

Purpose:

- normalize L documents;
- validate names and effects;
- preserve source spans;
- reject forbidden behavior;
- support deterministic testing;
- provide stable input for C/Rust implementations.

LIR should be boring, explicit, serializable, and test-friendly.

## C policy

C is allowed where machine control and portability matter.

C must follow a strict subset:

- fixed-size structs where possible;
- no unsafe string APIs;
- no hidden allocation in the early core;
- no undefined behavior tolerated;
- no unchecked pointer mutation;
- no host/network/hardware effects without explicit gates;
- no global mutable state unless named in a contract;
- all transitions return status codes.

## Rust policy

Rust is preferred for:

- validators;
- CLI tools;
- documentation guards;
- package/update tools;
- server interaction prototypes;
- test harnesses;
- host-side automation.

Rust does not replace the need for a disciplined low-level C ABI when Latticra touches embedded or boot-adjacent surfaces.

## Implementation order

1. Define contracts and docs.
2. Add C state lattice fixture.
3. Add invariant tests.
4. Add Rust validation tooling if needed.
5. Define L-Core grammar draft.
6. Define LIR shape.
7. Add parser prototype only after syntax contracts stabilize.
8. Add L-UI only after state reports are stable.
9. Add L-Orch only after effect gates are stable.

## Non-claims

This document does not claim that L, L-UI, L-Orch, or LIR are implemented.

It defines the intended language architecture before implementation begins.
