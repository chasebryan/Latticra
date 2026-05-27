# Latticra Seal Local Capability Registry Schema Surface

Status: report surface for the Latticra Seal local capability registry schema
Scope: deterministic local report surface after the no-effect local capability registry schema implementation. This document does not implement a registry loader, read registry files, write registry files, create registry artifacts, execute tools beyond the local test fixture, perform runtime behavior, grant runtime authority, enforce capabilities, perform effects, verify signatures, parse public keys, load key material, handle private keys, query trust stores, use networks, mutate host files outside temporary test output, implement MCP behavior, control AI agents, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This document records the first operator-visible report surface for the Latticra Seal local capability registry schema.

The report surface renders one deterministic local schema report with a default descriptive capability entry. The entry remains denied, report-only, and unable to grant authority or effects.

## Added Files

```text
tests/seal_local_capability_registry_schema_surface.c
scripts/latticra-seal-local-capability-registry-schema.sh
scripts/test-latticra-seal-local-capability-registry-schema-surface.sh
```

## Report Runner

```sh
sh scripts/latticra-seal-local-capability-registry-schema.sh
```

## Expected Report Posture

The report surface renders:

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
error=ok
```

## Boundary

This report surface compiles and runs a local deterministic fixture only.

It does not load registry files, read registry paths, write registry files, execute tools beyond compiling and running the local test fixture, read host files beyond the repository sources needed for local compilation, write host files beyond the temporary test binary/report path, use the network, evaluate external policies, verify signatures, query trust stores, grant authority, turn registry entries into execution grants, turn registry entries into effect grants, claim production readiness, claim AI-agent security, or claim MCP implementation.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-local-capability-registry-schema-surface.sh
```

Expected output:

```text
latticra seal local capability registry schema surface: ok
```

The underlying implementation remains covered by:

```sh
sh scripts/test-latticra-seal-local-capability-registry-schema.sh
```

## Claim Boundary

This report surface does not justify the public claim that Latticra Seal is a production security product.

It makes the denied local schema posture easier to inspect before any future capability enforcement, registry loading, or runtime authority path is considered.

## Next Valid Slice

The local capability registry schema status checkpoint is now represented by `docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md`.

The Panel-visible Seal dashboard planning checkpoint is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The next valid Latticra Seal slice is a Seal Panel dashboard view-model implementation plan or a signed receipt proof path.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.
