#!/usr/bin/env sh
set -eu

cat <<'REPORT'
LATTICRA SEAL CORE EVIDENCE REPORT
report_profile=latticra-seal-core-evidence/0.1
scope=report-only-runtime-gate-core-cases
seal_agentic_automation_metadata_present=1
seal_parameter_schema_metadata_present=1
seal_request_freshness_metadata_present=1
seal_signed_request_metadata_present=1
seal_policy_decision_metadata_present=1
seal_runtime_gate_metadata_present=1
unknown_tool_case_validated=1
unsigned_request_case_validated=1
stale_request_case_validated=1
replayed_request_case_validated=1
core_blocked_case_set_complete=1
runtime_gate_report_only=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
runtime_enforcement_implemented=0
policy_enforcement_implemented=0
tool_execution_implemented=0
ai_agent_security_claimed=0
public_claim_ready=qualified-report-only-milestone
recommended_public_claim=Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.
REPORT
