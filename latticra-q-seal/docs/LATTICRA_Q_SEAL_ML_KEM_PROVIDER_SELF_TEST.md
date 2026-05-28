# Latticra Q-Seal ML-KEM Provider Self-Test

Status: provider-backed ML-KEM self-test implementation
Scope: bounded local OpenSSL EVP self-test for ML-KEM key generation, encapsulation, decapsulation, shared-secret equality, and zeroization. This does not add production crypto claims, FIPS validation claims, key storage, release signing, update signing, receipt signing, network behavior, host authority, capability enforcement, or runtime authority.

## Purpose

This slice adds a true ML-KEM mechanism check to Q-Seal without changing the existing clean-room parameter and readiness gates.

The self-test runs the OpenSSL EVP ML-KEM provider for each FIPS 203 parameter set, verifies that generated and reimported keys remain bound to the requested ML-KEM algorithm identity, reimports the generated public key before encapsulation, verifies that public-key encapsulation and private-key decapsulation recover the same 32-byte shared secret through constant-time equality, verifies through the same constant-time comparison path that a tampered ciphertext decapsulates to a different shared secret, and then zeroizes the internal shared-secret and ciphertext buffers before returning.

## Added Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_provider_self_test.h
latticra-q-seal/src/q_seal_ml_kem_provider_self_test.c
latticra-q-seal/tests/q_seal_ml_kem_provider_self_test_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-self-test.sh
scripts/test-latticra-q-seal-ml-kem-provider-self-test.sh
latticra-q-seal/evidence/ML_KEM_PROVIDER_SELF_TEST.md
```

## Current Fields

```text
ml_kem_provider_self_test_present=1
provider=OpenSSL-EVP
standards_source=NIST-FIPS-203
parameter_sets_tested=ML-KEM-512,ML-KEM-768,ML-KEM-1024
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

## Behavior

The self-test:

```text
loads the OpenSSL EVP ML-KEM provider by algorithm name
generates an ephemeral ML-KEM key pair
verifies the generated key pair reports the requested ML-KEM algorithm identity
serializes and reimports the public key before encapsulation
verifies the reimported public key reports the requested ML-KEM algorithm identity
encapsulates through the reimported public key
decapsulates the ciphertext with the generated private key
compares the encapsulated and decapsulated shared secrets using constant-time equality
mutates the ciphertext and verifies through constant-time equality that the tampered decapsulation does not preserve the shared secret
zeroizes shared-secret buffers before returning
zeroizes the local ciphertext buffer before returning
does not return, print, log, or persist shared-secret bytes
does not return, print, log, or persist ciphertext bytes
does not grant authority on success
```

## Boundary

This is a provider self-test and not a production key-establishment API.

It proves the local substrate can execute provider-backed ML-KEM operations through OpenSSL EVP. It does not promote Q-Seal readiness to production runtime crypto, does not store keys, does not emit secrets, does not claim FIPS validation, and does not replace the clean-room review and ACVP evidence gates.

## Validation

```sh
sh scripts/test-latticra-q-seal-ml-kem-provider-self-test.sh
```

Expected output:

```text
latticra q-seal ml-kem provider self-test invariants: ok
latticra q-seal ml-kem provider self-test: ok
```
