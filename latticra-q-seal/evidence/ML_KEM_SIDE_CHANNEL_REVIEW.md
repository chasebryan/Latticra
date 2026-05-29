# Latticra Q-Seal ML-KEM Side-Channel Review

Status: side-channel policy recorded; leakage evidence blocked
Date: 2026-05-27

This evidence record defines the side-channel review gate for future Latticra Q-Seal ML-KEM implementation work. It records the FIPS 203 algorithm scope and the FIPS 140-3 non-invasive security posture that must be addressed before Q-Seal may promote any clean-room ML-KEM primitive implementation.

No leakage model is recorded, no power-analysis test is recorded, no timing measurement is recorded, no cache-access analysis is recorded, no fault-injection review is recorded, no side-channel tests are executed, no ML-KEM operation is enabled, no production cryptography claim is allowed, no FIPS claim is allowed, and no runtime authority is granted by this record.

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

## Promotion Rule

Q-Seal may not promote ML-KEM primitive code until a leakage model, power-analysis test record, timing measurement record, cache-access analysis, fault-injection review, microarchitectural leakage review, masking or hardening decision, compiler artifact review, test platform matrix, negative leakage test, reviewer signoff, and implementation binding are recorded.

This record is a policy and evidence gate only; it is not a side-channel test result, not FIPS validation evidence, not an operation-enabling authority, and not a production cryptography claim.
