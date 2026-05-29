#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signing authorization status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signing authorization status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNER_HANDOFF_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNER_INVOCATION_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md
require_file include/latticra/seal_signing_authorization.h
require_file include/latticra/seal_signer_handoff.h
require_file include/latticra/seal_signer_invocation.h
require_file src/seal_signing_authorization.c
require_file src/seal_signer_handoff.c
require_file src/seal_signer_invocation.c
require_file tests/seal_signing_authorization_invariants.c
require_file tests/seal_signer_handoff_invariants.c
require_file tests/seal_signer_invocation_invariants.c
require_file scripts/test-latticra-seal-signing-authorization-contract.sh
require_file scripts/test-latticra-seal-signing-authorization.sh
require_file scripts/test-latticra-seal-signer-handoff-contract.sh
require_file scripts/test-latticra-seal-signer-handoff.sh
require_file scripts/test-latticra-seal-signer-handoff-status.sh
require_file scripts/test-latticra-seal-signer-invocation-contract.sh
require_file scripts/test-latticra-seal-signer-invocation.sh
require_file scripts/test-latticra-seal-signer-invocation-status.sh
require_file scripts/test-latticra-seal-signing-operation-contract.sh
require_file docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNATURE_REQUEST_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md
require_file docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_file scripts/test-latticra-seal-signature-request-status.sh
require_file .github/workflows/latticra-seal-signature-request-status.yml
require_file .github/workflows/latticra-seal-signing-authorization-status.yml
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md

require_contains 'Status: status record for Latticra Seal signing authorization metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_signing_authorization_contract_present=1' "$status_file"
require_contains 'seal_signing_authorization_implementation_present=1' "$status_file"
require_contains 'seal_signing_authorization_header_present=1' "$status_file"
require_contains 'seal_signing_authorization_source_present=1' "$status_file"
require_contains 'seal_signing_authorization_invariant_test_present=1' "$status_file"
require_contains 'seal_signing_authorization_runner_present=1' "$status_file"
require_contains 'seal_signing_authorization_status_present=1' "$status_file"
require_contains 'seal_signing_authorization_status_runner_present=1' "$status_file"
require_contains 'seal_signing_authorization_status_workflow_present=1' "$status_file"
require_contains 'seal_signer_handoff_contract_present=1' "$status_file"
require_contains 'seal_signer_handoff_implementation_present=1' "$status_file"
require_contains 'seal_signer_handoff_header_present=1' "$status_file"
require_contains 'seal_signer_handoff_source_present=1' "$status_file"
require_contains 'seal_signer_handoff_invariant_test_present=1' "$status_file"
require_contains 'seal_signer_handoff_runner_present=1' "$status_file"
require_contains 'seal_signer_handoff_metadata_present=1' "$status_file"
require_contains 'seal_signer_handoff_status_present=1' "$status_file"
require_contains 'seal_signer_invocation_contract_present=1' "$status_file"
require_contains 'seal_signer_invocation_implementation_present=1' "$status_file"
require_contains 'seal_signer_invocation_metadata_present=1' "$status_file"
require_contains 'seal_signer_invocation_status_present=1' "$status_file"
require_contains 'seal_signing_operation_contract_present=1' docs/status/SEAL_SIGNER_INVOCATION_STATUS.md
require_contains 'seal_signature_request_contract_present=1' "$status_file"
require_contains 'seal_signature_request_implementation_present=1' "$status_file"
require_contains 'seal_signature_request_status_present=1' "$status_file"
require_contains 'seal_signature_request_status_runner_present=1' "$status_file"
require_contains 'seal_signature_request_status_workflow_present=1' "$status_file"
require_contains 'seal_crypto_graduation_gate_status_present=1' "$status_file"
require_contains 'signing_authorization_predecessor_signature_request_status_present=1' "$status_file"
require_contains 'readme_links_signing_authorization_status=1' "$status_file"
require_contains 'root_status_mentions_signing_authorization_status=1' "$status_file"
require_contains 'status_index_links_signing_authorization_status=1' "$status_file"
require_contains 'foundation_index_links_signing_authorization_status=1' "$status_file"
require_contains 'signing_authorization_profile=latticra-seal-signing-authorization/0.1' "$status_file"
require_contains 'signature_request_profile=latticra-seal-signature-request/0.1' "$status_file"
require_contains 'crypto_graduation_profile=latticra-seal-crypto-graduation-gate/0.1' "$status_file"
require_contains 'assurance_baseline_profile=latticra-cryptographic-assurance-key-management/0.1' "$status_file"
require_contains 'crypto_graduation_gate_state=graduated-authority-neutral' "$status_file"
require_contains 'requested_signature=Ed25519-development' "$status_file"
require_contains 'requested_signing_authorization=metadata-only' "$status_file"
require_contains 'crypto_graduation_gate_present=1' "$status_file"
require_contains 'crypto_graduation_gate_passed=1' "$status_file"
require_contains 'standard_expectations_met=1' "$status_file"
require_contains 'local_verify_graduated=1' "$status_file"
require_contains 'receipt_promotion_graduated=1' "$status_file"
require_contains 'authority_promotion_allowed=0' "$status_file"
require_contains 'signature_request_state=requested-metadata-only' "$status_file"
require_contains 'signature_request_ready=1' "$status_file"
require_contains 'signing_authorization_state=authorized-metadata-only' "$status_file"
require_contains 'signing_authorization_ready=1' "$status_file"
require_contains 'signature_performed=0' "$status_file"
require_contains 'verification_performed=0' "$status_file"
require_contains 'private_key_handling=0' "$status_file"
require_contains 'key_generation_performed=0' "$status_file"
require_contains 'trust_store_loaded=0' "$status_file"
require_contains 'revocation_lookup_performed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'mode=metadata-only' "$status_file"
require_contains 'status=signing-authorization-metadata' "$status_file"
require_contains 'signing_authorization_status_added=1' "$status_file"
require_contains 'signing_added=0' "$status_file"
require_contains 'signature_verification_added=0' "$status_file"
require_contains 'key_generation_added=0' "$status_file"
require_contains 'private_key_handling_added=0' "$status_file"
require_contains 'trust_store_behavior_added=0' "$status_file"
require_contains 'revocation_lookup_added=0' "$status_file"
require_contains 'object_sealing_added=0' "$status_file"
require_contains 'runtime_handoff_execution_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'seal signing authorization status: ok' "$status_file"
require_contains 'signer handoff status/workflow guard alignment' "$status_file"

require_contains 'DENIED_CRYPTO_GRADUATION_GATE' include/latticra/seal_signing_authorization.h
require_contains 'denied-crypto-graduation-gate' src/seal_signing_authorization.c
require_contains 'crypto_graduation_gate_present=%u' src/seal_signing_authorization.c
require_contains 'standard_expectations_met=%u' src/seal_signing_authorization.c

require_contains 'SEAL_SIGNING_AUTHORIZATION_STATUS.md' README.md
require_contains 'latticra_seal_signing_authorization_status_present=1' README.md
require_contains 'seal_signing_authorization_status_present=1' README.md
require_contains 'signing_authorization_crypto_graduation_gate_present=1' README.md
require_contains 'signing_authorization_crypto_graduation_gate_passed=1' README.md
require_contains 'signing_authorization_standard_expectations_met=1' README.md
require_contains 'signing_authorization_authority_promotion_allowed=0' README.md
require_contains 'signing-authorization status record now ties that metadata-only checkpoint to the guarded signature-request status predecessor' README.md
require_contains 'signing-authorization status record now preserves crypto graduation evidence from the guarded signature-request predecessor without adding signing authority' README.md
require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md' README.md
require_contains 'LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md' README.md
require_contains 'SEAL_SIGNER_INVOCATION_STATUS.md' README.md
require_contains 'LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md' README.md
require_contains 'latticra_seal_signer_handoff_contract_present=1' README.md
require_contains 'latticra_seal_signer_handoff_metadata_present=1' README.md
require_contains 'latticra_seal_signer_invocation_contract_present=1' README.md
require_contains 'latticra_seal_signer_invocation_metadata_present=1' README.md
require_contains 'latticra_seal_signer_invocation_status_present=1' README.md
require_contains 'latticra_seal_signing_operation_contract_present=1' README.md
require_contains 'seal_signer_handoff_contract_present=1' README.md
require_contains 'seal_signer_handoff_metadata_present=1' README.md
require_contains 'seal_signer_invocation_contract_present=1' README.md
require_contains 'seal_signer_invocation_metadata_present=1' README.md
require_contains 'seal_signer_invocation_status_present=1' README.md
require_contains 'seal_signing_operation_contract_present=1' README.md
require_contains 'Seal signing authorization status/public-entry alignment' STATUS.md
require_contains 'Seal signing authorization predecessor status alignment' STATUS.md
require_contains 'seal_signing_authorization_status_present=1' STATUS.md
require_contains 'signing_authorization_predecessor_signature_request_status_present=1' STATUS.md
require_contains 'signing_authorization_crypto_graduation_gate_present=1' STATUS.md
require_contains 'signing_authorization_crypto_graduation_gate_passed=1' STATUS.md
require_contains 'signing_authorization_standard_expectations_met=1' STATUS.md
require_contains 'signing_authorization_authority_promotion_allowed=0' STATUS.md
require_contains 'Seal signer handoff contract' STATUS.md
require_contains 'Seal signer handoff metadata implementation' STATUS.md
require_contains 'Seal signer handoff status/public-entry alignment' STATUS.md
require_contains 'Seal signer invocation contract' STATUS.md
require_contains 'Seal signer invocation metadata implementation' STATUS.md
require_contains 'Seal signer invocation status/public-entry alignment' STATUS.md
require_contains 'Seal signing operation contract' STATUS.md
require_contains 'seal_signer_handoff_contract_present=1' STATUS.md
require_contains 'seal_signer_handoff_metadata_present=1' STATUS.md
require_contains 'seal_signer_handoff_status_present=1' STATUS.md
require_contains 'seal_signer_invocation_contract_present=1' STATUS.md
require_contains 'seal_signer_invocation_metadata_present=1' STATUS.md
require_contains 'seal_signer_invocation_status_present=1' STATUS.md
require_contains 'seal_signing_operation_contract_present=1' STATUS.md
require_contains 'SEAL_SIGNING_AUTHORIZATION_STATUS.md' docs/status/README.md
require_contains 'seal_signing_authorization_status_present=1' docs/status/README.md
require_contains 'signing_authorization_predecessor_signature_request_status_present=1' docs/status/README.md
require_contains 'signing_authorization_crypto_graduation_gate_present=1' docs/status/README.md
require_contains 'signing_authorization_crypto_graduation_gate_passed=1' docs/status/README.md
require_contains 'signing_authorization_standard_expectations_met=1' docs/status/README.md
require_contains 'signing_authorization_authority_promotion_allowed=0' docs/status/README.md
require_contains 'seal_signer_handoff_contract_present=1' docs/status/README.md
require_contains 'seal_signer_handoff_metadata_present=1' docs/status/README.md
require_contains 'seal_signer_handoff_status_present=1' docs/status/README.md
require_contains 'seal_signer_invocation_contract_present=1' docs/status/README.md
require_contains 'seal_signer_invocation_metadata_present=1' docs/status/README.md
require_contains 'seal_signer_invocation_status_present=1' docs/status/README.md
require_contains 'seal_signing_operation_contract_present=1' docs/status/README.md
require_contains 'Latticra Seal signing authorization status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signing authorization predecessor status alignment' docs/status/CURRENT_STATUS.md
require_contains 'signing_authorization_predecessor_signature_request_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'signing_authorization_crypto_graduation_gate_present=1' docs/status/CURRENT_STATUS.md
require_contains 'signing_authorization_crypto_graduation_gate_passed=1' docs/status/CURRENT_STATUS.md
require_contains 'signing_authorization_standard_expectations_met=1' docs/status/CURRENT_STATUS.md
require_contains 'signing_authorization_authority_promotion_allowed=0' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer handoff contract' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer handoff metadata implementation' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer handoff status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer invocation contract' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer invocation metadata implementation' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer invocation status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signing operation contract' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_SIGNING_AUTHORIZATION_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signing authorization predecessor status alignment' docs/FOUNDATION_INDEX.md
require_contains 'crypto graduation evidence carry-forward' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_SIGNER_HANDOFF_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_SIGNER_INVOCATION_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signing authorization status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signing authorization predecessor status alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer handoff contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer handoff metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer handoff status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer invocation contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer invocation metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer invocation status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signing operation contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal bounded no-effect key parsing implementation' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latticra Seal signing authorization predecessor status alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md' docs/project_notes/README.md
require_contains 'sh scripts/test-latticra-seal-signing-authorization-status.sh' .github/workflows/latticra-seal-signing-authorization-status.yml

sh scripts/test-latticra-seal-signature-request-status.sh

printf 'seal signing authorization status: ok\n'
