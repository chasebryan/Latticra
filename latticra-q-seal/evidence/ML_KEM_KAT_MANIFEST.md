# Latticra Q-Seal ML-KEM KAT Manifest

Status: fail-closed known-answer test manifest shape
Date: 2026-05-27
Scope: ML-KEM KAT and ACVP evidence shape before any Latticra Q-Seal ML-KEM operation implementation.

This manifest records the test evidence that must exist before Latticra Q-Seal can enable ML-KEM key generation, encapsulation, decapsulation, shared-secret output, provider differential comparison, production cryptography claims, FIPS claims, network behavior, host mutation, or runtime authority. It is now backed by the first-class `q_seal_ml_kem_kat_manifest` readiness component.

No known-answer vectors are embedded here.

The schema-only vector contract is recorded in `latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md`. That contract records the ACVP/KAT prompt and response field shape, while keeping vector loading, response generation, operation execution, ACVP submission, production crypto claims, FIPS claims, and runtime authority disabled.

The vector-source intake contract is recorded in `latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md`. That contract records source authority and digest policy, while keeping vector bundle URL acceptance, fetch, import, processing, ACVP submission, production crypto claims, FIPS claims, and runtime authority disabled.

The vector fixture lock is recorded in `latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md`. That fixture records offline KAT/ACVP bundle digest, license, storage, schema crosscheck, parameter coverage, negative-case coverage, and import-review blockers while keeping vector loading, vector execution, ACVP submission, production crypto claims, FIPS claims, and runtime authority disabled.

The vector fixture digest ledger is recorded in `latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md`. That ledger records source URL, SHA-256 digest, bundle size, license, storage, schema crosscheck, parameter coverage, keygen/encaps/decaps coverage, negative-case coverage, import-review, and ledger-review blockers before any vector fixture can be loaded.

The negative-test evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md`. That contract records malformed-input, length-validation, encoding canonicality, invalid ciphertext, invalid key, decapsulation-failure, implicit-rejection, parser-rejection, fuzzing-corpus, differential negative-test, and implementation-binding blockers before parser or decapsulation behavior can be promoted.

The memory-safety evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md`. That contract records bounded-buffer, overflow, bounds, sanitizer, static-analysis, fuzzing, alias/lifetime, secret-buffer, zeroization-binding, and implementation-binding blockers before primitive promotion.

The API misuse-resistance contract is recorded in `latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md`. That contract records parameter validation, buffer preflight, typed key material, error taxonomy, state machine, misuse-case tests, language-binding, documentation-review, and implementation-binding blockers before public API promotion.

The source digest manifest is recorded in `latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md`. That manifest records SHA-256 clean-room source, test, and build digest templates, third-party source denial, reproducible-source snapshot, reviewed digest receipt, and CI digest-verification blockers before source can be accepted.

The source digest receipt fixture is recorded in `latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md`. That fixture records clean-room source, test, and build-script receipt rows, normalized paths, SHA-256 replay policy, tamper evidence, reviewed receipt, and CI digest-verification blockers before source receipts can be accepted.

The source digest verification harness is recorded in `latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md`. That harness records offline receipt replay, tamper fixture, CI verification harness, and reviewed verification-result blockers before source digest receipts can be promoted.

The receipt replay result fixture is recorded in `latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md`. That fixture records source, test, build, and tamper replay result blockers before digest verification can promote implementation work.

The code-owner review contract is recorded in `latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md`. That contract records SSDF review posture, clean-room review policy, reviewer identity, CODEOWNERS, cryptography review, security review, standards traceability, side-channel review, source-digest review, finding closure, and approval blockers before implementation promotion.

The review disposition ledger is recorded in `latticra-q-seal/evidence/ML_KEM_REVIEW_DISPOSITION_LEDGER.md`. That ledger records reviewer identity, code-owner, cryptography, security, standards traceability, side-channel, source-digest, finding-closure, rejection-policy, and approval-receipt disposition blockers before implementation promotion.

The reviewer identity fixture is recorded in `latticra-q-seal/evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md`. That fixture records reviewer identity import, role mapping, independence attestation, PII minimization, identity import review, and approval-authority blockers before review evidence can promote implementation work.

The reviewer role-mapping fixture is recorded in `latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md`. That fixture records required role records, reviewer separation, conflict-of-interest policy, and approval-authority blockers before review evidence can promote implementation work.

The CI promotion evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md`. That contract records SSDF secure-build posture, FIPS 203/SP 800-227 binding, local wrappers, readiness binding, implementation-binding dependency, KAT/ACVP, constant-time, memory-safety, side-channel, negative-test, provider differential, workflow, release-claim, and artifact-receipt blockers before implementation promotion.

The constant-time review contract is recorded in `latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md`. That contract records control-flow, memory-access, loop-bound, implicit-rejection, optimizer, measurement, assembly, CI, and signoff blockers before any implementation promotion.

The randomness-source contract is recorded in `latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md`. That contract records FIPS 203 seed-material policy and NIST SP 800-90A / SP 800-90B entropy, DRBG, reseed, health-test, failure-mode, platform-boundary, signoff, and implementation-binding blockers before random byte generation.

The zeroization evidence contract is recorded in `latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md`. That contract records FIPS 203 secret-material scope and FIPS 140-3 zeroization posture, wipe primitive, compiler strategy, failure path, memory-scan, assembly review, and implementation-binding blockers before secret handling.

The side-channel review contract is recorded in `latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md`. That contract records FIPS 203 algorithm scope and FIPS 140-3 non-invasive security posture, leakage model, power, timing, cache, fault, compiler-artifact, platform, negative-test, signoff, and implementation-binding blockers before primitive promotion.

The implementation-binding manifest is recorded in `latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md`. That manifest binds planned ML-KEM source and test units to KAT/ACVP, vector, fixture-lock, fixture-digest-ledger, negative-test, memory-safety, API, constant-time, randomness, zeroization, side-channel, provider differential, secret-state, CI-promotion, digest, receipt, digest-verification, replay-result, code-owner, disposition, reviewer-identity, and reviewer-role blockers before primitive code.

## Current Fields

```text
manifest_profile=latticra-q-seal-ml-kem-kat-manifest/0.1
ml_kem_kat_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM KAT Manifest
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
kat_scope=ML-KEM-known-answer-manifest-before-vector-execution
manifest_state=kat-manifest-recorded-runner-and-vector-evidence-missing
standards_source=NIST-FIPS-203
standards_publication_date=2024-08-13
standards_errata_state=errata-review-required
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
acvp_keygen_aft_required=1
acvp_encapdecap_aft_required=1
acvp_decapsulation_val_required=1
acvp_keycheck_val_required=1
ml_kem_512_coverage_required=1
ml_kem_768_coverage_required=1
ml_kem_1024_coverage_required=1
seed_material_handling_policy_recorded=1
positive_vector_family_required=1
negative_vector_family_required=1
malformed_vector_family_required=1
implicit_rejection_vector_required=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
vector_schema_bound=1
vector_source_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
provider_differential_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
no_embedded_vectors_policy_recorded=1
known_answer_vectors_embedded=0
apple_corecrypto_code_copied=0
external_provider_code_copied=0
kat_runner_implementation_present=0
vector_bundle_digest_recorded=0
vector_bundle_license_reviewed=0
vector_bundle_storage_reviewed=0
kat_parser_reviewed=0
positive_vectors_verified=0
negative_vectors_verified=0
malformed_vectors_verified=0
cross_provider_differential_recorded=0
ci_kat_replay_recorded=0
known_answer_vectors_loaded=0
known_answer_vectors_verified=0
acvp_vector_review_recorded=0
operation_implementation_present=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_manifest_items_total=40
required_kat_manifest_items_satisfied=26
status=ml-kem-kat-manifest-blocked
```

## Required Vector Families

```text
ML-KEM-512 -> keyGen AFT, encapDecap AFT, decapsulation VAL, key-check VAL, malformed-input negative cases, implicit rejection
ML-KEM-768 -> keyGen AFT, encapDecap AFT, decapsulation VAL, key-check VAL, malformed-input negative cases, implicit rejection
ML-KEM-1024 -> keyGen AFT, encapDecap AFT, decapsulation VAL, key-check VAL, malformed-input negative cases, implicit rejection
```

## Promotion Blockers

Before vectors can promote ML-KEM implementation work, the review packet must record the current zero-valued fields above as satisfied evidence. These are promotion prerequisites, not current-state claims.

## Validation

```text
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
make latticra-q-seal-ml-kem-kat-manifest
```

## Non-Claims

This manifest is not a vector bundle, not a cryptographic implementation, not an ACVP submission, not FIPS validation evidence, not production cryptography, not proof of quantum resistance, not provider linking, not runtime authority, not network behavior, and not host mutation.
