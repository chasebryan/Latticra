# Latticra Q-Seal ML-KEM Side-Channel Review

Status: side-channel policy recorded; leakage evidence blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM side-channel review defines the leakage-evidence gate for future clean-room ML-KEM primitive code. It records required review posture for power analysis, timing leakage, cache access, fault injection, microarchitectural leakage, hardening decisions, compiler artifacts, platform coverage, negative leakage tests, reviewer signoff, and implementation binding.

This slice does not implement ML-KEM, run leakage measurements, inspect compiler artifacts, promote implementation code, execute operations, or allow production cryptography claims. It exists so future primitive work cannot move forward with only constant-time policy; it must also collect explicit side-channel evidence.

## Source Posture

```text
fips_203_url=https://csrc.nist.gov/pubs/fips/203/final
fips_140_3_url=https://csrc.nist.gov/pubs/fips/140-3/final
```

## Review Fields

```text
ml_kem_side_channel_review_present=1
review_profile=latticra-q-seal-ml-kem-side-channel-review/0.1
formal_title=Latticra Q-Seal ML-KEM Side-Channel Review
standards_source=NIST-FIPS-203
module_security_source=NIST-FIPS-140-3-non-invasive-security-posture
review_scope=ML-KEM-keygen-encap-decap-side-channel-surface
review_state=policy-recorded-leakage-evidence-missing
fips_203_source_verified=1
fips_140_3_non_invasive_security_tracked=1
constant_time_review_bound=1
secret_state_contract_bound=1
power_analysis_review_required=1
timing_leakage_review_required=1
cache_access_review_required=1
leakage_model_recorded=0
power_analysis_test_recorded=0
timing_measurement_recorded=0
cache_access_analysis_recorded=0
fault_injection_review_recorded=0
microarchitectural_leakage_review_recorded=0
masked_or_hardened_design_recorded=0
compiler_artifact_review_recorded=0
test_platform_matrix_recorded=0
negative_leakage_test_recorded=0
reviewer_signoff_recorded=0
implementation_binding_recorded=0
side_channel_tests_executed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_review_items_total=19
required_review_items_satisfied=7
status=ml-kem-side-channel-review-blocked
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_side_channel_review.h
latticra-q-seal/src/q_seal_ml_kem_side_channel_review.c
latticra-q-seal/tests/q_seal_ml_kem_side_channel_review_invariants.c
latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
```

## Runtime Blockers

Implementation promotion remains blocked until:

- the leakage model is recorded;
- power-analysis and timing-measurement evidence are recorded;
- cache-access and microarchitectural leakage reviews are recorded;
- fault-injection review is recorded;
- masking or hardening decisions are recorded;
- compiler artifact review is recorded;
- the test platform matrix and negative leakage tests are recorded;
- reviewer signoff and implementation binding are recorded.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
make latticra-q-seal-ml-kem-side-channel-review
```

Expected output:

```text
latticra q-seal ml-kem side-channel review invariants: ok
latticra q-seal ml-kem side-channel review: ok
```
