# Latticra Seal Crypto Verify Backend Contract

Status: Latticra Seal crypto verify backend contract
Scope: contract for future cryptographic verification backend behavior after signature metadata, verification policy metadata, verification receipt metadata, and capability gate metadata. This document does not implement cryptographic verification, signing, key generation, private-key storage, public-key trust stores, network trust lookup, revocation lookup, object sealing, capability enforcement, runtime authority, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal crypto verify backend layer.

The purpose of this layer is to introduce a bounded, verify-only cryptographic boundary that can later verify signature material without immediately granting capability, effect, or runtime authority.

This document does not implement cryptographic verification.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
include/latticra/seal_manifest.h
include/latticra/seal_signature.h
include/latticra/seal_verification_policy.h
include/latticra/seal_verification_receipt.h
include/latticra/seal_capability_gate.h
src/seal_manifest.c
src/seal_signature.c
src/seal_verification_policy.c
src/seal_verification_receipt.c
src/seal_capability_gate.c
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature.sh
scripts/test-latticra-seal-verification-policy.sh
scripts/test-latticra-seal-verification-receipt.sh
scripts/test-latticra-seal-capability-gate.sh
```

The verification receipt metadata surface remains the authority boundary until a later verified receipt implementation explicitly consumes cryptographic verification results.

## Backend boundary

The crypto verify backend may only evaluate verification input and produce bounded verification-result metadata.

A successful verification result may not directly grant authority.

A failed verification result must fail closed.

Allowed in this contract slice:

```text
verification backend vocabulary
algorithm labels
verification input metadata planning
verification result-state planning
public-key identity metadata planning
trust-source metadata planning
failure-state planning
promotion rules
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
cryptographic verification implementation
signature generation
private-key handling
key generation
network trust lookup
revocation lookup
public-key trust store loading
capability enforcement
effect execution
runtime authority grants
host reads
host writes
kernel interaction
```

## Planned algorithm policy

Initial planned verification families:

```text
Ed25519-development for local development verification
ML-DSA-planned for future post-quantum signature verification
SLH-DSA-planned for future conservative offline/root signature verification
```

No custom cryptographic primitive may be introduced.

The first implementation after this contract may only add backend metadata and unsupported verification-state handling unless a separate implementation contract authorizes real Ed25519 verification.

## Planned verification states

Future records should use explicit labels:

```text
crypto_verify_state=unsupported
crypto_verify_state=unverified-metadata
crypto_verify_state=verified
crypto_verify_state=invalid-signature
crypto_verify_state=unsupported-algorithm
crypto_verify_state=missing-public-key
crypto_verify_state=policy-denied
```

For the next metadata implementation, the expected state is:

```text
crypto_verify_state=unsupported
```

## Planned fields

A future crypto verification backend record should be bounded and deterministic.

Planned fields:

```text
backend_profile
signature_profile
manifest_profile
artifact_digest_algorithm
artifact_digest_hex
signer_identity_label
signature_algorithm
public_key_identity_label
trust_source
crypto_verify_state
cryptographic_verification_supported
cryptographic_verification_performed
verified
invalid
authority_usable
capability_gate_allowed
runtime_authority_granted
status
```

Initial values before real verification:

```text
crypto_verify_state=unsupported
cryptographic_verification_supported=0
cryptographic_verification_performed=0
verified=0
invalid=0
authority_usable=0
capability_gate_allowed=0
runtime_authority_granted=0
status=crypto-verify-backend-contract-only
```

## Failure behavior

Future crypto verify backend handling must fail closed.

Required failure states:

```text
null backend output -> invalid
null signature metadata -> invalid
invalid signature metadata -> invalid
missing artifact digest -> invalid
missing signer identity -> invalid
missing public-key identity -> invalid
unsupported algorithm -> unsupported-algorithm
verification requested before support -> unsupported
authority request -> rejected
capability gate request -> rejected
runtime authority request -> rejected
```

Failures must not create keys, store keys, contact networks, query revocation status, sign records, write host files, enforce capabilities, perform effects, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
crypto verification backend metadata implementation
```

It does not permit real cryptographic verification, key handling, trust-store behavior, revocation lookup, object sealing, capability enforcement, network behavior, host reads, host writes, or runtime authority.

After crypto verification backend metadata exists and is guarded, the next valid planning slice is an Ed25519 verify-only implementation contract.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-crypto-verify-backend-contract.sh
```
