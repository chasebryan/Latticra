# Latticra Q-Seal ML-KEM Per-File Standards Trace Gate

Status: fail-closed per-file standards trace slice
Date: 2026-05-27
Scope: per-file FIPS 203 and SP 800-227 trace schema before ML-KEM source acceptance.

This slice records the standards-trace schema that future clean-room ML-KEM implementation files must satisfy before source acceptance can treat those files as implementation candidates. It binds FIPS 203, SP 800-227, SSDF provenance posture, implementation traceability, file-digest planning, clean-room author attestation, source-digest evidence, code-owner review, review disposition, reviewer role mapping, and CI promotion evidence. It does not create source files, record per-file standards rows, approve trace coverage, accept source, execute ML-KEM operations, emit shared secrets, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_per_file_standards_trace_gate.h
latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c
latticra-q-seal/tests/q_seal_ml_kem_per_file_standards_trace_gate_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
latticra-q-seal/evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
```

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
blocked_reason=source-files-per-file-standards-trace-rows-coverage-review-and-trace-acceptance-missing
status=ml-kem-per-file-standards-trace-gate-blocked
```

## Trace Schema

```text
trace_id
normalized_repo_path
file_role
ml_kem_parameter_set
operation_family
fips_203_clause_reference
sp800_227_usage_reference
trace_requirement_summary
digest_row_reference
author_attestation_reference
review_disposition_id
trace_status
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
```

Expected output:

```text
latticra q-seal ml-kem per-file standards trace gate invariants: ok
latticra q-seal ml-kem per-file standards trace gate: ok
```
