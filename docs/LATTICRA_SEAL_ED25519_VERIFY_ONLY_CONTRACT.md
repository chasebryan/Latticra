# Latticra Seal Ed25519 Verify-Only Contract

Status: Latticra Seal Ed25519 verify-only implementation contract
Scope: contract for a future Ed25519 verify-only implementation after the crypto verify backend metadata surface. This document does not implement verification. It does not implement signing, key generation, private-key storage, public-key trust stores, network lookup, revocation lookup, object sealing, capability enforcement, runtime authority, host effects, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first real cryptographic operation that may become valid inside Latticra Seal: local Ed25519 signature verification.

The purpose of this layer is narrow:

```text
caller-supplied manifest bytes
caller-supplied Ed25519 public key bytes
caller-supplied Ed25519 signature bytes
local verify-only operation
bounded verification result metadata
```

A successful Ed25519 verification result may not directly grant capability, effect, or runtime authority.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md
include/latticra/seal_crypto_verify_backend.h
src/seal_crypto_verify_backend.c
tests/seal_crypto_verify_backend_invariants.c
include/latticra/seal_verification_policy.h
src/seal_verification_policy.c
include/latticra/seal_signature.h
src/seal_signature.c
```

The crypto verify backend metadata surface remains the source of truth until a separate implementation slice adds actual Ed25519 verification.

## Verify-only boundary

Allowed in the next implementation slice:

```text
accept caller-supplied message bytes
accept caller-supplied Ed25519 public key bytes
accept caller-supplied Ed25519 signature bytes
validate bounded input lengths
call a reviewed Ed25519 verification provider
record verification attempted
record verification success or failure
render deterministic verification result metadata
```

Forbidden in the next implementation slice:

```text
signature generation
private-key input
private-key storage
key generation
custom curve math
network lookup
revocation lookup
trust-store loading
capability enforcement
effect execution
host reads
host writes
runtime authority grants
kernel interaction
```

## Primitive policy

The implementation must use Ed25519 verification only.

Required labels:

```text
signature_algorithm=Ed25519-development
crypto_verify_state=verified
crypto_verify_state=invalid-signature
crypto_verify_state=unsupported-algorithm
```

No custom cryptographic primitive may be introduced.

The implementation must not contain handwritten Ed25519 curve arithmetic. It must use a reviewed provider boundary selected in the implementation plan.

## Planned input policy

The future implementation should use bounded input records.

Planned constants:

```text
ed25519_public_key_bytes=32
ed25519_signature_bytes=64
message_size_max=65536
```

Planned input fields:

```text
message_label
message_size_bytes
message_digest_algorithm
message_digest_hex
public_key_identity_label
public_key_size_bytes
signature_algorithm
signature_size_bytes
trust_source
```

## Planned result fields

A future Ed25519 verify-only result should be bounded and deterministic.

Planned fields:

```text
ed25519_verify_profile
backend_profile
verification_policy_profile
message_label
message_size_bytes
message_digest_algorithm
message_digest_hex
public_key_identity_label
public_key_size_bytes
signature_algorithm
signature_size_bytes
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

A successful verification result may set:

```text
cryptographic_verification_supported=1
cryptographic_verification_performed=1
verified=1
invalid=0
crypto_verify_state=verified
```

Even after success, these must remain zero:

```text
authority_usable=0
capability_gate_allowed=0
runtime_authority_granted=0
```

A failed verification result must set:

```text
cryptographic_verification_supported=1
cryptographic_verification_performed=1
verified=0
invalid=1
crypto_verify_state=invalid-signature
```

## Failure behavior

Future Ed25519 verify-only handling must fail closed.

Required failure states:

```text
null output -> invalid
null message -> invalid
empty message -> invalid
message too large -> invalid
null public key -> missing-public-key
wrong public key size -> invalid-public-key-size
null signature -> missing-signature
wrong signature size -> invalid-signature-size
unsupported algorithm -> unsupported-algorithm
provider failure -> verification-provider-failure
private-key input -> rejected
runtime authority request -> rejected
```

Failures must not create keys, store keys, contact networks, query revocation status, sign records, read host files, write host files, enforce capabilities, perform effects, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
Ed25519 verify-only local implementation
```

It does not permit signing, key generation, private-key handling, trust-store behavior, revocation lookup, object sealing, capability enforcement, network behavior, host effects, or runtime authority.

After Ed25519 verify-only implementation exists and is guarded, the next valid planning slice is verified receipt promotion from a successful verify-only result.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-ed25519-verify-only-contract.sh
```
