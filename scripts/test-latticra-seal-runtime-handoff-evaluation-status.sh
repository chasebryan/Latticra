#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal runtime handoff evaluation status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime handoff evaluation status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_RUNTIME_HANDOFF_EVALUATION_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md
require_file docs/status/SEAL_VERIFIED_EFFECT_DECISION_STATUS.md
require_file docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_file include/latticra/seal_runtime_handoff_evaluation.h
require_file src/seal_runtime_handoff_evaluation.c
require_file tests/seal_runtime_handoff_evaluation_invariants.c
require_file scripts/test-latticra-seal-runtime-handoff-evaluation-contract.sh
require_file scripts/test-latticra-seal-runtime-handoff-evaluation.sh

require_contains 'Status: status record for the Latticra Seal runtime handoff evaluation metadata surface' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_contract_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_implementation_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_header_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_source_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_invariant_test_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_runner_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_status_present=1' "$status_file"
require_contains 'seal_verified_effect_decision_status_present=1' "$status_file"
require_contains 'seal_crypto_graduation_gate_status_present=1' "$status_file"
require_contains 'handoff_profile=latticra-seal-runtime-handoff-evaluation/0.1' "$status_file"
require_contains 'decision_profile=latticra-seal-verified-effect-decision/0.1' "$status_file"
require_contains 'crypto_graduation_profile=latticra-seal-crypto-graduation-gate/0.1' "$status_file"
require_contains 'assurance_baseline_profile=latticra-cryptographic-assurance-key-management/0.1' "$status_file"
require_contains 'crypto_graduation_gate_state=graduated-authority-neutral' "$status_file"
require_contains 'requested_handoff=report-only' "$status_file"
require_contains 'crypto_graduation_gate_present=1' "$status_file"
require_contains 'crypto_graduation_gate_passed=1' "$status_file"
require_contains 'standard_expectations_met=1' "$status_file"
require_contains 'local_verify_graduated=1' "$status_file"
require_contains 'receipt_promotion_graduated=1' "$status_file"
require_contains 'authority_promotion_allowed=0' "$status_file"
require_contains 'handoff_state=eligible-report-only' "$status_file"
require_contains 'handoff_eligible=1' "$status_file"
require_contains 'handoff_performed=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'status=runtime-handoff-evaluation-metadata' "$status_file"
require_contains 'runtime handoff report status/public-entry alignment' "$status_file"
require_contains 'DENIED_CRYPTO_GRADUATION_GATE' include/latticra/seal_runtime_handoff_evaluation.h
require_contains 'crypto_graduation_gate_present=%u' src/seal_runtime_handoff_evaluation.c
require_contains 'standard_expectations_met=%u' src/seal_runtime_handoff_evaluation.c
require_contains 'denied-crypto-graduation-gate' src/seal_runtime_handoff_evaluation.c

require_contains 'runtime handoff evaluation metadata/status' README.md
require_contains 'seal_runtime_handoff_evaluation_contract_present=1' README.md
require_contains 'seal_runtime_handoff_evaluation_implementation_present=1' README.md
require_contains 'seal_runtime_handoff_evaluation_status_present=1' README.md
require_contains 'runtime_handoff_evaluation_eligible=1' README.md
require_contains 'runtime_handoff_evaluation_state=eligible-report-only' README.md
require_contains 'runtime_handoff_evaluation_handoff_performed=0' README.md
require_contains 'runtime_handoff_evaluation_runtime_authority_granted=0' README.md
require_contains 'docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_RUNTIME_HANDOFF_EVALUATION_STATUS.md' README.md

require_contains 'Latest Seal runtime handoff evaluation status/public-entry note: 2026-05-25 CDT' STATUS.md
require_contains 'Seal runtime handoff evaluation status/public-entry alignment' STATUS.md
require_contains 'seal_runtime_handoff_evaluation_status_present=1' STATUS.md
require_contains 'runtime_handoff_evaluation_eligible=1' STATUS.md
require_contains 'runtime_handoff_evaluation_state=eligible-report-only' STATUS.md
require_contains 'runtime_handoff_evaluation_handoff_performed=0' STATUS.md
require_contains 'runtime_handoff_evaluation_runtime_authority_granted=0' STATUS.md

require_contains 'SEAL_RUNTIME_HANDOFF_EVALUATION_STATUS.md' docs/status/README.md
require_contains 'seal_runtime_handoff_evaluation_status_present=1' docs/status/README.md
require_contains 'runtime handoff evaluation metadata/status' docs/status/README.md

require_contains 'Latest Seal runtime handoff evaluation status/public-entry note: 2026-05-25 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal runtime handoff evaluation status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'seal_runtime_handoff_evaluation_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_evaluation_eligible=1' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_evaluation_state=eligible-report-only' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_evaluation_handoff_performed=0' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_evaluation_runtime_authority_granted=0' docs/status/CURRENT_STATUS.md

require_contains 'SEAL_RUNTIME_HANDOFF_EVALUATION_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal runtime handoff evaluation status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal runtime handoff evaluation status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal runtime handoff evaluation status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_RUNTIME_HANDOFF_EVALUATION_STATUS.md' docs/project_notes/README.md

printf 'seal runtime handoff evaluation status: ok\n'
