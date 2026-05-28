# Latticra Seal Ed25519 Provider Self-Test

Status: provider-backed Ed25519 sign/verify self-test
Scope: local OpenSSL EVP Ed25519 key generation, one-shot signing, public-key-only verification, tamper rejection, and non-authority evidence.

## Evidence Fields

```text
ed25519_provider_self_test_present=1
provider=OpenSSL-EVP
signature_algorithm=Ed25519
standards_source=NIST-FIPS-186-5,RFC-8032,OpenSSL-EVP-Ed25519
operation_scope=local-provider-self-test-no-runtime-authority
provider_linked=1
provider_runtime_used=1
ed25519_key_generation_performed=1
ed25519_public_key_export_performed=1
ed25519_public_key_only_verification_performed=1
ed25519_signature_generation_performed=1
ed25519_signature_verification_performed=1
ed25519_signature_valid=1
ed25519_tampered_message_rejected=1
ed25519_tampered_signature_rejected=1
ed25519_public_key_bytes=32
ed25519_signature_bytes=64
one_shot_sign_api_used=1
one_shot_verify_api_used=1
message_prehashed_before_signing=0
ed25519_private_key_exported=0
ed25519_private_key_output_emitted=0
ed25519_public_key_output_emitted=0
ed25519_signature_output_emitted=0
public_key_buffer_zeroized=1
signature_buffer_zeroized=1
production_crypto_claim_allowed=0
fips_claim_allowed=0
signing_authority_granted=0
key_storage_allowed=0
network_lookup_allowed=0
runtime_authority_granted=0
```

## Boundary

The self-test uses OpenSSL EVP for Ed25519 key generation, one-shot signing, and one-shot verification. It does not implement custom curve arithmetic and does not sign a prehashed message.

The verifier path reconstructs an EVP public-key-only object from the generated public key bytes before checking the signature. The private key remains inside the provider key object, is not exported, is not rendered, and does not grant signing authority.

## Validation

```sh
sh scripts/test-latticra-seal-ed25519-provider-self-test.sh
```
