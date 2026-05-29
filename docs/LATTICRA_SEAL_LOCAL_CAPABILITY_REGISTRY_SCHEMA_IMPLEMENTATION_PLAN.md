# Latticra Seal Local Capability Registry Schema Implementation Plan

Status: implementation plan for a future no-effect Latticra Seal local capability registry schema
Scope: implementation planning after the local capability registry schema contract. This document does not implement a registry loader, read registry files, write registry files, create registry artifacts, execute tools, perform runtime behavior, grant runtime authority, enforce capabilities, perform effects, verify signatures, parse public keys, load key material, handle private keys, query trust stores, use networks, mutate host files, implement MCP behavior, control AI agents, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This plan defines the exact future implementation shape for a no-effect local capability registry schema.

The future implementation should make capability records inspectable as bounded local metadata while preserving denial, non-execution, and zero runtime authority.

## Required Contract

The implementation plan depends on:

```text
docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md
scripts/test-latticra-seal-local-capability-registry-schema-contract.sh
```

The contract must remain merged and guarded before implementation code is added.

## Planned Files

A future implementation slice may add:

```text
include/latticra/seal_local_capability_registry_schema.h
src/seal_local_capability_registry_schema.c
tests/seal_local_capability_registry_schema_invariants.c
scripts/test-latticra-seal-local-capability-registry-schema.sh
docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
```

A later report-surface slice may add:

```text
tests/seal_local_capability_registry_schema_surface.c
scripts/latticra-seal-local-capability-registry-schema.sh
scripts/test-latticra-seal-local-capability-registry-schema-surface.sh
docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
```

## Header API Plan

The header should define:

```text
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_PROFILE_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_FORMAT_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_MODE_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_STATUS_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_ID_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAMESPACE_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAME_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_DESCRIPTION_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_BLOCKED_REASON_MAX
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_REPORT_MAX
latticra_seal_local_capability_registry_schema_error_t
latticra_seal_local_capability_registry_scope_t
latticra_seal_local_capability_registry_effect_class_t
latticra_seal_local_capability_registry_authority_class_t
latticra_seal_local_capability_registry_entry_t
latticra_seal_local_capability_registry_schema_t
latticra_seal_local_capability_registry_schema_error_label
latticra_seal_local_capability_registry_schema_init
latticra_seal_local_capability_registry_schema_add_entry
latticra_seal_local_capability_registry_schema_add_default_entry
latticra_seal_local_capability_registry_schema_validate
latticra_seal_local_capability_registry_schema_is_report_only
latticra_seal_local_capability_registry_schema_render
```

The API must not include a path-loading function, registry-file reader, registry-file writer, network loader, trust-store loader, signature verifier, policy evaluator, runtime handoff function, or effect executor.

## Capacity Plan

The future implementation should use bounded fixed storage:

```text
registry_entry_count_max=16
registry_entry_id_max=64
registry_namespace_max=64
registry_name_max=96
registry_description_max=256
registry_blocked_reason_max=160
```

No dynamic allocation is required for the initial implementation.

## Error Model

The error enum should include:

```text
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_INPUT
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_PROFILE
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_SCOPE
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_EFFECT_CLASS
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_AUTHORITY_CLASS
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_DEFAULT_DECISION
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_CAPACITY_EXCEEDED
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_NON_REPORT_ONLY_ENTRY
LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_BUFFER_TOO_SMALL
```

## Registry Record Fields

The registry record should include:

```text
registry_schema_profile
registry_format_version
registry_scope
registry_mode
registry_status
registry_contract_present
registry_schema_planning_only
registry_loader_implemented
registry_file_loading_supported
registry_network_loading_supported
registry_signature_verification_supported
registry_trust_store_supported
registry_entry_count
registry_entry_count_max
registry_entry_id_max
registry_namespace_max
registry_name_max
registry_description_max
registry_blocked_reason_max
default_action_deny
runtime_authority_granted
effect_performed
host_read_performed
host_write_performed
network_performed
last_error
```

## Capability Entry Record Fields

Every entry should include:

```text
capability_id
capability_namespace
capability_name
capability_description
capability_scope
capability_effect_class
capability_authority_class
capability_default_decision
capability_requires_guarded_allowlist
capability_requires_policy_decision
capability_requires_runtime_gate
capability_requires_runtime_dry_run
capability_requires_operator_review
capability_requires_verification_receipt
capability_requires_signed_request
capability_grants_authority
capability_executes_tool
capability_reads_host
capability_writes_host
capability_uses_network
capability_report_only
capability_deprecated
capability_blocked_reason
```

## Initial Constants

The implementation should emit for an initialized schema:

```text
registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1
registry_format_version=0.1
registry_scope=local-only
registry_mode=report-only
registry_status=contract-only
registry_contract_present=1
registry_schema_planning_only=1
registry_loader_implemented=0
registry_file_loading_supported=0
registry_network_loading_supported=0
registry_signature_verification_supported=0
registry_trust_store_supported=0
registry_entry_count=0
registry_entry_count_max=16
registry_entry_id_max=64
registry_namespace_max=64
registry_name_max=96
registry_description_max=256
registry_blocked_reason_max=160
default_action_deny=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

The default fixture entry should emit:

```text
capability_id=seal.local.registry.schema
capability_namespace=seal.local
capability_name=seal.local.registry.schema
capability_description=Describes local Seal capability schema metadata without loading or granting capabilities.
capability_scope=operator-review-boundary
capability_effect_class=none
capability_authority_class=descriptive-only
capability_default_decision=deny
capability_requires_guarded_allowlist=1
capability_requires_policy_decision=1
capability_requires_runtime_gate=1
capability_requires_runtime_dry_run=1
capability_requires_operator_review=1
capability_requires_verification_receipt=1
capability_requires_signed_request=1
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
capability_report_only=1
capability_deprecated=0
capability_blocked_reason=registry-schema-is-descriptive-only
```

## Function Behavior

The builder should:

```text
initialize a caller-provided registry record
add caller-provided static entries only
add one default fixture entry
validate bounded vocabulary values
validate deny-by-default entry posture
reject null registry output
reject null entry input
reject entry capacity overflow
reject malformed vocabulary values
reject unsupported default decisions
reject any capability entry that would grant authority
reject any capability entry that would perform an effect
reject any non-report-only capability entry
render deterministic metadata only
return BUFFER_TOO_SMALL for insufficient render buffers
```

The implementation must not expose a file-path input API.

## Report Shape

The render function should produce:

```text
LATTICRA SEAL LOCAL CAPABILITY REGISTRY SCHEMA REPORT
registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1
registry_format_version=0.1
registry_scope=local-only
registry_mode=report-only
registry_status=contract-only
registry_contract_present=1
registry_schema_planning_only=1
registry_loader_implemented=0
registry_file_loading_supported=0
registry_network_loading_supported=0
registry_signature_verification_supported=0
registry_trust_store_supported=0
registry_entry_count=1
registry_entry_count_max=16
default_action_deny=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
capability_id=seal.local.registry.schema
capability_namespace=seal.local
capability_name=seal.local.registry.schema
capability_scope=operator-review-boundary
capability_effect_class=none
capability_authority_class=descriptive-only
capability_default_decision=deny
capability_requires_guarded_allowlist=1
capability_requires_policy_decision=1
capability_requires_runtime_gate=1
capability_requires_runtime_dry_run=1
capability_requires_operator_review=1
capability_requires_verification_receipt=1
capability_requires_signed_request=1
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
capability_report_only=1
capability_deprecated=0
capability_blocked_reason=registry-schema-is-descriptive-only
error=ok
```

## Test Plan

The invariant test should cover:

```text
default schema initializes as report-only
default fixture entry remains denied
render output includes the report header
null output is rejected
null entry input is rejected
small render buffer is rejected
entry capacity overflow is rejected
invalid scope is rejected
invalid effect class is rejected
invalid authority class is rejected
allow default decision is rejected
entry authority grant is rejected
entry tool execution is rejected
entry host read is rejected
entry host write is rejected
entry network use is rejected
non-report-only entry is rejected
no-effect counters remain zero on invalid input
```

## Forbidden Behavior

The implementation must not add:

```text
registry loader
registry file loading
registry file writing
remote registry loading
trust-store lookup
signature verification
policy evaluation
policy enforcement
capability enforcement
runtime enforcement
tool execution
shell execution
AI-agent execution control
MCP protocol behavior
host reads
host writes
network behavior
runtime handoff execution
runtime authority grants
turning registry entries into execution grants
turning registry entries into effect grants
malware prevention claims
ransomware prevention claims
production security-product claims
```

## Current Next Valid Slice

The local capability registry schema contract is represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md`.

The local capability registry schema implementation is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md`.

The local capability registry schema surface is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md`.

The local capability registry schema status checkpoint is now represented by `docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md`.

The Panel-visible Seal dashboard planning checkpoint is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The Seal Panel dashboard view-model implementation plan is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.
