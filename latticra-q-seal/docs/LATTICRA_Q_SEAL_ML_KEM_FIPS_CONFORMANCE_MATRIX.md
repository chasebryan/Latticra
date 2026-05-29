# Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix

The Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix is a no-effect contract for keeping the implementation lane anchored to FIPS 203 before primitive code is accepted. It records required algorithm, parameter-set, encoding, randomness, hash/XOF, and failure-semantics boundaries, then blocks until implementation traces and review evidence exist.

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

The matrix is deliberately not a cryptographic implementation. It is a standards-facing acceptance gate for future clean-room code, and it remains blocked until the per-parameter traces, algorithm-step traces, encoding tests, decapsulation failure-semantics tests, primitive mapping review, errata review, implementation trace acceptance, and matrix acceptance are recorded.

Validation:

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
```
