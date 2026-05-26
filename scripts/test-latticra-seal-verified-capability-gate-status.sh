#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verified capability gate status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verified capability gate status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_CONTRACT.md
require_file docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md
require_file docs/status/SEAL_VERIFIED_RECEIPT_PROMOTION_STATUS.md
require_file include/latticra/seal_verified_capability_gate.h
require_file src/seal_verified_capability_gate.c
require_file tests/seal_verified_capability_gate_invariants.c
require_file scripts/test-latticra-seal-verified-capability-gate-contract.sh
require_file scripts/test-latticra-seal-verified-capability-gate.sh

require_contains 'Status: status record for the Latticra Seal verified capability gate metadata surface' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_verified_capability_gate_contract_present=1' "$status_file"
require_contains 'seal_verified_capability_gate_implementation_present=1' "$status_file"
require_contains 'seal_verified_capability_gate_header_present=1' "$status_file"
require_contains 'seal_verified_capability_gate_source_present=1' "$status_file"
require_contains 'seal_verified_capability_gate_invariant_test_present=1' "$status_file"
require_contains 'seal_verified_capability_gate_runner_present=1' "$status_file"
require_contains 'seal_verified_capability_gate_status_present=1' "$status_file"
require_contains 'seal_verified_receipt_promotion_status_present=1' "$status_file"
require_contains 'readme_links_verified_capability_gate_contract=1' "$status_file"
require_contains 'readme_links_verified_capability_gate_implementation=1' "$status_file"
require_contains 'readme_links_verified_capability_gate_status=1' "$status_file"
require_contains 'root_status_mentions_verified_capability_gate_status=1' "$status_file"
require_contains 'status_index_links_verified_capability_gate_status=1' "$status_file"
require_contains 'foundation_index_links_verified_capability_gate_status=1' "$status_file"
require_contains 'project_notes_mark_verified_capability_gate_status_complete=1' "$status_file"
require_contains 'gate_profile=latticra-seal-verified-capability-gate/0.1' "$status_file"
require_contains 'receipt_profile=latticra-seal-verified-receipt/0.1' "$status_file"
require_contains 'verify_profile=latticra-seal-ed25519-verify/0.1' "$status_file"
require_contains 'message_digest_algorithm=SHA-256' "$status_file"
require_contains 'public_key_identity_label=rfc8032-test-key' "$status_file"
require_contains 'receipt_state=verified' "$status_file"
require_contains 'verification_state=verified' "$status_file"
require_contains 'requested_capability=verified-receipt-report' "$status_file"
require_contains 'requested_effect=report-only' "$status_file"
require_contains 'requested_scope=local-fixture-scope' "$status_file"
require_contains 'verified=1' "$status_file"
require_contains 'authority_usable=0' "$status_file"
require_contains 'receipt_capability_gate_allowed=0' "$status_file"
require_contains 'gate_allowed=1' "$status_file"
require_contains 'gate_state=allowed-metadata-only' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'status=verified-capability-gate-metadata' "$status_file"
require_contains 'verified_capability_gate_added=1' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'signing_added=0' "$status_file"
require_contains 'key_generation_added=0' "$status_file"
require_contains 'private_key_handling_added=0' "$status_file"
require_contains 'trust_store_behavior_added=0' "$status_file"
require_contains 'revocation_lookup_added=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'seal verified capability gate status: ok' "$status_file"
require_contains 'seal verified capability gate invariants: ok' "$status_file"
require_contains 'effect decision evaluation from an allowed metadata-only capability gate' "$status_file"

require_contains 'verified capability gate metadata/status' README.md
require_contains 'seal_verified_capability_gate_contract_present=1' README.md
require_contains 'seal_verified_capability_gate_implementation_present=1' README.md
require_contains 'seal_verified_capability_gate_status_present=1' README.md
require_contains 'verified_capability_gate_allowed=1' README.md
require_contains 'verified_capability_gate_state=allowed-metadata-only' README.md
require_contains 'verified_capability_gate_runtime_authority_granted=0' README.md
require_contains 'verified_capability_gate_effect_performed=0' README.md
require_contains 'docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md' README.md

require_contains 'Latest Seal verified capability gate status/public-entry note: 2026-05-25 CDT' STATUS.md
require_contains 'Seal verified capability gate status/public-entry alignment' STATUS.md
require_contains 'seal_verified_capability_gate_status_present=1' STATUS.md
require_contains 'verified_capability_gate_allowed=1' STATUS.md
require_contains 'verified_capability_gate_state=allowed-metadata-only' STATUS.md
require_contains 'verified_capability_gate_runtime_authority_granted=0' STATUS.md
require_contains 'verified_capability_gate_effect_performed=0' STATUS.md

require_contains 'SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md' docs/status/README.md
require_contains 'seal_verified_capability_gate_status_present=1' docs/status/README.md
require_contains 'verified capability gate metadata/status' docs/status/README.md

require_contains 'Latest Seal verified capability gate status/public-entry note: 2026-05-25 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal verified capability gate status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'seal_verified_capability_gate_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'verified_capability_gate_allowed=1' docs/status/CURRENT_STATUS.md
require_contains 'verified_capability_gate_state=allowed-metadata-only' docs/status/CURRENT_STATUS.md
require_contains 'verified_capability_gate_runtime_authority_granted=0' docs/status/CURRENT_STATUS.md
require_contains 'verified_capability_gate_effect_performed=0' docs/status/CURRENT_STATUS.md

require_contains 'SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal verified capability gate status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal verified capability gate status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal verified capability gate status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md' docs/project_notes/README.md

printf 'seal verified capability gate status: ok\n'
