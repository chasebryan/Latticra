# Latticra Q-Seal ML-KEM Provider Differential

Status: comparison-only provider differential contract
Date: 2026-05-27
Scope: future clean-room differential testing against an allowed comparison provider before ML-KEM implementation promotion.

This record defines how Latticra Q-Seal may later compare clean-room ML-KEM behavior against a vetted external provider. It does not link a provider, execute provider code, import provider source, run ML-KEM operations, load vectors, accept mismatches, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

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
status=ml-kem-provider-differential-blocked
```

## Promotion Blockers

```text
provider_license_review_recorded=0
provider_pinned_version_recorded=0
provider_source_digest_recorded=0
provider_build_reproducibility_recorded=0
positive_vector_comparison_recorded=0
negative_vector_comparison_recorded=0
mismatch_triage_recorded=0
```

## Non-Claims

This differential contract is not provider endorsement, not provider linking, not runtime provider use, not a cryptographic implementation, not a vector result, not a FIPS validation path by itself, not production cryptography, not network behavior, not host mutation, and not runtime authority.
