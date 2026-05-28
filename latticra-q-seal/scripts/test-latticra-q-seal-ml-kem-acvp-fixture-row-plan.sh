#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem acvp fixture row plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem acvp fixture row plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-acvp-fixture-row-plan"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_fixture_row_plan.h
require_file latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_file latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_row_plan_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh

require_contains 'latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_fixture_row_plan.h
require_contains 'latticra-q-seal-ml-kem-acvp-fixture-row-plan/0.1' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_contains 'NIST-FIPS-203-and-NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_contains 'acvp_fixture_digest_row_template_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_contains 'minimum_fixture_row_classes_required = 15u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_contains 'fixture_digest_rows_recorded = 0u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_contains 'required_fixture_row_plan_items_total = 36u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
require_contains 'latticra q-seal ml-kem acvp fixture row plan invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_row_plan_invariants.c
require_contains 'ml_kem_acvp_fixture_row_plan_present=1' latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
require_contains 'acvp_fixture_digest_row_template_bound=1' latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
require_contains 'minimum_fixture_row_classes_planned=15' latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
require_contains 'response_case_fields=tcId,ek,dk,c,k,testPassed' latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
require_contains 'required_fixture_row_plan_items_total=36' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c \
  latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_row_plan_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem acvp fixture row plan: ok\n'
