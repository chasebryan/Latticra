#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal crypto verify backend contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal crypto verify backend contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
require_file include/latticra/seal_signature.h
require_file include/latticra/seal_verification_policy.h
require_file include/latticra/seal_verification_receipt.h
require_file include/latticra/seal_capability_gate.h
require_file src/seal_signature.c
require_file src/seal_verification_policy.c
require_file src/seal_verification_receipt.c
require_file src/seal_capability_gate.c

require_contains 'Status: Latticra Seal crypto verify backend contract' "$contract"
require_contains 'This document does not implement cryptographic verification.' "$contract"
require_contains 'No custom cryptographic primitive may be introduced.' "$contract"
require_contains 'A successful verification result may not directly grant authority.' "$contract"
require_contains 'A failed verification result must fail closed.' "$contract"
require_contains 'Ed25519-development' "$contract"
require_contains 'ML-DSA-planned' "$contract"
require_contains 'SLH-DSA-planned' "$contract"
require_contains 'crypto_verify_state=unsupported' "$contract"
require_contains 'crypto_verify_state=verified' "$contract"
require_contains 'crypto_verify_state=invalid-signature' "$contract"
require_contains 'cryptographic_verification_supported=0' "$contract"
require_contains 'cryptographic_verification_performed=0' "$contract"
require_contains 'verified=0' "$contract"
require_contains 'authority_usable=0' "$contract"
require_contains 'capability_gate_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'crypto verification backend metadata implementation' "$contract"
require_contains 'Ed25519 verify-only implementation contract' "$contract"
require_contains 'sh scripts/test-latticra-seal-crypto-verify-backend-contract.sh' "$contract"

printf 'seal crypto verify backend contract: ok\n'
