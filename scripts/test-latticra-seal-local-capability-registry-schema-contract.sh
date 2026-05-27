#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal local capability registry schema contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal local capability registry schema contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
require_file docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
require_file docs/latticra-seal/PRODUCT.md
require_file docs/status/SEAL_PRODUCT_SPINE_STATUS.md
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md
require_file docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
require_file docs/LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_SURFACE.md
require_file docs/status/SEAL_CAPABILITY_METADATA_REPORT_SURFACE_STATUS.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md

require_contains 'Status: contract for a future no-effect Latticra Seal local capability registry schema' "$contract"
require_contains 'registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1' "$contract"
require_contains 'registry_scope=local-only' "$contract"
require_contains 'registry_mode=report-only' "$contract"
require_contains 'registry_status=contract-only' "$contract"
require_contains 'registry_contract_present=1' "$contract"
require_contains 'registry_schema_planning_only=1' "$contract"
require_contains 'registry_loader_implemented=0' "$contract"
require_contains 'registry_file_loading_supported=0' "$contract"
require_contains 'registry_network_loading_supported=0' "$contract"
require_contains 'registry_signature_verification_supported=0' "$contract"
require_contains 'registry_trust_store_supported=0' "$contract"
require_contains 'registry_entry_count_max=' "$contract"
require_contains 'registry_entry_id_max=' "$contract"
require_contains 'registry_namespace_max=' "$contract"
require_contains 'registry_description_max=' "$contract"
require_contains 'default_action_deny=1' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'capability_id=' "$contract"
require_contains 'capability_namespace=' "$contract"
require_contains 'capability_scope=operator-review-boundary' "$contract"
require_contains 'capability_effect_class=runtime-authority' "$contract"
require_contains 'capability_authority_class=future-guarded' "$contract"
require_contains 'capability_default_decision=deny' "$contract"
require_contains 'capability_requires_guarded_allowlist=1' "$contract"
require_contains 'capability_requires_policy_decision=1' "$contract"
require_contains 'capability_requires_runtime_gate=1' "$contract"
require_contains 'capability_requires_runtime_dry_run=1' "$contract"
require_contains 'capability_requires_operator_review=1' "$contract"
require_contains 'capability_requires_verification_receipt=1' "$contract"
require_contains 'capability_requires_signed_request=1' "$contract"
require_contains 'capability_grants_authority=0' "$contract"
require_contains 'capability_executes_tool=0' "$contract"
require_contains 'capability_reads_host=0' "$contract"
require_contains 'capability_writes_host=0' "$contract"
require_contains 'capability_uses_network=0' "$contract"
require_contains 'capability_report_only=1' "$contract"
require_contains 'registry file loading' "$contract"
require_contains 'remote registry loading' "$contract"
require_contains 'turning registry entries into execution grants' "$contract"
require_contains 'turning registry entries into effect grants' "$contract"
require_contains 'This contract does not authorize a registry loader.' "$contract"
require_contains 'a separate capability enforcement and runtime authority contract would be required' "$contract"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md' "$contract"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' "$contract"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' "$contract"
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' "$contract"
require_contains 'The next valid Latticra Seal slice is a Seal Panel dashboard view-model implementation plan or a signed receipt proof path.' "$contract"

printf 'latticra seal local capability registry schema contract: ok\n'
