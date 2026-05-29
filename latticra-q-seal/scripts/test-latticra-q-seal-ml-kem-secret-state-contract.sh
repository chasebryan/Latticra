#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-secret-state-contract.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem secret-state contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem secret-state contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-secret-state-contract"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_secret_state_contract.h
require_file latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
require_file latticra-q-seal/tests/q_seal_ml_kem_secret_state_contract_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh

require_contains 'latticra_q_seal_ml_kem_secret_state_contract_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_secret_state_contract.h
require_contains 'latticra-q-seal-ml-kem-secret-state-contract/0.1' latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
require_contains 'secret_dependent_branch_forbidden = 1u' latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
require_contains 'zeroization_primitive_implemented = 0u' latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
require_contains 'required_secret_state_items_total = 19u' latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
require_contains 'shared_secret_emitted == 0u' latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
require_contains 'latticra q-seal ml-kem secret-state contract invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_secret_state_contract_invariants.c
require_contains 'ml_kem_secret_state_contract_present=1' latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
require_contains 'zeroization_primitive_implemented=0' latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
require_contains 'ml_kem_secret_state_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md
require_contains 'required_secret_state_items_total=19' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c \
  latticra-q-seal/tests/q_seal_ml_kem_secret_state_contract_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem secret-state contract: ok\n'
