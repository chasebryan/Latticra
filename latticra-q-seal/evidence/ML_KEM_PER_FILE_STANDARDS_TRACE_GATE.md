# Latticra Q-Seal ML-KEM Per-File Standards Trace Gate

Status: per-file standards trace template
Date: 2026-05-27
Scope: per-file FIPS 203 and SP 800-227 trace before ML-KEM source acceptance.

This evidence record defines the per-file standards-trace gate for future ML-KEM implementation files. It binds each future source or test file to FIPS 203 clauses, SP 800-227 usage obligations, digest rows, clean-room author attestation, review disposition, reviewer role mapping, and CI promotion evidence. It does not create source files, record real trace rows, approve coverage, accept source, execute ML-KEM operations, emit shared secrets, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
per_file_standards_trace_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Per-File Standards Trace Gate
standards_trace_profile=latticra-q-seal-ml-kem-per-file-standards-trace-gate/0.1
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF
source_boundary=clean-room-no-apple-code
trace_scope=ML-KEM-per-file-FIPS-203-SP-800-227-trace-before-source-acceptance
trace_state=standards-trace-template-recorded-trace-rows-blocked
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
implementation_traceability_matrix_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
primitive_source_acceptance_gate_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
fips203_clause_columns_recorded=1
sp800_227_usage_columns_recorded=1
parameter_set_columns_recorded=1
operation_family_columns_recorded=1
acceptance_blocker_columns_recorded=1
review_disposition_columns_recorded=1
source_files_created=0
per_file_standards_trace_rows_recorded=0
fips203_clause_coverage_reviewed=0
sp800_227_usage_coverage_reviewed=0
parameter_set_coverage_reviewed=0
trace_review_approved=0
per_file_standards_trace_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_standards_trace_items_total=31
required_standards_trace_items_satisfied=24
status=ml-kem-per-file-standards-trace-gate-blocked
```

## Acceptance Blockers

```text
source_files_created=0
per_file_standards_trace_rows_recorded=0
fips203_clause_coverage_reviewed=0
sp800_227_usage_coverage_reviewed=0
parameter_set_coverage_reviewed=0
trace_review_approved=0
per_file_standards_trace_accepted=0
```

## Non-Claims

This gate is not a standards conformance claim, not a real implementation trace, not source approval, not KAT or ACVP evidence, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
