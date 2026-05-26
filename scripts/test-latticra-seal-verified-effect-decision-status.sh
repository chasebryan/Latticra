#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verified effect decision status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verified effect decision status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_VERIFIED_EFFECT_DECISION_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_CONTRACT.md
require_file docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_IMPLEMENTATION.md
require_file docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md
require_file include/latticra/seal_verified_effect_decision.h
require_file src/seal_verified_effect_decision.c
require_file tests/seal_verified_effect_decision_invariants.c
require_file scripts/test-latticra-seal-verified-effect-decision-contract.sh
require_file scripts/test-latticra-seal-verified-effect-decision.sh

require_contains 'Status: status record for the Latticra Seal verified effect decision metadata surface' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_verified_effect_decision_contract_present=1' "$status_file"
require_contains 'seal_verified_effect_decision_implementation_present=1' "$status_file"
require_contains 'seal_verified_effect_decision_header_present=1' "$status_file"
require_contains 'seal_verified_effect_decision_source_present=1' "$status_file"
require_contains 'seal_verified_effect_decision_invariant_test_present=1' "$status_file"
require_contains 'seal_verified_effect_decision_runner_present=1' "$status_file"
require_contains 'seal_verified_effect_decision_status_present=1' "$status_file"
require_contains 'seal_verified_capability_gate_status_present=1' "$status_file"
require_contains 'decision_profile=latticra-seal-verified-effect-decision/0.1' "$status_file"
require_contains 'gate_profile=latticra-seal-verified-capability-gate/0.1' "$status_file"
require_contains 'requested_effect=report-only' "$status_file"
require_contains 'decision_state=allowed-report-only' "$status_file"
require_contains 'effect_allowed=1' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'status=verified-effect-decision-metadata' "$status_file"
require_contains 'runtime handoff evaluation status/public-entry alignment' "$status_file"

require_contains 'verified effect decision metadata/status' README.md
require_contains 'seal_verified_effect_decision_contract_present=1' README.md
require_contains 'seal_verified_effect_decision_implementation_present=1' README.md
require_contains 'seal_verified_effect_decision_status_present=1' README.md
require_contains 'verified_effect_decision_allowed=1' README.md
require_contains 'verified_effect_decision_state=allowed-report-only' README.md
require_contains 'verified_effect_decision_effect_performed=0' README.md
require_contains 'verified_effect_decision_runtime_authority_granted=0' README.md
require_contains 'docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_VERIFIED_EFFECT_DECISION_STATUS.md' README.md

require_contains 'Latest Seal verified effect decision status/public-entry note: 2026-05-25 CDT' STATUS.md
require_contains 'Seal verified effect decision status/public-entry alignment' STATUS.md
require_contains 'seal_verified_effect_decision_status_present=1' STATUS.md
require_contains 'verified_effect_decision_allowed=1' STATUS.md
require_contains 'verified_effect_decision_state=allowed-report-only' STATUS.md
require_contains 'verified_effect_decision_effect_performed=0' STATUS.md
require_contains 'verified_effect_decision_runtime_authority_granted=0' STATUS.md

require_contains 'SEAL_VERIFIED_EFFECT_DECISION_STATUS.md' docs/status/README.md
require_contains 'seal_verified_effect_decision_status_present=1' docs/status/README.md
require_contains 'verified effect decision metadata/status' docs/status/README.md

require_contains 'Latest Seal verified effect decision status/public-entry note: 2026-05-25 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal verified effect decision status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'seal_verified_effect_decision_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'verified_effect_decision_allowed=1' docs/status/CURRENT_STATUS.md
require_contains 'verified_effect_decision_state=allowed-report-only' docs/status/CURRENT_STATUS.md
require_contains 'verified_effect_decision_effect_performed=0' docs/status/CURRENT_STATUS.md
require_contains 'verified_effect_decision_runtime_authority_granted=0' docs/status/CURRENT_STATUS.md

require_contains 'SEAL_VERIFIED_EFFECT_DECISION_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal verified effect decision status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal verified effect decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal verified effect decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_VERIFIED_EFFECT_DECISION_STATUS.md' docs/project_notes/README.md

printf 'seal verified effect decision status: ok\n'
