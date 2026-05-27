# Latticra Q-Seal ML-KEM API Misuse Resistance

Status: API misuse-resistance policy recorded; public API execution blocked
Date: 2026-05-27

This evidence record defines the API misuse-resistance gate for future Latticra Q-Seal ML-KEM public API work. It records FIPS 203 algorithm scope, FIPS 140-3 module-interface posture, and NIST SSDF secure-development posture before Q-Seal may promote public API entry points.

No error taxonomy is recorded, no API state machine is recorded, no misuse-case matrix is recorded, no misuse tests are executed, no public API execution is allowed, no ML-KEM operation is enabled, no production cryptography claim is allowed, no FIPS claim is allowed, and no runtime authority is granted by this record.

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

## Promotion Rule

Q-Seal may not promote ML-KEM public API entry points until error taxonomy, API state machine, misuse-case matrix, wrong-parameter-set tests, null and overlap tests, deterministic test-mode guard, secret-output lifetime policy, language-binding policy, documentation examples review, and implementation binding are recorded.

This record is a policy and evidence gate only; it is not a public API implementation, not API safety test evidence, not FIPS validation evidence, not an operation-enabling authority, and not a production cryptography claim.
