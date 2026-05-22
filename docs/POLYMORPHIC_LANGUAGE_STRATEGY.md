# Polymorphic Language Strategy

Status: active architecture strategy
Scope: language placement rules for Latticra, Lat, LIR, Latticra Seal, C, C++, and Rust. This document does not implement runtime execution, runtime authority, policy enforcement, cryptographic verification, operating-system behavior, production readiness, or external endorsement.

## Purpose

Latticra should be polymorphic in its use of programming languages without becoming undisciplined.

The project should use each language where it is strongest, keep cross-language interfaces explicit, and avoid language ideology. The goal is a serious systems architecture where C, constrained C++, Rust, Lat, and LIR each have a bounded role.

## Core rule

```text
C owns the substrate.
C++ owns governed architecture and policy modeling.
Rust owns safe tooling and high-risk input surfaces.
Lat owns Latticra-native declaration and system intent.
LIR owns bounded intermediate representation and evidence-bearing shape.
```

## C role

C is the substrate language for Latticra.

Use C for:

```text
stable ABI boundaries
small no-effect runtime primitives
state and boundary fixtures
Lat-to-LIR lowering foundations
LIR shape and metadata surfaces
runtime-boundary classification
Seal metadata structs
capability records
evidence receipts
host-neutral invariant tests
```

C code should remain small, auditable, deterministic, and boring. It should not hide policy complexity, own broad orchestration, or become a dumping ground for every subsystem.

## C++ role

Constrained C++ is the architecture and policy language for Latticra.

Use C++ for:

```text
policy graph modeling
capability graph modeling
Seal decision modeling
tool-boundary planning
Lat semantic architecture experiments
higher-order validation engines
audit and planning reports
future bounded architecture simulators
```

C++ must remain governed by the existing constrained C++ authority-layer direction. It should not bypass C effect gates, grant runtime authority, execute tools, perform host mutation, perform network behavior, or introduce unrestricted ownership and allocation patterns.

## Rust role

Rust is the safety-focused tooling and verification language for Latticra.

Use Rust for:

```text
CLI tooling
manifest parsing
evidence report generation
signature metadata tooling
future cryptographic verification wrappers
serialization and deserialization
untrusted input handling
safe developer tools
future network-facing user-space tools
```

Rust should not be used to erase the C/C++ architecture. It should protect risky input surfaces and developer-facing tools where memory safety and parser safety are especially valuable.

## Lat role

Lat is the Latticra-native language direction.

Use Lat for:

```text
system declarations
capability annotations
Seal intent declarations
policy-aware function shape
runtime-boundary descriptions
future Latticra-native system contracts
```

Lat is not currently a compiler product, interpreter product, execution engine, production language, or operating-system replacement layer. Its current valid path is parsing, semantic validation, diagnostics, metadata lowering, and no-effect LIR representation.

## LIR role

LIR is the bounded intermediate representation.

Use LIR for:

```text
Lat declaration shape
metadata-bearing graph representation
operator-visible reports
semantic lowering evidence
no-effect transition between language and runtime-boundary planning
```

LIR should remain evidence-bearing and bounded before execution is considered.

## Boundary interface policy

Cross-language boundaries should use explicit contracts.

Preferred boundary shape:

```text
plain C ABI
fixed-capacity structs where practical
explicit ownership
explicit error codes
no hidden runtime dependency
no implicit authority grant
no effect without a named gate
```

Every new cross-language boundary must name:

1. caller language;
2. callee language;
3. ownership rules;
4. error behavior;
5. effect posture;
6. authority posture;
7. test or guard path.

## Layer map

```text
Lat
  declaration and system intent layer

LIR
  bounded metadata and intermediate representation layer

C substrate
  ABI, fixtures, no-effect primitives, runtime-boundary records

Constrained C++
  policy graph, authority planning, capability graph, decision models

Rust tools
  safe CLI, manifest parsing, evidence processing, verification wrappers

Fedora/Linux
  current host-facing validation lane and integration target
```

## Non-claims

This strategy does not claim:

```text
Rust implementation present for all named Rust areas
C++ implementation present for all named C++ areas
Lat execution
LIR execution
runtime authority
policy enforcement
cryptographic verification
tool execution
MCP implementation
production readiness
operating-system replacement
```

## Implementation rule

A language should be introduced into a subsystem only when that subsystem has a contract, a boundary, and a test path.

The acceptable question is not "which language is best overall?"

The acceptable question is:

```text
Which language is safest, clearest, and most auditable for this specific layer?
```
