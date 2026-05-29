# Latticra Q-Seal ML-KEM Zeroization Evidence

Status: zeroization policy recorded; primitive implementation blocked
Date: 2026-05-27

This evidence record defines the zeroization gate for future Latticra Q-Seal ML-KEM implementation work. It records the FIPS 203 secret-material scope and the FIPS 140-3 zeroization requirement posture that must exist before Q-Seal may handle ML-KEM secret intermediates, keys, or seed material.

No zeroization primitive is selected, no zeroization primitive is implemented, no memory wipe is performed, no secret material handling is allowed, no ML-KEM operation is enabled, no production cryptography claim is allowed, no FIPS claim is allowed, and no runtime authority is granted by this record.

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

## Promotion Rule

Q-Seal may not handle ML-KEM secret material until the zeroization primitive is selected and implemented, compiler dead-store behavior is reviewed, the volatile or intrinsic strategy is recorded, stack/heap/register clearing policy is recorded, error-path and decapsulation-failure zeroization are recorded, memory-scan tests are recorded, sanitizer or Valgrind review is recorded, generated assembly is reviewed, cross-platform review is recorded, formal review is recorded, and implementation binding is recorded.

This record is a policy and evidence gate only; it is not a zeroization implementation, not a memory-wipe result, not FIPS validation evidence, not an operation-enabling authority, and not a production cryptography claim.
