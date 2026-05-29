#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-crypto-graduation-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal crypto graduation gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal crypto graduation gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

OPENSSL_CFLAGS="${OPENSSL_CFLAGS:-}"
OPENSSL_LIBS="${OPENSSL_LIBS:-}"

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v pkg-config >/dev/null 2>&1; then
  if pkg-config --exists openssl; then
    OPENSSL_CFLAGS="$(pkg-config --cflags openssl)"
    OPENSSL_LIBS="$(pkg-config --libs openssl)"
  fi
fi

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v brew >/dev/null 2>&1; then
  openssl_prefix="$(brew --prefix openssl@3 2>/dev/null || brew --prefix openssl 2>/dev/null || true)"
  if [ -n "$openssl_prefix" ]; then
    OPENSSL_CFLAGS="-I$openssl_prefix/include"
    OPENSSL_LIBS="-L$openssl_prefix/lib -lcrypto"
  fi
fi

if [ -z "$OPENSSL_LIBS" ]; then
  OPENSSL_LIBS="-lcrypto"
fi

binary="$tmpdir/seal_crypto_graduation_gate_invariants"

require_file include/latticra/seal_crypto_graduation_gate.h
require_file src/seal_crypto_graduation_gate.c
require_file tests/seal_crypto_graduation_gate_invariants.c
require_file docs/LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_IMPLEMENTATION.md
require_file docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_file docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
require_file docs/status/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE_STATUS.md

require_contains 'LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_OK' include/latticra/seal_crypto_graduation_gate.h
require_contains 'LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_AUTHORITY_NOT_NEUTRAL' include/latticra/seal_crypto_graduation_gate.h
require_contains 'latticra_seal_crypto_graduation_gate_from_verified_receipt' include/latticra/seal_crypto_graduation_gate.h
require_contains 'latticra_seal_crypto_graduation_gate_report' include/latticra/seal_crypto_graduation_gate.h
require_contains 'latticra-seal-crypto-graduation-gate/0.1' src/seal_crypto_graduation_gate.c
require_contains 'provider_backed_verification_required=%u' src/seal_crypto_graduation_gate.c
require_contains 'fips_186_5_signature_standard_tracked=%u' src/seal_crypto_graduation_gate.c
require_contains 'fips_204_ml_dsa_planning_tracked=%u' src/seal_crypto_graduation_gate.c
require_contains 'production_crypto_claim_allowed=%u' src/seal_crypto_graduation_gate.c
require_contains 'authority_promotion_allowed=%u' src/seal_crypto_graduation_gate.c
require_contains 'rfc8032-test-vector-2' tests/seal_crypto_graduation_gate_invariants.c
require_contains 'seal crypto graduation gate invariants: ok' tests/seal_crypto_graduation_gate_invariants.c
require_contains 'seal_crypto_graduation_gate_present=1' docs/LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_IMPLEMENTATION.md
require_contains 'standard_expectations_met=1' docs/LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_IMPLEMENTATION.md
require_contains 'authority_promotion_allowed=0' docs/LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_IMPLEMENTATION.md
require_contains 'seal_crypto_graduation_gate_present=1' docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_contains 'seal_crypto_graduation_gate_present=1' docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
require_contains 'seal_crypto_graduation_gate_present=1' docs/status/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE_STATUS.md

cc $CFLAGS $OPENSSL_CFLAGS -Iinclude \
  src/seal_ed25519_verify.c \
  src/seal_verified_receipt_promotion.c \
  src/seal_crypto_graduation_gate.c \
  tests/seal_crypto_graduation_gate_invariants.c \
  $OPENSSL_LIBS \
  -o "$binary"

"$binary"

printf 'latticra seal crypto graduation gate: ok\n'
