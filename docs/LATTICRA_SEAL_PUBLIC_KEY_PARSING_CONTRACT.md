# Latticra Seal Public-Key Parsing Boundary Contract

Status: Latticra Seal public-key parsing boundary contract
Scope: contract for a future metadata-only public-key parsing surface after Seal key-material metadata. This document does not implement public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store loading, revocation lookup, cryptographic signing, signature verification, signer invocation behavior, signer process execution, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal public-key parsing boundary after ready key-material metadata.

The purpose of this layer is to decide whether a ready metadata-only key-material record may be represented as eligible for a future metadata-only public-key parsing request before any public-key parser, key material loader, private key, signer process, trust store, hardware key, runtime bridge, host authority, or signature generation exists.

The public-key parsing surface is public-key parsing path classification, not public-key parsing, not key material handling, not signing, not verification, and not trust-store behavior.

This document does not parse public keys.

This document does not load key material.

This document does not handle private keys.

## Relationship to key material

Latticra Seal key-material metadata already records a no-effect eligibility checkpoint for the future key path:

```text
docs/LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md
docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
docs/status/SEAL_KEY_MATERIAL_STATUS.md
```

This public-key parsing boundary contract starts from that checkpoint. It does not replace key-material metadata, parse public keys, load key material, handle private keys, route to runtime behavior, invoke a signer, perform signing, verify signatures, load trust stores, persist policy, or grant runtime authority.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md
docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
docs/status/SEAL_KEY_MATERIAL_STATUS.md
include/latticra/seal_key_material.h
src/seal_key_material.c
tests/seal_key_material_invariants.c
scripts/test-latticra-seal-key-material-contract.sh
scripts/test-latticra-seal-key-material.sh
scripts/test-latticra-seal-key-material-status.sh
```

The key-material metadata surface remains the source of readiness evidence for this public-key parsing surface.

## Public-Key Parsing Boundary

Allowed in the next implementation slice:

```text
accept key-material metadata
require key_material_ready=1
require key_material_state=key-material-metadata-only
require requested_signature=Ed25519-development
require requested_signing_authorization=metadata-only
require requested_signer_handoff=metadata-only
require requested_signer_invocation=metadata-only
require requested_signing_operation=metadata-only
require requested_key_handling=metadata-only
require requested_key_material=metadata-only
require signature_performed=0
require verification_performed=0
require signer_invoked=0
require public_key_parsed=0
require key_material_loaded=0
require private_key_handling=0
require key_generation_performed=0
require hardware_key_used=0
require trust_store_loaded=0
require revocation_lookup_performed=0
require handoff_performed=0
require effect_performed=0
require runtime_authority_granted=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested_public_key_parsing=metadata-only
classify metadata-only as public_key_parsing_state=public-key-parsing-metadata-only
produce deterministic public-key parsing metadata
```

Forbidden in the next implementation slice:

```text
public-key parsing
key material loading
private-key handling
key generation
hardware-key use
trust-store loading
revocation lookup
cryptographic signing
signature verification
signer process invocation
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

## Initial Public-Key Parsing Policy

Allowed key-material state:

```text
key_material_state=key-material-metadata-only
```

Allowed requested key-material label:

```text
metadata-only
```

Allowed requested public-key parsing label:

```text
metadata-only
```

These labels are metadata labels only. They do not mean public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust establishment, trust-store behavior, Ed25519 signing, Ed25519 verification, signer invocation, revocation lookup, runtime handoff, host behavior, network behavior, or capability enforcement exists in this path.

Planned public-key parsing states:

```text
public_key_parsing_state=public-key-parsing-metadata-only
public_key_parsing_state=denied-key-material
public_key_parsing_state=denied-key-handling
public_key_parsing_state=denied-signing-operation
public_key_parsing_state=denied-signer-invocation
public_key_parsing_state=denied-signer-handoff
public_key_parsing_state=denied-signing-authorization
public_key_parsing_state=denied-signature-algorithm
public_key_parsing_state=denied-public-key-parsing
public_key_parsing_state=denied-private-key
public_key_parsing_state=denied-trust-store
public_key_parsing_state=denied-runtime-authority
public_key_parsing_state=denied-host-effect
public_key_parsing_state=denied-network-effect
```

The first implementation may set:

```text
public_key_parsing_ready=1
```

only for ready metadata-only key-material metadata, the allowed development signature label, the metadata-only key-handling label, the metadata-only key-material label, and the metadata-only public-key parsing label.

Even when public_key_parsing_ready=1, these must remain zero:

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

## Planned Fields

A future public-key parsing record should be bounded and deterministic.

Planned fields:

```text
public_key_parsing_profile
key_material_profile
key_handling_profile
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
requested_key_handling
requested_key_material
requested_public_key_parsing
requested_scope
signing_authorization_state
signing_authorization_ready
signer_handoff_state
signer_handoff_ready
signer_invocation_state
signer_invocation_ready
signing_operation_state
signing_operation_ready
key_handling_state
key_handling_ready
key_material_state
key_material_ready
public_key_parsing_state
public_key_parsing_ready
signature_performed
verification_performed
signer_invoked
public_key_parsed
key_material_loaded
private_key_handling
key_generation_performed
hardware_key_used
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
public_key_parsing_profile=latticra-seal-public-key-parsing/0.1
key_material_profile=latticra-seal-key-material/0.1
key_handling_profile=latticra-seal-key-handling/0.1
requested_key_handling=metadata-only
requested_key_material=metadata-only
requested_public_key_parsing=metadata-only
key_material_state=key-material-metadata-only
key_material_ready=1
public_key_parsing_state=public-key-parsing-metadata-only
public_key_parsing_ready=1
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
runtime_authority_granted=0
mode=metadata-only
status=public-key-parsing-metadata
```

## Failure Behavior

Future public-key parsing metadata handling must fail closed.

Required failure states:

```text
null output -> invalid
null key material -> invalid
invalid key material -> denied-key-material
key_material_ready=0 -> denied-key-material
key_material_state not key-material-metadata-only -> denied-key-material
requested_key_material not metadata-only -> denied-key-material
key_handling_ready=0 -> denied-key-handling
key_handling_state not key-handling-metadata-only -> denied-key-handling
requested_key_handling not metadata-only -> denied-key-handling
signing_operation_ready=0 -> denied-signing-operation
signing_operation_state not operation-metadata-only -> denied-signing-operation
requested_signing_operation not metadata-only -> denied-signing-operation
signer_invocation_ready=0 -> denied-signer-invocation
signer_invocation_state not invocation-metadata-only -> denied-signer-invocation
requested_signer_invocation not metadata-only -> denied-signer-invocation
signer_handoff_ready=0 -> denied-signer-handoff
signer_handoff_state not handoff-metadata-only -> denied-signer-handoff
requested_signer_handoff not metadata-only -> denied-signer-handoff
requested_signing_authorization not metadata-only -> denied-signing-authorization
missing requested signature -> denied-signature-algorithm
unknown requested signature -> denied-signature-algorithm
missing requested public key parsing -> denied-public-key-parsing
unknown requested public key parsing -> denied-public-key-parsing
public-key parsing requested or observed -> denied-public-key-parsing
key material loading requested or observed -> denied-key-material
private-key handling requested or observed -> denied-private-key
key generation requested or observed -> denied-private-key
hardware-key use requested or observed -> denied-private-key
trust-store loading requested or observed -> denied-trust-store
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

Failures must not sign, verify signatures, invoke a signer, parse public keys, load key material, handle private keys, generate keys, use hardware keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform runtime handoff, persist policy, or grant runtime authority.

## Promotion Rule

This contract permits only the next implementation slice:

```text
public-key parsing metadata implementation
```

It does not permit public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, revocation lookup, cryptographic signing, signature verification, signer invocation behavior, runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, object sealing, or kernel behavior.

After public-key parsing metadata, status/public-entry alignment, and the future key parsing implementation contract exist and are guarded, the next valid planning slice is future key parsing implementation plan that still must not add public-key parsing without separate implementation, public-key, key-material, and guard contracts.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-public-key-parsing-contract.sh
```
