#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-vector-source.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem vector source: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem vector source: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-vector-source"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_vector_source.h
require_file latticra-q-seal/src/q_seal_ml_kem_vector_source.c
require_file latticra-q-seal/tests/q_seal_ml_kem_vector_source_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh

require_contains 'latticra_q_seal_ml_kem_vector_source_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_vector_source.h
require_contains 'latticra-q-seal-ml-kem-vector-source/0.1' latticra-q-seal/src/q_seal_ml_kem_vector_source.c
require_contains 'digest_algorithm_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_vector_source.c
require_contains 'bundle_source_url_recorded = 0u' latticra-q-seal/src/q_seal_ml_kem_vector_source.c
require_contains 'network_fetch_enabled = 0u' latticra-q-seal/src/q_seal_ml_kem_vector_source.c
require_contains 'required_source_items_total = 14u' latticra-q-seal/src/q_seal_ml_kem_vector_source.c
require_contains 'latticra q-seal ml-kem vector source invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_vector_source_invariants.c
require_contains 'ml_kem_vector_source_intake_present=1' latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
require_contains 'bundle_fetch_performed=0' latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
require_contains 'ml_kem_vector_source_intake_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md
require_contains 'required_source_items_total=14' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_vector_source.c \
  latticra-q-seal/tests/q_seal_ml_kem_vector_source_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem vector source: ok\n'
