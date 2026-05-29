# Latticra Q-Seal ML-KEM Provider Differential

Status: comparison-only provider differential readiness slice
Date: 2026-05-27
Scope: clean-room differential-test planning for future ML-KEM implementation validation.

This slice records how Latticra Q-Seal may later compare clean-room ML-KEM behavior against a vetted comparison provider such as liboqs. It keeps provider linking, provider runtime use, vector execution, mismatch acceptance, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_provider_differential.h
latticra-q-seal/src/q_seal_ml_kem_provider_differential.c
latticra-q-seal/tests/q_seal_ml_kem_provider_differential_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
latticra-q-seal/evidence/ML_KEM_PROVIDER_DIFFERENTIAL.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL.md
scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
```

## Current Fields

```text
ml_kem_provider_differential_present=1
formal_title=Latticra Q-Seal ML-KEM Provider Differential
differential_profile=latticra-q-seal-ml-kem-provider-differential/0.1
candidate_provider=liboqs-comparison-only
comparison_scope=ML-KEM-FIPS203-keygen-encap-decap
provider_candidate_recorded=1
provider_comparison_only=1
provider_license_review_required=1
provider_license_review_recorded=0
provider_pinned_version_required=1
provider_pinned_version_recorded=0
provider_source_digest_required=1
provider_source_digest_recorded=0
provider_build_reproducibility_required=1
provider_build_reproducibility_recorded=0
provider_linking_enabled=0
provider_runtime_used=0
parameter_sets_recorded=1
ml_kem_512_comparison_required=1
ml_kem_768_comparison_required=1
ml_kem_1024_comparison_required=1
positive_vector_comparison_required=1
positive_vector_comparison_recorded=0
negative_vector_comparison_required=1
negative_vector_comparison_recorded=0
mismatch_triage_required=1
mismatch_triage_recorded=0
differential_keygen_enabled=0
differential_encap_decap_enabled=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_comparison_items_total=10
required_comparison_items_satisfied=3
blocked_reason=provider-license-version-digest-build-vector-and-mismatch-triage-evidence-missing
status=ml-kem-provider-differential-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
```

Expected output:

```text
latticra q-seal ml-kem provider differential invariants: ok
latticra q-seal ml-kem provider differential: ok
```
