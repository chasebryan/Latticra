# Latticra Q-Seal ML-KEM Primitive Source Acceptance Gate

Latticra Q-Seal records a primitive source acceptance gate before future clean-room ML-KEM source files can be treated as implementation candidates. The gate binds source layout, traceability, standards evidence, source-digest evidence, review evidence, and CI promotion evidence while keeping ML-KEM operations, shared-secret emission, production claims, FIPS claims, and runtime authority disabled.

```text
acceptance_profile=latticra-q-seal-ml-kem-primitive-source-acceptance-gate/0.1
formal_title=Latticra Q-Seal ML-KEM Primitive Source Acceptance Gate
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM
source_boundary=clean-room-no-apple-code
acceptance_scope=ML-KEM-primitive-source-acceptance-before-runtime-crypto
acceptance_state=source-acceptance-blocked-runtime-crypto-blocked
primitive_source_acceptance_gate_present=1
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
source_layout_bound=1
source_layout_gate_bound=1
implementation_traceability_matrix_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
kat_manifest_bound=1
acvp_contracts_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
per_file_test_trace_gate_bound=1
receipt_replay_results_bound=1
constant_time_review_bound=1
memory_safety_evidence_bound=1
zeroization_evidence_bound=1
randomness_source_bound=1
negative_test_evidence_bound=1
api_misuse_resistance_bound=1
side_channel_review_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
source_files_created=0
implementation_code_present=0
source_file_digest_rows_recorded=0
clean_room_author_attestation_recorded=0
per_file_standards_trace_recorded=0
per_file_test_trace_recorded=0
per_file_review_approval_recorded=0
source_acceptance_approved=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_acceptance_items_total=38
required_acceptance_items_satisfied=30
blocked_reason=source-files-digests-clean-room-attestation-per-file-trace-review-and-approval-missing
error=blocked
status=ml-kem-source-acceptance-gate-blocked
```

## Acceptance Boundary

Before source acceptance can be approved, Q-Seal must record real source files, digest rows for those files, clean-room author attestation, per-file standards trace, per-file test trace, and per-file review approval. Even after this gate is satisfied, runtime cryptography remains blocked until the full readiness profile has no blockers and all cryptographic evidence is complete.
