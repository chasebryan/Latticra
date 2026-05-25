#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verification receipt status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verification receipt status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md
require_file docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
require_file include/latticra/seal_verification_receipt.h
require_file src/seal_verification_receipt.c
require_file tests/seal_verification_receipt_invariants.c
require_file scripts/test-latticra-seal-verification-receipt-contract.sh
require_file scripts/test-latticra-seal-verification-receipt.sh
require_file docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md
require_file docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
require_file docs/status/SEAL_CAPABILITY_GATE_STATUS.md
require_file include/latticra/seal_capability_gate.h
require_file src/seal_capability_gate.c
require_file tests/seal_capability_gate_invariants.c
require_file scripts/test-latticra-seal-capability-gate-contract.sh
require_file scripts/test-latticra-seal-capability-gate.sh
require_file scripts/test-latticra-seal-capability-gate-status.sh
require_file docs/status/SEAL_EFFECT_DECISION_STATUS.md
require_file scripts/test-latticra-seal-effect-decision-status.sh
require_file docs/LATTICRA_SEAL_VERIFICATION_POLICY_CONTRACT.md
require_file docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
require_file docs/status/SEAL_VERIFICATION_POLICY_STATUS.md
require_file include/latticra/seal_verification_policy.h
require_file src/seal_verification_policy.c
require_file tests/seal_verification_policy_invariants.c
require_file scripts/test-latticra-seal-verification-policy-contract.sh
require_file scripts/test-latticra-seal-verification-policy.sh
require_file scripts/test-latticra-seal-verification-policy-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md

require_contains 'Status: status record for Latticra Seal verification receipt metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_verification_receipt_contract_present=1' "$status_file"
require_contains 'seal_verification_receipt_implementation_present=1' "$status_file"
require_contains 'seal_verification_receipt_header_present=1' "$status_file"
require_contains 'seal_verification_receipt_source_present=1' "$status_file"
require_contains 'seal_verification_receipt_invariant_test_present=1' "$status_file"
require_contains 'seal_verification_receipt_runner_present=1' "$status_file"
require_contains 'seal_verification_receipt_metadata_present=1' "$status_file"
require_contains 'seal_verification_receipt_status_present=1' "$status_file"
require_contains 'seal_capability_gate_contract_present=1' "$status_file"
require_contains 'seal_capability_gate_implementation_present=1' "$status_file"
require_contains 'seal_capability_gate_status_present=1' "$status_file"
require_contains 'seal_effect_decision_status_present=1' "$status_file"
require_contains 'seal_verification_policy_contract_present=1' "$status_file"
require_contains 'seal_verification_policy_implementation_present=1' "$status_file"
require_contains 'seal_verification_policy_status_present=1' "$status_file"
require_contains 'receipt_profile=latticra-seal-verification-receipt/0.1' "$status_file"
require_contains 'verification_policy_profile=latticra-seal-verification-policy/0.1' "$status_file"
require_contains 'signature_profile=latticra-seal-signature/0.1' "$status_file"
require_contains 'manifest_profile=latticra-seal-manifest/0.1' "$status_file"
require_contains 'artifact_digest_algorithm=SHA-256' "$status_file"
require_contains 'signer_identity_label=latticra-dev-signer' "$status_file"
require_contains 'signature_algorithm=Ed25519-development' "$status_file"
require_contains 'public_key_identity_label=latticra-dev-public-key' "$status_file"
require_contains 'trust_source=local-metadata-only' "$status_file"
require_contains 'requested_verification_receipt=metadata-only' "$status_file"
require_contains 'verification_receipt_ready=1' "$status_file"
require_contains 'verification_state=unsupported' "$status_file"
require_contains 'receipt_state=unverified-metadata' "$status_file"
require_contains 'cryptographic_verification_supported=0' "$status_file"
require_contains 'cryptographic_verification_performed=0' "$status_file"
require_contains 'verification_performed=0' "$status_file"
require_contains 'verified=0' "$status_file"
require_contains 'invalid=0' "$status_file"
require_contains 'authority_usable=0' "$status_file"
require_contains 'capability_gate_allowed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'public_key_material_handling=0' "$status_file"
require_contains 'public_key_bytes_consumed=0' "$status_file"
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
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'mode=metadata-only' "$status_file"
require_contains 'status=verification-receipt-metadata' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'seal verification receipt contract: ok' "$status_file"
require_contains 'seal verification receipt invariants: ok' "$status_file"
require_contains 'seal verification receipt status: ok' "$status_file"
require_contains 'seal capability gate status: ok' "$status_file"
require_contains 'seal effect decision status: ok' "$status_file"
require_contains 'runtime handoff status/public-entry alignment' "$status_file"

require_contains 'SEAL_VERIFICATION_RECEIPT_STATUS.md' README.md
require_contains 'LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md' README.md
require_contains 'latticra_seal_verification_receipt_metadata_present=1' README.md
require_contains 'latticra_seal_verification_receipt_status_present=1' README.md
require_contains 'seal_verification_receipt_metadata_present=1' README.md
require_contains 'seal_verification_receipt_status_present=1' README.md
require_contains 'SEAL_CAPABILITY_GATE_STATUS.md' README.md
require_contains 'SEAL_EFFECT_DECISION_STATUS.md' README.md
require_contains 'seal_capability_gate_status_present=1' README.md
require_contains 'seal_effect_decision_status_present=1' README.md
require_contains 'Seal verification receipt status/public-entry alignment' STATUS.md
require_contains 'seal_verification_receipt_metadata_present=1' STATUS.md
require_contains 'seal_verification_receipt_status_present=1' STATUS.md
require_contains 'Seal capability gate status/public-entry alignment' STATUS.md
require_contains 'Seal effect decision status/public-entry alignment' STATUS.md
require_contains 'seal_capability_gate_status_present=1' STATUS.md
require_contains 'seal_effect_decision_status_present=1' STATUS.md
require_contains 'SEAL_VERIFICATION_RECEIPT_STATUS.md' docs/status/README.md
require_contains 'seal_verification_receipt_metadata_present=1' docs/status/README.md
require_contains 'seal_verification_receipt_status_present=1' docs/status/README.md
require_contains 'SEAL_CAPABILITY_GATE_STATUS.md' docs/status/README.md
require_contains 'SEAL_EFFECT_DECISION_STATUS.md' docs/status/README.md
require_contains 'seal_capability_gate_status_present=1' docs/status/README.md
require_contains 'seal_effect_decision_status_present=1' docs/status/README.md
require_contains 'Latticra Seal verification receipt status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal capability gate status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal effect decision status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_VERIFICATION_RECEIPT_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_CAPABILITY_GATE_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_EFFECT_DECISION_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal verification receipt status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal capability gate status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal effect decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal runtime handoff status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal verification receipt status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal capability gate status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal effect decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal runtime handoff status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md' docs/project_notes/README.md
require_contains 'docs/status/SEAL_CAPABILITY_GATE_STATUS.md' docs/project_notes/README.md
require_contains 'docs/status/SEAL_EFFECT_DECISION_STATUS.md' docs/project_notes/README.md

printf 'seal verification receipt status: ok\n'
