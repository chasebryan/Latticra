#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-implementation-binding-manifest.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem implementation binding manifest: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem implementation binding manifest: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-implementation-binding-manifest"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_binding_manifest.h
require_file latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_file latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh

require_contains 'latticra_q_seal_ml_kem_implementation_binding_manifest_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_binding_manifest.h
require_contains 'latticra-q-seal-ml-kem-implementation-binding-manifest/0.1' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'NIST-FIPS-203-and-SP-800-227' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'fips_conformance_matrix_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'sp800_227_usage_profile_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'implementation_traceability_matrix_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'primitive_source_acceptance_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'source_layout_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'implementation_file_digest_plan_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'clean_room_author_attestation_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'per_file_standards_trace_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'per_file_test_trace_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_capability_matrix_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_fixture_row_plan_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_fixture_digest_row_template_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_parser_contract_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_response_contract_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_response_fixture_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_submission_package_contract_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'vector_fixture_lock_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'vector_fixture_digest_ledger_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'replay_transcript_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'acvp_verdict_receipt_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'validation_claim_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'module_boundary_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'required_binding_items_total = 48u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'latticra q-seal ml-kem implementation binding manifest invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
require_contains 'ml_kem_implementation_binding_manifest_present=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'fips_conformance_matrix_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'sp800_227_usage_profile_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'implementation_traceability_matrix_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'primitive_source_acceptance_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'source_layout_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'implementation_file_digest_plan_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'clean_room_author_attestation_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'per_file_standards_trace_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'per_file_test_trace_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'ci_promotion_evidence_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_capability_matrix_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_fixture_row_plan_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_fixture_digest_row_template_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_parser_contract_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_response_contract_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_response_fixture_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_submission_package_contract_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'vector_fixture_lock_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'vector_fixture_digest_ledger_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'replay_transcript_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_verdict_receipt_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'validation_claim_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'module_boundary_gate_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'implementation_code_present=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'source_layout_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'implementation_file_digest_plan_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'clean_room_author_attestation_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'per_file_standards_trace_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'per_file_test_trace_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'replay_transcript_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'acvp_verdict_receipt_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'validation_claim_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'module_boundary_gate_bound=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'required_binding_items_total=48' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c \
  latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem implementation binding manifest: ok\n'
