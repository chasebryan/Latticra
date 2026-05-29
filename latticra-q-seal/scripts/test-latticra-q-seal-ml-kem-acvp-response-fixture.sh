#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-acvp-response-fixture.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem acvp response fixture: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem acvp response fixture: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-acvp-response-fixture"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_response_fixture.h
require_file latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_file latticra-q-seal/tests/q_seal_ml_kem_acvp_response_fixture_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh

require_contains 'latticra_q_seal_ml_kem_acvp_response_fixture_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_response_fixture.h
require_contains 'latticra-q-seal-ml-kem-acvp-response-fixture/0.1' latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_contains 'NIST-FIPS-203-and-NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_contains 'kat_result_row_fixture_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_contains 'keygen_response_fixture_required = 1u' latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_contains 'response_output_accepted = 0u' latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_contains 'response_json_generation_enabled = 0u' latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_contains 'required_response_fixture_items_total = 46u' latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
require_contains 'latticra q-seal ml-kem acvp response fixture invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_acvp_response_fixture_invariants.c
require_contains 'acvp_response_fixture_present=1' latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
require_contains 'kat_result_row_fixture_bound=1' latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
require_contains 'keygen_response_fixture_required=1' latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
require_contains 'response_output_accepted=0' latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
require_contains 'required_response_fixture_items_total=46' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c \
  latticra-q-seal/tests/q_seal_ml_kem_acvp_response_fixture_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem acvp response fixture: ok\n'
