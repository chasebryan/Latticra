# Latticra Seal Guarded Allowlist Contract

Status: planning contract for a future Latticra Seal guarded allowlist surface
Scope: contract-only planning for a future no-effect guarded allowlist layer after the completed Latticra Seal runtime dry-run public-entrypoint alignment. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This contract defines the next safe Latticra Seal step after the runtime dry-run lane became public-entrypoint visible.

The future guarded allowlist surface should answer one question:

```text
If a tool name is known to Latticra Seal, can the boundary report that it is only a candidate for later review while still denying every effect?
```

The answer must remain no-effect, deterministic, local, planning-only, and report-only.

## Required prerequisites

A future implementation plan may begin only after these existing layers remain present and guarded:

```text
seal_agentic_automation_metadata_present=1
seal_parameter_schema_metadata_present=1
seal_request_freshness_metadata_present=1
seal_signed_request_metadata_present=1
seal_policy_decision_metadata_present=1
seal_policy_decision_report_surface_present=1
seal_runtime_gate_metadata_present=1
seal_runtime_dry_run_metadata_present=1
seal_runtime_dry_run_report_surface_present=1
seal_runtime_dry_run_report_surface_status_present=1
seal_runtime_dry_run_status_index_alignment_present=1
seal_runtime_dry_run_public_entrypoint_alignment_present=1
operator_visible_runtime_dry_run_report=1
core_blocked_case_set_complete=1
```

## Future record shape

A future guarded allowlist record should expose bounded metadata fields similar to:

```text
guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1
allowlist_contract_present
allowlist_planning_only
allowlist_source
allowlist_entry_count
allowlist_lookup_performed
requested_tool_name_present
requested_tool_known
requested_tool_unknown
requested_tool_candidate
requested_tool_allow_candidate
allow_candidate_requires_policy_decision
allow_candidate_requires_runtime_gate
allow_candidate_requires_runtime_dry_run
allow_candidate_requires_operator_review
allow_candidate_grants_authority
allow_candidate_executes_tool
allow_candidate_reads_host
allow_candidate_writes_host
allow_candidate_uses_network
default_action
would_allow
would_deny
would_require_operator_review
blocked_reason
report_only
mode
status
```

## Required defaults

The initial implementation, if added later, must default to:

```text
allowlist_planning_only=1
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
default_action=deny
would_allow=0
would_deny=1
would_require_operator_review=1
blocked_reason=default-deny-guarded-allowlist
report_only=1
mode=report-only
status=guarded-allowlist-metadata
```

## Required denied cases

The guarded allowlist surface must preserve the existing core blocked-request vocabulary:

```text
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
```

## Known-tool candidate rule

A known tool name may only become a candidate classification.

A known-tool candidate must still report:

```text
requested_tool_known=1
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
```

This means a future allowlist match can improve reporting, but cannot authorize execution.

## Forbidden behavior

The guarded allowlist layer must not:

```text
load production allowlist files
evaluate real policy files
enforce policy
execute tools
execute shell commands
call a runtime executor
read host files
write host files
perform network operations
verify signatures
validate freshness against live time
perform replay-cache mutation
generate keys
load private keys
load trust stores
query revocation services
grant runtime authority
turn allowlist matches into execution grants
claim production readiness
claim AI-agent security
claim MCP implementation
```

## Required future report surface

A future implementation must include a deterministic report renderer and a local fixture runner.

Required future files:

```text
include/latticra/seal_guarded_allowlist.h
src/seal_guarded_allowlist.c
tests/seal_guarded_allowlist_invariants.c
tests/seal_guarded_allowlist_report_surface.c
scripts/test-latticra-seal-guarded-allowlist.sh
scripts/latticra-seal-guarded-allowlist-report.sh
docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md
```

## Required future tests

A future implementation must prove:

```text
unknown tool remains denied
known tool only becomes a candidate
known tool candidate grants no authority
known tool candidate performs no effect
known tool candidate does not execute tools
known tool candidate does not read host state
known tool candidate does not write host state
known tool candidate does not use the network
unsigned request remains denied
invalid schema remains denied
stale request remains denied
replayed request remains denied
invalid signature remains denied
report rendering is deterministic
small buffers fail closed
null inputs fail closed
invalid upstream metadata fails closed
```

## Promotion rule

This contract does not authorize runtime enforcement.

A guarded allowlist may be considered only as report-only metadata until a future implementation plan, implementation, report surface, status record, status-index alignment, public-entrypoint alignment, and negative-case evidence all remain merged and guarded.

Even after that sequence, a separate runtime authority contract would be required before any execution or effect path could be considered.

## Boundary

This is a contract-only planning slice.

It does not change implementation behavior, add runtime behavior, grant authority, or change public readiness.

## Current next valid slice

The next valid slice is a no-effect guarded allowlist implementation plan.

That future slice must still avoid implementation behavior and must specify exact structs, fields, APIs, report format, fixtures, tests, and failure behavior before any C code is added.