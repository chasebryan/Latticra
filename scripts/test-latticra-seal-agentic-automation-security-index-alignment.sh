#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal agentic automation security index alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal agentic automation security index alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md"

require_file "$record"
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md
require_file scripts/test-latticra-seal-agentic-automation-security-status.sh
require_file scripts/test-latticra-seal-agentic-automation-security.sh
require_file scripts/test-latticra-seal-agentic-automation-security-public-entrypoint-alignment.sh

require_contains 'Status: index alignment record' "$record"
require_contains 'Source: PR #268' "$record"
require_contains 'contract -> MCP alignment plan -> report-only metadata implementation -> status record -> index alignment' "$record"
require_contains 'seal_agentic_contract_indexed=1' "$record"
require_contains 'seal_mcp_alignment_plan_indexed=1' "$record"
require_contains 'seal_agentic_metadata_implementation_indexed=1' "$record"
require_contains 'seal_agentic_status_record_indexed=1' "$record"
require_contains 'seal_agentic_status_guard_indexed=1' "$record"
require_contains 'seal_agentic_index_alignment_record_present=1' "$record"
require_contains 'seal_agentic_public_entrypoint_alignment_present=1' "$record"
require_contains 'mode=doc-status-alignment' "$record"
require_contains 'implementation_behavior_changed=0' "$record"
require_contains 'runtime_authority_granted=0' "$record"
require_contains 'host_behavior_changed=0' "$record"
require_contains 'network_behavior_changed=0' "$record"
require_contains 'mcp_behavior_changed=0' "$record"
require_contains 'agent_execution_added=0' "$record"
require_contains 'tool_execution_added=0' "$record"
require_contains 'shell_execution_added=0' "$record"
require_contains 'cryptographic_enforcement_added=0' "$record"
require_contains 'capability_enforcement_added=0' "$record"
require_contains 'policy decision status/public-entry alignment' "$record"

printf 'seal agentic automation security index alignment: ok\n'
