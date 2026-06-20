#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra v1 product completion blocker audit contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_output_contains() {
  pattern="$1"
  output="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_CONTRACT.md'
status='docs/status/LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_STATUS.md'
audit='scripts/latticra-v1-product-completion-blocker-audit.sh'
test_script='scripts/test-latticra-v1-product-completion-blocker-audit-contract.sh'
release_gate='scripts/latticra-v1-release-readiness-gate.sh'
release_gate_doc='docs/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_CONTRACT.md'
release_gate_status='docs/status/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_STATUS.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
fedora_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
nadia_status='docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md'
q_seal='latticra-q-seal/evidence/Q_SEAL_READINESS.md'

for file in "$doc" "$status" "$audit" "$test_script" "$release_gate" \
  "$release_gate_doc" "$release_gate_status" "$ledger" "$fedora_status" \
  "$nadia_status" "$q_seal" README.md STATUS.md docs/status/CURRENT_STATUS.md \
  docs/project_notes/CURRENT_DIRECTION.md docs/project_notes/UPCOMING_WORK.md \
  docs/status/README.md docs/README.md Makefile .github/workflows/latticra-v1-release-readiness-gate.yml
do
  require_file "$file"
done

sh -n "$audit"
sh -n "$test_script"
sh -n "$release_gate"

require_contains 'Status: no-effect v1.0.0 product completion blocker audit contract' "$doc"
require_contains 'Evidence level: product-blocker decomposition only' "$doc"
require_contains 'v1_product_completion_blocker_audit_present=1' "$doc"
require_contains 'v1_product_completion_blocker_audit_mode=no-effect-product-blocker-decomposition' "$doc"
require_contains 'v1_product_completion_blocker_audit_passed=0' "$doc"
require_contains 'v1_product_completion_detail_blocker_count=<observed>' "$doc"
require_contains 'v1_product_completion_detail_blockers=<observed>' "$doc"
require_contains 'fedora_mock_build_evidence_present=<observed>' "$doc"
require_contains 'nadia_inference_runtime_validated=<observed>' "$doc"
require_contains 'q_seal_runtime_blockers_total=<observed>' "$doc"
require_contains 'runtime_authority_granted=<observed>' "$doc"
require_contains 'current_edge_checkpoint_not_v1' "$doc"
require_contains 'fedora_mock_build_evidence_missing' "$doc"
require_contains 'nadia_safety_runtime_not_validated' "$doc"
require_contains 'q_seal_runtime_crypto_blocked' "$doc"
require_contains 'runtime_authority_closed' "$doc"
require_contains 'sh scripts/latticra-v1-product-completion-blocker-audit.sh' "$doc"
require_contains 'sh scripts/test-latticra-v1-product-completion-blocker-audit-contract.sh' "$doc"

require_contains 'Status: v1.0.0 product completion blocker audit/status alignment' "$status"
require_contains 'v1_product_completion_blocker_audit_present=1' "$status"
require_contains 'v1_product_completion_blocker_audit_passed=0' "$status"
require_contains 'v1_product_completion_detail_blocker_count=<observed>' "$status"
require_contains 'fedora_install_remove_transcript_present=<observed>' "$status"
require_contains 'nadia_release_receipt_reviewed=<observed>' "$status"
require_contains 'q_seal_required_readiness_items_satisfied=<observed>' "$status"
require_contains 'host_mutation_performed=0' "$status"

require_contains 'LATTICRA V1 PRODUCT COMPLETION BLOCKER AUDIT' "$audit"
require_contains 'v1_product_completion_blocker_audit_mode=no-effect-product-blocker-decomposition' "$audit"
require_contains 'v1_product_completion_detail_blocker_count=$DETAIL_BLOCKER_COUNT' "$audit"
require_contains "add_detail_blocker 'fedora_mock_build_evidence_missing'" "$audit"
require_contains "add_detail_blocker 'nadia_inference_runtime_not_validated'" "$audit"
require_contains "add_detail_blocker 'q_seal_runtime_blockers_open'" "$audit"
require_contains 'model1_process_launch_performed=0' "$audit"
require_contains 'runtime_crypto_enabled=0' "$audit"
require_contains 'host_mutation_performed=0' "$audit"

require_contains 'PRODUCT_BLOCKER_AUDIT_OUTPUT="$(' "$release_gate"
require_contains 'scripts/latticra-v1-product-completion-blocker-audit.sh' "$release_gate"
require_contains 'v1_product_completion_blocker_audit_present=$PRODUCT_BLOCKER_AUDIT_PRESENT' "$release_gate"
require_contains 'v1_product_completion_detail_blocker_count=$PRODUCT_BLOCKER_DETAIL_COUNT' "$release_gate"
require_contains 'v1_product_completion_detail_blockers=$PRODUCT_BLOCKER_DETAILS' "$release_gate"
require_contains 'v1_product_completion_blocker_audit_present=1' "$release_gate_doc"
require_contains 'v1_product_completion_detail_blocker_count=<observed>' "$release_gate_doc"
require_contains 'v1_product_completion_blocker_audit_present=1' "$release_gate_status"
require_contains 'v1_product_completion_detail_blockers=<observed>' "$release_gate_status"
require_contains 'v1_product_completion_blocker_audit_present=1' "$ledger"
require_contains 'v1_product_completion_detail_blocker_count=<observed>' "$ledger"
require_contains 'product-completion detail blocker audit' README.md
require_contains 'LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_STATUS.md' docs/status/README.md
require_contains 'LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_CONTRACT.md' docs/README.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' STATUS.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'latticra-v1-product-completion-blocker-audit:' Makefile
require_contains 'scripts/test-latticra-v1-product-completion-blocker-audit-contract.sh' .github/workflows/latticra-v1-release-readiness-gate.yml

output="$(sh "$audit")"
require_output_contains 'LATTICRA V1 PRODUCT COMPLETION BLOCKER AUDIT' "$output"
require_output_contains 'v1_product_completion_blocker_audit_present=1' "$output"
require_output_contains 'v1_product_completion_blocker_audit_mode=no-effect-product-blocker-decomposition' "$output"
require_output_contains 'v1_product_completion_blocker_audit_passed=0' "$output"
require_output_contains 'v1_product_completion_detail_blocker_count=' "$output"
require_output_contains 'current_edge_checkpoint_not_v1' "$output"
require_output_contains 'fedora_mock_build_evidence_missing' "$output"
require_output_contains 'nadia_inference_runtime_not_validated' "$output"
require_output_contains 'q_seal_runtime_blockers_open' "$output"
require_output_contains 'runtime_authority_closed' "$output"
require_output_contains 'fedora_mock_build_evidence_present=0' "$output"
require_output_contains 'nadia_inference_runtime_validated=0' "$output"
require_output_contains 'q_seal_runtime_crypto_ready=0' "$output"
require_output_contains 'runtime_authority_granted=0' "$output"
require_output_contains 'model1_process_launch_performed=0' "$output"
require_output_contains 'runtime_crypto_enabled=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"

gate_output="$(sh "$release_gate" --version v1.0.0)"
require_output_contains 'v1_product_completion_blocker_audit_present=1' "$gate_output"
require_output_contains 'v1_product_completion_blocker_audit_passed=0' "$gate_output"
require_output_contains 'v1_product_completion_detail_blocker_count=' "$gate_output"
require_output_contains 'v1_product_completion_detail_blockers=' "$gate_output"

printf 'latticra_v1_product_completion_blocker_audit_contract: ok\n'
