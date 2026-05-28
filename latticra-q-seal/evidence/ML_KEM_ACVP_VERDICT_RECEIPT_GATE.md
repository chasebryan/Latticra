# Latticra Q-Seal ML-KEM ACVP Verdict Receipt Gate

Status: ACVP validation-server verdict receipt gate
Scope: fail-closed ML-KEM ACVP verdict evidence before local verdict acceptance, validation claims, production claims, or operation execution.

This gate records the evidence Q-Seal must require after an ACVP submission package has been prepared and replayed. It separates local KAT/ACVP replay from validation-server verdict evidence so Latticra cannot imply that ML-KEM has passed ACVP, received a certificate, or earned a FIPS-related claim from local fixtures alone. It does not open an ACVP network session, submit results, execute ML-KEM, import Apple or external provider code, claim FIPS validation, claim production cryptography, or grant runtime authority.

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

## Required Evidence

Before Q-Seal can accept ACVP verdict evidence locally, it must record:

- ACVP session identity and `vsId`/`tgId`/`tcId` mapping from submitted response rows to returned verdict rows;
- ML-KEM algorithm revision, parameter-set verdicts, operation verdicts, and pass/fail verdict text;
- validation-server receipt or equivalent server-signed/digested response evidence;
- SHA-256 digest of the receipt artifact and the server response digest used for replay;
- certificate identifier or validation record when one exists, plus validation date and lab/server identity;
- reviewer disposition that binds the receipt to the reviewed submission package and replay transcripts.

Satisfying this gate accepts only the verdict receipt evidence. Public validation wording, FIPS wording, migration claims, runtime cryptography, production claims, network sessions, and ACVP submissions remain governed by separate authority gates, including `ML_KEM_VALIDATION_CLAIM_GATE.md`.

## Non-Claims

This gate is not an ACVP client, not a network session, not an ACVP submission, not KAT execution, not primitive code, not generated source, not FIPS validation, not production cryptography, not provider linking, not host mutation, and not runtime authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
```
