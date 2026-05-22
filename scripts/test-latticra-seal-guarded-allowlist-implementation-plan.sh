#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal guarded allowlist implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal guarded allowlist implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md
require_file scripts/test-latticra-seal-guarded-allowlist-contract.sh
require_file docs/status/SEAL_RUNTIME_DRY_RUN_PUBLIC_ENTRYPOINT_ALIGNMENT.md

require_contains 'Status: implementation planning contract for a future no-effect Latticra Seal guarded allowlist surface' "$plan"
require_contains 'include/latticra/seal_guarded_allowlist.h' "$plan"
require_contains 'src/seal_guarded_allowlist.c' "$plan"
require_contains 'tests/seal_guarded_allowlist_invariants.c' "$plan"
require_contains 'scripts/test-latticra-seal-guarded-allowlist.sh' "$plan"
require_contains 'latticra_seal_guarded_allowlist_t' "$plan"
require_contains 'latticra_seal_guarded_allowlist_result_t' "$plan"
require_contains 'latticra_seal_guarded_allowlist_result_unknown' "$plan"
require_contains 'latticra_seal_guarded_allowlist_result_candidate' "$plan"
require_contains 'LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME' "$plan"
require_contains 'LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_ALLOWLIST' "$plan"
require_contains 'guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1' "$plan"
require_contains 'allowlist_source=deterministic-local-fixture' "$plan"
require_contains 'allowlist_entry_count=3' "$plan"
require_contains 'latticra.seal.inspect' "$plan"
require_contains 'latticra.seal.report' "$plan"
require_contains 'latticra.seal.dry_run' "$plan"
require_contains 'requested_tool_known=0' "$plan"
require_contains 'requested_tool_unknown=1' "$plan"
require_contains 'requested_tool_candidate=0' "$plan"
require_contains 'requested_tool_allow_candidate=0' "$plan"
require_contains 'requested_tool_known=1' "$plan"
require_contains 'requested_tool_candidate=1' "$plan"
require_contains 'requested_tool_allow_candidate=1' "$plan"
require_contains 'allow_candidate_grants_authority=0' "$plan"
require_contains 'allow_candidate_executes_tool=0' "$plan"
require_contains 'allow_candidate_reads_host=0' "$plan"
require_contains 'allow_candidate_writes_host=0' "$plan"
require_contains 'allow_candidate_uses_network=0' "$plan"
require_contains 'default_action_deny=1' "$plan"
require_contains 'would_allow=0' "$plan"
require_contains 'would_deny=1' "$plan"
require_contains 'would_require_operator_review=1' "$plan"
require_contains 'blocked_reason=default-deny-guarded-allowlist' "$plan"
require_contains 'blocked_reason=known-tool-candidate-still-denied' "$plan"
require_contains 'LATTICRA SEAL GUARDED ALLOWLIST' "$plan"
require_contains 'small report buffers fail closed' "$plan"
require_contains 'oversized tool name fails closed' "$plan"
require_contains 'turn allowlist matches into execution grants' "$plan"
require_contains 'No runtime enforcement work may begin from this plan alone.' "$plan"
require_contains 'The next valid Latticra Seal slice is the no-effect guarded allowlist implementation.' "$plan"

printf 'latticra seal guarded allowlist implementation plan: ok\n'
