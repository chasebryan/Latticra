# Latticra Seal Signature Request Contract

Status: Latticra Seal signature request contract
Scope: contract for a future metadata-only signature request surface after sealed report-envelope metadata. This document does not implement signing, signature verification, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal signature-request boundary for sealed report-envelope metadata.

The purpose of this layer is to decide whether a ready metadata-only report envelope may be marked as eligible for a future signing request before any signing implementation, key authority, trust store, or runtime bridge exists.

The signature-request surface is request classification, not signing and not verification.

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

This contract is a separate envelope-chain planning layer. It starts from ready sealed report-envelope metadata and does not consume private keys, produce signatures, verify signatures, trust signatures, or grant authority.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_REPORT_ENVELOPE_CONTRACT.md
docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md
include/latticra/seal_report_envelope.h
src/seal_report_envelope.c
tests/seal_report_envelope_invariants.c
scripts/test-latticra-seal-report-envelope.sh
```

The report-envelope metadata surface remains the source of envelope-readiness evidence for this signature-request surface.

## Signature request boundary

Allowed in the next implementation slice:

```text
accept sealed report-envelope metadata
require envelope_ready=1
require envelope_state=sealed-report-only or envelope_state=sealed-evaluate-only
require signature_performed=0
require handoff_performed=0
require effect_performed=0
require runtime_authority_granted=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested signature metadata
classify Ed25519-development as signature_request_state=requested-metadata-only
produce deterministic signature request metadata
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

## Initial request policy

Allowed input envelope states:

```text
envelope_state=sealed-report-only
envelope_state=sealed-evaluate-only
```

Allowed requested signature labels:

```text
Ed25519-development
```

This label is a metadata request label only. It does not mean Ed25519 signing, Ed25519 verification, key generation, private-key handling, or trust establishment exists in this path.

Planned signature request states:

```text
signature_request_state=requested-metadata-only
signature_request_state=denied-envelope
signature_request_state=denied-signature-request
signature_request_state=denied-runtime-authority
signature_request_state=denied-host-effect
signature_request_state=denied-network-effect
```

The first implementation may set:

```text
signature_request_ready=1
```

only for ready metadata-only sealed report/evaluate envelopes and an allowed metadata-only signature request label.

Even when signature_request_ready=1, these must remain zero:

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

## Planned fields

A future signature request record should be bounded and deterministic.

Planned fields:

```text
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
requested_scope
envelope_state
envelope_ready
signature_request_state
signature_request_ready
signature_performed
verification_performed
private_key_handling
handoff_performed
effect_performed
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
status
```

## Failure behavior

Future signature-request handling must fail closed.

Required failure states:

```text
null output -> invalid
null report envelope -> invalid
invalid report envelope -> denied-envelope
envelope_ready=0 -> denied-envelope
envelope_state not sealed-report-only or sealed-evaluate-only -> denied-envelope
missing requested signature -> denied-signature-request
unknown requested signature -> denied-signature-request
signature already performed -> denied-host-effect
runtime authority already granted -> denied-runtime-authority
handoff already performed -> denied-host-effect
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
```

Failures must not sign, verify signatures, handle private keys, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform handoff, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
signature request metadata implementation
```

It does not permit cryptographic signing, signature verification, private-key handling, key generation, trust-store behavior, revocation lookup, runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, object sealing, or kernel behavior.

After signature request metadata and its status/public-entry checkpoint exist, the next valid planning slice is a signing authorization contract that still must not add signing without a separate implementation contract.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-signature-request-contract.sh
```
