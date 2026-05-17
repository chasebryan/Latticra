# Latticra Current Direction

Status: active project note
Last updated: 2026-05-16 16:15 CDT

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
Lat / Latticra Language: contract and declaration layer.
```

This does not mean unrestricted C++.

## Current C++ authority boundary

The C++ authority layer is now contract-bound, implementation-plan-bound, and represented by its first no-effect implementation slice.

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

The current technical lane is moving from the L-UI parser, AST, source-policy, diagnostic, semantic validation, LIR shape foundation, Lat parser foundation, C/C++ foundation direction, constrained C++ authority-layer contract, constrained C++ authority-layer implementation plan, and first no-effect C++ authority implementation toward L-UI rendering contract work.

The next recommended implementation lane is:

```text
L-UI rendering contract
```

## Current non-claim

Latticra does not currently prevent malware or ransomware, provide a hardened sandbox, replace an operating system, provide unrestricted C++ authority, provide an effect-performing implemented C++ authority layer, provide a Lat runtime, or provide a production security boundary.

Those are long-term goals and design targets, not current claims.
