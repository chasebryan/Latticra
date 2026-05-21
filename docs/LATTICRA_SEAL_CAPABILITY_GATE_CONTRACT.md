# Latticra Seal Capability Gate Contract

Status: Latticra Seal capability gate contract
Scope: contract for future capability gate metadata after verification receipt metadata. This document does not implement capability enforcement, runtime authority, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal capability gate layer.

The purpose of this layer is to decide how a future receipt may be evaluated before any capability, effect, or authority request can become eligible for execution.

This document does not implement capability gates.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md
docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
include/latticra/seal_measurement.h
include/latticra/seal_manifest.h
include/latticra/seal_signature_policy.h
include/latticra/seal_signature.h
include/latticra/seal_verification_policy.h
include/latticra/seal_verification_receipt.h
src/seal_measurement.c
src/seal_manifest.c
src/seal_signature_policy.c
src/seal_signature.c
src/seal_verification_policy.c
src/seal_verification_receipt.c
scripts/test-latticra-seal-measurement.sh
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature-policy.sh
scripts/test-latticra-seal-signature.sh
scripts/test-latticra-seal-verification-policy.sh
scripts/test-latticra-seal-verification-receipt-contract.sh
scripts/test-latticra-seal-verification-receipt.sh
```

The verification receipt metadata surface remains unverified metadata until cryptographic verification and verified receipt behavior exist.

## Gate boundary

No receipt becomes authority without a capability gate.

No capability gate may allow authority from an unverified receipt.

No capability gate may grant runtime authority until cryptographic verification, verified receipts, and runtime-boundary enforcement exist.

Allowed in this contract slice:

```text
capability gate vocabulary
gate-state labels
requested capability metadata planning
requested effect metadata planning
deny-by-default rule planning
failure-state planning
promotion rules
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
capability enforcement
runtime authority grants
host effect execution
host writes
network access
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

## Initial gate policy

The initial capability gate policy is denied by default.

```text
unverified receipt metadata may be inspected
unverified receipt metadata may not authorize capability use
verified=0 must deny capability gates
authority_usable=0 must deny capability gates
capability_gate_allowed=0 must deny effects
runtime_authority_granted=0 must remain zero
unknown requested capability must deny
unknown requested effect must deny
```

The first implementation after this contract may only add metadata fields and denied-state handling. It must not enforce real capabilities or grant authority.

## Planned gate states

Future records should use explicit labels:

```text
gate_state=unsupported
gate_state=denied-unverified
gate_state=denied-unsupported
gate_state=denied-policy
gate_state=allowed-metadata-only
gate_state=allowed-runtime-gated
gate_state=revoked
gate_state=expired
```

For the next implementation, the expected state is:

```text
gate_state=denied-unverified
```

## Planned gate fields

A future capability gate record should be bounded and deterministic.

Planned fields:

```text
gate_profile
receipt_profile
verification_policy_profile
artifact_digest_algorithm
artifact_digest_hex
signer_identity_label
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
status
```

Initial values before real capability enforcement:

```text
receipt_state=unverified-metadata
verification_state=unsupported
verified=0
authority_usable=0
receipt_capability_gate_allowed=0
gate_allowed=0
gate_state=denied-unverified
runtime_authority_granted=0
status=capability-gate-contract-only
```

## Failure behavior

Future capability gate handling must fail closed.

Required failure states:

```text
null receipt metadata -> invalid
invalid receipt metadata -> invalid
missing artifact digest -> invalid
missing signer identity -> invalid
missing public-key identity -> invalid
missing requested capability -> denied
missing requested effect -> denied
unknown requested capability -> denied
unknown requested effect -> denied
unverified receipt -> denied-unverified
unsupported verification -> denied-unsupported
runtime authority request -> rejected
```

Failures must not parse keys, create keys, persist secrets, contact networks, query revocation status, verify records, sign records, write host files, enforce capabilities, execute effects, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
capability gate metadata implementation
```

It does not permit capability enforcement, runtime authority, cryptographic verification, verified receipt generation, key handling, trust-store behavior, revocation lookup, object sealing, network behavior, host writes, or kernel behavior.

After capability gate metadata exists and is guarded, the next valid planning slice is an effect authorization contract.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-capability-gate-contract.sh
```
