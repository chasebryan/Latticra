#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-pqc-integration-frame.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal pqc integration frame: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal pqc integration frame: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/seal_pqc_integration_frame_invariants"

require_file include/latticra/seal_pqc_integration_frame.h
require_file src/seal_pqc_integration_frame.c
require_file tests/seal_pqc_integration_frame_invariants.c
require_file docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
require_file docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
require_file docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
require_file docs/status/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE_STATUS.md

require_contains 'LATTICRA_SEAL_PQC_INTEGRATION_FRAME_OK' include/latticra/seal_pqc_integration_frame.h
require_contains 'latticra_seal_pqc_integration_frame_prepare' include/latticra/seal_pqc_integration_frame.h
require_contains 'latticra_seal_pqc_integration_frame_report' include/latticra/seal_pqc_integration_frame.h
require_contains 'latticra-seal-pqc-integration-frame/0.1' src/seal_pqc_integration_frame.c
require_contains 'github.com/apple/corecrypto@2026-05' src/seal_pqc_integration_frame.c
require_contains 'evaluation-only-no-redistribution' src/seal_pqc_integration_frame.c
require_contains 'github.com/open-quantum-safe/liboqs' src/seal_pqc_integration_frame.c
require_contains 'nist_fips_203_ml_kem_tracked=%u' src/seal_pqc_integration_frame.c
require_contains 'apple_corecrypto_embedding_allowed=%u' src/seal_pqc_integration_frame.c
require_contains 'candidate_provider_production_use_allowed=%u' src/seal_pqc_integration_frame.c
require_contains 'post_quantum_migration_claim_allowed=%u' src/seal_pqc_integration_frame.c
require_contains 'seal pqc integration frame invariants: ok' tests/seal_pqc_integration_frame_invariants.c
require_contains 'apple_corecrypto_embedding_allowed=0' tests/seal_pqc_integration_frame_invariants.c
require_contains 'seal_pqc_integration_frame_present=1' docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
require_contains 'apple_corecrypto_embedding_allowed=0' docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
require_contains 'candidate_provider=liboqs' docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
require_contains 'seal_pqc_integration_frame_present=1' docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
require_contains 'seal_pqc_integration_frame_present=1' docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
require_contains 'seal_pqc_integration_frame_present=1' docs/status/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE_STATUS.md

cc $CFLAGS -Iinclude \
  src/seal_pqc_integration_frame.c \
  tests/seal_pqc_integration_frame_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra seal pqc integration frame: ok\n'
