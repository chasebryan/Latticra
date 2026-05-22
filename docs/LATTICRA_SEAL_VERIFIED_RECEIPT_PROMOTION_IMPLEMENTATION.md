# Latticra Seal Verified Receipt Promotion Implementation

Status: initial verified receipt promotion metadata implementation
Scope: bounded C metadata surface for promoting a successful Ed25519 verify-only result into verified receipt metadata.

## Purpose

This document records the first Latticra Seal verified receipt promotion metadata implementation.

The implementation accepts an existing Ed25519 verify-only result and produces deterministic verified receipt metadata only when the verify-only result is already successful.

The promotion is evidence promotion, not permission promotion.

## Added files

```text
include/latticra/seal_verified_receipt_promotion.h
src/seal_verified_receipt_promotion.c
tests/seal_verified_receipt_promotion_invariants.c
scripts/test-latticra-seal-verified-receipt-promotion.sh
```

## API summary

The verified receipt promotion metadata surface adds:

```text
latticra_seal_verified_receipt_promotion_t
latticra_seal_verified_receipt_promotion_error_t
latticra_seal_verified_receipt_promotion_error_label
latticra_seal_verified_receipt_promotion_from_ed25519_result
latticra_seal_verified_receipt_promotion_is_authority_neutral
latticra_seal_verified_receipt_promotion_report
```

## Promotion behavior

The implementation:

```text
accepts a valid Ed25519 verify-only result
requires cryptographic_verification_supported=1
requires cryptographic_verification_performed=1
requires verified=1
requires invalid=0
requires crypto_verify_state=verified
copies verify profile metadata
copies backend profile metadata
copies verification policy profile metadata
copies message label metadata
copies message size metadata
copies message digest metadata
copies public-key identity metadata
copies signature algorithm metadata
copies trust-source metadata
sets verification_state=verified
sets receipt_state=verified
sets cryptographic_verification_supported=1
sets cryptographic_verification_performed=1
sets verified=1
sets invalid=0
sets authority_usable=0
sets capability_gate_allowed=0
sets runtime_authority_granted=0
renders deterministic verified receipt metadata
```

## Authority boundary

The promoted receipt remains authority-neutral.

These fields remain zero:

```text
authority_usable=0
capability_gate_allowed=0
runtime_authority_granted=0
```

## Failure behavior

The implementation fails closed:

```text
null verified receipt output -> LATTICRA_STATUS_NULL_ARGUMENT
null Ed25519 verify result input -> invalid-input
invalid Ed25519 verify result -> invalid-verify-result
unsupported verification -> unsupported-verification
verification not performed -> verification-not-performed
verified flag not set -> not-verified
invalid flag set -> not-verified
crypto verify state not verified -> invalid-verify-state
missing message digest -> missing-message-digest
missing public-key identity -> missing-public-key-identity
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not create keys, store secrets, contact networks, query revocation status, sign records, read host files, write host files, enforce capabilities, perform effects, or grant runtime authority.

## Validation

Run locally:

```sh
sh scripts/test-latticra-seal-verified-receipt-promotion.sh
```

Expected output:

```text
seal verified receipt promotion invariants: ok
```

## Next valid slice

The next valid Latticra Seal slice is capability gate evaluation of a verified but authority-neutral receipt.
