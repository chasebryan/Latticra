# Latticra Q-Seal ML-KEM ACVP Parser Contract

Status: ACVP parser contract
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_ACVP_PARSER_CONTRACT.md` for the Q-Seal documentation set. The parser contract records the fail-closed JSON parsing guardrails that must be satisfied before future ML-KEM ACVP/KAT vector bundles can be imported, replayed, or used to generate response JSON.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_parser_contract.h
latticra-q-seal/src/q_seal_ml_kem_acvp_parser_contract.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_parser_contract_invariants.c
latticra-q-seal/evidence/ML_KEM_ACVP_PARSER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
```

## Current Fields

```text
ml_kem_acvp_parser_contract_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Parser Contract
parser_profile=latticra-q-seal-ml-kem-acvp-parser-contract/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
parser_scope=ML-KEM-ACVP-JSON-parser-contract-before-vector-import
parser_state=parser-contract-recorded-parser-implementation-missing
acvp_parser_contract_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
vector_set_fields_policy_recorded=1
test_group_fields_policy_recorded=1
test_case_fields_policy_recorded=1
response_fields_policy_recorded=1
parameter_set_allowlist_required=1
mode_allowlist_required=1
test_type_allowlist_required=1
function_allowlist_required=1
hex_string_decoder_policy_recorded=1
integer_range_policy_recorded=1
max_input_size_policy_recorded=1
max_nesting_depth_policy_recorded=1
duplicate_key_rejection_required=1
unknown_field_rejection_policy_recorded=1
malformed_json_rejection_required=1
canonical_output_mapping_required=1
no_dynamic_code_loading_required=1
no_network_fetch_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
parser_implementation_present=0
parser_negative_tests_recorded=0
parser_fuzzing_recorded=0
parser_schema_reviewed=0
parser_security_reviewed=0
parser_ci_replay_recorded=0
fixture_digest_rows_recorded=0
fixture_import_reviewed=0
parser_output_accepted=0
vector_execution_allowed=0
response_json_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_parser_contract_items_total=40
required_parser_contract_items_satisfied=31
status=ml-kem-acvp-parser-contract-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
```

Expected output:

```text
latticra q-seal ml-kem acvp parser contract invariants: ok
latticra q-seal ml-kem acvp parser contract: ok
```
