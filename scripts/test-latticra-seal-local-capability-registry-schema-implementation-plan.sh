#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal local capability registry schema implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal local capability registry schema implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
require_file docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
require_file scripts/test-latticra-seal-local-capability-registry-schema-contract.sh
require_file docs/latticra-seal/PRODUCT.md
require_file docs/status/SEAL_PRODUCT_SPINE_STATUS.md
require_file docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md

require_contains 'Status: implementation plan for a future no-effect Latticra Seal local capability registry schema' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md' "$plan"
require_contains 'scripts/test-latticra-seal-local-capability-registry-schema-contract.sh' "$plan"
require_contains 'include/latticra/seal_local_capability_registry_schema.h' "$plan"
require_contains 'src/seal_local_capability_registry_schema.c' "$plan"
require_contains 'tests/seal_local_capability_registry_schema_invariants.c' "$plan"
require_contains 'scripts/test-latticra-seal-local-capability-registry-schema.sh' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' "$plan"
require_contains 'tests/seal_local_capability_registry_schema_surface.c' "$plan"
require_contains 'scripts/latticra-seal-local-capability-registry-schema.sh' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' "$plan"
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX' "$plan"
require_contains 'latticra_seal_local_capability_registry_schema_t' "$plan"
require_contains 'latticra_seal_local_capability_registry_schema_add_default_entry' "$plan"
require_contains 'latticra_seal_local_capability_registry_schema_validate' "$plan"
require_contains 'latticra_seal_local_capability_registry_schema_render' "$plan"
require_contains 'The API must not include a path-loading function' "$plan"
require_contains 'registry_entry_count_max=16' "$plan"
require_contains 'registry_entry_id_max=64' "$plan"
require_contains 'registry_namespace_max=64' "$plan"
require_contains 'registry_name_max=96' "$plan"
require_contains 'registry_description_max=256' "$plan"
require_contains 'registry_blocked_reason_max=160' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_SCOPE' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_EFFECT_CLASS' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_AUTHORITY_CLASS' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_CAPACITY_EXCEEDED' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT' "$plan"
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_BUFFER_TOO_SMALL' "$plan"
require_contains 'registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1' "$plan"
require_contains 'registry_scope=local-only' "$plan"
require_contains 'registry_mode=report-only' "$plan"
require_contains 'registry_status=contract-only' "$plan"
require_contains 'registry_contract_present=1' "$plan"
require_contains 'registry_schema_planning_only=1' "$plan"
require_contains 'registry_loader_implemented=0' "$plan"
require_contains 'registry_file_loading_supported=0' "$plan"
require_contains 'registry_network_loading_supported=0' "$plan"
require_contains 'registry_signature_verification_supported=0' "$plan"
require_contains 'registry_trust_store_supported=0' "$plan"
require_contains 'default_action_deny=1' "$plan"
require_contains 'runtime_authority_granted=0' "$plan"
require_contains 'effect_performed=0' "$plan"
require_contains 'host_read_performed=0' "$plan"
require_contains 'host_write_performed=0' "$plan"
require_contains 'network_performed=0' "$plan"
require_contains 'capability_id=seal.local.registry.schema' "$plan"
require_contains 'capability_namespace=seal.local' "$plan"
require_contains 'capability_scope=operator-review-boundary' "$plan"
require_contains 'capability_effect_class=none' "$plan"
require_contains 'capability_authority_class=descriptive-only' "$plan"
require_contains 'capability_default_decision=deny' "$plan"
require_contains 'capability_requires_guarded_allowlist=1' "$plan"
require_contains 'capability_requires_policy_decision=1' "$plan"
require_contains 'capability_requires_runtime_gate=1' "$plan"
require_contains 'capability_requires_runtime_dry_run=1' "$plan"
require_contains 'capability_requires_operator_review=1' "$plan"
require_contains 'capability_requires_verification_receipt=1' "$plan"
require_contains 'capability_requires_signed_request=1' "$plan"
require_contains 'capability_grants_authority=0' "$plan"
require_contains 'capability_executes_tool=0' "$plan"
require_contains 'capability_reads_host=0' "$plan"
require_contains 'capability_writes_host=0' "$plan"
require_contains 'capability_uses_network=0' "$plan"
require_contains 'capability_report_only=1' "$plan"
require_contains 'capability_blocked_reason=registry-schema-is-descriptive-only' "$plan"
require_contains 'reject malformed vocabulary values' "$plan"
require_contains 'reject entry capacity overflow' "$plan"
require_contains 'reject any capability entry that would grant authority' "$plan"
require_contains 'reject any capability entry that would perform an effect' "$plan"
require_contains 'The implementation must not expose a file-path input API.' "$plan"
require_contains 'LATTICRA SEAL LOCAL CAPABILITY REGISTRY SCHEMA REPORT' "$plan"
require_contains 'registry file loading' "$plan"
require_contains 'remote registry loading' "$plan"
require_contains 'turning registry entries into execution grants' "$plan"
require_contains 'turning registry entries into effect grants' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' "$plan"
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' "$plan"
require_contains 'The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.' "$plan"

printf 'latticra seal local capability registry schema implementation plan: ok\n'
