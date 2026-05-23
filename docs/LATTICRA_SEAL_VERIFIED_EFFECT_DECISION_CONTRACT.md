# Latticra Seal Verified Effect Decision Contract

Status: Latticra Seal verified effect decision contract
Scope: contract for a future effect-decision evaluation step after verified capability gate metadata. This document does not implement effect execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, signing, key generation, private-key storage, trust-store loading, revocation lookup, object sealing, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first effect decision evaluation boundary that may consume an allowed metadata-only verified capability gate.

The purpose of this layer is to decide whether a previously allowed metadata-only gate remains limited to report/evaluate posture before any future runtime handoff is considered.

The decision is effect classification, not effect execution.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md
docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_CONTRACT.md
docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md
include/latticra/seal_effect_decision.h
include/latticra/seal_verified_capability_gate.h
src/seal_effect_decision.c
src/seal_verified_capability_gate.c
tests/seal_effect_decision_invariants.c
tests/seal_verified_capability_gate_invariants.c
scripts/test-latticra-seal-effect-decision.sh
scripts/test-latticra-seal-verified-capability-gate.sh
```

The verified capability gate metadata surface remains the source of gate evidence for this decision.

## Decision boundary

Allowed in the next implementation slice:

```text
accept verified capability gate metadata
require gate_allowed=1
require gate_state=allowed-metadata-only
require runtime_authority_granted=0
require effect_performed=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested effect metadata
classify report-only as decision_state=allowed-report-only
classify evaluate-only as decision_state=allowed-evaluate-only
produce deterministic effect decision metadata
```

Forbidden in the next implementation slice:

```text
effect execution
runtime authority grants
host reads
host writes
network access
shell execution
tool execution
capability enforcement
policy persistence
trust-store loading
revocation lookup
key generation
private-key handling
object sealing
kernel interaction
```

## Initial decision policy

Allowed input gate states:

```text
gate_state=allowed-metadata-only
```

Allowed requested effect labels:

```text
report-only
evaluate-only
```

Planned decision states:

```text
decision_state=allowed-report-only
decision_state=allowed-evaluate-only
decision_state=denied-gate
decision_state=denied-effect
decision_state=denied-runtime-authority
decision_state=denied-host-effect
decision_state=denied-network-effect
```

The first implementation may set:

```text
effect_allowed=1
```

only for metadata-only report/evaluate decisions.

Even when effect_allowed=1, these must remain zero:

```text
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Planned fields

A future verified effect decision record should be bounded and deterministic.

Planned fields:

```text
decision_profile
gate_profile
receipt_profile
requested_capability
requested_effect
requested_scope
gate_allowed
gate_state
decision_state
effect_allowed
effect_performed
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
status
```

## Failure behavior

Future verified effect decision handling must fail closed.

Required failure states:

```text
null output -> invalid
null verified gate -> invalid
invalid verified gate -> denied-gate
gate_allowed=0 -> denied-gate
gate_state not allowed-metadata-only -> denied-gate
missing requested effect -> denied-effect
unknown requested effect -> denied-effect
runtime authority already granted -> denied-runtime-authority
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
```

Failures must not read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform effects, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
verified effect decision metadata implementation
```

It does not permit effect execution, capability enforcement, runtime authority, host behavior, network behavior, trust-store behavior, revocation lookup, key handling, object sealing, or kernel behavior.

After verified effect decision metadata exists and is guarded, the next valid planning slice is runtime handoff evaluation from an allowed metadata-only effect decision.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-verified-effect-decision-contract.sh
```
