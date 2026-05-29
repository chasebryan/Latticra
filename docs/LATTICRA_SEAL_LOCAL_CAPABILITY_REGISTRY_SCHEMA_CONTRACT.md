# Latticra Seal Local Capability Registry Schema Contract

Status: contract for a future no-effect Latticra Seal local capability registry schema
Scope: contract-only planning for a future local capability registry schema after the operator receipt report surface/status checkpoint. This document does not implement a registry loader, read registry files, write registry files, create registry artifacts, execute tools, perform runtime behavior, grant runtime authority, enforce capabilities, perform effects, verify signatures, parse public keys, load key material, handle private keys, query trust stores, use networks, mutate host files, implement MCP behavior, control AI agents, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This contract defines the next Latticra Seal product slice: a future local capability registry schema.

The future schema should answer:

```text
What local capability records may exist?
What fields must every capability record expose?
Which vocabulary values are allowed?
Which defaults keep every capability denied?
Which fields are descriptive only and cannot grant authority?
What evidence must exist before a future loader can be considered?
```

The answer must remain contract-only, local, no-effect, denied-by-default, and report-only.

## Required Predecessors

A future implementation plan may only proceed after these predecessor surfaces remain present and guarded:

```text
docs/latticra-seal/PRODUCT.md
docs/status/SEAL_PRODUCT_SPINE_STATUS.md
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md
docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
docs/LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_SURFACE.md
docs/status/SEAL_CAPABILITY_METADATA_REPORT_SURFACE_STATUS.md
docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md
```

## Schema Profile

The future schema must use this profile:

```text
registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1
registry_scope=local-only
registry_mode=report-only
registry_status=contract-only
```

## Registry Schema Fields

The future registry schema record must expose bounded metadata fields for:

```text
registry_schema_profile=
registry_format_version=
registry_scope=
registry_mode=
registry_status=
registry_contract_present=
registry_schema_planning_only=
registry_loader_implemented=
registry_file_loading_supported=
registry_network_loading_supported=
registry_signature_verification_supported=
registry_trust_store_supported=
registry_entry_count_max=
registry_entry_id_max=
registry_namespace_max=
registry_description_max=
default_action_deny=
runtime_authority_granted=
effect_performed=
host_read_performed=
host_write_performed=
network_performed=
```

## Capability Entry Fields

Every future capability entry must expose bounded metadata fields for:

```text
capability_id=
capability_namespace=
capability_name=
capability_description=
capability_scope=
capability_effect_class=
capability_authority_class=
capability_default_decision=
capability_requires_guarded_allowlist=
capability_requires_policy_decision=
capability_requires_runtime_gate=
capability_requires_runtime_dry_run=
capability_requires_operator_review=
capability_requires_verification_receipt=
capability_requires_signed_request=
capability_grants_authority=
capability_executes_tool=
capability_reads_host=
capability_writes_host=
capability_uses_network=
capability_report_only=
capability_deprecated=
capability_blocked_reason=
```

## Required Defaults

The future schema implementation, if added later, must default to:

```text
registry_contract_present=1
registry_schema_planning_only=1
registry_loader_implemented=0
registry_file_loading_supported=0
registry_network_loading_supported=0
registry_signature_verification_supported=0
registry_trust_store_supported=0
default_action_deny=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
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
```

## Required Vocabulary

The future schema must restrict capability scopes to:

```text
capability_scope=tool-boundary
capability_scope=request-boundary
capability_scope=policy-boundary
capability_scope=runtime-boundary
capability_scope=evidence-boundary
capability_scope=operator-review-boundary
```

The future schema must restrict effect classes to:

```text
capability_effect_class=none
capability_effect_class=tool
capability_effect_class=host-read
capability_effect_class=host-write
capability_effect_class=network
capability_effect_class=runtime-authority
```

The future schema must restrict authority classes to:

```text
capability_authority_class=none
capability_authority_class=descriptive-only
capability_authority_class=future-guarded
```

Any value other than `none` remains descriptive only until a separate implementation, verification, review, and authority contract exists.

## Required Denial Rule

A future registry entry may describe a capability but must not authorize it.

Every future entry must preserve:

```text
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
default_action_deny=1
runtime_authority_granted=0
effect_performed=0
```

## Forbidden Behavior

This contract does not allow:

```text
registry file loading
registry file writing
production capability registry loading
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

## Required Future Implementation Plan

A future implementation plan must specify:

```text
exact header path
exact source path
exact test path
bounded struct sizes
enum labels
entry capacity
field copy behavior
default fixture entries
report shape
invalid schema handling
small-buffer behavior
null-input behavior
no-effect invariants
status/report-surface follow-up path
```

## Promotion Rule

This contract does not authorize a registry loader.

The schema may be considered only as report-only metadata until a future implementation plan, implementation, report surface, status record, status-index alignment, public-entrypoint alignment, and negative-case evidence all remain merged and guarded.

Even after that sequence, a separate capability enforcement and runtime authority contract would be required before any registry entry could be used to authorize execution or effects.

## Boundary

This is a contract-only planning slice.

It does not change implementation behavior, add runtime behavior, grant authority, or change public readiness.

## Current Next Valid Slice

The local capability registry schema implementation plan is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md`.

The local capability registry schema implementation is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md`.

The local capability registry schema surface is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md`.

The local capability registry schema status checkpoint is now represented by `docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md`.

The Panel-visible Seal dashboard planning checkpoint is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The Seal Panel dashboard view-model implementation plan is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.
