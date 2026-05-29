#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal policy decision status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal policy decision status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_POLICY_DECISION_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_SIGNED_REQUEST_STATUS.md
require_file include/latticra/seal_policy_decision.h
require_file src/seal_policy_decision.c
require_file tests/seal_policy_decision_invariants.c
require_file scripts/test-latticra-seal-policy-decision-contract.sh
require_file scripts/test-latticra-seal-policy-decision.sh
require_file scripts/test-latticra-seal-policy-decision-report-surface.sh
require_file scripts/test-latticra-seal-policy-decision-report-surface-status.sh
require_file scripts/test-latticra-seal-signed-request-status.sh
require_file .github/workflows/latticra-seal-signed-request-status.yml
require_file .github/workflows/latticra-seal-policy-decision-status.yml
require_file docs/status/SEAL_CORE_EVIDENCE_STATUS.md

require_contains 'Status: status record for the Latticra Seal report-only policy decision metadata surface' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_policy_decision_contract_present=1' "$status_file"
require_contains 'seal_policy_decision_implementation_present=1' "$status_file"
require_contains 'seal_policy_decision_header_present=1' "$status_file"
require_contains 'seal_policy_decision_source_present=1' "$status_file"
require_contains 'seal_policy_decision_invariant_test_present=1' "$status_file"
require_contains 'seal_policy_decision_runner_present=1' "$status_file"
require_contains 'seal_policy_decision_status_surface_present=1' "$status_file"
require_contains 'seal_policy_decision_status_present=1' "$status_file"
require_contains 'seal_policy_decision_status_runner_present=1' "$status_file"
require_contains 'seal_policy_decision_status_workflow_present=1' "$status_file"
require_contains 'seal_policy_decision_report_surface_present=1' "$status_file"
require_contains 'seal_policy_decision_report_surface_status_present=1' "$status_file"
require_contains 'seal_signed_request_status_present=1' "$status_file"
require_contains 'seal_signed_request_status_runner_present=1' "$status_file"
require_contains 'seal_signed_request_status_workflow_present=1' "$status_file"
require_contains 'signed_request_predecessor_request_freshness_status_present=1' "$status_file"
require_contains 'policy_decision_predecessor_signed_request_status_present=1' "$status_file"
require_contains 'readme_mentions_policy_decision_metadata=1' "$status_file"
require_contains 'readme_mentions_policy_decision_report_surface=1' "$status_file"
require_contains 'readme_links_policy_decision_contract=1' "$status_file"
require_contains 'readme_links_policy_decision_implementation=1' "$status_file"
require_contains 'readme_links_policy_decision_report_surface=1' "$status_file"
require_contains 'readme_links_policy_decision_status=1' "$status_file"
require_contains 'readme_links_policy_decision_report_surface_status=1' "$status_file"
require_contains 'root_status_mentions_policy_decision_status=1' "$status_file"
require_contains 'status_index_links_policy_decision_status=1' "$status_file"
require_contains 'status_index_links_policy_decision_report_surface_status=1' "$status_file"
require_contains 'foundation_index_links_policy_decision_status=1' "$status_file"
require_contains 'foundation_index_links_policy_decision_report_surface_status=1' "$status_file"
require_contains 'project_notes_mark_policy_decision_status_complete=1' "$status_file"
require_contains 'policy_decision_profile=latticra-seal-policy-decision/0.1' "$status_file"
require_contains 'policy_decision_supported=0' "$status_file"
require_contains 'policy_evaluation_supported=0' "$status_file"
require_contains 'policy_enforcement_supported=0' "$status_file"
require_contains 'policy_id_present=0' "$status_file"
require_contains 'policy_version_present=0' "$status_file"
require_contains 'requested_action_present=0' "$status_file"
require_contains 'requested_tool_present=0' "$status_file"
require_contains 'signed_request_present=0' "$status_file"
require_contains 'signature_valid=0' "$status_file"
require_contains 'schema_valid=0' "$status_file"
require_contains 'freshness_valid=0' "$status_file"
require_contains 'replay_detected=0' "$status_file"
require_contains 'default_decision=deny' "$status_file"
require_contains 'decision_state=report-only' "$status_file"
require_contains 'decision_allowed=0' "$status_file"
require_contains 'decision_denied=1' "$status_file"
require_contains 'operator_review_required=1' "$status_file"
require_contains 'unknown_tool_denied=1' "$status_file"
require_contains 'unsigned_request_denied=1' "$status_file"
require_contains 'invalid_schema_denied=1' "$status_file"
require_contains 'stale_request_denied=1' "$status_file"
require_contains 'replayed_request_denied=1' "$status_file"
require_contains 'invalid_signature_denied=1' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'mode=report-only' "$status_file"
require_contains 'decision=report-only' "$status_file"
require_contains 'reason=policy-decision-metadata-only' "$status_file"
require_contains 'seal_policy_decision_metadata_present=1' "$status_file"
require_contains 'policy_decision_predecessor_signed_request_status_present=1' "$status_file"
require_contains 'runtime_gate_report_only=1' "$status_file"
require_contains 'core_blocked_case_set_complete=1' "$status_file"
require_contains 'mode=status-public-entry-alignment' "$status_file"
require_contains 'policy_decision_status_added=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'real_policy_evaluation_added=0' "$status_file"
require_contains 'policy_enforcement_added=0' "$status_file"
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
require_contains 'operator receipt report status/workflow guard alignment' "$status_file"
require_contains 'sh scripts/test-latticra-seal-policy-decision-status.sh' .github/workflows/latticra-seal-policy-decision-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-policy-decision-status.yml

require_contains 'latticra_seal_policy_decision_contract_present=1' README.md
require_contains 'latticra_seal_policy_decision_metadata_present=1' README.md
require_contains 'latticra_seal_policy_decision_report_surface_present=1' README.md
require_contains 'latticra_seal_policy_decision_report_surface_status_present=1' README.md
require_contains 'latticra_seal_policy_decision_status_present=1' README.md
require_contains 'seal_policy_decision_contract_present=1' README.md
require_contains 'seal_policy_decision_metadata_present=1' README.md
require_contains 'seal_policy_decision_report_surface_present=1' README.md
require_contains 'seal_policy_decision_report_surface_status_present=1' README.md
require_contains 'seal_policy_decision_status_present=1' README.md
require_contains 'policy_decision_predecessor_signed_request_status_present=1' README.md
require_contains 'report-only policy decision metadata' README.md
require_contains 'operator-visible deterministic policy decision report surface' README.md
require_contains 'policy decision status record now ties that report-only policy checkpoint to the guarded signed request status predecessor' README.md
require_contains 'docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md' README.md
require_contains 'docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md' README.md
require_contains 'docs/status/SEAL_POLICY_DECISION_STATUS.md' README.md
require_contains 'docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md' README.md

require_contains 'Seal policy decision status/public-entry alignment' STATUS.md
require_contains 'Seal policy decision predecessor status alignment' STATUS.md
require_contains 'seal_policy_decision_status_present=1' STATUS.md
require_contains 'seal_policy_decision_report_surface_status_present=1' STATUS.md
require_contains 'policy_decision_predecessor_signed_request_status_present=1' STATUS.md
require_contains 'SEAL_POLICY_DECISION_STATUS.md' docs/status/README.md
require_contains 'SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md' docs/status/README.md
require_contains 'seal_policy_decision_status_present=1' docs/status/README.md
require_contains 'seal_policy_decision_report_surface_status_present=1' docs/status/README.md
require_contains 'policy_decision_predecessor_signed_request_status_present=1' docs/status/README.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal policy decision predecessor status alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_POLICY_DECISION_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal policy decision predecessor status alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal policy decision predecessor status alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latticra Seal policy decision predecessor status alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_POLICY_DECISION_STATUS.md' docs/project_notes/README.md
require_contains 'docs/status/SEAL_SIGNED_REQUEST_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-signed-request-status.sh

printf 'latticra seal policy decision status: ok\n'
