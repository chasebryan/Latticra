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
encapsulation_performed=1
decapsulation_performed=1
shared_secret_internal_buffers_used=1
shared_secret_match=1
shared_secret_zeroized=1
ciphertext_zeroized=1
shared_secret_output_emitted=0
ciphertext_output_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
```

This evidence records local execution of OpenSSL EVP ML-KEM key generation,
encapsulation, decapsulation, shared-secret equality, and zeroization for the
three FIPS 203 ML-KEM parameter sets. It is self-test evidence only and does
not claim production readiness, FIPS validation, key storage, secret output,
capability enforcement, or runtime authority.
