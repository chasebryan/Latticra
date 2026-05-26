# Latticra C/C++ Security Profile

Status: Draft  
Layer: Security  
Applies to: C substrate, restricted C++ governed authority layer, trusted core code.

## 1. Purpose

This document defines the required C/C++ security profile for Latticra.

Latticra may use C and C++ only under a restricted profile. This profile exists because C and C++ allow unsafe behavior unless the project explicitly prevents, isolates, or reviews that behavior.

The goal is not to pretend C/C++ is memory-safe by default. The goal is to establish a disciplined systems profile with narrow unsafe zones, explicit review, hard tooling, and evidence-bound validation.

## 2. Core posture

Latticra follows these principles:

1. C is the narrow substrate.
2. C++ is the governed authority layer.
3. Unsafe behavior is isolated and documented.
4. Ownership is explicit.
5. Lifetime is explicit.
6. Buffer boundaries are explicit.
7. Effects are gated.
8. Privileged mutation is auditable.
9. External input is validated.
10. Security claims require evidence.

## 2A. Memory-safety roadmap alignment

Latticra aligns its C/C++ posture with current NSA/CISA memory-safe-language guidance and CISA/FBI product-security bad-practice guidance.

This does not mean existing substrate code must be rewritten all at once. It does mean the project must keep a visible memory-safety roadmap and prefer a memory-safe implementation language for new high-risk components.

Required allocation:

```text
memory_safety_roadmap_required=1
memory_safe_language_preferred_for_new_high_risk_components=1
restricted_c_cpp_profile_required_for_existing_substrate=1
unsafe_exception_record_required=1
sanitizer_or_static_analysis_path_required=1
fuzzing_required_before_parser_security_boundary_claim=1
```

High-risk components include:

- network-facing code;
- cryptographic key handling;
- parsers for untrusted external input;
- installer or host-mutation authority;
- update, recovery, rollback, boot, hardware, or agentic automation authority;
- IPC, privilege, capability, or policy-enforcement boundaries.

When a high-risk component remains in C or C++, it must use the restricted profile in this document, keep unsafe behavior isolated, document why a memory-safe alternative is not used, and add targeted tests for malformed input, length boundaries, ownership, lifetime, and failure behavior.

## 3. Allowed C++ patterns in trusted core

The following patterns are preferred:

- RAII for cleanup and resource release;
- value types for simple data transfer;
- `enum class` for typed state and policy names;
- `std::array` where size is static;
- span/view-style APIs for non-owning buffers where available and appropriate;
- `std::unique_ptr` for unique heap ownership when dynamic allocation is permitted;
- explicit `Result<T, E>` or status/error-return types;
- immutable configuration objects after initialization;
- small policy objects with narrow responsibilities;
- typed capability objects;
- deterministic destructors;
- explicit move semantics;
- dependency-free or dependency-minimal modules;
- pure validation functions where possible;
- parser/validator separation.

## 4. Restricted or forbidden C++ patterns in trusted core

The following are forbidden or require explicit review exception:

| Pattern | Status | Reason |
|---|---:|---|
| Raw owning pointers | Forbidden | Ownership must be explicit. |
| `new` / `delete` in ordinary code | Forbidden | Use RAII and approved allocators. |
| Unchecked pointer arithmetic | Forbidden | High memory safety risk. |
| `reinterpret_cast` | Exception-only | Platform or ABI code only, with review notes. |
| C-style casts | Forbidden | Cast intent must be explicit. |
| Exceptions across C ABI or security boundaries | Forbidden | Failure must be explicit and deterministic. |
| RTTI in trusted/freestanding core | Restricted | Avoid hidden runtime assumptions. |
| Hidden global mutable state | Forbidden | Breaks auditability and determinism. |
| Varargs | Forbidden | Type safety and boundary risk. |
| Template metaprogramming for core policy | Restricted | Avoid unreadable authority logic. |
| Complex inheritance trees | Restricted | Prefer composition and final small types. |
| Silent integer narrowing | Forbidden | Must use checked conversion. |
| Unbounded string/buffer operations | Forbidden | Buffer length must be explicit. |
| Large unreviewed dependencies | Forbidden | Dependency trust must be reviewed. |

## 5. Allowed C patterns

C code is allowed only for substrate responsibilities:

- boot and early runtime;
- C ABI surfaces;
- platform shims;
- freestanding helpers;
- fixed-layout interop structs;
- hardware-facing entry points;
- minimal wrappers around platform mechanisms.

C code should be small, boring, and directly reviewable.

## 6. Restricted or forbidden C patterns

The following C patterns are forbidden or exception-only:

| Pattern | Status |
|---|---:|
| Unbounded `strcpy`, `strcat`, `sprintf`, similar APIs | Forbidden |
| Unchecked `memcpy` / `memmove` sizes | Forbidden |
| Implicit ownership transfer through raw pointers | Forbidden |
| Mutable global state | Exception-only |
| Macro-heavy control logic | Restricted |
| Type-punning through incompatible pointers | Exception-only |
| Undocumented inline assembly | Forbidden |
| Platform-specific behavior in generic files | Forbidden |
| Undefined behavior reliance | Forbidden |
| Silent integer truncation | Forbidden |

## 7. Boundary rules

No C/C++ boundary may rely on implicit ownership or lifetime.

Boundary rule set:

```text
No lifetime crosses the C ABI boundary.
No ownership crosses without an explicit handle.
No mutation crosses without an effect gate.
No error crosses without a typed status or result.
No buffer crosses without pointer + length + validation.
No privileged action crosses without audit intent.
```

## 8. Error handling

Trusted code should avoid hidden failure paths.

Preferred:

```text
Result<T, LatticraError>
StatusCode
Expected<T, E>
```

Required behavior:

- all failure states must be explicit;
- no security boundary should throw exceptions across ABI;
- no privileged effect should silently fail;
- user-facing reports must not leak sensitive internals;
- audit records must distinguish denied, invalid, unsupported, and internal error states.

## 9. Allocation policy

Early substrate and platform code should avoid dynamic allocation unless explicitly approved.

C++ authority layer may use dynamic allocation only after allocator policy is defined.

Required allocation posture:

- boot/substrate: no ordinary heap dependency unless explicitly documented;
- trusted core: deterministic allocation preferred;
- no allocation inside critical sections unless justified;
- all ownership must be visible in the type system;
- allocation failure must be handled intentionally.

## 10. Input validation policy

All external input must pass through validation before use.

Examples:

- contract files;
- command input;
- serialized policy data;
- configuration files;
- plugin descriptors;
- platform-reported data;
- filesystem paths;
- network-originated input if networking exists later.

Validation must produce typed output. Downstream authority code should operate on validated types, not raw input.

## 11. Effect gate policy

Any action that mutates system state, opens access, executes code, loads external data, alters policy, or touches hardware-like surfaces must pass through an effect gate.

Effect gate requirements:

- request type;
- caller context;
- validation result;
- authorization decision;
- denied-state behavior;
- audit record;
- bounded effect;
- deterministic return value.

## 12. Dependency policy

Dependencies are not accepted only because they are convenient.

A dependency requires:

- purpose;
- license review;
- build impact review;
- security history review where practical;
- transitive dependency review;
- freestanding compatibility review if applicable;
- replacement/removal plan if the dependency becomes unsuitable.

Trusted core dependencies should be rare.

## 12A. CISA/FBI product-security bad-practice exclusions

The trusted core and future infrastructure surfaces must exclude the following classes unless an explicit exception contract exists:

- no hardcoded default passwords, tokens, or private keys;
- no command injection surface through implicit shells;
- no direct SQL string construction if a database layer is ever introduced;
- no cross-site scripting exposure if web UI or rendered HTML input becomes dynamic;
- no directory traversal in installer, package, update, recovery, or artifact paths;
- no known-insecure or deprecated cryptographic algorithms for production data protection;
- no unmanaged third-party dependency with unknown maintenance or security status;
- no production claim for memory-unsafe high-risk code without a memory-safety roadmap;
- no security release with known exploitable vulnerabilities lacking mitigation notes.

Cryptographic code has an additional rule: production cryptography requires a documented module boundary and a FIPS 140-3 applicability decision before any FIPS, federal, or high-assurance cryptographic claim is allowed.

## 13. Build and analysis expectations

Baseline debug/CI expectations:

```text
-Wall
-Wextra
-Wpedantic
-Wconversion
-Wshadow
-Werror where practical
clang-tidy cppcoreguidelines-* where practical
CERT-oriented static analysis where available
AddressSanitizer where supported
UndefinedBehaviorSanitizer where supported
ThreadSanitizer for concurrent modules where supported
fuzzing for parsers and contract loaders
```

Baseline release expectations:

```text
stack protector where supported
FORTIFY/source hardening where supported
PIE/RELRO/NX/canaries where applicable
LTO only after sanitizer-clean builds
reproducible build notes where practical
no unreviewed unsafe/platform files
```

Tool availability depends on platform and build mode. Unsupported tools must be documented rather than silently ignored.

## 14. Review labels

Suggested code review labels:

- `trusted-core`
- `c-substrate`
- `cpp-authority`
- `abi-boundary`
- `unsafe-exception`
- `effect-gate`
- `parser`
- `validator`
- `audit`
- `platform-specific`
- `dependency-review`

## 15. Unsafe exception template

Any exception to this profile should include:

```text
File:
Function:
Rule being excepted:
Reason:
Why safer alternative is not used:
Scope of unsafe behavior:
How lifetime is bounded:
How buffer size is bounded:
How failure is handled:
Test coverage:
Reviewer:
Date:
```

## 16. Promotion rule

A feature may not be described as secure, hardened, or safe merely because it follows this profile.

A feature can only be promoted with precise evidence:

- tests pass;
- analyzers run or exceptions are documented;
- unsafe exceptions are reviewed;
- parser inputs are fuzzed where relevant;
- ABI boundaries are documented;
- effect gates exist for privileged behavior;
- audit records exist for privileged behavior.
