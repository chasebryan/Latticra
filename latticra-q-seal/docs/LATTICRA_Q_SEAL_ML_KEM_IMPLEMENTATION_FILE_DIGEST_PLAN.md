# Latticra Q-Seal ML-KEM Implementation File Digest Plan

Status: fail-closed implementation-file digest row plan
Date: 2026-05-27
Scope: per-file digest-row schema before clean-room ML-KEM primitive source acceptance.

This slice records the row schema and evidence bindings future clean-room ML-KEM implementation files must satisfy before their file digests can be accepted. It does not create implementation source, record live primitive digests, accept digest rows, approve source, execute ML-KEM operations, emit shared secrets, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_file_digest_plan.h
latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_file_digest_plan_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
```

## Current Fields

```text
ml_kem_implementation_file_digest_plan_present=1
formal_title=Latticra Q-Seal ML-KEM Implementation File Digest Plan
digest_plan_profile=latticra-q-seal-ml-kem-implementation-file-digest-plan/0.1
standards_basis=NIST-SP-800-218-SSDF,NIST-FIPS-203,NIST-ACVP-ML-KEM
digest_algorithm=SHA-256
source_boundary=clean-room-no-apple-code
digest_plan_scope=ML-KEM-implementation-file-digest-row-plan-before-source-acceptance
digest_plan_state=file-digest-plan-recorded-digest-rows-blocked
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
digest_algorithm_sha256_recorded=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
receipt_replay_results_bound=1
implementation_binding_manifest_bound=1
implementation_traceability_matrix_bound=1
primitive_source_acceptance_gate_bound=1
source_layout_gate_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
kat_manifest_bound=1
acvp_contracts_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
per_file_digest_row_schema_recorded=1
per_file_trace_columns_recorded=1
per_file_review_columns_recorded=1
source_files_created=0
implementation_file_digest_rows_recorded=0
test_file_digest_rows_recorded=0
build_script_digest_rows_recorded=0
digest_receipt_reviewed=0
digest_replay_verified=0
file_digest_plan_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_digest_plan_items_total=33
required_digest_plan_items_satisfied=26
blocked_reason=source-files-implementation-test-build-digest-rows-reviewed-receipts-replay-and-plan-acceptance-missing
status=ml-kem-implementation-file-digest-plan-blocked
```

## Row Schema

```text
row_id
normalized_repo_path
file_role
ml_kem_operation_family
parameter_set_scope
fips_203_clause_trace
sp800_227_usage_trace
kat_trace_id
acvp_trace_id
sha256_digest
digest_command_profile
source_author_attestation_id
review_disposition_id
code_owner_review_id
ci_replay_receipt_id
acceptance_status
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
```

Expected output:

```text
latticra q-seal ml-kem implementation file digest plan invariants: ok
latticra q-seal ml-kem implementation file digest plan: ok
```
