# Latticra Q-Seal ML-KEM KAT Runner Contract

Status: KAT runner contract
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_KAT_RUNNER_CONTRACT.md` for the Q-Seal documentation set. The runner contract records the fail-closed requirements a future known-answer test runner must satisfy before ML-KEM fixture replay, ACVP response generation, or runtime operation authority can be considered.

The current slice is a contract only. It does not implement a runner, import vectors, execute ML-KEM, generate ACVP responses, or claim production cryptography readiness.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_kat_runner_contract.h
latticra-q-seal/src/q_seal_ml_kem_kat_runner_contract.c
latticra-q-seal/tests/q_seal_ml_kem_kat_runner_contract_invariants.c
latticra-q-seal/evidence/ML_KEM_KAT_RUNNER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_ACVP_PARSER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
```

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
required_kat_runner_contract_items_total=46
required_kat_runner_contract_items_satisfied=30
status=ml-kem-kat-runner-contract-blocked
```

## Promotion Blockers

All zero-valued runner, fixture, review, result-row, replay, response-generation, operation, submission, production, FIPS, and runtime-authority fields must remain zero until audited evidence is present. The runner contract keeps Q-Seal design-frame ready while preventing test execution from becoming a disguised production crypto claim.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
```

Expected output:

```text
latticra q-seal ml-kem kat runner contract invariants: ok
latticra q-seal ml-kem kat runner contract: ok
```
