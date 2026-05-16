# Latticra C/C++ Foundation Roadmap

Status: Draft  
Layer: Roadmap  
Scope: Documentation-first implementation plan for the constrained C/C++ direction.

## 1. Purpose

This roadmap defines the staged path for turning the Latticra C/C++ direction into an implementation foundation.

The goal is to avoid rushing into code before the architecture, security profile, and validation expectations are clear.

## 2. Phase 0 — Documentation lock

Objective: Establish the direction before implementation.

Tasks:

- [ ] Add `docs/latticra/DOCUMENTATION_MAP.md`.
- [ ] Add `docs/architecture/LATTICRA_LANGUAGE_FOUNDATION.md`.
- [ ] Add `docs/security/C_CPP_SECURITY_PROFILE.md`.
- [ ] Add `docs/security/C_ABI_BOUNDARY_POLICY.md`.
- [ ] Add this roadmap.
- [ ] Ensure public wording avoids unsupported security claims.
- [ ] Record the official phrase: `C is the metal. C++ is the disciplined structure. Latticra is the contract.`

Exit criteria:

- docs are committed;
- docs are internally consistent;
- future implementation can reference these docs.

## 3. Phase 1 — Repository structure

Objective: Prepare the codebase layout without overbuilding.

Candidate layout:

```text
latticra/
├── docs/
│   ├── architecture/
│   ├── security/
│   ├── roadmap/
│   └── latticra/
├── include/
│   └── latticra/
│       └── latticra.h
├── src/
│   ├── c_substrate/
│   ├── cpp_authority/
│   ├── nucleus/
│   ├── contract/
│   ├── audit/
│   └── platform/
├── tests/
│   ├── abi/
│   ├── contract/
│   ├── security/
│   └── docs/
└── tools/
```

Tasks:

- [ ] Create minimal include/source directories.
- [ ] Create placeholder C ABI header.
- [ ] Create placeholder C++ authority module.
- [ ] Add build system skeleton.
- [ ] Add documentation integrity tests if project test framework exists.

Exit criteria:

- clean empty build or placeholder build;
- no fake security claims;
- C/C++ boundaries named clearly.

## 4. Phase 2 — C ABI skeleton

Objective: Create the narrow public C-facing substrate.

Tasks:

- [ ] Define `latticra_status`.
- [ ] Define opaque `latticra_handle`.
- [ ] Define `latticra_bytes`.
- [ ] Define create/destroy lifecycle.
- [ ] Define validation entry point.
- [ ] Add null pointer tests.
- [ ] Add buffer length tests.
- [ ] Add invalid input tests.
- [ ] Document every ABI function.

Exit criteria:

- ABI does not expose internal C++ types;
- no ownership crosses implicitly;
- invalid inputs fail deterministically.

## 5. Phase 3 — Restricted C++ authority core

Objective: Build the first governed authority objects.

Candidate objects:

```text
Nucleus
ContractInput
ValidatedContract
EffectContext
EffectGate
AuditRecord
LatticraError
Result<T, E>
```

Tasks:

- [ ] Add `Result<T, E>` or equivalent.
- [ ] Add typed error enum.
- [ ] Add immutable validated contract object.
- [ ] Add effect gate stub.
- [ ] Add audit record stub.
- [ ] Add tests for denied, invalid, and accepted paths.
- [ ] Avoid raw owning pointers.
- [ ] Avoid exceptions across ABI.

Exit criteria:

- C ABI wraps C++ authority logic;
- policy decisions live above C substrate;
- audit path exists even if minimal.

## 6. Phase 4 — Contract language preparation

Objective: Prepare Latticra contract parsing and validation.

Tasks:

- [ ] Define smallest contract syntax or data model.
- [ ] Separate parse from validation.
- [ ] Reject malformed input.
- [ ] Reject unsupported declarations.
- [ ] Convert accepted input into typed validated objects.
- [ ] Add fuzzing target for parser when practical.
- [ ] Add tests for malformed, oversized, and boundary inputs.

Exit criteria:

- raw contract input never directly drives privileged behavior;
- only validated contract objects enter authority logic.

## 7. Phase 5 — Effect gates and audit trail

Objective: Make privileged mutation visible and governed.

Tasks:

- [ ] Define effect categories.
- [ ] Define authorization context.
- [ ] Define denied behavior.
- [ ] Define audit record format.
- [ ] Add tests for denied effects.
- [ ] Add tests for accepted effects.
- [ ] Add tests confirming audit output exists.

Exit criteria:

- every privileged mutation path has an effect gate;
- every security-relevant gate produces audit evidence.

## 8. Phase 6 — Tooling and hardening

Objective: Make the security profile enforceable.

Tasks:

- [ ] Add strict compiler warnings.
- [ ] Add sanitizer build mode where supported.
- [ ] Add static analysis target where supported.
- [ ] Add clang-tidy config where supported.
- [ ] Add fuzz target for parsers.
- [ ] Add dependency review notes.
- [ ] Add unsafe exception template to PR/review process.

Exit criteria:

- build/test path catches common C/C++ errors early;
- exceptions are documented rather than hidden.

## 9. Phase 7 — Public evidence and status

Objective: Align public claims with real evidence.

Tasks:

- [ ] Add public status document.
- [ ] List supported platforms honestly.
- [ ] List unsupported platforms honestly.
- [ ] List security work completed.
- [ ] List security work still planned.
- [ ] Avoid claiming hardened status before validation.

Exit criteria:

- public communication reflects actual implementation state;
- no security marketing outruns the evidence.

## 10. Initial milestone recommendation

Recommended first milestone:

```text
Milestone: latticra-foundation-docs-v0.1
Scope:
  - documentation map
  - language foundation doc
  - C/C++ security profile
  - C ABI boundary policy
  - roadmap
No implementation claims.
```

Recommended commit message:

```text
Add Latticra C/C++ foundation documentation
```

## 11. Risk register

| Risk | Mitigation |
|---|---|
| Unrestricted C++ enters trusted core | Enforce C/C++ Security Profile and review labels. |
| C substrate grows too large | Keep C limited to ABI, platform, and boot substrate. |
| ABI carries unsafe lifetime assumptions | Require opaque handles, explicit buffer lengths, and status codes. |
| Security claims outrun implementation | Use evidence-bound promotion rule. |
| Dependency graph grows uncontrolled | Require dependency review. |
| Parser becomes attack surface | Separate parse/validate, add fuzzing, reject malformed input. |
| Platform-specific code contaminates generic core | Isolate platform code under dedicated directories. |

## 12. Definition of done for the direction

This direction is ready for deeper implementation when:

- the docs are committed;
- the repo structure reflects the layer model;
- the first ABI skeleton exists;
- the first C++ authority object exists;
- security profile rules are visible in review;
- tests exist for invalid input and boundary cases;
- public messaging remains precise and evidence-bound.
