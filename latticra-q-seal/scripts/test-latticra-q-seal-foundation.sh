#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-foundation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal foundation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal foundation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-foundation"

require_file latticra-q-seal/README.md
require_file latticra-q-seal/include/latticra/q_seal.h
require_file latticra-q-seal/src/q_seal.c
require_file latticra-q-seal/tests/q_seal_foundation_invariants.c
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_FOUNDATION.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-foundation.sh

require_contains 'Latticra Q-Seal' latticra-q-seal/README.md
require_contains 'latticra_q_seal_present=1' latticra-q-seal/README.md
require_contains 'LATTICRA_Q_SEAL_FOUNDATION_OK' latticra-q-seal/include/latticra/q_seal.h
require_contains 'latticra_q_seal_foundation_prepare' latticra-q-seal/include/latticra/q_seal.h
require_contains 'latticra-q-seal-foundation/0.1' latticra-q-seal/src/q_seal.c
require_contains 'clean-room-no-apple-code' latticra-q-seal/src/q_seal.c
require_contains 'LATTICRA Q-SEAL FOUNDATION' latticra-q-seal/src/q_seal.c
require_contains 'latticra q-seal foundation invariants: ok' latticra-q-seal/tests/q_seal_foundation_invariants.c
require_contains 'apple_corecrypto_code_copied=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_FOUNDATION.md
require_contains 'key_generation_performed=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_FOUNDATION.md
require_contains 'subsystem_directory=latticra-q-seal' latticra-q-seal/docs/LATTICRA_Q_SEAL_FOUNDATION.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal.c \
  latticra-q-seal/tests/q_seal_foundation_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal foundation: ok\n'
