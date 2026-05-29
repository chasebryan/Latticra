# Latticra Q-Seal ML-KEM Zeroization Evidence

Status: zeroization policy recorded; primitive implementation blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM zeroization evidence contract defines the evidence gate for future handling of ML-KEM secret intermediates, keys, and seed material. It binds the Q-Seal design frame to FIPS 203 secret-material scope and FIPS 140-3 zeroization posture without selecting a wipe primitive, implementing a wipe primitive, performing memory writes, or enabling any cryptographic operation.

This slice does not implement zeroization, run memory scans, inspect generated assembly, handle secrets, execute ML-KEM, create key material, emit shared secrets, or allow production cryptography claims.

## Source Posture

```text
fips_203_url=https://csrc.nist.gov/pubs/fips/203/final
fips_140_3_url=https://csrc.nist.gov/pubs/fips/140-3/final
```

## Zeroization Fields

```text
ml_kem_zeroization_evidence_present=1
zeroization_profile=latticra-q-seal-ml-kem-zeroization-evidence/0.1
formal_title=Latticra Q-Seal ML-KEM Zeroization Evidence
standards_source=NIST-FIPS-203
module_security_source=NIST-FIPS-140-3-zeroization-requirements
zeroization_scope=ML-KEM-secret-intermediates-key-and-seed-material
zeroization_state=policy-recorded-primitive-not-implemented
fips_203_source_verified=1
fips_140_3_zeroization_tracked=1
secret_state_contract_bound=1
zeroization_required=1
secret_material_inventory_required=1
compiler_barrier_required=1
zeroization_primitive_selected=0
zeroization_primitive_implemented=0
dead_store_elimination_review_recorded=0
volatile_or_intrinsic_strategy_recorded=0
stack_heap_register_clear_policy_recorded=0
error_path_zeroization_recorded=0
decapsulation_failure_zeroization_recorded=0
test_harness_memory_scan_recorded=0
sanitizer_or_valgrind_review_recorded=0
generated_assembly_review_recorded=0
cross_platform_review_recorded=0
formal_review_recorded=0
implementation_binding_recorded=0
zeroization_performed=0
secret_material_handling_allowed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_zeroization_items_total=19
required_zeroization_items_satisfied=6
status=ml-kem-zeroization-evidence-blocked
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_zeroization_evidence.h
latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c
latticra-q-seal/tests/q_seal_ml_kem_zeroization_evidence_invariants.c
latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
```

## Runtime Blockers

Secret material handling remains blocked until:

- the zeroization primitive is selected and implemented;
- compiler dead-store behavior is reviewed;
- the volatile or intrinsic strategy is recorded;
- stack, heap, and register clear policy is recorded;
- error-path and decapsulation-failure zeroization are recorded;
- memory-scan tests are recorded;
- sanitizer or Valgrind review is recorded;
- generated assembly and cross-platform behavior are reviewed;
- formal review and implementation binding are recorded.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
make latticra-q-seal-ml-kem-zeroization-evidence
```

Expected output:

```text
latticra q-seal ml-kem zeroization evidence invariants: ok
latticra q-seal ml-kem zeroization evidence: ok
```
