#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal operator receipt report status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal operator receipt report status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md
require_file scripts/latticra-seal-operator-receipt-report.sh
require_file scripts/test-latticra-seal-operator-receipt-report-surface.sh
require_file tests/seal_operator_receipt_report_surface.c
require_file scripts/test-latticra-seal-operator-receipt-report.sh

require_contains 'Status: status record for the Latticra Seal operator receipt report surface' "$status_file"
require_contains 'seal_operator_receipt_report_surface_document_present=1' "$status_file"
require_contains 'seal_operator_receipt_report_surface_fixture_present=1' "$status_file"
require_contains 'seal_operator_receipt_report_runner_present=1' "$status_file"
require_contains 'seal_operator_receipt_report_surface_guard_present=1' "$status_file"
require_contains 'seal_operator_receipt_report_status_present=1' "$status_file"
require_contains 'operator_visible_operator_receipt_report=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'source_metadata_bound=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'operator_receipt_profile=latticra-seal-operator-receipt-report/0.1' "$status_file"
require_contains 'receipt_mode=report-only' "$status_file"
require_contains 'receipt_status=denied-report-only' "$status_file"
require_contains 'source_capability_metadata_present=1' "$status_file"
require_contains 'source_policy_decision_present=1' "$status_file"
require_contains 'source_request_freshness_present=1' "$status_file"
require_contains 'source_signed_request_present=1' "$status_file"
require_contains 'source_runtime_dry_run_present=1' "$status_file"
require_contains 'source_denial_reason_present=1' "$status_file"
require_contains 'capability_name=seal.capability.report' "$status_file"
require_contains 'capability_known=1' "$status_file"
require_contains 'capability_candidate=1' "$status_file"
require_contains 'policy_decision_state=report-only' "$status_file"
require_contains 'request_freshness_state=report-only' "$status_file"
require_contains 'signed_request_state=report-only' "$status_file"
require_contains 'runtime_dry_run_state=report-only' "$status_file"
require_contains 'default_action_deny=1' "$status_file"
require_contains 'would_allow=0' "$status_file"
require_contains 'would_deny=1' "$status_file"
require_contains 'would_require_operator_review=1' "$status_file"
require_contains 'would_execute_tool=0' "$status_file"
require_contains 'would_read_host=0' "$status_file"
require_contains 'would_write_host=0' "$status_file"
require_contains 'would_use_network=0' "$status_file"
require_contains 'would_grant_runtime_authority=0' "$status_file"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$status_file"
require_contains 'receipt_complete=1' "$status_file"
require_contains 'receipt_invalid=0' "$status_file"
require_contains 'report_only=1' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'Panel-visible Seal dashboard planning checkpoint' "$status_file"
require_contains 'local capability registry schema contract' "$status_file"

printf 'latticra seal operator receipt report status: ok\n'
