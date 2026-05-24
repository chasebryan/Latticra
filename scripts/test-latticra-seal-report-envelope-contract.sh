#!/usr/bin/env sh
set -eu

contract="docs/LATTICRA_SEAL_REPORT_ENVELOPE_CONTRACT.md"

test -f "$contract"
test -f docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md
test -f include/latticra/seal_runtime_handoff_report.h

grep -Fq 'Status: Latticra Seal report envelope contract' "$contract"
grep -Fq 'The envelope surface is envelope classification, not signing and not runtime handoff.' "$contract"
grep -Fq 'envelope_state=sealed-report-only' "$contract"
grep -Fq 'envelope_state=sealed-evaluate-only' "$contract"
grep -Fq 'envelope_ready=1' "$contract"
grep -Fq 'signature_performed=0' "$contract"
grep -Fq 'sealed report envelope metadata implementation' "$contract"
grep -Fq 'signature request contract' "$contract"

printf 'seal report envelope contract: ok\n'
