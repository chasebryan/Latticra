# Latticra Q-Seal ML-KEM Randomness Source Contract

Status: randomness policy recorded; random bit generation blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM randomness-source contract defines the evidence gate for future random byte generation used by ML-KEM key generation and encapsulation seed material. It binds the Q-Seal design frame to FIPS 203 and the NIST SP 800-90A / SP 800-90B random-bit-generation evidence path without selecting a platform entropy source, selecting a DRBG, loading deterministic test seeds, or generating random bytes.

This slice does not implement a DRBG, read platform randomness, execute ML-KEM, create key material, emit shared secrets, or allow production cryptography claims.

## Source Posture

```text
fips_203_url=https://csrc.nist.gov/pubs/fips/203/final
sp_800_90a_url=https://csrc.nist.gov/pubs/sp/800/90/a/r1/final
sp_800_90b_url=https://csrc.nist.gov/pubs/sp/800/90/b/final
```

## Randomness Fields

```text
ml_kem_randomness_source_contract_present=1
randomness_profile=latticra-q-seal-ml-kem-randomness-source/0.1
formal_title=Latticra Q-Seal ML-KEM Randomness Source Contract
standards_source=NIST-FIPS-203
random_bit_generation_source=NIST-SP-800-90A-and-NIST-SP-800-90B
randomness_scope=ML-KEM-keygen-encapsulation-seed-material
randomness_state=policy-recorded-random-bit-generation-blocked
fips_203_source_verified=1
sp_800_90a_tracked=1
sp_800_90b_tracked=1
keygen_seed_material_required=1
encapsulation_seed_material_required=1
deterministic_test_seed_separation_required=1
entropy_source_inventory_recorded=0
entropy_source_validation_recorded=0
drbg_selection_recorded=0
drbg_security_strength_recorded=0
seed_derivation_policy_recorded=0
reseed_policy_recorded=0
prediction_resistance_policy_recorded=0
health_tests_policy_recorded=0
failure_mode_policy_recorded=0
platform_rng_boundary_recorded=0
entropy_review_signoff_recorded=0
implementation_binding_recorded=0
random_bytes_generated=0
deterministic_test_seed_loaded=0
deterministic_rng_mode_enabled=0
random_bit_generation_allowed=0
key_generation_randomness_allowed=0
encapsulation_randomness_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_randomness_items_total=18
required_randomness_items_satisfied=6
status=ml-kem-randomness-source-blocked
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_randomness_source.h
latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
latticra-q-seal/tests/q_seal_ml_kem_randomness_source_invariants.c
latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
```

## Runtime Blockers

Random byte generation remains blocked until:

- entropy source inventory and validation evidence are recorded;
- DRBG selection and security-strength review are recorded;
- seed derivation, reseed, prediction-resistance, health-test, and failure-mode policies are recorded;
- the platform RNG boundary is reviewed;
- entropy review signoff is recorded;
- implementation binding is recorded;
- deterministic test seed handling is proven separate from production randomness.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
make latticra-q-seal-ml-kem-randomness-source
```

Expected output:

```text
latticra q-seal ml-kem randomness source invariants: ok
latticra q-seal ml-kem randomness source: ok
```
