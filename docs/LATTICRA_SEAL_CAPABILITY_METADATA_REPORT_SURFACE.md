# Latticra Seal Capability Metadata Report Surface

Status: report surface for the Latticra Seal capability metadata layer
Scope: deterministic local report surface after the no-effect capability metadata implementation. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This document records the first operator-visible report surface for Latticra Seal capability metadata.

The report surface renders whether a deterministic local fixture capability name is known only as a candidate while still denying execution, host access, network use, effects, and runtime authority.

## Added files

```text
tests/seal_capability_metadata_report_surface.c
scripts/latticra-seal-capability-metadata-report.sh
```

## Report runner

```sh
sh scripts/latticra-seal-capability-metadata-report.sh
```

## Expected report posture

The report surface renders the current capability metadata posture for a known local fixture capability candidate, including:

```text
LATTICRA SEAL CAPABILITY METADATA
capability_metadata_profile=latticra-seal-capability-metadata/0.1
capability_name=seal.capability.report
capability_scope=evidence-boundary
capability_effect_class=none
capability_fixture_source=deterministic-local-fixture
capability_fixture_entry_count=3
capability_lookup_performed=1
capability_name_present=1
capability_known=1
capability_unknown=0
capability_candidate=1
capability_requires_guarded_allowlist=1
capability_requires_policy_decision=1
capability_requires_runtime_gate=1
capability_requires_runtime_dry_run=1
capability_requires_operator_review=1
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
unknown_capability_denied=1
missing_capability_denied=0
invalid_capability_denied=0
blocked_reason=known-capability-candidate-still-denied
report_only=1
mode=report-only
status=capability-metadata
```

## Boundary

This report surface compiles and runs a local deterministic fixture only.

It does not execute tools, execute shell commands beyond compiling and running the local test fixture, read host files beyond the repository sources needed for local compilation, write host files beyond the temporary test binary/report path, use the network, evaluate external policies, load policy files, load production capability files, load production allowlist files, verify signatures, validate freshness against live time, mutate replay caches, grant authority, turn capability matches into execution grants, turn capability matches into effect grants, claim production readiness, claim AI-agent security, or claim MCP implementation.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-capability-metadata-report-surface.sh
```

Expected output:

```text
latticra seal capability metadata report surface: ok
```

The underlying capability metadata implementation remains covered by:

```sh
sh scripts/test-latticra-seal-capability-metadata.sh
```

## Claim boundary

This report surface does not justify the public claim that Latticra secures AI agents.

It makes the capability candidate denial posture easier to inspect before any future capability enforcement or runtime authority path is considered.

## Next valid slice

The next valid Latticra Seal slice is capability metadata report status alignment.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.