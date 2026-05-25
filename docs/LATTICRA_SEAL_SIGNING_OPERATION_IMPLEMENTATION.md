# Latticra Seal Signing Operation Implementation

Status: initial signing operation metadata implementation
Scope: bounded C metadata surface for classifying Seal signing operation eligibility after ready signer invocation metadata. This slice does not add cryptographic signing, signature verification, signer invocation behavior, signer process execution, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal signing operation metadata implementation.

The implementation consumes ready signer invocation metadata and classifies whether the request remains eligible for a future metadata-only signing operation path.

It is signing-operation path classification only.

It does not invoke a signer.

It does not sign.

It does not handle private keys.

## Files

```text
include/latticra/seal_signing_operation.h
src/seal_signing_operation.c
tests/seal_signing_operation_invariants.c
scripts/test-latticra-seal-signing-operation.sh
```

## Required predecessors

This implementation depends on the signing operation contract and the signer invocation metadata surface:

```text
docs/LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
docs/status/SEAL_SIGNER_INVOCATION_STATUS.md
include/latticra/seal_signer_invocation.h
src/seal_signer_invocation.c
tests/seal_signer_invocation_invariants.c
scripts/test-latticra-seal-signing-operation-contract.sh
scripts/test-latticra-seal-signer-invocation-contract.sh
scripts/test-latticra-seal-signer-invocation.sh
scripts/test-latticra-seal-signer-invocation-status.sh
```

## Implemented surface

The signing operation metadata surface adds:

```text
latticra_seal_signing_operation_t
latticra_seal_signing_operation_error_t
latticra_seal_signing_operation_error_label
latticra_seal_signing_operation_from_invocation
latticra_seal_signing_operation_is_metadata_only
latticra_seal_signing_operation_render
```

The implementation:

```text
accepts signer invocation metadata
requires signer_invocation_ready=1
requires signer_invocation_state=invocation-metadata-only
requires requested_signature=Ed25519-development
requires requested_signing_authorization=metadata-only
requires requested_signer_handoff=metadata-only
requires requested_signer_invocation=metadata-only
accepts requested_signing_operation=metadata-only
classifies the result as signing_operation_state=operation-metadata-only
sets signing_operation_ready=1 only for metadata-only allowed signer invocation states
renders deterministic signing operation metadata
fails closed for invalid or denied predecessor metadata
```

Even when signing_operation_ready=1, these fields remain zero:

```text
signature_performed=0
verification_performed=0
signer_invoked=0
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
signing_operation_profile=latticra-seal-signing-operation/0.1
signer_invocation_profile=latticra-seal-signer-invocation/0.1
signer_handoff_profile=latticra-seal-signer-handoff/0.1
signing_authorization_profile=latticra-seal-signing-authorization/0.1
signature_request_profile=latticra-seal-signature-request/0.1
requested_signature=Ed25519-development
requested_signing_authorization=metadata-only
requested_signer_handoff=metadata-only
requested_signer_invocation=metadata-only
requested_signing_operation=metadata-only
signing_authorization_state=authorized-metadata-only
signing_authorization_ready=1
signer_handoff_state=handoff-metadata-only
signer_handoff_ready=1
signer_invocation_state=invocation-metadata-only
signer_invocation_ready=1
signing_operation_state=operation-metadata-only
signing_operation_ready=1
signer_invoked=0
mode=metadata-only
status=signing-operation-metadata
```

## Failure behavior

The implementation fails closed for:

```text
null output
null signer invocation
invalid signer invocation
signer_invocation_ready=0
signer_invocation_state not invocation-metadata-only
requested_signer_invocation not metadata-only
signer_handoff_ready=0
signer_handoff_state not handoff-metadata-only
requested_signer_handoff not metadata-only
signing_authorization_ready=0
signing_authorization_state not authorized-metadata-only
requested_signing_authorization not metadata-only
missing requested signature
unknown requested signature
missing requested signing operation
unknown requested signing operation
private-key handling already present
key generation already present
trust-store loading already present
revocation lookup already present
runtime authority already granted
signature already performed
verification already performed
signer already invoked
handoff already performed
effect already performed
host read already performed
host write already performed
network already performed
small render buffer
```

Failures do not sign, verify signatures, invoke a signer, handle private keys, generate keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform runtime handoff, persist policy, or grant runtime authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signing-operation-contract.sh
sh scripts/test-latticra-seal-signing-operation.sh
```

Expected output:

```text
seal signing operation contract: ok
seal signing operation invariants: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is public-key parsing status/public-entry alignment or another narrow status/index alignment follow-up that still must not add signing without a separate implementation contract, key-handling contract, key-material contract, and guards.

The signing operation metadata implementation and its status/public-entry checkpoint are guarded checkpoints. Future work must not add private-key handling, signing, verification, signer invocation behavior, trust-store behavior, revocation lookup, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately implemented and guarded.
