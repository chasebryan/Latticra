#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal effect decision status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal effect decision status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_EFFECT_DECISION_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md
require_file docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md
require_file include/latticra/seal_effect_decision.h
require_file src/seal_effect_decision.c
require_file tests/seal_effect_decision_invariants.c
require_file scripts/test-latticra-seal-effect-decision-contract.sh
require_file scripts/test-latticra-seal-effect-decision.sh
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md
require_file include/latticra/seal_runtime_handoff.h
require_file src/seal_runtime_handoff.c
require_file tests/seal_runtime_handoff_invariants.c
require_file scripts/test-latticra-seal-runtime-handoff-contract.sh
require_file scripts/test-latticra-seal-runtime-handoff.sh
require_file docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md
require_file docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
require_file docs/status/SEAL_CAPABILITY_GATE_STATUS.md
require_file include/latticra/seal_capability_gate.h
require_file src/seal_capability_gate.c
require_file tests/seal_capability_gate_invariants.c
require_file scripts/test-latticra-seal-capability-gate-contract.sh
require_file scripts/test-latticra-seal-capability-gate.sh
require_file scripts/test-latticra-seal-capability-gate-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md

require_contains 'Status: status record for Latticra Seal effect decision metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_effect_decision_contract_present=1' "$status_file"
require_contains 'seal_effect_decision_implementation_present=1' "$status_file"
require_contains 'seal_effect_decision_header_present=1' "$status_file"
require_contains 'seal_effect_decision_source_present=1' "$status_file"
require_contains 'seal_effect_decision_invariant_test_present=1' "$status_file"
require_contains 'seal_effect_decision_runner_present=1' "$status_file"
require_contains 'seal_effect_decision_metadata_present=1' "$status_file"
require_contains 'seal_effect_decision_status_present=1' "$status_file"
require_contains 'seal_runtime_handoff_contract_present=1' "$status_file"
require_contains 'seal_runtime_handoff_implementation_present=1' "$status_file"
require_contains 'seal_capability_gate_contract_present=1' "$status_file"
require_contains 'seal_capability_gate_implementation_present=1' "$status_file"
require_contains 'seal_capability_gate_status_present=1' "$status_file"
require_contains 'decision_profile=latticra-seal-effect-decision/0.1' "$status_file"
require_contains 'gate_profile=latticra-seal-capability-gate/0.1' "$status_file"
require_contains 'receipt_profile=latticra-seal-verification-receipt/0.1' "$status_file"
require_contains 'artifact_digest_algorithm=SHA-256' "$status_file"
require_contains 'requested_capability=seal.inspect' "$status_file"
require_contains 'requested_effect=read-metadata' "$status_file"
require_contains 'requested_scope=local-artifact' "$status_file"
require_contains 'requested_effect_decision=metadata-only' "$status_file"
require_contains 'effect_decision_ready=1' "$status_file"
require_contains 'gate_state=denied-unverified' "$status_file"
require_contains 'decision_state=denied-gate' "$status_file"
require_contains 'gate_allowed=0' "$status_file"
require_contains 'effect_allowed=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'capability_enforcement_performed=0' "$status_file"
require_contains 'runtime_handoff_performed=0' "$status_file"
require_contains 'cryptographic_verification_performed=0' "$status_file"
require_contains 'verification_performed=0' "$status_file"
require_contains 'public_key_material_handling=0' "$status_file"
require_contains 'key_material_loaded=0' "$status_file"
require_contains 'private_key_handling=0' "$status_file"
require_contains 'key_generation_performed=0' "$status_file"
require_contains 'hardware_key_used=0' "$status_file"
require_contains 'trust_store_loaded=0' "$status_file"
require_contains 'network_lookup_allowed=0' "$status_file"
require_contains 'revocation_lookup_allowed=0' "$status_file"
require_contains 'revocation_lookup_performed=0' "$status_file"
require_contains 'signature_performed=0' "$status_file"
require_contains 'signer_invoked=0' "$status_file"
require_contains 'mode=metadata-only' "$status_file"
require_contains 'status=effect-decision-denied-metadata' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'seal effect decision contract: ok' "$status_file"
require_contains 'seal effect decision invariants: ok' "$status_file"
require_contains 'seal effect decision status: ok' "$status_file"
require_contains 'seal runtime handoff contract: ok' "$status_file"
require_contains 'seal capability gate status: ok' "$status_file"
require_contains 'runtime handoff status/public-entry alignment' "$status_file"

require_contains 'SEAL_EFFECT_DECISION_STATUS.md' README.md
require_contains 'LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md' README.md
require_contains 'latticra_seal_effect_decision_metadata_present=1' README.md
require_contains 'latticra_seal_effect_decision_status_present=1' README.md
require_contains 'seal_effect_decision_metadata_present=1' README.md
require_contains 'seal_effect_decision_status_present=1' README.md
require_contains 'Seal effect decision status/public-entry alignment' STATUS.md
require_contains 'seal_effect_decision_metadata_present=1' STATUS.md
require_contains 'seal_effect_decision_status_present=1' STATUS.md
require_contains 'SEAL_EFFECT_DECISION_STATUS.md' docs/status/README.md
require_contains 'seal_effect_decision_metadata_present=1' docs/status/README.md
require_contains 'seal_effect_decision_status_present=1' docs/status/README.md
require_contains 'Latticra Seal effect decision status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_EFFECT_DECISION_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal effect decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal runtime handoff status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal effect decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal runtime handoff status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_EFFECT_DECISION_STATUS.md' docs/project_notes/README.md

printf 'seal effect decision status: ok\n'
