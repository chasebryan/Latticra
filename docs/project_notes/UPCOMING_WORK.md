# Latticra Upcoming Work

Status: active project note
Last updated: 2026-05-16 16:15 CDT

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
Runtime boundary contract
```

Purpose completed:

```text
define the first runtime boundary contract before any runtime behavior, including allowed surfaces, denied effects, execution limits, authority prerequisites, task prerequisites, report expectations, future files, exact tests, compatibility expectations, and non-claims
```

## Previous contract slice

```text
Nucleus task execution contract
```

Purpose completed:

```text
define the first contract for future Nucleus task execution boundaries, prerequisites, authority checks, no-effect defaults, denial behavior, report surfaces, exact future tests, compatibility expectations, and non-claims before any task execution code
```

## Latest completed planning slice

```text
Runtime boundary implementation plan
```

Purpose completed:

```text
define exact public API, header path, source path, runtime request struct, runtime record struct, runtime result struct, runtime mode enum, runtime policy enum, runtime denial enum, authority summary usage, Nucleus task result usage, effect-gate state usage, operator-confirmation metadata, report format, capacity constants, output-buffer behavior, exact tests, compatibility expectations, and non-claims before runtime boundary code
```

## Previous planning slice

```text
Nucleus task execution implementation plan
```

Purpose completed:

```text
define exact public API, C implementation files, task request/result/record structs, policy enum, denial enum, effect-gate enum usage, authority summary usage, operator-confirmation metadata, rollback metadata, report format, capacity constants, output-buffer behavior, exact tests, compatibility expectations, and non-claims before Nucleus task execution code
```

## Latest completed implementation slice

```text
Runtime boundary implementation
```

Purpose completed:

```text
add the first C runtime boundary public API, compileable source surface, smoke invariants, dedicated test runner, dedicated workflow, and implementation record while preserving disabled-by-default runtime behavior
```

## Previous implementation slice

```text
Nucleus task execution implementation
```

Purpose completed:

```text
implement the first no-effect C Nucleus task classification/report surface using the guarded implementation plan, with explicit API, denied-by-default policy, authority prerequisites, effect-gate metadata, caller-provided buffers, deterministic reports, and invariant tests
```

## Earlier implementation slice

```text
L-UI rendering implementation
```

Purpose completed:

```text
implement the first no-effect C L-UI renderer using the guarded implementation plan, with explicit API, caller-provided buffers, deterministic report output, semantic/LIR/authority prerequisites, source-span rendering, length-aware text rendering, and invariant tests
```

## Recommended next slice

```text
Defensive threat model contract
```

Purpose:

```text
define the first defensive threat model contract for Latticra, including protected assets, assumed adversary capabilities, non-goals, trust boundaries, evidence expectations, abuse-case vocabulary, validation expectations, and non-claims before additional security-facing implementation work
```

## Near-term queue

1. Defensive threat model contract.
2. Runtime boundary refinement.
3. Public status update after major milestones.
4. Completion percentage review after defensive threat model contract.
5. Strategy estimate review after defensive threat model contract.
6. C++ authority implementation review after initial no-effect validator/audit slice.
7. Runtime-to-threat-model boundary review after runtime boundary implementation.
8. L-UI rendering detailed report refinement after initial renderer implementation.
9. Nucleus task execution refinement only after defensive threat model contract.
10. Runtime boundary implementation expansion only after threat model review.

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
- Move next into defensive threat model contract planning.
- Maintain professional public docs.
- Keep status and completion estimates current.
- Keep security ambitions framed as mission and design targets until proven.
- Keep Lat metadata-only until separate lowering or execution contracts exist.
- Keep C++ constrained by the governed authority-layer implementation plan.
