# Latticra Seal Signature Request Implementation

Status: initial signature request metadata implementation
Scope: bounded C metadata surface for classifying ready sealed report-envelope metadata into deterministic signature-request readiness. This does not implement cryptographic signing, signature verification, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal signature request metadata implementation.

The implementation consumes sealed report-envelope metadata and classifies whether the requested metadata-only signature request remains eligible for a future signing path.

The signature-request surface is request classification, not signing and not verification.

## Added files

```text
include/latticra/seal_signature_request.h
src/seal_signature_request.c
tests/seal_signature_request_invariants.c
scripts/test-latticra-seal-signature-request.sh
```

## Required predecessor

This implementation depends on the signature request contract and the report-envelope metadata surface:

```text
docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md
docs/LATTICRA_SEAL_REPORT_ENVELOPE_CONTRACT.md
docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md
include/latticra/seal_report_envelope.h
src/seal_report_envelope.c
tests/seal_report_envelope_invariants.c
scripts/test-latticra-seal-report-envelope.sh
```

## API summary

The signature request metadata surface adds:

```text
latticra_seal_signature_request_t
latticra_seal_signature_request_error_t
latticra_seal_signature_request_error_label
latticra_seal_signature_request_from_envelope
latticra_seal_signature_request_is_metadata_only
latticra_seal_signature_request_render
```

## Request behavior

The implementation:

```text
accepts sealed report-envelope metadata
requires envelope_ready=1
requires envelope_state=sealed-report-only or envelope_state=sealed-evaluate-only
requires signature_performed=0
requires handoff_performed=0
requires effect_performed=0
requires runtime_authority_granted=0
requires host_read_performed=0
requires host_write_performed=0
requires network_performed=0
accepts requested signature metadata
classifies Ed25519-development as signature_request_state=requested-metadata-only
sets signature_request_ready=1 only for metadata-only sealed report/evaluate envelope surfaces
renders deterministic signature request metadata
```

## Effect and runtime boundary

Even when signature_request_ready=1, these fields remain zero:

```text
signature_performed=0
verification_performed=0
private_key_handling=0
handoff_performed=0
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

This implementation does not sign records, verify signatures, handle private keys, load trust stores, look up revocation status, perform runtime handoff, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, persist policy, seal objects, or interact with the kernel.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null report envelope -> invalid-input
invalid report envelope -> invalid-envelope
envelope_ready=0 -> denied-envelope
envelope_state not sealed-report-only or sealed-evaluate-only -> denied-envelope
missing requested signature -> missing-requested-signature
unknown requested signature -> denied-unknown-signature
signature already performed -> denied-host-effect
runtime authority already granted -> denied-runtime-authority
handoff already performed -> denied-host-effect
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not sign, verify, handle private keys, perform handoff, perform effects, read host files, write host files, contact networks, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
ready sealed-report-only envelope metadata produces requested-metadata-only signature request metadata
ready sealed-evaluate-only envelope metadata produces requested-metadata-only signature request metadata
signature_request_ready is one only for metadata-only allowed request states
signature_performed remains zero
verification_performed remains zero
private_key_handling remains zero
handoff_performed remains zero
effect_performed remains zero
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
small render buffer fails closed
null inputs fail closed
invalid envelope metadata fails closed
missing and unknown requested signature labels fail closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signature-request-contract.sh
sh scripts/test-latticra-seal-signature-request.sh
```

Expected output:

```text
seal signature request contract: ok
seal signature request invariants: ok
```

## Next valid slice

The next valid Latticra Seal slice is signer invocation metadata implementation or a narrow status-index alignment follow-up.

That future slice must not add private-key handling, signing, verification, trust-store behavior, revocation lookup, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately contracted, implemented, and guarded.
