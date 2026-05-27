# Latticra Q-Seal ML-KEM API Misuse Resistance

Status: API misuse-resistance policy recorded; public API execution blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM API misuse-resistance contract defines the promotion gate for future public API entry points. It records required evidence for explicit algorithm identification, parameter-set validation, buffer-length preflight, typed key material, no implicit random generation, error taxonomy, API state machine, misuse-case matrix, wrong-parameter-set tests, null and overlap tests, deterministic test-mode guard, secret-output lifetime policy, language-binding policy, documentation examples review, and implementation binding.

This slice does not implement public APIs, execute ML-KEM operations, run misuse tests, expose language bindings, promote implementation code, or allow production cryptography claims.

## Source Posture

```text
fips_203_url=https://csrc.nist.gov/pubs/fips/203/final
fips_140_3_url=https://csrc.nist.gov/pubs/fips/140-3/final
nist_ssdf_url=https://csrc.nist.gov/pubs/sp/800/218/final
```

## Evidence Fields

```text
ml_kem_api_misuse_resistance_present=1
resistance_profile=latticra-q-seal-ml-kem-api-misuse-resistance/0.1
formal_title=Latticra Q-Seal ML-KEM API Misuse Resistance
standards_source=NIST-FIPS-203
module_security_source=NIST-FIPS-140-3-module-interface-security
secure_development_source=NIST-SP-800-218-SSDF
resistance_scope=ML-KEM-public-api-parameter-buffer-key-and-error-misuse-resistance
resistance_state=policy-recorded-misuse-test-evidence-missing
fips_203_source_verified=1
fips_140_3_interface_security_tracked=1
nist_ssdf_source_tracked=1
implementation_frame_bound=1
memory_safety_evidence_bound=1
negative_test_evidence_bound=1
explicit_algorithm_identifier_required=1
parameter_set_validation_required=1
buffer_length_preflight_required=1
typed_key_material_required=1
no_implicit_rng_required=1
error_taxonomy_recorded=0
api_state_machine_recorded=0
misuse_case_matrix_recorded=0
wrong_parameter_set_tests_recorded=0
null_and_overlap_tests_recorded=0
deterministic_test_mode_guard_recorded=0
secret_output_lifetime_policy_recorded=0
language_binding_policy_recorded=0
documentation_examples_review_recorded=0
implementation_binding_recorded=0
api_misuse_tests_executed=0
public_api_execution_allowed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_api_misuse_items_total=21
required_api_misuse_items_satisfied=11
status=ml-kem-api-misuse-resistance-blocked
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_api_misuse_resistance.h
latticra-q-seal/src/q_seal_ml_kem_api_misuse_resistance.c
latticra-q-seal/tests/q_seal_ml_kem_api_misuse_resistance_invariants.c
latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
```

## Runtime Blockers

Public API execution remains blocked until:

- error taxonomy and API state machine are recorded;
- misuse-case matrix is recorded;
- wrong-parameter-set and null/overlap tests are recorded;
- deterministic test-mode guard is recorded;
- secret-output lifetime policy is recorded;
- language-binding policy and documentation examples review are recorded;
- implementation binding is recorded.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
make latticra-q-seal-ml-kem-api-misuse-resistance
```

Expected output:

```text
latticra q-seal ml-kem api misuse resistance invariants: ok
latticra q-seal ml-kem api misuse resistance: ok
```
