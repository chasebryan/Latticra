# Latticra Q-Seal ML-KEM ACVP Verdict Receipt Gate

This slice adds the fail-closed ACVP validation-server verdict receipt gate for Latticra Q-Seal ML-KEM. It sits after the submission package and replay transcript work, and before any local acceptance of ACVP verdict evidence or validation-related claims.

It records the offline evidence Q-Seal will require for validation-server verdict receipts: session identity, `vsId`/`tgId`/`tcId` verdict mapping, algorithm revision, parameter and operation verdicts, server response digests, receipt hashes, certificate or validation record identifiers, reviewer disposition, and explicit acceptance. It does not open a network session, submit to ACVP, execute ML-KEM, claim production cryptography, claim FIPS validation, or grant runtime authority.

```text
acvp_verdict_receipt_gate_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Verdict Receipt Gate
verdict_receipt_profile=latticra-q-seal-ml-kem-acvp-verdict-receipt-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
verdict_receipt_scope=ML-KEM-ACVP-validation-server-verdicts-before-validation-claims
verdict_receipt_state=acvp-verdict-receipt-gate-recorded-verdict-missing
fips_203_algorithm_bound=1
acvp_ml_kem_protocol_bound=1
acvp_submission_package_contract_bound=1
replay_transcript_gate_bound=1
acvp_response_contract_bound=1
acvp_response_fixture_bound=1
acvp_parser_contract_bound=1
acvp_capability_matrix_bound=1
vector_fixture_digest_ledger_bound=1
implementation_binding_manifest_bound=1
review_disposition_ledger_bound=1
reviewer_identity_fixture_bound=1
reviewer_role_mapping_bound=1
clean_room_source_boundary_recorded=1
offline_verdict_receipt_policy_recorded=1
validation_server_receipt_required=1
acvp_session_identifier_required=1
vsid_tgid_tcid_verdict_mapping_required=1
algorithm_revision_required=1
parameter_set_verdicts_required=1
operation_verdicts_required=1
pass_fail_verdict_required=1
server_response_digest_required=1
receipt_digest_sha256_required=1
certificate_or_validation_record_required=1
validation_date_required=1
lab_or_server_identity_required=1
no_secret_material_logging_required=1
offline_only_intake_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
submission_receipt_bound=0
validation_server_acceptance_bound=0
pass_verdict_recorded=0
certificate_identifier_recorded=0
receipt_digest_verified=0
reviewer_disposition_recorded=0
acvp_verdict_receipt_accepted=0
network_session_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_verdict_receipt_items_total=39
required_verdict_receipt_items_satisfied=32
status=ml-kem-acvp-verdict-receipt-gate-blocked
```

## Guardrail

This gate lets Q-Seal model ACVP verdict receipt acceptance without pretending that local fixtures are validation-server proof. Even when this gate is eventually satisfied, it only accepts the receipt evidence; public validation wording, FIPS wording, migration claims, runtime operations, production claims, network sessions, and submission authority remain disabled unless separate gates, including `LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_GATE.md`, grant them.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
```
