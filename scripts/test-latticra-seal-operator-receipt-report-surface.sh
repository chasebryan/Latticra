#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-operator-receipt-report-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal operator receipt report surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal operator receipt report surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc="docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md"
report="$tmpdir/latticra-seal-operator-receipt-report.out"

require_file "$doc"
require_file tests/seal_operator_receipt_report_surface.c
require_file scripts/latticra-seal-operator-receipt-report.sh
require_file include/latticra/seal_operator_receipt_report.h
require_file src/seal_operator_receipt_report.c
require_file scripts/test-latticra-seal-operator-receipt-report.sh
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md

require_contains 'Status: report surface for the Latticra Seal operator receipt report' "$doc"
require_contains 'tests/seal_operator_receipt_report_surface.c' "$doc"
require_contains 'scripts/latticra-seal-operator-receipt-report.sh' "$doc"
require_contains 'LATTICRA SEAL OPERATOR RECEIPT REPORT' "$doc"
require_contains 'operator_receipt_profile=latticra-seal-operator-receipt-report/0.1' "$doc"
require_contains 'receipt_mode=report-only' "$doc"
require_contains 'receipt_status=denied-report-only' "$doc"
require_contains 'source_capability_metadata_present=1' "$doc"
require_contains 'source_policy_decision_present=1' "$doc"
require_contains 'source_request_freshness_present=1' "$doc"
require_contains 'source_signed_request_present=1' "$doc"
require_contains 'source_runtime_dry_run_present=1' "$doc"
require_contains 'source_denial_reason_present=1' "$doc"
require_contains 'capability_name=seal.capability.report' "$doc"
require_contains 'capability_known=1' "$doc"
require_contains 'capability_candidate=1' "$doc"
require_contains 'policy_decision_state=report-only' "$doc"
require_contains 'request_freshness_state=report-only' "$doc"
require_contains 'signed_request_state=report-only' "$doc"
require_contains 'runtime_dry_run_state=report-only' "$doc"
require_contains 'default_action_deny=1' "$doc"
require_contains 'would_allow=0' "$doc"
require_contains 'would_deny=1' "$doc"
require_contains 'would_require_operator_review=1' "$doc"
require_contains 'would_execute_tool=0' "$doc"
require_contains 'would_read_host=0' "$doc"
require_contains 'would_write_host=0' "$doc"
require_contains 'would_use_network=0' "$doc"
require_contains 'would_grant_runtime_authority=0' "$doc"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$doc"
require_contains 'receipt_complete=1' "$doc"
require_contains 'receipt_invalid=0' "$doc"
require_contains 'report_only=1' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'effect_performed=0' "$doc"
require_contains 'host_read_performed=0' "$doc"
require_contains 'host_write_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'operator receipt report status alignment' "$doc"

sh scripts/latticra-seal-operator-receipt-report.sh > "$report"

require_contains 'LATTICRA SEAL OPERATOR RECEIPT REPORT' "$report"
require_contains 'operator_receipt_profile=latticra-seal-operator-receipt-report/0.1' "$report"
require_contains 'receipt_mode=report-only' "$report"
require_contains 'receipt_status=denied-report-only' "$report"
require_contains 'source_capability_metadata_present=1' "$report"
require_contains 'source_policy_decision_present=1' "$report"
require_contains 'source_request_freshness_present=1' "$report"
require_contains 'source_signed_request_present=1' "$report"
require_contains 'source_runtime_dry_run_present=1' "$report"
require_contains 'source_denial_reason_present=1' "$report"
require_contains 'capability_name=seal.capability.report' "$report"
require_contains 'capability_known=1' "$report"
require_contains 'capability_candidate=1' "$report"
require_contains 'policy_decision_state=report-only' "$report"
require_contains 'request_freshness_state=report-only' "$report"
require_contains 'signed_request_state=report-only' "$report"
require_contains 'runtime_dry_run_state=report-only' "$report"
require_contains 'would_allow=0' "$report"
require_contains 'would_deny=1' "$report"
require_contains 'would_execute_tool=0' "$report"
require_contains 'would_read_host=0' "$report"
require_contains 'would_write_host=0' "$report"
require_contains 'would_use_network=0' "$report"
require_contains 'would_grant_runtime_authority=0' "$report"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$report"
require_contains 'receipt_complete=1' "$report"
require_contains 'receipt_invalid=0' "$report"
require_contains 'report_only=1' "$report"
require_contains 'runtime_authority_granted=0' "$report"
require_contains 'effect_performed=0' "$report"
require_contains 'host_read_performed=0' "$report"
require_contains 'host_write_performed=0' "$report"
require_contains 'network_performed=0' "$report"
require_contains 'error=ok' "$report"

printf 'latticra seal operator receipt report surface: ok\n'
