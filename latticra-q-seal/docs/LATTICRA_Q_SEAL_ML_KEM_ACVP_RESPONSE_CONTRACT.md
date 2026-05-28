# Latticra Q-Seal ML-KEM ACVP Response Contract

Status: ACVP response contract
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md` for the Q-Seal documentation set. The response contract records the fail-closed response-generation guardrails that must be satisfied before future ML-KEM ACVP/KAT replay can emit keyGen or encapDecap response JSON.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_response_contract.h
latticra-q-seal/src/q_seal_ml_kem_acvp_response_contract.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_response_contract_invariants.c
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_ACVP_PARSER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
```

## Current Fields

```text
ml_kem_acvp_response_contract_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Response Contract
response_profile=latticra-q-seal-ml-kem-acvp-response-contract/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
response_scope=ML-KEM-ACVP-JSON-response-contract-before-response-generation
response_state=response-contract-recorded-response-generator-missing
acvp_response_contract_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
acvp_parser_contract_bound=1
acvp_response_fixture_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
response_envelope_policy_recorded=1
keygen_response_fields_policy_recorded=1
encapsulation_response_fields_policy_recorded=1
decapsulation_response_fields_policy_recorded=1
key_check_response_fields_policy_recorded=1
tcid_tgid_mapping_required=1
acv_version_echo_policy_recorded=1
vsid_echo_policy_recorded=1
parameter_set_crosscheck_required=1
function_crosscheck_required=1
hex_output_canonicalization_required=1
boolean_output_policy_recorded=1
deterministic_ordering_required=1
duplicate_response_rejection_required=1
unknown_response_field_rejection_required=1
response_size_limit_recorded=1
no_dynamic_code_loading_required=1
no_network_submission_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
response_generator_implementation_present=0
response_negative_tests_recorded=0
response_schema_reviewed=0
response_security_reviewed=0
response_ci_replay_recorded=0
parser_output_accepted=0
vector_execution_evidence_recorded=0
response_json_generation_enabled=0
response_output_accepted=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_response_contract_items_total=42
required_response_contract_items_satisfied=33
status=ml-kem-acvp-response-contract-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
```

Expected output:

```text
latticra q-seal ml-kem acvp response contract invariants: ok
latticra q-seal ml-kem acvp response contract: ok
```
