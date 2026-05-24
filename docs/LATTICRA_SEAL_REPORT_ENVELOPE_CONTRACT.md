# Latticra Seal Report Envelope Contract

Status: Latticra Seal report envelope contract
Scope: contract for a future sealed report envelope surface after ready runtime handoff report metadata. This document does not implement runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, signing, key generation, private-key storage, trust-store loading, revocation lookup, object sealing, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal report envelope boundary that may consume ready metadata-only runtime handoff report metadata.

The purpose of this layer is to decide whether a previously ready metadata-only report may be wrapped into a deterministic envelope record before any future signing or runtime bridge exists.

The envelope surface is envelope classification, not signing and not runtime handoff.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md
include/latticra/seal_runtime_handoff_report.h
src/seal_runtime_handoff_report.c
tests/seal_runtime_handoff_report_invariants.c
scripts/test-latticra-seal-runtime-handoff-report.sh
```

The runtime handoff report metadata surface remains the source of report-readiness evidence for this envelope surface.

## Envelope boundary

Allowed in the next implementation slice:

```text
accept runtime handoff report metadata
require report_ready=1
require report_state=ready-report-only or report_state=ready-evaluate-only
require handoff_performed=0
require runtime_authority_granted=0
require effect_performed=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested envelope metadata
classify report-only as envelope_state=sealed-report-only
classify evaluate-only as envelope_state=sealed-evaluate-only
produce deterministic sealed report envelope metadata
```

Forbidden in the next implementation slice:

```text
cryptographic signing
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

## Initial envelope policy

Allowed input report states:

```text
report_state=ready-report-only
report_state=ready-evaluate-only
```

Allowed requested envelope labels:

```text
report-only
evaluate-only
```

Planned envelope states:

```text
envelope_state=sealed-report-only
envelope_state=sealed-evaluate-only
envelope_state=denied-report
envelope_state=denied-envelope
envelope_state=denied-runtime-authority
envelope_state=denied-host-effect
envelope_state=denied-network-effect
```

The first implementation may set:

```text
envelope_ready=1
```

only for metadata-only report/evaluate envelopes.

Even when envelope_ready=1, these must remain zero:

```text
signature_performed=0
handoff_performed=0
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Planned fields

A future sealed report envelope record should be bounded and deterministic.

Planned fields:

```text
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
requested_scope
report_state
report_ready
envelope_state
envelope_ready
signature_performed
handoff_performed
effect_performed
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
status
```

## Failure behavior

Future report envelope handling must fail closed.

Required failure states:

```text
null output -> invalid
null runtime handoff report -> invalid
invalid runtime handoff report -> denied-report
report_ready=0 -> denied-report
report_state not ready-report-only or ready-evaluate-only -> denied-report
missing requested envelope -> denied-envelope
unknown requested envelope -> denied-envelope
requested envelope mismatch -> denied-envelope
runtime authority already granted -> denied-runtime-authority
signature already performed -> denied-host-effect
handoff already performed -> denied-host-effect
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
```

Failures must not sign, handle private keys, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform handoff, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
sealed report envelope metadata implementation
```

It does not permit cryptographic signing, private-key handling, key generation, trust-store behavior, revocation lookup, runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, object sealing, or kernel behavior.

After sealed report envelope metadata exists and is guarded, the next valid planning slice is a signature request contract that still performs no signing.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-report-envelope-contract.sh
```
