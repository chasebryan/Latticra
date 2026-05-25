# Latticra Seal Signer Invocation Contract

Status: Latticra Seal signer invocation contract
Scope: contract for a future metadata-only signer invocation surface after Seal signer handoff metadata. This document does not implement signing, signature verification, signer invocation behavior, signer process execution, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal signer invocation boundary after ready signer handoff metadata.

The purpose of this layer is to decide whether a ready metadata-only signer handoff may be represented as eligible for a future signer invocation request before any signer process, private key, trust store, runtime bridge, host authority, or signature generation exists.

The signer invocation surface is signer-invocation path classification, not signer invocation, not signing, not verification, and not runtime handoff.

This document does not invoke a signer.

This document does not implement signing.

## Relationship to signer handoff

Latticra Seal signer handoff metadata already records a no-effect eligibility checkpoint for the future signer path:

```text
docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
docs/status/SEAL_SIGNER_HANDOFF_STATUS.md
```

This signer invocation contract starts from that checkpoint. It does not replace signer handoff, route to runtime behavior, invoke a signer, perform signing, handle private keys, verify signatures, persist policy, or grant runtime authority.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
docs/status/SEAL_SIGNER_HANDOFF_STATUS.md
include/latticra/seal_signer_handoff.h
src/seal_signer_handoff.c
tests/seal_signer_handoff_invariants.c
scripts/test-latticra-seal-signer-handoff-contract.sh
scripts/test-latticra-seal-signer-handoff.sh
scripts/test-latticra-seal-signer-handoff-status.sh
```

The signer handoff metadata surface remains the source of readiness evidence for this signer invocation surface.

## Signer invocation boundary

Allowed in the next implementation slice:

```text
accept signer handoff metadata
require signer_handoff_ready=1
require signer_handoff_state=handoff-metadata-only
require requested_signature=Ed25519-development
require requested_signing_authorization=metadata-only
require requested_signer_handoff=metadata-only
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
accept requested signer invocation metadata
classify metadata-only as signer_invocation_state=invocation-metadata-only
produce deterministic signer invocation metadata
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

## Initial invocation policy

Allowed signer handoff state:

```text
signer_handoff_state=handoff-metadata-only
```

Allowed requested signer handoff label:

```text
metadata-only
```

Allowed requested signer invocation label:

```text
metadata-only
```

These labels are metadata labels only. They do not mean Ed25519 signing, Ed25519 verification, signer invocation, key generation, private-key handling, trust establishment, runtime handoff, host behavior, network behavior, or capability enforcement exists in this path.

Planned signer invocation states:

```text
signer_invocation_state=invocation-metadata-only
signer_invocation_state=denied-signer-handoff
signer_invocation_state=denied-signing-authorization
signer_invocation_state=denied-signature-algorithm
signer_invocation_state=denied-signer-invocation
signer_invocation_state=denied-private-key
signer_invocation_state=denied-runtime-authority
signer_invocation_state=denied-host-effect
signer_invocation_state=denied-network-effect
```

The first implementation may set:

```text
signer_invocation_ready=1
```

only for ready metadata-only signer handoff metadata, the allowed development signature label, the metadata-only signer handoff label, and the metadata-only signer invocation label.

Even when signer_invocation_ready=1, these must remain zero:

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

A future signer invocation record should be bounded and deterministic.

Planned fields:

```text
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
requested_scope
signing_authorization_state
signing_authorization_ready
signer_handoff_state
signer_handoff_ready
signer_invocation_state
signer_invocation_ready
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
signer_invocation_profile=latticra-seal-signer-invocation/0.1
signer_handoff_profile=latticra-seal-signer-handoff/0.1
requested_signer_invocation=metadata-only
signer_invocation_state=invocation-metadata-only
signer_invocation_ready=1
signature_performed=0
verification_performed=0
signer_invoked=0
private_key_handling=0
key_generation_performed=0
trust_store_loaded=0
revocation_lookup_performed=0
runtime_authority_granted=0
mode=metadata-only
status=signer-invocation-metadata
```

## Failure behavior

Future signer invocation handling must fail closed.

Required failure states:

```text
null output -> invalid
null signer handoff -> invalid
invalid signer handoff -> denied-signer-handoff
signer_handoff_ready=0 -> denied-signer-handoff
signer_handoff_state not handoff-metadata-only -> denied-signer-handoff
requested_signer_handoff not metadata-only -> denied-signer-handoff
missing requested signature -> denied-signature-algorithm
unknown requested signature -> denied-signature-algorithm
missing requested signer invocation -> denied-signer-invocation
unknown requested signer invocation -> denied-signer-invocation
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
signer invocation metadata implementation
```

It does not permit cryptographic signing, signature verification, signer invocation behavior, private-key handling, key generation, trust-store behavior, revocation lookup, runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, object sealing, or kernel behavior.

After signer invocation metadata exists and is guarded, the next valid planning slice is signer invocation status/public-entry alignment or a future signing operation contract that still must not add signing without a separate implementation contract, key-handling contract, and guards.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-signer-invocation-contract.sh
```
