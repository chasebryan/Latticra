# Latticra Seal Signer Handoff Implementation

Status: signer handoff metadata implementation with crypto graduation evidence carry-forward
Scope: bounded C metadata surface for classifying Seal signer handoff eligibility after ready signing authorization metadata, including read-only crypto graduation evidence when the signing authorization carries it. This slice does not add signing, signature verification, signer invocation, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the Latticra Seal signer handoff metadata implementation.

The implementation consumes ready signing authorization metadata and classifies whether the request remains eligible for a future metadata-only signer handoff.

When signing authorization metadata carries crypto graduation metadata, the signer handoff copies that evidence forward and requires it to remain passed, standard-aligned, locally graduated, receipt-promotion graduated, and authority-neutral.

It is signer-path handoff classification only.

It does not invoke a signer.

It does not sign.

## Files

```text
include/latticra/seal_signer_handoff.h
src/seal_signer_handoff.c
tests/seal_signer_handoff_invariants.c
scripts/test-latticra-seal-signer-handoff.sh
```

## Required predecessors

This implementation depends on the signer handoff contract and the signing authorization metadata surface:

```text
docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md
docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md
docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md
include/latticra/seal_signing_authorization.h
src/seal_signing_authorization.c
tests/seal_signing_authorization_invariants.c
scripts/test-latticra-seal-signer-handoff-contract.sh
scripts/test-latticra-seal-signing-authorization-contract.sh
scripts/test-latticra-seal-signing-authorization.sh
scripts/test-latticra-seal-signing-authorization-status.sh
```

## Implemented surface

The signer handoff metadata surface adds:

```text
latticra_seal_signer_handoff_t
latticra_seal_signer_handoff_error_t
latticra_seal_signer_handoff_error_label
latticra_seal_signer_handoff_from_authorization
latticra_seal_signer_handoff_is_metadata_only
latticra_seal_signer_handoff_render
```

The implementation:

```text
accepts signing authorization metadata
requires signing_authorization_ready=1
requires signing_authorization_state=authorized-metadata-only
copies crypto graduation gate metadata when present
requires crypto_graduation_gate_passed=1 when crypto_graduation_gate_present=1
requires standard_expectations_met=1 when crypto_graduation_gate_present=1
requires local_verify_graduated=1 when crypto_graduation_gate_present=1
requires receipt_promotion_graduated=1 when crypto_graduation_gate_present=1
requires authority_promotion_allowed=0 when crypto_graduation_gate_present=1
requires crypto_graduation_gate_state=graduated-authority-neutral when crypto_graduation_gate_present=1
requires requested_signature=Ed25519-development
requires requested_signing_authorization=metadata-only
accepts requested_signer_handoff=metadata-only
classifies the result as signer_handoff_state=handoff-metadata-only
sets signer_handoff_ready=1 only for metadata-only allowed authorization states
renders deterministic signer handoff metadata
fails closed for invalid or denied predecessor metadata
```

Even when signer_handoff_ready=1, these fields remain zero:

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
signer_handoff_profile=latticra-seal-signer-handoff/0.1
signing_authorization_profile=latticra-seal-signing-authorization/0.1
signature_request_profile=latticra-seal-signature-request/0.1
requested_signature=Ed25519-development
requested_signing_authorization=metadata-only
requested_signer_handoff=metadata-only
signing_authorization_state=authorized-metadata-only
signing_authorization_ready=1
signer_handoff_state=handoff-metadata-only
signer_handoff_ready=1
signer_invoked=0
mode=metadata-only
status=signer-handoff-metadata
```

Crypto-bound signer handoff metadata records:

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
signer_handoff_state=handoff-metadata-only
signer_handoff_ready=1
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
null signing authorization
invalid signing authorization
failed crypto graduation gate evidence
authority-bearing crypto graduation evidence
signing_authorization_ready=0
signing_authorization_state not authorized-metadata-only
requested_signing_authorization not metadata-only
missing requested signature
unknown requested signature
missing requested signer handoff
unknown requested signer handoff
private-key handling already present
key generation already present
trust-store loading already present
revocation lookup already present
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

Failures do not sign, verify signatures, invoke a signer, handle private keys, generate keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform runtime handoff, persist policy, or grant runtime authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signer-handoff-contract.sh
sh scripts/test-latticra-seal-signer-handoff.sh
```

Expected output:

```text
seal signer handoff contract: ok
seal signer handoff invariants: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is signing operation or policy decision report propagation from ready crypto-graduation-gated signer invocation metadata, bounded no-effect key parsing implementation, or another narrow status/index alignment follow-up that still must not add signing without separate implementation, key-handling, key-material, and guard contracts.

The signer invocation metadata implementation, status/public-entry alignment, signing operation contract, signing operation metadata implementation, signing operation status/public-entry alignment, key-handling boundary contract, and key-handling metadata implementation now exist as guarded checkpoints. Future work must not add private-key handling, signing, verification, signer invocation behavior, trust-store behavior, revocation lookup, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately implemented and guarded.
