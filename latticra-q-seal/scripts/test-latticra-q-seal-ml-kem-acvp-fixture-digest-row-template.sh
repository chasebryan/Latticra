#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem acvp fixture digest row template: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem acvp fixture digest row template: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-acvp-fixture-digest-row-template"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_fixture_digest_row_template.h
require_file latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_file latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_digest_row_template_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh

require_contains 'latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_fixture_digest_row_template.h
require_contains 'latticra-q-seal-ml-kem-acvp-fixture-digest-row-template/0.1' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_contains 'NIST-FIPS-203-and-NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_contains 'planned_fixture_digest_rows_required = 15u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_contains 'sha256_digest_rows_recorded = 0u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_contains 'fixture_digest_row_acceptance_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_contains 'required_digest_row_template_items_total = 45u' latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
require_contains 'latticra q-seal ml-kem acvp fixture digest row template invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_digest_row_template_invariants.c
require_contains 'ml_kem_acvp_fixture_digest_row_template_present=1' latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
require_contains 'planned_fixture_digest_rows_reserved=15' latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
require_contains 'sha256_digest_rows_recorded=0' latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
require_contains 'required_digest_row_template_items_total=45' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c \
  latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_digest_row_template_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem acvp fixture digest row template: ok\n'
