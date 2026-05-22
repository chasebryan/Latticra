#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal runtime dry-run status index alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal runtime dry-run status index alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_RUNTIME_DRY_RUN_STATUS_INDEX_ALIGNMENT.md"
index="docs/status/README.md"

require_file "$record"
require_file "$index"
require_file docs/status/SEAL_POLICY_DECISION_STATUS.md
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
require_file scripts/latticra-seal-runtime-dry-run-report.sh
require_file scripts/test-latticra-seal-runtime-dry-run.sh
require_file scripts/test-latticra-seal-runtime-dry-run-report-surface.sh
require_file scripts/test-latticra-seal-runtime-dry-run-report-surface-status.sh

require_contains 'Status: index alignment record for the Latticra Seal runtime dry-run report surface status' "$record"
require_contains 'Source: PR #306' "$record"
require_contains 'policy decision -> policy decision report surface -> runtime dry-run metadata -> runtime dry-run report surface -> runtime dry-run status -> status index alignment' "$record"
require_contains 'seal_policy_decision_status_indexed=1' "$record"
require_contains 'seal_policy_decision_report_surface_status_indexed=1' "$record"
require_contains 'seal_runtime_dry_run_report_surface_status_indexed=1' "$record"
require_contains 'seal_runtime_dry_run_status_index_alignment_record_present=1' "$record"
require_contains 'status_index_mentions_runtime_dry_run=1' "$record"
require_contains 'operator_visible_runtime_dry_run_report=1' "$record"
require_contains 'uses_local_deterministic_fixture=1' "$record"
require_contains 'mode=doc-status-index-alignment' "$record"
require_contains 'implementation_behavior_changed=0' "$record"
require_contains 'runtime_authority_granted=0' "$record"
require_contains 'runtime_enforcement_implemented=0' "$record"
require_contains 'policy_enforcement_implemented=0' "$record"
require_contains 'host_behavior_changed=0' "$record"
require_contains 'network_behavior_changed=0' "$record"
require_contains 'mcp_behavior_changed=0' "$record"
require_contains 'agent_execution_added=0' "$record"
require_contains 'tool_execution_added=0' "$record"
require_contains 'cryptographic_enforcement_added=0' "$record"
require_contains 'capability_enforcement_added=0' "$record"
require_contains 'production_readiness_claimed=0' "$record"
require_contains 'external_endorsement_claimed=0' "$record"
require_contains 'runtime dry-run report surface status present' "$record"
require_contains 'policy_decision_state=report-only' "$record"
require_contains 'runtime_gate_state=report-only' "$record"
require_contains 'blocked_reason=default-deny-dry-run' "$record"
require_contains 'default_action_deny=1' "$record"
require_contains 'would_allow=0' "$record"
require_contains 'would_deny=1' "$record"
require_contains 'would_require_operator_review=1' "$record"
require_contains 'would_execute_tool=0' "$record"
require_contains 'would_read_host=0' "$record"
require_contains 'would_write_host=0' "$record"
require_contains 'would_use_network=0' "$record"
require_contains 'would_grant_runtime_authority=0' "$record"
require_contains 'report_only=1' "$record"
require_contains 'mode=report-only' "$record"
require_contains 'status=runtime-dry-run-metadata' "$record"
require_contains 'future guarded allowlist planning contract' "$record"

printf 'latticra seal runtime dry-run status index alignment: ok\n'
