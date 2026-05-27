# Latticra Q-Seal ML-KEM Constant-Time Review

Status: constant-time policy recorded; implementation promotion blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM constant-time review defines the promotion gate for future ML-KEM primitive code. It records the required policy for secret-dependent branches, secret-indexed memory, loop bounds, early returns, implicit rejection, compiler optimization review, timing measurements, generated assembly, CI gates, and reviewer signoff.

This slice does not implement ML-KEM, run timing measurements, inspect generated assembly, promote implementation code, execute operations, or allow production cryptography claims. It exists so future primitive work cannot move forward without explicit constant-time evidence.

## Review Fields

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

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_constant_time_review.h
latticra-q-seal/src/q_seal_ml_kem_constant_time_review.c
latticra-q-seal/tests/q_seal_ml_kem_constant_time_review_invariants.c
latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
```

## Runtime Blockers

Implementation promotion remains blocked until:

- dudect or equivalent timing measurement evidence is recorded;
- ctgrind or static-analysis evidence is recorded;
- generated assembly is reviewed for relevant target platforms;
- optimizer flags and compiler assumptions are reviewed;
- the secret-state inventory is bound to the implementation;
- negative timing tests and cross-platform timing review are recorded;
- formal reviewer signoff is recorded;
- CI constant-time gates are recorded;
- the reviewed implementation binding is recorded.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
make latticra-q-seal-ml-kem-constant-time-review
```

Expected output:

```text
latticra q-seal ml-kem constant-time review invariants: ok
latticra q-seal ml-kem constant-time review: ok
```
