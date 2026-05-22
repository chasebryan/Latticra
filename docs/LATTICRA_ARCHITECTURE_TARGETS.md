# Latticra Architecture Targets

Status: active architecture target plan
Scope: target architecture planning for C substrate work, constrained C++ policy work, Rust tooling work, Lat/LIR language work, Seal trust-boundary work, and Fedora/Linux validation. This document does not implement runtime execution, production enforcement, kernel behavior, boot behavior, or operating-system replacement behavior.

## Purpose

This document turns the Latticra / Lat / Latticra Seal roadmap into concrete architecture target lanes.

The goal is to keep implementation polymorphic, evidence-bound, and testable.

## Top-level architecture

```text
User / operator / developer
  -> L-UI reports and CLI tools
  -> Lat declarations
  -> Lat parser and semantic validation
  -> LIR metadata representation
  -> Nucleus coordination and task classification
  -> Runtime Boundary classification
  -> Latticra Seal trust-boundary planning
  -> Fedora/Linux validation lane
```

No layer should imply authority by existing. Authority must be explicit, denied by default, and proven by tests before promotion.

## C substrate targets

C targets should remain bounded and deterministic.

Current and near-term C lanes:

```text
include/latticra/*.h
src/*.c
tests/*_invariants.c
scripts/test-*.sh
```

Target responsibilities:

```text
state fixtures
runtime-boundary structs
Lat parser/lowering substrate
LIR shape and report substrate
Seal request and allowlist metadata
no-effect invariant tests
operator-visible deterministic report fixtures
```

C success criteria:

```text
fixed capacities where practical
explicit error values
no hidden host effects
no network effects
no runtime authority grants
shell guard validates reports and non-claims
```

## Constrained C++ targets

C++ targets should be introduced only when graph or policy structure requires stronger modeling than C.

Candidate layout:

```text
cpp/include/latticra/CapabilityGraph.hpp
cpp/include/latticra/PolicyGraph.hpp
cpp/include/latticra/SealDecision.hpp
cpp/include/latticra/ToolBoundaryPlanner.hpp
cpp/src/CapabilityGraph.cpp
cpp/src/PolicyGraph.cpp
cpp/src/SealDecision.cpp
cpp/src/ToolBoundaryPlanner.cpp
cpp/tests/test_capability_graph.cpp
cpp/tests/test_policy_graph.cpp
```

Initial C++ targets:

```text
CapabilityGraph report-only model
PolicyGraph report-only model
SealDecision report-only model
ToolBoundaryPlanner report-only model
```

C++ non-claims:

```text
runtime_authority_granted=0
tool_execution=0
host_read=0
host_write=0
network=0
policy_enforcement=0
production_authority_layer=0
```

## Rust targets

Rust targets should protect risky input surfaces and developer tooling.

Candidate layout:

```text
tools/seal-report/
tools/seal-verify/
tools/latcheck/
tools/latfmt/
tools/latticra-status/
crates/latticra_manifest/
crates/latticra_evidence/
crates/latticra_seal_policy/
```

Initial Rust target:

```text
local fixture parser and report generator only
```

Rust success criteria:

```text
no network by default
no host mutation beyond temporary test output
no verification claim without real verification
clear CLI output
negative fixtures
```

## Lat targets

Lat should remain declaration-first.

Target areas:

```text
module declarations
capability annotations
Seal intent annotations
policy-aware function signatures
runtime-boundary declarations
LIR metadata lowering
```

Lat success criteria:

```text
parse deterministically
validate semantically
produce diagnostics
lower into bounded LIR metadata
perform no execution
make no compiler-product claim
```

## LIR targets

LIR should preserve evidence-bearing structure between Lat and runtime-boundary planning.

Target areas:

```text
node shape
edge shape
Lat-specific node labels
transition-source edges
report fields
no-effect evidence chain
```

LIR success criteria:

```text
bounded representation
operator-visible reports
negative tests
no execution
no authority grant
```

## Seal targets

Latticra Seal should mature in stages.

Target areas:

```text
request metadata
parameter schema metadata
freshness metadata
signed request metadata
policy decision metadata
runtime gate metadata
runtime dry-run report
guarded allowlist metadata
capability metadata
evidence receipt metadata
cryptographic verification planning
```

Seal success criteria:

```text
default_action_deny=1
would_deny=1 until all prerequisites exist
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
runtime_authority_granted=0
effect_performed=0
```

## Fedora/Linux targets

Fedora/Linux is the validation lane.

Target areas:

```text
disposable VM validation
local RPM documentation payload
host-facing transcript records
packaging boundary docs
Fedora integration docs
```

Fedora/Linux non-claims:

```text
fedora_approval_claimed=0
production_installer_ready=0
daily_driver_install_ready=0
immutable_fedora_ready=0
operating_system_replacement=0
```

## MCP and AI-era tool-boundary targets

Latticra should plan for AI-era tool invocation without claiming production MCP behavior.

Target flow:

```text
tool request
  -> declared parameters
  -> freshness metadata
  -> signature metadata
  -> guarded allowlist candidate
  -> policy decision metadata
  -> runtime gate metadata
  -> dry-run denial report
  -> evidence receipt
```

Non-claims:

```text
mcp_server=0
mcp_client=0
ai_agent_execution_control=0
tool_execution=0
production_agent_security=0
```

## Review rule

Every new target lane must answer:

1. What language owns the substrate?
2. What layer owns the policy?
3. What tool owns the report?
4. What effect is denied?
5. What authority remains absent?
6. What script validates the claim?
