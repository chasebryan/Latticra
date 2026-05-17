# Latticra Upcoming Work

Status: active project note
Last updated: 2026-05-16 16:15 CDT

## Latest completed planning slice

```text
Constrained C++ authority layer implementation plan
```

Purpose completed:

```text
define exact public API, namespace, file paths, C++ standard, compiler flags, exception policy, RTTI policy, allocation policy, ownership/lifetime rules, result labels, C ABI boundaries, validators, audit reports, and tests before any C++ authority-layer code
```

## Recommended next slice

```text
Constrained C++ authority layer implementation
```

Purpose:

```text
implement the first no-effect constrained C++ authority layer using the guarded implementation plan, with explicit API, fixed-capacity audit reporting, Lat metadata validation, LIR metadata validation, effect classification without performing effects, and invariant tests
```

## Near-term queue

1. Constrained C++ authority layer implementation.
2. L-UI rendering contract.
3. Nucleus task execution contract.
4. Runtime boundary contract.
5. Defensive threat model contract.
6. Public status update after major milestones.
7. Completion percentage review after constrained C++ authority-layer implementation planning.
8. Strategy estimate review after constrained C++ authority-layer implementation planning.
9. LIR-to-Lat relationship review after Lat grammar parser stabilization.
10. C++ authority implementation review after initial no-effect validator/audit slice.

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
- Move from constrained C++ authority-layer implementation planning into no-effect implementation.
- Maintain professional public docs.
- Keep status and completion estimates current.
- Keep security ambitions framed as mission and design targets until proven.
- Keep Lat metadata-only until separate lowering or execution contracts exist.
- Keep C++ constrained by the governed authority-layer implementation plan.
