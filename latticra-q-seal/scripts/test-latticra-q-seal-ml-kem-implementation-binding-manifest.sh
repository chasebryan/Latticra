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
require_contains 'required_binding_items_total = 26u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
require_contains 'latticra q-seal ml-kem implementation binding manifest invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
require_contains 'ml_kem_implementation_binding_manifest_present=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'ci_promotion_evidence_bound=1' latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'implementation_code_present=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
require_contains 'required_binding_items_total=26' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c \
  latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem implementation binding manifest: ok\n'
