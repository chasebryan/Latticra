# Latticra Seal Verified Receipt Promotion Contract

Status: Latticra Seal verified receipt promotion contract
Scope: contract for a future metadata promotion step after Ed25519 verify-only local verification. This document does not implement verified receipt promotion, capability authorization, effect execution, runtime authority, signing, key generation, private-key storage, trust-store loading, network lookup, revocation lookup, object sealing, host effects, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the verified receipt promotion boundary for Latticra Seal.

The purpose of this layer is to convert a successful local verify-only result into a bounded verified receipt record without granting authority.

The promotion is evidence promotion, not permission promotion.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md
docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md
docs/LATTICRA_SEAL_ED25519_VERIFY_ONLY_CONTRACT.md
docs/LATTICRA_SEAL_ED25519_VERIFY_IMPLEMENTATION.md
include/latticra/seal_verification_receipt.h
include/latticra/seal_crypto_verify_backend.h
include/latticra/seal_ed25519_verify.h
src/seal_verification_receipt.c
src/seal_crypto_verify_backend.c
src/seal_ed25519_verify.c
tests/seal_verification_receipt_invariants.c
tests/seal_crypto_verify_backend_invariants.c
tests/seal_ed25519_verify_invariants.c
scripts/test-latticra-seal-verification-receipt.sh
scripts/test-latticra-seal-ed25519-verify.sh
```

The Ed25519 verify-only result is the only allowed input source for the first promotion implementation.

## Promotion boundary

Allowed in the next implementation slice:

```text
accept a valid Ed25519 verify-only result
require cryptographic_verification_supported=1
require cryptographic_verification_performed=1
require verified=1
require invalid=0
require crypto_verify_state=verified
copy message digest metadata
copy public-key identity metadata
copy signature algorithm metadata
copy trust-source metadata
set receipt_state=verified
set verification_state=verified
render deterministic verified receipt metadata
```

Forbidden in the next implementation slice:

```text
capability authorization
effect execution
runtime authority grants
host reads
host writes
network lookup
revocation lookup
trust-store loading
signature generation
key generation
private-key handling
object sealing
kernel interaction
```

## Authority boundary

A promoted verified receipt remains authority-neutral.

The future implementation may set:

```text
verified=1
cryptographic_verification_supported=1
cryptographic_verification_performed=1
receipt_state=verified
verification_state=verified
```

The future implementation must keep these zero:

```text
authority_usable=0
capability_gate_allowed=0
runtime_authority_granted=0
```

A verified receipt may become usable by a later capability gate only after a separate contract explicitly permits that behavior.

## Planned fields

A future verified receipt promotion record should be bounded and deterministic.

Planned fields:

```text
receipt_profile
verify_profile
backend_profile
verification_policy_profile
message_label
message_size_bytes
message_digest_algorithm
message_digest_hex
public_key_identity_label
signature_algorithm
trust_source
verification_state
receipt_state
cryptographic_verification_supported
cryptographic_verification_performed
verified
invalid
authority_usable
capability_gate_allowed
runtime_authority_granted
status
```

## Failure behavior

Future verified receipt promotion must fail closed.

Required failure states:

```text
null output -> invalid
null verify result -> invalid
unsupported verification -> rejected
verification not performed -> rejected
verified=0 -> rejected
invalid=1 -> rejected
crypto_verify_state not verified -> rejected
missing message digest -> rejected
missing public-key identity -> rejected
runtime authority request -> rejected
capability authorization request -> rejected
```

Failures must not create keys, store keys, contact networks, query revocation status, sign records, read host files, write host files, enforce capabilities, perform effects, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
verified receipt promotion metadata implementation
```

It does not permit capability authorization, effect execution, runtime authority, key handling, trust-store behavior, revocation lookup, network behavior, host effects, or kernel behavior.

After verified receipt promotion exists and is guarded, the next valid planning slice is capability gate evaluation of a verified but authority-neutral receipt.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-verified-receipt-promotion-contract.sh
```
