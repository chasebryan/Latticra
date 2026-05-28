# Latticra Seal Hybrid Provider Self-Test

Status: local provider-backed hybrid key-establishment self-test
Scope: authority-neutral OpenSSL EVP self-test that derives a classical NIST P-256 ECDH shared secret and ML-KEM-512, ML-KEM-768, and ML-KEM-1024 shared secrets, binds provider transcript material into Seal AAD, then feeds those secrets into the existing Seal HKDF-SHA256/AES-256-GCM attached-record envelope. This does not add production crypto claims, FIPS validation claims, key storage, secret output, record output, release signing, update signing, receipt signing, capability enforcement, or runtime authority.

## Purpose

This slice closes the gap between the provider-level Q-Seal ML-KEM self-test and the existing Seal hybrid envelope.

The self-test proves that the local substrate can obtain a classical provider-derived 32-byte P-256 ECDH shared secret and provider-derived 32-byte ML-KEM shared secrets for all three FIPS 203 parameter sets, bind the P-256 public keys, ML-KEM ciphertext, and algorithm labels into authenticated transcript AAD, pass each pairing into the hybrid envelope, authenticate attached records, reject tampered transcript AAD before plaintext release, and zeroize all local secret and record buffers before returning.

## Current Fields

```text
hybrid_provider_self_test_present=1
self_test_profile=latticra-seal-hybrid-provider-self-test/0.1
classical_provider=OpenSSL-EVP
pqc_provider=OpenSSL-EVP
classical_algorithm=ECDH-P-256
pqc_algorithm=ML-KEM-512,ML-KEM-768,ML-KEM-1024
envelope_algorithm=HKDF-SHA256+AES-256-GCM
standards_source=NIST-SP-800-56A-REV3,NIST-FIPS-203,NIST-SP-800-56C-REV2,NIST-FIPS-197,NIST-SP-800-38D
provider_linked=1
provider_runtime_used=1
p256_key_generation_performed=1
p256_ecdh_derive_performed=1
p256_shared_secret_match=1
p256_shared_secret_bytes=32
ml_kem_key_generation_performed=1
ml_kem_encapsulation_performed=1
ml_kem_decapsulation_performed=1
ml_kem_shared_secret_match=1
ml_kem_shared_secret_bytes=32
ml_kem_parameter_sets_tested=3
ml_kem_512_key_generation_performed=1
ml_kem_512_encapsulation_performed=1
ml_kem_512_decapsulation_performed=1
ml_kem_512_shared_secret_match=1
ml_kem_512_ciphertext_bytes=768
ml_kem_512_hybrid_envelope_authenticated=1
ml_kem_768_key_generation_performed=1
ml_kem_768_encapsulation_performed=1
ml_kem_768_decapsulation_performed=1
ml_kem_768_shared_secret_match=1
ml_kem_768_ciphertext_bytes=1088
ml_kem_768_hybrid_envelope_authenticated=1
ml_kem_1024_key_generation_performed=1
ml_kem_1024_encapsulation_performed=1
ml_kem_1024_decapsulation_performed=1
ml_kem_1024_shared_secret_match=1
ml_kem_1024_ciphertext_bytes=1568
ml_kem_1024_hybrid_envelope_authenticated=1
hybrid_envelope_record_sealed=1
hybrid_envelope_record_opened=1
hybrid_envelope_authenticated=1
hybrid_envelope_plaintext_recovered=1
hybrid_envelope_records_sealed_total=3
hybrid_envelope_records_opened_total=3
hybrid_envelope_records_authenticated_total=3
hybrid_transcript_aad_bound=1
hybrid_transcript_cases_bound_total=3
hybrid_transcript_tampering_rejected=1
hybrid_transcript_tampering_rejected_total=3
provider_algorithm_transcript_bound=1
p256_public_key_transcript_bound=1
ml_kem_ciphertext_transcript_bound=1
ml_kem_ciphertext_transcript_bytes_total=3424
secret_material_output_emitted=0
record_output_emitted=0
plaintext_output_emitted=0
classical_secret_zeroized=1
pqc_secret_zeroized=1
record_buffer_zeroized=1
plaintext_buffer_zeroized=1
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
status=hybrid-provider-self-test-passed
```

## Boundary

This is a local self-test, not a public key-establishment API.

It generates ephemeral provider keys, uses the derived secrets only in internal buffers, authenticates provider transcript material as AAD, seals and opens internal attached records, and returns only metadata fields. It does not emit the ECDH secret, ML-KEM secrets, ML-KEM ciphertexts, Seal records, recovered plaintext, or private keys.

## Validation

```sh
sh scripts/test-latticra-seal-hybrid-provider-self-test.sh
```

Expected output:

```text
latticra seal hybrid provider self-test invariants: ok
latticra seal hybrid provider self-test: ok
```
