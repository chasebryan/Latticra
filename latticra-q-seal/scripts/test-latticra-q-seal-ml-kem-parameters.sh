#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-parameters.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem parameters: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem parameters: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-parameters"

require_file latticra-q-seal/include/latticra/q_seal.h
require_file latticra-q-seal/src/q_seal.c
require_file latticra-q-seal/include/latticra/q_seal_ml_kem.h
require_file latticra-q-seal/src/q_seal_ml_kem.c
require_file latticra-q-seal/tests/q_seal_ml_kem_parameters_invariants.c
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-parameters.sh

require_contains 'LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512' latticra-q-seal/include/latticra/q_seal_ml_kem.h
require_contains 'latticra_q_seal_ml_kem_parameters' latticra-q-seal/include/latticra/q_seal_ml_kem.h
require_contains 'latticra-q-seal-ml-kem/0.1' latticra-q-seal/src/q_seal_ml_kem.c
require_contains 'NIST-FIPS-203' latticra-q-seal/src/q_seal_ml_kem.c
require_contains 'set_common_parameter_fields(out, parameter_set, 1u, 2u, 3u, 2u, 10u, 4u, 128u, 800u, 1632u, 768u)' latticra-q-seal/src/q_seal_ml_kem.c
require_contains 'set_common_parameter_fields(out, parameter_set, 3u, 3u, 2u, 2u, 10u, 4u, 192u, 1184u, 2400u, 1088u)' latticra-q-seal/src/q_seal_ml_kem.c
require_contains 'set_common_parameter_fields(out, parameter_set, 5u, 4u, 2u, 2u, 11u, 5u, 256u, 1568u, 3168u, 1568u)' latticra-q-seal/src/q_seal_ml_kem.c
require_contains 'latticra q-seal ml-kem parameters invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_parameters_invariants.c
require_contains 'ml_kem_parameters_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
require_contains 'ML-KEM-512 256 3329 2 3 2 10 4 128 800 1632 768 32' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
require_contains 'ML-KEM-768 256 3329 3 2 2 10 4 192 1184 2400 1088 32' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
require_contains 'ML-KEM-1024 256 3329 4 2 2 11 5 256 1568 3168 1568 32' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/tests/q_seal_ml_kem_parameters_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem parameters: ok\n'
