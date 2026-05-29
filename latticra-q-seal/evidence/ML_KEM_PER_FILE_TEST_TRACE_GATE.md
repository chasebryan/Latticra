# Latticra Q-Seal ML-KEM Per-File Test Trace Gate

Status: per-file test trace template
Date: 2026-05-27
Scope: per-file KAT, ACVP, vector, and negative-test trace before ML-KEM source acceptance.

This evidence record defines the per-file test-trace gate for future ML-KEM implementation files. It binds each future source or test file to KAT evidence, ACVP contracts, vector fixtures, negative-test evidence, digest rows, per-file standards trace, review disposition, reviewer role mapping, and CI promotion evidence. It does not create source files, record real trace rows, run vectors, generate ACVP responses, approve coverage, accept source, execute ML-KEM operations, emit shared secrets, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
per_file_test_trace_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Per-File Test Trace Gate
test_trace_profile=latticra-q-seal-ml-kem-per-file-test-trace-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
source_boundary=clean-room-no-apple-code
trace_scope=ML-KEM-per-file-KAT-ACVP-negative-test-trace-before-source-acceptance
trace_state=test-trace-template-recorded-trace-rows-blocked
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
primitive_source_acceptance_gate_bound=1
implementation_traceability_matrix_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
kat_manifest_bound=1
kat_runner_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
acvp_contracts_bound=1
vector_schema_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
test_family_columns_recorded=1
parameter_set_columns_recorded=1
operation_family_columns_recorded=1
vector_reference_columns_recorded=1
expected_result_columns_recorded=1
review_disposition_columns_recorded=1
source_files_created=0
per_file_test_trace_rows_recorded=0
kat_trace_coverage_reviewed=0
acvp_trace_coverage_reviewed=0
negative_test_trace_reviewed=0
trace_review_approved=0
per_file_test_trace_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_test_trace_items_total=39
required_test_trace_items_satisfied=32
status=ml-kem-per-file-test-trace-gate-blocked
```

## Acceptance Blockers

```text
source_files_created=0
per_file_test_trace_rows_recorded=0
kat_trace_coverage_reviewed=0
acvp_trace_coverage_reviewed=0
negative_test_trace_reviewed=0
trace_review_approved=0
per_file_test_trace_accepted=0
```

## Non-Claims

This gate is not KAT passage, not ACVP validation, not vector execution, not response generation, not source approval, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
