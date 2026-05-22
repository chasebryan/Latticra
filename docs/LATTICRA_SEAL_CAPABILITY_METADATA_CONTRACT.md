# Latticra Seal Capability Metadata Contract

Status: planning contract for a future Latticra Seal capability metadata surface
Scope: contract-only planning for a future no-effect capability metadata layer after the completed Latticra Seal guarded allowlist public-entrypoint alignment. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This contract defines the next safe Latticra Seal step after guarded allowlist candidate reporting became public-entrypoint visible.

The future capability metadata surface should answer one question:

```text
If a tool request names a capability, can Latticra Seal describe that capability as metadata without granting the authority to use it?
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
seal_runtime_gate_metadata_present=1
seal_runtime_dry_run_metadata_present=1
seal_runtime_dry_run_report_surface_present=1
seal_guarded_allowlist_metadata_present=1
seal_guarded_allowlist_report_surface_present=1
seal_guarded_allowlist_report_surface_status_present=1
seal_guarded_allowlist_status_index_alignment_present=1
seal_guarded_allowlist_public_entrypoint_alignment_present=1
operator_visible_guarded_allowlist_report=1
core_blocked_case_set_complete=1
```

## Future record shape

A future capability metadata record should expose bounded metadata fields similar to:

```text
capability_metadata_profile=latticra-seal-capability-metadata/0.1
capability_contract_present
capability_metadata_planning_only
capability_name_present
capability_name
capability_scope
capability_effect_class
capability_known
capability_unknown
capability_candidate
capability_requires_guarded_allowlist
capability_requires_policy_decision
capability_requires_runtime_gate
capability_requires_runtime_dry_run
capability_requires_operator_review
capability_grants_authority
capability_executes_tool
capability_reads_host
capability_writes_host
capability_uses_network
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
capability_metadata_planning_only=1
capability_name_present=0
capability_known=0
capability_unknown=1
capability_candidate=0
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
default_action=deny
would_allow=0
would_deny=1
would_require_operator_review=1
blocked_reason=default-deny-capability-metadata
report_only=1
mode=report-only
status=capability-metadata
```

## Capability candidate rule

A known capability name may only become a candidate classification.

A known capability candidate must still report:

```text
capability_known=1
capability_candidate=1
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
would_allow=0
would_deny=1
would_require_operator_review=1
```

This means a future capability match can improve reporting, but cannot authorize execution or effects.

## Capability scope vocabulary

The initial planning vocabulary should stay small and explicit:

```text
capability_scope=tool-boundary
capability_scope=request-boundary
capability_scope=policy-boundary
capability_scope=runtime-boundary
capability_scope=evidence-boundary
```

## Capability effect vocabulary

The initial planning vocabulary should separate effect classes from authority:

```text
capability_effect_class=none
capability_effect_class=tool
capability_effect_class=host-read
capability_effect_class=host-write
capability_effect_class=network
capability_effect_class=runtime-authority
```

Any effect class other than `none` remains descriptive only.

It must not make the effect available.

## Required denied cases

The capability metadata surface must preserve the existing core blocked-request vocabulary:

```text
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
unknown_capability_denied=1
missing_capability_denied=1
invalid_capability_denied=1
```

## Forbidden behavior

The capability metadata layer must not:

```text
load production capability files
evaluate real policy files
enforce policy
enforce capabilities
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
turn capability matches into execution grants
turn capability matches into effect grants
claim production readiness
claim AI-agent security
claim MCP implementation
```

## Required future report surface

A future implementation must include a deterministic report renderer and a local fixture runner.

Required future files:

```text
include/latticra/seal_capability_metadata.h
src/seal_capability_metadata.c
tests/seal_capability_metadata_invariants.c
tests/seal_capability_metadata_report_surface.c
scripts/test-latticra-seal-capability-metadata.sh
scripts/latticra-seal-capability-metadata-report.sh
docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION.md
```

## Required future tests

A future implementation must prove:

```text
missing capability remains denied
unknown capability remains denied
invalid capability remains denied
known capability only becomes a candidate
known capability candidate grants no authority
known capability candidate performs no effect
known capability candidate does not execute tools
known capability candidate does not read host state
known capability candidate does not write host state
known capability candidate does not use the network
capability effect class is descriptive only
report rendering is deterministic
small buffers fail closed
null inputs fail closed
invalid upstream metadata fails closed
```

## Promotion rule

This contract does not authorize capability enforcement.

Capability metadata may be considered only as report-only metadata until a future implementation plan, implementation, report surface, status record, status-index alignment, public-entrypoint alignment, and negative-case evidence all remain merged and guarded.

Even after that sequence, a separate runtime authority contract would be required before any execution or effect path could be considered.

## Boundary

This is a contract-only planning slice.

It does not change implementation behavior, add runtime behavior, grant authority, or change public readiness.

## Current next valid slice

The next valid slice is a no-effect capability metadata implementation plan.

That future slice must still avoid implementation behavior and must specify exact structs, fields, APIs, report format, fixtures, tests, and failure behavior before any C code is added.