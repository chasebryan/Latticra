# Latticra Seal Signing Authorization Implementation

Status: initial signing authorization metadata implementation
Scope: bounded C metadata surface for classifying Seal signing authorization after ready signature request metadata. This slice does not add signing, signature verification, key generation, private-key handling, trust-store loading, revocation lookup, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, object sealing, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal signing authorization metadata implementation.

The implementation consumes ready signature request metadata and classifies whether the request remains eligible for a future metadata-only signing path.

It is signing-path classification only.

It does not sign.

## Files

```text
include/latticra/seal_signing_authorization.h
src/seal_signing_authorization.c
tests/seal_signing_authorization_invariants.c
scripts/test-latticra-seal-signing-authorization.sh
```

## Required predecessors

This implementation depends on the signing authorization contract and the signature request metadata surface:

```text
docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md
docs/LATTICRA_SEAL_SIGNATURE_REQUEST_IMPLEMENTATION.md
docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md
include/latticra/seal_signature_request.h
src/seal_signature_request.c
tests/seal_signature_request_invariants.c
scripts/test-latticra-seal-signature-request-contract.sh
scripts/test-latticra-seal-signature-request.sh
scripts/test-latticra-seal-signature-request-status.sh
```

## Implemented surface

The signing authorization metadata surface adds:

```text
latticra_seal_signing_authorization_t
latticra_seal_signing_authorization_error_t
latticra_seal_signing_authorization_error_label
latticra_seal_signing_authorization_from_request
latticra_seal_signing_authorization_is_metadata_only
latticra_seal_signing_authorization_render
```

The implementation:

```text
accepts signature request metadata
requires signature_request_ready=1
requires signature_request_state=requested-metadata-only
requires requested_signature=Ed25519-development
accepts requested_signing_authorization=metadata-only
classifies the result as signing_authorization_state=authorized-metadata-only
sets signing_authorization_ready=1 only for metadata-only allowed request states
renders deterministic signing authorization metadata
fails closed for invalid or denied predecessor metadata
```

Even when signing_authorization_ready=1, these fields remain zero:

```text
signature_performed=0
verification_performed=0
private_key_handling=0
key_generation_performed=0
trust_store_loaded=0
revocation_lookup_performed=0
handoff_performed=0
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Current metadata output

The successful metadata path renders:

```text
signing_authorization_profile=latticra-seal-signing-authorization/0.1
signature_request_profile=latticra-seal-signature-request/0.1
requested_signature=Ed25519-development
requested_signing_authorization=metadata-only
signature_request_state=requested-metadata-only
signature_request_ready=1
signing_authorization_state=authorized-metadata-only
signing_authorization_ready=1
mode=metadata-only
status=signing-authorization-metadata
```

## Failure behavior

The implementation fails closed for:

```text
null output
null signature request
invalid signature request
signature_request_ready=0
signature_request_state not requested-metadata-only
missing requested signature
unknown requested signature
missing requested signing authorization
unknown requested signing authorization
private-key handling already present
runtime authority already granted
signature already performed
verification already performed
handoff already performed
effect already performed
host read already performed
host write already performed
network already performed
small render buffer
```

Failures do not sign, verify signatures, handle private keys, generate keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform handoff, persist policy, or grant runtime authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signing-authorization-contract.sh
sh scripts/test-latticra-seal-signing-authorization.sh
```

Expected output:

```text
seal signing authorization contract: ok
seal signing authorization invariants: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is signer invocation metadata implementation or a narrow status-index alignment follow-up.

That future slice must not add private-key handling, signing, verification, trust-store behavior, revocation lookup, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately contracted, implemented, and guarded.
