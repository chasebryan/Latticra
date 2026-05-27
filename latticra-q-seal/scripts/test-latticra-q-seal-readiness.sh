#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-readiness.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal readiness: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal readiness: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-readiness"

require_file latticra-q-seal/include/latticra/q_seal_readiness.h
require_file latticra-q-seal/src/q_seal_readiness.c
require_file latticra-q-seal/tests/q_seal_readiness_invariants.c
require_file latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh

require_contains 'latticra_q_seal_readiness_prepare' latticra-q-seal/include/latticra/q_seal_readiness.h
require_contains 'latticra-q-seal-readiness/0.1' latticra-q-seal/src/q_seal_readiness.c
require_contains 'components_total = 20u' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_vector_schema_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_vector_source_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_negative_test_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_memory_safety_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_api_misuse_resistance_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_source_digest_manifest_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_code_owner_review_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_ci_promotion_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_constant_time_review_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_randomness_source_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_zeroization_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_side_channel_review_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_implementation_binding_manifest_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'runtime_crypto_ready = 0u' latticra-q-seal/src/q_seal_readiness.c
require_contains 'required_readiness_items_total' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra q-seal readiness invariants: ok' latticra-q-seal/tests/q_seal_readiness_invariants.c
require_contains 'q_seal_readiness_profile_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'design_frame_integration_ready=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'runtime_crypto_ready=0' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'q_seal_readiness_profile_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'vector_schema_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'vector_source_intake_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'negative_test_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'memory_safety_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'api_misuse_resistance_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'source_digest_manifest_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'code_owner_review_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'ci_promotion_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'constant_time_review_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'randomness_source_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'zeroization_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'side_channel_review_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'implementation_binding_manifest_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'required_readiness_items_total=328' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal.c \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_evidence_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_intake.c \
  latticra-q-seal/src/q_seal_ml_kem_vector_schema.c \
  latticra-q-seal/src/q_seal_ml_kem_vector_source.c \
  latticra-q-seal/src/q_seal_ml_kem_negative_test_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_api_misuse_resistance.c \
  latticra-q-seal/src/q_seal_ml_kem_source_digest_manifest.c \
  latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c \
  latticra-q-seal/src/q_seal_ml_kem_ci_promotion_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_constant_time_review.c \
  latticra-q-seal/src/q_seal_ml_kem_randomness_source.c \
  latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_side_channel_review.c \
  latticra-q-seal/src/q_seal_ml_kem_provider_differential.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c \
  latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c \
  latticra-q-seal/src/q_seal_readiness.c \
  latticra-q-seal/tests/q_seal_readiness_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal readiness: ok\n'
