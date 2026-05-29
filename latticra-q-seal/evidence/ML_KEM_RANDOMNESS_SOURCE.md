# Latticra Q-Seal ML-KEM Randomness Source Evidence

Status: randomness policy recorded; random bit generation blocked
Date: 2026-05-27

This evidence record defines the randomness-source gate for future Latticra Q-Seal ML-KEM implementation work. It records the FIPS 203 linkage for ML-KEM seed material and the NIST SP 800-90A / SP 800-90B random-bit-generation evidence that must exist before Q-Seal can generate random bytes for key generation or encapsulation.

No entropy source is selected, no DRBG is selected, no deterministic test seed is loaded, no random bytes are generated, no ML-KEM operation is enabled, no production cryptography claim is allowed, no FIPS claim is allowed, and no runtime authority is granted by this record.

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

## Promotion Rule

Q-Seal may not generate random bytes for ML-KEM until the entropy source inventory, entropy validation evidence, DRBG selection, DRBG security-strength review, seed derivation policy, reseed policy, prediction-resistance policy, health-test policy, failure-mode policy, platform RNG boundary, entropy review signoff, and implementation binding are recorded.

This record is a policy and evidence gate only; it is not an entropy validation result, not a DRBG implementation, not a random byte generator, not a FIPS validation artifact, not an operation-enabling authority, and not a production cryptography claim.
