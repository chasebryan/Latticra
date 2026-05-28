# Latticra Q-Seal ML-KEM ACVP Fixture Row Plan

Status: ACVP fixture row plan
Date: 2026-05-27
Scope: ML-KEM ACVP fixture row classes before digest-ledger row acceptance.

This row plan records the minimum local fixture row classes that future ML-KEM ACVP/KAT fixture evidence must cover before Q-Seal accepts digest-ledger rows. The downstream digest row template is recorded in `latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md`. It is anchored to FIPS 203 and the NIST ACVP ML-KEM JSON schema. It does not fetch vectors, embed vectors, load vector JSON, generate response JSON, execute ML-KEM, submit ACVP results, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
ml_kem_acvp_fixture_row_plan_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Fixture Row Plan
row_plan_profile=latticra-q-seal-ml-kem-acvp-fixture-row-plan/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
row_plan_scope=ML-KEM-ACVP-fixture-row-classes-before-digest-ledger-acceptance
row_plan_state=fixture-row-plan-recorded-digest-rows-missing
acvp_fixture_row_plan_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_digest_row_template_bound=1
vector_fixture_digest_ledger_bound=1
top_level_vector_set_fields_recorded=1
test_group_fields_recorded=1
test_case_fields_recorded=1
response_group_fields_recorded=1
response_case_fields_recorded=1
parameter_set_rows_total=3
parameter_set_rows_planned=3
keygen_aft_rows_required=3
keygen_aft_rows_planned=3
encapsulation_aft_rows_required=3
encapsulation_aft_rows_planned=3
decapsulation_val_rows_required=3
decapsulation_val_rows_planned=3
encapsulation_key_check_val_rows_required=3
encapsulation_key_check_val_rows_planned=3
decapsulation_key_check_val_rows_required=3
decapsulation_key_check_val_rows_planned=3
minimum_fixture_row_classes_required=15
minimum_fixture_row_classes_planned=15
fixture_row_ids_reserved=1
digest_columns_required=1
source_url_columns_required=1
license_review_columns_required=1
schema_crosscheck_columns_required=1
review_columns_required=1
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
acvp_registration_json_reviewed=0
capability_matrix_reviewed=0
fixture_row_plan_reviewed=0
fixture_digest_rows_recorded=0
fixture_source_digests_recorded=0
fixture_storage_paths_recorded=0
fixture_license_review_recorded=0
fixture_schema_crosscheck_recorded=0
fixture_import_reviewed=0
fixture_digest_ledger_reviewed=0
row_plan_to_digest_ledger_reviewed=0
fixture_bundle_loaded=0
vector_execution_allowed=0
response_json_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_fixture_row_plan_items_total=36
required_fixture_row_plan_items_satisfied=25
status=ml-kem-acvp-fixture-row-plan-blocked
```

## Planned Fixture Row Classes

```text
parameter_sets=ML-KEM-512,ML-KEM-768,ML-KEM-1024
vector_set_fields=acvVersion,vsId,algorithm,mode,revision,testGroups
test_group_fields=tgId,testType,parameterSet,function,tests
test_case_fields=tcId,d,z,dk,ek,m,c
response_group_fields=tgId,tests
response_case_fields=tcId,ek,dk,c,k,testPassed
row_class=keyGen.AFT parameter_sets=3
row_class=encapDecap.AFT.encapsulation parameter_sets=3
row_class=encapDecap.VAL.decapsulation parameter_sets=3
row_class=encapDecap.VAL.encapsulationKeyCheck parameter_sets=3
row_class=encapDecap.VAL.decapsulationKeyCheck parameter_sets=3
minimum_fixture_row_classes=15
```

## Promotion Blockers

```text
acvp_registration_json_reviewed=0
capability_matrix_reviewed=0
fixture_row_plan_reviewed=0
fixture_digest_rows_recorded=0
fixture_source_digests_recorded=0
fixture_storage_paths_recorded=0
fixture_license_review_recorded=0
fixture_schema_crosscheck_recorded=0
fixture_import_reviewed=0
fixture_digest_ledger_reviewed=0
row_plan_to_digest_ledger_reviewed=0
```

## Non-Claims

This row plan is not an ACVP client, not an ACVP session, not vector JSON, not response JSON, not known-answer test execution, not primitive code, not generated source, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
