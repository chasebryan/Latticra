#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal policy decision public entrypoint alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal policy decision public entrypoint alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_POLICY_DECISION_PUBLIC_ENTRYPOINT_ALIGNMENT.md"

require_file "$record"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNED_REQUEST_STATUS.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
require_file docs/status/SEAL_POLICY_DECISION_STATUS.md
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file include/latticra/seal_policy_decision.h
require_file src/seal_policy_decision.c
require_file tests/seal_policy_decision_invariants.c
require_file tests/seal_policy_decision_report_surface.c
require_file scripts/test-latticra-seal-policy-decision-contract.sh
require_file scripts/test-latticra-seal-policy-decision.sh
require_file scripts/latticra-seal-policy-decision-report.sh
require_file scripts/test-latticra-seal-policy-decision-status.sh
require_file scripts/test-latticra-seal-policy-decision-report-surface.sh
require_file scripts/test-latticra-seal-policy-decision-report-surface-status.sh
require_file docs/LATTICRA_SEAL_RUNTIME_ENFORCEMENT_GATE_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_GATE_IMPLEMENTATION.md
require_file include/latticra/seal_runtime_gate.h
require_file src/seal_runtime_gate.c
require_file tests/seal_runtime_gate_invariants.c
require_file scripts/test-latticra-seal-runtime-gate-contract.sh
require_file scripts/test-latticra-seal-runtime-gate.sh
require_file docs/DEFENSIVE_THREAT_MODEL_CONTRACT.md
require_file docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
require_file scripts/test-defensive-threat-model-contract.sh
require_file scripts/test-defensive-threat-model-implementation-plan.sh
require_file scripts/test-defensive-threat-model-validation.sh

require_contains 'Status: public-entrypoint alignment record for the Latticra Seal policy decision checkpoint' "$record"
require_contains 'Source: local follow-up slice' "$record"
require_contains 'seal_policy_decision_contract_present=1' "$record"
require_contains 'seal_policy_decision_implementation_present=1' "$record"
require_contains 'seal_policy_decision_header_present=1' "$record"
require_contains 'seal_policy_decision_source_present=1' "$record"
require_contains 'seal_policy_decision_invariant_test_present=1' "$record"
require_contains 'seal_policy_decision_runner_present=1' "$record"
require_contains 'seal_policy_decision_metadata_present=1' "$record"
require_contains 'seal_policy_decision_status_present=1' "$record"
require_contains 'seal_policy_decision_report_surface_present=1' "$record"
require_contains 'seal_policy_decision_report_runner_present=1' "$record"
require_contains 'seal_policy_decision_report_guard_present=1' "$record"
require_contains 'seal_policy_decision_report_surface_status_present=1' "$record"
require_contains 'seal_policy_decision_public_entrypoint_alignment_present=1' "$record"
require_contains 'readme_mentions_policy_decision_metadata=1' "$record"
require_contains 'readme_mentions_policy_decision_report_surface=1' "$record"
require_contains 'readme_links_policy_decision_contract=1' "$record"
require_contains 'readme_links_policy_decision_implementation=1' "$record"
require_contains 'readme_links_policy_decision_report_surface=1' "$record"
require_contains 'readme_links_policy_decision_status=1' "$record"
require_contains 'readme_links_policy_decision_report_surface_status=1' "$record"
require_contains 'readme_links_policy_decision_public_entrypoint_alignment=1' "$record"
require_contains 'root_status_mentions_policy_decision_public_entrypoint=1' "$record"
require_contains 'status_index_links_policy_decision_public_entrypoint=1' "$record"
require_contains 'foundation_index_links_policy_decision_public_entrypoint=1' "$record"
require_contains 'project_notes_point_to_defensive_threat_model_validation=1' "$record"
require_contains 'policy_decision_profile=latticra-seal-policy-decision/0.1' "$record"
require_contains 'policy_decision_supported=0' "$record"
require_contains 'policy_evaluation_supported=0' "$record"
require_contains 'policy_enforcement_supported=0' "$record"
require_contains 'policy_id_present=0' "$record"
require_contains 'policy_version_present=0' "$record"
require_contains 'requested_action_present=0' "$record"
require_contains 'requested_tool_present=0' "$record"
require_contains 'signed_request_present=0' "$record"
require_contains 'signature_valid=0' "$record"
require_contains 'schema_valid=0' "$record"
require_contains 'freshness_valid=0' "$record"
require_contains 'replay_detected=0' "$record"
require_contains 'default_decision=deny' "$record"
require_contains 'decision_state=report-only' "$record"
require_contains 'decision_allowed=0' "$record"
require_contains 'decision_denied=1' "$record"
require_contains 'operator_review_required=1' "$record"
require_contains 'unknown_tool_denied=1' "$record"
require_contains 'unsigned_request_denied=1' "$record"
require_contains 'invalid_schema_denied=1' "$record"
require_contains 'stale_request_denied=1' "$record"
require_contains 'replayed_request_denied=1' "$record"
require_contains 'invalid_signature_denied=1' "$record"
require_contains 'mode=public-entrypoint-alignment' "$record"
require_contains 'implementation_behavior_changed=0' "$record"
require_contains 'policy_evaluation_implemented=0' "$record"
require_contains 'policy_enforcement_implemented=0' "$record"
require_contains 'runtime_enforcement_implemented=0' "$record"
require_contains 'runtime_authority_granted=0' "$record"
require_contains 'runtime_execution_added=0' "$record"
require_contains 'effect_execution_added=0' "$record"
require_contains 'host_behavior_changed=0' "$record"
require_contains 'network_behavior_changed=0' "$record"
require_contains 'mcp_behavior_changed=0' "$record"
require_contains 'agent_execution_added=0' "$record"
require_contains 'model_execution_added=0' "$record"
require_contains 'tool_execution_added=0' "$record"
require_contains 'shell_execution_added=0' "$record"
require_contains 'cryptographic_enforcement_added=0' "$record"
require_contains 'capability_enforcement_added=0' "$record"
require_contains 'production_readiness_claimed=0' "$record"
require_contains 'external_endorsement_claimed=0' "$record"
require_contains 'defensive threat model validation refinement' "$record"

require_contains 'latticra_seal_policy_decision_contract_present=1' README.md
require_contains 'latticra_seal_policy_decision_metadata_present=1' README.md
require_contains 'latticra_seal_policy_decision_report_surface_present=1' README.md
require_contains 'latticra_seal_policy_decision_status_present=1' README.md
require_contains 'latticra_seal_policy_decision_report_surface_status_present=1' README.md
require_contains 'latticra_seal_policy_decision_public_entrypoint_alignment_present=1' README.md
require_contains 'seal_policy_decision_contract_present=1' README.md
require_contains 'seal_policy_decision_metadata_present=1' README.md
require_contains 'seal_policy_decision_report_surface_present=1' README.md
require_contains 'seal_policy_decision_status_present=1' README.md
require_contains 'seal_policy_decision_report_surface_status_present=1' README.md
require_contains 'seal_policy_decision_public_entrypoint_alignment_present=1' README.md
require_contains 'report-only policy decision metadata' README.md
require_contains 'operator-visible deterministic policy decision report surface' README.md
require_contains 'docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md' README.md
require_contains 'docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md' README.md
require_contains 'docs/status/SEAL_POLICY_DECISION_STATUS.md' README.md
require_contains 'docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md' README.md
require_contains 'docs/status/SEAL_POLICY_DECISION_PUBLIC_ENTRYPOINT_ALIGNMENT.md' README.md

require_contains 'Seal policy decision status/public-entry alignment' STATUS.md
require_contains 'Defensive threat model validation refinement' STATUS.md
require_contains 'seal_policy_decision_public_entrypoint_alignment_present=1' STATUS.md
require_contains 'SEAL_POLICY_DECISION_PUBLIC_ENTRYPOINT_ALIGNMENT.md' docs/status/README.md
require_contains 'seal_policy_decision_public_entrypoint_alignment_present=1' docs/status/README.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_POLICY_DECISION_PUBLIC_ENTRYPOINT_ALIGNMENT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Defensive threat model validation refinement' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal policy decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Defensive threat model validation refinement' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_POLICY_DECISION_PUBLIC_ENTRYPOINT_ALIGNMENT.md' docs/project_notes/README.md

printf 'seal policy decision public entrypoint alignment: ok\n'
