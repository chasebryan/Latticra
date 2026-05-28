# Latticra Q-Seal ML-KEM KAT Result Row Fixture Evidence

Status: fail-closed KAT result row fixture
Date: 2026-05-27

This evidence record defines the row-family fixture required before future ML-KEM known-answer replay can record reviewed result rows. It is a fixture contract only: it does not load fixture bundles, execute vectors, record positive or negative rows, emit ACVP responses, submit ACVP material, or grant runtime cryptography authority.

The fixture is backed by `latticra_q_seal_ml_kem_kat_result_row_fixture_prepare`.

## Current Fields

```text
ml_kem_kat_result_row_fixture_present=1
kat_result_row_fixture_present=1
formal_title=Latticra Q-Seal ML-KEM KAT Result Row Fixture
row_fixture_profile=latticra-q-seal-ml-kem-kat-result-row-fixture/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
row_fixture_scope=ML-KEM-known-answer-result-row-fixture-before-result-recording
row_fixture_state=kat-result-row-fixture-recorded-result-rows-missing
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
kat_manifest_bound=1
kat_runner_contract_bound=1
kat_result_schema_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
vector_schema_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
provider_differential_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
result_row_fixture_policy_recorded=1
row_id_policy_recorded=1
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
implicit_rejection_row_policy_recorded=1
provider_differential_row_policy_recorded=1
transcript_digest_reference_required=1
no_secret_material_logging_required=1
deterministic_ordering_required=1
no_network_submission_required=1
no_dynamic_provider_loading_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
row_fixture_reviewed=0
fixture_bundle_digest_bound=0
positive_result_row_fixture_recorded=0
negative_result_row_fixture_recorded=0
malformed_result_row_fixture_recorded=0
implicit_rejection_row_fixture_recorded=0
provider_differential_row_fixture_recorded=0
ci_kat_replay_transcript_bound=0
kat_runner_execution_recorded=0
acvp_response_generation_evidence_recorded=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_result_row_fixture_items_total=44
required_kat_result_row_fixture_items_satisfied=34
status=ml-kem-kat-result-row-fixture-blocked
```

## Required Row Families

Before result rows can promote implementation evidence, the fixture must record reviewed rows for:

- positive known-answer outcomes;
- negative parser and validation outcomes;
- malformed-input outcomes;
- implicit-rejection outcomes;
- provider-differential outcomes tied to transcript digests.

## Non-Claims

This evidence does not claim KAT passage, ACVP response acceptance, FIPS validation, production cryptography readiness, Apple corecrypto reuse, external provider reuse, result-row review, fixture loading, vector execution, or runtime operation authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-result-row-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-result-row-fixture.sh
```
