#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-kat-manifest.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem kat manifest: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem kat manifest: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-kat-manifest"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_kat_manifest.h
require_file latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
require_file latticra-q-seal/tests/q_seal_ml_kem_kat_manifest_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh

require_contains 'latticra_q_seal_ml_kem_kat_manifest_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_kat_manifest.h
require_contains 'latticra-q-seal-ml-kem-kat-manifest/0.1' latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
require_contains 'NIST-FIPS-203-and-NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
require_contains 'acvp_keygen_aft_required = 1u' latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
require_contains 'known_answer_vectors_loaded = 0u' latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
require_contains 'required_kat_manifest_items_total = 40u' latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
require_contains 'latticra q-seal ml-kem kat manifest invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_kat_manifest_invariants.c
require_contains 'ml_kem_kat_manifest_present=1' latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
require_contains 'acvp_keygen_aft_required=1' latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
require_contains 'known_answer_vectors_loaded=0' latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
require_contains 'required_kat_manifest_items_total=40' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c \
  latticra-q-seal/tests/q_seal_ml_kem_kat_manifest_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem kat manifest: ok\n'
