# Latticra Seal Verified Capability Gate Implementation

Status: initial verified capability gate metadata implementation
Scope: bounded C metadata surface for evaluating a verified receipt against a narrow metadata-only capability/effect allowlist.

## Purpose

This document records the first Latticra Seal verified capability gate metadata implementation.

The implementation accepts verified receipt promotion metadata plus requested capability, requested effect, and requested scope labels.

It also exposes a stricter crypto-bound entry point that requires a passing crypto graduation gate before evaluating the same metadata-only capability/effect allowlist.

It can allow metadata-only gate evaluation for a narrow local allowlist, but it does not perform effects or grant runtime authority.

## Added files

```text
include/latticra/seal_verified_capability_gate.h
src/seal_verified_capability_gate.c
tests/seal_verified_capability_gate_invariants.c
scripts/test-latticra-seal-verified-capability-gate.sh
include/latticra/seal_crypto_graduation_gate.h
src/seal_crypto_graduation_gate.c
```

## API summary

The verified capability gate metadata surface adds:

```text
latticra_seal_verified_capability_gate_t
latticra_seal_verified_capability_gate_error_t
latticra_seal_verified_capability_gate_error_label
latticra_seal_verified_capability_gate_from_receipt
latticra_seal_verified_capability_gate_from_crypto_graduation_gate
latticra_seal_verified_capability_gate_is_metadata_only
latticra_seal_verified_capability_gate_report
```

## Gate behavior

The implementation:

```text
accepts verified receipt promotion metadata
optionally requires crypto graduation gate metadata through the crypto-bound entry point
requires a passing crypto graduation gate for the crypto-bound entry point
requires crypto graduation gate metadata to match receipt profile, verify profile, digest, public-key identity, receipt state, and verification state
requires receipt_state=verified
requires verification_state=verified
requires verified=1
requires invalid=0
requires message digest metadata
requires public-key identity metadata
accepts requested capability metadata
accepts requested effect metadata
accepts requested scope metadata
allows verified-receipt-inspection
allows verified-receipt-report
allows report-only
allows evaluate-only
sets gate_allowed=1 only for locally allowed metadata-only requests
sets gate_state=allowed-metadata-only only for locally allowed metadata-only requests
renders deterministic verified capability gate metadata
```

Crypto-bound successful gate metadata records:

```text
crypto_graduation_profile=latticra-seal-crypto-graduation-gate/0.1
assurance_baseline_profile=latticra-cryptographic-assurance-key-management/0.1
crypto_graduation_gate_state=graduated-authority-neutral
crypto_graduation_gate_present=1
crypto_graduation_gate_passed=1
standard_expectations_met=1
local_verify_graduated=1
receipt_promotion_graduated=1
authority_promotion_allowed=0
gate_allowed=1
gate_state=allowed-metadata-only
```

## Effect and runtime boundary

Even when gate_allowed=1, these fields remain zero:

```text
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Failure behavior

The implementation fails closed:

```text
null gate output -> LATTICRA_STATUS_NULL_ARGUMENT
null verified receipt input -> invalid-input
invalid verified receipt input -> invalid-receipt
receipt_state not verified -> denied-unverified
verification_state not verified -> denied-unverified
verified flag not set -> denied-unverified
invalid flag set -> denied-invalid-receipt
missing message digest -> denied-invalid-receipt
missing public-key identity -> denied-invalid-receipt
missing requested capability -> missing-requested-capability
missing requested effect -> missing-requested-effect
unknown requested capability -> denied-unknown-capability
unknown requested effect -> denied-unknown-effect
missing crypto graduation gate in crypto-bound entry point -> denied-crypto-graduation-gate
failed crypto graduation gate in crypto-bound entry point -> denied-crypto-graduation-gate
crypto graduation gate / receipt mismatch -> denied-crypto-graduation-gate
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform effects, persist policy, or grant runtime authority.

## Validation

Run locally:

```sh
sh scripts/test-latticra-seal-verified-capability-gate.sh
```

Expected output:

```text
seal verified capability gate invariants: ok
```

## Next valid slice

The next valid Latticra Seal slice is effect decision evaluation from an allowed crypto-graduation-gated metadata-only capability gate.
