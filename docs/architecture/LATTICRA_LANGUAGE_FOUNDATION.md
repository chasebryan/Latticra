# Latticra Language Foundation

Status: Draft  
Layer: Architecture  
Applies to: Latticra core, trusted runtime design, language substrate, security-facing documentation.

## 1. Direction

Latticra is moving toward a constrained C/C++ foundation.

The goal is not to use C/C++ casually. The goal is to use C and C++ in a disciplined, security-governed form suitable for a low-level, contract-driven systems project.

The intended stack is:

```text
Latticra
├── Latticra contract language
│   ├── declarations
│   ├── policies
│   ├── validation forms
│   ├── system descriptions
│   └── human-facing control surfaces
│
├── Restricted C++ governed authority layer
│   ├── Nucleus logic
│   ├── state lattice transitions
│   ├── policy objects
│   ├── validators
│   ├── effect gates
│   ├── audit records
│   └── typed resource ownership
│
├── C secure substrate
│   ├── boot paths
│   ├── ABI boundaries
│   ├── platform shims
│   ├── fixed-layout structures
│   ├── freestanding runtime support
│   └── hardware-facing interfaces
│
└── platform-specific assembly or firmware interfaces
```

Core phrase:

> C is the metal. C++ is the disciplined structure. Latticra is the contract.

## 2. Rationale

Latticra requires:

- deep platform control;
- clear ABI boundaries;
- freestanding and low-level implementation paths;
- audit-visible security transitions;
- explicit trust boundaries;
- long-lived independence from unnecessary dependency churn;
- predictable integration with boot, hardware, runtime, and toolchain surfaces.

C gives Latticra a narrow, stable substrate for platform-facing interfaces.

C++ gives Latticra stronger structure above that substrate when it is constrained by project rules: RAII, typed ownership, value objects, explicit status returns, validators, and policy types.

The Latticra contract language sits above both layers and expresses declarations, authority boundaries, policy intent, and system-visible commitments.

## 3. Non-goals

This direction does not mean:

- unrestricted C++ is acceptable;
- large dependency graphs are acceptable;
- raw pointer ownership is acceptable in trusted core code;
- unchecked buffer behavior is acceptable;
- undefined behavior is an acceptable engineering cost;
- memory safety concerns are dismissed;
- marketing claims can outrun evidence.

Latticra must remain honest about C/C++ risk. Security must come from architecture, review, tooling, tests, and narrow boundaries.

## 4. Architectural roles

### 4.1 C secure substrate

C is limited to substrate responsibilities:

- boot entry and early runtime;
- C ABI exposure;
- platform shims;
- fixed-layout interop structures;
- minimal hardware-facing interfaces;
- freestanding runtime helpers;
- thin wrappers over platform-specific mechanisms.

C should not own high-level policy decisions unless no higher layer exists yet.

### 4.2 Restricted C++ governed authority layer

Restricted C++ owns the higher structure:

- Nucleus supervision;
- state lattice logic;
- typed security transitions;
- effect gate dispatch;
- validators;
- audit trail assembly;
- resource ownership;
- capability objects;
- policy evaluation;
- deterministic failure handling.

C++ code in this layer must follow the Latticra C/C++ Security Profile.

### 4.3 Latticra contract language

The Latticra language expresses system intent above the implementation foundation.

It should describe:

- what authority exists;
- what transitions are allowed;
- what validation must occur;
- what evidence is required;
- what effects may be attempted;
- what audit record must be produced;
- what failure state is safe.

The contract language should never hide unsafe behavior. It should make authority visible.

## 5. Security posture

Latticra treats unsafe power as explicit.

Every privileged action should pass through these conceptual stages:

```text
request
  -> parse
  -> validate
  -> authorize
  -> effect gate
  -> execute
  -> audit
  -> report
```

The central design rule:

> No privileged mutation without validation, authorization, effect gating, and audit visibility.

## 6. Layer boundaries

Layer boundaries should be treated as security boundaries.

| Boundary | Rule |
|---|---|
| Latticra language -> C++ | Contracts must be parsed, validated, and transformed into typed policy objects. |
| C++ -> C | No ownership, lifetime, or unchecked mutable buffer may cross implicitly. |
| C -> platform | Platform-specific code must be isolated, documented, and reviewable. |
| Any layer -> privileged effect | Must pass through an effect gate. |

## 7. Naming recommendations

Suggested terms for public/project documentation:

- `Secure Substrate` for the C layer.
- `Governed Authority Layer` for the restricted C++ layer.
- `Contract Language` for the Latticra language layer.
- `Effect Gate` for controlled privileged action paths.
- `Evidence-bound validation` for claims that require testable proof.
- `Nucleus` for the core supervisory authority.

## 8. Public wording

Preferred:

> Latticra uses a minimal C substrate for ABI, boot, and platform-facing interfaces, with a constrained C++ authority layer above it for policy, validation, effect gates, audit logic, and typed security transitions.

Avoid:

> C++ makes Latticra secure.

Better:

> Latticra uses constrained C/C++ with explicit security contracts, narrow unsafe boundaries, build hardening, static analysis, sanitizer testing, fuzzing, and evidence-bound validation.

## 9. Current status language

Use this status language until implementation evidence exists:

> This direction is architectural and preparatory. It defines the intended foundation and security posture. It is not yet a completed hardened implementation.

## 10. Acceptance criteria

This architecture can be considered ready for implementation work when:

- the C/C++ Security Profile exists and is checked into the repo;
- ABI boundary rules are documented;
- build flags and analyzer expectations are documented;
- a roadmap exists for staged migration or implementation;
- public wording avoids unsupported security claims;
- early tests enforce at least some documentation invariants.
