#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal guarded allowlist report surface status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal guarded allowlist report surface status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE.md
require_file scripts/latticra-seal-guarded-allowlist-report.sh
require_file scripts/test-latticra-seal-guarded-allowlist-report-surface.sh
require_file tests/seal_guarded_allowlist_report_surface.c
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md
require_file scripts/test-latticra-seal-guarded-allowlist.sh

require_contains 'Status: status record for the Latticra Seal guarded allowlist report surface' "$status_file"
require_contains 'Source: PR #312' "$status_file"
require_contains 'seal_guarded_allowlist_report_surface_document_present=1' "$status_file"
require_contains 'seal_guarded_allowlist_report_surface_fixture_present=1' "$status_file"
require_contains 'seal_guarded_allowlist_report_runner_present=1' "$status_file"
require_contains 'seal_guarded_allowlist_report_surface_guard_present=1' "$status_file"
require_contains 'operator_visible_guarded_allowlist_report=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'known_fixture_tool_candidate_visible=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1' "$status_file"
require_contains 'tool_name=latticra.seal.report' "$status_file"
require_contains 'allowlist_source=deterministic-local-fixture' "$status_file"
require_contains 'allowlist_entry_count=3' "$status_file"
require_contains 'allowlist_lookup_performed=1' "$status_file"
require_contains 'requested_tool_name_present=1' "$status_file"
require_contains 'requested_tool_known=1' "$status_file"
require_contains 'requested_tool_unknown=0' "$status_file"
require_contains 'requested_tool_candidate=1' "$status_file"
require_contains 'requested_tool_allow_candidate=1' "$status_file"
require_contains 'allow_candidate_requires_policy_decision=1' "$status_file"
require_contains 'allow_candidate_requires_runtime_gate=1' "$status_file"
require_contains 'allow_candidate_requires_runtime_dry_run=1' "$status_file"
require_contains 'allow_candidate_requires_operator_review=1' "$status_file"
require_contains 'allow_candidate_grants_authority=0' "$status_file"
require_contains 'allow_candidate_executes_tool=0' "$status_file"
require_contains 'allow_candidate_reads_host=0' "$status_file"
require_contains 'allow_candidate_writes_host=0' "$status_file"
require_contains 'allow_candidate_uses_network=0' "$status_file"
require_contains 'default_action_deny=1' "$status_file"
require_contains 'would_allow=0' "$status_file"
require_contains 'would_deny=1' "$status_file"
require_contains 'would_require_operator_review=1' "$status_file"
require_contains 'blocked_reason=known-tool-candidate-still-denied' "$status_file"
require_contains 'report_only=1' "$status_file"
require_contains 'mode=report-only' "$status_file"
require_contains 'status=guarded-allowlist-metadata' "$status_file"
require_contains 'guarded allowlist status-index alignment' "$status_file"

printf 'latticra seal guarded allowlist report surface status: ok\n'
