# Latticra Seal Runtime Handoff Evaluation Implementation

Status: initial runtime handoff evaluation metadata implementation
Scope: bounded C metadata surface for classifying allowed metadata-only verified effect decision output into deterministic runtime handoff eligibility. This does not implement runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, trust-store loading, revocation lookup, key generation, private-key handling, object sealing, kernel interaction, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal runtime handoff evaluation metadata implementation.

The implementation consumes verified effect decision metadata and classifies whether the requested metadata-only runtime handoff remains eligible as report-only or evaluate-only.

When the verified effect decision carries crypto graduation metadata, the evaluation copies that evidence forward and requires it to remain passed, standard-aligned, and authority-neutral.

The evaluation is handoff classification, not runtime handoff.

## Added files

```text
include/latticra/seal_runtime_handoff_evaluation.h
src/seal_runtime_handoff_evaluation.c
tests/seal_runtime_handoff_evaluation_invariants.c
scripts/test-latticra-seal-runtime-handoff-evaluation.sh
```

## Required predecessor

This implementation depends on the verified effect decision metadata surface:

```text
include/latticra/seal_verified_effect_decision.h
src/seal_verified_effect_decision.c
tests/seal_verified_effect_decision_invariants.c
scripts/test-latticra-seal-verified-effect-decision.sh
docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_IMPLEMENTATION.md
```

## API summary

The runtime handoff evaluation metadata surface adds:

```text
latticra_seal_runtime_handoff_evaluation_t
latticra_seal_runtime_handoff_evaluation_error_t
latticra_seal_runtime_handoff_evaluation_error_label
latticra_seal_runtime_handoff_evaluation_from_decision
latticra_seal_runtime_handoff_evaluation_is_metadata_only
latticra_seal_runtime_handoff_evaluation_report
```

## Evaluation behavior

The implementation:

```text
accepts verified effect decision metadata
copies crypto graduation gate metadata when present
requires crypto_graduation_gate_passed=1 when crypto_graduation_gate_present=1
requires standard_expectations_met=1 when crypto_graduation_gate_present=1
requires local_verify_graduated=1 when crypto_graduation_gate_present=1
requires receipt_promotion_graduated=1 when crypto_graduation_gate_present=1
requires authority_promotion_allowed=0 when crypto_graduation_gate_present=1
requires effect_allowed=1
requires decision_state=allowed-report-only or decision_state=allowed-evaluate-only
requires runtime_authority_granted=0
requires effect_performed=0
requires host_read_performed=0
requires host_write_performed=0
requires network_performed=0
accepts requested handoff metadata
classifies report-only as handoff_state=eligible-report-only
classifies evaluate-only as handoff_state=eligible-evaluate-only
sets handoff_eligible=1 only for metadata-only report/evaluate handoff evaluations
renders deterministic runtime handoff evaluation metadata
```

Crypto-bound handoff evaluation metadata records:

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
handoff_state=eligible-report-only
handoff_eligible=1
handoff_performed=0
runtime_authority_granted=0
```

## Effect and runtime boundary

Even when handoff_eligible=1, these fields remain zero:

```text
handoff_performed=0
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

This implementation does not perform runtime handoff, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, persist policy, load trust stores, look up revocation status, generate keys, handle private keys, seal objects, or interact with the kernel.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null verified effect decision -> invalid-input
invalid verified effect decision -> invalid-decision
failed crypto graduation gate evidence -> denied-crypto-graduation-gate
authority-bearing crypto graduation evidence -> denied-crypto-graduation-gate
effect_allowed=0 -> denied-effect
decision_state not allowed-report-only or allowed-evaluate-only -> denied-decision
missing requested handoff -> missing-requested-handoff
unknown requested handoff -> denied-unknown-handoff
runtime authority already granted -> denied-runtime-authority
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not perform handoff, perform effects, read host files, write host files, contact networks, or grant runtime authority.

## Validation

Run locally:

```sh
sh scripts/test-latticra-seal-runtime-handoff-evaluation.sh
```

Expected output:

```text
seal runtime handoff evaluation invariants: ok
```

## Next valid slice

The next valid Latticra Seal planning slice is sealed report envelope or policy decision report propagation from ready crypto-graduation-gated metadata-only runtime handoff report metadata.

That next slice should remain contract-first and should not perform runtime handoff unless separately implemented and guarded.
