# Latticra Q-Seal ML-KEM ACVP Response Fixture

Status: ACVP response fixture
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md` for the Q-Seal documentation set. The fixture records the fail-closed response-output families required before ACVP response evidence can be accepted.

The current slice is a fixture contract only. It does not accept parser output, execute vectors, generate ACVP response JSON, submit ACVP material, execute ML-KEM, or claim production cryptography readiness.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_response_fixture.h
latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_response_fixture_invariants.c
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_KAT_RESULT_ROW_FIXTURE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
```

## Current Fields

```text
ml_kem_acvp_response_fixture_present=1
acvp_response_fixture_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Response Fixture
response_fixture_profile=latticra-q-seal-ml-kem-acvp-response-fixture/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
response_fixture_scope=ML-KEM-ACVP-response-fixture-before-response-output-acceptance
response_fixture_state=acvp-response-fixture-recorded-response-output-missing
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
vector_schema_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
response_fixture_policy_recorded=1
response_envelope_policy_recorded=1
acv_version_echo_required=1
vsid_echo_required=1
tgid_tcid_mapping_required=1
deterministic_ordering_required=1
keygen_response_fixture_required=1
encapsulation_response_fixture_required=1
decapsulation_response_fixture_required=1
key_check_response_fixture_required=1
canonical_hex_output_required=1
boolean_output_policy_recorded=1
no_secret_material_logging_required=1
no_network_submission_required=1
no_dynamic_code_loading_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
response_fixture_reviewed=0
fixture_bundle_digest_bound=0
parser_output_accepted=0
vector_execution_evidence_recorded=0
keygen_response_fixture_recorded=0
encapsulation_response_fixture_recorded=0
decapsulation_response_fixture_recorded=0
key_check_response_fixture_recorded=0
negative_response_fixture_recorded=0
response_schema_reviewed=0
response_security_reviewed=0
response_ci_replay_recorded=0
response_output_accepted=0
acvp_response_generation_evidence_recorded=0
response_json_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_response_fixture_items_total=46
required_response_fixture_items_satisfied=32
status=ml-kem-acvp-response-fixture-blocked
```

## Promotion Blockers

All zero-valued review, digest, parser-output, vector-execution, response-family, security-review, CI-replay, output-acceptance, response-generation, submission, operation, production, FIPS, and runtime-authority fields must remain zero until audited evidence exists.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
```

Expected output:

```text
latticra q-seal ml-kem acvp response fixture invariants: ok
latticra q-seal ml-kem acvp response fixture: ok
```
