# Latticra Q-Seal ML-KEM KAT Result Schema

Status: KAT result schema
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md` for the Q-Seal documentation set. The result schema records the fail-closed result-row shape a future known-answer test runner must satisfy before replay outcomes can be reviewed, tied to locked fixture digests, or used as ACVP response evidence.

The current slice is a schema contract only. It does not record result rows, load fixtures, execute ML-KEM, generate ACVP responses, submit ACVP material, or claim production cryptography readiness.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_kat_result_schema.h
latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c
latticra-q-seal/tests/q_seal_ml_kem_kat_result_schema_invariants.c
latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_KAT_RUNNER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
```

## Current Fields

```text
ml_kem_kat_result_schema_present=1
kat_result_schema_present=1
formal_title=Latticra Q-Seal ML-KEM KAT Result Schema
result_schema_profile=latticra-q-seal-ml-kem-kat-result-schema/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
result_scope=ML-KEM-known-answer-result-schema-before-result-recording
schema_state=kat-result-schema-recorded-result-rows-missing
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
kat_manifest_bound=1
kat_runner_contract_bound=1
kat_result_row_fixture_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
vector_schema_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
provider_differential_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
deterministic_result_ordering_required=1
result_envelope_policy_recorded=1
fixture_digest_reference_required=1
vector_family_reference_required=1
parameter_set_field_required=1
operation_family_field_required=1
test_type_field_required=1
tgid_tcid_mapping_required=1
expected_result_field_required=1
observed_result_field_required=1
pass_fail_field_required=1
failure_reason_field_required=1
implicit_rejection_result_required=1
provider_differential_field_required=1
transcript_digest_field_required=1
no_secret_material_logging_required=1
no_network_submission_required=1
no_dynamic_provider_loading_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
result_schema_reviewed=0
fixture_bundle_digest_bound=0
result_row_fixture_recorded=0
positive_result_rows_recorded=0
negative_result_rows_recorded=0
malformed_result_rows_recorded=0
implicit_rejection_rows_recorded=0
provider_differential_rows_recorded=0
ci_kat_replay_transcript_bound=0
kat_runner_execution_recorded=0
acvp_response_generation_evidence_recorded=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_result_schema_items_total=44
required_kat_result_schema_items_satisfied=33
status=ml-kem-kat-result-schema-blocked
```

## Promotion Blockers

All zero-valued review, fixture-digest, result-row, CI transcript, runner-execution, response-evidence, submission, operation, production, FIPS, and runtime-authority fields must remain zero until audited evidence exists. The schema gives Q-Seal a typed result surface without treating schema presence as KAT passage.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
```

Expected output:

```text
latticra q-seal ml-kem kat result schema invariants: ok
latticra q-seal ml-kem kat result schema: ok
```
