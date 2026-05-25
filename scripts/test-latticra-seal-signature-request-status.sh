#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signature request status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signature request status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNATURE_REQUEST_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNER_HANDOFF_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNER_INVOCATION_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md
require_file include/latticra/seal_signature_request.h
require_file include/latticra/seal_signing_authorization.h
require_file include/latticra/seal_signer_handoff.h
require_file include/latticra/seal_signer_invocation.h
require_file src/seal_signature_request.c
require_file src/seal_signing_authorization.c
require_file src/seal_signer_handoff.c
require_file src/seal_signer_invocation.c
require_file tests/seal_signature_request_invariants.c
require_file tests/seal_signing_authorization_invariants.c
require_file tests/seal_signer_handoff_invariants.c
require_file tests/seal_signer_invocation_invariants.c
require_file scripts/test-latticra-seal-signature-request-contract.sh
require_file scripts/test-latticra-seal-signature-request.sh
require_file scripts/test-latticra-seal-signing-authorization-contract.sh
require_file scripts/test-latticra-seal-signing-authorization.sh
require_file scripts/test-latticra-seal-signing-authorization-status.sh
require_file scripts/test-latticra-seal-signer-handoff-contract.sh
require_file scripts/test-latticra-seal-signer-handoff.sh
require_file scripts/test-latticra-seal-signer-handoff-status.sh
require_file scripts/test-latticra-seal-signer-invocation-contract.sh
require_file scripts/test-latticra-seal-signer-invocation.sh
require_file scripts/test-latticra-seal-signer-invocation-status.sh
require_file scripts/test-latticra-seal-signing-operation-contract.sh
require_file docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md
require_file scripts/test-latticra-seal-report-envelope.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md

require_contains 'Status: status record for Latticra Seal signature request metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_signature_request_contract_present=1' "$status_file"
require_contains 'seal_signature_request_implementation_present=1' "$status_file"
require_contains 'seal_signature_request_header_present=1' "$status_file"
require_contains 'seal_signature_request_source_present=1' "$status_file"
require_contains 'seal_signature_request_invariant_test_present=1' "$status_file"
require_contains 'seal_signature_request_runner_present=1' "$status_file"
require_contains 'seal_signing_authorization_contract_present=1' "$status_file"
require_contains 'seal_signing_authorization_implementation_present=1' "$status_file"
require_contains 'seal_signing_authorization_header_present=1' "$status_file"
require_contains 'seal_signing_authorization_source_present=1' "$status_file"
require_contains 'seal_signing_authorization_invariant_test_present=1' "$status_file"
require_contains 'seal_signing_authorization_runner_present=1' "$status_file"
require_contains 'seal_signing_authorization_status_present=1' "$status_file"
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
require_contains 'seal_report_envelope_implementation_present=1' "$status_file"
require_contains 'seal_report_envelope_runner_present=1' "$status_file"
require_contains 'signature_request_profile=latticra-seal-signature-request/0.1' "$status_file"
require_contains 'requested_signature=Ed25519-development' "$status_file"
require_contains 'signature_request_state=requested-metadata-only' "$status_file"
require_contains 'signature_request_ready=1' "$status_file"
require_contains 'signature_performed=0' "$status_file"
require_contains 'verification_performed=0' "$status_file"
require_contains 'private_key_handling=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'mode=metadata-only' "$status_file"
require_contains 'status=signature-request-metadata' "$status_file"
require_contains 'public-key parsing metadata implementation' "$status_file"

require_contains 'SEAL_SIGNATURE_REQUEST_STATUS.md' README.md
require_contains 'seal_signature_request_status_present=1' README.md
require_contains 'Seal signature request status/public-entry alignment' STATUS.md
require_contains 'seal_signature_request_status_present=1' STATUS.md
require_contains 'SEAL_SIGNATURE_REQUEST_STATUS.md' docs/status/README.md
require_contains 'seal_signature_request_status_present=1' docs/status/README.md
require_contains 'Latticra Seal signature request status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_SIGNATURE_REQUEST_STATUS.md' docs/FOUNDATION_INDEX.md

printf 'seal signature request status: ok\n'
