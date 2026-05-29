# Latticra Seal PQC Integration Frame Status

Status: status record for the authority-neutral post-quantum cryptography integration frame
Date: 2026-05-27

## Scope

This record tracks the Latticra Seal PQC integration frame after the Apple corecrypto May 2026 source release review.

It does not vendor Apple corecrypto, vendor liboqs, implement ML-KEM, implement ML-DSA, perform encryption, perform signing, generate keys, store keys, load trust stores, run network lookup, claim FIPS validation, claim production cryptography, migrate deployed cryptography, enforce capabilities, execute effects, mutate host state, or grant runtime authority.

## Files

```text
include/latticra/seal_pqc_integration_frame.h
src/seal_pqc_integration_frame.c
tests/seal_pqc_integration_frame_invariants.c
scripts/test-latticra-seal-pqc-integration-frame.sh
docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
```

## Current Fields

```text
seal_pqc_integration_frame_present=1
seal_pqc_integration_frame_header_present=1
seal_pqc_integration_frame_source_present=1
seal_pqc_integration_frame_invariant_test_present=1
seal_pqc_integration_frame_runner_present=1
seal_pqc_integration_frame_status_present=1
pqc_integration_profile=latticra-seal-pqc-integration-frame/0.1
research_date=2026-05-27
apple_corecrypto_source=github.com/apple/corecrypto@2026-05
apple_corecrypto_license=evaluation-only-no-redistribution
apple_corecrypto_ml_kem_published=1
apple_corecrypto_ml_dsa_published=1
apple_corecrypto_formal_verification_published=1
apple_corecrypto_reference_allowed=1
apple_corecrypto_embedding_allowed=0
apple_corecrypto_redistribution_allowed=0
nist_fips_203_ml_kem_tracked=1
nist_fips_204_ml_dsa_tracked=1
nist_fips_205_slh_dsa_backup_tracked=1
ml_kem_key_establishment_planned=1
ml_dsa_signature_planned=1
hybrid_classical_pqc_transition_required=1
candidate_provider=liboqs
candidate_provider_source=github.com/open-quantum-safe/liboqs
candidate_provider_license=MIT-with-third-party-notice-review
liboqs_candidate_tracked=1
liboqs_mit_license_tracked=1
liboqs_prototype_only_warning_tracked=1
candidate_provider_production_use_allowed=0
cryptographic_module_boundary_required=1
algorithm_parameter_inventory_required=1
known_answer_tests_required=1
cavp_acvp_vector_review_required=1
constant_time_review_required=1
side_channel_review_required=1
fips_140_3_claim_gate_required=1
sp_800_57_key_management_required=1
source_notice_review_required=1
third_party_code_vendored=0
cryptographic_behavior_changed=0
post_quantum_migration_claim_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
key_generation_allowed=0
key_storage_allowed=0
encryption_performed=0
signing_performed=0
network_lookup_allowed=0
runtime_authority_granted=0
frame_state=prepared-authority-neutral
blocked_reason=license-validation-and-provider-review-required
status=pqc-integration-frame-prepared
```

## Validation

```sh
sh scripts/test-latticra-seal-pqc-integration-frame.sh
```

Expected output:

```text
seal pqc integration frame invariants: ok
latticra seal pqc integration frame: ok
```
