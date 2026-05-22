#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal runtime dry-run contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal runtime dry-run contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md"

require_file "$contract"
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_CORE_EVIDENCE_STATUS.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
require_file docs/LATTICRA_SEAL_RUNTIME_GATE_IMPLEMENTATION.md

require_contains 'Status: planning contract for a future Latticra Seal runtime dry-run surface' "$contract"
require_contains 'If this request reached the Seal runtime boundary, what would the boundary report, deny, and refuse to do?' "$contract"
require_contains 'seal_policy_decision_report_surface_present=1' "$contract"
require_contains 'seal_runtime_gate_metadata_present=1' "$contract"
require_contains 'seal_core_blocked_case_set_complete=1' "$contract"
require_contains 'runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1' "$contract"
require_contains 'dry_run_supported=1' "$contract"
require_contains 'dry_run_performed=1' "$contract"
require_contains 'default_action=deny' "$contract"
require_contains 'would_allow=0' "$contract"
require_contains 'would_deny=1' "$contract"
require_contains 'would_require_operator_review=1' "$contract"
require_contains 'would_execute_tool=0' "$contract"
require_contains 'would_read_host=0' "$contract"
require_contains 'would_write_host=0' "$contract"
require_contains 'would_use_network=0' "$contract"
require_contains 'would_grant_runtime_authority=0' "$contract"
require_contains 'report_only=1' "$contract"
require_contains 'mode=report-only' "$contract"
require_contains 'unknown_tool_denied=1' "$contract"
require_contains 'unsigned_request_denied=1' "$contract"
require_contains 'invalid_schema_denied=1' "$contract"
require_contains 'stale_request_denied=1' "$contract"
require_contains 'replayed_request_denied=1' "$contract"
require_contains 'invalid_signature_denied=1' "$contract"
require_contains 'This contract does not authorize runtime enforcement.' "$contract"
require_contains 'The next valid slice is a no-effect runtime dry-run implementation plan.' "$contract"

printf 'latticra seal runtime dry-run contract: ok\n'
