# Latticra Seal Verification Receipt Contract

Status: Latticra Seal verification receipt contract
Scope: contract for future verification receipt metadata after verification policy metadata. This document does not implement cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, capability enforcement, runtime authority, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal verification receipt layer.

The purpose of this layer is to decide how a future verification result may be represented as bounded evidence before any verification result is allowed to participate in capability, gate, or authority decisions.

This document does not implement verification receipts.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_POLICY_CONTRACT.md
docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
include/latticra/seal_measurement.h
include/latticra/seal_manifest.h
include/latticra/seal_signature_policy.h
include/latticra/seal_signature.h
include/latticra/seal_verification_policy.h
src/seal_measurement.c
src/seal_manifest.c
src/seal_signature_policy.c
src/seal_signature.c
src/seal_verification_policy.c
scripts/test-latticra-seal-measurement.sh
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature-policy.sh
scripts/test-latticra-seal-signature.sh
scripts/test-latticra-seal-verification-policy-contract.sh
scripts/test-latticra-seal-verification-policy.sh
```

The verification policy metadata surface remains the source of truth for unsupported verification posture until a later verification receipt implementation exists and is guarded.

## Receipt boundary

No signature metadata becomes authority without a receipt.

No receipt becomes authority without cryptographic verification evidence and a later explicit capability gate.

A verification receipt may summarize verification policy posture, but it must not imply success when cryptographic verification is unsupported or unperformed.

Allowed in this policy slice:

```text
receipt vocabulary
receipt-state labels
verification-result labels
trust-source metadata planning
failure-state planning
promotion rules
non-claims
static guard validation
```

Forbidden in this policy slice:

```text
cryptographic verification
verified receipt generation
public-key parsing
public-key trust store loading
private-key handling
key generation
signature generation
network trust lookup
revocation lookup
certificate authority behavior
hardware token behavior
object sealing
capability enforcement
runtime authority grants
host writes
kernel interaction
```

## Initial receipt policy

The initial verification receipt policy is conservative.

```text
verification policy metadata may be copied
verification_state=unsupported must remain unverified
cryptographic verification is not performed
receipt may not assert verified=true
receipt may not authorize capability gates
receipt may not grant runtime authority
public-key material is not handled
private keys are not handled
network lookup remains disabled
revocation lookup remains disabled
```

The first implementation after this contract may only add metadata fields and unsupported-state handling. It must not verify signatures or emit a verified receipt.

## Planned receipt states

Future records should use explicit labels:

```text
receipt_state=unsupported
receipt_state=unverified-metadata
receipt_state=verification-unsupported
receipt_state=verified
receipt_state=invalid
receipt_state=expired
receipt_state=revoked
receipt_state=policy-denied
```

For the next implementation, the expected state is:

```text
receipt_state=unverified-metadata
```

## Planned receipt fields

A future verification receipt record should be bounded and deterministic.

Planned fields:

```text
receipt_profile
verification_policy_profile
signature_profile
manifest_profile
artifact_digest_algorithm
artifact_digest_hex
signer_identity_label
signature_algorithm
public_key_identity_label
trust_source
verification_state
receipt_state
cryptographic_verification_supported
cryptographic_verification_performed
verified
invalid
authority_usable
capability_gate_allowed
runtime_authority_granted
status
```

Initial values before real verification:

```text
verification_state=unsupported
receipt_state=unverified-metadata
cryptographic_verification_supported=0
cryptographic_verification_performed=0
verified=0
invalid=0
authority_usable=0
capability_gate_allowed=0
runtime_authority_granted=0
status=verification-receipt-contract-only
```

## Failure behavior

Future verification receipt handling must fail closed.

Required failure states:

```text
null verification policy metadata -> invalid
invalid verification policy metadata -> invalid
missing artifact digest -> invalid
missing signer identity -> invalid
missing public-key identity -> invalid
verification unsupported -> unverified-metadata
verified receipt requested before support -> unsupported
capability gate requested before support -> rejected
runtime authority request -> rejected
```

Failures must not parse keys, create keys, persist secrets, contact networks, query revocation status, verify records, sign records, write host files, enforce capabilities, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
verification receipt metadata implementation
```

It does not permit cryptographic verification, verified receipt generation, key handling, trust-store behavior, revocation lookup, object sealing, capability enforcement, network behavior, host writes, or runtime authority.

After verification receipt metadata exists and is guarded, the next valid planning slice is a capability gate contract.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-verification-receipt-contract.sh
```
