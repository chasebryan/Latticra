#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal local capability registry schema status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal local capability registry schema status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
require_file docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
require_file scripts/latticra-seal-local-capability-registry-schema.sh
require_file scripts/test-latticra-seal-local-capability-registry-schema.sh
require_file scripts/test-latticra-seal-local-capability-registry-schema-surface.sh
require_file scripts/test-latticra-seal-operator-receipt-report-status.sh
require_file tests/seal_local_capability_registry_schema_surface.c
require_file .github/workflows/latticra-seal-local-capability-registry-schema-surface.yml
require_file .github/workflows/latticra-seal-local-capability-registry-schema-status.yml

require_contains 'Status: status record for the Latticra Seal local capability registry schema surface' "$status_file"
require_contains 'seal_local_capability_registry_schema_implementation_present=1' "$status_file"
require_contains 'seal_local_capability_registry_schema_surface_document_present=1' "$status_file"
require_contains 'seal_local_capability_registry_schema_surface_fixture_present=1' "$status_file"
require_contains 'seal_local_capability_registry_schema_runner_present=1' "$status_file"
require_contains 'seal_local_capability_registry_schema_surface_guard_present=1' "$status_file"
require_contains 'seal_local_capability_registry_schema_status_present=1' "$status_file"
require_contains 'seal_operator_receipt_report_status_present=1' "$status_file"
require_contains 'local_capability_registry_schema_predecessor_operator_receipt_report_status_present=1' "$status_file"
require_contains 'operator_visible_local_capability_registry_schema=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'registry_loader_implemented=0' "$status_file"
require_contains 'registry_file_loading_supported=0' "$status_file"
require_contains 'registry_network_loading_supported=0' "$status_file"
require_contains 'registry_signature_verification_supported=0' "$status_file"
require_contains 'registry_trust_store_supported=0' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1' "$status_file"
require_contains 'registry_scope=local-only' "$status_file"
require_contains 'registry_mode=report-only' "$status_file"
require_contains 'registry_status=contract-only' "$status_file"
require_contains 'registry_entry_count=1' "$status_file"
require_contains 'default_action_deny=1' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'capability_id=seal.local.registry.schema' "$status_file"
require_contains 'capability_scope=operator-review-boundary' "$status_file"
require_contains 'capability_effect_class=none' "$status_file"
require_contains 'capability_authority_class=descriptive-only' "$status_file"
require_contains 'capability_grants_authority=0' "$status_file"
require_contains 'capability_executes_tool=0' "$status_file"
require_contains 'capability_reads_host=0' "$status_file"
require_contains 'capability_writes_host=0' "$status_file"
require_contains 'capability_uses_network=0' "$status_file"
require_contains 'capability_report_only=1' "$status_file"
require_contains 'Seal Panel dashboard view-model contract' "$status_file"
require_contains 'signed receipt proof path' "$status_file"
require_contains 'sh scripts/test-latticra-seal-local-capability-registry-schema-surface.sh' .github/workflows/latticra-seal-local-capability-registry-schema-surface.yml
require_contains 'sh scripts/test-latticra-seal-local-capability-registry-schema-status.sh' .github/workflows/latticra-seal-local-capability-registry-schema-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-local-capability-registry-schema-surface.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-local-capability-registry-schema-status.yml

require_contains 'latticra_seal_local_capability_registry_schema_surface_present=1' README.md
require_contains 'seal_local_capability_registry_schema_status_present=1' README.md
require_contains 'local_capability_registry_schema_predecessor_operator_receipt_report_status_present=1' README.md
require_contains 'local capability registry schema status record now ties that report-only schema checkpoint to the guarded operator receipt report status predecessor' README.md
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' README.md
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' README.md
require_contains 'Latest Seal local capability registry schema surface/status note: 2026-05-26 CDT' STATUS.md
require_contains 'Latest Seal local capability registry schema surface/status note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' docs/status/README.md
require_contains 'Latticra Seal local capability registry schema surface/status' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal local capability registry schema surface/status' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-operator-receipt-report-status.sh
sh scripts/test-latticra-seal-local-capability-registry-schema.sh
sh scripts/test-latticra-seal-local-capability-registry-schema-surface.sh

printf 'latticra seal local capability registry schema status: ok\n'
