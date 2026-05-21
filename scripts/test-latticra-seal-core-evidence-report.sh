#!/usr/bin/env sh
set -eu

output="$(sh scripts/latticra-seal-core-evidence-report.sh)"

require_output() {
  pattern="$1"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra seal core evidence report: missing output: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_output 'LATTICRA SEAL CORE EVIDENCE REPORT'
require_output 'report_profile=latticra-seal-core-evidence/0.1'
require_output 'scope=report-only-runtime-gate-core-cases'
require_output 'seal_agentic_automation_metadata_present=1'
require_output 'seal_parameter_schema_metadata_present=1'
require_output 'seal_request_freshness_metadata_present=1'
require_output 'seal_signed_request_metadata_present=1'
require_output 'seal_policy_decision_metadata_present=1'
require_output 'seal_runtime_gate_metadata_present=1'
require_output 'unknown_tool_case_validated=1'
require_output 'unsigned_request_case_validated=1'
require_output 'stale_request_case_validated=1'
require_output 'replayed_request_case_validated=1'
require_output 'core_blocked_case_set_complete=1'
require_output 'runtime_gate_report_only=1'
require_output 'runtime_authority_granted=0'
require_output 'effect_performed=0'
require_output 'host_read_performed=0'
require_output 'host_write_performed=0'
require_output 'network_performed=0'
require_output 'runtime_enforcement_implemented=0'
require_output 'policy_enforcement_implemented=0'
require_output 'tool_execution_implemented=0'
require_output 'ai_agent_security_claimed=0'
require_output 'public_claim_ready=qualified-report-only-milestone'
require_output 'recommended_public_claim=Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.'

printf 'latticra seal core evidence report: ok\n'
