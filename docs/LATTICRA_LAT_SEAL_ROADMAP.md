# Latticra / Lat / Latticra Seal Roadmap

Status: active strategy roadmap
Scope: coordinated planning for Latticra, Lat, LIR, Latticra Seal, C, constrained C++, Rust, Fedora/Linux integration, and AI-era tool-boundary work. This roadmap does not implement runtime execution, operating-system replacement behavior, cryptographic verification, MCP behavior, production enforcement, or production readiness.

## Strategic position

Latticra should advance as an evidence-bound systems substrate and secure computing architecture. Fedora/Linux remains the proving lane. Lat is the native language direction. LIR is the bounded intermediate representation. Latticra Seal is the trust-boundary, request-boundary, capability-boundary, and tool-boundary subsystem.

The roadmap principle is:

```text
evidence first
declarations before execution
reports before authority
allowlist candidates before allow grants
verification before enforcement
Fedora/Linux validation before deeper host claims
```

## Project pillars

```text
Latticra
  Secure systems substrate architecture, runtime-boundary model, Fedora/Linux validation lane, Nucleus coordination, and evidence posture.

Lat
  Latticra-native declaration language for system intent, capability shape, policy-aware declarations, and no-effect lowering into LIR.

LIR
  Bounded intermediate representation with graph shape, metadata, and report evidence before execution.

Latticra Seal
  Trust-boundary and tool-boundary subsystem for signed request planning, freshness metadata, guarded allowlists, capability planning, runtime gates, and evidence receipts.
```

## Language architecture

```text
C
  substrate, ABI, fixtures, state records, LIR/Lat lowering foundations, runtime-boundary records, Seal metadata records, no-effect invariants.

Constrained C++
  architecture and policy modeling, capability graphs, Seal decisions, authority planning, validation engines, bounded audit reports.

Rust
  safe CLI tools, manifest parsing, evidence report generation, signature and verification tooling, serialization, untrusted input handling, future network-facing tools.

Lat
  system declaration and Latticra-native intent.

LIR
  bounded evidence-bearing representation.
```

## Architecture lane

```text
Lat source
  -> parser
  -> semantic validation
  -> diagnostics
  -> LIR metadata lowering
  -> runtime-boundary classification
  -> Seal policy / allowlist / gate metadata
  -> operator-visible evidence report
```

The current valid posture is no-effect and report-oriented. Future execution must be gated by stronger evidence, verification, authority contracts, and explicit promotion rules.

## Phase 1: Integration documentation and guardrails

Goal:

```text
make the roadmap explicit and testable without changing runtime behavior
```

Deliverables:

```text
docs/POLYMORPHIC_LANGUAGE_STRATEGY.md
docs/LATTICRA_LAT_SEAL_ROADMAP.md
docs/LATTICRA_ARCHITECTURE_TARGETS.md
scripts/test-latticra-lat-seal-roadmap.sh
```

Exit criteria:

```text
strategy docs exist
language roles are explicit
non-claims remain explicit
roadmap guard passes
README/foundation links are aligned in a future slice
no runtime authority added
no effect behavior added
```

## Phase 2: Lat and LIR strengthening

Goal:

```text
mature Lat as declaration and no-effect system-intent language
```

Priority work:

```text
Lat grammar refinement
Lat semantic diagnostics refinement
Lat-to-LIR lowering refinement
Lat-specific LIR nodes and edges
LIR report clarity
operator-visible Lat pipeline reports
negative fixtures for invalid declarations
```

C should continue to own the bounded parser/lowering/report substrate. C++ may be introduced for semantic architecture experiments only after contracts exist. Rust may be introduced for future tooling such as latfmt or latcheck after CLI contracts exist.

Non-claims:

```text
lat_execution=0
lir_execution=0
compiler_product=0
interpreter_product=0
production_language=0
```

## Phase 3: Seal guarded allowlist maturation

Goal:

```text
move from blocked-request metadata toward guarded allowlist planning while preserving no-effect behavior
```

Priority work:

```text
guarded allowlist status alignment
guarded allowlist public entry-point alignment
capability metadata contract
manifest metadata contract
evidence receipt contract
negative allowlist cases
operator-visible denial report refinement
```

Valid posture:

```text
allow_candidate_grants_authority=0
allow_candidate_executes_tool=0
allow_candidate_reads_host=0
allow_candidate_writes_host=0
allow_candidate_uses_network=0
runtime_authority_granted=0
effect_performed=0
```

## Phase 4: Rust tooling lane

Goal:

```text
introduce Rust only where it improves safety and tooling clarity
```

Candidate tools:

```text
tools/seal-report
tools/seal-verify
tools/latcheck
tools/latfmt
tools/latticra-status
```

Valid Rust first slice:

```text
parse a deterministic local fixture
produce a report
perform no host mutation beyond temporary test output
perform no network behavior
make no verification claim unless real verification is implemented
```

## Phase 5: Constrained C++ policy model lane

Goal:

```text
use C++ where policy and graph structure need stronger architecture
```

Candidate components:

```text
CapabilityGraph
SealDecision
ToolBoundaryPlanner
PolicyGraph
LatSemanticModel
AuthorityAuditModel
```

C++ must remain constrained:

```text
no unrestricted authority
no hidden effects
no exception crossing C boundary
no implicit allocation at ABI boundary
no runtime authority grant
no tool execution
```

## Phase 6: Cryptographic verification planning

Goal:

```text
separate metadata signature policy from real cryptographic verification
```

Planned distinction:

```text
signature_metadata_present
signature_policy_evaluated
signature_verification_implemented
trusted_key_store_present
revocation_policy_present
hardware_identity_present
post_quantum_transition_present
```

Do not promote metadata to verification. Verification requires real primitives, real test vectors, negative tests, key handling rules, and clear non-claims.

## Phase 7: Fedora/Linux integration lane

Goal:

```text
keep Fedora/Linux as the practical validation lane without claiming OS replacement
```

Priority work:

```text
local RPM documentation lane
Fedora disposable VM validation
host-facing validation transcripts
packaging boundary records
Fedora integration docs
no daily-driver claim
no Fedora approval claim
no immutable Fedora claim until evidence exists
```

## Phase 8: Limited enforcement research

Goal:

```text
consider narrow enforcement only after reports, allowlists, verification, and evidence receipts mature
```

Earliest possible enforcement candidates:

```text
deny unknown tool
deny unsigned request
deny stale request
deny replayed request
deny missing capability
deny manifest mismatch
```

This phase is future research. It is not current production behavior.

## Priority queue

Near-term implementation queue:

```text
1. Add roadmap and polymorphic language strategy guardrails.
2. Align README and foundation index entry points.
3. Add Seal guarded allowlist status alignment.
4. Add capability metadata contract.
5. Add evidence receipt contract.
6. Add Rust tooling contract before Rust code.
7. Add C++ policy graph contract before C++ expansion.
```

## Promotion rule

A feature can move forward only when it has:

```text
contract
implementation plan
bounded implementation or fixture
negative tests
operator-visible report or status surface
non-claims
README/status alignment when public-facing
```

## Public claim boundary

The careful public position is:

```text
Latticra is building an evidence-bound systems substrate for Linux-era and AI-era computing.
Lat provides the native declaration direction.
Latticra Seal provides report-only trust-boundary and tool-boundary planning today.
Fedora/Linux is the current validation lane.
```

Do not claim:

```text
production runtime
operating-system replacement
security product
sandbox
malware prevention
MCP implementation
AI-agent security enforcement
cryptographic verification
runtime enforcement
Fedora approval
daily-driver readiness
```
