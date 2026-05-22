# Latticra Seal Guarded Allowlist Implementation

Status: no-effect implementation record for the Latticra Seal guarded allowlist surface
Source: follows `docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION_PLAN.md`
Scope: deterministic local guarded allowlist metadata only. This implementation does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This implementation adds a small, deterministic, local guarded allowlist metadata surface.

The allowlist can classify a known local fixture tool name as a candidate for later review, but it still denies execution and grants no authority.

## Added files

```text
include/latticra/seal_guarded_allowlist.h
src/seal_guarded_allowlist.c
tests/seal_guarded_allowlist_invariants.c
scripts/test-latticra-seal-guarded-allowlist.sh
docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md
```

## Deterministic local fixture

The implementation uses only this local fixture set:

```text
latticra.seal.inspect
latticra.seal.report
latticra.seal.dry_run
```

The fixture is compiled into the local C implementation.

It is not loaded from host files, policy files, network sources, MCP servers, tools, trust stores, or external services.

## Unknown-tool posture

Unknown tools remain denied:

```text
guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1
allowlist_source=deterministic-local-fixture
allowlist_entry_count=3
allowlist_lookup_performed=1
requested_tool_known=0
requested_tool_unknown=1
requested_tool_candidate=0
requested_tool_allow_candidate=0
allow_candidate_requires_policy_decision=1
allow_candidate_requires_runtime_gate=1
allow_candidate_requires_runtime_dry_run=1
allow_candidate_requires_operator_review=1
allow_candidate_grants_authority=0
allow_candidate_executes_tool=0
allow_candidate_reads_host=0
allow_candidate_writes_host=0
allow_candidate_uses_network=0
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
blocked_reason=default-deny-guarded-allowlist
report_only=1
mode=report-only
status=guarded-allowlist-metadata
```

## Known-tool candidate posture

Known fixture tools become candidates only:

```text
requested_tool_known=1
requested_tool_unknown=0
requested_tool_candidate=1
requested_tool_allow_candidate=1
allow_candidate_grants_authority=0
allow_candidate_executes_tool=0
allow_candidate_reads_host=0
allow_candidate_writes_host=0
allow_candidate_uses_network=0
would_allow=0
would_deny=1
would_require_operator_review=1
blocked_reason=known-tool-candidate-still-denied
report_only=1
mode=report-only
status=guarded-allowlist-metadata
```

A known fixture tool improves reporting but does not authorize execution.

## API surface

The implementation exposes:

```text
latticra_seal_guarded_allowlist_error_label
latticra_seal_guarded_allowlist_fixture
latticra_seal_guarded_allowlist_result_unknown
latticra_seal_guarded_allowlist_result_candidate
latticra_seal_guarded_allowlist_evaluate
latticra_seal_guarded_allowlist_is_report_only
latticra_seal_guarded_allowlist_report
```

## Report format

The report begins with:

```text
LATTICRA SEAL GUARDED ALLOWLIST
```

It renders deterministic `key=value` metadata, including known/unknown/candidate state, authority-denial state, effect-denial state, report-only state, error label, and status.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-guarded-allowlist.sh
```

Expected output:

```text
seal guarded allowlist invariants: ok
```

The invariant test proves:

```text
unknown tool remains denied
unknown tool is not a candidate
known tool becomes candidate only
known tool remains denied
known tool grants no authority
known tool executes no tools
known tool reads no host state
known tool writes no host state
known tool uses no network
allowlist lookup uses deterministic local fixture
allowlist entry count is stable
profile is stable
status remains guarded-allowlist-metadata
report_only remains one
mode remains report-only
small report buffers fail closed
null output fails closed
null tool name fails closed
empty tool name fails closed
oversized tool name fails closed
```

## Boundary

This implementation is metadata-only and no-effect.

It does not execute tools, execute shell commands, read host files, write host files, use the network, evaluate external policies, load policy files, load production allowlist files, verify signatures, validate freshness against live time, mutate replay caches, grant authority, turn allowlist matches into execution grants, claim production readiness, claim AI-agent security, or claim MCP implementation.

## Current next valid slice

The next valid Latticra Seal slice is a guarded allowlist report surface.

That future slice must render the current deterministic metadata through a local fixture runner and must not perform effects or grant authority.