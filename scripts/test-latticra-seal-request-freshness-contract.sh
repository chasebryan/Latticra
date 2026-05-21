#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal request freshness contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal request freshness contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md
require_file include/latticra/seal_parameter_schema.h
require_file src/seal_parameter_schema.c
require_file scripts/test-latticra-seal-parameter-schema-contract.sh
require_file scripts/test-latticra-seal-parameter-schema.sh
require_file scripts/test-latticra-seal-parameter-schema-report-surface.sh

require_contains 'Status: Latticra Seal request freshness contract' "$contract"
require_contains 'This document does not implement request freshness behavior.' "$contract"
require_contains 'seal_request_freshness_contract_present=1' "$contract"
require_contains 'request_freshness_supported=0' "$contract"
require_contains 'request_freshness_validation_supported=0' "$contract"
require_contains 'replay_protection_supported=0' "$contract"
require_contains 'request_id_present=0' "$contract"
require_contains 'caller_id_present=0' "$contract"
require_contains 'tool_id_present=0' "$contract"
require_contains 'request_timestamp_present=0' "$contract"
require_contains 'request_expiration_present=0' "$contract"
require_contains 'nonce_present=0' "$contract"
require_contains 'context_hash_present=0' "$contract"
require_contains 'parameter_hash_present=0' "$contract"
require_contains 'freshness_valid=0' "$contract"
require_contains 'replay_detected=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'mode=contract-only' "$contract"
require_contains 'status=request-freshness-contract-only' "$contract"
require_contains 'Latticra must not claim to secure AI agents from this contract alone.' "$contract"
require_contains 'request identity metadata implemented' "$contract"
require_contains 'signed request metadata implemented' "$contract"
require_contains 'runtime enforcement gate implemented' "$contract"
require_contains 'freshness_validation_implemented=0' "$contract"
require_contains 'replay_protection_implemented=0' "$contract"
require_contains 'signed_request_verification_implemented=0' "$contract"
require_contains 'ai_agent_security_claimed=0' "$contract"
require_contains 'report-only request freshness metadata' "$contract"

printf 'seal request freshness contract: ok\n'
