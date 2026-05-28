# ML-KEM Provider Self-Test Evidence

Status: local provider-backed ML-KEM self-test evidence
Source: OpenSSL EVP local run

```text
ml_kem_provider_self_test_present=1
provider=OpenSSL-EVP
standards_source=NIST-FIPS-203
ML-KEM-512-provider_self_test_passed=1
ML-KEM-768-provider_self_test_passed=1
ML-KEM-1024-provider_self_test_passed=1
provider_linked=1
provider_available=1
provider_runtime_used=1
key_generation_performed=1
keypair_algorithm_identity_verified=1
public_key_reimported=1
public_key_algorithm_identity_verified=1
encapsulation_public_key_only=1
encapsulation_performed=1
decapsulation_performed=1
tampered_ciphertext_decapsulation_performed=1
tampered_ciphertext_shared_secret_mismatch=1
tampered_ciphertext_rejected=1
shared_secret_internal_buffers_used=1
shared_secret_match=1
shared_secret_constant_time_compare=1
tampered_ciphertext_constant_time_compare=1
shared_secret_zeroized=1
ciphertext_zeroized=1
shared_secret_output_emitted=0
ciphertext_output_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
```

This evidence records local execution of OpenSSL EVP ML-KEM key generation,
algorithm-identity verification for generated and reimported keys, public-key
reimport, public-key encapsulation, decapsulation, tampered ciphertext
shared-secret mismatch, constant-time shared-secret equality checks, and
zeroization for the three FIPS 203 ML-KEM parameter sets. It is self-test
evidence only and does not claim production readiness, FIPS validation, key
storage, secret output, capability enforcement, or runtime authority.
