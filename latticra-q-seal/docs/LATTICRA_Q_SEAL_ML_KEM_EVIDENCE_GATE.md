# Latticra Q-Seal ML-KEM Evidence Gate

Status: fail-closed ML-KEM readiness gate
Date: 2026-05-27
Scope: C evidence-gate API, KAT manifest shape, errata review posture, and operation-blocking invariants before ML-KEM implementation.

This gate turns Latticra Q-Seal ML-KEM from a parameter-only packet into a readiness-controlled subsystem. It records the evidence required before key generation, encapsulation, decapsulation, shared-secret output, provider comparison, production cryptography claims, FIPS claims, network behavior, host mutation, or runtime authority can be enabled.

## Source Posture

NIST FIPS 203 was published on August 13, 2024 and defines ML-KEM. The current Q-Seal gate treats the standard as authoritative while requiring an errata review before implementation promotion.

```text
source_url=https://csrc.nist.gov/pubs/fips/203/final
publication_url=https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.203.pdf
standards_errata_state=errata-review-required
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_evidence_gate.h
latticra-q-seal/src/q_seal_ml_kem_evidence_gate.c
latticra-q-seal/tests/q_seal_ml_kem_evidence_gate_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_ACVP_INTAKE.md
latticra-q-seal/evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md
latticra-q-seal/evidence/ML_KEM_REVIEW_DISPOSITION_LEDGER.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md
latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
latticra-q-seal/evidence/ML_KEM_PROVIDER_DIFFERENTIAL.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FRAME.md
latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE.md
scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
scripts/test-latticra-q-seal-ml-kem-vector-source.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
```

## Current Fields

```text
ml_kem_evidence_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Evidence Gate
gate_profile=latticra-q-seal-ml-kem-evidence-gate/0.1
standards_source=NIST-FIPS-203
standards_publication_date=2024-08-13
standards_errata_state=errata-review-required
fips_203_source_verified=1
fips_203_errata_review_required=1
fips_203_errata_review_recorded=0
parameter_sets_recorded=1
ml_kem_512_parameters_recorded=1
ml_kem_768_parameters_recorded=1
ml_kem_1024_parameters_recorded=1
known_answer_test_manifest_present=1
known_answer_vectors_embedded=0
known_answer_vectors_loaded=0
known_answer_vectors_verified=0
acvp_vector_review_required=1
acvp_vector_review_recorded=0
clean_room_required=1
clean_room_implementation_review_recorded=0
apple_corecrypto_code_copied=0
provider_differential_test_contract_required=1
provider_differential_test_contract_recorded=0
provider_linked=0
constant_time_review_required=1
constant_time_review_recorded=0
side_channel_review_required=1
side_channel_review_recorded=0
randomness_source_contract_required=1
randomness_source_contract_recorded=0
intermediate_zeroization_contract_required=1
intermediate_zeroization_contract_recorded=0
memory_safety_review_required=1
memory_safety_review_recorded=0
api_misuse_resistance_review_required=1
api_misuse_resistance_review_recorded=0
fuzzing_and_negative_tests_required=1
fuzzing_and_negative_tests_recorded=0
ci_quality_gate_required=1
ci_quality_gate_recorded=0
required_evidence_items_total=16
required_evidence_items_satisfied=3
implementation_present=0
operations_enabled=0
key_generation_enabled=0
encapsulation_enabled=0
decapsulation_enabled=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
gate_state=blocked-awaiting-evidence
blocked_reason=kat-acvp-errata-constant-time-side-channel-randomness-zeroization-reviews-missing
status=ml-kem-evidence-gate-fail-closed
```

## Promotion Rule

The operation gate remains closed unless all required evidence items are satisfied and the implementation is present, reviewed, and explicitly enabled.

```text
operation_promotion_allowed=0
reason=required-evidence-items-satisfied-is-3-of-16
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
sh scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
```

Expected output:

```text
latticra q-seal ml-kem evidence gate invariants: ok
latticra q-seal ml-kem evidence gate: ok
latticra q-seal ml-kem acvp intake invariants: ok
latticra q-seal ml-kem acvp intake: ok
latticra q-seal ml-kem acvp capability matrix invariants: ok
latticra q-seal ml-kem acvp capability matrix: ok
latticra q-seal ml-kem acvp fixture row plan invariants: ok
latticra q-seal ml-kem acvp fixture row plan: ok
latticra q-seal ml-kem vector schema invariants: ok
latticra q-seal ml-kem vector schema: ok
latticra q-seal ml-kem vector source invariants: ok
latticra q-seal ml-kem vector source: ok
latticra q-seal ml-kem vector fixture lock invariants: ok
latticra q-seal ml-kem vector fixture lock: ok
latticra q-seal ml-kem vector fixture digest ledger invariants: ok
latticra q-seal ml-kem vector fixture digest ledger: ok
latticra q-seal ml-kem negative-test evidence invariants: ok
latticra q-seal ml-kem negative-test evidence: ok
latticra q-seal ml-kem memory-safety evidence invariants: ok
latticra q-seal ml-kem memory-safety evidence: ok
latticra q-seal ml-kem api misuse resistance invariants: ok
latticra q-seal ml-kem api misuse resistance: ok
latticra q-seal ml-kem source digest manifest invariants: ok
latticra q-seal ml-kem source digest manifest: ok
latticra q-seal ml-kem source digest receipt invariants: ok
latticra q-seal ml-kem source digest receipt: ok
latticra q-seal ml-kem source digest verification invariants: ok
latticra q-seal ml-kem source digest verification: ok
latticra q-seal ml-kem receipt replay results invariants: ok
latticra q-seal ml-kem receipt replay results: ok
latticra q-seal ml-kem code owner review invariants: ok
latticra q-seal ml-kem code owner review: ok
latticra q-seal ml-kem review disposition ledger invariants: ok
latticra q-seal ml-kem review disposition ledger: ok
latticra q-seal ml-kem reviewer identity fixture invariants: ok
latticra q-seal ml-kem reviewer identity fixture: ok
latticra q-seal ml-kem reviewer role mapping invariants: ok
latticra q-seal ml-kem reviewer role mapping: ok
latticra q-seal ml-kem ci promotion evidence invariants: ok
latticra q-seal ml-kem ci promotion evidence: ok
latticra q-seal ml-kem constant-time review invariants: ok
latticra q-seal ml-kem constant-time review: ok
latticra q-seal ml-kem randomness source invariants: ok
latticra q-seal ml-kem randomness source: ok
latticra q-seal ml-kem zeroization evidence invariants: ok
latticra q-seal ml-kem zeroization evidence: ok
latticra q-seal ml-kem side-channel review invariants: ok
latticra q-seal ml-kem side-channel review: ok
latticra q-seal ml-kem provider differential invariants: ok
latticra q-seal ml-kem provider differential: ok
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
latticra q-seal ml-kem implementation frame invariants: ok
latticra q-seal ml-kem implementation frame: ok
latticra q-seal ml-kem secret-state contract invariants: ok
latticra q-seal ml-kem secret-state contract: ok
```
