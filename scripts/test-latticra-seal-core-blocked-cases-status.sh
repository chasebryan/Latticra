#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal core blocked cases status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal core blocked cases status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_CORE_BLOCKED_CASES_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_UNKNOWN_TOOL_CASE_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_UNSIGNED_REQUEST_CASE_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_STALE_REQUEST_CASE_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_REPLAYED_REQUEST_CASE_IMPLEMENTATION.md
require_file tests/seal_unknown_tool_case.c
require_file tests/seal_unsigned_request_case.c
require_file tests/seal_stale_request_case.c
require_file tests/seal_replayed_request_case.c
require_file scripts/test-latticra-seal-unknown-tool-case.sh
require_file scripts/test-latticra-seal-unsigned-request-case.sh
require_file scripts/test-latticra-seal-stale-request-case.sh
require_file scripts/test-latticra-seal-replayed-request-case.sh

require_contains 'Status: status record for the completed core blocked-request case set' "$status_file"
require_contains 'unknown_tool_case_fixture_present=1' "$status_file"
require_contains 'unsigned_request_case_fixture_present=1' "$status_file"
require_contains 'stale_request_case_fixture_present=1' "$status_file"
require_contains 'replayed_request_case_fixture_present=1' "$status_file"
require_contains 'core_blocked_case_set_present=1' "$status_file"
require_contains 'core_blocked_case_set_complete=1' "$status_file"
require_contains 'core_case_unknown_tool_validated=1' "$status_file"
require_contains 'core_case_unsigned_request_validated=1' "$status_file"
require_contains 'core_case_stale_request_validated=1' "$status_file"
require_contains 'core_case_replayed_request_validated=1' "$status_file"
require_contains 'runtime_gate_report_only=1' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'ai_agent_security_claimed=0' "$status_file"
require_contains 'operator-visible evidence report surface' "$status_file"

printf 'seal core blocked cases status: ok\n'
