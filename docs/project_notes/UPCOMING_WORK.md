# Latticra Upcoming Work

Status: active project note
Last updated: 2026-05-18 18:15 CDT

## Earlier planning slice

```text
Constrained C++ authority layer implementation plan
```

Purpose completed:

```text
define exact public API, namespace, file paths, C++ standard, compiler flags, exception policy, RTTI policy, allocation policy, ownership/lifetime rules, result labels, C ABI boundaries, validators, audit reports, and tests before any C++ authority-layer code
```

## Latest completed contract slice

```text
Lat-to-LIR lowering contract
```

Purpose completed:

```text
define the first Lat-to-LIR lowering boundary after grammar parsing and semantic validation, including semantic prerequisites, LIR node and edge mapping, source-span preservation, effect preservation, diagnostics, reports, compatibility requirements, and non-claims before any lowering code
```

## Previous contract slice

```text
Lat semantic validation contract
```

Purpose completed:

```text
define the first semantic validation boundary after bounded Lat grammar parsing, including declaration identity, transition source resolution, state-field vocabulary, effect metadata, clause validation, no-effect preservation, deterministic reports, and non-claims
```

## Latest completed planning slice

```text
Lat-to-LIR lowering implementation plan
```

Purpose completed:

```text
define exact public API, files, structs, errors, capacity accounting, node mapping, edge mapping, source-span mapping, report format, tests, compatibility expectations, and non-claims before Lat-to-LIR lowering code
```

## Previous planning slice

```text
Lat semantic validation implementation plan
```

Purpose completed:

```text
define exact public API, result structs, diagnostics, validation rules, report surface, fixture, tests, compatibility expectations, and non-claims before semantic validation code
```

## Latest completed implementation slice

```text
Lat-to-LIR lowering implementation
```

Purpose completed:

```text
add the first bounded no-effect C Lat-to-LIR lowering layer, with parser and semantic prerequisites, lat_module LIR output, source-span preservation, no-effect flag preservation, deterministic lowering reports, invariant tests, and workflow coverage
```

## Previous implementation slice

```text
Lat semantic validation foundation
```

Purpose completed:

```text
add the first bounded no-effect C semantic validation layer after the Lat grammar parser, with declaration identity checks, transition source resolution, state-field vocabulary checks, effect-target checks, effect-value checks, no-effect preservation, deterministic reports, fixture coverage, invariant tests, and CI coverage
```

## Historical implementation slices

```text
Runtime boundary contract
Runtime boundary implementation plan
Runtime boundary implementation
Nucleus task execution contract
Nucleus task execution implementation plan
Nucleus task execution implementation
L-UI rendering implementation
```

## Recommended next slice

```text
Lat-specific LIR refinement plan
```

Purpose:

```text
define whether Lat needs dedicated LIR node or edge kinds beyond the current conservative mapping, including compatibility requirements, report expectations, capacity impact, and non-claims before any enum or shape expansion
```

## Near-term queue

1. Lat-specific LIR refinement plan.
2. Lat-to-LIR implementation documentation/status verification.
3. Public status update after major milestones.
4. Completion percentage review after Lat-to-LIR implementation.
5. Strategy estimate review after Lat semantic validation and lowering foundations.
6. C++ authority implementation review after initial no-effect validator/audit slice.
7. L-UI rendering detailed report refinement after initial renderer implementation.
8. Runtime boundary refinement.
9. Nucleus task execution refinement only after the next language representation review.
10. Defensive threat model validation refinement.

## Quality rules

Upcoming work should remain:

```text
small
reviewable
tested or guarded
evidence-bound
clear about non-claims
consistent with public Latticra identity
consistent with the C/C++ foundation direction
```

## Current project priorities

- Preserve the C/C++ foundation checkpoint: C is the metal, C++ is the disciplined structure, Latticra is the contract.
- Keep the constrained C++ authority layer no-effect until separate effect contracts exist.
- Keep L-UI rendering no-effect and presentation-only.
- Keep Nucleus task execution no-effect and denied-by-default.
- Keep runtime behavior no-effect and disabled-by-default.
- Keep Lat semantic validation no-effect and metadata-only.
- Keep Lat-to-LIR lowering no-effect and metadata-only.
- Move next into Lat-specific LIR refinement planning.
- Maintain professional public docs.
- Keep status and completion estimates current.
- Keep Lat metadata-only until separate execution contracts exist.
- Keep C++ constrained by the governed authority-layer implementation plan.
