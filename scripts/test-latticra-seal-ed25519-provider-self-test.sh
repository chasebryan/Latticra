#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-ed25519-provider-self-test.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal ed25519 provider self-test: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal ed25519 provider self-test: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
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

require_file include/latticra/seal_ed25519_provider_self_test.h
require_file src/seal_ed25519_provider_self_test.c
require_file tests/seal_ed25519_provider_self_test_invariants.c
require_file docs/LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST.md
require_file docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md

require_contains 'EVP_PKEY_ED25519' src/seal_ed25519_provider_self_test.c
require_contains 'EVP_PKEY_keygen' src/seal_ed25519_provider_self_test.c
require_contains 'EVP_PKEY_get_raw_public_key' src/seal_ed25519_provider_self_test.c
require_contains 'EVP_PKEY_new_raw_public_key' src/seal_ed25519_provider_self_test.c
require_contains 'EVP_DigestSign' src/seal_ed25519_provider_self_test.c
require_contains 'EVP_DigestVerify' src/seal_ed25519_provider_self_test.c
require_contains 'message_prehashed_before_signing = 0u' src/seal_ed25519_provider_self_test.c
require_contains 'ed25519_private_key_output_emitted = 0u' src/seal_ed25519_provider_self_test.c
require_contains 'ed25519_signature_output_emitted = 0u' src/seal_ed25519_provider_self_test.c
require_contains 'OPENSSL_cleanse(signature' src/seal_ed25519_provider_self_test.c
require_contains 'seal ed25519 provider self-test invariants: ok' tests/seal_ed25519_provider_self_test_invariants.c
require_contains 'ed25519_provider_self_test_present=1' docs/LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST.md
require_contains 'provider=OpenSSL-EVP' docs/LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST.md
require_contains 'signature_algorithm=Ed25519' docs/LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST.md
require_contains 'ed25519_key_generation_performed=1' docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ed25519_signature_generation_performed=1' docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ed25519_signature_verification_performed=1' docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ed25519_tampered_signature_rejected=1' docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ed25519_private_key_output_emitted=0' docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ed25519_signature_output_emitted=0' docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md
require_contains 'runtime_authority_granted=0' docs/status/SEAL_ED25519_PROVIDER_SELF_TEST_STATUS.md

"$CC" $CFLAGS $OPENSSL_CFLAGS -Iinclude \
  src/seal_ed25519_provider_self_test.c \
  tests/seal_ed25519_provider_self_test_invariants.c \
  $OPENSSL_LIBS \
  -o "$tmpdir/latticra-seal-ed25519-provider-self-test-invariants"

"$tmpdir/latticra-seal-ed25519-provider-self-test-invariants"
printf 'latticra seal ed25519 provider self-test: ok\n'
