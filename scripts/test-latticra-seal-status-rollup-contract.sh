#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal status rollup contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal status rollup contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_STATUS_ROLLUP_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md
require_file include/latticra/seal_runtime_handoff.h
require_file src/seal_runtime_handoff.c
require_file scripts/test-latticra-seal-runtime-handoff.sh

require_contains 'Status: Latticra Seal status rollup contract' "$contract"
require_contains 'This document does not implement status rollup behavior.' "$contract"
require_contains 'rollup_state=metadata-only' "$contract"
require_contains 'cryptographic_verification_supported=0' "$contract"
require_contains 'verified=0' "$contract"
require_contains 'capability_gate_allowed=0' "$contract"
require_contains 'effect_allowed=0' "$contract"
require_contains 'handoff_active=0' "$contract"
require_contains 'runtime_boundary_state=disabled' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'status rollup metadata implementation' "$contract"
require_contains 'Seal documentation/index alignment' "$contract"

printf 'seal status rollup contract: ok\n'
