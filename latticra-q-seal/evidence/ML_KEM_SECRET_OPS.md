# ML-KEM Secret Ops Evidence

Status: candidate helper evidence recorded
Date: 2026-05-27

```text
ml_kem_secret_ops_present=1
secret_ops_profile=latticra-q-seal-ml-kem-secret-ops/0.2
secure_zero_candidate_present=1
constant_time_equal_candidate_present=1
constant_time_select_candidate_present=1
branchless_select_mask_recorded=1
equal_length_input_contract_required=1
zero_length_public_input_allowed=1
exact_select_alias_allowed=1
partial_select_overlap_rejected=1
partial_select_overlap_failure_writes_output=0
invalid_argument_status_recorded=1
operation_execution_allowed=0
key_generation_enabled=0
encapsulation_enabled=0
decapsulation_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
```

The helpers are not a promoted ML-KEM implementation. They provide a concrete candidate wiping primitive, constant-time equality helper, and mask-selection helper for later clean-room ML-KEM implementation work while preserving the existing operation-disabled gate. The selection helper permits exact in-place output aliases but rejects partial output/input overlap before writing so future secret buffers cannot be corrupted by overlapping caller ranges.
