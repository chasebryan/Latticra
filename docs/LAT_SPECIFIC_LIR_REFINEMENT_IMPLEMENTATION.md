# Latticra Lat-Specific LIR Refinement Implementation

Status: initial implementation contract
Scope: first explicit Lat declaration node kinds and transition-source edge kind in LIR.

## Purpose

This slice implements the first Lat-specific LIR refinement after the parser, semantic validator, Lat-to-LIR lowering layer, and Lat pipeline foundation.

The refinement makes Lat declaration roles visible in LIR without changing the no-effect posture or introducing execution behavior.

## Added behavior

Lat-to-LIR lowering now emits explicit node kinds for:

```text
state declarations
policy declarations
transition declarations
assertion declarations
effect declarations
require / ensure clauses
```

Transition source references now use an explicit:

```text
transitions_from
```

edge kind.

The later Lat-to-LIR clause metadata refinement preserves clause operators in the LIR node `operator_text` field while keeping role labels in the existing node binding field.

## Validation

Run:

```sh
sh scripts/test-lat-specific-lir-refinement.sh
```

The test covers stable labels, declaration node kind mapping, requirement node mapping, transition-source edge mapping, counts, and no-effect preservation.

Related operator metadata is covered by:

```sh
sh scripts/test-lat-to-lir-clause-metadata-refinement.sh
```

## Boundary

This implementation remains metadata-only. It does not execute Lat or LIR, interpret transition behavior, mutate state, perform effects, call Nucleus, call runtime code, or perform host operations.

## Compatibility

Existing generic LIR node and edge values are preserved. L-UI LIR lowering remains generic and unchanged.

## Non-claims

This implementation does not provide a Lat compiler, Lat interpreter, Lat runtime, LIR executor, command system, task executor, production runtime, security boundary, malware prevention guarantee, ransomware prevention guarantee, certification, accreditation, or operating-system replacement.
