#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-memory-safety-evidence.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem memory-safety evidence: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem memory-safety evidence: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-memory-safety-evidence"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_memory_safety_evidence.h
require_file latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
require_file latticra-q-seal/tests/q_seal_ml_kem_memory_safety_evidence_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh

require_contains 'latticra_q_seal_ml_kem_memory_safety_evidence_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_memory_safety_evidence.h
require_contains 'latticra-q-seal-ml-kem-memory-safety-evidence/0.1' latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
require_contains 'size_overflow_checks_recorded = 0u' latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
require_contains 'memory_safety_tests_executed = 0u' latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
require_contains 'required_memory_safety_items_total = 20u' latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
require_contains 'latticra q-seal ml-kem memory-safety evidence invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_memory_safety_evidence_invariants.c
require_contains 'ml_kem_memory_safety_evidence_present=1' latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
require_contains 'memory_safety_tests_executed=0' latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
require_contains 'ml_kem_memory_safety_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md
require_contains 'required_memory_safety_items_total=20' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c \
  latticra-q-seal/tests/q_seal_ml_kem_memory_safety_evidence_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem memory-safety evidence: ok\n'
