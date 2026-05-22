#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal core evidence status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal core evidence status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_CORE_EVIDENCE_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_CORE_EVIDENCE_REPORT.md
require_file docs/status/SEAL_CORE_EVIDENCE_PUBLIC_STATUS_UPDATE.md
require_file scripts/latticra-seal-core-evidence-report.sh
require_file scripts/test-latticra-seal-core-evidence-report.sh
require_file scripts/test-latticra-seal-core-evidence-public-status.sh

require_contains 'Status: status record for the Latticra Seal core evidence report surface' "$status_file"
require_contains 'Source: PR #294' "$status_file"
require_contains 'completed report-only Seal runtime gate metadata path' "$status_file"
require_contains 'operator-facing project checkpoint' "$status_file"
require_contains 'seal_agentic_automation_metadata_present=1' "$status_file"
require_contains 'seal_parameter_schema_metadata_present=1' "$status_file"
require_contains 'seal_request_freshness_metadata_present=1' "$status_file"
require_contains 'seal_signed_request_metadata_present=1' "$status_file"
require_contains 'seal_policy_decision_metadata_present=1' "$status_file"
require_contains 'seal_runtime_gate_metadata_present=1' "$status_file"
require_contains 'unknown_tool_case_validated=1' "$status_file"
require_contains 'unsigned_request_case_validated=1' "$status_file"
require_contains 'stale_request_case_validated=1' "$status_file"
require_contains 'replayed_request_case_validated=1' "$status_file"
require_contains 'core_blocked_case_set_complete=1' "$status_file"
require_contains 'seal_core_evidence_report_present=1' "$status_file"
require_contains 'seal_core_evidence_public_status_present=1' "$status_file"
require_contains 'seal_core_evidence_status_surface_present=1' "$status_file"
require_contains 'operator_visible_status_surface=1' "$status_file"
require_contains 'deterministic_local_report_path=1' "$status_file"
require_contains 'mcp_alignment_context=ai-era-tool-boundary-planning' "$status_file"
require_contains 'runtime_gate_report_only=1' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'runtime_enforcement_implemented=0' "$status_file"
require_contains 'policy_enforcement_implemented=0' "$status_file"
require_contains 'tool_execution_implemented=0' "$status_file"
require_contains 'ai_agent_security_claimed=0' "$status_file"
require_contains 'production_readiness_claimed=0' "$status_file"
require_contains 'external_endorsement_claimed=0' "$status_file"
require_contains 'Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.' "$status_file"
require_contains 'It is not yet accurate to claim production AI-agent security' "$status_file"
require_contains 'documentation/status alignment only' "$status_file"
require_contains 'guarded policy-decision status surface' "$status_file"

printf 'latticra seal core evidence status: ok\n'
