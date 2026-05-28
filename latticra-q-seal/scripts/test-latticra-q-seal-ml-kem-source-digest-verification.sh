#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-source-digest-verification.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem source digest verification: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem source digest verification: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-source-digest-verification"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_verification.h
require_file latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c
require_file latticra-q-seal/tests/q_seal_ml_kem_source_digest_verification_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh

require_contains 'latticra_q_seal_ml_kem_source_digest_verification_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_verification.h
require_contains 'latticra-q-seal-ml-kem-source-digest-verification/0.1' latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c
require_contains 'NIST-SP-800-218-SSDF-and-FIPS-203' latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c
require_contains 'required_verification_items_total = 23u' latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c
require_contains 'latticra q-seal ml-kem source digest verification invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_source_digest_verification_invariants.c
require_contains 'ml_kem_source_digest_verification_present=1' latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
require_contains 'source_digest_receipt_bound=1' latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
require_contains 'source_digest_replay_executed=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md
require_contains 'required_verification_items_total=23' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c \
  latticra-q-seal/tests/q_seal_ml_kem_source_digest_verification_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem source digest verification: ok\n'
