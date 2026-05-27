# Latticra Seal PQC Provider Adapter

Status: clean-room no-effect post-quantum provider adapter
Date: 2026-05-27
Scope: first clean-room adapter surface after the Seal PQC integration frame. This adapter prepares ML-KEM and ML-DSA implementation work from standards, fixtures, and allowed comparison providers without copying Apple corecrypto or performing cryptographic operations.

This implementation does not link liboqs, vendor liboqs, vendor Apple corecrypto, copy Apple code, copy Apple proof artifacts, reuse Apple symbols, implement ML-KEM, implement ML-DSA, generate keys, store keys, encapsulate, decapsulate, sign, verify, encrypt, run network lookup, claim FIPS validation, claim production cryptography, migrate deployed cryptography, enforce capabilities, execute effects, mutate host state, or grant runtime authority.

## Clean-Room Boundary

The adapter consumes `latticra_seal_pqc_integration_frame_t` and refuses any frame that allows Apple embedding or redistribution. Apple corecrypto remains a reference-only research input. Latticra implementation work must come from NIST FIPS 203, FIPS 204, FIPS 205, public test vectors, permissively licensed references, and Latticra-owned implementation notes.

`liboqs` is allowed only as a future comparison provider. It is not linked by this adapter, not used at runtime, not enabled by default, and not accepted as production cryptography.

## Files

```text
include/latticra/seal_pqc_provider_adapter.h
src/seal_pqc_provider_adapter.c
tests/seal_pqc_provider_adapter_invariants.c
scripts/test-latticra-seal-pqc-provider-adapter.sh
docs/LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md
docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md
```

## Current Fields

```text
seal_pqc_provider_adapter_present=1
adapter_profile=latticra-seal-pqc-provider-adapter/0.1
integration_profile=latticra-seal-pqc-integration-frame/0.1
clean_room_profile=latticra-clean-room-pqc/0.1
provider_name=liboqs
provider_role=comparison-provider-only
provider_license=MIT-with-third-party-notice-review
source_boundary=clean-room-no-apple-code
adapter_state=prepared-clean-room-adapter
blocked_reason=crypto-operations-not-implemented
integration_frame_present=1
clean_room_design_required=1
nist_fips_203_ml_kem_required=1
nist_fips_204_ml_dsa_required=1
nist_fips_205_slh_dsa_backup_tracked=1
ml_kem_512_planned=1
ml_kem_768_planned=1
ml_kem_1024_planned=1
ml_dsa_44_planned=1
ml_dsa_65_planned=1
ml_dsa_87_planned=1
liboqs_comparison_provider_allowed=1
liboqs_linked=0
liboqs_runtime_used=0
apple_corecrypto_reference_allowed=1
apple_corecrypto_code_copied=0
apple_corecrypto_proof_artifacts_copied=0
apple_corecrypto_symbols_reused=0
permissive_reference_code_required=1
third_party_notice_review_required=1
compile_time_gate_required=1
default_build_enabled=0
known_answer_tests_required=1
differential_tests_allowed=1
differential_tests_performed=0
fuzzing_required=1
constant_time_review_required=1
side_channel_review_required=1
memory_safe_implementation_preferred=1
c_abi_boundary_required=1
cryptographic_module_boundary_required=1
fips_140_3_claim_gate_required=1
cavp_acvp_vector_review_required=1
key_generation_performed=0
key_storage_performed=0
encapsulation_performed=0
decapsulation_performed=0
signing_performed=0
verification_performed=0
encryption_performed=0
network_lookup_allowed=0
production_crypto_claim_allowed=0
post_quantum_migration_claim_allowed=0
runtime_authority_granted=0
status=pqc-provider-adapter-prepared
```

## Next Valid Slice

The next valid slice is a clean-room ML-KEM work packet that records FIPS 203 parameter constants, NIST known-answer test fixture locations, API shape, memory-safety ownership rules, and differential-test expectations against `liboqs`, while still keeping key generation, encapsulation, decapsulation, and production crypto disabled.

## Validation

Current guard:

```sh
sh scripts/test-latticra-seal-pqc-provider-adapter.sh
```

Expected output:

```text
seal pqc provider adapter invariants: ok
latticra seal pqc provider adapter: ok
```
