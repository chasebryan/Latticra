#!/usr/bin/env sh
set -eu

output="$(sh scripts/latticra-seal-agentic-automation-security-report.sh)"

require_output() {
  pattern="$1"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'seal agentic automation security report surface: missing output: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_output 'LATTICRA SEAL AGENTIC AUTOMATION SECURITY'
require_output 'agentic_profile=latticra-seal-agentic-automation-security/0.1'
require_output 'automation_context=local-report-only'
require_output 'mcp_alignment_declared=1'
require_output 'mcp_protocol_implemented=0'
require_output 'mcp_server_implemented=0'
require_output 'mcp_client_implemented=0'
require_output 'agent_execution_supported=0'
require_output 'model_execution_supported=0'
require_output 'tool_execution_supported=0'
require_output 'shell_execution_supported=0'
require_output 'cryptographic_verification_supported=0'
require_output 'capability_enforcement_supported=0'
require_output 'runtime_authority_requested=0'
require_output 'runtime_authority_granted=0'
require_output 'unknown_tool_allowed=0'
require_output 'unsigned_manifest_allowed=0'
require_output 'network_access_allowed=0'
require_output 'private_key_access_allowed=0'
require_output 'system_mutation_allowed=0'
require_output 'host_read_performed=0'
require_output 'host_write_performed=0'
require_output 'network_performed=0'
require_output 'mode=report-only'
require_output 'decision=report-only'
require_output 'status=agentic-automation-security-metadata'

printf 'seal agentic automation security report surface: ok\n'
