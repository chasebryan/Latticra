# Latticra Seal Capability Metadata Implementation Plan

Status: implementation planning contract for a future no-effect Latticra Seal capability metadata surface
Scope: implementation plan only after the Latticra Seal capability metadata contract. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This plan defines the exact future implementation shape for a no-effect Seal capability metadata layer.

The future implementation should classify whether a requested capability name is known only as descriptive metadata, while still denying execution, host access, network access, effects, and runtime authority.

## Required contract

The implementation plan depends on:

```text
docs/LATTICRA_SEAL_CAPABILITY_METADATA_CONTRACT.md
scripts/test-latticra-seal-capability-metadata-contract.sh
```

The contract must remain merged and guarded before implementation code is added.

## Future files

The future implementation slice should add:

```text
include/latticra/seal_capability_metadata.h
src/seal_capability_metadata.c
tests/seal_capability_metadata_invariants.c
scripts/test-latticra-seal-capability-metadata.sh
docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION.md
```

A later report-surface slice may add:

```text
tests/seal_capability_metadata_report_surface.c
scripts/latticra-seal-capability-metadata-report.sh
scripts/test-latticra-seal-capability-metadata-report-surface.sh
```

## Header API plan

The future header should define:

```text
LATTICRA_SEAL_CAPABILITY_METADATA_PROFILE_MAX
LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX
LATTICRA_SEAL_CAPABILITY_METADATA_SCOPE_MAX
LATTICRA_SEAL_CAPABILITY_METADATA_EFFECT_MAX
LATTICRA_SEAL_CAPABILITY_METADATA_REASON_MAX
LATTICRA_SEAL_CAPABILITY_METADATA_STATUS_MAX
LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_MAX
LATTICRA_SEAL_CAPABILITY_METADATA_ENTRY_MAX
latticra_seal_capability_metadata_error_t
latticra_seal_capability_metadata_entry_t
latticra_seal_capability_metadata_fixture_t
latticra_seal_capability_metadata_result_t
latticra_seal_capability_metadata_error_label
latticra_seal_capability_metadata_fixture
latticra_seal_capability_metadata_result_missing
latticra_seal_capability_metadata_result_unknown
latticra_seal_capability_metadata_result_candidate
latticra_seal_capability_metadata_evaluate
latticra_seal_capability_metadata_is_report_only
latticra_seal_capability_metadata_report
```

## Error model

The future error enum should include:

```text
LATTICRA_SEAL_CAPABILITY_METADATA_OK
LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_INPUT
LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME
LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_FIXTURE
LATTICRA_SEAL_CAPABILITY_METADATA_BUFFER_TOO_SMALL
```

## Planned static fixture

The first implementation must use only a deterministic local fixture.

Initial fixture entries may include placeholder capability names such as:

```text
seal.capability.inspect
seal.capability.report
seal.capability.dry_run
```

These entries are capability candidate names only.

They must not become authority grants, execution grants, or effect grants.

## Record fields

The future result record should include:

```text
capability_metadata_profile
capability_name
capability_scope
capability_effect_class
capability_fixture_source
capability_fixture_entry_count
capability_lookup_performed
capability_name_present
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
default_action_deny
would_allow
would_deny
would_require_operator_review
unknown_tool_denied
unsigned_request_denied
invalid_schema_denied
stale_request_denied
replayed_request_denied
invalid_signature_denied
unknown_capability_denied
missing_capability_denied
invalid_capability_denied
blocked_reason
report_only
mode
status
error
```

## Initial constants

The initial future implementation should emit for missing capability names:

```text
capability_metadata_profile=latticra-seal-capability-metadata/0.1
capability_fixture_source=deterministic-local-fixture
capability_fixture_entry_count=3
capability_lookup_performed=1
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
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
unknown_capability_denied=1
missing_capability_denied=1
invalid_capability_denied=1
blocked_reason=missing-capability-denied
report_only=1
mode=report-only
status=capability-metadata
```

The initial future implementation should emit for unknown capability names:

```text
capability_name_present=1
capability_known=0
capability_unknown=1
capability_candidate=0
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
would_allow=0
would_deny=1
would_require_operator_review=1
unknown_capability_denied=1
blocked_reason=default-deny-capability-metadata
report_only=1
mode=report-only
status=capability-metadata
```

The initial future implementation should emit for known fixture capability names:

```text
capability_name_present=1
capability_known=1
capability_unknown=0
capability_candidate=1
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
would_allow=0
would_deny=1
would_require_operator_review=1
blocked_reason=known-capability-candidate-still-denied
report_only=1
mode=report-only
status=capability-metadata
```

## Function behavior

The future builder should:

```text
accept a requested capability name string
accept a deterministic local capability fixture
reject null output
classify null capability names as missing capability
classify empty capability names as missing capability
reject oversized capability names
reject invalid capability fixture metadata
classify unknown capabilities as denied
classify known capabilities as candidates only
set no authority fields to zero
set all effect fields to zero
render deterministic metadata only
```

## Required report format

The report should begin with:

```text
LATTICRA SEAL CAPABILITY METADATA
```

It should render all fields as stable `key=value` lines.

Required report fields:

```text
capability_metadata_profile=latticra-seal-capability-metadata/0.1
capability_name
capability_scope
capability_effect_class
capability_fixture_source=deterministic-local-fixture
capability_lookup_performed=1
capability_known
capability_unknown
capability_candidate
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
missing_capability_denied=1
invalid_capability_denied=1
report_only=1
mode=report-only
status=capability-metadata
```

## Required invariant tests

The future invariant test should verify:

```text
missing capability remains denied
missing capability is not a candidate
unknown capability remains denied
unknown capability is not a candidate
known capability becomes candidate only
known capability remains denied
known capability grants no authority
known capability executes no tools
known capability reads no host state
known capability writes no host state
known capability uses no network
capability effect class is descriptive only
capability lookup uses deterministic local fixture
capability fixture entry count is stable
profile is stable
status remains capability-metadata
report_only remains one
mode remains report-only
small report buffers fail closed
null output fails closed
empty capability name fails closed as missing capability
oversized capability name fails closed
invalid fixture metadata fails closed
```

## Required build runner

The future test runner should compile only local C sources and fixtures.

Planned runner:

```sh
sh scripts/test-latticra-seal-capability-metadata.sh
```

It should compile:

```text
src/seal_capability_metadata.c
tests/seal_capability_metadata_invariants.c
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
load production capability files
load production allowlist files
verify signatures
validate freshness against live time
mutate replay caches
grant authority
turn capability matches into execution grants
turn capability matches into effect grants
claim production readiness
claim AI-agent security
claim MCP implementation
```

## Promotion rule

No capability enforcement work may begin from this plan alone.

A future C implementation must first be merged with tests, a report surface, status record, status-index alignment, public-entrypoint alignment, and negative-case evidence while preserving the report-only boundary.

Even then, runtime authority would require a separate contract and evidence path.

## Current next valid slice

The next valid Latticra Seal slice is the no-effect capability metadata implementation.

That future slice must implement only deterministic metadata, local fixtures, fail-closed behavior, and report rendering. It must not perform effects or grant authority.