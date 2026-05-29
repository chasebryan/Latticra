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
require_file scripts/test-latticra-seal-agentic-automation-security-status.sh
require_file .github/workflows/latticra-seal-agentic-automation-security-status.yml
require_file scripts/test-latticra-seal-agentic-automation-security-public-entrypoint-alignment.sh
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md
require_file docs/LATTICRA_SEAL_STATUS_ROLLUP_CONTRACT.md
require_file docs/LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md
require_file docs/status/SEAL_STATUS_ROLLUP_STATUS.md
require_file scripts/test-latticra-seal-status-rollup-status.sh
require_file .github/workflows/latticra-seal-status-rollup-status.yml
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
require_file docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md
require_file scripts/test-latticra-seal-parameter-schema-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md

require_contains 'Status: status record for report-only Latticra Seal agentic automation security metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_agentic_automation_security_contract_present=1' "$status_file"
require_contains 'seal_mcp_alignment_plan_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_implementation_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_header_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_source_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_invariant_test_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_runner_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_status_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_status_runner_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_status_workflow_present=1' "$status_file"
require_contains 'seal_status_rollup_contract_present=1' "$status_file"
require_contains 'seal_status_rollup_implementation_present=1' "$status_file"
require_contains 'seal_status_rollup_status_present=1' "$status_file"
require_contains 'seal_status_rollup_status_runner_present=1' "$status_file"
require_contains 'seal_status_rollup_status_workflow_present=1' "$status_file"
require_contains 'status_rollup_predecessor_runtime_handoff_status_present=1' "$status_file"
require_contains 'agentic_automation_security_predecessor_status_rollup_status_present=1' "$status_file"
require_contains 'seal_parameter_schema_contract_present=1' "$status_file"
require_contains 'seal_parameter_schema_implementation_present=1' "$status_file"
require_contains 'seal_parameter_schema_status_present=1' "$status_file"
require_contains 'mcp_alignment_declared=1' "$status_file"
require_contains 'mcp_protocol_implemented=0' "$status_file"
require_contains 'mcp_server_implemented=0' "$status_file"
require_contains 'mcp_client_implemented=0' "$status_file"
require_contains 'agent_execution_supported=0' "$status_file"
require_contains 'model_execution_supported=0' "$status_file"
require_contains 'tool_execution_supported=0' "$status_file"
require_contains 'shell_execution_supported=0' "$status_file"
require_contains 'cryptographic_verification_supported=0' "$status_file"
require_contains 'capability_enforcement_supported=0' "$status_file"
require_contains 'runtime_authority_requested=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'unknown_tool_allowed=0' "$status_file"
require_contains 'unsigned_manifest_allowed=0' "$status_file"
require_contains 'network_access_allowed=0' "$status_file"
require_contains 'private_key_access_allowed=0' "$status_file"
require_contains 'system_mutation_allowed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'mode=report-only' "$status_file"
require_contains 'decision=report-only' "$status_file"
require_contains 'status=agentic-automation-security-metadata' "$status_file"
require_contains 'agentic_automation_security_status_added=1' "$status_file"
require_contains 'runtime_execution_added=0' "$status_file"
require_contains 'runtime_handoff_execution_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'runtime_authority_added=0' "$status_file"
require_contains 'cryptographic_verification_added=0' "$status_file"
require_contains 'verified_receipt_authority_added=0' "$status_file"
require_contains 'signature_verification_added=0' "$status_file"
require_contains 'public_key_byte_verification_added=0' "$status_file"
require_contains 'key_material_loading_added=0' "$status_file"
require_contains 'private_key_handling_added=0' "$status_file"
require_contains 'key_generation_added=0' "$status_file"
require_contains 'hardware_key_use_added=0' "$status_file"
require_contains 'trust_store_behavior_added=0' "$status_file"
require_contains 'revocation_lookup_added=0' "$status_file"
require_contains 'signing_added=0' "$status_file"
require_contains 'signer_invocation_behavior_added=0' "$status_file"
require_contains 'signer_process_execution_added=0' "$status_file"
require_contains 'object_sealing_added=0' "$status_file"
require_contains 'policy_persistence_added=0' "$status_file"
require_contains 'mcp_behavior_changed=0' "$status_file"
require_contains 'agent_execution_added=0' "$status_file"
require_contains 'model_execution_added=0' "$status_file"
require_contains 'tool_execution_added=0' "$status_file"
require_contains 'shell_execution_added=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'agentic automation security status guard workflow' "$status_file"
require_contains 'parameter schema status/workflow guard alignment' "$status_file"
require_contains 'seal agentic automation security status: ok' "$status_file"
require_contains 'seal status rollup status: ok' "$status_file"

require_contains 'agentic automation security status record now ties that report-only automation checkpoint to the guarded status rollup status predecessor' README.md
require_contains 'latticra_seal_agentic_automation_security_status_present=1' README.md
require_contains 'agentic_automation_security_predecessor_status_rollup_status_present=1' README.md
require_contains 'seal_agentic_automation_security_status_present=1' README.md
require_contains 'Seal agentic automation security predecessor status alignment' STATUS.md
require_contains 'agentic_automation_security_predecessor_status_rollup_status_present=1' STATUS.md
require_contains 'SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md' docs/status/README.md
require_contains 'agentic_automation_security_predecessor_status_rollup_status_present=1' docs/status/README.md
require_contains 'Latticra Seal agentic automation security predecessor status alignment' docs/status/CURRENT_STATUS.md
require_contains 'agentic_automation_security_predecessor_status_rollup_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal agentic automation security predecessor status alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal agentic automation security predecessor status alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal agentic automation security predecessor status alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latticra Seal agentic automation security predecessor status alignment' docs/project_notes/README.md
require_contains 'docs/status/SEAL_STATUS_ROLLUP_STATUS.md' docs/project_notes/README.md
require_contains 'sh scripts/test-latticra-seal-agentic-automation-security-status.sh' .github/workflows/latticra-seal-agentic-automation-security-status.yml

sh scripts/test-latticra-seal-status-rollup-status.sh

printf 'seal agentic automation security status: ok\n'
