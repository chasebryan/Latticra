#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem implementation file digest plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem implementation file digest plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-implementation-file-digest-plan"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_file_digest_plan.h
require_file latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c
require_file latticra-q-seal/tests/q_seal_ml_kem_implementation_file_digest_plan_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh

require_contains 'latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_file_digest_plan.h
require_contains 'latticra-q-seal-ml-kem-implementation-file-digest-plan/0.1' latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c
require_contains 'NIST-SP-800-218-SSDF,NIST-FIPS-203,NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c
require_contains 'source_layout_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c
require_contains 'required_digest_plan_items_total = 33u' latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c
require_contains 'shared_secret_emission_allowed == 0u' latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c
require_contains 'latticra q-seal ml-kem implementation file digest plan invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_implementation_file_digest_plan_invariants.c
require_contains 'ml_kem_implementation_file_digest_plan_present=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
require_contains 'digest_algorithm=SHA-256' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
require_contains 'implementation_file_digest_rows_recorded=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
require_contains 'source_layout_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
require_contains 'required_digest_plan_items_total=33' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c \
  latticra-q-seal/tests/q_seal_ml_kem_implementation_file_digest_plan_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem implementation file digest plan: ok\n'
