#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal guarded allowlist status index alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal guarded allowlist status index alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_GUARDED_ALLOWLIST_STATUS_INDEX_ALIGNMENT.md"
index="docs/status/README.md"

require_file "$record"
require_file "$index"
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION_PLAN.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE.md
require_file docs/status/SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE_STATUS.md
require_file scripts/test-latticra-seal-guarded-allowlist-contract.sh
require_file scripts/test-latticra-seal-guarded-allowlist-implementation-plan.sh
require_file scripts/test-latticra-seal-guarded-allowlist.sh
require_file scripts/test-latticra-seal-guarded-allowlist-report-surface.sh
require_file scripts/test-latticra-seal-guarded-allowlist-report-surface-status.sh

require_contains 'Status: index alignment record for the Latticra Seal guarded allowlist report surface status' "$record"
require_contains 'Source: PR #313' "$record"
require_contains 'guarded allowlist contract -> guarded allowlist implementation plan -> guarded allowlist implementation -> guarded allowlist report surface -> guarded allowlist report surface status -> status index alignment' "$record"
require_contains 'seal_guarded_allowlist_contract_present=1' "$record"
require_contains 'seal_guarded_allowlist_implementation_plan_present=1' "$record"
require_contains 'seal_guarded_allowlist_implementation_present=1' "$record"
require_contains 'seal_guarded_allowlist_report_surface_present=1' "$record"
require_contains 'seal_guarded_allowlist_report_surface_status_present=1' "$record"
require_contains 'seal_guarded_allowlist_status_index_alignment_record_present=1' "$record"
require_contains 'operator_visible_guarded_allowlist_report=1' "$record"
require_contains 'known_fixture_tool_candidate_visible=1' "$record"
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
require_contains 'requested_tool_known=1' "$record"
require_contains 'requested_tool_candidate=1' "$record"
require_contains 'requested_tool_allow_candidate=1' "$record"
require_contains 'allow_candidate_grants_authority=0' "$record"
require_contains 'allow_candidate_executes_tool=0' "$record"
require_contains 'allow_candidate_reads_host=0' "$record"
require_contains 'allow_candidate_writes_host=0' "$record"
require_contains 'allow_candidate_uses_network=0' "$record"
require_contains 'would_allow=0' "$record"
require_contains 'would_deny=1' "$record"
require_contains 'would_require_operator_review=1' "$record"
require_contains 'blocked_reason=known-tool-candidate-still-denied' "$record"
require_contains 'report_only=1' "$record"
require_contains 'status=guarded-allowlist-metadata' "$record"
require_contains 'public entry-point refresh for the completed guarded allowlist milestone' "$record"

printf 'latticra seal guarded allowlist status index alignment: ok\n'
