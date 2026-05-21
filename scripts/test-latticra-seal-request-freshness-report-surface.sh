#!/usr/bin/env sh
set -eu

output="$(sh scripts/latticra-seal-request-freshness-report.sh)"

require_output() {
  pattern="$1"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'seal request freshness report surface: missing output: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_output 'LATTICRA SEAL REQUEST FRESHNESS'
require_output 'freshness_profile=latticra-seal-request-freshness/0.1'
require_output 'request_id=unset'
require_output 'caller_id=unset'
require_output 'tool_id=unset'
require_output 'request_timestamp=unset'
require_output 'request_expiration=unset'
require_output 'nonce=unset'
require_output 'context_hash=unset'
require_output 'parameter_hash=unset'
require_output 'request_freshness_supported=0'
require_output 'request_freshness_validation_supported=0'
require_output 'replay_protection_supported=0'
require_output 'request_id_present=0'
require_output 'caller_id_present=0'
require_output 'tool_id_present=0'
require_output 'request_timestamp_present=0'
require_output 'request_expiration_present=0'
require_output 'nonce_present=0'
require_output 'context_hash_present=0'
require_output 'parameter_hash_present=0'
require_output 'freshness_valid=0'
require_output 'replay_detected=0'
require_output 'runtime_authority_granted=0'
require_output 'host_read_performed=0'
require_output 'host_write_performed=0'
require_output 'network_performed=0'
require_output 'mode=report-only'
require_output 'decision=report-only'
require_output 'reason=request-freshness-metadata-only'
require_output 'status=request-freshness-metadata'

printf 'seal request freshness report surface: ok\n'
