#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-provider-self-test.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem provider self-test: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem provider self-test: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
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

binary="$tmpdir/latticra-q-seal-ml-kem-provider-self-test"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_provider_self_test.h
require_file latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
require_file latticra-q-seal/tests/q_seal_ml_kem_provider_self_test_invariants.c
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST.md
require_file latticra-q-seal/evidence/ML_KEM_PROVIDER_SELF_TEST.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-self-test.sh

require_contains 'latticra_q_seal_ml_kem_provider_self_test_run' latticra-q-seal/include/latticra/q_seal_ml_kem_provider_self_test.h
require_contains 'EVP_PKEY_CTX_new_from_name' latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
require_contains 'EVP_PKEY_keygen' latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
require_contains 'EVP_PKEY_encapsulate' latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
require_contains 'EVP_PKEY_decapsulate' latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
require_contains 'latticra_q_seal_ml_kem_constant_time_equal' latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
require_contains 'latticra_q_seal_ml_kem_secure_zero' latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
require_contains 'shared_secret_output_emitted=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST.md
require_contains 'ml_kem_provider_self_test_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST.md
require_contains 'ML-KEM-512-provider_self_test_passed=1' latticra-q-seal/evidence/ML_KEM_PROVIDER_SELF_TEST.md
require_contains 'ML-KEM-768-provider_self_test_passed=1' latticra-q-seal/evidence/ML_KEM_PROVIDER_SELF_TEST.md
require_contains 'ML-KEM-1024-provider_self_test_passed=1' latticra-q-seal/evidence/ML_KEM_PROVIDER_SELF_TEST.md
require_contains 'shared_secret_match=1' latticra-q-seal/evidence/ML_KEM_PROVIDER_SELF_TEST.md
require_contains 'shared_secret_zeroized=1' latticra-q-seal/evidence/ML_KEM_PROVIDER_SELF_TEST.md
require_contains 'latticra q-seal ml-kem provider self-test invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_provider_self_test_invariants.c

cc $CFLAGS $OPENSSL_CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_secret_ops.c \
  latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c \
  latticra-q-seal/tests/q_seal_ml_kem_provider_self_test_invariants.c \
  $OPENSSL_LIBS \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem provider self-test: ok\n'
