#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal guarded allowlist public entrypoint alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal guarded allowlist public entrypoint alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_GUARDED_ALLOWLIST_PUBLIC_ENTRYPOINT_ALIGNMENT.md"
readme="README.md"

require_file "$record"
require_file "$readme"
require_file docs/status/SEAL_GUARDED_ALLOWLIST_STATUS_INDEX_ALIGNMENT.md
require_file docs/status/SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE_STATUS.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION_PLAN.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE.md
require_file scripts/test-latticra-seal-guarded-allowlist-status-index-alignment.sh

require_contains 'Status: public-entrypoint alignment record for the Latticra Seal guarded allowlist milestone' "$record"
require_contains 'Source: PR #315' "$record"
require_contains 'seal_guarded_allowlist_public_entrypoint_alignment_present=1' "$record"
require_contains 'readme_mentions_guarded_allowlist_metadata=1' "$record"
require_contains 'readme_mentions_guarded_allowlist_report_surface=1' "$record"
require_contains 'readme_links_guarded_allowlist_contract=1' "$record"
require_contains 'readme_links_guarded_allowlist_implementation_plan=1' "$record"
require_contains 'readme_links_guarded_allowlist_implementation=1' "$record"
require_contains 'readme_links_guarded_allowlist_report_surface=1' "$record"
require_contains 'readme_links_guarded_allowlist_report_surface_status=1' "$record"
require_contains 'readme_links_guarded_allowlist_status_index_alignment=1' "$record"
require_contains 'readme_mentions_operator_visible_guarded_allowlist_report=1' "$record"
require_contains 'readme_mentions_known_fixture_tool_candidate_only=1' "$record"
require_contains 'readme_mentions_no_runtime_authority=1' "$record"
require_contains 'mode=public-entrypoint-alignment' "$record"
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
require_contains 'capability metadata contract' "$record"

require_contains 'latticra_seal_guarded_allowlist_report_surface_present=1' "$readme"
require_contains 'seal_guarded_allowlist_metadata_present=1' "$readme"
require_contains 'seal_guarded_allowlist_report_surface_present=1' "$readme"
require_contains 'operator_visible_guarded_allowlist_report=1' "$readme"
require_contains 'guarded_allowlist_status_index_alignment_present=1' "$readme"
require_contains 'known_fixture_tool_candidate_visible=1' "$readme"
require_contains 'allow_candidate_grants_authority=0' "$readme"
require_contains 'allow_candidate_executes_tool=0' "$readme"
require_contains 'allow_candidate_reads_host=0' "$readme"
require_contains 'allow_candidate_writes_host=0' "$readme"
require_contains 'allow_candidate_uses_network=0' "$readme"
require_contains 'report-only runtime dry-run and guarded allowlist candidate-denial paths' "$readme"
require_contains 'docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md' "$readme"
require_contains 'docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION_PLAN.md' "$readme"
require_contains 'docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md' "$readme"
require_contains 'docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE.md' "$readme"
require_contains 'docs/status/SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE_STATUS.md' "$readme"
require_contains 'docs/status/SEAL_GUARDED_ALLOWLIST_STATUS_INDEX_ALIGNMENT.md' "$readme"
require_contains 'docs/status/SEAL_GUARDED_ALLOWLIST_PUBLIC_ENTRYPOINT_ALIGNMENT.md' "$readme"
require_contains 'test-latticra-seal-guarded-allowlist-public-entrypoint-alignment.sh' "$record"

printf 'latticra seal guarded allowlist public entrypoint alignment: ok\n'
