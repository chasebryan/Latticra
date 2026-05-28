# Latticra Q-Seal ML-KEM ACVP Submission Package Contract

This slice adds the fail-closed ACVP submission-package contract for Latticra Q-Seal ML-KEM. It sits after the response fixture and before any local package acceptance or future ACVP client/session work.

It records the offline evidence Q-Seal will require for a reviewed submission package: request and response bundle digests, ACVP session metadata, `vsId`/`tgId`/`tcId` traceability, canonical response JSON, local replay transcript, client-boundary review, submission receipt, and validation-server acceptance. It does not generate response JSON, open a network session, submit to ACVP, execute ML-KEM, or grant runtime authority.

```text
acvp_submission_package_contract_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Submission Package Contract
submission_package_profile=latticra-q-seal-ml-kem-acvp-submission-package-contract/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
submission_package_scope=ML-KEM-ACVP-submission-package-before-network-submission
submission_package_state=acvp-submission-package-contract-recorded-package-acceptance-missing
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
acvp_response_fixture_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
vector_schema_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
submission_package_policy_recorded=1
offline_package_manifest_required=1
algorithm_registration_required=1
acvp_session_metadata_required=1
vsid_tgid_tcid_traceability_required=1
request_bundle_digest_required=1
response_bundle_digest_required=1
canonical_response_json_required=1
local_replay_transcript_required=1
no_secret_material_logging_required=1
no_network_submission_required=1
no_dynamic_code_loading_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
submission_package_reviewed=0
request_bundle_digest_bound=0
response_bundle_digest_bound=0
vector_execution_evidence_recorded=0
response_output_accepted=0
local_replay_transcript_recorded=0
acvp_client_boundary_reviewed=0
submission_receipt_recorded=0
validation_server_acceptance_recorded=0
acvp_submission_package_accepted=0
acvp_response_acceptance_recorded=0
response_json_generation_enabled=0
network_session_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_submission_package_items_total=41
required_submission_package_items_satisfied=30
status=ml-kem-acvp-submission-package-contract-blocked
```

## Guardrail

This contract keeps ACVP submission disabled until reviewed offline evidence exists. Network submission is also a separate authority boundary; satisfying this contract alone must not open a network session, FIPS claim, production cryptography claim, or runtime operation path.

Validation-server verdict receipts are gated separately by `LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md`; a reviewed package is not the same thing as an accepted ACVP verdict.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
```
