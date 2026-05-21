#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signed request contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signed request contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
require_file include/latticra/seal_request_freshness.h
require_file src/seal_request_freshness.c
require_file scripts/test-latticra-seal-request-freshness-contract.sh
require_file scripts/test-latticra-seal-request-freshness.sh
require_file scripts/test-latticra-seal-request-freshness-report-surface.sh

require_contains 'Status: Latticra Seal signed request contract' "$contract"
require_contains 'This document does not implement signed request behavior.' "$contract"
require_contains 'seal_signed_request_contract_present=1' "$contract"
require_contains 'signed_request_supported=0' "$contract"
require_contains 'signature_generation_supported=0' "$contract"
require_contains 'signature_verification_supported=0' "$contract"
require_contains 'signature_present=0' "$contract"
require_contains 'signature_valid=0' "$contract"
require_contains 'signature_algorithm_declared=0' "$contract"
require_contains 'signing_key_id_present=0' "$contract"
require_contains 'signature_hash_present=0' "$contract"
require_contains 'signed_request_id_present=0' "$contract"
require_contains 'identity_binding_declared=0' "$contract"
require_contains 'context_binding_declared=0' "$contract"
require_contains 'parameter_binding_declared=0' "$contract"
require_contains 'freshness_binding_declared=0' "$contract"
require_contains 'policy_binding_declared=0' "$contract"
require_contains 'trust_store_supported=0' "$contract"
require_contains 'revocation_lookup_supported=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'mode=contract-only' "$contract"
require_contains 'status=signed-request-contract-only' "$contract"
require_contains 'Latticra must not claim to secure AI agents from this contract alone.' "$contract"
require_contains 'signed request metadata implemented' "$contract"
require_contains 'runtime enforcement gate implemented' "$contract"
require_contains 'signed_request_verification_implemented=0' "$contract"
require_contains 'signature_generation_implemented=0' "$contract"
require_contains 'signature_verification_implemented=0' "$contract"
require_contains 'trust_store_implemented=0' "$contract"
require_contains 'revocation_lookup_implemented=0' "$contract"
require_contains 'ai_agent_security_claimed=0' "$contract"
require_contains 'report-only signed request metadata' "$contract"

printf 'seal signed request contract: ok\n'
