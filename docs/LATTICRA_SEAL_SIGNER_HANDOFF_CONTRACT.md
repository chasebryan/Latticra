# Latticra Seal Signer Handoff Contract

Status: Latticra Seal signer handoff contract
Scope: contract for a future metadata-only signer handoff surface after Seal signing authorization metadata. This document does not implement signing, signature verification, signer invocation, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal signer handoff boundary after ready signing authorization metadata.

The purpose of this layer is to decide whether a ready metadata-only signing authorization may be represented as eligible for a future signer handoff before any signer, private key, trust store, runtime bridge, host authority, or signature generation exists.

The signer handoff surface is signer-path classification, not signing, not verification, not signer invocation, and not runtime handoff.

This document does not implement signing.

## Relationship to runtime handoff

Latticra Seal already has runtime handoff planning and metadata surfaces for effect and runtime-boundary posture:

```text
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md
```

Those surfaces describe runtime-boundary posture for effect decisions.

This signer handoff contract is separate. It starts from signing authorization metadata and describes only a future signer-path handoff record. It does not route to runtime behavior, invoke a signer, perform signing, handle private keys, verify signatures, persist policy, or grant runtime authority.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md
docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md
include/latticra/seal_signing_authorization.h
src/seal_signing_authorization.c
tests/seal_signing_authorization_invariants.c
scripts/test-latticra-seal-signing-authorization-contract.sh
scripts/test-latticra-seal-signing-authorization.sh
scripts/test-latticra-seal-signing-authorization-status.sh
```

The signing authorization metadata surface remains the source of readiness evidence for this signer handoff surface.

## Signer handoff boundary

Allowed in the next implementation slice:

```text
accept signing authorization metadata
require signing_authorization_ready=1
require signing_authorization_state=authorized-metadata-only
require requested_signature=Ed25519-development
require requested_signing_authorization=metadata-only
require signature_performed=0
require verification_performed=0
require private_key_handling=0
require key_generation_performed=0
require trust_store_loaded=0
require revocation_lookup_performed=0
require handoff_performed=0
require effect_performed=0
require runtime_authority_granted=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested signer handoff metadata
classify metadata-only as signer_handoff_state=handoff-metadata-only
produce deterministic signer handoff metadata
```

Forbidden in the next implementation slice:

```text
cryptographic signing
signature verification
signer process invocation
private-key handling
key generation
trust-store loading
revocation lookup
runtime handoff execution
runtime authority grants
host reads
host writes
network access
shell execution
tool execution
capability enforcement
policy persistence
object sealing
kernel interaction
```

## Initial handoff policy

Allowed input signing authorization state:

```text
signing_authorization_state=authorized-metadata-only
```

Allowed requested signature label:

```text
Ed25519-development
```

Allowed requested signing authorization label:

```text
metadata-only
```

Allowed requested signer handoff label:

```text
metadata-only
```

These labels are metadata labels only. They do not mean Ed25519 signing, Ed25519 verification, signer invocation, key generation, private-key handling, trust establishment, runtime handoff, host behavior, network behavior, or capability enforcement exists in this path.

Planned signer handoff states:

```text
signer_handoff_state=handoff-metadata-only
signer_handoff_state=denied-signing-authorization
signer_handoff_state=denied-signature-algorithm
signer_handoff_state=denied-signer-handoff
signer_handoff_state=denied-private-key
signer_handoff_state=denied-runtime-authority
signer_handoff_state=denied-host-effect
signer_handoff_state=denied-network-effect
```

The first implementation may set:

```text
signer_handoff_ready=1
```

only for ready metadata-only signing authorization, the allowed development signature label, and the metadata-only signer handoff label.

Even when signer_handoff_ready=1, these must remain zero:

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

## Planned fields

A future signer handoff record should be bounded and deterministic.

Planned fields:

```text
signer_handoff_profile
signing_authorization_profile
signature_request_profile
envelope_profile
report_profile
handoff_profile
decision_profile
gate_profile
receipt_profile
verify_profile
message_digest_algorithm
message_digest_hex
public_key_identity_label
requested_capability
requested_effect
requested_handoff
requested_report
requested_envelope
requested_signature
requested_signing_authorization
requested_signer_handoff
requested_scope
signing_authorization_state
signing_authorization_ready
signer_handoff_state
signer_handoff_ready
signature_performed
verification_performed
signer_invoked
private_key_handling
key_generation_performed
trust_store_loaded
revocation_lookup_performed
handoff_performed
effect_performed
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
mode
status
```

Expected values for an allowed first implementation result:

```text
signer_handoff_profile=latticra-seal-signer-handoff/0.1
requested_signer_handoff=metadata-only
signer_handoff_state=handoff-metadata-only
signer_handoff_ready=1
signature_performed=0
verification_performed=0
signer_invoked=0
private_key_handling=0
key_generation_performed=0
trust_store_loaded=0
revocation_lookup_performed=0
runtime_authority_granted=0
mode=metadata-only
status=signer-handoff-metadata
```

## Failure behavior

Future signer handoff handling must fail closed.

Required failure states:

```text
null output -> invalid
null signing authorization -> invalid
invalid signing authorization -> denied-signing-authorization
signing_authorization_ready=0 -> denied-signing-authorization
signing_authorization_state not authorized-metadata-only -> denied-signing-authorization
missing requested signature -> denied-signature-algorithm
unknown requested signature -> denied-signature-algorithm
missing requested signer handoff -> denied-signer-handoff
unknown requested signer handoff -> denied-signer-handoff
private-key handling requested or observed -> denied-private-key
key generation requested or observed -> denied-private-key
trust-store loading requested or observed -> denied-private-key
revocation lookup requested or observed -> denied-network-effect
signature already performed -> denied-host-effect
verification already performed -> denied-host-effect
signer already invoked -> denied-host-effect
runtime authority already granted -> denied-runtime-authority
handoff already performed -> denied-host-effect
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
```

Failures must not sign, verify signatures, invoke a signer, handle private keys, generate keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform runtime handoff, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
signer handoff metadata implementation
```

It does not permit cryptographic signing, signature verification, signer invocation, private-key handling, key generation, trust-store behavior, revocation lookup, runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, object sealing, or kernel behavior.

After signer handoff metadata, its status/public-entry checkpoint, the signer invocation contract, the signer invocation metadata implementation, signer invocation status/public-entry alignment, the signing operation contract, signing operation metadata implementation, signing operation status/public-entry alignment, the key-handling boundary contract, key-handling metadata implementation, key-handling status/public-entry alignment, the key-material boundary contract, and key-material metadata implementation exist and are guarded, the next valid planning slice is public-key parsing boundary contract or another narrow status/index alignment follow-up that still must not add signing without separate implementation, key-handling, key-material, and guard contracts.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-signer-handoff-contract.sh
```
