# Latticra Seal Guarded Allowlist Implementation Plan

Status: implementation planning contract for a future no-effect Latticra Seal guarded allowlist surface
Scope: implementation plan only after the Latticra Seal guarded allowlist contract. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This plan defines the exact future implementation shape for a no-effect Seal guarded allowlist layer.

The future implementation should classify whether a requested tool name is known only as a planning candidate, while still denying execution, host access, network access, and runtime authority.

## Required contract

The implementation plan depends on:

```text
docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md
scripts/test-latticra-seal-guarded-allowlist-contract.sh
```

The contract must remain merged and guarded before implementation code is added.

## Future files

The future implementation slice should add:

```text
include/latticra/seal_guarded_allowlist.h
src/seal_guarded_allowlist.c
tests/seal_guarded_allowlist_invariants.c
scripts/test-latticra-seal-guarded-allowlist.sh
docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md
```

A later report-surface slice may add:

```text
tests/seal_guarded_allowlist_report_surface.c
scripts/latticra-seal-guarded-allowlist-report.sh
scripts/test-latticra-seal-guarded-allowlist-report-surface.sh
```

## Header API plan

The future header should define:

```text
LATTICRA_SEAL_GUARDED_ALLOWLIST_PROFILE_MAX
LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX
LATTICRA_SEAL_GUARDED_ALLOWLIST_REASON_MAX
LATTICRA_SEAL_GUARDED_ALLOWLIST_STATUS_MAX
LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_MAX
latticra_seal_guarded_allowlist_error_t
latticra_seal_guarded_allowlist_entry_t
latticra_seal_guarded_allowlist_t
latticra_seal_guarded_allowlist_result_t
latticra_seal_guarded_allowlist_error_label
latticra_seal_guarded_allowlist_result_unknown
latticra_seal_guarded_allowlist_result_candidate
latticra_seal_guarded_allowlist_is_report_only
latticra_seal_guarded_allowlist_report
```

## Error model

The future error enum should include:

```text
LATTICRA_SEAL_GUARDED_ALLOWLIST_OK
LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_INPUT
LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME
LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_ALLOWLIST
LATTICRA_SEAL_GUARDED_ALLOWLIST_BUFFER_TOO_SMALL
```

## Planned static fixture

The first implementation must use only a deterministic local fixture.

Initial fixture entries may include placeholder tool names such as:

```text
latticra.seal.inspect
latticra.seal.report
latticra.seal.dry_run
```

These entries are candidate names only.

They must not become execution grants.

## Record fields

The future result record should include:

```text
guarded_allowlist_profile
tool_name
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
default_action_deny
would_allow
would_deny
would_require_operator_review
blocked_reason
report_only
mode
status
error
```

## Initial constants

The initial future implementation should emit for unknown tools:

```text
guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1
allowlist_source=deterministic-local-fixture
allowlist_entry_count=3
allowlist_lookup_performed=1
requested_tool_name_present=1
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

The initial future implementation should emit for known fixture tools:

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

## Function behavior

The future builder should:

```text
accept a requested tool name string
accept a deterministic local allowlist fixture
reject null output
reject null tool names
reject empty tool names
reject oversized tool names
reject invalid allowlist fixture metadata
classify unknown tools as denied
classify known tools as candidates only
set no authority fields to zero
set all effect fields to zero
render deterministic metadata only
```

## Required report format

The report should begin with:

```text
LATTICRA SEAL GUARDED ALLOWLIST
```

It should render all fields as stable `key=value` lines.

Required report fields:

```text
guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1
allowlist_source=deterministic-local-fixture
allowlist_lookup_performed=1
requested_tool_known
requested_tool_unknown
requested_tool_candidate
requested_tool_allow_candidate
allow_candidate_grants_authority=0
allow_candidate_executes_tool=0
allow_candidate_reads_host=0
allow_candidate_writes_host=0
allow_candidate_uses_network=0
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
report_only=1
mode=report-only
status=guarded-allowlist-metadata
```

## Required invariant tests

The future invariant test should verify:

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
invalid allowlist metadata fails closed
```

## Required build runner

The future test runner should compile only local C sources and fixtures.

Planned runner:

```sh
sh scripts/test-latticra-seal-guarded-allowlist.sh
```

It should compile:

```text
src/seal_guarded_allowlist.c
tests/seal_guarded_allowlist_invariants.c
```

If the implementation later depends on upstream Seal metadata records, the runner may also compile local Seal sources, but still must not call tools, read host files, write host files, use the network, or grant authority.

## Explicit non-goals

The future implementation must not:

```text
execute tools
execute shell commands
read host files
write host files
use the network
evaluate external policies
load policy files
load production allowlist files
verify signatures
validate freshness against live time
mutate replay caches
grant authority
turn allowlist matches into execution grants
claim production readiness
claim AI-agent security
claim MCP implementation
```

## Promotion rule

No runtime enforcement work may begin from this plan alone.

A future C implementation must first be merged with tests, a report surface, status record, status-index alignment, public-entrypoint alignment, and negative-case evidence while preserving the report-only boundary.

Even then, runtime authority would require a separate contract and evidence path.

## Current next valid slice

The next valid Latticra Seal slice is the no-effect guarded allowlist implementation.

That future slice must implement only deterministic metadata, local fixtures, fail-closed behavior, and report rendering. It must not perform effects or grant authority.