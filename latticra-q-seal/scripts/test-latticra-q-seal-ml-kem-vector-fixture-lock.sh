#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-vector-fixture-lock.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem vector fixture lock: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem vector fixture lock: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-vector-fixture-lock"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_vector_fixture_lock.h
require_file latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
require_file latticra-q-seal/tests/q_seal_ml_kem_vector_fixture_lock_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh

require_contains 'latticra_q_seal_ml_kem_vector_fixture_lock_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_vector_fixture_lock.h
require_contains 'latticra-q-seal-ml-kem-vector-fixture-lock/0.1' latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
require_contains 'NIST-FIPS-203-and-NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
require_contains 'fixture_bundle_loaded = 0u' latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
require_contains 'required_fixture_lock_items_total = 28u' latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
require_contains 'latticra q-seal ml-kem vector fixture lock invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_vector_fixture_lock_invariants.c
require_contains 'ml_kem_vector_fixture_lock_present=1' latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
require_contains 'fixture_bundle_loaded=0' latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
require_contains 'ml_kem_vector_fixture_lock_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK.md
require_contains 'required_fixture_lock_items_total=28' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c \
  latticra-q-seal/tests/q_seal_ml_kem_vector_fixture_lock_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem vector fixture lock: ok\n'
