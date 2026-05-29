# Latticra Q-Seal ML-KEM Primitive Source Acceptance Gate Evidence

Status: fail-closed primitive source acceptance gate

Scope: clean-room ML-KEM primitive source acceptance before runtime cryptography, shared-secret emission, production claims, or FIPS claims.

This evidence record defines the gate that future clean-room ML-KEM primitive source files must satisfy before they can be accepted as implementation code. It binds the implementation traceability matrix, FIPS 203 conformance matrix, SP 800-227 usage profile, KAT and ACVP contracts, source-digest evidence, code-owner review, and CI promotion evidence. It does not create source files, copy Apple corecrypto, copy external provider code, execute ML-KEM operations, emit shared secrets, generate ACVP responses, submit ACVP material, claim production cryptography, claim FIPS validation, or grant runtime authority.

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

## Source Acceptance Requirements

```text
source_layout=polynomial_arithmetic,ntt,sampling,compression,encoding,hash_xof,keygen,encapsulation,decapsulation
acceptance_requires=clean_room_author_attestation
acceptance_requires=source_file_digest_rows
acceptance_requires=per_file_fips_203_trace
acceptance_requires=per_file_sp800_227_usage_trace
acceptance_requires=per_file_kat_acvp_trace
acceptance_requires=constant_time_review_mapping
acceptance_requires=memory_safety_and_zeroization_mapping
acceptance_requires=code_owner_review_and_review_disposition
acceptance_allows_runtime_crypto=0
acceptance_allows_shared_secret_emission=0
```

This gate is not primitive code, not a source digest receipt, not a source replay result, not KAT passage, not ACVP validation, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
