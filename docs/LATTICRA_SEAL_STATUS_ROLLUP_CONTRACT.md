# Latticra Seal Status Rollup Contract

Status: Latticra Seal status rollup contract
Scope: contract for future status rollup metadata after runtime handoff metadata. This document does not implement runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal status rollup layer.

The purpose of this layer is to provide one bounded summary of the current Seal chain:

```text
report -> measurement -> manifest -> signature policy -> signature metadata -> verification policy -> verification receipt -> capability gate -> effect decision -> runtime handoff
```

This document does not implement status rollup behavior.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_REPORT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md
include/latticra/seal_report.h
include/latticra/seal_measurement.h
include/latticra/seal_manifest.h
include/latticra/seal_signature_policy.h
include/latticra/seal_signature.h
include/latticra/seal_verification_policy.h
include/latticra/seal_verification_receipt.h
include/latticra/seal_capability_gate.h
include/latticra/seal_effect_decision.h
include/latticra/seal_runtime_handoff.h
src/seal_report.c
src/seal_measurement.c
src/seal_manifest.c
src/seal_signature_policy.c
src/seal_signature.c
src/seal_verification_policy.c
src/seal_verification_receipt.c
src/seal_capability_gate.c
src/seal_effect_decision.c
src/seal_runtime_handoff.c
scripts/test-latticra-seal-report.sh
scripts/test-latticra-seal-measurement.sh
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature-policy.sh
scripts/test-latticra-seal-signature.sh
scripts/test-latticra-seal-verification-policy.sh
scripts/test-latticra-seal-verification-receipt.sh
scripts/test-latticra-seal-capability-gate.sh
scripts/test-latticra-seal-effect-decision.sh
scripts/test-latticra-seal-runtime-handoff-contract.sh
scripts/test-latticra-seal-runtime-handoff.sh
```

The runtime handoff metadata surface remains inactive metadata until runtime-boundary behavior exists and is guarded.

## Rollup boundary

The rollup may summarize Seal layer posture.

The rollup may not convert unsupported, unverified, denied, or inactive metadata into authority.

The rollup may not perform host reads, host writes, network access, kernel interaction, or runtime behavior.

Allowed in this contract slice:

```text
rollup vocabulary
rollup-state labels
layer-present metadata planning
unsupported-state summary planning
denied-state summary planning
inactive-runtime summary planning
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

## Initial rollup policy

The initial status rollup policy is conservative and metadata-only.

```text
all implemented Seal layers may be summarized
cryptographic verification remains unsupported
verified receipt remains false
capability gate remains denied
effect decision remains denied
runtime handoff remains inactive
runtime boundary remains disabled
runtime authority remains zero
host read/write/network behavior remains zero
```

The first implementation after this contract may only add metadata fields and deterministic rendering. It must not perform runtime behavior.

## Planned rollup states

Future records should use explicit labels:

```text
rollup_state=metadata-only
rollup_state=incomplete
rollup_state=unsupported
rollup_state=denied
rollup_state=runtime-disabled
rollup_state=ready-for-review
```

For the next implementation, the expected state is:

```text
rollup_state=metadata-only
```

## Planned rollup fields

A future status rollup record should be bounded and deterministic.

Planned fields:

```text
rollup_profile
report_present
measurement_present
manifest_present
signature_policy_present
signature_metadata_present
verification_policy_present
verification_receipt_present
capability_gate_present
effect_decision_present
runtime_handoff_present
cryptographic_verification_supported
verified
capability_gate_allowed
effect_allowed
handoff_active
runtime_boundary_state
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
rollup_state
status
```

Initial values before real authority:

```text
cryptographic_verification_supported=0
verified=0
capability_gate_allowed=0
effect_allowed=0
handoff_active=0
runtime_boundary_state=disabled
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
rollup_state=metadata-only
status=status-rollup-contract-only
```

## Failure behavior

Future status rollup handling must fail closed.

Required failure states:

```text
null rollup output -> invalid
missing required layer metadata -> incomplete
unsupported verification -> metadata-only
unverified receipt -> metadata-only
denied capability gate -> metadata-only
denied effect decision -> metadata-only
inactive runtime handoff -> metadata-only
runtime authority request -> rejected
```

Failures must not parse keys, create keys, persist secrets, contact networks, query revocation status, verify records, sign records, read host files, write host files, enforce capabilities, execute effects, call runtime components, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
status rollup metadata implementation
```

It does not permit runtime execution, effect execution, capability enforcement, runtime authority, cryptographic verification, verified receipt generation, key handling, trust-store behavior, revocation lookup, object sealing, network behavior, host reads, host writes, or kernel behavior.

After status rollup metadata exists and is guarded, the next valid planning slice is Seal documentation/index alignment.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-status-rollup-contract.sh
```
