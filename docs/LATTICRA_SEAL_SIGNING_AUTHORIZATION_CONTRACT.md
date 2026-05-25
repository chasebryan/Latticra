# Latticra Seal Signing Authorization Contract

Status: Latticra Seal signing authorization contract
Scope: contract for a future metadata-only signing authorization surface after Seal signature request metadata. This document does not implement signing, signature verification, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal signing authorization boundary after ready signature request metadata.

The purpose of this layer is to decide whether a ready metadata-only signature request may be marked as eligible for a future signing path before any signer, private key, trust store, runtime bridge, or host authority exists.

The signing authorization surface is signing-path classification, not signing, not verification, and not runtime authorization.

This document does not implement signing.

## Relationship to existing signature metadata

Latticra Seal already has a manifest-chain signature metadata envelope:

```text
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
include/latticra/seal_signature.h
src/seal_signature.c
tests/seal_signature_invariants.c
scripts/test-latticra-seal-signature.sh
```

That earlier surface records caller-supplied signature metadata for unsigned evidence manifests.

This contract is a separate envelope-chain authorization-planning layer. It starts from ready Seal signature request metadata and does not consume private keys, produce signatures, verify signatures, trust signatures, persist policy, or grant runtime authority.

## Required predecessors

This contract depends on:

```text
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

The signature request metadata surface remains the source of readiness evidence for this signing authorization surface.

## Signing authorization boundary

Allowed in the next implementation slice:

```text
accept signature request metadata
require signature_request_ready=1
require signature_request_state=requested-metadata-only
require requested_signature=Ed25519-development
require signature_performed=0
require verification_performed=0
require private_key_handling=0
require handoff_performed=0
require effect_performed=0
require runtime_authority_granted=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested signing authorization metadata
classify metadata-only as signing_authorization_state=authorized-metadata-only
produce deterministic signing authorization metadata
```

Forbidden in the next implementation slice:

```text
cryptographic signing
signature verification
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

## Initial authorization policy

Allowed input signature request state:

```text
signature_request_state=requested-metadata-only
```

Allowed requested signature label:

```text
Ed25519-development
```

Allowed requested signing authorization label:

```text
metadata-only
```

These labels are metadata labels only. They do not mean Ed25519 signing, Ed25519 verification, key generation, private-key handling, trust establishment, runtime handoff, host behavior, network behavior, or capability enforcement exists in this path.

Planned signing authorization states:

```text
signing_authorization_state=authorized-metadata-only
signing_authorization_state=denied-signature-request
signing_authorization_state=denied-signature-algorithm
signing_authorization_state=denied-authorization-request
signing_authorization_state=denied-private-key
signing_authorization_state=denied-runtime-authority
signing_authorization_state=denied-host-effect
signing_authorization_state=denied-network-effect
```

The first implementation may set:

```text
signing_authorization_ready=1
```

only for ready metadata-only signature requests, the allowed development signature label, and the metadata-only signing authorization label.

Even when signing_authorization_ready=1, these must remain zero:

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

## Planned fields

A future signing authorization record should be bounded and deterministic.

Planned fields:

```text
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
requested_scope
signature_request_state
signature_request_ready
signing_authorization_state
signing_authorization_ready
signature_performed
verification_performed
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
signing_authorization_profile=latticra-seal-signing-authorization/0.1
requested_signing_authorization=metadata-only
signing_authorization_state=authorized-metadata-only
signing_authorization_ready=1
signature_performed=0
verification_performed=0
private_key_handling=0
key_generation_performed=0
trust_store_loaded=0
revocation_lookup_performed=0
runtime_authority_granted=0
mode=metadata-only
status=signing-authorization-metadata
```

## Failure behavior

Future signing authorization handling must fail closed.

Required failure states:

```text
null output -> invalid
null signature request -> invalid
invalid signature request -> denied-signature-request
signature_request_ready=0 -> denied-signature-request
signature_request_state not requested-metadata-only -> denied-signature-request
missing requested signature -> denied-signature-algorithm
unknown requested signature -> denied-signature-algorithm
missing requested signing authorization -> denied-authorization-request
unknown requested signing authorization -> denied-authorization-request
private-key handling requested or observed -> denied-private-key
key generation requested or observed -> denied-private-key
trust-store loading requested or observed -> denied-private-key
revocation lookup requested or observed -> denied-network-effect
signature already performed -> denied-host-effect
verification already performed -> denied-host-effect
runtime authority already granted -> denied-runtime-authority
handoff already performed -> denied-host-effect
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
```

Failures must not sign, verify signatures, handle private keys, generate keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform handoff, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
signing authorization metadata implementation
```

It does not permit cryptographic signing, signature verification, private-key handling, key generation, trust-store behavior, revocation lookup, runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, object sealing, or kernel behavior.

After signing authorization metadata exists and is guarded, the next valid planning slice is a signing authorization status/public-entry alignment or a future signer-handoff contract that still must not add signing without a separate implementation contract, key-handling contract, and guards.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-signing-authorization-contract.sh
```
