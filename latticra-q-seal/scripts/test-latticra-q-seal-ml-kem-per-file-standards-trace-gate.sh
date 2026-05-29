#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem per-file standards trace gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem per-file standards trace gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-per-file-standards-trace-gate"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_per_file_standards_trace_gate.h
require_file latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c
require_file latticra-q-seal/tests/q_seal_ml_kem_per_file_standards_trace_gate_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh

require_contains 'latticra_q_seal_ml_kem_per_file_standards_trace_gate_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_per_file_standards_trace_gate.h
require_contains 'latticra-q-seal-ml-kem-per-file-standards-trace-gate/0.1' latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c
require_contains 'NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF' latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c
require_contains 'required_standards_trace_items_total = 31u' latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c
require_contains 'shared_secret_emission_allowed == 0u' latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c
require_contains 'latticra q-seal ml-kem per-file standards trace gate invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_per_file_standards_trace_gate_invariants.c
require_contains 'per_file_standards_trace_gate_present=1' latticra-q-seal/evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
require_contains 'per_file_standards_trace_accepted=0' latticra-q-seal/evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
require_contains 'required_standards_trace_items_total=31' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
require_contains 'required_standards_trace_items_satisfied=24' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c \
  latticra-q-seal/tests/q_seal_ml_kem_per_file_standards_trace_gate_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem per-file standards trace gate: ok\n'
