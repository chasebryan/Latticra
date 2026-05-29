# Latticra Q-Seal ML-KEM ACVP Capability Matrix

Status: ACVP capability matrix
Date: 2026-05-27
Scope: ML-KEM ACVP mode, parameter-set, function, and response-schema coverage before fixture digest row planning.

This matrix records the ACVP capability coverage that future local ML-KEM fixture rows must satisfy before Q-Seal accepts digest-ledger rows. The downstream fixture row plan is recorded in `latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md`. It is anchored to FIPS 203 and the NIST ACVP ML-KEM JSON schema. It does not open an ACVP session, load vector JSON, generate response JSON, execute ML-KEM, submit ACVP results, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

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

## Required Capability Rows

```text
algorithm=ML-KEM
revision=FIPS203
mode=keyGen parameter_sets=ML-KEM-512,ML-KEM-768,ML-KEM-1024 test_type=AFT
mode=encapDecap parameter_sets=ML-KEM-512,ML-KEM-768,ML-KEM-1024 test_types=AFT,VAL
encapDecap.functions=encapsulation,decapsulation,encapsulationKeyCheck,decapsulationKeyCheck
response_schema.keyGen=tcId,ek,dk
response_schema.encapDecap=tcId,c,k,testPassed
```

## Promotion Blockers

```text
acvp_registration_json_reviewed=0
capability_matrix_reviewed=0
keygen_parameter_coverage_reviewed=0
encap_decap_parameter_coverage_reviewed=0
function_coverage_reviewed=0
response_schema_reviewed=0
fixture_row_generation_allowed=0
```

## Non-Claims

This matrix is not an ACVP client, not an ACVP session, not vector JSON, not response JSON, not known-answer test execution, not primitive code, not generated source, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
