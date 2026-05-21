#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal core evidence public status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal core evidence public status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_CORE_EVIDENCE_PUBLIC_STATUS_UPDATE.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_CORE_EVIDENCE_REPORT.md
require_file scripts/latticra-seal-core-evidence-report.sh
require_file scripts/test-latticra-seal-core-evidence-report.sh

require_contains 'Status: public status update draft for the Latticra Seal core evidence milestone' "$status_file"
require_contains 'Latticra Seal has reached an important report-only milestone.' "$status_file"
require_contains 'unknown tool case' "$status_file"
require_contains 'unsigned request case' "$status_file"
require_contains 'stale request case' "$status_file"
require_contains 'replayed request case' "$status_file"
require_contains 'Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.' "$status_file"
require_contains 'This milestone does not mean Latticra broadly secures AI agents in production.' "$status_file"
require_contains 'ai_agent_security_claimed=0' "$status_file"
require_contains 'runtime_enforcement_implemented=0' "$status_file"
require_contains 'authority_granted=0' "$status_file"
require_contains 'core_blocked_case_set_complete=1' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'operator-visible evidence report surface' "$status_file"

printf 'latticra seal core evidence public status: ok\n'
