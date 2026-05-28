# Latticra Q-Seal ML-KEM Implementation Traceability Matrix

Latticra Q-Seal records an implementation traceability matrix before accepting clean-room ML-KEM primitive source files. The matrix binds each planned source unit to FIPS 203, SP 800-227 usage constraints, KAT/ACVP evidence, source digest evidence, and review ownership while keeping implementation acceptance, operation execution, shared-secret emission, production claims, and FIPS claims blocked.

```text
traceability_profile=latticra-q-seal-ml-kem-implementation-traceability-matrix/0.1
formal_title=Latticra Q-Seal ML-KEM Implementation Traceability Matrix
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM
source_boundary=clean-room-no-apple-code
traceability_scope=ML-KEM-source-unit-to-evidence-trace-before-implementation
traceability_state=traceability-recorded-implementation-blocked
implementation_traceability_matrix_present=1
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
planned_source_unit_matrix_recorded=1
polynomial_arithmetic_unit_bound=1
ntt_unit_bound=1
sampling_unit_bound=1
compression_unit_bound=1
encoding_unit_bound=1
hash_xof_unit_bound=1
keygen_unit_bound=1
encaps_unit_bound=1
decaps_unit_bound=1
fips_203_section_mapping_recorded=1
sp800_227_usage_mapping_recorded=1
kat_vector_family_mapping_recorded=1
acvp_test_type_mapping_recorded=1
clean_room_review_path_recorded=1
no_external_code_dependency_recorded=1
constant_time_review_mapping_recorded=0
memory_safety_mapping_recorded=0
zeroization_mapping_recorded=0
randomness_mapping_recorded=0
negative_test_mapping_recorded=0
source_digest_mapping_recorded=0
code_owner_mapping_recorded=0
review_disposition_mapping_recorded=0
implementation_trace_accepted=0
implementation_file_digest_manifest_recorded=0
implementation_code_present=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_traceability_items_total=30
required_traceability_items_satisfied=20
blocked_reason=review-digest-constant-time-memory-randomness-zeroization-negative-and-owner-mappings-missing
error=blocked
status=ml-kem-traceability-matrix-blocked
```

## Acceptance Gates

The matrix is blocked until the future implementation records:

- per-unit constant-time review mapping;
- per-unit memory-safety and zeroization mapping;
- randomness and negative-test mapping for the units that consume entropy or reject malformed input;
- source digest mapping for every implementation file;
- code-owner and review-disposition mapping for every source unit.

Trace acceptance still does not allow operation execution. It only allows the implementation-binding manifest to move closer to primitive source acceptance after the downstream evidence exists.
