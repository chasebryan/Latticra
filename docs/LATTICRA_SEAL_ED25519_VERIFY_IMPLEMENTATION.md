# Latticra Seal Ed25519 Verify-Only Implementation

Status: initial Ed25519 verify-only local implementation
Scope: provider-backed local Ed25519 verification result surface after the Ed25519 verify-only contract.

## Purpose

This document records the first local Ed25519 verify-only implementation for Latticra Seal.

The implementation accepts caller-supplied message bytes, caller-supplied public key bytes, caller-supplied signature bytes, and an existing crypto verify backend metadata record.

It produces bounded verification result metadata.

## Added files

```text
include/latticra/seal_ed25519_verify.h
src/seal_ed25519_verify.c
tests/seal_ed25519_verify_invariants.c
scripts/test-latticra-seal-ed25519-verify.sh
```

## Provider boundary

The implementation uses OpenSSL EVP Ed25519 verification and does not implement custom curve arithmetic.

The test runner links with:

```text
-lcrypto
```

## Behavior

The implementation:

```text
accepts a valid crypto verify backend metadata record
accepts Ed25519-development as the only supported algorithm label
accepts caller-supplied message bytes
accepts caller-supplied 32-byte Ed25519 public key bytes
accepts caller-supplied 64-byte Ed25519 signature bytes
computes a SHA-256 digest of the message for reporting
calls the OpenSSL EVP Ed25519 verify provider
records crypto_verify_state=verified on success
records crypto_verify_state=invalid-signature on signature failure
renders deterministic verification result metadata
```

## Authority boundary

A successful verification result remains authority-neutral.

These fields remain zero:

```text
authority_usable=0
capability_gate_allowed=0
runtime_authority_granted=0
```

## Validation

Run locally:

```sh
sh scripts/test-latticra-seal-ed25519-verify.sh
```

Expected output:

```text
seal ed25519 verify invariants: ok
```

## Next valid slice

The next valid Latticra Seal slice is verified receipt promotion from a successful verify-only result.
