#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal measurement contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal measurement contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md
require_file docs/LATTICRA_SEAL_CONTRACT.md
require_file docs/LATTICRA_SEAL_REPORT_IMPLEMENTATION.md
require_file include/latticra/seal_report.h
require_file src/seal_report.c
require_file include/latticra/seal_measurement.h
require_file src/seal_measurement.c
require_file tests/seal_measurement_invariants.c
require_file scripts/test-latticra-seal-measurement.sh

require_contains 'Status: Latticra Seal measurement contract' docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md
require_contains 'This document does not implement measurement.' docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md
require_contains 'SHA-256' docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md
require_contains 'No custom hash function may be introduced.' docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md
require_contains 'read-only SHA-256 measurement implementation' docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md
require_contains 'does not permit signing, encryption, key handling' docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md

require_contains 'measurement_supported=1' docs/LATTICRA_SEAL_REPORT_IMPLEMENTATION.md
require_contains 'measurement_supported' include/latticra/seal_report.h
require_contains 'report.measurement_supported = 1u;' src/seal_report.c
require_contains 'LATTICRA SEAL MEASUREMENT' src/seal_measurement.c
require_contains 'SHA-256' src/seal_measurement.c
require_contains 'write_performed == 0u' src/seal_measurement.c
require_contains 'network_performed == 0u' src/seal_measurement.c
require_contains 'runtime_granted == 0u' src/seal_measurement.c

printf 'latticra seal measurement contract: ok\n'
