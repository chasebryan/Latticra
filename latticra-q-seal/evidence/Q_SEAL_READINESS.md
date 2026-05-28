# Latticra Q-Seal Readiness Evidence

Status: design-frame ready; runtime cryptography blocked
Date: 2026-05-27

This evidence record aggregates the Q-Seal foundation, ML-KEM parameter packet, evidence gate, KAT manifest, KAT runner contract, KAT result schema, KAT result row fixture, ACVP intake, ACVP capability matrix, ACVP fixture row plan, ACVP fixture digest row template, ACVP parser contract, ACVP response contract, ACVP response fixture, ACVP submission-package contract, vector schema, vector source intake, vector fixture lock, vector fixture digest ledger, negative-test evidence, memory-safety evidence, API misuse-resistance evidence, source digest manifest, source digest receipt, source digest verification, receipt replay results, code-owner review, review disposition ledger, reviewer identity fixture, reviewer role mapping, CI promotion evidence, constant-time review, randomness-source contract, zeroization evidence, side-channel review, provider differential contract, implementation-binding manifest, implementation frame, and secret-state contract into one fail-closed readiness profile.

```text
q_seal_readiness_profile_present=1
readiness_profile=latticra-q-seal-readiness/0.1
formal_title=Latticra Q-Seal Readiness Profile
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
source_boundary=clean-room-no-apple-code
readiness_state=design-frame-ready-runtime-crypto-blocked
foundation_present=1
ml_kem_parameters_present=1
evidence_gate_present=1
kat_manifest_present=1
kat_runner_contract_present=1
kat_result_schema_present=1
kat_result_row_fixture_present=1
acvp_intake_present=1
acvp_capability_matrix_present=1
acvp_fixture_row_plan_present=1
acvp_fixture_digest_row_template_present=1
acvp_parser_contract_present=1
acvp_response_contract_present=1
acvp_response_fixture_present=1
acvp_submission_package_contract_present=1
vector_schema_present=1
vector_source_intake_present=1
vector_fixture_lock_present=1
vector_fixture_digest_ledger_present=1
negative_test_evidence_present=1
memory_safety_evidence_present=1
api_misuse_resistance_present=1
source_digest_manifest_present=1
source_digest_receipt_present=1
source_digest_verification_present=1
receipt_replay_results_present=1
code_owner_review_present=1
review_disposition_ledger_present=1
reviewer_identity_fixture_present=1
reviewer_role_mapping_present=1
ci_promotion_evidence_present=1
constant_time_review_present=1
randomness_source_contract_present=1
zeroization_evidence_present=1
side_channel_review_present=1
provider_differential_present=1
implementation_binding_manifest_present=1
implementation_frame_present=1
secret_state_contract_present=1
clean_room_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
provider_runtime_used=0
components_total=39
components_present=39
runtime_blockers_total=37
required_readiness_items_total=1003
required_readiness_items_satisfied=643
design_frame_integration_ready=1
runtime_crypto_ready=0
operations_enabled=0
key_generation_enabled=0
encapsulation_enabled=0
decapsulation_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
status=q-seal-readiness-profile-blocked
```

The readiness profile allows Latticra design frames to depend on Q-Seal metadata and gates, but it explicitly blocks runtime cryptography, production cryptography claims, FIPS claims, and shared-secret emission until the missing evidence is recorded and independently validated.
