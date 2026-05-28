#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-secret-ops.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem secret ops: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem secret ops: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-secret-ops"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_secret_ops.h
require_file latticra-q-seal/src/q_seal_ml_kem_secret_ops.c
require_file latticra-q-seal/tests/q_seal_ml_kem_secret_ops_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_SECRET_OPS.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-ops.sh

require_contains 'latticra_q_seal_ml_kem_secure_zero' latticra-q-seal/include/latticra/q_seal_ml_kem_secret_ops.h
require_contains 'latticra_q_seal_ml_kem_constant_time_equal' latticra-q-seal/include/latticra/q_seal_ml_kem_secret_ops.h
require_contains 'latticra_q_seal_ml_kem_constant_time_select' latticra-q-seal/include/latticra/q_seal_ml_kem_secret_ops.h
require_contains 'LATTICRA_Q_SEAL_STATUS_INVALID_ARGUMENT' latticra-q-seal/include/latticra/q_seal.h
require_contains 'volatile unsigned char *cursor' latticra-q-seal/src/q_seal_ml_kem_secret_ops.c
require_contains '0u - nonzero_to_one(select)' latticra-q-seal/src/q_seal_ml_kem_secret_ops.c
require_contains 'for (index = 0u; index < buffer_len; index++)' latticra-q-seal/src/q_seal_ml_kem_secret_ops.c
require_contains 'byte_ranges_overlap' latticra-q-seal/src/q_seal_ml_kem_secret_ops.c
require_contains 'partial nonzero overlap leaves output untouched' latticra-q-seal/tests/q_seal_ml_kem_secret_ops_invariants.c
require_contains 'latticra q-seal ml-kem secret ops invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_secret_ops_invariants.c
require_contains 'ml_kem_secret_ops_present=1' latticra-q-seal/evidence/ML_KEM_SECRET_OPS.md
require_contains 'partial_select_overlap_rejected=1' latticra-q-seal/evidence/ML_KEM_SECRET_OPS.md
require_contains 'operation_execution_allowed=0' latticra-q-seal/evidence/ML_KEM_SECRET_OPS.md
require_contains 'ml_kem_secret_ops_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md
require_contains 'partial_select_overlap_rejected=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md
require_contains 'production_crypto_claim_allowed=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_secret_ops.c \
  latticra-q-seal/tests/q_seal_ml_kem_secret_ops_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem secret ops: ok\n'
