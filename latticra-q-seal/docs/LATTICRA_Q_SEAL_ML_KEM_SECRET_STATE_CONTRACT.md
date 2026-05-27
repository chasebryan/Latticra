# Latticra Q-Seal ML-KEM Secret-State Contract

Status: constant-time and zeroization design contract
Date: 2026-05-27
Scope: fail-closed secret-state policy before any ML-KEM primitive implementation.

This slice adds the Latticra Q-Seal ML-KEM secret-state contract. It captures the constant-time and zeroization design rules that future primitive code must satisfy: no secret-dependent branches, no secret-indexed memory access, no secret-dependent early returns, explicit constant-time comparison, constant-time decapsulation, implicit rejection handling, zeroization design, randomness boundary, seed handling, stack-spill review, compiler optimization review, sanitizer strategy, and side-channel review.

## Source Posture

```text
source_url=https://csrc.nist.gov/pubs/fips/203/final
acvp_ml_kem_schema_url=https://pages.nist.gov/ACVP/draft-celi-acvp-ml-kem.html
standards_source=NIST-FIPS-203
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_secret_state_contract.h
latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
latticra-q-seal/tests/q_seal_ml_kem_secret_state_contract_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md
latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md
scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
```

## Current Fields

```text
ml_kem_secret_state_contract_present=1
formal_title=Latticra Q-Seal ML-KEM Secret-State Contract
contract_profile=latticra-q-seal-ml-kem-secret-state-contract/0.1
standards_source=NIST-FIPS-203
source_boundary=clean-room-no-apple-code
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_code_present=0
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
key_generation_enabled=0
encapsulation_enabled=0
decapsulation_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_secret_state_items_total=19
required_secret_state_items_satisfied=4
blocked_reason=secret-inventory-constant-time-zeroization-randomness-compiler-and-side-channel-reviews-missing
status=ml-kem-secret-state-contract-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
```

Expected output:

```text
latticra q-seal ml-kem secret-state contract invariants: ok
latticra q-seal ml-kem secret-state contract: ok
latticra q-seal ml-kem constant-time review invariants: ok
latticra q-seal ml-kem constant-time review: ok
latticra q-seal ml-kem randomness source invariants: ok
latticra q-seal ml-kem randomness source: ok
latticra q-seal ml-kem zeroization evidence invariants: ok
latticra q-seal ml-kem zeroization evidence: ok
latticra q-seal ml-kem side-channel review invariants: ok
latticra q-seal ml-kem side-channel review: ok
```
