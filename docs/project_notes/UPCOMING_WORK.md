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
Nucleus task execution contract
```

Purpose completed:

```text
define the first contract for future Nucleus task execution boundaries, prerequisites, authority checks, no-effect defaults, denial behavior, report surfaces, exact future tests, compatibility expectations, and non-claims before any task execution code
```

## Previous contract slice

```text
L-UI rendering contract
```

Purpose completed:

```text
define the first contract for rendering validated L-UI/LIR metadata into operator-visible output without execution, mutation, network behavior, recovery behavior, hardware behavior, or production UI claims
```

## Latest completed planning slice

```text
Nucleus task execution implementation plan
```

Purpose completed:

```text
define exact public API, C implementation files, task request/result/record structs, policy enum, denial enum, effect-gate enum usage, authority summary usage, operator-confirmation metadata, rollback metadata, report format, capacity constants, output-buffer behavior, exact tests, compatibility expectations, and non-claims before Nucleus task execution code
```

## Previous planning slice

```text
L-UI rendering implementation plan
```

Purpose completed:

```text
define exact public API, header path, source path, render request struct, render result struct, render mode enum, render error enum, capacity constants, output buffer rules, section order, source-span rendering rules, embedded NUL rendering rules, authority metadata rendering rules, exact tests, compatibility expectations, and non-claims before renderer code
```

## Latest completed implementation slice

```text
Nucleus task execution implementation
```

Purpose completed:

```text
implement the first no-effect C Nucleus task classification/report surface using the guarded implementation plan, with explicit API, denied-by-default policy, authority prerequisites, effect-gate metadata, caller-provided buffers, deterministic reports, and invariant tests
```

## Previous implementation slice

```text
L-UI rendering implementation
```

Purpose completed:

```text
implement the first no-effect C L-UI renderer using the guarded implementation plan, with explicit API, caller-provided buffers, deterministic report output, semantic/LIR/authority prerequisites, source-span rendering, length-aware text rendering, and invariant tests
```

## Earlier implementation slice

```text
Constrained C++ authority layer implementation
```

Purpose completed:

```text
implement the first no-effect constrained C++ authority layer using the guarded implementation plan, with explicit API, fixed-capacity audit reporting, Lat metadata validation, LIR metadata validation, effect classification without performing effects, and invariant tests
```

## Recommended next slice

```text
Runtime boundary contract
```

Purpose:

```text
define the first runtime boundary contract before any runtime behavior, including allowed surfaces, denied effects, execution limits, authority prerequisites, task prerequisites, report expectations, future files, exact tests, compatibility expectations, and non-claims
```

## Near-term queue

1. Runtime boundary contract.
2. Defensive threat model contract.
3. Runtime boundary implementation plan after the runtime boundary contract is merged.
4. Public status update after major milestones.
5. Completion percentage review after Nucleus task execution implementation.
6. Strategy estimate review after Nucleus task execution implementation.
7. C++ authority implementation review after initial no-effect validator/audit slice.
8. Rendering-to-Nucleus boundary review after task execution implementation.
9. L-UI rendering detailed report refinement after initial renderer implementation.
10. Nucleus task execution refinement only after runtime boundary contract.

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
- Move next into runtime boundary contract planning.
- Maintain professional public docs.
- Keep status and completion estimates current.
- Keep security ambitions framed as mission and design targets until proven.
- Keep Lat metadata-only until separate lowering or execution contracts exist.
- Keep C++ constrained by the governed authority-layer implementation plan.
