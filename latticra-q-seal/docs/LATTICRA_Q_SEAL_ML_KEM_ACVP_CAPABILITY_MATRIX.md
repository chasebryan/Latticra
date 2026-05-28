# Latticra Q-Seal ML-KEM ACVP Capability Matrix

Status: ACVP capability matrix
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md` for the Q-Seal documentation set. The capability matrix records the ML-KEM ACVP modes, parameter sets, functions, test types, response schemas, and review blockers that must be satisfied before fixture digest rows can be planned. The downstream fixture row plan is recorded in `LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_capability_matrix.h
latticra-q-seal/src/q_seal_ml_kem_acvp_capability_matrix.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_capability_matrix_invariants.c
latticra-q-seal/evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
```

## Current Fields

```text
ml_kem_acvp_capability_matrix_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Capability Matrix
matrix_profile=latticra-q-seal-ml-kem-acvp-capability-matrix/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
matrix_scope=ML-KEM-ACVP-capability-coverage-before-fixture-row-planning
matrix_state=capability-matrix-recorded-review-missing
acvp_capability_matrix_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
algorithm_ml_kem_recorded=1
revision_fips203_recorded=1
keygen_mode_required=1
encap_decap_mode_required=1
ml_kem_512_parameter_set_required=1
ml_kem_768_parameter_set_required=1
ml_kem_1024_parameter_set_required=1
keygen_aft_required=1
encap_decap_aft_required=1
decapsulation_val_required=1
encapsulation_function_required=1
decapsulation_function_required=1
encapsulation_key_check_required=1
decapsulation_key_check_required=1
response_schema_keygen_bound=1
response_schema_encap_decap_bound=1
capability_exchange_policy_recorded=1
prereq_sha_validation_policy_recorded=1
vector_source_intake_bound=1
vector_fixture_digest_ledger_bound=1
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
acvp_registration_json_reviewed=0
capability_matrix_reviewed=0
keygen_parameter_coverage_reviewed=0
encap_decap_parameter_coverage_reviewed=0
function_coverage_reviewed=0
response_schema_reviewed=0
fixture_row_generation_allowed=0
vector_json_loaded=0
response_json_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_capability_items_total=30
required_capability_items_satisfied=24
status=ml-kem-acvp-capability-matrix-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
```

Expected output:

```text
latticra q-seal ml-kem acvp capability matrix invariants: ok
latticra q-seal ml-kem acvp capability matrix: ok
latticra q-seal ml-kem acvp fixture row plan invariants: ok
latticra q-seal ml-kem acvp fixture row plan: ok
```
