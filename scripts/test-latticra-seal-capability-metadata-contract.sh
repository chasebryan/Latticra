#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal capability metadata contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal capability metadata contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_CAPABILITY_METADATA_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE.md
require_file docs/status/SEAL_GUARDED_ALLOWLIST_PUBLIC_ENTRYPOINT_ALIGNMENT.md
require_file scripts/test-latticra-seal-guarded-allowlist-public-entrypoint-alignment.sh

require_contains 'Status: planning contract for a future Latticra Seal capability metadata surface' "$contract"
require_contains 'If a tool request names a capability, can Latticra Seal describe that capability as metadata without granting the authority to use it?' "$contract"
require_contains 'seal_guarded_allowlist_metadata_present=1' "$contract"
require_contains 'seal_guarded_allowlist_report_surface_present=1' "$contract"
require_contains 'seal_guarded_allowlist_report_surface_status_present=1' "$contract"
require_contains 'seal_guarded_allowlist_status_index_alignment_present=1' "$contract"
require_contains 'seal_guarded_allowlist_public_entrypoint_alignment_present=1' "$contract"
require_contains 'operator_visible_guarded_allowlist_report=1' "$contract"
require_contains 'capability_metadata_profile=latticra-seal-capability-metadata/0.1' "$contract"
require_contains 'capability_contract_present' "$contract"
require_contains 'capability_metadata_planning_only=1' "$contract"
require_contains 'capability_name_present=0' "$contract"
require_contains 'capability_known=0' "$contract"
require_contains 'capability_unknown=1' "$contract"
require_contains 'capability_candidate=0' "$contract"
require_contains 'capability_requires_guarded_allowlist=1' "$contract"
require_contains 'capability_requires_policy_decision=1' "$contract"
require_contains 'capability_requires_runtime_gate=1' "$contract"
require_contains 'capability_requires_runtime_dry_run=1' "$contract"
require_contains 'capability_requires_operator_review=1' "$contract"
require_contains 'capability_grants_authority=0' "$contract"
require_contains 'capability_executes_tool=0' "$contract"
require_contains 'capability_reads_host=0' "$contract"
require_contains 'capability_writes_host=0' "$contract"
require_contains 'capability_uses_network=0' "$contract"
require_contains 'default_action=deny' "$contract"
require_contains 'would_allow=0' "$contract"
require_contains 'would_deny=1' "$contract"
require_contains 'would_require_operator_review=1' "$contract"
require_contains 'blocked_reason=default-deny-capability-metadata' "$contract"
require_contains 'status=capability-metadata' "$contract"
require_contains 'A known capability name may only become a candidate classification.' "$contract"
require_contains 'capability_scope=tool-boundary' "$contract"
require_contains 'capability_effect_class=runtime-authority' "$contract"
require_contains 'unknown_capability_denied=1' "$contract"
require_contains 'missing_capability_denied=1' "$contract"
require_contains 'invalid_capability_denied=1' "$contract"
require_contains 'turn capability matches into execution grants' "$contract"
require_contains 'turn capability matches into effect grants' "$contract"
require_contains 'This contract does not authorize capability enforcement.' "$contract"
require_contains 'a separate runtime authority contract would be required' "$contract"
require_contains 'The next valid slice is a no-effect capability metadata implementation plan.' "$contract"

printf 'latticra seal capability metadata contract: ok\n'
