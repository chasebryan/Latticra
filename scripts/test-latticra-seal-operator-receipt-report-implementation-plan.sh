#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal operator receipt report implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal operator receipt report implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_CONTRACT.md
require_file scripts/test-latticra-seal-operator-receipt-report-contract.sh
require_file docs/status/SEAL_PRODUCT_SPINE_STATUS.md
require_file docs/status/SEAL_CAPABILITY_METADATA_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
require_file docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md
require_file docs/status/SEAL_SIGNED_REQUEST_STATUS.md
require_file docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md

require_contains 'Status: implementation planning contract fulfilled by the no-effect Latticra Seal operator receipt report implementation' "$plan"
require_contains 'include/latticra/seal_operator_receipt_report.h' "$plan"
require_contains 'src/seal_operator_receipt_report.c' "$plan"
require_contains 'tests/seal_operator_receipt_report_invariants.c' "$plan"
require_contains 'scripts/test-latticra-seal-operator-receipt-report.sh' "$plan"
require_contains 'latticra_seal_operator_receipt_report_t' "$plan"
require_contains 'latticra_seal_operator_receipt_report_from_sources' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_POLICY_DECISION' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_REQUEST_FRESHNESS' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_SIGNED_REQUEST' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_RUNTIME_DRY_RUN' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT' "$plan"
require_contains 'LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_BUFFER_TOO_SMALL' "$plan"
require_contains 'operator_receipt_profile=latticra-seal-operator-receipt-report/0.1' "$plan"
require_contains 'receipt_mode=report-only' "$plan"
require_contains 'receipt_status=denied-report-only' "$plan"
require_contains 'receipt_status=invalid-source-denied' "$plan"
require_contains 'source_capability_metadata_present=1' "$plan"
require_contains 'source_policy_decision_present=1' "$plan"
require_contains 'source_request_freshness_present=1' "$plan"
require_contains 'source_signed_request_present=1' "$plan"
require_contains 'source_runtime_dry_run_present=1' "$plan"
require_contains 'source_denial_reason_present=1' "$plan"
require_contains 'capability_name=seal.capability.report' "$plan"
require_contains 'capability_known=1' "$plan"
require_contains 'capability_candidate=1' "$plan"
require_contains 'policy_decision_state=report-only' "$plan"
require_contains 'request_freshness_state=report-only' "$plan"
require_contains 'signed_request_state=report-only' "$plan"
require_contains 'runtime_dry_run_state=report-only' "$plan"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$plan"
require_contains 'default_action_deny=1' "$plan"
require_contains 'would_allow=0' "$plan"
require_contains 'would_deny=1' "$plan"
require_contains 'would_require_operator_review=1' "$plan"
require_contains 'would_execute_tool=0' "$plan"
require_contains 'would_read_host=0' "$plan"
require_contains 'would_write_host=0' "$plan"
require_contains 'would_use_network=0' "$plan"
require_contains 'would_grant_runtime_authority=0' "$plan"
require_contains 'receipt_complete=1' "$plan"
require_contains 'receipt_invalid=0' "$plan"
require_contains 'receipt_complete=0' "$plan"
require_contains 'receipt_invalid=1' "$plan"
require_contains 'runtime_authority_granted=0' "$plan"
require_contains 'effect_performed=0' "$plan"
require_contains 'host_read_performed=0' "$plan"
require_contains 'host_write_performed=0' "$plan"
require_contains 'network_performed=0' "$plan"
require_contains 'LATTICRA SEAL OPERATOR RECEIPT REPORT' "$plan"
require_contains 'Operator receipt report implementation work is now represented by `docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md`.' "$plan"
require_contains 'docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md' "$plan"
require_contains 'docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' "$plan"
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' "$plan"
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' "$plan"
require_contains 'The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.' "$plan"

printf 'latticra seal operator receipt report implementation plan: ok\n'
