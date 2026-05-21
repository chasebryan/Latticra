# Latticra Seal Verification Policy Contract

Status: Latticra Seal verification policy contract
Scope: policy for future verification behavior after the signature metadata envelope. This document does not implement cryptographic verification, public-key parsing, public-key trust stores, key generation, private-key storage, network trust lookup, revocation lookup, object sealing, capability enforcement, runtime authority, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal verification policy layer.

The purpose of this layer is to decide how future signature metadata may be evaluated before any signature metadata is allowed to participate in capability, gate, or authority decisions.

This document does not implement cryptographic verification.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_CONTRACT.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION_CONTRACT.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
include/latticra/seal_measurement.h
include/latticra/seal_manifest.h
include/latticra/seal_signature_policy.h
include/latticra/seal_signature.h
src/seal_measurement.c
src/seal_manifest.c
src/seal_signature_policy.c
src/seal_signature.c
scripts/test-latticra-seal-measurement.sh
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature-policy.sh
scripts/test-latticra-seal-signature.sh
```

The signature metadata surface remains metadata-only until a later verification implementation explicitly adds cryptographic verification and evidence.

## Verification boundary

No signature metadata becomes authority without verification policy.

No verification policy becomes authority without a later verified evidence record and explicit capability gate.

Allowed in this policy slice:

```text
verification vocabulary
verification-state labels
trust-source labels
public-key metadata planning
algorithm acceptance policy
failure-state planning
promotion rules
non-claims
static guard validation
```

Forbidden in this policy slice:

```text
cryptographic verification
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

## Initial verification policy

The initial verification policy is conservative.

```text
signature metadata may be inspected
signature metadata may not be trusted as verified
verification support remains disabled
cryptographic verification is not performed
public-key material is not handled
private keys are not handled
network lookup remains disabled
runtime authority remains denied
```

The first implementation after this contract may only add metadata fields and unsupported-state handling. It must not verify signatures.

## Planned verification states

Future records should use explicit labels:

```text
verification_state=unsupported
verification_state=unverified
verification_state=verification-requested
verification_state=verified
verification_state=invalid
verification_state=expired
verification_state=revoked
verification_state=unsupported-algorithm
verification_state=missing-public-key
verification_state=policy-denied
```

For the next implementation, the expected state is:

```text
verification_state=unsupported
```

## Planned policy fields

A future verification policy record should be bounded and deterministic.

Planned fields:

```text
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
cryptographic_verification_supported
cryptographic_verification_performed
public_key_material_handling
private_key_handling
network_lookup_allowed
revocation_lookup_allowed
runtime_authority_granted
status
```

Initial values before implementation:

```text
cryptographic_verification_supported=0
cryptographic_verification_performed=0
public_key_material_handling=0
private_key_handling=0
network_lookup_allowed=0
revocation_lookup_allowed=0
runtime_authority_granted=0
status=verification-policy-only
```

## Failure behavior

Future verification policy handling must fail closed.

Required failure states:

```text
null signature metadata -> invalid
invalid signature metadata -> invalid
missing artifact digest -> invalid
missing signer identity -> invalid
unsupported algorithm -> unsupported-algorithm
missing public-key identity -> unsupported
verification requested before support -> unsupported
private-key input -> rejected
network lookup request -> rejected
revocation lookup request -> rejected
runtime authority request -> rejected
```

Failures must not parse keys, create keys, persist secrets, contact networks, verify records, sign records, write host files, enforce capabilities, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
verification policy metadata implementation
```

It does not permit cryptographic verification, key handling, trust-store behavior, revocation lookup, object sealing, capability enforcement, network behavior, host writes, or runtime authority.

After verification policy metadata exists and is guarded, the next valid planning slice is a verification receipt contract.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-verification-policy-contract.sh
```
