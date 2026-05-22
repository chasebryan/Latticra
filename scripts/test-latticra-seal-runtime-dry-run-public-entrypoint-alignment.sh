#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal runtime dry-run public entrypoint alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal runtime dry-run public entrypoint alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_RUNTIME_DRY_RUN_PUBLIC_ENTRYPOINT_ALIGNMENT.md"
readme="README.md"

require_file "$record"
require_file "$readme"
require_file docs/status/SEAL_RUNTIME_DRY_RUN_STATUS_INDEX_ALIGNMENT.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION_PLAN.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
require_file scripts/test-latticra-seal-runtime-dry-run-status-index-alignment.sh

require_contains 'Status: public-entrypoint alignment record for the Latticra Seal runtime dry-run milestone' "$record"
require_contains 'Source: PR #307' "$record"
require_contains 'seal_runtime_dry_run_public_entrypoint_alignment_present=1' "$record"
require_contains 'readme_mentions_runtime_dry_run_metadata=1' "$record"
require_contains 'readme_mentions_runtime_dry_run_report_surface=1' "$record"
require_contains 'readme_links_runtime_dry_run_contract=1' "$record"
require_contains 'readme_links_runtime_dry_run_implementation=1' "$record"
require_contains 'readme_links_runtime_dry_run_report_surface=1' "$record"
require_contains 'readme_links_runtime_dry_run_report_surface_status=1' "$record"
require_contains 'readme_links_runtime_dry_run_status_index_alignment=1' "$record"
require_contains 'readme_mentions_operator_visible_runtime_dry_run_report=1' "$record"
require_contains 'readme_mentions_default_deny_dry_run=1' "$record"
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
require_contains 'guarded allowlist planning contract' "$record"

require_contains 'latticra_seal_runtime_dry_run_report_surface_present=1' "$readme"
require_contains 'seal_runtime_dry_run_metadata_present=1' "$readme"
require_contains 'seal_runtime_dry_run_report_surface_present=1' "$readme"
require_contains 'operator_visible_runtime_dry_run_report=1' "$readme"
require_contains 'runtime_dry_run_status_index_alignment_present=1' "$readme"
require_contains 'blocked_reason=default-deny-dry-run' "$readme"
require_contains 'would_execute_tool=0' "$readme"
require_contains 'would_read_host=0' "$readme"
require_contains 'would_write_host=0' "$readme"
require_contains 'would_use_network=0' "$readme"
require_contains 'would_grant_runtime_authority=0' "$readme"
require_contains 'runtime_authority_granted=0' "$readme"
require_contains 'report-only runtime dry-run path with operator-visible denial reporting' "$readme"
require_contains 'docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md' "$readme"
require_contains 'docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md' "$readme"
require_contains 'docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md' "$readme"
require_contains 'docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md' "$readme"
require_contains 'docs/status/SEAL_RUNTIME_DRY_RUN_STATUS_INDEX_ALIGNMENT.md' "$readme"
require_contains 'docs/status/SEAL_RUNTIME_DRY_RUN_PUBLIC_ENTRYPOINT_ALIGNMENT.md' "$readme"
require_contains 'test-latticra-seal-runtime-dry-run-public-entrypoint-alignment.sh' "$record"

printf 'latticra seal runtime dry-run public entrypoint alignment: ok\n'
