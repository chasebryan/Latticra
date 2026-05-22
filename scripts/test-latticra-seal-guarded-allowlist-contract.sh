#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal guarded allowlist contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal guarded allowlist contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_STATUS_INDEX_ALIGNMENT.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_PUBLIC_ENTRYPOINT_ALIGNMENT.md
require_file scripts/test-latticra-seal-runtime-dry-run-public-entrypoint-alignment.sh

require_contains 'Status: planning contract for a future Latticra Seal guarded allowlist surface' "$contract"
require_contains 'If a tool name is known to Latticra Seal, can the boundary report that it is only a candidate for later review while still denying every effect?' "$contract"
require_contains 'seal_runtime_dry_run_metadata_present=1' "$contract"
require_contains 'seal_runtime_dry_run_report_surface_present=1' "$contract"
require_contains 'seal_runtime_dry_run_report_surface_status_present=1' "$contract"
require_contains 'seal_runtime_dry_run_status_index_alignment_present=1' "$contract"
require_contains 'seal_runtime_dry_run_public_entrypoint_alignment_present=1' "$contract"
require_contains 'operator_visible_runtime_dry_run_report=1' "$contract"
require_contains 'guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1' "$contract"
require_contains 'allowlist_contract_present' "$contract"
require_contains 'allowlist_planning_only=1' "$contract"
require_contains 'allowlist_lookup_performed=1' "$contract"
require_contains 'requested_tool_known=0' "$contract"
require_contains 'requested_tool_unknown=1' "$contract"
require_contains 'requested_tool_candidate=0' "$contract"
require_contains 'requested_tool_allow_candidate=0' "$contract"
require_contains 'allow_candidate_requires_policy_decision=1' "$contract"
require_contains 'allow_candidate_requires_runtime_gate=1' "$contract"
require_contains 'allow_candidate_requires_runtime_dry_run=1' "$contract"
require_contains 'allow_candidate_requires_operator_review=1' "$contract"
require_contains 'allow_candidate_grants_authority=0' "$contract"
require_contains 'allow_candidate_executes_tool=0' "$contract"
require_contains 'allow_candidate_reads_host=0' "$contract"
require_contains 'allow_candidate_writes_host=0' "$contract"
require_contains 'allow_candidate_uses_network=0' "$contract"
require_contains 'default_action=deny' "$contract"
require_contains 'would_allow=0' "$contract"
require_contains 'would_deny=1' "$contract"
require_contains 'would_require_operator_review=1' "$contract"
require_contains 'blocked_reason=default-deny-guarded-allowlist' "$contract"
require_contains 'report_only=1' "$contract"
require_contains 'mode=report-only' "$contract"
require_contains 'status=guarded-allowlist-metadata' "$contract"
require_contains 'unknown_tool_denied=1' "$contract"
require_contains 'unsigned_request_denied=1' "$contract"
require_contains 'invalid_schema_denied=1' "$contract"
require_contains 'stale_request_denied=1' "$contract"
require_contains 'replayed_request_denied=1' "$contract"
require_contains 'invalid_signature_denied=1' "$contract"
require_contains 'A known tool name may only become a candidate classification.' "$contract"
require_contains 'turn allowlist matches into execution grants' "$contract"
require_contains 'This contract does not authorize runtime enforcement.' "$contract"
require_contains 'a separate runtime authority contract would be required' "$contract"
require_contains 'The next valid slice is a no-effect guarded allowlist implementation plan.' "$contract"

printf 'latticra seal guarded allowlist contract: ok\n'
