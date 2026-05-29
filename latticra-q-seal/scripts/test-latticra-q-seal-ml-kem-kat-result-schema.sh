#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-kat-result-schema.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem kat result schema: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem kat result schema: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-kat-result-schema"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_kat_result_schema.h
require_file latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_file latticra-q-seal/tests/q_seal_ml_kem_kat_result_schema_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh

require_contains 'latticra_q_seal_ml_kem_kat_result_schema_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_kat_result_schema.h
require_contains 'latticra-q-seal-ml-kem-kat-result-schema/0.1' latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_contains 'NIST-FIPS-203-and-NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_contains 'kat_runner_contract_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_contains 'kat_result_row_fixture_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_contains 'result_schema_reviewed = 0u' latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_contains 'required_kat_result_schema_items_total = 44u' latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
require_contains 'latticra q-seal ml-kem kat result schema invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_kat_result_schema_invariants.c
require_contains 'kat_result_schema_present=1' latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
require_contains 'kat_runner_contract_bound=1' latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
require_contains 'kat_result_row_fixture_bound=1' latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
require_contains 'result_schema_reviewed=0' latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
require_contains 'required_kat_result_schema_items_total=44' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c \
  latticra-q-seal/tests/q_seal_ml_kem_kat_result_schema_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem kat result schema: ok\n'
