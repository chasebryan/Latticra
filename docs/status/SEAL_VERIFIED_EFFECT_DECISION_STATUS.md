# Latticra Seal Verified Effect Decision Status

Status: status record for the Latticra Seal verified effect decision metadata surface
Source: local follow-up slice
Scope: status and public-entry alignment after the Seal verified effect decision contract and metadata implementation, now carrying crypto graduation metadata forward when present on the verified capability gate. This record does not add effect execution, capability enforcement, runtime authority, host effects, network behavior, signing, key generation, private-key storage, public-key trust stores, network trust lookup, revocation lookup, object sealing, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This status record makes the Latticra Seal verified effect decision implementation visible from public entry points.

The decision consumes verified capability gate metadata and evaluates a narrow local metadata-only effect request. When the gate carries crypto graduation metadata, the decision requires that evidence to remain passed, standard-aligned, and authority-neutral before allowing the metadata-only effect classification.

It is effect classification metadata, not effect execution.

## Reviewed files

```text
docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_CONTRACT.md
docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_IMPLEMENTATION.md
docs/status/SEAL_VERIFIED_EFFECT_DECISION_STATUS.md
docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md
docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
include/latticra/seal_verified_effect_decision.h
src/seal_verified_effect_decision.c
tests/seal_verified_effect_decision_invariants.c
scripts/test-latticra-seal-verified-effect-decision-contract.sh
scripts/test-latticra-seal-verified-effect-decision.sh
scripts/test-latticra-seal-verified-effect-decision-status.sh
README.md
STATUS.md
docs/status/README.md
docs/status/CURRENT_STATUS.md
docs/FOUNDATION_INDEX.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/project_notes/README.md
```

## Current checkpoint

Current verified effect decision posture:

```text
seal_verified_effect_decision_contract_present=1
seal_verified_effect_decision_implementation_present=1
seal_verified_effect_decision_header_present=1
seal_verified_effect_decision_source_present=1
seal_verified_effect_decision_invariant_test_present=1
seal_verified_effect_decision_runner_present=1
seal_verified_effect_decision_status_present=1
seal_verified_capability_gate_status_present=1
seal_crypto_graduation_gate_status_present=1
readme_links_verified_effect_decision_contract=1
readme_links_verified_effect_decision_implementation=1
readme_links_verified_effect_decision_status=1
root_status_mentions_verified_effect_decision_status=1
status_index_links_verified_effect_decision_status=1
foundation_index_links_verified_effect_decision_status=1
project_notes_mark_verified_effect_decision_status_complete=1
decision_profile=latticra-seal-verified-effect-decision/0.1
gate_profile=latticra-seal-verified-capability-gate/0.1
receipt_profile=latticra-seal-verified-receipt/0.1
verify_profile=latticra-seal-ed25519-verify/0.1
message_digest_algorithm=SHA-256
public_key_identity_label=rfc8032-test-key
receipt_state=verified
verification_state=verified
crypto_graduation_profile=latticra-seal-crypto-graduation-gate/0.1
assurance_baseline_profile=latticra-cryptographic-assurance-key-management/0.1
crypto_graduation_gate_state=graduated-authority-neutral
requested_capability=verified-receipt-report
requested_effect=report-only
requested_scope=local-fixture-scope
crypto_graduation_gate_present=1
crypto_graduation_gate_passed=1
standard_expectations_met=1
local_verify_graduated=1
receipt_promotion_graduated=1
authority_promotion_allowed=0
verified=1
authority_usable=0
receipt_capability_gate_allowed=0
gate_allowed=1
gate_state=allowed-metadata-only
decision_state=allowed-report-only
effect_allowed=1
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
error=ok
status=verified-effect-decision-metadata
verified_effect_decision_added=1
effect_execution_added=0
capability_enforcement_added=0
signing_added=0
key_generation_added=0
private_key_handling_added=0
trust_store_behavior_added=0
revocation_lookup_added=0
network_behavior_changed=0
host_behavior_changed=0
```

## Validation

This status surface is covered by:

```sh
sh scripts/test-latticra-seal-verified-effect-decision-status.sh
```

The underlying implementation remains covered by:

```sh
sh scripts/test-latticra-seal-verified-effect-decision.sh
```

Expected output:

```text
seal verified effect decision status: ok
seal verified effect decision invariants: ok
```

## Boundary

This status record is documentation/status alignment only.

The verified effect decision implementation evaluates a verified capability gate record against a narrow local metadata-only effect request. If the gate includes crypto graduation evidence, the decision requires `crypto_graduation_gate_passed=1`, `standard_expectations_met=1`, and `authority_promotion_allowed=0`. A successful decision may set `effect_allowed=1` and `decision_state=allowed-report-only`, but it remains metadata-only and authority-neutral.

It does not add effect execution, capability enforcement, runtime behavior, host behavior, network behavior, signing, key generation, private-key handling, trust-store behavior, revocation lookup, production readiness, external endorsement, or authority grants.

## Current next valid slice

No completion-estimate review is required from this status/public-entry alignment.

The runtime handoff evaluation status/public-entry alignment now provides the predecessor for the next valid Latticra Seal slice: runtime handoff report or policy decision report propagation from eligible crypto-graduation-gated metadata-only runtime handoff evaluation, runtime handoff report status/public-entry alignment, or another narrow status/index alignment follow-up.
