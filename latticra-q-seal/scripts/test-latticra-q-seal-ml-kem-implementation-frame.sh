#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-implementation-frame.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem implementation frame: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem implementation frame: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-implementation-frame"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_frame.h
require_file latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
require_file latticra-q-seal/tests/q_seal_ml_kem_implementation_frame_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FRAME.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh

require_contains 'latticra_q_seal_ml_kem_implementation_frame_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_frame.h
require_contains 'latticra-q-seal-ml-kem-implementation-frame/0.1' latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
require_contains 'clean-room-no-apple-code' latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
require_contains 'planned_module_count = 9u' latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
require_contains 'constant_time_design_recorded == 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
require_contains 'implementation_code_present == 0u' latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
require_contains 'latticra q-seal ml-kem implementation frame invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_implementation_frame_invariants.c
require_contains 'ml_kem_implementation_frame_present=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FRAME.md
require_contains 'implementation_code_present=0' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FRAME.md
require_contains 'ml_kem_implementation_frame_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md
require_contains 'required_design_items_total=12' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c \
  latticra-q-seal/tests/q_seal_ml_kem_implementation_frame_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem implementation frame: ok\n'
