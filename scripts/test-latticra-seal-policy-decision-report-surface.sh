#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-policy-decision-report-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal policy decision report surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal policy decision report surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc="docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md"
report="$tmpdir/latticra-seal-policy-decision-report.out"

require_file "$doc"
require_file tests/seal_policy_decision_report_surface.c
require_file scripts/latticra-seal-policy-decision-report.sh
require_file docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
require_file docs/status/SEAL_POLICY_DECISION_STATUS.md
require_file scripts/test-latticra-seal-policy-decision-status.sh

require_contains 'Status: report-only policy decision report surface' "$doc"
require_contains 'tests/seal_policy_decision_report_surface.c' "$doc"
require_contains 'scripts/latticra-seal-policy-decision-report.sh' "$doc"
require_contains 'LATTICRA SEAL POLICY DECISION' "$doc"
require_contains 'policy_decision_profile=latticra-seal-policy-decision/0.1' "$doc"
require_contains 'policy_decision_supported=0' "$doc"
require_contains 'policy_evaluation_supported=0' "$doc"
require_contains 'policy_enforcement_supported=0' "$doc"
require_contains 'default_decision=deny' "$doc"
require_contains 'decision_state=report-only' "$doc"
require_contains 'decision_allowed=0' "$doc"
require_contains 'decision_denied=1' "$doc"
require_contains 'operator_review_required=1' "$doc"
require_contains 'unknown_tool_denied=1' "$doc"
require_contains 'unsigned_request_denied=1' "$doc"
require_contains 'invalid_schema_denied=1' "$doc"
require_contains 'stale_request_denied=1' "$doc"
require_contains 'replayed_request_denied=1' "$doc"
require_contains 'invalid_signature_denied=1' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'host_read_performed=0' "$doc"
require_contains 'host_write_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'mode=report-only' "$doc"
require_contains 'decision=report-only' "$doc"
require_contains 'reason=policy-decision-metadata-only' "$doc"
require_contains 'status=policy-decision-metadata' "$doc"
require_contains 'It renders metadata only.' "$doc"
require_contains 'policy-decision report status alignment' "$doc"

sh scripts/latticra-seal-policy-decision-report.sh > "$report"

require_contains 'LATTICRA SEAL POLICY DECISION' "$report"
require_contains 'policy_decision_profile=latticra-seal-policy-decision/0.1' "$report"
require_contains 'default_decision=deny' "$report"
require_contains 'decision_allowed=0' "$report"
require_contains 'decision_denied=1' "$report"
require_contains 'operator_review_required=1' "$report"
require_contains 'unknown_tool_denied=1' "$report"
require_contains 'unsigned_request_denied=1' "$report"
require_contains 'stale_request_denied=1' "$report"
require_contains 'replayed_request_denied=1' "$report"
require_contains 'invalid_signature_denied=1' "$report"
require_contains 'runtime_authority_granted=0' "$report"
require_contains 'host_read_performed=0' "$report"
require_contains 'host_write_performed=0' "$report"
require_contains 'network_performed=0' "$report"
require_contains 'status=policy-decision-metadata' "$report"

printf 'latticra seal policy decision report surface: ok\n'
