# Latticra Q-Seal ML-KEM Implementation Binding Manifest

Status: fail-closed clean-room implementation-binding slice
Date: 2026-05-27
Scope: module-to-evidence bindings before ML-KEM implementation files or primitive operations.

This slice records the binding manifest that future ML-KEM implementation code must satisfy before it can be treated as an implementation candidate. It binds the FIPS 203 conformance matrix, SP 800-227 usage profile, implementation traceability matrix, and primitive source acceptance gate before KAT and ACVP intake and includes the ACVP fixture digest row template between fixture row planning and digest-ledger acceptance. It also binds the ACVP parser, response, response-fixture, and submission-package contracts before any vector execution, response-generation, or ACVP package-acceptance path can exist. It keeps primitive source creation, key generation, encapsulation, decapsulation, shared-secret emission, vector execution, response generation, provider execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_binding_manifest.h
latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_FIPS_CONFORMANCE_MATRIX.md
latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
latticra-q-seal/evidence/ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE.md
latticra-q-seal/evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
latticra-q-seal/evidence/ML_KEM_PER_FILE_TEST_TRACE_GATE.md
latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
latticra-q-seal/evidence/ML_KEM_ACVP_PARSER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md
latticra-q-seal/evidence/ML_KEM_REVIEW_DISPOSITION_LEDGER.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
scripts/test-latticra-q-seal-ml-kem-per-file-test-trace-gate.sh
scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
```

## Current Fields

```text
ml_kem_implementation_binding_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM Implementation Binding Manifest
binding_profile=latticra-q-seal-ml-kem-implementation-binding-manifest/0.1
standards_basis=NIST-FIPS-203-and-SP-800-227
source_boundary=clean-room-no-apple-code
manifest_scope=ML-KEM-module-to-evidence-binding-before-primitive-code
binding_state=implementation-binding-blocked
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
fips_203_algorithm_bound=1
sp_800_227_kem_usage_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
implementation_traceability_matrix_bound=1
primitive_source_acceptance_gate_bound=1
source_layout_gate_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
per_file_test_trace_gate_bound=1
kat_manifest_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
acvp_response_fixture_bound=1
acvp_submission_package_contract_bound=1
vector_schema_bound=1
vector_source_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
replay_transcript_gate_bound=1
negative_test_evidence_bound=1
memory_safety_evidence_bound=1
api_misuse_resistance_bound=1
constant_time_review_bound=1
randomness_source_bound=1
zeroization_evidence_bound=1
side_channel_review_bound=1
provider_differential_bound=1
secret_state_contract_bound=1
ci_promotion_evidence_bound=1
module_to_gate_matrix_recorded=1
implementation_files_created=0
implementation_code_present=0
primitive_operations_bound=0
keygen_binding_approved=0
encaps_binding_approved=0
decaps_binding_approved=0
implementation_file_digest_manifest_recorded=0
code_owner_review_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_binding_items_total=45
required_binding_items_satisfied=40
blocked_reason=implementation-file-digest-keygen-encap-decap-code-owner-and-runtime-evidence-missing
status=ml-kem-implementation-binding-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
sh scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
```

Expected output:

```text
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
latticra q-seal ml-kem kat manifest invariants: ok
latticra q-seal ml-kem kat manifest: ok
latticra q-seal ml-kem acvp capability matrix invariants: ok
latticra q-seal ml-kem acvp capability matrix: ok
latticra q-seal ml-kem acvp fixture row plan invariants: ok
latticra q-seal ml-kem acvp fixture row plan: ok
latticra q-seal ml-kem acvp fixture digest row template invariants: ok
latticra q-seal ml-kem acvp fixture digest row template: ok
latticra q-seal ml-kem acvp parser contract invariants: ok
latticra q-seal ml-kem acvp parser contract: ok
latticra q-seal ml-kem acvp response contract invariants: ok
latticra q-seal ml-kem acvp response contract: ok
latticra q-seal ml-kem source digest manifest invariants: ok
latticra q-seal ml-kem source digest manifest: ok
latticra q-seal ml-kem source digest receipt invariants: ok
latticra q-seal ml-kem source digest receipt: ok
latticra q-seal ml-kem source digest verification invariants: ok
latticra q-seal ml-kem source digest verification: ok
latticra q-seal ml-kem receipt replay results invariants: ok
latticra q-seal ml-kem receipt replay results: ok
latticra q-seal ml-kem vector fixture lock invariants: ok
latticra q-seal ml-kem vector fixture lock: ok
latticra q-seal ml-kem vector fixture digest ledger invariants: ok
latticra q-seal ml-kem vector fixture digest ledger: ok
latticra q-seal ml-kem code owner review invariants: ok
latticra q-seal ml-kem code owner review: ok
latticra q-seal ml-kem review disposition ledger invariants: ok
latticra q-seal ml-kem review disposition ledger: ok
latticra q-seal ml-kem reviewer identity fixture invariants: ok
latticra q-seal ml-kem reviewer identity fixture: ok
latticra q-seal ml-kem reviewer role mapping invariants: ok
latticra q-seal ml-kem reviewer role mapping: ok
```
