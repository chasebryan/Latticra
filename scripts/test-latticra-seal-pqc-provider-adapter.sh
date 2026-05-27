#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-pqc-provider-adapter.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal pqc provider adapter: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal pqc provider adapter: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/seal_pqc_provider_adapter_invariants"

require_file include/latticra/seal_pqc_integration_frame.h
require_file src/seal_pqc_integration_frame.c
require_file include/latticra/seal_pqc_provider_adapter.h
require_file src/seal_pqc_provider_adapter.c
require_file tests/seal_pqc_provider_adapter_invariants.c
require_file docs/LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md
require_file docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md
require_file docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
require_file docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md

require_contains 'LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_OK' include/latticra/seal_pqc_provider_adapter.h
require_contains 'latticra_seal_pqc_provider_adapter_from_frame' include/latticra/seal_pqc_provider_adapter.h
require_contains 'latticra_seal_pqc_provider_adapter_report' include/latticra/seal_pqc_provider_adapter.h
require_contains 'latticra-seal-pqc-provider-adapter/0.1' src/seal_pqc_provider_adapter.c
require_contains 'latticra-clean-room-pqc/0.1' src/seal_pqc_provider_adapter.c
require_contains 'clean-room-no-apple-code' src/seal_pqc_provider_adapter.c
require_contains 'provider_name=%s' src/seal_pqc_provider_adapter.c
require_contains 'apple_corecrypto_code_copied=%u' src/seal_pqc_provider_adapter.c
require_contains 'key_generation_performed=%u' src/seal_pqc_provider_adapter.c
require_contains 'seal pqc provider adapter invariants: ok' tests/seal_pqc_provider_adapter_invariants.c
require_contains 'apple_corecrypto_code_copied=0' tests/seal_pqc_provider_adapter_invariants.c
require_contains 'seal_pqc_provider_adapter_present=1' docs/LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md
require_contains 'clean_room_profile=latticra-clean-room-pqc/0.1' docs/LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md
require_contains 'provider_name=liboqs' docs/LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md
require_contains 'seal_pqc_provider_adapter_present=1' docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md

cc $CFLAGS -Iinclude \
  src/seal_pqc_integration_frame.c \
  src/seal_pqc_provider_adapter.c \
  tests/seal_pqc_provider_adapter_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra seal pqc provider adapter: ok\n'
