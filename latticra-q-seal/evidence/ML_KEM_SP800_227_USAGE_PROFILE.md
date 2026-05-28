# Latticra Q-Seal ML-KEM SP 800-227 Usage Profile

Status: SP 800-227 KEM usage profile accepted; runtime operation remains closed
Scope: accepted ML-KEM usage guidance before shared-secret emission, operation execution, FIPS claim, or production cryptography claim.

## Status Fields

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

## Usage Boundary

This contract records the SP 800-227 KEM usage boundary accepted for the clean-room Seal hybrid envelope. Shared-secret emission and ML-KEM runtime operation remain disabled until the implementation, vector, source-acceptance, and runtime gates are satisfied:

- ML-KEM must be treated as an approved KEM algorithm bound to FIPS 203.
- The application or protocol context must be recorded before shared-secret use.
- Key confirmation, KDF, domain separation, key separation, failure handling, and shared-secret lifecycle decisions must be reviewed.
- The accepted profile is evidence only; it does not grant runtime operation.

The profile does not copy Apple corecrypto code, copy external provider code, emit shared secrets, execute operations, or permit FIPS or production cryptography claims.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
```
