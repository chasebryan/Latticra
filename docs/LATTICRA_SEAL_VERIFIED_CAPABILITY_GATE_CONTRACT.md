# Latticra Seal Verified Capability Gate Contract

Status: Latticra Seal verified capability gate contract
Scope: contract for a future capability gate evaluation step after verified receipt promotion. This document does not implement capability authorization, effect execution, runtime authority, host effects, network behavior, signing, key generation, private-key storage, trust-store loading, revocation lookup, object sealing, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first capability gate evaluation boundary that may consume verified receipt metadata.

The purpose of this layer is to evaluate whether a verified but authority-neutral receipt could satisfy a declared capability request while still refusing runtime authority and effect execution.

The gate is policy evaluation, not effect execution.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md
docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_CONTRACT.md
docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_IMPLEMENTATION.md
include/latticra/seal_capability_gate.h
include/latticra/seal_verified_receipt_promotion.h
src/seal_capability_gate.c
src/seal_verified_receipt_promotion.c
tests/seal_capability_gate_invariants.c
tests/seal_verified_receipt_promotion_invariants.c
scripts/test-latticra-seal-capability-gate.sh
scripts/test-latticra-seal-verified-receipt-promotion.sh
```

The verified receipt promotion surface remains the evidence source for this gate.

## Gate boundary

Allowed in the next implementation slice:

```text
accept verified receipt promotion metadata
require receipt_state=verified
require verification_state=verified
require verified=1
require invalid=0
require cryptographic_verification_performed=1
accept requested capability metadata
accept requested effect metadata
accept requested scope metadata
compare requested capability against a narrow local allowlist
compare requested effect against a report-only/evaluate-only effect class
produce deterministic capability gate evaluation metadata
```

Forbidden in the next implementation slice:

```text
host reads
host writes
network access
effect execution
runtime authority grants
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

## Initial gate policy

The initial policy is deliberately narrow.

Allowed requested capability labels:

```text
verified-receipt-inspection
verified-receipt-report
```

Allowed requested effect labels:

```text
report-only
evaluate-only
```

Any other capability or effect must deny.

## Planned gate states

Future records should use explicit labels:

```text
gate_state=allowed-metadata-only
gate_state=denied-unverified
gate_state=denied-invalid-receipt
gate_state=denied-unknown-capability
gate_state=denied-unknown-effect
gate_state=denied-policy
gate_state=denied-runtime-authority
```

The first implementation may set:

```text
gate_allowed=1
gate_state=allowed-metadata-only
```

only for a verified receipt and a locally allowed report-only/evaluate-only request.

Even when gate_allowed=1, these must remain zero:

```text
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Planned fields

A future verified capability gate record should be bounded and deterministic.

Planned fields:

```text
gate_profile
receipt_profile
verify_profile
message_digest_algorithm
message_digest_hex
public_key_identity_label
receipt_state
verification_state
requested_capability
requested_effect
requested_scope
verified
authority_usable
receipt_capability_gate_allowed
gate_allowed
gate_state
runtime_authority_granted
effect_performed
host_read_performed
host_write_performed
network_performed
status
```

## Failure behavior

Future verified capability gate handling must fail closed.

Required failure states:

```text
null output -> invalid
null verified receipt -> invalid
receipt_state not verified -> denied-unverified
verification_state not verified -> denied-unverified
verified=0 -> denied-unverified
invalid=1 -> denied-invalid-receipt
missing message digest -> denied-invalid-receipt
missing public-key identity -> denied-invalid-receipt
missing requested capability -> denied-unknown-capability
missing requested effect -> denied-unknown-effect
unknown requested capability -> denied-unknown-capability
unknown requested effect -> denied-unknown-effect
runtime authority request -> denied-runtime-authority
```

Failures must not read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform effects, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
verified capability gate metadata implementation
```

It does not permit effect execution, capability enforcement, runtime authority, host behavior, network behavior, trust-store behavior, revocation lookup, key handling, object sealing, or kernel behavior.

After verified capability gate metadata exists and is guarded, the next valid planning slice is effect decision evaluation from an allowed metadata-only capability gate.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-verified-capability-gate-contract.sh
```
