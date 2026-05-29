# Latticra Q-Seal ML-KEM SP 800-227 Usage Profile

The Latticra Q-Seal ML-KEM SP 800-227 Usage Profile is a no-effect contract for KEM usage semantics. It records accepted usage evidence for the Seal hybrid envelope binding while keeping operation execution, shared-secret emission, FIPS claims, production cryptography claims, and runtime authority disabled.

```text
sp800_227_usage_profile_present=1
formal_title=Latticra Q-Seal ML-KEM SP 800-227 Usage Profile
usage_profile=latticra-q-seal-ml-kem-sp800-227-usage-profile/0.1
standards_basis=NIST-SP-800-227
sp_800_227_source_url=https://csrc.nist.gov/pubs/sp/800/227/final
sp_800_227_publication_date=September-2025
usage_scope=ML-KEM-SP-800-227-usage-before-shared-secret-emission
usage_state=sp800-227-usage-profile-accepted-for-seal-hybrid-envelope-binding
sp_800_227_source_bound=1
sp_800_227_publication_date_recorded=1
kem_definition_bound=1
shared_secret_establishment_scope_bound=1
encapsulation_role_bound=1
decapsulation_role_bound=1
approved_kem_algorithm_required=1
fips_203_ml_kem_bound=1
key_establishment_context_required=1
application_protocol_binding_required=1
key_confirmation_decision_required=1
kdf_boundary_required=1
domain_separation_required=1
shared_secret_lifecycle_required=1
failure_handling_required=1
key_separation_required=1
algorithm_agility_policy_required=1
clean_room_source_boundary_recorded=1
implementation_binding_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
kem_use_case_review_recorded=1
application_protocol_binding_recorded=1
key_confirmation_decision_recorded=1
kdf_binding_recorded=1
domain_separation_reviewed=1
shared_secret_lifecycle_reviewed=1
failure_handling_reviewed=1
key_separation_reviewed=1
algorithm_agility_reviewed=1
kem_usage_profile_accepted=1
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_usage_items_total=30
required_usage_items_satisfied=30
blocked_reason=none
status=ml-kem-sp800-227-usage-profile-accepted-runtime-closed
```

This profile is deliberately not runtime cryptography. It accepts the usage evidence needed for the current clean-room hybrid-envelope design: the KEM use case is limited to hybrid key establishment, the application/protocol binding is the Seal envelope transcript, the key-confirmation decision is bound to envelope authentication and commitment verification, the KDF and domain-separation boundary is recorded, and shared-secret lifecycle, failure handling, key separation, and algorithm agility are reviewed before any runtime operation is allowed.

Validation:

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
```
