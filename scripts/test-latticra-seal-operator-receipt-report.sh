#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-operator-receipt-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal operator receipt report: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal operator receipt report: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/seal_operator_receipt_report_invariants"

require_file include/latticra/seal_operator_receipt_report.h
require_file src/seal_operator_receipt_report.c
require_file tests/seal_operator_receipt_report_invariants.c
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_CONTRACT.md
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION_PLAN.md

require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK' include/latticra/seal_operator_receipt_report.h
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA' include/latticra/seal_operator_receipt_report.h
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE' include/latticra/seal_operator_receipt_report.h
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT' include/latticra/seal_operator_receipt_report.h
require_contains 'latticra_seal_operator_receipt_report_from_sources' include/latticra/seal_operator_receipt_report.h
require_contains 'latticra_seal_operator_receipt_report_render' include/latticra/seal_operator_receipt_report.h
require_contains 'LATTICRA SEAL OPERATOR RECEIPT REPORT' src/seal_operator_receipt_report.c
require_contains 'operator_receipt_profile=%s' src/seal_operator_receipt_report.c
require_contains 'receipt_status=%s' src/seal_operator_receipt_report.c
require_contains 'source_capability_metadata_present=%u' src/seal_operator_receipt_report.c
require_contains 'source_denial_reason_present=%u' src/seal_operator_receipt_report.c
require_contains 'bounded_string_is' src/seal_operator_receipt_report.c
require_contains 'source-would-allow-effect-denied' src/seal_operator_receipt_report.c
require_contains 'non-report-only-source-denied' src/seal_operator_receipt_report.c
require_contains 'known-capability-candidate-still-denied' tests/seal_operator_receipt_report_invariants.c
require_contains 'unterminated receipt render rejected' tests/seal_operator_receipt_report_invariants.c
require_contains 'seal operator receipt report invariants: ok' tests/seal_operator_receipt_report_invariants.c
require_contains 'operator_receipt_profile=latticra-seal-operator-receipt-report/0.1' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'receipt_status=denied-report-only' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'source_capability_metadata_present=1' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'source_denial_reason_present=1' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'effect_performed=0' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'unterminated source strings before receipt copy' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'scripts/test-latticra-seal-operator-receipt-report.sh' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
require_contains 'docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md' docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md

cc -std=c99 -Wall -Wextra -Werror -Iinclude \
  src/seal_capability_metadata.c \
  src/seal_operator_receipt_report.c \
  tests/seal_operator_receipt_report_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra seal operator receipt report: ok\n'
