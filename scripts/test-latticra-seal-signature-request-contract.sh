#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signature request contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signature request contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md
require_file include/latticra/seal_report_envelope.h
require_file src/seal_report_envelope.c
require_file tests/seal_report_envelope_invariants.c
require_file scripts/test-latticra-seal-report-envelope.sh

require_contains 'Status: Latticra Seal signature request contract' "$contract"
require_contains 'The signature-request surface is request classification, not signing and not verification.' "$contract"
require_contains 'This document does not implement signing.' "$contract"
require_contains 'signature_request_state=requested-metadata-only' "$contract"
require_contains 'signature_request_ready=1' "$contract"
require_contains 'signature_performed=0' "$contract"
require_contains 'verification_performed=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'signature request metadata implementation' "$contract"

printf 'seal signature request contract: ok\n'
