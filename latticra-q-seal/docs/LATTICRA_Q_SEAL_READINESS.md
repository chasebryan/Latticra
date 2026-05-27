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
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
source_boundary=clean-room-no-apple-code
readiness_state=design-frame-ready-runtime-crypto-blocked
foundation_present=1
ml_kem_parameters_present=1
ml_kem_512_parameters_present=1
ml_kem_768_parameters_present=1
ml_kem_1024_parameters_present=1
evidence_gate_present=1
acvp_intake_present=1
vector_schema_present=1
vector_source_intake_present=1
negative_test_evidence_present=1
memory_safety_evidence_present=1
api_misuse_resistance_present=1
source_digest_manifest_present=1
code_owner_review_present=1
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
components_total=20
components_present=20
runtime_blockers_total=18
required_readiness_items_total=328
required_readiness_items_satisfied=158
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

Runtime cryptography remains blocked by eighteen aggregate blockers:

- ML-KEM evidence gate is missing KAT, ACVP, errata, constant-time, side-channel, randomness, zeroization, review, fuzzing, and CI evidence.
- ACVP intake has no reviewed vector source, digest, license review, schema review, loader, response generator, or submission path.
- ML-KEM vector schema has no reviewed vector source, digest, license review, loader, JSON parser, response generator, vector execution, or ACVP submission authority.
- ML-KEM vector source intake has no reviewed bundle URL, digest, size, license review, hash verification, schema crosscheck, errata binding, offline storage path, or import review.
- ML-KEM negative-test evidence has no length validation, encoding canonicality, invalid ciphertext, invalid key, decapsulation-failure, implicit-rejection, parser-rejection, fuzzing-corpus, differential negative-test, or implementation-binding evidence.
- ML-KEM memory-safety evidence has no overflow review, bounds review, sanitizer evidence, static-analysis evidence, memory-safety fuzzing, alias/lifetime review, secret-buffer isolation, zeroization binding, cross-platform word-size review, or implementation binding.
- ML-KEM API misuse-resistance evidence has no error taxonomy, API state machine, misuse-case matrix, wrong-parameter tests, null/overlap tests, deterministic test-mode guard, secret-output lifetime policy, language-binding policy, documentation examples review, or implementation binding.
- ML-KEM source digest manifest has no implementation files, source-file digests, test-file digests, build-script digests, reviewed digest receipt, reproducible source snapshot, or CI digest verification.
- ML-KEM code-owner review has no reviewer identities, CODEOWNERS record, cryptography review, security review, standards traceability review, side-channel review, source-digest review, closed findings, or approval receipt.
- ML-KEM CI promotion evidence has no KAT/ACVP passing record, constant-time passing record, memory-safety passing record, side-channel passing record, negative-test passing record, provider differential passing record, implementation-binding CI result, promotion workflow record, release-claim gate, or signed artifact receipt.
- ML-KEM constant-time review has no timing measurement, static-analysis record, assembly review, optimizer review, secret-state binding, negative timing tests, cross-platform review, formal signoff, CI gate, or implementation binding.
- ML-KEM randomness source has no entropy-source inventory, entropy validation, DRBG selection, security-strength review, seed derivation policy, reseed policy, prediction-resistance policy, health-test policy, failure-mode policy, platform RNG boundary, entropy signoff, or implementation binding.
- ML-KEM zeroization evidence has no selected wipe primitive, implemented wipe primitive, compiler dead-store review, volatile or intrinsic strategy, stack/heap/register policy, error-path zeroization, decapsulation-failure zeroization, memory-scan test, assembly review, cross-platform review, formal review, or implementation binding.
- ML-KEM side-channel review has no leakage model, power-analysis test, timing measurement, cache-access analysis, fault-injection review, microarchitectural leakage review, hardening decision, compiler artifact review, platform matrix, negative leakage test, reviewer signoff, or implementation binding.
- Provider differential comparison is not licensed, pinned, digested, reproducible, vector-tested, or triaged.
- Implementation-binding manifest has no implementation files, source digest manifest, keygen binding approval, encaps binding approval, decapsulation binding approval, code-owner review, or runtime evidence.
- Implementation frame has no primitive implementation, constant-time design proof, zeroization design, randomness design, canonical serialization policy, malformed-input policy, vector binding, or formal review.
- Secret-state contract has no secret inventory, constant-time review, implicit rejection proof, zeroization primitive, randomness boundary, seed-handling review, compiler review, sanitizer strategy, or side-channel review.

## Files

```text
latticra-q-seal/include/latticra/q_seal_readiness.h
latticra-q-seal/src/q_seal_readiness.c
latticra-q-seal/tests/q_seal_readiness_invariants.c
latticra-q-seal/evidence/Q_SEAL_READINESS.md
latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh
scripts/test-latticra-q-seal-readiness.sh
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh
sh scripts/test-latticra-q-seal-readiness.sh
make latticra-q-seal-readiness
```

Expected output:

```text
latticra q-seal readiness invariants: ok
latticra q-seal readiness: ok
```
