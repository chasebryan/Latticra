#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-randomness-source.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem randomness source: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem randomness source: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-randomness-source"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_randomness_source.h
require_file latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
require_file latticra-q-seal/tests/q_seal_ml_kem_randomness_source_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh

require_contains 'latticra_q_seal_ml_kem_randomness_source_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_randomness_source.h
require_contains 'latticra-q-seal-ml-kem-randomness-source/0.1' latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
require_contains 'sp_800_90a_tracked = 1u' latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
require_contains 'entropy_source_inventory_recorded = 0u' latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
require_contains 'random_bytes_generated = 0u' latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
require_contains 'required_randomness_items_total = 18u' latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
require_contains 'latticra q-seal ml-kem randomness source invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_randomness_source_invariants.c
require_contains 'ml_kem_randomness_source_contract_present=1' latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
require_contains 'random_bit_generation_allowed=0' latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
require_contains 'ml_kem_randomness_source_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE.md
require_contains 'required_randomness_items_total=18' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_randomness_source.c \
  latticra-q-seal/tests/q_seal_ml_kem_randomness_source_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem randomness source: ok\n'
