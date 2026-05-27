# Latticra Q-Seal ML-KEM KAT Manifest

Status: no-vector known-answer test manifest shape
Date: 2026-05-27
Scope: ML-KEM KAT and ACVP evidence shape before any Latticra Q-Seal ML-KEM operation implementation.

This manifest records the test evidence that must exist before Latticra Q-Seal can enable ML-KEM key generation, encapsulation, decapsulation, shared-secret output, provider differential comparison, production cryptography claims, FIPS claims, network behavior, host mutation, or runtime authority.

No known-answer vectors are embedded here.

The schema-only vector contract is recorded in `latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md`. That contract records the ACVP/KAT prompt and response field shape, while keeping vector loading, response generation, operation execution, ACVP submission, production crypto claims, FIPS claims, and runtime authority disabled.

The vector-source intake contract is recorded in `latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md`. That contract records source authority and digest policy, while keeping vector bundle URL acceptance, fetch, import, processing, ACVP submission, production crypto claims, FIPS claims, and runtime authority disabled.

The negative-test evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md`. That contract records malformed-input, length-validation, encoding canonicality, invalid ciphertext, invalid key, decapsulation-failure, implicit-rejection, parser-rejection, fuzzing-corpus, differential negative-test, and implementation-binding blockers before parser or decapsulation behavior can be promoted.

The memory-safety evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md`. That contract records bounded-buffer, overflow, bounds, sanitizer, static-analysis, fuzzing, alias/lifetime, secret-buffer, zeroization-binding, and implementation-binding blockers before primitive promotion.

The API misuse-resistance contract is recorded in `latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md`. That contract records parameter validation, buffer preflight, typed key material, error taxonomy, state machine, misuse-case tests, language-binding, documentation-review, and implementation-binding blockers before public API promotion.

The source digest manifest is recorded in `latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md`. That manifest records SHA-256 clean-room source, test, and build digest templates, third-party source denial, reproducible-source snapshot, reviewed digest receipt, and CI digest-verification blockers before source can be accepted.

The code-owner review contract is recorded in `latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md`. That contract records SSDF review posture, clean-room review policy, reviewer identity, CODEOWNERS, cryptography review, security review, standards traceability, side-channel review, source-digest review, finding closure, and approval blockers before implementation promotion.

The CI promotion evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md`. That contract records SSDF secure-build posture, FIPS 203/SP 800-227 binding, local wrappers, readiness binding, implementation-binding dependency, KAT/ACVP, constant-time, memory-safety, side-channel, negative-test, provider differential, workflow, release-claim, and artifact-receipt blockers before implementation promotion.

The constant-time review contract is recorded in `latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md`. That contract records control-flow, memory-access, loop-bound, implicit-rejection, optimizer, measurement, assembly, CI, and signoff blockers before any implementation promotion.

The randomness-source contract is recorded in `latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md`. That contract records FIPS 203 seed-material policy and NIST SP 800-90A / SP 800-90B entropy, DRBG, reseed, health-test, failure-mode, platform-boundary, signoff, and implementation-binding blockers before random byte generation.

The zeroization evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md`. That contract records FIPS 203 secret-material scope and FIPS 140-3 zeroization posture, wipe primitive, compiler strategy, failure path, memory-scan, assembly review, and implementation-binding blockers before secret handling.

The side-channel review contract is recorded in `latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md`. That contract records FIPS 203 algorithm scope and FIPS 140-3 non-invasive security posture, leakage model, power, timing, cache, fault, compiler-artifact, platform, negative-test, signoff, and implementation-binding blockers before primitive promotion.

The implementation-binding manifest is recorded in `latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md`. That manifest binds planned ML-KEM source and test units to KAT/ACVP, vector, negative-test, memory-safety, API, constant-time, randomness, zeroization, side-channel, provider differential, secret-state, CI-promotion, digest, and code-owner blockers before primitive code.

## Current Fields

```text
ml_kem_kat_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM KAT Manifest
standards_source=NIST-FIPS-203
standards_publication_date=2024-08-13
standards_errata_state=errata-review-required
known_answer_vectors_embedded=0
known_answer_vectors_loaded=0
known_answer_vectors_verified=0
acvp_vector_review_recorded=0
operation_implementation_present=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
```

## Required Vector Families

```text
ML-KEM-512 keygen encaps decaps malformed-input negative-replay
ML-KEM-768 keygen encaps decaps malformed-input negative-replay
ML-KEM-1024 keygen encaps decaps malformed-input negative-replay
```

## Acceptance Gates

Before vectors can promote ML-KEM implementation work, the review packet must record every field below as satisfied. These are promotion prerequisites, not current-state claims.

```text
vector_source_authority=NIST-ACVP-or-approved-equivalent
vector_source_url_recorded=1
vector_source_digest_recorded=1
vector_license_review_recorded=1
errata_review_recorded=1
seed_material_handling_review_recorded=1
test_fixture_parser_review_recorded=1
positive_vectors_verified=1
negative_vectors_verified=1
malformed_input_cases_verified=1
cross_provider_differential_results_recorded=1
constant_time_review_recorded=1
side_channel_review_recorded=1
randomness_source_contract_recorded=1
intermediate_zeroization_contract_recorded=1
clean_room_implementation_review_recorded=1
```

## Non-Claims

This manifest is not a vector bundle, not a cryptographic implementation, not an ACVP submission, not FIPS validation evidence, not production cryptography, not proof of quantum resistance, not provider linking, not runtime authority, not network behavior, and not host mutation.
