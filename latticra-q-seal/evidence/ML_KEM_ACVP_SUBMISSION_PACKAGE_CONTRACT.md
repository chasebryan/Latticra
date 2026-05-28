# Latticra Q-Seal ML-KEM ACVP Submission Package Contract

Status: ACVP submission-package contract
Scope: fail-closed ML-KEM ACVP submission-package evidence before package acceptance, network submission, response acceptance, or operation execution.

This contract records the offline package evidence that future ML-KEM ACVP response material must satisfy before Q-Seal can accept a submission package for review. It binds the response fixture, response contract, parser contract, fixture digest ledger, KAT result schema, KAT result row fixture, negative-test evidence, implementation binding, and CI promotion evidence. It does not generate response JSON, open an ACVP client session, submit ACVP results, execute ML-KEM, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

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

## Required Promotion Evidence

Before a future ACVP submission package can be accepted locally, Q-Seal must record:

- reviewed offline package manifest tying request and response bundles to digest rows;
- algorithm-registration metadata for ML-KEM keyGen and encapDecap;
- `vsId`, `tgId`, and `tcId` traceability from request vector to response row;
- SHA-256 digests for request and response bundles;
- local replay transcript for the locked fixture bundle;
- ACVP client boundary review showing no hidden network, dynamic-code, or secret logging behavior;
- submission receipt and validation-server acceptance evidence.

Even after local package acceptance, runtime cryptography and production claims remain blocked until the broader Q-Seal readiness profile is satisfied.

The validation-server verdict receipt gate is recorded separately in `latticra-q-seal/evidence/ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md`; local package acceptance alone is not ACVP pass evidence and does not support validation, FIPS, or production-readiness claims.

## Non-Claims

This contract is not an ACVP client, not an ACVP network session, not ACVP response JSON, not a submission receipt, not validation-server acceptance, not known-answer test execution, not primitive code, not generated source, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
```
