# Latticra Upcoming Work

Status: active project note
Last updated: 2026-05-16 16:15 CDT

## Previous planning slice

```text
Constrained C++ authority layer implementation plan
```

Purpose completed:

```text
define exact public API, namespace, file paths, C++ standard, compiler flags, exception policy, RTTI policy, allocation policy, ownership/lifetime rules, result labels, C ABI boundaries, validators, audit reports, and tests before any C++ authority-layer code
```

## Latest completed contract slice

```text
L-UI rendering contract
```

Purpose completed:

```text
define the first contract for rendering validated L-UI/LIR metadata into operator-visible output without execution, mutation, network behavior, recovery behavior, hardware behavior, or production UI claims
```

## Latest completed planning slice

```text
L-UI rendering implementation plan
```

Purpose completed:

```text
define exact public API, header path, source path, render request struct, render result struct, render mode enum, render error enum, capacity constants, output buffer rules, section order, source-span rendering rules, embedded NUL rendering rules, authority metadata rendering rules, exact tests, compatibility expectations, and non-claims before renderer code
```

## Latest completed implementation slice

```text
Constrained C++ authority layer implementation
```

Purpose completed:

```text
implement the first no-effect constrained C++ authority layer using the guarded implementation plan, with explicit API, fixed-capacity audit reporting, Lat metadata validation, LIR metadata validation, effect classification without performing effects, and invariant tests
```

## Recommended next slice

```text
L-UI rendering implementation
```

Purpose:

```text
implement the first no-effect C L-UI renderer using the guarded implementation plan, with explicit API, caller-provided buffers, deterministic report output, semantic/LIR/authority prerequisites, source-span rendering, length-aware text rendering, and invariant tests
```

## Near-term queue

1. L-UI rendering implementation.
2. Nucleus task execution contract.
3. Runtime boundary contract.
4. Defensive threat model contract.
5. Public status update after major milestones.
6. Completion percentage review after L-UI rendering implementation.
7. Strategy estimate review after L-UI rendering implementation.
8. C++ authority implementation review after initial no-effect validator/audit slice.
9. Rendering-to-Nucleus boundary review before any task execution contract.
10. L-UI rendering detailed report refinement after initial renderer implementation.

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
- Move next into L-UI rendering implementation.
- Maintain professional public docs.
- Keep status and completion estimates current.
- Keep security ambitions framed as mission and design targets until proven.
- Keep Lat metadata-only until separate lowering or execution contracts exist.
- Keep C++ constrained by the governed authority-layer implementation plan.
