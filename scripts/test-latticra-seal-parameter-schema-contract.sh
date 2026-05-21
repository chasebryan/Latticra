#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal parameter schema contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal parameter schema contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md
require_file include/latticra/seal_agentic_automation_security.h
require_file src/seal_agentic_automation_security.c
require_file scripts/test-latticra-seal-agentic-automation-security.sh
require_file scripts/test-latticra-seal-agentic-automation-security-report-surface.sh

require_contains 'Status: Latticra Seal parameter schema contract' "$contract"
require_contains 'This document does not implement parameter schema behavior.' "$contract"
require_contains 'seal_parameter_schema_contract_present=1' "$contract"
require_contains 'parameter_schema_supported=0' "$contract"
require_contains 'parameter_schema_parsing_supported=0' "$contract"
require_contains 'parameter_schema_validation_supported=0' "$contract"
require_contains 'parameter_schema_present=0' "$contract"
require_contains 'parameter_schema_valid=0' "$contract"
require_contains 'schema_language_supported=0' "$contract"
require_contains 'schema_hash_present=0' "$contract"
require_contains 'max_input_bytes_declared=0' "$contract"
require_contains 'parameter_count_declared=0' "$contract"
require_contains 'required_parameter_count_declared=0' "$contract"
require_contains 'unknown_parameters_allowed=0' "$contract"
require_contains 'parameter_forwarding_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'mode=contract-only' "$contract"
require_contains 'status=parameter-schema-contract-only' "$contract"
require_contains 'parameter_validation_implemented=0' "$contract"
require_contains 'schema_parser_implemented=0' "$contract"
require_contains 'schema_validator_implemented=0' "$contract"
require_contains 'mcp_tool_security_enforced=0' "$contract"
require_contains 'production_readiness_claimed=0' "$contract"
require_contains 'report-only parameter schema metadata' "$contract"

printf 'seal parameter schema contract: ok\n'
