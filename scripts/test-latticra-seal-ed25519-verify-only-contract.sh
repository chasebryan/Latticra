#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal ed25519 verify-only contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal ed25519 verify-only contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_ED25519_VERIFY_ONLY_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md
require_file include/latticra/seal_crypto_verify_backend.h
require_file src/seal_crypto_verify_backend.c
require_file tests/seal_crypto_verify_backend_invariants.c

require_contains 'Status: Latticra Seal Ed25519 verify-only implementation contract' "$contract"
require_contains 'This document does not implement verification.' "$contract"
require_contains 'A successful Ed25519 verification result may not directly grant capability, effect, or runtime authority.' "$contract"
require_contains 'signature_algorithm=Ed25519-development' "$contract"
require_contains 'No custom cryptographic primitive may be introduced.' "$contract"
require_contains 'custom curve math' "$contract"
require_contains 'ed25519_public_key_bytes=32' "$contract"
require_contains 'ed25519_signature_bytes=64' "$contract"
require_contains 'message_size_max=65536' "$contract"
require_contains 'crypto_verify_state=verified' "$contract"
require_contains 'crypto_verify_state=invalid-signature' "$contract"
require_contains 'cryptographic_verification_supported=1' "$contract"
require_contains 'cryptographic_verification_performed=1' "$contract"
require_contains 'authority_usable=0' "$contract"
require_contains 'capability_gate_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'private-key input -> rejected' "$contract"
require_contains 'Ed25519 verify-only local implementation' "$contract"
require_contains 'verified receipt promotion from a successful verify-only result' "$contract"
require_contains 'sh scripts/test-latticra-seal-ed25519-verify-only-contract.sh' "$contract"

printf 'seal ed25519 verify-only contract: ok\n'
