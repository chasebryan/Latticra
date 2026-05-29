#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-guarded-allowlist-report-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal guarded allowlist report surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal guarded allowlist report surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc="docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE.md"
report="$tmpdir/latticra-seal-guarded-allowlist-report.out"

require_file "$doc"
require_file tests/seal_guarded_allowlist_report_surface.c
require_file scripts/latticra-seal-guarded-allowlist-report.sh
require_file include/latticra/seal_guarded_allowlist.h
require_file src/seal_guarded_allowlist.c
require_file scripts/test-latticra-seal-guarded-allowlist.sh
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md

require_contains 'Status: report surface for the Latticra Seal guarded allowlist metadata layer' "$doc"
require_contains 'tests/seal_guarded_allowlist_report_surface.c' "$doc"
require_contains 'scripts/latticra-seal-guarded-allowlist-report.sh' "$doc"
require_contains 'LATTICRA SEAL GUARDED ALLOWLIST' "$doc"
require_contains 'guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1' "$doc"
require_contains 'tool_name=latticra.seal.report' "$doc"
require_contains 'allowlist_source=deterministic-local-fixture' "$doc"
require_contains 'allowlist_entry_count=3' "$doc"
require_contains 'allowlist_lookup_performed=1' "$doc"
require_contains 'requested_tool_name_present=1' "$doc"
require_contains 'requested_tool_known=1' "$doc"
require_contains 'requested_tool_unknown=0' "$doc"
require_contains 'requested_tool_candidate=1' "$doc"
require_contains 'requested_tool_allow_candidate=1' "$doc"
require_contains 'allow_candidate_requires_policy_decision=1' "$doc"
require_contains 'allow_candidate_requires_runtime_gate=1' "$doc"
require_contains 'allow_candidate_requires_runtime_dry_run=1' "$doc"
require_contains 'allow_candidate_requires_operator_review=1' "$doc"
require_contains 'allow_candidate_grants_authority=0' "$doc"
require_contains 'allow_candidate_executes_tool=0' "$doc"
require_contains 'allow_candidate_reads_host=0' "$doc"
require_contains 'allow_candidate_writes_host=0' "$doc"
require_contains 'allow_candidate_uses_network=0' "$doc"
require_contains 'default_action_deny=1' "$doc"
require_contains 'would_allow=0' "$doc"
require_contains 'would_deny=1' "$doc"
require_contains 'would_require_operator_review=1' "$doc"
require_contains 'blocked_reason=known-tool-candidate-still-denied' "$doc"
require_contains 'report_only=1' "$doc"
require_contains 'mode=report-only' "$doc"
require_contains 'status=guarded-allowlist-metadata' "$doc"
require_contains 'guarded allowlist report status alignment' "$doc"

sh scripts/latticra-seal-guarded-allowlist-report.sh > "$report"

require_contains 'LATTICRA SEAL GUARDED ALLOWLIST' "$report"
require_contains 'guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1' "$report"
require_contains 'tool_name=latticra.seal.report' "$report"
require_contains 'allowlist_source=deterministic-local-fixture' "$report"
require_contains 'allowlist_entry_count=3' "$report"
require_contains 'allowlist_lookup_performed=1' "$report"
require_contains 'requested_tool_name_present=1' "$report"
require_contains 'requested_tool_known=1' "$report"
require_contains 'requested_tool_unknown=0' "$report"
require_contains 'requested_tool_candidate=1' "$report"
require_contains 'requested_tool_allow_candidate=1' "$report"
require_contains 'allow_candidate_grants_authority=0' "$report"
require_contains 'allow_candidate_executes_tool=0' "$report"
require_contains 'allow_candidate_reads_host=0' "$report"
require_contains 'allow_candidate_writes_host=0' "$report"
require_contains 'allow_candidate_uses_network=0' "$report"
require_contains 'would_allow=0' "$report"
require_contains 'would_deny=1' "$report"
require_contains 'blocked_reason=known-tool-candidate-still-denied' "$report"
require_contains 'report_only=1' "$report"
require_contains 'mode=report-only' "$report"
require_contains 'status=guarded-allowlist-metadata' "$report"

printf 'latticra seal guarded allowlist report surface: ok\n'
