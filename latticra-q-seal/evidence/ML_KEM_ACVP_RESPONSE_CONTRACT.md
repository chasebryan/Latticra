# Latticra Q-Seal ML-KEM ACVP Response Contract

Status: ACVP response contract
Date: 2026-05-27
Scope: fail-closed ML-KEM ACVP JSON response contract before response generation, submission, or operation execution.

This contract records the response-generation guardrails that future ML-KEM ACVP/KAT replay must satisfy before Q-Seal can emit response JSON. It is anchored to FIPS 203 and the NIST ACVP ML-KEM JSON response shape for keyGen and encapDecap. It binds the intake, capability matrix, fixture row plan, digest row template, parser contract, ACVP response fixture, vector schema, vector source intake, digest ledger, negative-test evidence, and implementation-binding manifest. It does not implement a response generator, accept parser output, execute vectors, generate response JSON, submit ACVP results, execute ML-KEM, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

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

## Response Guardrails

```text
response_envelope=acvVersion,vsId,testGroups,tgId,tests
keygen.response_fields=tcId,ek,dk
encapDecap.response_fields=tcId,c,k,testPassed
field_policy=known-fields-only
mapping_policy=tcId-and-tgId-preserved-from-accepted-parser-output
ordering_policy=deterministic
hex_policy=canonical-even-length-uppercase
boolean_policy=testPassed-only-for-key-check-functions
side_effects=none
network_submission_enabled=0
response_json_generation_enabled=0
```

## Promotion Blockers

```text
response_generator_implementation_present=0
response_negative_tests_recorded=0
response_schema_reviewed=0
response_security_reviewed=0
response_ci_replay_recorded=0
parser_output_accepted=0
vector_execution_evidence_recorded=0
response_json_generation_enabled=0
response_output_accepted=0
```

## Non-Claims

This contract is not a response generator implementation, not vector execution, not ACVP response JSON, not ACVP submission, not known-answer test execution, not primitive code, not generated source, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
