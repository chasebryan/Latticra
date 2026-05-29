# Latticra Q-Seal ML-KEM Secret-State Contract

Status: constant-time and zeroization design contract
Date: 2026-05-27
Scope: secret-state, constant-time, zeroization, randomness, compiler, sanitizer, and side-channel blockers before ML-KEM primitive code.

This contract records the secret-state policy that must govern a future clean-room ML-KEM implementation. It does not implement ML-KEM operations, materialize secret data, emit shared secrets, select a zeroization primitive, execute vector tests, link a provider, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

The dedicated constant-time measurement and implementation-promotion gate is recorded in `latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md`; this secret-state contract records policy requirements but does not claim timing evidence.

The dedicated randomness-source gate is recorded in `latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md`; this secret-state contract records randomness-boundary requirements but does not claim entropy validation, DRBG selection, or random byte generation.

The dedicated zeroization gate is recorded in `latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md`; this secret-state contract records zeroization requirements but does not claim a wipe primitive, memory-scan result, or secret-material handling authority.

The dedicated side-channel review gate is recorded in `latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md`; this secret-state contract records side-channel requirements but does not claim leakage measurements, power-analysis evidence, cache-access analysis, fault-injection review, reviewer signoff, or implementation binding.

## Current Fields

```text
ml_kem_secret_state_contract_present=1
formal_title=Latticra Q-Seal ML-KEM Secret-State Contract
contract_profile=latticra-q-seal-ml-kem-secret-state-contract/0.1
standards_source=NIST-FIPS-203
source_boundary=clean-room-no-apple-code
secret_material_inventory_required=1
secret_material_inventory_recorded=0
secret_dependent_branch_forbidden=1
secret_dependent_branch_review_recorded=0
secret_indexed_memory_forbidden=1
secret_indexed_memory_review_recorded=0
secret_dependent_early_return_forbidden=1
secret_dependent_early_return_review_recorded=0
constant_time_compare_required=1
constant_time_compare_recorded=0
constant_time_decapsulation_required=1
constant_time_decapsulation_recorded=0
implicit_rejection_required=1
implicit_rejection_recorded=0
zeroization_required=1
zeroization_design_recorded=0
zeroization_primitive_selected=0
zeroization_primitive_implemented=0
randomness_boundary_required=1
randomness_boundary_recorded=0
seed_material_handling_required=1
seed_material_handling_recorded=0
stack_secret_spill_review_required=1
stack_secret_spill_review_recorded=0
compiler_optimization_review_required=1
compiler_optimization_review_recorded=0
sanitizer_strategy_required=1
sanitizer_strategy_recorded=0
side_channel_review_required=1
side_channel_review_recorded=0
operations_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_secret_state_items_total=19
required_secret_state_items_satisfied=4
status=ml-kem-secret-state-contract-blocked
```

## Non-Claims

This contract is not a constant-time proof, not a side-channel review, not a zeroization implementation, not randomness evidence, not ML-KEM implementation code, not ACVP evidence, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
