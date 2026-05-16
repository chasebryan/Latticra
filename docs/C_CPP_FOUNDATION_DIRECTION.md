# Latticra C/C++ Foundation Direction

Status: active language direction
Scope: C/C++ foundation policy for Latticra systems implementation and public direction.

## Purpose

This document records the current implementation direction for Latticra:

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Latticra should use a constrained C/C++ foundation for security-conscious system work.

This direction does not claim unrestricted C++, broad runtime behavior, operating-system completeness, sandboxing, malware prevention, ransomware prevention, or production security guarantees.

## Layer model

The intended public model is:

```text
Lat / Latticra Language: contract layer
C++: governed authority layer
C: secure substrate
```

## C secure substrate

C owns the lowest software boundary.

Primary C responsibilities:

```text
boot paths
ABI boundaries
platform shims
fixed-size data structures
freestanding-adjacent boundaries
minimal substrate behavior
no-hidden-allocation early core
portable test fixtures
```

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

```text
policy logic
validators
effect gates
audit logic
bounded orchestration structures
operator-visible reports
higher-level state coordination
safe wrappers around C substrate APIs
```

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

## Latticra contract language layer

Lat / Latticra Language is the contract and declaration layer.

Primary Lat responsibilities:

```text
state declarations
policy declarations
transition declarations
assertions
effect requirements
operator-visible contract surfaces
future validated input to LIR
```

Lat is not currently a parser, compiler, interpreter, runtime, package manager, or execution surface.

## Not unrestricted C++

The direction explicitly rejects unrestricted C++.

C++ may be used only when it is:

```text
bounded
reviewable
effect-aware
policy-oriented
audit-friendly
compatible with C substrate boundaries
covered by tests or guards
clear about ownership and lifetime
```

## Trust and evidence rules

All C/C++ work should preserve:

```text
explicit trust boundaries
evidence-bound validation
source-aware diagnostics
bounded reports
no-effect defaults
operator-visible state
contract before capability
```

## Relationship to LIR

The current LIR implementation is metadata-only.

LIR remains a representation target and must not become an execution surface without a separate contract.

C/C++ implementation work must not use LIR to bypass semantic validation, source-span preservation, no-effect flags, or effect gates.

## Relationship to Rust

Rust is not the current public foundation direction for Latticra.

Rust may appear only as optional external tooling or historical comparison if separately justified, but it is not the default public implementation lane and should not be presented as a primary foundation layer.

## Public wording

Approved public wording:

```text
A constrained C/C++ foundation for a security-conscious system.
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Avoid wording that implies:

```text
unrestricted C++
finished operating system
finished language runtime
production security boundary
malware prevention guarantee
ransomware prevention guarantee
```

## Implementation ordering

Recommended ordering:

1. C substrate fixtures and ABI-safe data structures.
2. C parser, AST, semantic validation, and LIR metadata foundations.
3. C++ policy, validation, effect-gate, and audit layers after C substrate contracts are stable.
4. Lat grammar and parser contracts before any Lat parser implementation.
5. LIR/Lat lowering only after separate contracts.
6. Execution only after explicit runtime/effect/security contracts.

## Current validation command

This direction is guarded by:

```sh
sh scripts/test-c-cpp-foundation-direction.sh
```

The guard is static. It does not implement C++ policy code.

## Non-claims

This document does not implement C++ infrastructure, Lat parsing, LIR execution, L-UI rendering, Nucleus task execution, live movement, state mutation, server interaction, recovery behavior, hardware behavior, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
