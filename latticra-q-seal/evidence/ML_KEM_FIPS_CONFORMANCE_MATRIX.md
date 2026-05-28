# Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix

Status: FIPS 203 conformance matrix recorded; implementation trace blocked
Scope: fail-closed ML-KEM standards conformance before primitive implementation, runtime operation, FIPS claim, or production cryptography claim.

## Status Fields

```text
fips_conformance_matrix_present=1
formal_title=Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix
conformance_profile=latticra-q-seal-ml-kem-fips-conformance-matrix/0.1
standards_basis=NIST-FIPS-203
conformance_scope=ML-KEM-FIPS-203-conformance-before-implementation
conformance_state=fips-conformance-matrix-recorded-implementation-trace-missing
fips_203_source_bound=1
fips_203_publication_date_recorded=1
parameter_sets_bound=1
ml_kem_512_bound=1
ml_kem_768_bound=1
ml_kem_1024_bound=1
algorithm_functions_bound=1
keygen_algorithm_bound=1
encaps_algorithm_bound=1
decaps_algorithm_bound=1
byte_encoding_requirements_bound=1
randomness_requirements_bound=1
hash_xof_boundary_bound=1
decapsulation_failure_semantics_bound=1
acvp_kat_consistency_required=1
clean_room_source_boundary_recorded=1
implementation_binding_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
per_parameter_trace_recorded=0
keygen_step_trace_recorded=0
encaps_step_trace_recorded=0
decaps_step_trace_recorded=0
encoding_tests_recorded=0
failure_semantics_tests_recorded=0
primitive_mapping_reviewed=0
errata_review_recorded=0
implementation_trace_accepted=0
conformance_matrix_accepted=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_conformance_items_total=28
required_conformance_items_satisfied=18
blocked_reason=per-parameter-step-trace-encoding-failure-semantics-primitive-mapping-errata-and-acceptance-evidence-missing
status=ml-kem-fips-conformance-matrix-blocked
```

## Matrix Boundary

This contract records the FIPS 203 conformance surface that a clean-room ML-KEM implementation must satisfy before any primitive code can be accepted for execution:

- ML-KEM-512, ML-KEM-768, and ML-KEM-1024 parameter-set coverage.
- Key generation, encapsulation, and decapsulation algorithm-step traceability.
- Byte encoding, randomness, hash/XOF primitive boundary, and decapsulation failure-semantics review.
- ACVP/KAT consistency checks before implementation trace acceptance.
- Errata review before conformance acceptance.

It does not copy Apple corecrypto code, copy external provider code, accept implementation traces, enable operations, or permit FIPS or production cryptography claims.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
```
