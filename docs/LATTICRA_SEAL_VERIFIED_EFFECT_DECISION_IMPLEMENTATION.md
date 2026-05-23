# Latticra Seal Verified Effect Decision Implementation

Status: initial verified effect decision metadata implementation
Scope: bounded C metadata surface for classifying allowed metadata-only verified capability gate output into a deterministic effect decision. This does not implement effect execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, trust-store loading, revocation lookup, key generation, private-key handling, object sealing, kernel interaction, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal verified effect decision metadata implementation.

The implementation consumes verified capability gate metadata and classifies whether the requested metadata-only effect remains allowed as report-only or evaluate-only.

The decision is effect classification, not effect execution.

## Added files

```text
include/latticra/seal_verified_effect_decision.h
src/seal_verified_effect_decision.c
tests/seal_verified_effect_decision_invariants.c
scripts/test-latticra-seal-verified-effect-decision.sh
```

## Required predecessor

This implementation depends on the verified capability gate metadata surface:

```text
include/latticra/seal_verified_capability_gate.h
src/seal_verified_capability_gate.c
tests/seal_verified_capability_gate_invariants.c
scripts/test-latticra-seal-verified-capability-gate.sh
docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md
```

## API summary

The verified effect decision metadata surface adds:

```text
latticra_seal_verified_effect_decision_t
latticra_seal_verified_effect_decision_error_t
latticra_seal_verified_effect_decision_error_label
latticra_seal_verified_effect_decision_from_gate
latticra_seal_verified_effect_decision_is_metadata_only
latticra_seal_verified_effect_decision_report
```

## Decision behavior

The implementation:

```text
accepts verified capability gate metadata
requires gate_allowed=1
requires gate_state=allowed-metadata-only
requires runtime_authority_granted=0
requires effect_performed=0
requires host_read_performed=0
requires host_write_performed=0
requires network_performed=0
accepts requested effect metadata
classifies report-only as decision_state=allowed-report-only
classifies evaluate-only as decision_state=allowed-evaluate-only
sets effect_allowed=1 only for metadata-only report/evaluate decisions
renders deterministic verified effect decision metadata
```

## Effect and runtime boundary

Even when effect_allowed=1, these fields remain zero:

```text
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

This implementation does not read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, persist policy, load trust stores, look up revocation status, generate keys, handle private keys, seal objects, or interact with the kernel.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null verified gate -> invalid-input
invalid verified gate -> invalid-gate
gate_allowed=0 -> denied-gate
gate_state not allowed-metadata-only -> denied-gate
missing requested effect -> missing-requested-effect
unknown requested effect -> denied-unknown-effect
runtime authority already granted -> denied-runtime-authority
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not perform effects and do not grant runtime authority.

## Validation

Run locally:

```sh
sh scripts/test-latticra-seal-verified-effect-decision.sh
```

Expected output:

```text
seal verified effect decision invariants: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is runtime handoff evaluation from an allowed metadata-only verified effect decision.

That next slice should remain contract-first and should not perform runtime handoff yet unless separately implemented and guarded.
