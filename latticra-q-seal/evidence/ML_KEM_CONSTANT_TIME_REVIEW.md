# Latticra Q-Seal ML-KEM Constant-Time Review Evidence

Status: constant-time policy recorded; implementation promotion blocked
Date: 2026-05-27

This evidence record defines the constant-time review gate for future Latticra Q-Seal ML-KEM implementation work. It records the policy requirements for secret-dependent control flow, secret-indexed memory access, loop bounds, early returns, implicit rejection, compiler optimization review, measurement evidence, assembly review, CI gates, and formal signoff.

No timing measurement is executed, no implementation is promoted, no ML-KEM operation is enabled, no production cryptography claim is allowed, no FIPS claim is allowed, and no runtime authority is granted by this record.

```text
ml_kem_constant_time_review_present=1
review_profile=latticra-q-seal-ml-kem-constant-time-review/0.1
formal_title=Latticra Q-Seal ML-KEM Constant-Time Review
standards_source=NIST-FIPS-203
review_scope=ML-KEM-keygen-encap-decap-secret-state
analysis_policy=no-secret-dependent-control-flow-or-addresses
review_state=design-rules-recorded-measurement-not-recorded
fips_203_source_verified=1
secret_dependent_branch_forbidden=1
secret_dependent_memory_index_forbidden=1
secret_dependent_loop_bound_forbidden=1
secret_dependent_early_return_forbidden=1
constant_time_compare_required=1
decapsulation_implicit_rejection_required=1
compiler_optimization_review_required=1
dudect_measurement_recorded=0
ctgrind_or_static_analysis_recorded=0
generated_assembly_review_recorded=0
optimizer_flag_review_recorded=0
secret_state_inventory_bound=0
negative_timing_test_recorded=0
cross_platform_timing_review_recorded=0
formal_reviewer_signoff_recorded=0
ci_constant_time_gate_recorded=0
implementation_binding_recorded=0
measurement_execution_allowed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_review_items_total=18
required_review_items_satisfied=8
status=ml-kem-constant-time-review-blocked
```

## Promotion Rule

Q-Seal may not promote ML-KEM implementation code until the measurement record, static-analysis record, generated-assembly review, optimizer flag review, secret-state inventory binding, negative timing tests, cross-platform timing review, formal reviewer signoff, CI constant-time gate, and implementation binding are recorded.

This record is a policy and evidence gate only; it is not a timing test result, not an implementation proof, not a FIPS validation artifact, not an operation-enabling authority, and not a production cryptography claim.
