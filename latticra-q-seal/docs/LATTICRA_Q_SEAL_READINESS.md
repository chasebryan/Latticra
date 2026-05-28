# Latticra Q-Seal Readiness Profile

Status: design-frame ready; runtime cryptography blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal readiness profile is the aggregate production-readiness surface for Q-Seal. It gives the rest of Latticra a single, deterministic answer about whether Q-Seal is ready for design-frame integration and whether it is allowed to perform runtime cryptography.

The current answer is intentionally split:

- Design-frame integration is ready.
- Runtime cryptography is blocked.
- No Apple corecrypto code is copied.
- No external provider code is copied.
- No provider runtime is used.
- No key generation, encapsulation, decapsulation, shared-secret emission, production cryptography claim, FIPS claim, or runtime authority is enabled.

## Readiness Fields

```text
q_seal_readiness_profile_present=1
readiness_profile=latticra-q-seal-readiness/0.1
formal_title=Latticra Q-Seal Readiness Profile
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM
source_boundary=clean-room-no-apple-code
readiness_state=design-frame-ready-runtime-crypto-blocked
foundation_present=1
ml_kem_parameters_present=1
ml_kem_512_parameters_present=1
ml_kem_768_parameters_present=1
ml_kem_1024_parameters_present=1
evidence_gate_present=1
fips_conformance_matrix_present=1
sp800_227_usage_profile_present=1
kat_manifest_present=1
kat_runner_contract_present=1
replay_transcript_gate_present=1
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
acvp_verdict_receipt_gate_present=1
validation_claim_gate_present=1
module_boundary_gate_present=1
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
source_layout_gate_present=1
implementation_file_digest_plan_present=1
clean_room_author_attestation_gate_present=1
per_file_standards_trace_gate_present=1
per_file_test_trace_gate_present=1
implementation_traceability_matrix_present=1
primitive_source_acceptance_gate_present=1
implementation_frame_present=1
secret_state_contract_present=1
clean_room_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
provider_runtime_used=0
components_total=52
components_present=52
runtime_blockers_total=49
required_readiness_items_total=1487
required_readiness_items_satisfied=1029
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

## Runtime Blockers

Runtime cryptography remains blocked by forty-nine aggregate blockers:

- ML-KEM evidence gate is missing KAT, ACVP, errata, constant-time, side-channel, randomness, zeroization, review, fuzzing, and CI evidence.
- ML-KEM FIPS 203 conformance matrix has no per-parameter trace, keygen step trace, encapsulation step trace, decapsulation step trace, encoding tests, decapsulation failure-semantics tests, primitive mapping review, errata review, implementation trace acceptance, or conformance matrix acceptance.
- ML-KEM KAT manifest has no KAT runner implementation, vector bundle digest, license review, storage review, parser review, positive vector verification, negative vector verification, malformed vector verification, provider differential record, CI KAT replay, loaded known-answer vectors, ACVP vector review, or operation implementation.
- ML-KEM KAT runner contract has no runner implementation, loaded fixture bundle, verified fixture digest, license review, storage review, runner parser review, result-schema review, positive result rows, negative result rows, malformed result rows, implicit-rejection result rows, provider differential rows, CI KAT replay transcript, operation implementation, KAT execution, or ACVP response generation.
- ML-KEM KAT result schema has no schema review, fixture bundle digest binding, result row fixture, positive result rows, negative result rows, malformed result rows, implicit-rejection rows, provider-differential rows, CI KAT replay transcript binding, runner execution record, or ACVP response-generation evidence.
- ML-KEM KAT result row fixture has no row-fixture review, fixture-bundle digest binding, positive row fixture, negative row fixture, malformed row fixture, implicit-rejection row fixture, provider-differential row fixture, CI KAT replay transcript binding, runner execution record, or ACVP response-generation evidence.
- ACVP intake has no reviewed vector source, digest, license review, schema review, loader, response generator, or submission path.
- ACVP capability matrix has no reviewed registration JSON, capability matrix review, parameter coverage review, function coverage review, response-schema review, or fixture row-generation approval.
- ACVP fixture row plan has no reviewed registration JSON, capability matrix review, fixture row plan review, digest rows, source digests, storage paths, license review, schema crosscheck, import review, digest-ledger review, or row-plan-to-ledger review.
- ACVP fixture digest row template has no real digest rows, source URL rows, SHA-256 digest rows, bundle-size rows, storage-path rows, license-review rows, schema-crosscheck rows, reviewer identity rows, review timestamp rows, CI replay transcript rows, tamper evidence rows, or template review.
- ACVP parser contract has no parser implementation, canonical schema validation, length-bound enforcement, duplicate-field rejection, invalid-type rejection, parameter-set crosscheck, deterministic fixture replay, fuzzing harness, negative parser corpus, response-emission review, memory-safety review, or implementation binding.
- ACVP response contract has no response generator implementation, response negative tests, schema review, security review, CI replay, accepted parser output, vector execution evidence, response JSON generation, or accepted response output.
- ACVP response fixture has no fixture review, fixture-bundle digest binding, accepted parser output, vector-execution evidence, keyGen response fixture, encapsulation response fixture, decapsulation response fixture, key-check response fixture, negative response fixture, response schema review, security review, CI replay, accepted response output, or response-generation evidence.
- ACVP submission-package contract has no package review, request-bundle digest binding, response-bundle digest binding, vector-execution evidence, accepted response output, local replay transcript, ACVP client-boundary review, submission receipt, validation-server acceptance, local package acceptance, or ACVP response-acceptance record.
- ACVP verdict receipt gate has no bound submission receipt, validation-server acceptance, pass verdict record, certificate identifier, verified receipt digest, reviewer disposition, or accepted verdict receipt.
- ML-KEM validation claim gate has no implementation claim evidence, ACVP pass evidence, CMVP certificate, module boundary, security policy, release artifact digest, public claim review, reviewer disposition, or accepted claim gate.
- ML-KEM module-boundary gate has no cryptographic module name, module version, operational environment, FIPS 140-3 security policy, roles/services/authentication record, self-test policy, approved algorithm inventory, entropy boundary, zeroization boundary review, ACVP algorithm certificate, CMVP submission identifier, boundary review, reviewer disposition, or accepted boundary evidence.
- ML-KEM vector schema has no reviewed vector source, digest, license review, loader, JSON parser, response generator, vector execution, or ACVP submission authority.
- ML-KEM vector source intake has no reviewed bundle URL, digest, size, license review, hash verification, schema crosscheck, errata binding, offline storage path, or import review.
- ML-KEM vector fixture lock has no fixture source digest, license review, storage path, schema crosscheck, parameter coverage, negative-case coverage, import review, loaded bundle, vector execution, or runtime authority.
- ML-KEM vector fixture digest ledger has no source URL, source digest, bundle size, license review, storage path, schema crosscheck, parameter-set coverage, operation-family coverage, negative-case coverage, import review, or ledger review.
- ML-KEM negative-test evidence has no length validation, encoding canonicality, invalid ciphertext, invalid key, decapsulation-failure, implicit-rejection, parser-rejection, fuzzing-corpus, differential negative-test, or implementation-binding evidence.
- ML-KEM memory-safety evidence has no overflow review, bounds review, sanitizer evidence, static-analysis evidence, memory-safety fuzzing, alias/lifetime review, secret-buffer isolation, zeroization binding, cross-platform word-size review, or implementation binding.
- ML-KEM implementation file digest plan has no source files, implementation digest rows, test digest rows, build-script digest rows, reviewed receipt, verified replay, or accepted digest-row plan.
- ML-KEM source layout gate has no source files, source layout rows, layout digest rows, layout review, layout approval, or accepted source layout.
- ML-KEM clean-room author attestation gate has no source files, author identity import, per-file author attestations, clean-room attestation review, provenance exception review, or accepted author attestation.
- ML-KEM per-file standards trace gate has no source files, per-file standards trace rows, FIPS 203 clause coverage review, SP 800-227 usage coverage review, parameter-set coverage review, trace review approval, or accepted standards trace.
- ML-KEM per-file test trace gate has no source files, per-file test trace rows, KAT trace coverage review, ACVP trace coverage review, negative-test trace review, trace review approval, or accepted test trace.
- ML-KEM API misuse-resistance evidence has no error taxonomy, API state machine, misuse-case matrix, wrong-parameter tests, null/overlap tests, deterministic test-mode guard, secret-output lifetime policy, language-binding policy, documentation examples review, or implementation binding.
- ML-KEM source digest manifest has no implementation files, source-file digests, test-file digests, build-script digests, reviewed digest receipt, reproducible source snapshot, or CI digest verification.
- ML-KEM source digest receipt has no source receipts, test receipts, build receipts, receipt verification, reviewed digest receipt, replay check, or CI digest verification.
- ML-KEM source digest verification has no source receipts, test receipts, build receipts, digest replay execution, tamper fixture execution, CI verification harness, or reviewed verification result.
- ML-KEM receipt replay results have no source replay results, test replay results, build replay results, tamper replay results, or replay-result review.
- ML-KEM code-owner review has no reviewer identities, CODEOWNERS record, cryptography review, security review, standards traceability review, side-channel review, source-digest review, closed findings, or approval receipt.
- ML-KEM review disposition ledger has no reviewer identity disposition, code-owner disposition, cryptography disposition, security disposition, standards traceability disposition, side-channel disposition, source-digest disposition, closed findings, or approval receipt.
- ML-KEM reviewer identity fixture has no imported reviewer identities, cryptography reviewer identity, security reviewer identity, code-owner identity, independence attestation, identity import review, or approval authority.
- ML-KEM reviewer role mapping has no imported role records, cryptography role mapping, security role mapping, code-owner role mapping, standards traceability role mapping, side-channel role mapping, source-digest role mapping, separation review, or approval-authority mapping.
- ML-KEM CI promotion evidence has no KAT/ACVP passing record, ACVP verdict receipt record, validation-claim gate, constant-time passing record, memory-safety passing record, side-channel passing record, negative-test passing record, provider differential passing record, implementation-binding CI result, promotion workflow record, release-claim gate, or signed artifact receipt.
- ML-KEM constant-time review has no timing measurement, static-analysis record, assembly review, optimizer review, secret-state binding, negative timing tests, cross-platform review, formal signoff, CI gate, or implementation binding.
- ML-KEM randomness source has no entropy-source inventory, entropy validation, DRBG selection, security-strength review, seed derivation policy, reseed policy, prediction-resistance policy, health-test policy, failure-mode policy, platform RNG boundary, entropy signoff, or implementation binding.
- ML-KEM zeroization evidence has no selected wipe primitive, implemented wipe primitive, compiler dead-store review, volatile or intrinsic strategy, stack/heap/register policy, error-path zeroization, decapsulation-failure zeroization, memory-scan test, assembly review, cross-platform review, formal review, or implementation binding.
- ML-KEM side-channel review has no leakage model, power-analysis test, timing measurement, cache-access analysis, fault-injection review, microarchitectural leakage review, hardening decision, compiler artifact review, platform matrix, negative leakage test, reviewer signoff, or implementation binding.
- Provider differential comparison is not licensed, pinned, digested, reproducible, vector-tested, or triaged.
- ML-KEM implementation traceability matrix has no constant-time mapping, memory-safety mapping, zeroization mapping, randomness mapping, negative-test mapping, source digest mapping, code-owner mapping, review-disposition mapping, accepted trace, implementation file digest manifest, implementation code, or runtime authority.
- Implementation-binding manifest has no implementation files, source digest manifest, keygen binding approval, encaps binding approval, decapsulation binding approval, code-owner review, or runtime evidence.
- Implementation traceability matrix has no constant-time, memory-safety, zeroization, randomness, negative-test, source-digest, code-owner, review-disposition, implementation-trace acceptance, or implementation-file digest mapping.
- Primitive source acceptance gate has no source files, source-file digest rows, clean-room author attestation, per-file standards trace, per-file test trace, per-file review approval, or source acceptance approval.
- Implementation frame has no primitive implementation, constant-time design proof, zeroization design, randomness design, canonical serialization policy, malformed-input policy, vector binding, or formal review.
- Secret-state contract has no secret inventory, constant-time review, implicit rejection proof, zeroization primitive, randomness boundary, seed-handling review, compiler review, sanitizer strategy, or side-channel review.

## Files

```text
latticra-q-seal/include/latticra/q_seal_readiness.h
latticra-q-seal/src/q_seal_readiness.c
latticra-q-seal/tests/q_seal_readiness_invariants.c
latticra-q-seal/evidence/Q_SEAL_READINESS.md
latticra-q-seal/evidence/ML_KEM_FIPS_CONFORMANCE_MATRIX.md
latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
latticra-q-seal/evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
latticra-q-seal/evidence/ML_KEM_PER_FILE_TEST_TRACE_GATE.md
latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_KAT_RUNNER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_KAT_RESULT_ROW_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
latticra-q-seal/evidence/ML_KEM_ACVP_PARSER_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_ACVP_SUBMISSION_PACKAGE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md
latticra-q-seal/evidence/ML_KEM_VALIDATION_CLAIM_GATE.md
latticra-q-seal/evidence/ML_KEM_MODULE_BOUNDARY_GATE.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/evidence/ML_KEM_REVIEW_DISPOSITION_LEDGER.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/evidence/ML_KEM_SOURCE_LAYOUT_GATE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-layout-gate.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh
scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-source-layout-gate.sh
scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
scripts/test-latticra-q-seal-ml-kem-kat-result-row-fixture.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
scripts/test-latticra-q-seal-readiness.sh
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh
sh scripts/test-latticra-q-seal-readiness.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
make latticra-q-seal-readiness
```

Expected output:

```text
latticra q-seal readiness invariants: ok
latticra q-seal readiness: ok
latticra q-seal ml-kem module boundary gate invariants: ok
latticra q-seal ml-kem module boundary gate: ok
```
