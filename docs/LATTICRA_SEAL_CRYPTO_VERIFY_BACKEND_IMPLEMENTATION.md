# Latticra Seal Crypto Verify Backend Implementation

Status: crypto verify backend readiness implementation
Scope: bounded C readiness surface for crypto verification backend posture after verification policy metadata. This slice does not perform signature verification itself, signing, key generation, private-key storage, public-key trust stores, network trust lookup, revocation lookup, object sealing, capability enforcement, runtime authority, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the Latticra Seal crypto verify backend readiness implementation.

The implementation accepts an existing verification policy metadata record and produces deterministic crypto verify backend readiness metadata for the local Ed25519 verifier. It does not verify signatures in this backend layer and does not treat readiness metadata as authority.

## Added files

```text
include/latticra/seal_crypto_verify_backend.h
src/seal_crypto_verify_backend.c
tests/seal_crypto_verify_backend_invariants.c
```

The intended local runner is:

```text
scripts/test-latticra-seal-crypto-verify-backend.sh
```

## API summary

The crypto verify backend metadata surface adds:

```text
latticra_seal_crypto_verify_backend_t
latticra_seal_crypto_verify_backend_error_t
latticra_seal_crypto_verify_backend_error_label
latticra_seal_crypto_verify_backend_from_policy
latticra_seal_crypto_verify_backend_is_metadata_only
latticra_seal_crypto_verify_backend_is_authority_neutral
latticra_seal_crypto_verify_backend_report
```

## Backend behavior

The implementation:

```text
accepts a valid verification policy metadata record
copies verification policy profile metadata
copies signature profile metadata
copies manifest profile metadata
copies artifact digest algorithm metadata
copies artifact digest hex metadata
copies signer identity metadata
copies signature algorithm metadata
copies public-key identity metadata
copies trust-source metadata
accepts only the Ed25519-development signature algorithm label
sets crypto_verify_state=ready-local-ed25519
sets cryptographic_verification_supported=1
sets cryptographic_verification_performed=0
sets verified=0
sets invalid=0
sets authority_usable=0
sets capability_gate_allowed=0
sets runtime_authority_granted=0
renders deterministic crypto verify backend metadata
```

## Boundary

This implementation does not verify signatures, parse public keys, create keys, store keys, contact networks, query revocation status, persist verification decisions, seal objects, enforce capabilities, read host files, write host files, execute network behavior, call runtime components, or grant runtime authority.

It is a readiness boundary only. Real Ed25519 signature verification remains in the local provider-backed verify-only layer and now requires this ready backend state before invoking OpenSSL.

## Failure behavior

The implementation fails closed:

```text
null crypto verify backend output -> LATTICRA_STATUS_NULL_ARGUMENT
null verification policy metadata input -> invalid-input
invalid verification policy metadata -> invalid-policy
missing artifact digest -> missing-digest
missing signer identity -> missing-signer
missing public-key identity -> missing-public-key-identity
unsupported algorithm label -> unsupported-algorithm
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not create keys, store secrets, contact networks, verify records, sign records, read host files, write host files, enforce capabilities, perform effects, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
valid verification policy metadata produces deterministic crypto verify backend metadata
backend profile is set
verification policy profile is copied
signature profile is copied
manifest profile is copied
artifact digest algorithm is copied
artifact digest hex is copied
signer identity label is copied
signature algorithm label is copied
public-key identity label is copied
trust source is copied
crypto_verify_state is ready-local-ed25519 for the supported local Ed25519 backend
cryptographic_verification_supported is one before verification
cryptographic_verification_performed remains zero
verified remains zero
invalid remains zero
authority_usable remains zero
capability_gate_allowed remains zero
runtime_authority_granted remains zero
metadata-only helper rejects the ready backend
authority-neutral helper accepts the ready backend
small report buffer fails closed
null inputs fail closed
invalid verification policy metadata fails closed
missing digest fails closed
missing signer fails closed
missing public-key identity fails closed
unsupported algorithm fails closed
```

## Validation

Run locally:

```sh
tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-crypto.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
cc -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude src/seal_crypto_verify_backend.c tests/seal_crypto_verify_backend_invariants.c -o "$tmpdir/latticra-seal-crypto-verify-backend-invariants"
"$tmpdir/latticra-seal-crypto-verify-backend-invariants"
```

Expected output:

```text
seal crypto verify backend invariants: ok
```

## Next valid slice

The next valid Latticra Seal slice is an Ed25519 verify-only implementation contract.

That future slice must be contract-first and must not be added directly to this metadata implementation.
