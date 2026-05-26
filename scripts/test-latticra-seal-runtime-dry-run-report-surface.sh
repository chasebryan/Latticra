#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-runtime-dry-run-report-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal runtime dry-run report surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal runtime dry-run report surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc="docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md"
report="$tmpdir/latticra-seal-runtime-dry-run-report.out"

require_file "$doc"
require_file tests/seal_runtime_dry_run_report_surface.c
require_file scripts/latticra-seal-runtime-dry-run-report.sh
require_file include/latticra/seal_runtime_dry_run.h
require_file src/seal_runtime_dry_run.c
require_file scripts/test-latticra-seal-runtime-dry-run.sh
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md

require_contains 'Status: report surface for the Latticra Seal runtime dry-run metadata layer' "$doc"
require_contains 'tests/seal_runtime_dry_run_report_surface.c' "$doc"
require_contains 'scripts/latticra-seal-runtime-dry-run-report.sh' "$doc"
require_contains 'LATTICRA SEAL RUNTIME DRY RUN' "$doc"
require_contains 'runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1' "$doc"
require_contains 'request_class=core-blocked-request' "$doc"
require_contains 'policy_decision_state=report-only' "$doc"
require_contains 'runtime_gate_state=report-only' "$doc"
require_contains 'blocked_reason=default-deny-dry-run' "$doc"
require_contains 'dry_run_supported=1' "$doc"
require_contains 'dry_run_performed=1' "$doc"
require_contains 'input_policy_decision_present=1' "$doc"
require_contains 'input_runtime_gate_present=1' "$doc"
require_contains 'policy_decision_report_only=1' "$doc"
require_contains 'runtime_gate_report_only=1' "$doc"
require_contains 'default_action_deny=1' "$doc"
require_contains 'would_allow=0' "$doc"
require_contains 'would_deny=1' "$doc"
require_contains 'would_require_operator_review=1' "$doc"
require_contains 'would_execute_tool=0' "$doc"
require_contains 'would_read_host=0' "$doc"
require_contains 'would_write_host=0' "$doc"
require_contains 'would_use_network=0' "$doc"
require_contains 'would_grant_runtime_authority=0' "$doc"
require_contains 'unknown_tool_denied=1' "$doc"
require_contains 'unsigned_request_denied=1' "$doc"
require_contains 'invalid_schema_denied=1' "$doc"
require_contains 'stale_request_denied=1' "$doc"
require_contains 'replayed_request_denied=1' "$doc"
require_contains 'invalid_signature_denied=1' "$doc"
require_contains 'report_only=1' "$doc"
require_contains 'mode=report-only' "$doc"
require_contains 'status=runtime-dry-run-metadata' "$doc"
require_contains 'runtime dry-run report status alignment' "$doc"

sh scripts/latticra-seal-runtime-dry-run-report.sh > "$report"

require_contains 'LATTICRA SEAL RUNTIME DRY RUN' "$report"
require_contains 'runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1' "$report"
require_contains 'request_class=core-blocked-request' "$report"
require_contains 'blocked_reason=default-deny-dry-run' "$report"
require_contains 'dry_run_performed=1' "$report"
require_contains 'would_allow=0' "$report"
require_contains 'would_deny=1' "$report"
require_contains 'would_execute_tool=0' "$report"
require_contains 'would_read_host=0' "$report"
require_contains 'would_write_host=0' "$report"
require_contains 'would_use_network=0' "$report"
require_contains 'would_grant_runtime_authority=0' "$report"
require_contains 'report_only=1' "$report"
require_contains 'status=runtime-dry-run-metadata' "$report"

printf 'latticra seal runtime dry-run report surface: ok\n'
