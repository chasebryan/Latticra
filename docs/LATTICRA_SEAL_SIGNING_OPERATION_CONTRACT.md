# Latticra Seal Signing Operation Contract

Status: Latticra Seal signing operation contract
Scope: contract for a future metadata-only signing operation surface after Seal signer invocation metadata. This document does not implement cryptographic signing, signature verification, signer invocation behavior, signer process execution, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal signing operation boundary after ready signer invocation metadata.

The purpose of this layer is to decide whether a ready metadata-only signer invocation record may be represented as eligible for a future metadata-only signing operation request before any private key, signer process, trust store, runtime bridge, host authority, or signature generation exists.

The signing operation surface is signing-operation path classification, not signing, not verification, not signer invocation, and not runtime handoff.

This document does not sign.

This document does not handle private keys.

## Relationship to signer invocation

Latticra Seal signer invocation metadata already records a no-effect eligibility checkpoint for the future signer path:

```text
docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
docs/status/SEAL_SIGNER_INVOCATION_STATUS.md
```

This signing operation contract starts from that checkpoint. It does not replace signer invocation metadata, route to runtime behavior, invoke a signer, perform signing, handle private keys, verify signatures, persist policy, or grant runtime authority.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
docs/status/SEAL_SIGNER_INVOCATION_STATUS.md
include/latticra/seal_signer_invocation.h
src/seal_signer_invocation.c
tests/seal_signer_invocation_invariants.c
scripts/test-latticra-seal-signer-invocation-contract.sh
scripts/test-latticra-seal-signer-invocation.sh
scripts/test-latticra-seal-signer-invocation-status.sh
```

The signer invocation metadata surface remains the source of readiness evidence for this signing operation surface.

## Signing operation boundary

Allowed in the next implementation slice:

```text
accept signer invocation metadata
require signer_invocation_ready=1
require signer_invocation_state=invocation-metadata-only
require requested_signature=Ed25519-development
require requested_signing_authorization=metadata-only
require requested_signer_handoff=metadata-only
require requested_signer_invocation=metadata-only
require signature_performed=0
require verification_performed=0
require signer_invoked=0
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
accept requested signing operation metadata
classify metadata-only as signing_operation_state=operation-metadata-only
produce deterministic signing operation metadata
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

## Initial operation policy

Allowed signer invocation state:

```text
signer_invocation_state=invocation-metadata-only
```

Allowed requested signer invocation label:

```text
metadata-only
```

Allowed requested signing operation label:

```text
metadata-only
```

These labels are metadata labels only. They do not mean Ed25519 signing, Ed25519 verification, signer invocation, key generation, private-key handling, trust establishment, runtime handoff, host behavior, network behavior, or capability enforcement exists in this path.

Planned signing operation states:

```text
signing_operation_state=operation-metadata-only
signing_operation_state=denied-signer-invocation
signing_operation_state=denied-signer-handoff
signing_operation_state=denied-signing-authorization
signing_operation_state=denied-signature-algorithm
signing_operation_state=denied-signing-operation
signing_operation_state=denied-private-key
signing_operation_state=denied-runtime-authority
signing_operation_state=denied-host-effect
signing_operation_state=denied-network-effect
```

The first implementation may set:

```text
signing_operation_ready=1
```

only for ready metadata-only signer invocation metadata, the allowed development signature label, the metadata-only signer invocation label, and the metadata-only signing operation label.

Even when signing_operation_ready=1, these must remain zero:

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

A future signing operation record should be bounded and deterministic.

Planned fields:

```text
signing_operation_profile
signer_invocation_profile
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
requested_signer_invocation
requested_signing_operation
requested_scope
signing_authorization_state
signing_authorization_ready
signer_handoff_state
signer_handoff_ready
signer_invocation_state
signer_invocation_ready
signing_operation_state
signing_operation_ready
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
signing_operation_profile=latticra-seal-signing-operation/0.1
signer_invocation_profile=latticra-seal-signer-invocation/0.1
requested_signing_operation=metadata-only
signing_operation_state=operation-metadata-only
signing_operation_ready=1
signature_performed=0
verification_performed=0
signer_invoked=0
private_key_handling=0
key_generation_performed=0
trust_store_loaded=0
revocation_lookup_performed=0
runtime_authority_granted=0
mode=metadata-only
status=signing-operation-metadata
```

## Failure behavior

Future signing operation handling must fail closed.

Required failure states:

```text
null output -> invalid
null signer invocation -> invalid
invalid signer invocation -> denied-signer-invocation
signer_invocation_ready=0 -> denied-signer-invocation
signer_invocation_state not invocation-metadata-only -> denied-signer-invocation
requested_signer_invocation not metadata-only -> denied-signer-invocation
signer_handoff_ready=0 -> denied-signer-handoff
signer_handoff_state not handoff-metadata-only -> denied-signer-handoff
requested_signer_handoff not metadata-only -> denied-signer-handoff
requested_signing_authorization not metadata-only -> denied-signing-authorization
missing requested signature -> denied-signature-algorithm
unknown requested signature -> denied-signature-algorithm
missing requested signing operation -> denied-signing-operation
unknown requested signing operation -> denied-signing-operation
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
signing operation metadata implementation
```

It does not permit cryptographic signing, signature verification, signer invocation behavior, private-key handling, key generation, trust-store behavior, revocation lookup, runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, object sealing, or kernel behavior.

After signing operation metadata, its status/public-entry checkpoint, the key-handling boundary contract, key-handling metadata implementation, key-handling status/public-entry alignment, the key-material boundary contract, and key-material metadata implementation exist and are guarded, the next valid planning slice is public-key parsing metadata implementation or another narrow status/index alignment follow-up that still must not add signing without a separate implementation contract, key-handling contract, key-material contract, and guards.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-signing-operation-contract.sh
```
