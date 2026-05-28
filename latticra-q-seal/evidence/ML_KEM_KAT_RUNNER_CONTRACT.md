# Latticra Q-Seal ML-KEM KAT Runner Contract Evidence

Status: fail-closed KAT runner contract
Date: 2026-05-27

This evidence record defines the guardrails for a future ML-KEM known-answer test runner before any fixture replay, vector execution, ACVP response generation, or runtime cryptographic operation is allowed. It is intentionally a contract only: it does not embed vectors, load fixtures, execute ML-KEM, submit ACVP material, or grant production cryptography authority.

The contract is backed by `latticra_q_seal_ml_kem_kat_runner_contract_prepare`.

## Current Fields

```text
ml_kem_kat_runner_contract_present=1
kat_runner_contract_present=1
formal_title=Latticra Q-Seal ML-KEM KAT Runner Contract
runner_profile=latticra-q-seal-ml-kem-kat-runner-contract/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
runner_scope=ML-KEM-known-answer-runner-contract-before-vector-replay
runner_state=kat-runner-contract-recorded-runner-implementation-missing
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
kat_manifest_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
vector_schema_bound=1
vector_source_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
provider_differential_bound=1
replay_transcript_gate_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
deterministic_replay_policy_recorded=1
offline_fixture_policy_recorded=1
no_network_execution_required=1
no_dynamic_provider_loading_required=1
seed_material_handling_policy_recorded=1
positive_result_row_policy_recorded=1
negative_result_row_policy_recorded=1
malformed_result_row_policy_recorded=1
implicit_rejection_result_policy_recorded=1
parameter_set_coverage_required=1
operation_family_coverage_required=1
transcript_retention_policy_recorded=1
failure_triage_policy_recorded=1
no_embedded_vectors_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
kat_runner_implementation_present=0
fixture_bundle_loaded=0
fixture_bundle_digest_verified=0
fixture_bundle_license_reviewed=0
fixture_bundle_storage_reviewed=0
parser_reviewed_for_runner=0
result_schema_reviewed=0
positive_result_rows_recorded=0
negative_result_rows_recorded=0
malformed_result_rows_recorded=0
implicit_rejection_rows_recorded=0
provider_differential_rows_recorded=0
ci_kat_replay_transcript_recorded=0
operation_implementation_present=0
kat_execution_enabled=0
acvp_response_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_runner_contract_items_total=47
required_kat_runner_contract_items_satisfied=31
status=ml-kem-kat-runner-contract-blocked
```

## Required Runner Evidence

The future runner cannot be enabled until the following are reviewed and recorded:

- Clean-room runner implementation and operation implementation.
- Offline fixture bundle load path, SHA-256 digest verification, license review, and storage review.
- ACVP parser review and KAT result schema review.
- Positive, negative, malformed-input, implicit-rejection, and provider-differential result rows.
- CI KAT replay transcript tied to the locked fixture bundle.
- Explicit runtime authority before any operation execution.

## Non-Claims

This evidence does not claim FIPS validation, ACVP acceptance, production cryptography readiness, Apple corecrypto reuse, external provider reuse, KAT passage, or runtime operation authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
```
