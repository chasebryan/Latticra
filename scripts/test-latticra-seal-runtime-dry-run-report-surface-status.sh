#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal runtime dry-run report surface status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal runtime dry-run report surface status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
require_file scripts/latticra-seal-runtime-dry-run-report.sh
require_file scripts/test-latticra-seal-runtime-dry-run-report-surface.sh
require_file tests/seal_runtime_dry_run_report_surface.c
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md
require_file scripts/test-latticra-seal-runtime-dry-run.sh

require_contains 'Status: status record for the Latticra Seal runtime dry-run report surface' "$status_file"
require_contains 'Source: PR #305' "$status_file"
require_contains 'seal_runtime_dry_run_report_surface_document_present=1' "$status_file"
require_contains 'seal_runtime_dry_run_report_surface_fixture_present=1' "$status_file"
require_contains 'seal_runtime_dry_run_report_runner_present=1' "$status_file"
require_contains 'seal_runtime_dry_run_report_surface_guard_present=1' "$status_file"
require_contains 'operator_visible_runtime_dry_run_report=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1' "$status_file"
require_contains 'request_class=core-blocked-request' "$status_file"
require_contains 'policy_decision_state=report-only' "$status_file"
require_contains 'runtime_gate_state=report-only' "$status_file"
require_contains 'blocked_reason=default-deny-dry-run' "$status_file"
require_contains 'dry_run_supported=1' "$status_file"
require_contains 'dry_run_performed=1' "$status_file"
require_contains 'input_policy_decision_present=1' "$status_file"
require_contains 'input_runtime_gate_present=1' "$status_file"
require_contains 'policy_decision_report_only=1' "$status_file"
require_contains 'runtime_gate_report_only=1' "$status_file"
require_contains 'default_action_deny=1' "$status_file"
require_contains 'would_allow=0' "$status_file"
require_contains 'would_deny=1' "$status_file"
require_contains 'would_require_operator_review=1' "$status_file"
require_contains 'would_execute_tool=0' "$status_file"
require_contains 'would_read_host=0' "$status_file"
require_contains 'would_write_host=0' "$status_file"
require_contains 'would_use_network=0' "$status_file"
require_contains 'would_grant_runtime_authority=0' "$status_file"
require_contains 'unknown_tool_denied=1' "$status_file"
require_contains 'unsigned_request_denied=1' "$status_file"
require_contains 'invalid_schema_denied=1' "$status_file"
require_contains 'stale_request_denied=1' "$status_file"
require_contains 'replayed_request_denied=1' "$status_file"
require_contains 'invalid_signature_denied=1' "$status_file"
require_contains 'report_only=1' "$status_file"
require_contains 'mode=report-only' "$status_file"
require_contains 'status=runtime-dry-run-metadata' "$status_file"
require_contains 'runtime dry-run status-index alignment' "$status_file"
require_contains 'future guarded allowlist planning contract' "$status_file"

printf 'latticra seal runtime dry-run report surface status: ok\n'
