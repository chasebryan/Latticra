# Latticra Seal Runtime Handoff Evaluation Contract

Status: Latticra Seal runtime handoff evaluation contract
Scope: contract for a future runtime handoff evaluation step after verified effect decision metadata. This document does not implement runtime handoff, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, signing, key generation, private-key storage, trust-store loading, revocation lookup, object sealing, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal runtime handoff evaluation boundary that may consume an allowed metadata-only verified effect decision.

The purpose of this layer is to decide whether a previously allowed metadata-only effect decision is eligible to be described as a runtime handoff candidate before any future runtime bridge exists.

The evaluation is handoff classification, not runtime handoff.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_CONTRACT.md
docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_IMPLEMENTATION.md
include/latticra/seal_verified_effect_decision.h
src/seal_verified_effect_decision.c
tests/seal_verified_effect_decision_invariants.c
scripts/test-latticra-seal-verified-effect-decision.sh
```

The verified effect decision metadata surface remains the source of effect-decision evidence for this runtime handoff evaluation.

## Evaluation boundary

Allowed in the next implementation slice:

```text
accept verified effect decision metadata
require effect_allowed=1
require decision_state=allowed-report-only
require decision_state=allowed-evaluate-only
require runtime_authority_granted=0
require effect_performed=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested handoff metadata
classify report-only as handoff_state=eligible-report-only
classify evaluate-only as handoff_state=eligible-evaluate-only
produce deterministic runtime handoff evaluation metadata
```

Forbidden in the next implementation slice:

```text
runtime handoff execution
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

## Initial handoff policy

Allowed input decision states:

```text
decision_state=allowed-report-only
decision_state=allowed-evaluate-only
```

Allowed requested handoff labels:

```text
report-only
evaluate-only
```

Planned handoff states:

```text
handoff_state=eligible-report-only
handoff_state=eligible-evaluate-only
handoff_state=denied-decision
handoff_state=denied-effect
handoff_state=denied-runtime-authority
handoff_state=denied-host-effect
handoff_state=denied-network-effect
```

The first implementation may set:

```text
handoff_eligible=1
```

only for metadata-only report/evaluate decisions.

Even when handoff_eligible=1, these must remain zero:

```text
handoff_performed=0
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Planned fields

A future runtime handoff evaluation record should be bounded and deterministic.

Planned fields:

```text
handoff_profile
decision_profile
gate_profile
receipt_profile
requested_capability
requested_effect
requested_handoff
requested_scope
decision_state
effect_allowed
handoff_state
handoff_eligible
handoff_performed
effect_performed
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
status
```

## Failure behavior

Future runtime handoff evaluation handling must fail closed.

Required failure states:

```text
null output -> invalid
null verified effect decision -> invalid
invalid verified effect decision -> denied-decision
effect_allowed=0 -> denied-effect
decision_state not allowed-report-only or allowed-evaluate-only -> denied-decision
missing requested handoff -> denied-effect
unknown requested handoff -> denied-effect
runtime authority already granted -> denied-runtime-authority
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
```

Failures must not read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform handoff, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
runtime handoff evaluation metadata implementation
```

It does not permit runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, trust-store behavior, revocation lookup, key handling, object sealing, or kernel behavior.

After runtime handoff evaluation metadata exists and is guarded, the next valid planning slice is a runtime handoff report surface that still performs no runtime handoff.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-runtime-handoff-evaluation-contract.sh
```
