# Latticra Seal Local Capability Registry Schema Implementation

Status: no-effect implementation for the Latticra Seal local capability registry schema
Scope: implementation record after the local capability registry schema contract and implementation plan. This implementation does not add a registry loader, read registry files, write registry files, create registry artifacts, execute tools, perform runtime behavior, grant runtime authority, enforce capabilities, perform effects, verify signatures, parse public keys, load key material, handle private keys, query trust stores, use networks, mutate host files, implement MCP behavior, control AI agents, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Implemented Files

```text
include/latticra/seal_local_capability_registry_schema.h
src/seal_local_capability_registry_schema.c
tests/seal_local_capability_registry_schema_invariants.c
scripts/test-latticra-seal-local-capability-registry-schema.sh
```

## Implemented API

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
latticra_seal_local_capability_registry_scope_label
latticra_seal_local_capability_registry_effect_class_label
latticra_seal_local_capability_registry_authority_class_label
latticra_seal_local_capability_registry_schema_init
latticra_seal_local_capability_registry_schema_add_entry
latticra_seal_local_capability_registry_schema_add_default_entry
latticra_seal_local_capability_registry_schema_validate
latticra_seal_local_capability_registry_schema_is_report_only
latticra_seal_local_capability_registry_schema_render
```

The API exposes no file-path input, registry-file reader, registry-file writer, network loader, trust-store loader, signature verifier, policy evaluator, runtime handoff function, or effect executor.

## Initial Schema Output

The initialized schema preserves:

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
error=ok
```

## Default Fixture Entry

The default fixture entry emits:

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

## Report Shape

The renderer emits deterministic local metadata:

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
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
capability_report_only=1
capability_blocked_reason=registry-schema-is-descriptive-only
error=ok
```

## Failure Behavior

The implementation fails closed for:

```text
null output
null entry input
small render buffer
entry capacity overflow
unterminated schema strings before render
unterminated entry default decisions before add
tampered schema authority/effect flags before render
tampered entry authority/effect flags before render
invalid scope
invalid effect class
invalid authority class
allow default decision
entry authority grant
entry tool execution
entry host read
entry host write
entry network use
non-report-only entry
```

Invalid entries are not added to the schema. Invalid input preserves:

```text
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Boundary

This is a no-effect local metadata implementation.

It does not authorize a registry loader, does not load a registry file, does not read a registry path, does not validate signatures, does not query a trust store, does not evaluate policy, does not enforce capabilities, and does not perform effects.

## Current Next Valid Slice

The local capability registry schema implementation plan is represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md`.

The local capability registry schema surface is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md`.

The local capability registry schema status checkpoint is now represented by `docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md`.

The Panel-visible Seal dashboard planning checkpoint is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The Seal Panel dashboard view-model implementation plan is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt proof path report surface/status checkpoint that remains verification-only until trust-root and revocation boundaries are implemented.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.
