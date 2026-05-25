#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal request freshness status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal request freshness status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md
require_file docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
require_file include/latticra/seal_request_freshness.h
require_file src/seal_request_freshness.c
require_file tests/seal_request_freshness_invariants.c
require_file tests/seal_request_freshness_report_surface.c
require_file scripts/test-latticra-seal-request-freshness-contract.sh
require_file scripts/test-latticra-seal-request-freshness.sh
require_file scripts/latticra-seal-request-freshness-report.sh
require_file scripts/test-latticra-seal-request-freshness-report-surface.sh
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNED_REQUEST_STATUS.md
require_file scripts/test-latticra-seal-signed-request-contract.sh
require_file scripts/test-latticra-seal-signed-request.sh
require_file scripts/test-latticra-seal-signed-request-status.sh

require_contains 'Status: status record for Latticra Seal request freshness metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_request_freshness_contract_present=1' "$status_file"
require_contains 'seal_request_freshness_implementation_present=1' "$status_file"
require_contains 'seal_request_freshness_header_present=1' "$status_file"
require_contains 'seal_request_freshness_source_present=1' "$status_file"
require_contains 'seal_request_freshness_invariant_test_present=1' "$status_file"
require_contains 'seal_request_freshness_runner_present=1' "$status_file"
require_contains 'seal_request_freshness_metadata_present=1' "$status_file"
require_contains 'seal_request_freshness_report_surface_present=1' "$status_file"
require_contains 'seal_request_freshness_report_runner_present=1' "$status_file"
require_contains 'seal_request_freshness_report_guard_present=1' "$status_file"
require_contains 'seal_request_freshness_status_present=1' "$status_file"
require_contains 'readme_mentions_request_freshness_metadata=1' "$status_file"
require_contains 'readme_mentions_request_freshness_report_surface=1' "$status_file"
require_contains 'readme_links_request_freshness_contract=1' "$status_file"
require_contains 'readme_links_request_freshness_implementation=1' "$status_file"
require_contains 'readme_links_request_freshness_report_surface=1' "$status_file"
require_contains 'readme_links_request_freshness_status=1' "$status_file"
require_contains 'root_status_mentions_request_freshness_status=1' "$status_file"
require_contains 'status_index_links_request_freshness_status=1' "$status_file"
require_contains 'foundation_index_links_request_freshness_status=1' "$status_file"
require_contains 'project_notes_point_to_policy_decision_status=1' "$status_file"
require_contains 'freshness_profile=latticra-seal-request-freshness/0.1' "$status_file"
require_contains 'request_freshness_supported=0' "$status_file"
require_contains 'request_freshness_validation_supported=0' "$status_file"
require_contains 'replay_protection_supported=0' "$status_file"
require_contains 'request_id_present=0' "$status_file"
require_contains 'caller_id_present=0' "$status_file"
require_contains 'tool_id_present=0' "$status_file"
require_contains 'request_timestamp_present=0' "$status_file"
require_contains 'request_expiration_present=0' "$status_file"
require_contains 'nonce_present=0' "$status_file"
require_contains 'context_hash_present=0' "$status_file"
require_contains 'parameter_hash_present=0' "$status_file"
require_contains 'freshness_valid=0' "$status_file"
require_contains 'replay_detected=0' "$status_file"
require_contains 'mode=status-public-entry-alignment' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'timestamp_parsing_implemented=0' "$status_file"
require_contains 'trusted_clock_behavior_added=0' "$status_file"
require_contains 'nonce_storage_added=0' "$status_file"
require_contains 'replay_cache_storage_added=0' "$status_file"
require_contains 'context_hashing_implemented=0' "$status_file"
require_contains 'parameter_hashing_implemented=0' "$status_file"
require_contains 'freshness_validation_implemented=0' "$status_file"
require_contains 'replay_protection_implemented=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'runtime_execution_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'mcp_behavior_changed=0' "$status_file"
require_contains 'agent_execution_added=0' "$status_file"
require_contains 'model_execution_added=0' "$status_file"
require_contains 'tool_execution_added=0' "$status_file"
require_contains 'shell_execution_added=0' "$status_file"
require_contains 'cryptographic_enforcement_added=0' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'production_readiness_claimed=0' "$status_file"
require_contains 'external_endorsement_claimed=0' "$status_file"
require_contains 'policy decision status/public-entry alignment' "$status_file"

require_contains 'latticra_seal_request_freshness_contract_present=1' README.md
require_contains 'latticra_seal_request_freshness_metadata_present=1' README.md
require_contains 'latticra_seal_request_freshness_report_surface_present=1' README.md
require_contains 'latticra_seal_request_freshness_status_present=1' README.md
require_contains 'seal_request_freshness_contract_present=1' README.md
require_contains 'seal_request_freshness_metadata_present=1' README.md
require_contains 'seal_request_freshness_report_surface_present=1' README.md
require_contains 'seal_request_freshness_status_present=1' README.md
require_contains 'report-only request freshness metadata' README.md
require_contains 'operator-visible deterministic request freshness report surface' README.md
require_contains 'docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md' README.md
require_contains 'docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md' README.md
require_contains 'docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md' README.md

require_contains 'Seal request freshness status/public-entry alignment' STATUS.md
require_contains 'Seal policy decision status/public-entry alignment' STATUS.md
require_contains 'seal_request_freshness_status_present=1' STATUS.md
require_contains 'SEAL_REQUEST_FRESHNESS_STATUS.md' docs/status/README.md
require_contains 'seal_request_freshness_status_present=1' docs/status/README.md
require_contains 'Latticra Seal request freshness status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_REQUEST_FRESHNESS_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal request freshness status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal request freshness status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal policy decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal request freshness status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal policy decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md' docs/project_notes/README.md

printf 'seal request freshness status: ok\n'
