# Latticra Seal Effect Decision Contract

Status: Latticra Seal effect decision contract
Scope: contract for future effect decision metadata after capability gate metadata. This document does not implement effect execution, capability enforcement, runtime authority, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal effect decision layer.

The purpose of this layer is to decide how a future capability gate record may be represented as an effect decision before any requested effect can become eligible for execution.

This document does not implement effect decisions.

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
docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md
docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
include/latticra/seal_measurement.h
include/latticra/seal_manifest.h
include/latticra/seal_signature_policy.h
include/latticra/seal_signature.h
include/latticra/seal_verification_policy.h
include/latticra/seal_verification_receipt.h
include/latticra/seal_capability_gate.h
src/seal_measurement.c
src/seal_manifest.c
src/seal_signature_policy.c
src/seal_signature.c
src/seal_verification_policy.c
src/seal_verification_receipt.c
src/seal_capability_gate.c
scripts/test-latticra-seal-measurement.sh
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature-policy.sh
scripts/test-latticra-seal-signature.sh
scripts/test-latticra-seal-verification-policy.sh
scripts/test-latticra-seal-verification-receipt.sh
scripts/test-latticra-seal-capability-gate-contract.sh
scripts/test-latticra-seal-capability-gate.sh
```

The capability gate metadata surface remains denied metadata until cryptographic verification, verified receipt behavior, and real capability enforcement exist.

## Effect boundary

No gate becomes an executable effect.

No denied gate may produce an allowed effect decision.

No effect decision may perform host reads, host writes, network access, kernel interaction, or runtime authority until a later runtime-boundary implementation explicitly permits and guards those behaviors.

Allowed in this contract slice:

```text
effect decision vocabulary
decision-state labels
requested effect metadata planning
requested capability metadata planning
no-effect posture planning
failure-state planning
promotion rules
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
effect execution
host reads
host writes
network access
runtime authority grants
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

## Initial decision policy

The initial effect decision policy is denied by default.

```text
denied gate metadata may be inspected
gate_allowed=0 must deny effect decisions
runtime_authority_granted=0 must remain zero
unknown requested effect must deny
unknown requested capability must deny
effect_performed must remain zero
host_read_performed must remain zero
host_write_performed must remain zero
network_performed must remain zero
```

The first implementation after this contract may only add metadata fields and denied-state handling. It must not perform effects.

## Planned decision states

Future records should use explicit labels:

```text
decision_state=unsupported
decision_state=denied-gate
decision_state=denied-unverified
decision_state=denied-unsupported
decision_state=denied-policy
decision_state=allowed-metadata-only
decision_state=allowed-runtime-gated
```

For the next implementation, the expected state is:

```text
decision_state=denied-gate
```

## Planned decision fields

A future effect decision record should be bounded and deterministic.

Planned fields:

```text
decision_profile
gate_profile
receipt_profile
artifact_digest_algorithm
artifact_digest_hex
requested_capability
requested_effect
requested_scope
gate_state
gate_allowed
effect_allowed
effect_performed
host_read_performed
host_write_performed
network_performed
runtime_authority_granted
status
```

Initial values before real effect handling:

```text
gate_allowed=0
effect_allowed=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
runtime_authority_granted=0
decision_state=denied-gate
status=effect-decision-contract-only
```

## Failure behavior

Future effect decision handling must fail closed.

Required failure states:

```text
null capability gate metadata -> invalid
invalid capability gate metadata -> invalid
missing artifact digest -> invalid
missing requested capability -> denied
missing requested effect -> denied
unknown requested capability -> denied
unknown requested effect -> denied
gate_allowed=0 -> denied-gate
runtime authority request -> rejected
```

Failures must not parse keys, create keys, persist secrets, contact networks, query revocation status, verify records, sign records, read host files, write host files, enforce capabilities, execute effects, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
effect decision metadata implementation
```

It does not permit effect execution, capability enforcement, runtime authority, cryptographic verification, verified receipt generation, key handling, trust-store behavior, revocation lookup, object sealing, network behavior, host reads, host writes, or kernel behavior.

After effect decision metadata exists and is guarded, the next valid planning slice is a runtime handoff contract.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-effect-decision-contract.sh
```
