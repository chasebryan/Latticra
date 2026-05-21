#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal policy decision contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal policy decision contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
require_file include/latticra/seal_signed_request.h
require_file src/seal_signed_request.c
require_file scripts/test-latticra-seal-signed-request-contract.sh
require_file scripts/test-latticra-seal-signed-request.sh

require_contains 'Status: Latticra Seal policy decision contract' "$contract"
require_contains 'This document does not implement policy decision behavior.' "$contract"
require_contains 'seal_policy_decision_contract_present=1' "$contract"
require_contains 'policy_decision_supported=0' "$contract"
require_contains 'policy_evaluation_supported=0' "$contract"
require_contains 'policy_enforcement_supported=0' "$contract"
require_contains 'policy_id_present=0' "$contract"
require_contains 'policy_version_present=0' "$contract"
require_contains 'requested_action_present=0' "$contract"
require_contains 'requested_tool_present=0' "$contract"
require_contains 'signed_request_present=0' "$contract"
require_contains 'signature_valid=0' "$contract"
require_contains 'schema_valid=0' "$contract"
require_contains 'freshness_valid=0' "$contract"
require_contains 'replay_detected=0' "$contract"
require_contains 'default_decision=deny' "$contract"
require_contains 'decision_state=report-only' "$contract"
require_contains 'decision_allowed=0' "$contract"
require_contains 'decision_denied=1' "$contract"
require_contains 'operator_review_required=1' "$contract"
require_contains 'unknown_tool_denied=1' "$contract"
require_contains 'unsigned_request_denied=1' "$contract"
require_contains 'invalid_schema_denied=1' "$contract"
require_contains 'stale_request_denied=1' "$contract"
require_contains 'replayed_request_denied=1' "$contract"
require_contains 'invalid_signature_denied=1' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'mode=contract-only' "$contract"
require_contains 'status=policy-decision-contract-only' "$contract"
require_contains 'Latticra must not claim to secure AI agents from this contract alone.' "$contract"
require_contains 'policy decision metadata implemented' "$contract"
require_contains 'runtime enforcement gate implemented' "$contract"
require_contains 'policy_evaluation_implemented=0' "$contract"
require_contains 'policy_enforcement_implemented=0' "$contract"
require_contains 'runtime_enforcement_implemented=0' "$contract"
require_contains 'ai_agent_security_claimed=0' "$contract"
require_contains 'report-only policy decision metadata' "$contract"

printf 'seal policy decision contract: ok\n'
