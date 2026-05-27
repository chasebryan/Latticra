# Latticra Q-Seal ML-KEM Implementation Binding Manifest

Status: clean-room implementation-binding manifest
Date: 2026-05-27
Scope: module-to-evidence bindings before ML-KEM primitive code is created or promoted.

This manifest binds the future clean-room ML-KEM module plan to the evidence gates that must precede implementation. It records intended source and test unit counts, standards anchors, and gate bindings, but it does not create primitive source files, implement polynomial arithmetic, implement NTT, sample secrets, encode keys, generate keys, encapsulate, decapsulate, execute tests over vectors, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
ml_kem_implementation_binding_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM Implementation Binding Manifest
binding_profile=latticra-q-seal-ml-kem-implementation-binding-manifest/0.1
standards_basis=NIST-FIPS-203-and-SP-800-227
source_boundary=clean-room-no-apple-code
manifest_scope=ML-KEM-module-to-evidence-binding-before-primitive-code
binding_state=implementation-binding-blocked
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
fips_203_algorithm_bound=1
sp_800_227_kem_usage_bound=1
kat_manifest_bound=1
acvp_intake_bound=1
vector_schema_bound=1
vector_source_bound=1
negative_test_evidence_bound=1
memory_safety_evidence_bound=1
api_misuse_resistance_bound=1
constant_time_review_bound=1
randomness_source_bound=1
zeroization_evidence_bound=1
side_channel_review_bound=1
provider_differential_bound=1
secret_state_contract_bound=1
ci_promotion_evidence_bound=1
module_to_gate_matrix_recorded=1
implementation_files_created=0
implementation_code_present=0
primitive_operations_bound=0
keygen_binding_approved=0
encaps_binding_approved=0
decaps_binding_approved=0
implementation_file_digest_manifest_recorded=0
code_owner_review_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_binding_items_total=26
required_binding_items_satisfied=21
status=ml-kem-implementation-binding-blocked
```

## Module-To-Gate Matrix

```text
polynomial_arithmetic -> constant_time_review, memory_safety_evidence, side_channel_review
ntt -> constant_time_review, side_channel_review, provider_differential
sampling -> randomness_source, zeroization_evidence, secret_state_contract
compression -> vector_schema, negative_test_evidence, api_misuse_resistance
encoding -> vector_schema, vector_source, negative_test_evidence
hash_xof -> FIPS203, SP800-227, provider_differential, source_digest_manifest
keygen -> KAT_manifest, ACVP_intake, randomness_source, source_digest_manifest, code_owner_review, CI_promotion
encapsulation -> KAT_manifest, ACVP_intake, vector_source, source_digest_manifest, code_owner_review, CI_promotion
decapsulation -> KAT_manifest, ACVP_intake, negative_test_evidence, source_digest_manifest, code_owner_review, CI_promotion
```

## Promotion Blockers

```text
implementation_files_created=0
implementation_code_present=0
primitive_operations_bound=0
keygen_binding_approved=0
encaps_binding_approved=0
decaps_binding_approved=0
implementation_file_digest_manifest_recorded=0
code_owner_review_recorded=0
```

## Non-Claims

This manifest is not primitive code, not generated source, not vector execution, not an ACVP submission, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
