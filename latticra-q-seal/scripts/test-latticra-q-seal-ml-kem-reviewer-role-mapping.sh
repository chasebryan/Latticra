#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-reviewer-role-mapping.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem reviewer role mapping: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem reviewer role mapping: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-reviewer-role-mapping"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_reviewer_role_mapping.h
require_file latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c
require_file latticra-q-seal/tests/q_seal_ml_kem_reviewer_role_mapping_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh

require_contains 'latticra_q_seal_ml_kem_reviewer_role_mapping_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_reviewer_role_mapping.h
require_contains 'latticra-q-seal-ml-kem-reviewer-role-mapping/0.1' latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c
require_contains 'NIST-SP-800-218-SSDF-and-FIPS-203' latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c
require_contains 'required_role_mapping_items_total = 30u' latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c
require_contains 'latticra q-seal ml-kem reviewer role mapping invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_reviewer_role_mapping_invariants.c
require_contains 'ml_kem_reviewer_role_mapping_present=1' latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
require_contains 'reviewer_identity_fixture_bound=1' latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
require_contains 'role_mapping_records_imported=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md
require_contains 'required_role_mapping_items_total=30' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c \
  latticra-q-seal/tests/q_seal_ml_kem_reviewer_role_mapping_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem reviewer role mapping: ok\n'
