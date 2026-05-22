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
require_file docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
require_file include/latticra/seal_policy_decision.h
require_file src/seal_policy_decision.c
require_file tests/seal_policy_decision_invariants.c
require_file scripts/test-latticra-seal-policy-decision-contract.sh
require_file scripts/test-latticra-seal-policy-decision.sh
require_file docs/status/SEAL_CORE_EVIDENCE_STATUS.md

require_contains 'Status: status record for the Latticra Seal report-only policy decision metadata surface' "$status_file"
require_contains 'Source: PR #281' "$status_file"
require_contains 'seal_policy_decision_contract_present=1' "$status_file"
require_contains 'seal_policy_decision_implementation_present=1' "$status_file"
require_contains 'seal_policy_decision_status_surface_present=1' "$status_file"
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
require_contains 'runtime_gate_report_only=1' "$status_file"
require_contains 'core_blocked_case_set_complete=1' "$status_file"
require_contains 'policy-decision status index alignment' "$status_file"

printf 'latticra seal policy decision status: ok\n'
