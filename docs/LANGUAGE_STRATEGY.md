# Latticra Language Strategy

Status: active language strategy
Scope: C, constrained C++, Lat, L-UI, LIR, and implementation ordering.

## Purpose

Latticra needs a language strategy from the beginning.

The real system should not grow as an accidental collection of shell scripts, raw C files, ad-hoc config formats, and UI strings. Latticra should define which languages own which parts of the architecture before implementation expands.

This document avoids using plain `L` as the public native language name. The language naming policy is defined in [`LANGUAGE_NAMING_POLICY.md`](LANGUAGE_NAMING_POLICY.md).

The active C/C++ foundation direction is defined in [`C_CPP_FOUNDATION_DIRECTION.md`](C_CPP_FOUNDATION_DIRECTION.md).

## Direction summary

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Latticra should use a constrained C/C++ foundation for a security-conscious system.

This does not mean unrestricted C++.

## Language roles

| Language | Role |
| --- | --- |
| C | Secure substrate, boot paths, ABI boundaries, platform shims, fixed-size data structures, and freestanding-adjacent boundaries. |
| C++ | Governed authority layer for policy, validators, effect gates, audit logic, bounded orchestration structures, and safe wrappers over C substrate APIs. |
| Lat / Latticra Language | Native contract/declaration language family for state, policy, orchestration, assertions, and controlled system expression. |
| L-UI | Terminal/operator UI declaration language or dialect. |
| LIR | Latticra Intermediate Representation for validating and lowering Latticra language-family documents. |

## C secure substrate

C owns the lowest software boundary.

Primary C responsibilities:

- boot paths;
- ABI boundaries;
- platform shims;
- fixed-size data structures;
- freestanding-adjacent boundaries;
- minimal substrate behavior;
- portable test fixtures.

C must remain disciplined:

- no unsafe string APIs;
- no unchecked pointer mutation;
- no undefined behavior tolerated;
- no implicit effects without explicit gates;
- no global mutable state unless named in a contract;
- all transitions return status codes;
- all source/input behavior remains bounded and testable.

## C++ governed authority layer

C++ is allowed above the C substrate as a governed authority layer.

Primary C++ responsibilities:

- policy logic;
- validators;
- effect gates;
- audit logic;
- bounded orchestration structures;
- operator-visible reports;
- higher-level state coordination;
- safe wrappers around C substrate APIs.

C++ must be constrained.

It is not:

```text
unrestricted C++
exception-heavy C++
reflection-heavy C++
template metaprogramming as architecture
hidden allocation by default
implicit authority
unchecked host execution
```

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
- provide stable input for C and constrained C++ implementations.

LIR should be boring, explicit, serializable, and test-friendly.

The `.lir` extension is reserved for Latticra Intermediate Representation and should remain internal or generated until a future contract promotes it.

## Rust relationship

Rust is not the current public foundation direction for Latticra.

Rust may appear only as optional external tooling or historical comparison if separately justified, but it is not the default public implementation lane and should not be presented as a primary foundation layer.

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
2. Add C substrate fixtures and invariant tests.
3. Add C parser, AST, semantic validation, and LIR metadata foundations.
4. Define constrained C++ policy/validator/effect-gate layers after C substrate contracts stabilize.
5. Define Lat-Core grammar and implementation plans before parser code.
6. Define Lat-to-LIR lowering only after parser and semantic contracts exist.
7. Add execution only after explicit runtime/effect/security contracts.

## Non-claims

This document does not claim that Lat, Lat-Core, Lat-Orch, L-UI, LIR, C++ authority layers, or any runtime are fully implemented.

It defines the intended language architecture before broader native-language implementation begins.
