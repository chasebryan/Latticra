# Latticra Seal Public-Key Parsing Implementation

Status: initial public-key parsing metadata implementation
Scope: bounded C metadata surface for classifying Seal public-key parsing eligibility after ready key-material metadata. This slice does not add public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store loading, revocation lookup, cryptographic signing, signature verification, signer invocation behavior, signer process execution, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal public-key parsing metadata implementation.

The implementation consumes ready key-material metadata and classifies whether the request remains eligible for a future metadata-only public-key parsing path.

It is public-key parsing path classification only.

It does not parse public keys.

It does not load key material.

It does not handle private keys.

It does not sign.

It does not verify signatures.

## Files

```text
include/latticra/seal_public_key_parsing.h
src/seal_public_key_parsing.c
tests/seal_public_key_parsing_invariants.c
scripts/test-latticra-seal-public-key-parsing.sh
```

## Required predecessors

This implementation depends on the public-key parsing boundary contract and the key-material metadata surface:

```text
docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
docs/LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md
docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
docs/status/SEAL_KEY_MATERIAL_STATUS.md
include/latticra/seal_key_material.h
src/seal_key_material.c
tests/seal_key_material_invariants.c
scripts/test-latticra-seal-public-key-parsing-contract.sh
scripts/test-latticra-seal-key-material-contract.sh
scripts/test-latticra-seal-key-material.sh
scripts/test-latticra-seal-key-material-status.sh
```

## Implemented surface

The public-key parsing metadata surface adds:

```text
latticra_seal_public_key_parsing_t
latticra_seal_public_key_parsing_error_t
latticra_seal_public_key_parsing_error_label
latticra_seal_public_key_parsing_from_key_material
latticra_seal_public_key_parsing_is_metadata_only
latticra_seal_public_key_parsing_render
```

The implementation:

```text
accepts key-material metadata
requires key_material_ready=1
requires key_material_state=key-material-metadata-only
requires requested_signature=Ed25519-development
requires requested_signing_authorization=metadata-only
requires requested_signer_handoff=metadata-only
requires requested_signer_invocation=metadata-only
requires requested_signing_operation=metadata-only
requires requested_key_handling=metadata-only
requires requested_key_material=metadata-only
accepts requested_public_key_parsing=metadata-only
classifies the result as public_key_parsing_state=public-key-parsing-metadata-only
sets public_key_parsing_ready=1 only for metadata-only allowed key-material states
renders deterministic public-key parsing metadata
fails closed for invalid or denied predecessor metadata
```

Even when public_key_parsing_ready=1, these fields remain zero:

```text
signature_performed=0
verification_performed=0
signer_invoked=0
public_key_parsed=0
key_material_loaded=0
private_key_handling=0
key_generation_performed=0
hardware_key_used=0
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
public_key_parsing_profile=latticra-seal-public-key-parsing/0.1
key_material_profile=latticra-seal-key-material/0.1
key_handling_profile=latticra-seal-key-handling/0.1
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
requested_key_handling=metadata-only
requested_key_material=metadata-only
requested_public_key_parsing=metadata-only
signing_authorization_state=authorized-metadata-only
signing_authorization_ready=1
signer_handoff_state=handoff-metadata-only
signer_handoff_ready=1
signer_invocation_state=invocation-metadata-only
signer_invocation_ready=1
signing_operation_state=operation-metadata-only
signing_operation_ready=1
key_handling_state=key-handling-metadata-only
key_handling_ready=1
key_material_state=key-material-metadata-only
key_material_ready=1
public_key_parsing_state=public-key-parsing-metadata-only
public_key_parsing_ready=1
public_key_parsed=0
key_material_loaded=0
hardware_key_used=0
mode=metadata-only
status=public-key-parsing-metadata
```

## Failure behavior

The implementation fails closed for:

```text
null output
null key material
invalid key material
key_material_ready=0
key_material_state not key-material-metadata-only
requested_key_material not metadata-only
key_handling_ready=0
key_handling_state not key-handling-metadata-only
requested_key_handling not metadata-only
signing_operation_ready=0
signing_operation_state not operation-metadata-only
requested_signing_operation not metadata-only
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
missing requested public-key parsing
unknown requested public-key parsing
public-key parsing request
key material loading request
private-key handling request
key generation request
hardware-key use request
trust-store loading request
revocation lookup request
public-key parsing already present
key material loading already present
private-key handling already present
key generation already present
hardware-key use already present
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

Failures do not sign, verify signatures, invoke a signer, parse public keys, load key material, handle private keys, generate keys, use hardware keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform runtime handoff, persist policy, or grant runtime authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-public-key-parsing-contract.sh
sh scripts/test-latticra-seal-public-key-parsing.sh
```

Expected output:

```text
seal public-key parsing contract: ok
seal public-key parsing invariants: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is public-key parsing status/public-entry alignment or another narrow status/index alignment follow-up that still must not add public-key parsing without separate public-key parsing, key-material, and guard contracts.

The public-key parsing metadata implementation is a guarded checkpoint. Future work must not add public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, revocation lookup, signing, verification, signer invocation behavior, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately implemented and guarded.
