# Latticra Current Direction

Status: active project note
Last updated: 2026-05-18 18:15 CDT
Latest Lat pipeline note: 2026-05-18 19:40 CDT

## Current direction

Latticra is being built as a contract-first open systems architecture and programming-language project.

The public direction is:

```text
open source
auditable
defensive
contract-driven
evidence-bound
operator-visible
security-conscious from the beginning
constrained C/C++ foundation
```

## C/C++ foundation checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Meaning:

```text
C: secure substrate, boot paths, ABI boundaries, platform shims.
C++: governed authority layer, policy, validators, effect gates, audit logic.
Lat / Latticra Language: contract, semantic validation, metadata lowering, and declaration layer.
```

This does not mean unrestricted C++.

## Current Lat language boundary

The Lat lane now has:

```text
bounded grammar parser
bounded no-effect semantic validation
bounded no-effect Lat-to-LIR metadata lowering
bounded no-effect Lat pipeline reporting
bounded no-effect Lat-specific LIR refinement
```

The current Lat-to-LIR lowering implementation consumes parser and semantic metadata, creates a `lat_module` LIR shape, preserves source spans and no-effect flags, and emits deterministic lowering reports.

The current Lat pipeline composes Lat source parsing, semantic validation, Lat-to-LIR lowering, LIR metadata, and deterministic pipeline reporting into one no-effect integration path.

The current Lat-specific LIR refinement makes Lat declarations and transition-source edges explicit in LIR while preserving source spans, counts, and no-effect flags.

It does not provide Lat execution, Lat interpretation, Lat compilation, LIR execution, runtime behavior, command execution, state mutation, file I/O, network I/O, recovery behavior, hardware behavior, or operating-system behavior.

## Current C++ authority boundary

The C++ authority layer is contract-bound, implementation-plan-bound, and represented by its first no-effect implementation slice.

Planning milestone preserved:

```text
Constrained C++ authority layer implementation plan
```

It currently implements no-effect authority behavior only:

```text
explicit status labels
explicit effect labels
explicit validator labels
fixed-capacity audit records
Lat parse-result metadata validation
LIR shape metadata validation
effect classification without performing effects
deterministic authority report rendering
```

The implementation does not provide unrestricted C++ authority, an effect-performing implemented C++ authority layer, runtime execution, mutation authority, file authority, network authority, recovery authority, hardware authority, or production security guarantees.

## Current L-UI rendering boundary

The L-UI rendering lane has a contract, implementation plan, and first no-effect C implementation.

The current renderer provides deterministic operator-visible text reports over already validated L-UI/LIR metadata and a C-compatible authority summary.

It does not provide terminal control, interactive UI behavior, command behavior, Lat execution, LIR execution, Nucleus effect execution, mutation, file I/O, network I/O, recovery behavior, hardware behavior, or production UI claims.

## Current Nucleus task boundary

The Nucleus task execution lane has a contract, implementation plan, and first no-effect C classification/report implementation.

The current implementation provides denied-by-default task classification and deterministic task reports with explicit request kinds, effects, policies, denial reasons, authority metadata, preview prerequisites, and no-effect flags.

It does not implement effect-performing Nucleus task execution, command behavior, mutation, network behavior, recovery behavior, hardware behavior, boot behavior, rollback, or production runtime claims.

## Current runtime boundary

The runtime boundary lane now has a contract, implementation plan, and initial no-effect C API/report surface.

Planning milestone preserved:

```text
Runtime boundary implementation plan
```

The current implementation adds the public runtime boundary header, source file, smoke invariants, report entry point, implementation record, and dedicated runtime-boundary workflow. It establishes a compileable boundary surface while preserving a disabled-by-default posture.

It does not implement effect-performing runtime behavior, command execution, Lat execution, LIR execution, task effect execution, mutation, file I/O, network I/O, recovery behavior, rollback, hardware behavior, boot behavior, terminal control, sandboxing, or production runtime claims.

## Mission target

The long-term mission is to build a complete open-source operating-system universe and programming-language stack that makes unsafe behavior harder to hide and easier to inspect.

This includes long-term defensive goals against malware, ransomware, unauthorized persistence, hidden mutation, unclear execution, and opaque system behavior.

## Target users

Primary target users include:

- intellectuals;
- scientists;
- computer scientists;
- security researchers;
- defensive engineering teams;
- infrastructure maintainers;
- government infrastructure stakeholders.

## Current technical lane

The current technical lane is moving from the L-UI parser, AST, source-policy, diagnostic, semantic validation, LIR shape foundation, Lat parser foundation, Lat semantic validation foundation, Lat-to-LIR lowering contract, Lat-to-LIR lowering implementation plan, first no-effect Lat-to-LIR lowering implementation, first no-effect Lat pipeline implementation, C/C++ foundation direction, constrained C++ authority-layer contract, constrained C++ authority-layer implementation plan, first no-effect C++ authority implementation, L-UI rendering contract, L-UI rendering implementation plan, first no-effect L-UI renderer implementation, Nucleus task execution contract, Nucleus task execution implementation plan, first no-effect Nucleus task classification/report implementation, runtime boundary contract, runtime boundary implementation plan, and initial runtime boundary API/smoke implementation toward runtime boundary refinement planning.

The next recommended implementation lane is:

```text
Runtime boundary refinement plan
```

## Current non-claim

Latticra does not currently prevent malware or ransomware, provide a hardened sandbox, replace an operating system, provide unrestricted C++ authority, provide an effect-performing C++ authority layer, provide effect-performing Nucleus task execution, provide effect-performing runtime behavior, provide command execution, provide interactive L-UI rendering, provide terminal-control L-UI rendering, provide a Lat runtime, provide Lat execution, provide LIR execution, or provide a production security boundary.

Those are long-term goals and design targets, not current claims.
