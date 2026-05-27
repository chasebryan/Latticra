# Latticra Q-Seal ML-KEM Implementation Binding Manifest

Status: fail-closed clean-room implementation-binding slice
Date: 2026-05-27
Scope: module-to-evidence bindings before ML-KEM implementation files or primitive operations.

This slice records the binding manifest that future ML-KEM implementation code must satisfy before it can be treated as an implementation candidate. It keeps primitive source creation, key generation, encapsulation, decapsulation, vector execution, provider execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_binding_manifest.h
latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
```

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
blocked_reason=implementation-file-digest-keygen-encap-decap-code-owner-and-runtime-evidence-missing
status=ml-kem-implementation-binding-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
```

Expected output:

```text
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
```
