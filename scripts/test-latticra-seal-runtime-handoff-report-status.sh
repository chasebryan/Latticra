#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal runtime handoff report status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime handoff report status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_RUNTIME_HANDOFF_REPORT_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md
require_file docs/status/SEAL_RUNTIME_HANDOFF_EVALUATION_STATUS.md
require_file docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_file include/latticra/seal_runtime_handoff_report.h
require_file src/seal_runtime_handoff_report.c
require_file tests/seal_runtime_handoff_report_invariants.c
require_file scripts/test-latticra-seal-runtime-handoff-report-contract.sh
require_file scripts/test-latticra-seal-runtime-handoff-report.sh

require_contains 'Status: status record for the Latticra Seal runtime handoff report metadata surface' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_runtime_handoff_report_contract_present=1' "$status_file"
require_contains 'seal_runtime_handoff_report_implementation_present=1' "$status_file"
require_contains 'seal_runtime_handoff_report_header_present=1' "$status_file"
require_contains 'seal_runtime_handoff_report_source_present=1' "$status_file"
require_contains 'seal_runtime_handoff_report_invariant_test_present=1' "$status_file"
require_contains 'seal_runtime_handoff_report_runner_present=1' "$status_file"
require_contains 'seal_runtime_handoff_report_status_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_contract_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_implementation_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_runner_present=1' "$status_file"
require_contains 'seal_runtime_handoff_evaluation_status_present=1' "$status_file"
require_contains 'seal_crypto_graduation_gate_status_present=1' "$status_file"
require_contains 'readme_links_runtime_handoff_report_contract=1' "$status_file"
require_contains 'readme_links_runtime_handoff_report_implementation=1' "$status_file"
require_contains 'readme_links_runtime_handoff_report_status=1' "$status_file"
require_contains 'root_status_mentions_runtime_handoff_report_status=1' "$status_file"
require_contains 'status_index_links_runtime_handoff_report_status=1' "$status_file"
require_contains 'foundation_index_links_runtime_handoff_report_status=1' "$status_file"
require_contains 'project_notes_mark_runtime_handoff_report_status_complete=1' "$status_file"
require_contains 'report_profile=latticra-seal-runtime-handoff-report/0.1' "$status_file"
require_contains 'handoff_profile=latticra-seal-runtime-handoff-evaluation/0.1' "$status_file"
require_contains 'decision_profile=latticra-seal-verified-effect-decision/0.1' "$status_file"
require_contains 'gate_profile=latticra-seal-verified-capability-gate/0.1' "$status_file"
require_contains 'receipt_profile=latticra-seal-verified-receipt/0.1' "$status_file"
require_contains 'verify_profile=latticra-seal-ed25519-verify/0.1' "$status_file"
require_contains 'message_digest_algorithm=SHA-256' "$status_file"
require_contains 'public_key_identity_label=rfc8032-test-key' "$status_file"
require_contains 'crypto_graduation_profile=latticra-seal-crypto-graduation-gate/0.1' "$status_file"
require_contains 'assurance_baseline_profile=latticra-cryptographic-assurance-key-management/0.1' "$status_file"
require_contains 'crypto_graduation_gate_state=graduated-authority-neutral' "$status_file"
require_contains 'requested_capability=verified-receipt-report' "$status_file"
require_contains 'requested_effect=report-only' "$status_file"
require_contains 'requested_handoff=report-only' "$status_file"
require_contains 'requested_report=report-only' "$status_file"
require_contains 'requested_scope=local-fixture-scope' "$status_file"
require_contains 'crypto_graduation_gate_present=1' "$status_file"
require_contains 'crypto_graduation_gate_passed=1' "$status_file"
require_contains 'standard_expectations_met=1' "$status_file"
require_contains 'local_verify_graduated=1' "$status_file"
require_contains 'receipt_promotion_graduated=1' "$status_file"
require_contains 'authority_promotion_allowed=0' "$status_file"
require_contains 'verified=1' "$status_file"
require_contains 'authority_usable=0' "$status_file"
require_contains 'receipt_capability_gate_allowed=0' "$status_file"
require_contains 'gate_allowed=1' "$status_file"
require_contains 'gate_state=allowed-metadata-only' "$status_file"
require_contains 'decision_state=allowed-report-only' "$status_file"
require_contains 'effect_allowed=1' "$status_file"
require_contains 'handoff_state=eligible-report-only' "$status_file"
require_contains 'handoff_eligible=1' "$status_file"
require_contains 'report_state=ready-report-only' "$status_file"
require_contains 'report_ready=1' "$status_file"
require_contains 'handoff_performed=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'status=runtime-handoff-report-metadata' "$status_file"
require_contains 'runtime_handoff_report_added=1' "$status_file"
require_contains 'runtime_handoff_execution_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'signing_added=0' "$status_file"
require_contains 'key_generation_added=0' "$status_file"
require_contains 'private_key_handling_added=0' "$status_file"
require_contains 'trust_store_behavior_added=0' "$status_file"
require_contains 'revocation_lookup_added=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'seal runtime handoff report status: ok' "$status_file"
require_contains 'seal runtime handoff report invariants: ok' "$status_file"
require_contains 'sealed report envelope status/public-entry alignment' "$status_file"
require_contains 'DENIED_CRYPTO_GRADUATION_GATE' include/latticra/seal_runtime_handoff_report.h
require_contains 'crypto_graduation_gate_present=%u' src/seal_runtime_handoff_report.c
require_contains 'standard_expectations_met=%u' src/seal_runtime_handoff_report.c
require_contains 'denied-crypto-graduation-gate' src/seal_runtime_handoff_report.c

require_contains 'runtime handoff report metadata/status' README.md
require_contains 'seal_runtime_handoff_report_contract_present=1' README.md
require_contains 'seal_runtime_handoff_report_implementation_present=1' README.md
require_contains 'seal_runtime_handoff_report_status_present=1' README.md
require_contains 'runtime_handoff_report_ready=1' README.md
require_contains 'runtime_handoff_report_state=ready-report-only' README.md
require_contains 'runtime_handoff_report_handoff_performed=0' README.md
require_contains 'runtime_handoff_report_runtime_authority_granted=0' README.md
require_contains 'docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_RUNTIME_HANDOFF_REPORT_STATUS.md' README.md

require_contains 'Latest Seal runtime handoff report status/public-entry note: 2026-05-25 CDT' STATUS.md
require_contains 'Seal runtime handoff report status/public-entry alignment' STATUS.md
require_contains 'seal_runtime_handoff_report_status_present=1' STATUS.md
require_contains 'runtime_handoff_report_ready=1' STATUS.md
require_contains 'runtime_handoff_report_state=ready-report-only' STATUS.md
require_contains 'runtime_handoff_report_handoff_performed=0' STATUS.md
require_contains 'runtime_handoff_report_runtime_authority_granted=0' STATUS.md

require_contains 'SEAL_RUNTIME_HANDOFF_REPORT_STATUS.md' docs/status/README.md
require_contains 'seal_runtime_handoff_report_status_present=1' docs/status/README.md
require_contains 'runtime handoff report metadata/status' docs/status/README.md

require_contains 'Latest Seal runtime handoff report status/public-entry note: 2026-05-25 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal runtime handoff report status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'seal_runtime_handoff_report_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_report_ready=1' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_report_state=ready-report-only' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_report_handoff_performed=0' docs/status/CURRENT_STATUS.md
require_contains 'runtime_handoff_report_runtime_authority_granted=0' docs/status/CURRENT_STATUS.md

require_contains 'SEAL_RUNTIME_HANDOFF_REPORT_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal runtime handoff report status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal runtime handoff report status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal runtime handoff report status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_RUNTIME_HANDOFF_REPORT_STATUS.md' docs/project_notes/README.md

printf 'seal runtime handoff report status: ok\n'
