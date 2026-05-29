#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signed request status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signed request status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_SIGNED_REQUEST_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
require_file docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md
require_file scripts/test-latticra-seal-request-freshness-status.sh
require_file .github/workflows/latticra-seal-request-freshness-status.yml
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
require_file include/latticra/seal_signed_request.h
require_file src/seal_signed_request.c
require_file tests/seal_signed_request_invariants.c
require_file scripts/test-latticra-seal-signed-request-contract.sh
require_file scripts/test-latticra-seal-signed-request.sh
require_file .github/workflows/latticra-seal-signed-request-status.yml
require_file docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
require_file docs/status/SEAL_POLICY_DECISION_STATUS.md
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file scripts/test-latticra-seal-policy-decision-contract.sh
require_file scripts/test-latticra-seal-policy-decision.sh
require_file scripts/test-latticra-seal-policy-decision-status.sh
require_file scripts/test-latticra-seal-policy-decision-report-surface.sh
require_file scripts/test-latticra-seal-policy-decision-report-surface-status.sh

require_contains 'Status: status record for Latticra Seal signed request metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_signed_request_contract_present=1' "$status_file"
require_contains 'seal_signed_request_implementation_present=1' "$status_file"
require_contains 'seal_signed_request_header_present=1' "$status_file"
require_contains 'seal_signed_request_source_present=1' "$status_file"
require_contains 'seal_signed_request_invariant_test_present=1' "$status_file"
require_contains 'seal_signed_request_runner_present=1' "$status_file"
require_contains 'seal_signed_request_metadata_present=1' "$status_file"
require_contains 'seal_signed_request_status_present=1' "$status_file"
require_contains 'seal_signed_request_status_runner_present=1' "$status_file"
require_contains 'seal_signed_request_status_workflow_present=1' "$status_file"
require_contains 'seal_request_freshness_status_present=1' "$status_file"
require_contains 'seal_request_freshness_status_runner_present=1' "$status_file"
require_contains 'seal_request_freshness_status_workflow_present=1' "$status_file"
require_contains 'request_freshness_predecessor_parameter_schema_status_present=1' "$status_file"
require_contains 'signed_request_predecessor_request_freshness_status_present=1' "$status_file"
require_contains 'readme_mentions_signed_request_metadata=1' "$status_file"
require_contains 'readme_links_signed_request_contract=1' "$status_file"
require_contains 'readme_links_signed_request_implementation=1' "$status_file"
require_contains 'readme_links_signed_request_status=1' "$status_file"
require_contains 'root_status_mentions_signed_request_status=1' "$status_file"
require_contains 'status_index_links_signed_request_status=1' "$status_file"
require_contains 'foundation_index_links_signed_request_status=1' "$status_file"
require_contains 'project_notes_point_to_policy_decision_status=1' "$status_file"
require_contains 'signed_request_profile=latticra-seal-signed-request/0.1' "$status_file"
require_contains 'signed_request_supported=0' "$status_file"
require_contains 'signature_generation_supported=0' "$status_file"
require_contains 'signature_verification_supported=0' "$status_file"
require_contains 'signature_present=0' "$status_file"
require_contains 'signature_valid=0' "$status_file"
require_contains 'signature_algorithm_declared=0' "$status_file"
require_contains 'signing_key_id_present=0' "$status_file"
require_contains 'signature_hash_present=0' "$status_file"
require_contains 'signed_request_id_present=0' "$status_file"
require_contains 'identity_binding_declared=0' "$status_file"
require_contains 'context_binding_declared=0' "$status_file"
require_contains 'parameter_binding_declared=0' "$status_file"
require_contains 'freshness_binding_declared=0' "$status_file"
require_contains 'policy_binding_declared=0' "$status_file"
require_contains 'trust_store_supported=0' "$status_file"
require_contains 'revocation_lookup_supported=0' "$status_file"
require_contains 'mode=status-public-entry-alignment' "$status_file"
require_contains 'signed_request_status_added=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'signature_generation_implemented=0' "$status_file"
require_contains 'signature_verification_implemented=0' "$status_file"
require_contains 'signed_request_enforcement_implemented=0' "$status_file"
require_contains 'trust_store_implemented=0' "$status_file"
require_contains 'revocation_lookup_implemented=0' "$status_file"
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
require_contains 'policy decision status/workflow guard alignment' "$status_file"
require_contains 'sh scripts/test-latticra-seal-signed-request-status.sh' .github/workflows/latticra-seal-signed-request-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-signed-request-status.yml

require_contains 'latticra_seal_signed_request_contract_present=1' README.md
require_contains 'latticra_seal_signed_request_metadata_present=1' README.md
require_contains 'latticra_seal_signed_request_status_present=1' README.md
require_contains 'seal_signed_request_contract_present=1' README.md
require_contains 'seal_signed_request_metadata_present=1' README.md
require_contains 'seal_signed_request_status_present=1' README.md
require_contains 'signed_request_predecessor_request_freshness_status_present=1' README.md
require_contains 'report-only signed request metadata' README.md
require_contains 'signed request status record now ties that report-only signed-request checkpoint to the guarded request freshness status predecessor' README.md
require_contains 'docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_SIGNED_REQUEST_STATUS.md' README.md

require_contains 'Seal signed request status/public-entry alignment' STATUS.md
require_contains 'Seal signed request predecessor status alignment' STATUS.md
require_contains 'Seal policy decision status/public-entry alignment' STATUS.md
require_contains 'seal_signed_request_status_present=1' STATUS.md
require_contains 'signed_request_predecessor_request_freshness_status_present=1' STATUS.md
require_contains 'SEAL_SIGNED_REQUEST_STATUS.md' docs/status/README.md
require_contains 'seal_signed_request_status_present=1' docs/status/README.md
require_contains 'signed_request_predecessor_request_freshness_status_present=1' docs/status/README.md
require_contains 'Latticra Seal signed request status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signed request predecessor status alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_SIGNED_REQUEST_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signed request status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signed request predecessor status alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signed request status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signed request predecessor status alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal policy decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signed request status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latticra Seal signed request predecessor status alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal policy decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_SIGNED_REQUEST_STATUS.md' docs/project_notes/README.md
require_contains 'docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-request-freshness-status.sh

printf 'seal signed request status: ok\n'
