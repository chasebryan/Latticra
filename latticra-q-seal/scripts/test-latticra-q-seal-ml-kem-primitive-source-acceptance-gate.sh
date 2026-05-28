#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem primitive source acceptance gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem primitive source acceptance gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-primitive-source-acceptance-gate"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_primitive_source_acceptance_gate.h
require_file latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_file latticra-q-seal/tests/q_seal_ml_kem_primitive_source_acceptance_gate_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh

require_contains 'latticra_q_seal_ml_kem_primitive_source_acceptance_gate_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_primitive_source_acceptance_gate.h
require_contains 'latticra-q-seal-ml-kem-primitive-source-acceptance-gate/0.1' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'planned_source_units_count = 9u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'source_layout_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'implementation_traceability_matrix_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'implementation_file_digest_plan_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'clean_room_author_attestation_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'per_file_standards_trace_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'per_file_test_trace_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'source_files_created = 0u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'shared_secret_emission_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c
require_contains 'latticra q-seal ml-kem primitive source acceptance gate invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_primitive_source_acceptance_gate_invariants.c
require_contains 'primitive_source_acceptance_gate_present=1' latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'source_layout_gate_bound=1' latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'implementation_file_digest_plan_bound=1' latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'clean_room_author_attestation_gate_bound=1' latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'per_file_standards_trace_gate_bound=1' latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'per_file_test_trace_gate_bound=1' latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'source_acceptance_approved=0' latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'required_acceptance_items_total=38' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_contains 'required_acceptance_items_satisfied=30' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c \
  latticra-q-seal/tests/q_seal_ml_kem_primitive_source_acceptance_gate_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem primitive source acceptance gate: ok\n'
