# Latticra Q-Seal ML-KEM ACVP Parser Contract

Status: ACVP parser contract
Date: 2026-05-27
Scope: fail-closed ML-KEM ACVP JSON parser contract before any vector import, response generation, or operation execution.

This contract records the parser guardrails that future ML-KEM ACVP/KAT vector ingestion must satisfy. It is anchored to FIPS 203 and the NIST ACVP ML-KEM JSON work-in-progress shape, and it binds the intake, capability matrix, fixture row plan, digest row template, vector schema, vector source intake, digest ledger, negative-test evidence, and implementation-binding manifest. It does not implement a parser, parse vector JSON, accept parser output, import fixtures, generate response JSON, execute ML-KEM, submit ACVP results, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

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

## Parser Guardrails

```text
field_policy=acvVersion,vsId,algorithm,mode,revision,testGroups,tgId,testType,parameterSet,function,tests,tcId
allowlists=parameterSet,mode,testType,function
reject=malformed-json,duplicate-keys,unknown-fields,overlarge-input,excessive-depth,invalid-integer-range,invalid-hex-string
side_effects=none
network_fetch_enabled=0
dynamic_code_loading_enabled=0
parser_output_accepted=0
```

## Promotion Blockers

```text
parser_implementation_present=0
parser_negative_tests_recorded=0
parser_fuzzing_recorded=0
parser_schema_reviewed=0
parser_security_reviewed=0
parser_ci_replay_recorded=0
fixture_digest_rows_recorded=0
fixture_import_reviewed=0
parser_output_accepted=0
```

## Non-Claims

This contract is not a parser implementation, not vector JSON, not fixture import, not ACVP response generation, not ACVP submission, not known-answer test execution, not primitive code, not generated source, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
