#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-zeroization-evidence.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem zeroization evidence: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem zeroization evidence: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-zeroization-evidence"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_zeroization_evidence.h
require_file latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c
require_file latticra-q-seal/tests/q_seal_ml_kem_zeroization_evidence_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh

require_contains 'latticra_q_seal_ml_kem_zeroization_evidence_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_zeroization_evidence.h
require_contains 'latticra-q-seal-ml-kem-zeroization-evidence/0.1' latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c
require_contains 'zeroization_primitive_implemented = 0u' latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c
require_contains 'zeroization_performed = 0u' latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c
require_contains 'required_zeroization_items_total = 19u' latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c
require_contains 'latticra q-seal ml-kem zeroization evidence invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_zeroization_evidence_invariants.c
require_contains 'ml_kem_zeroization_evidence_present=1' latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
require_contains 'zeroization_performed=0' latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
require_contains 'ml_kem_zeroization_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE.md
require_contains 'required_zeroization_items_total=19' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c \
  latticra-q-seal/tests/q_seal_ml_kem_zeroization_evidence_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem zeroization evidence: ok\n'
