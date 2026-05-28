# Latticra Seal Signer Invocation Implementation

Status: signer invocation metadata implementation with crypto graduation evidence carry-forward
Scope: bounded C metadata surface for classifying Seal signer invocation eligibility after ready signer handoff metadata, including read-only crypto graduation evidence when the signer handoff carries it. This slice does not add signing, signature verification, signer invocation behavior, signer process execution, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the Latticra Seal signer invocation metadata implementation.

The implementation consumes ready signer handoff metadata and classifies whether the request remains eligible for a future metadata-only signer invocation path.

When signer handoff metadata carries crypto graduation metadata, the signer invocation copies that evidence forward and requires it to remain passed, standard-aligned, locally graduated, receipt-promotion graduated, and authority-neutral.

It is signer-invocation path classification only.

It does not invoke a signer.

It does not sign.

## Files

```text
include/latticra/seal_signer_invocation.h
src/seal_signer_invocation.c
tests/seal_signer_invocation_invariants.c
scripts/test-latticra-seal-signer-invocation.sh
```

## Required predecessors

This implementation depends on the signer invocation contract and signer handoff metadata surface:

```text
docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md
docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
docs/status/SEAL_SIGNER_HANDOFF_STATUS.md
include/latticra/seal_signer_handoff.h
src/seal_signer_handoff.c
tests/seal_signer_handoff_invariants.c
scripts/test-latticra-seal-signer-invocation-contract.sh
scripts/test-latticra-seal-signer-handoff-contract.sh
scripts/test-latticra-seal-signer-handoff.sh
scripts/test-latticra-seal-signer-handoff-status.sh
```

## Implemented surface

The signer invocation metadata surface adds:

```text
latticra_seal_signer_invocation_t
latticra_seal_signer_invocation_error_t
latticra_seal_signer_invocation_error_label
latticra_seal_signer_invocation_from_handoff
latticra_seal_signer_invocation_is_metadata_only
latticra_seal_signer_invocation_render
```

The implementation:

```text
accepts signer handoff metadata
requires signer_handoff_ready=1
requires signer_handoff_state=handoff-metadata-only
copies crypto graduation gate metadata when present
requires crypto_graduation_gate_passed=1 when crypto_graduation_gate_present=1
requires standard_expectations_met=1 when crypto_graduation_gate_present=1
requires local_verify_graduated=1 when crypto_graduation_gate_present=1
requires receipt_promotion_graduated=1 when crypto_graduation_gate_present=1
requires authority_promotion_allowed=0 when crypto_graduation_gate_present=1
requires crypto_graduation_gate_state=graduated-authority-neutral when crypto_graduation_gate_present=1
requires requested_signature=Ed25519-development
requires requested_signing_authorization=metadata-only
requires requested_signer_handoff=metadata-only
accepts requested_signer_invocation=metadata-only
classifies the result as signer_invocation_state=invocation-metadata-only
sets signer_invocation_ready=1 only for metadata-only allowed handoff states
renders deterministic signer invocation metadata
fails closed for invalid or denied predecessor metadata
```

Even when signer_invocation_ready=1, these fields remain zero:

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
signer_invocation_profile=latticra-seal-signer-invocation/0.1
signer_handoff_profile=latticra-seal-signer-handoff/0.1
signing_authorization_profile=latticra-seal-signing-authorization/0.1
signature_request_profile=latticra-seal-signature-request/0.1
requested_signature=Ed25519-development
requested_signing_authorization=metadata-only
requested_signer_handoff=metadata-only
requested_signer_invocation=metadata-only
signing_authorization_state=authorized-metadata-only
signing_authorization_ready=1
signer_handoff_state=handoff-metadata-only
signer_handoff_ready=1
signer_invocation_state=invocation-metadata-only
signer_invocation_ready=1
signer_invoked=0
mode=metadata-only
status=signer-invocation-metadata
```

Crypto-bound signer invocation metadata records:

```text
crypto_graduation_profile=latticra-seal-crypto-graduation-gate/0.1
assurance_baseline_profile=latticra-cryptographic-assurance-key-management/0.1
crypto_graduation_gate_state=graduated-authority-neutral
crypto_graduation_gate_present=1
crypto_graduation_gate_passed=1
standard_expectations_met=1
local_verify_graduated=1
receipt_promotion_graduated=1
authority_promotion_allowed=0
signer_invocation_state=invocation-metadata-only
signer_invocation_ready=1
signature_performed=0
verification_performed=0
signer_invoked=0
private_key_handling=0
runtime_authority_granted=0
```

## Failure behavior

The implementation fails closed for:

```text
null output
null signer handoff
invalid signer handoff
unterminated signer handoff strings
invalid signer handoff boolean flags
failed crypto graduation gate evidence
authority-bearing crypto graduation evidence
signer_handoff_ready=0
signer_handoff_state not handoff-metadata-only
requested_signer_handoff not metadata-only
signing_authorization_ready=0
signing_authorization_state not authorized-metadata-only
requested_signing_authorization not metadata-only
missing requested signature
unknown requested signature
missing requested signer invocation
unknown requested signer invocation
unterminated requested signer invocation -> denied-signer-invocation without copying caller bytes
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
tampered signer invocation strings fail closed before render
tampered signer invocation authority/effect flags fail closed before render
tampered signer invocation ready/error state fails closed before render
small render buffer
```

Failures do not sign, verify signatures, invoke a signer, handle private keys, generate keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform runtime handoff, persist policy, or grant runtime authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signer-invocation-contract.sh
sh scripts/test-latticra-seal-signer-invocation.sh
sh scripts/test-latticra-seal-signer-invocation-status.sh
```

Expected output:

```text
seal signer invocation contract: ok
seal signer invocation invariants: ok
seal signer invocation status: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is key-handling or policy decision report propagation from ready crypto-graduation-gated signing operation metadata, bounded no-effect key parsing implementation, or another narrow status/index alignment follow-up that still must not add signing without separate implementation, key-handling, key-material, and guard contracts.

The signer invocation status/public-entry alignment, signing operation contract, signing operation metadata implementation, signing operation status/public-entry alignment, key-handling boundary contract, and key-handling metadata implementation now exist as guarded checkpoints. Future work must not add private-key handling, signing, verification, signer invocation behavior, trust-store behavior, revocation lookup, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately implemented and guarded.
