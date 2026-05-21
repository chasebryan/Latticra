#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal mcp alignment plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal mcp alignment plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file scripts/test-latticra-seal-agentic-automation-security-contract.sh

require_contains 'Status: Latticra Seal MCP alignment planning document' "$plan"
require_contains 'The purpose is not to implement MCP.' "$plan"
require_contains 'mcp_alignment_profile=latticra-seal-mcp-alignment/0.1' "$plan"
require_contains 'protocol_implementation_supported=0' "$plan"
require_contains 'server_behavior_supported=0' "$plan"
require_contains 'client_behavior_supported=0' "$plan"
require_contains 'tool_manifest_required=1' "$plan"
require_contains 'tool_manifest_signed_required=1' "$plan"
require_contains 'parameter_schema_required=1' "$plan"
require_contains 'request_identity_required=1' "$plan"
require_contains 'request_timestamp_required=1' "$plan"
require_contains 'request_expiration_required=1' "$plan"
require_contains 'nonce_required=1' "$plan"
require_contains 'context_hash_required=1' "$plan"
require_contains 'parameter_hash_required=1' "$plan"
require_contains 'message_signature_required=1' "$plan"
require_contains 'replay_protection_required=1' "$plan"
require_contains 'output_treated_as_untrusted=1' "$plan"
require_contains 'downstream_execution_allowed=0' "$plan"
require_contains 'operator_approval_required=1' "$plan"
require_contains 'receipt_required=1' "$plan"
require_contains 'runtime_authority_granted=0' "$plan"
require_contains 'mcp_protocol_implemented=0' "$plan"
require_contains 'mcp_server_implemented=0' "$plan"
require_contains 'mcp_client_implemented=0' "$plan"
require_contains 'external_endorsement_claimed=0' "$plan"
require_contains 'NSA_endorsement_claimed=0' "$plan"
require_contains 'Fedora_approval_claimed=0' "$plan"
require_contains 'production_readiness_claimed=0' "$plan"
require_contains 'host_read_performed=0' "$plan"
require_contains 'host_write_performed=0' "$plan"
require_contains 'network_performed=0' "$plan"
require_contains 'report-only agentic automation security metadata implementation' "$plan"

printf 'seal mcp alignment plan: ok\n'
