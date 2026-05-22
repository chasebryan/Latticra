#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal runtime dry-run implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal runtime dry-run implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md
require_file scripts/test-latticra-seal-runtime-dry-run-contract.sh
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_CORE_EVIDENCE_STATUS.md

require_contains 'Status: implementation planning contract for a future no-effect Latticra Seal runtime dry-run surface' "$plan"
require_contains 'include/latticra/seal_runtime_dry_run.h' "$plan"
require_contains 'src/seal_runtime_dry_run.c' "$plan"
require_contains 'tests/seal_runtime_dry_run_invariants.c' "$plan"
require_contains 'scripts/test-latticra-seal-runtime-dry-run.sh' "$plan"
require_contains 'latticra_seal_runtime_dry_run_t' "$plan"
require_contains 'latticra_seal_runtime_dry_run_from_policy_and_gate' "$plan"
require_contains 'LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_POLICY_DECISION' "$plan"
require_contains 'LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_RUNTIME_GATE' "$plan"
require_contains 'runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1' "$plan"
require_contains 'request_class=core-blocked-request' "$plan"
require_contains 'blocked_reason=default-deny-dry-run' "$plan"
require_contains 'dry_run_supported=1' "$plan"
require_contains 'dry_run_performed=1' "$plan"
require_contains 'input_policy_decision_present=1' "$plan"
require_contains 'input_runtime_gate_present=1' "$plan"
require_contains 'policy_decision_report_only=1' "$plan"
require_contains 'runtime_gate_report_only=1' "$plan"
require_contains 'default_action_deny=1' "$plan"
require_contains 'would_allow=0' "$plan"
require_contains 'would_deny=1' "$plan"
require_contains 'would_require_operator_review=1' "$plan"
require_contains 'would_execute_tool=0' "$plan"
require_contains 'would_read_host=0' "$plan"
require_contains 'would_write_host=0' "$plan"
require_contains 'would_use_network=0' "$plan"
require_contains 'would_grant_runtime_authority=0' "$plan"
require_contains 'unknown_tool_denied=1' "$plan"
require_contains 'unsigned_request_denied=1' "$plan"
require_contains 'invalid_schema_denied=1' "$plan"
require_contains 'stale_request_denied=1' "$plan"
require_contains 'replayed_request_denied=1' "$plan"
require_contains 'invalid_signature_denied=1' "$plan"
require_contains 'LATTICRA SEAL RUNTIME DRY RUN' "$plan"
require_contains 'No runtime enforcement work may begin from this plan alone.' "$plan"
require_contains 'The next valid Latticra Seal slice is the no-effect runtime dry-run implementation.' "$plan"

printf 'latticra seal runtime dry-run implementation plan: ok\n'
