#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-receipt-replay-results.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem receipt replay results: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem receipt replay results: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-receipt-replay-results"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_receipt_replay_results.h
require_file latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c
require_file latticra-q-seal/tests/q_seal_ml_kem_receipt_replay_results_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh

require_contains 'latticra_q_seal_ml_kem_receipt_replay_results_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_receipt_replay_results.h
require_contains 'latticra-q-seal-ml-kem-receipt-replay-results/0.1' latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c
require_contains 'NIST-SP-800-218-SSDF-and-FIPS-203' latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c
require_contains 'required_replay_items_total = 24u' latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c
require_contains 'latticra q-seal ml-kem receipt replay results invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_receipt_replay_results_invariants.c
require_contains 'ml_kem_receipt_replay_results_present=1' latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
require_contains 'source_digest_verification_bound=1' latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
require_contains 'source_replay_results_recorded=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md
require_contains 'required_replay_items_total=24' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c \
  latticra-q-seal/tests/q_seal_ml_kem_receipt_replay_results_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem receipt replay results: ok\n'
