# Latticra Seal Report Envelope Implementation

Status: initial sealed report envelope metadata implementation
Scope: bounded C metadata surface for classifying ready metadata-only runtime handoff report output into deterministic sealed report envelope readiness. This does not implement cryptographic signing, signature verification, key generation, private-key handling, trust-store loading, revocation lookup, object sealing, runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, kernel interaction, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal report envelope metadata implementation.

The implementation consumes runtime handoff report metadata and classifies whether the requested metadata-only envelope remains ready as report-only or evaluate-only.

When runtime handoff report metadata carries crypto graduation metadata, the envelope copies that evidence forward and requires it to remain passed, standard-aligned, and authority-neutral.

The envelope surface is envelope classification, not signing and not runtime handoff.

## Added files

```text
include/latticra/seal_report_envelope.h
src/seal_report_envelope.c
tests/seal_report_envelope_invariants.c
scripts/test-latticra-seal-report-envelope.sh
```

## Required predecessor

This implementation depends on the runtime handoff report metadata surface:

```text
docs/LATTICRA_SEAL_REPORT_ENVELOPE_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md
include/latticra/seal_runtime_handoff_report.h
src/seal_runtime_handoff_report.c
tests/seal_runtime_handoff_report_invariants.c
scripts/test-latticra-seal-runtime-handoff-report.sh
```

## API summary

The report envelope metadata surface adds:

```text
latticra_seal_report_envelope_t
latticra_seal_report_envelope_error_t
latticra_seal_report_envelope_error_label
latticra_seal_report_envelope_from_report
latticra_seal_report_envelope_is_metadata_only
latticra_seal_report_envelope_render
```

## Envelope behavior

The implementation:

```text
accepts runtime handoff report metadata
copies crypto graduation gate metadata when present
requires crypto_graduation_gate_passed=1 when crypto_graduation_gate_present=1
requires standard_expectations_met=1 when crypto_graduation_gate_present=1
requires local_verify_graduated=1 when crypto_graduation_gate_present=1
requires receipt_promotion_graduated=1 when crypto_graduation_gate_present=1
requires authority_promotion_allowed=0 when crypto_graduation_gate_present=1
requires report_ready=1
requires report_state=ready-report-only or report_state=ready-evaluate-only
requires runtime_authority_granted=0
requires handoff_performed=0
requires effect_performed=0
requires host_read_performed=0
requires host_write_performed=0
requires network_performed=0
accepts requested envelope metadata
classifies report-only as envelope_state=sealed-report-only
classifies evaluate-only as envelope_state=sealed-evaluate-only
sets envelope_ready=1 only for metadata-only report/evaluate envelope surfaces
renders deterministic sealed report envelope metadata
```

Crypto-bound sealed report envelope metadata records:

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
envelope_state=sealed-report-only
envelope_ready=1
signature_performed=0
runtime_authority_granted=0
```

## Effect and runtime boundary

Even when envelope_ready=1, these fields remain zero:

```text
signature_performed=0
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
null runtime handoff report -> invalid-input
invalid runtime handoff report -> invalid-report
failed crypto graduation gate evidence -> denied-crypto-graduation-gate
authority-bearing crypto graduation evidence -> denied-crypto-graduation-gate
report_ready=0 -> denied-report
report_state not ready-report-only or ready-evaluate-only -> denied-report
missing requested envelope -> missing-requested-envelope
unknown requested envelope -> denied-unknown-envelope
requested envelope mismatch -> denied-envelope
runtime authority already granted -> denied-runtime-authority
handoff already performed -> denied-host-effect
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not sign, perform handoff, perform effects, read host files, write host files, contact networks, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
ready report-only metadata produces sealed-report-only envelope metadata
ready evaluate-only metadata produces sealed-evaluate-only envelope metadata
envelope_ready is one only for metadata-only envelope states
signature_performed remains zero
handoff_performed remains zero
effect_performed remains zero
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
small render buffer fails closed
null inputs fail closed
invalid report metadata fails closed
missing, unknown, and mismatched requested envelope labels fail closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-report-envelope-contract.sh
sh scripts/test-latticra-seal-report-envelope.sh
```

Expected output:

```text
seal report envelope contract: ok
seal report envelope invariants: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is signature request or policy decision report propagation from ready crypto-graduation-gated sealed report-envelope metadata.

That future slice must remain contract-first and must not add private-key handling, signing, trust-store behavior, revocation lookup, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately contracted, implemented, and guarded.
