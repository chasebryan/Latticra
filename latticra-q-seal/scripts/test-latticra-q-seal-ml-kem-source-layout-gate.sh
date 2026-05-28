#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-source-layout-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem source layout gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem source layout gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-source-layout-gate"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_source_layout_gate.h
require_file latticra-q-seal/src/q_seal_ml_kem_source_layout_gate.c
require_file latticra-q-seal/tests/q_seal_ml_kem_source_layout_gate_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_SOURCE_LAYOUT_GATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-layout-gate.sh

require_contains 'latticra_q_seal_ml_kem_source_layout_gate_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_source_layout_gate.h
require_contains 'latticra-q-seal-ml-kem-source-layout-gate/0.1' latticra-q-seal/src/q_seal_ml_kem_source_layout_gate.c
require_contains 'NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF' latticra-q-seal/src/q_seal_ml_kem_source_layout_gate.c
require_contains 'required_layout_items_total = 38u' latticra-q-seal/src/q_seal_ml_kem_source_layout_gate.c
require_contains 'shared_secret_emission_allowed == 0u' latticra-q-seal/src/q_seal_ml_kem_source_layout_gate.c
require_contains 'latticra q-seal ml-kem source layout gate invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_source_layout_gate_invariants.c
require_contains 'source_layout_gate_present=1' latticra-q-seal/evidence/ML_KEM_SOURCE_LAYOUT_GATE.md
require_contains 'source_layout_accepted=0' latticra-q-seal/evidence/ML_KEM_SOURCE_LAYOUT_GATE.md
require_contains 'required_layout_items_total=38' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE.md
require_contains 'required_layout_items_satisfied=32' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_source_layout_gate.c \
  latticra-q-seal/tests/q_seal_ml_kem_source_layout_gate_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem source layout gate: ok\n'
