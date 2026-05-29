#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-code-owner-review.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem code owner review: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem code owner review: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-code-owner-review"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_code_owner_review.h
require_file latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c
require_file latticra-q-seal/tests/q_seal_ml_kem_code_owner_review_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh

require_contains 'latticra_q_seal_ml_kem_code_owner_review_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_code_owner_review.h
require_contains 'latticra-q-seal-ml-kem-code-owner-review/0.1' latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c
require_contains 'NIST-SP-800-218-SSDF-and-FIPS-203' latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c
require_contains 'required_review_items_total = 23u' latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c
require_contains 'latticra q-seal ml-kem code owner review invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_code_owner_review_invariants.c
require_contains 'ml_kem_code_owner_review_evidence_present=1' latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md
require_contains 'source_digest_manifest_bound=1' latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md
require_contains 'approval_receipt_recorded=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW.md
require_contains 'required_review_items_total=23' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c \
  latticra-q-seal/tests/q_seal_ml_kem_code_owner_review_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem code owner review: ok\n'
