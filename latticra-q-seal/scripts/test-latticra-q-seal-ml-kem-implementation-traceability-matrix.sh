#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem implementation traceability matrix: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem implementation traceability matrix: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-implementation-traceability-matrix"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_traceability_matrix.h
require_file latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_file latticra-q-seal/tests/q_seal_ml_kem_implementation_traceability_matrix_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh

require_contains 'latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_traceability_matrix.h
require_contains 'latticra-q-seal-ml-kem-implementation-traceability-matrix/0.1' latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_contains 'NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_contains 'planned_source_units_count = 9u' latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_contains 'fips_203_section_mapping_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_contains 'sp800_227_usage_mapping_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_contains 'constant_time_review_mapping_recorded = 0u' latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c
require_contains 'latticra q-seal ml-kem implementation traceability matrix invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_implementation_traceability_matrix_invariants.c
require_contains 'implementation_traceability_matrix_present=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
require_contains 'implementation_trace_accepted=0' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
require_contains 'required_traceability_items_total=30' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
require_contains 'required_traceability_items_satisfied=20' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c \
  latticra-q-seal/tests/q_seal_ml_kem_implementation_traceability_matrix_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem implementation traceability matrix: ok\n'
