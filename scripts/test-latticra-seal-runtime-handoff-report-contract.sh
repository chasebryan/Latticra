#!/usr/bin/env sh
set -eu

contract="docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md"

test -f "$contract"
test -f docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md
test -f include/latticra/seal_runtime_handoff_evaluation.h

grep -Fq 'Status: Latticra Seal runtime handoff report contract' "$contract"
grep -Fq 'The report surface is report classification, not runtime handoff.' "$contract"
grep -Fq 'report_state=ready-report-only' "$contract"
grep -Fq 'report_state=ready-evaluate-only' "$contract"
grep -Fq 'report_ready=1' "$contract"
grep -Fq 'runtime handoff report metadata implementation' "$contract"

printf 'seal runtime handoff report contract: ok\n'
