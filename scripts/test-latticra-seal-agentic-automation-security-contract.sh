#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal agentic automation security contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal agentic automation security contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md
require_file include/latticra/seal_status_rollup.h
require_file src/seal_status_rollup.c
require_file scripts/test-latticra-seal-status-rollup.sh

require_contains 'Status: Latticra Seal agentic automation security contract' "$contract"
require_contains 'This document does not implement agentic automation behavior.' "$contract"
require_contains 'agentic_automation_security_declared=1' "$contract"
require_contains 'mode=report-only' "$contract"
require_contains 'mcp_alignment_declared=1' "$contract"
require_contains 'mcp_implementation_supported=0' "$contract"
require_contains 'agent_execution_supported=0' "$contract"
require_contains 'model_execution_supported=0' "$contract"
require_contains 'tool_execution_supported=0' "$contract"
require_contains 'shell_execution_supported=0' "$contract"
require_contains 'cryptographic_verification_supported=0' "$contract"
require_contains 'verified_receipt_supported=0' "$contract"
require_contains 'parameter_schema_validation_supported=0' "$contract"
require_contains 'freshness_validation_supported=0' "$contract"
require_contains 'replay_protection_supported=0' "$contract"
require_contains 'capability_enforcement_supported=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'unknown_tool_allowed=0' "$contract"
require_contains 'unsigned_manifest_allowed=0' "$contract"
require_contains 'network_access_allowed=0' "$contract"
require_contains 'private_key_access_allowed=0' "$contract"
require_contains 'system_mutation_allowed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'external_endorsement_claimed=0' "$contract"
require_contains 'NSA_endorsement_claimed=0' "$contract"
require_contains 'Fedora_approval_claimed=0' "$contract"
require_contains 'production_readiness_claimed=0' "$contract"
require_contains 'MCP alignment planning' "$contract"

printf 'seal agentic automation security contract: ok\n'
