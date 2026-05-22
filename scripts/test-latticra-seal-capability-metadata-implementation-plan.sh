#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal capability metadata implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal capability metadata implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_CAPABILITY_METADATA_CONTRACT.md
require_file scripts/test-latticra-seal-capability-metadata-contract.sh
require_file docs/status/SEAL_GUARDED_ALLOWLIST_PUBLIC_ENTRYPOINT_ALIGNMENT.md

require_contains 'Status: implementation planning contract for a future no-effect Latticra Seal capability metadata surface' "$plan"
require_contains 'include/latticra/seal_capability_metadata.h' "$plan"
require_contains 'src/seal_capability_metadata.c' "$plan"
require_contains 'tests/seal_capability_metadata_invariants.c' "$plan"
require_contains 'scripts/test-latticra-seal-capability-metadata.sh' "$plan"
require_contains 'latticra_seal_capability_metadata_result_t' "$plan"
require_contains 'latticra_seal_capability_metadata_result_missing' "$plan"
require_contains 'latticra_seal_capability_metadata_result_unknown' "$plan"
require_contains 'latticra_seal_capability_metadata_result_candidate' "$plan"
require_contains 'LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME' "$plan"
require_contains 'LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_FIXTURE' "$plan"
require_contains 'capability_metadata_profile=latticra-seal-capability-metadata/0.1' "$plan"
require_contains 'capability_fixture_source=deterministic-local-fixture' "$plan"
require_contains 'capability_fixture_entry_count=3' "$plan"
require_contains 'seal.capability.inspect' "$plan"
require_contains 'seal.capability.report' "$plan"
require_contains 'seal.capability.dry_run' "$plan"
require_contains 'capability_name_present=0' "$plan"
require_contains 'capability_known=0' "$plan"
require_contains 'capability_unknown=1' "$plan"
require_contains 'capability_candidate=0' "$plan"
require_contains 'capability_name_present=1' "$plan"
require_contains 'capability_known=1' "$plan"
require_contains 'capability_candidate=1' "$plan"
require_contains 'capability_grants_authority=0' "$plan"
require_contains 'capability_executes_tool=0' "$plan"
require_contains 'capability_reads_host=0' "$plan"
require_contains 'capability_writes_host=0' "$plan"
require_contains 'capability_uses_network=0' "$plan"
require_contains 'default_action_deny=1' "$plan"
require_contains 'would_allow=0' "$plan"
require_contains 'would_deny=1' "$plan"
require_contains 'would_require_operator_review=1' "$plan"
require_contains 'missing_capability_denied=1' "$plan"
require_contains 'unknown_capability_denied=1' "$plan"
require_contains 'invalid_capability_denied=1' "$plan"
require_contains 'blocked_reason=missing-capability-denied' "$plan"
require_contains 'blocked_reason=default-deny-capability-metadata' "$plan"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$plan"
require_contains 'LATTICRA SEAL CAPABILITY METADATA' "$plan"
require_contains 'capability effect class is descriptive only' "$plan"
require_contains 'turn capability matches into execution grants' "$plan"
require_contains 'turn capability matches into effect grants' "$plan"
require_contains 'No capability enforcement work may begin from this plan alone.' "$plan"
require_contains 'The next valid Latticra Seal slice is the no-effect capability metadata implementation.' "$plan"

printf 'latticra seal capability metadata implementation plan: ok\n'
