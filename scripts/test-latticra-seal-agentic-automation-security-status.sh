#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal agentic automation security status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal agentic automation security status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md
require_file include/latticra/seal_agentic_automation_security.h
require_file src/seal_agentic_automation_security.c
require_file tests/seal_agentic_automation_security_invariants.c
require_file scripts/test-latticra-seal-agentic-automation-security-contract.sh
require_file scripts/test-latticra-seal-mcp-alignment-plan.sh
require_file scripts/test-latticra-seal-agentic-automation-security.sh
require_file scripts/test-latticra-seal-agentic-automation-security-public-entrypoint-alignment.sh
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md

require_contains 'Status: status record for report-only Latticra Seal agentic automation security metadata' "$status_file"
require_contains 'Source: PR #267' "$status_file"
require_contains 'seal_agentic_automation_security_contract_present=1' "$status_file"
require_contains 'seal_mcp_alignment_plan_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_implementation_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_header_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_source_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_invariant_test_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_runner_present=1' "$status_file"
require_contains 'mcp_alignment_declared=1' "$status_file"
require_contains 'mode=report-only' "$status_file"
require_contains 'decision=report-only' "$status_file"
require_contains 'status=agentic-automation-security-metadata' "$status_file"
require_contains 'policy decision status/public-entry alignment' "$status_file"

printf 'seal agentic automation security status: ok\n'
