#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal operator receipt report contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal operator receipt report contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_CONTRACT.md"

require_file "$contract"
require_file docs/latticra-seal/PRODUCT.md
require_file docs/status/SEAL_PRODUCT_SPINE_STATUS.md
require_file docs/LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_SURFACE.md
require_file docs/status/SEAL_CAPABILITY_METADATA_REPORT_SURFACE_STATUS.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_POLICY_DECISION_STATUS.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
require_file docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNED_REQUEST_STATUS.md
require_file docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md

require_contains 'Status: Latticra Seal operator receipt report contract' "$contract"
require_contains 'operator_receipt_profile=latticra-seal-operator-receipt-report/0.1' "$contract"
require_contains 'receipt_mode=report-only' "$contract"
require_contains 'receipt_status=denied-report-only' "$contract"
require_contains 'source_capability_metadata_present=1' "$contract"
require_contains 'source_policy_decision_present=1' "$contract"
require_contains 'source_request_freshness_present=1' "$contract"
require_contains 'source_signed_request_present=1' "$contract"
require_contains 'source_runtime_dry_run_present=1' "$contract"
require_contains 'source_denial_reason_present=1' "$contract"
require_contains 'capability_name=' "$contract"
require_contains 'capability_known=' "$contract"
require_contains 'capability_candidate=' "$contract"
require_contains 'policy_decision_state=' "$contract"
require_contains 'request_freshness_state=' "$contract"
require_contains 'signed_request_state=' "$contract"
require_contains 'runtime_dry_run_state=' "$contract"
require_contains 'blocked_reason=' "$contract"
require_contains 'default_action_deny=1' "$contract"
require_contains 'would_allow=0' "$contract"
require_contains 'would_deny=1' "$contract"
require_contains 'would_require_operator_review=1' "$contract"
require_contains 'would_execute_tool=0' "$contract"
require_contains 'would_read_host=0' "$contract"
require_contains 'would_write_host=0' "$contract"
require_contains 'would_use_network=0' "$contract"
require_contains 'would_grant_runtime_authority=0' "$contract"
require_contains 'report_only=1' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'receipt_complete=0' "$contract"
require_contains 'receipt_invalid=1' "$contract"
require_contains 'include/latticra/seal_operator_receipt_report.h' "$contract"
require_contains 'src/seal_operator_receipt_report.c' "$contract"
require_contains 'tests/seal_operator_receipt_report_invariants.c' "$contract"
require_contains 'scripts/test-latticra-seal-operator-receipt-report.sh' "$contract"
require_contains 'no-effect operator receipt report implementation, report surface, and status record are now current follow-up checkpoints' "$contract"
require_contains 'docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md' "$contract"
require_contains 'docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md' "$contract"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md' "$contract"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md' "$contract"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' "$contract"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' "$contract"
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' "$contract"
require_contains 'Seal Panel dashboard view-model implementation plan' "$contract"
require_contains 'signed receipt trust-root boundary contract' "$contract"

printf 'latticra seal operator receipt report contract: ok\n'
