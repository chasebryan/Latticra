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
Lat semantic validation contract
```

Purpose completed:

```text
define the first semantic validation boundary after bounded Lat grammar parsing, including declaration identity, transition source resolution, state-field vocabulary, effect metadata, clause validation, no-effect preservation, deterministic reports, and non-claims
```

## Previous contract slice

```text
Runtime boundary contract
```

Purpose completed:

```text
define the first runtime boundary contract before any runtime behavior, including allowed surfaces, denied effects, execution limits, authority prerequisites, task prerequisites, report expectations, future files, exact tests, compatibility expectations, and non-claims
```

## Earlier contract slice

```text
Nucleus task execution contract
```

Purpose completed:

```text
define the first contract for future Nucleus task execution boundaries, prerequisites, authority checks, no-effect defaults, denial behavior, report surfaces, exact future tests, compatibility expectations, and non-claims before any task execution code
```

## Latest completed planning slice

```text
Lat semantic validation implementation plan
```

Purpose completed:

```text
define exact public API, result structs, diagnostics, validation rules, report surface, fixture, tests, compatibility expectations, and non-claims before semantic validation code
```

## Previous planning slice

```text
Runtime boundary implementation plan
```

Purpose completed:

```text
define exact public API, header path, source path, runtime request struct, runtime record struct, runtime result struct, runtime mode enum, runtime policy enum, runtime denial enum, authority summary usage, Nucleus task result usage, effect-gate state usage, operator-confirmation metadata, report format, capacity constants, output-buffer behavior, exact tests, compatibility expectations, and non-claims before runtime boundary code
```

## Earlier planning slice

```text
Nucleus task execution implementation plan
```

Purpose completed:

```text
define exact public API, C implementation files, task request/result/record structs, policy enum, denial enum, effect-gate enum usage, authority summary usage, operator-confirmation metadata, rollback metadata, report format, capacity constants, output-buffer behavior, exact tests, compatibility expectations, and non-claims before Nucleus task execution code
```

## Latest completed implementation slice

```text
Lat semantic validation foundation
```

Purpose completed:

```text
add the first bounded no-effect C semantic validation layer after the Lat grammar parser, with declaration identity checks, transition source resolution, state-field vocabulary checks, effect-target checks, effect-value checks, no-effect preservation, deterministic reports, fixture coverage, invariant tests, and CI coverage
```

## Previous implementation slice

```text
Runtime boundary implementation
```

Purpose completed:

```text
add the first C runtime boundary public API, compileable source surface, smoke invariants, dedicated test runner, dedicated workflow, and implementation record while preserving disabled-by-default runtime behavior
```

## Earlier implementation slice

```text
Nucleus task execution implementation
```

Purpose completed:

```text
implement the first no-effect C Nucleus task classification/report surface using the guarded implementation plan, with explicit API, denied-by-default policy, authority prerequisites, effect-gate metadata, caller-provided buffers, deterministic reports, and invariant tests
```

## UI implementation slice

```text
L-UI rendering implementation
```

Purpose completed:

```text
implement the first no-effect C L-UI renderer using the guarded implementation plan, with explicit API, caller-provided buffers, deterministic report output, semantic/LIR/authority prerequisites, source-span rendering, length-aware text rendering, and invariant tests
```

## Recommended next slice

```text
Lat-to-LIR lowering contract
```

Purpose:

```text
define the first Lat-to-LIR lowering boundary after grammar parsing and semantic validation, including semantic prerequisites, LIR node and edge mapping, source-span preservation, effect preservation, diagnostics, reports, compatibility requirements, and non-claims before any lowering code
```

## Near-term queue

1. Lat-to-LIR lowering contract.
2. Lat-to-LIR lowering implementation plan.
3. Lat normalized module model contract.
4. Runtime boundary refinement.
5. Public status update after major milestones.
6. Completion percentage review after Lat-to-LIR contract.
7. Strategy estimate review after Lat semantic validation foundation.
8. C++ authority implementation review after initial no-effect validator/audit slice.
9. L-UI rendering detailed report refinement after initial renderer implementation.
10. Nucleus task execution refinement only after the next language-lowering contract.

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
- Move next into Lat-to-LIR lowering contract planning.
- Maintain professional public docs.
- Keep status and completion estimates current.
- Keep Lat metadata-only until separate lowering or execution contracts exist.
- Keep C++ constrained by the governed authority-layer implementation plan.
