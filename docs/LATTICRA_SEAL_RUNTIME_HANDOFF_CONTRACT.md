# Latticra Seal Runtime Handoff Contract

Status: Latticra Seal runtime handoff contract
Scope: contract for future runtime handoff metadata after effect decision metadata. This document does not implement runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal runtime handoff layer.

The purpose of this layer is to decide how a future effect decision may be represented at the runtime boundary before any runtime component is allowed to act on it.

This document does not implement runtime handoff behavior.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md
docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md
include/latticra/seal_measurement.h
include/latticra/seal_manifest.h
include/latticra/seal_signature_policy.h
include/latticra/seal_signature.h
include/latticra/seal_verification_policy.h
include/latticra/seal_verification_receipt.h
include/latticra/seal_capability_gate.h
include/latticra/seal_effect_decision.h
src/seal_measurement.c
src/seal_manifest.c
src/seal_signature_policy.c
src/seal_signature.c
src/seal_verification_policy.c
src/seal_verification_receipt.c
src/seal_capability_gate.c
src/seal_effect_decision.c
scripts/test-latticra-seal-measurement.sh
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature-policy.sh
scripts/test-latticra-seal-signature.sh
scripts/test-latticra-seal-verification-policy.sh
scripts/test-latticra-seal-verification-receipt.sh
scripts/test-latticra-seal-capability-gate.sh
scripts/test-latticra-seal-effect-decision-contract.sh
scripts/test-latticra-seal-effect-decision.sh
```

The effect decision metadata surface remains denied metadata until runtime handoff metadata exists and is guarded.

## Handoff boundary

No effect decision becomes runtime behavior.

No denied decision may produce an active runtime handoff.

No runtime handoff may perform host reads, host writes, network access, kernel interaction, or authority grants until a later runtime-boundary implementation explicitly permits and guards those behaviors.

Allowed in this contract slice:

```text
runtime handoff vocabulary
handoff-state labels
decision metadata planning
runtime-boundary label planning
no-runtime posture planning
failure-state planning
promotion rules
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
runtime execution
runtime authority grants
effect execution
host reads
host writes
network access
capability enforcement
cryptographic verification
verified receipt generation
public-key parsing
public-key trust store loading
private-key handling
key generation
signature generation
revocation lookup
object sealing
kernel interaction
```

## Initial handoff policy

The initial runtime handoff policy is denied by default.

```text
denied decision metadata may be inspected
effect_allowed=0 must deny handoff activation
effect_performed=0 must remain zero
runtime_authority_granted=0 must remain zero
handoff_active must remain zero
runtime_effect_performed must remain zero
unknown boundary target must deny
unknown runtime request must deny
```

The first implementation after this contract may only add metadata fields and denied-state handling. It must not perform runtime behavior.

## Planned handoff states

Future records should use explicit labels:

```text
handoff_state=unsupported
handoff_state=denied-decision
handoff_state=denied-runtime-boundary
handoff_state=denied-policy
handoff_state=inactive-metadata
handoff_state=active-runtime-gated
```

For the next implementation, the expected state is:

```text
handoff_state=denied-decision
```

## Planned handoff fields

A future runtime handoff record should be bounded and deterministic.

Planned fields:

```text
handoff_profile
decision_profile
gate_profile
requested_capability
requested_effect
requested_scope
decision_state
effect_allowed
effect_performed
runtime_boundary_state
runtime_request_label
handoff_active
runtime_effect_performed
host_read_performed
host_write_performed
network_performed
runtime_authority_granted
status
```

Initial values before real runtime behavior:

```text
effect_allowed=0
effect_performed=0
runtime_boundary_state=disabled
handoff_active=0
runtime_effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
runtime_authority_granted=0
handoff_state=denied-decision
status=runtime-handoff-contract-only
```

## Failure behavior

Future runtime handoff handling must fail closed.

Required failure states:

```text
null effect decision metadata -> invalid
invalid effect decision metadata -> invalid
missing requested capability -> denied
missing requested effect -> denied
unknown runtime boundary -> denied
unknown runtime request -> denied
effect_allowed=0 -> denied-decision
runtime boundary disabled -> denied-runtime-boundary
runtime authority request -> rejected
```

Failures must not parse keys, create keys, persist secrets, contact networks, query revocation status, verify records, sign records, read host files, write host files, enforce capabilities, execute effects, call runtime components, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
runtime handoff metadata implementation
```

It does not permit runtime execution, effect execution, capability enforcement, runtime authority, cryptographic verification, verified receipt generation, key handling, trust-store behavior, revocation lookup, object sealing, network behavior, host reads, host writes, or kernel behavior.

After runtime handoff metadata exists and is guarded, the next valid planning slice is a Seal status rollup contract.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-runtime-handoff-contract.sh
```
