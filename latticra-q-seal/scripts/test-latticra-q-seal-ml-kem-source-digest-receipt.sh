#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-source-digest-receipt.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem source digest receipt: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem source digest receipt: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-source-digest-receipt"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_receipt.h
require_file latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c
require_file latticra-q-seal/tests/q_seal_ml_kem_source_digest_receipt_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh

require_contains 'latticra_q_seal_ml_kem_source_digest_receipt_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_receipt.h
require_contains 'latticra-q-seal-ml-kem-source-digest-receipt/0.1' latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c
require_contains 'NIST-SP-800-218-SSDF-and-FIPS-203' latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c
require_contains 'required_receipt_items_total = 23u' latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c
require_contains 'latticra q-seal ml-kem source digest receipt invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_source_digest_receipt_invariants.c
require_contains 'ml_kem_source_digest_receipt_present=1' latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
require_contains 'source_digest_manifest_bound=1' latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
require_contains 'source_receipts_recorded=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT.md
require_contains 'required_receipt_items_total=23' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c \
  latticra-q-seal/tests/q_seal_ml_kem_source_digest_receipt_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem source digest receipt: ok\n'
