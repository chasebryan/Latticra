# Latticra Language Strategy

Status: initial language strategy
Scope: C, Rust, Lat, L-UI, LIR, and implementation ordering.

## Purpose

Latticra needs a language strategy from the beginning.

The real system should not grow as an accidental collection of shell scripts, raw C files, ad-hoc config formats, and UI strings. Latticra should define which languages own which parts of the architecture before implementation begins.

This document has been updated to avoid using plain `L` as the public native language name. The language naming policy is defined in [`LANGUAGE_NAMING_POLICY.md`](LANGUAGE_NAMING_POLICY.md).

## Language roles

| Language | Role |
| --- | --- |
| C | Low-level substrate, ABI surfaces, freestanding boundaries, embedded portability, and hardware-adjacent components. |
| Rust | Tooling, validators, host-side builders, test harnesses, services, and server-side utilities. |
| Lat / Latticra Language | Native Latticra language family for state, policy, orchestration, assertions, and controlled system expression. |
| L-UI | Terminal/operator UI declaration language or dialect. |
| LIR | Latticra Intermediate Representation for validating and lowering Latticra language-family documents. |

## Lat / Latticra Language

The native language is planned as:

```text
Lat
```

Full descriptive name:

```text
Latticra Language
```

Canonical source extension:

```text
.lat
```

Plain `L` and `.l` are not the public language name or canonical file extension.

Lat should begin as a controlled system language, not a general-purpose programming language.

Early Lat responsibilities:

- declare lattice state;
- declare policies;
- declare effect requirements;
- declare transition rules;
- declare assertions;
- describe supervisor orchestration plans;
- describe operator-visible state reports.

Lat should not initially provide a general-purpose runtime, unrestricted system access, production runtime claims, or broad platform claims.

## Lat-Core

Lat-Core is the first native-language target.

Purpose:

```text
state + policy + assertion + transition declaration
```

Lat example syntax only:

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

## Lat-Orch

Lat-Orch is the future orchestration dialect for Nucleus.

Purpose:

```text
supervisor task planning + effect gates + recovery visibility + update staging
```

Lat-Orch must be explicit about:

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

The `.lui` extension remains valid for L-UI fixtures and source documents.

## LIR

LIR is the Latticra Intermediate Representation.

Purpose:

- normalize Lat and L-UI documents;
- validate names and effects;
- preserve source spans;
- reject forbidden behavior;
- support deterministic testing;
- provide stable input for C/Rust implementations.

LIR should be boring, explicit, serializable, and test-friendly.

The `.lir` extension is reserved for Latticra Intermediate Representation and should remain internal or generated until a future contract promotes it.

## C policy

C is allowed where machine control and portability matter.

C must follow a strict subset:

- fixed-size structs where possible;
- no unsafe string APIs;
- no hidden allocation in the early core;
- no undefined behavior tolerated;
- no unchecked pointer mutation;
- no implicit effects without explicit gates;
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

## Extension policy

The reserved Latticra language-family extensions are:

```text
.lat
.lui
.lir
```

Meaning:

| Extension | Meaning |
| --- | --- |
| `.lat` | Latticra Language source, including future Lat-Core and Lat-Orch forms. |
| `.lui` | Latticra UI declaration source. |
| `.lir` | Latticra Intermediate Representation, internal or generated unless later promoted. |

The project should not use `.l` as the canonical source extension.

## Implementation order

1. Define contracts and docs.
2. Add C state lattice fixture.
3. Add invariant tests.
4. Add Rust validation tooling if needed.
5. Define Lat-Core grammar draft.
6. Define LIR shape.
7. Add parser prototype only after syntax contracts stabilize.
8. Add L-UI only after state reports are stable.
9. Add Lat-Orch only after effect gates are stable.

## Non-claims

This document does not claim that Lat, Lat-Core, Lat-Orch, L-UI, or LIR are fully implemented.

It defines the intended language architecture before native-language implementation begins.
