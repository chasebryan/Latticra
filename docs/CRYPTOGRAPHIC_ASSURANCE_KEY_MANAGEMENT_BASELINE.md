# Latticra Cryptographic Assurance and Key Management Baseline

Status: cryptographic assurance and key management baseline
Source refresh date: 2026-05-26
Scope: cryptographic module boundaries, FIPS/CMVP claim gates, algorithm and parameter inventory, key lifecycle, key storage, key destruction, randomness, self-tests, sensitive-data handling, post-quantum migration planning, Seal metadata, signing authority, and cryptographic non-claims.

This baseline records cryptographic assurance requirements only. It does not implement production cryptography, signing authority, key storage, key generation, entropy collection, random-bit generation, FIPS validation, CMVP submission, CAVP testing, post-quantum migration, compliance, or runtime authority.

## Authoritative Cryptographic Sources

Date checked: 2026-05-26

| Source | Latticra use |
| --- | --- |
| NIST FIPS 140-3 | cryptographic module boundary, security level, and validation vocabulary |
| NIST CMVP FIPS 140-3 standards and validated modules guidance | validation path and claim caveats for validated modules |
| NIST FIPS 186-5 | digital signature standard tracking for future approved signature policy |
| RFC 8032 | Ed25519 deterministic test-vector tracking for the current local verify-only layer |
| NIST FIPS 180-4 | SHA-256 digest vocabulary for current message/artifact digest reporting |
| NIST SP 800-57 Part 1 Rev. 5 | key-management lifecycle, key inventory, metadata, protection, usage period, and compromise vocabulary |
| NIST SP 800-131A Rev. 2 | algorithm and key-length transition vocabulary |
| NIST SP 800-90A Rev. 1 and SP 800-90B | deterministic random bit generation and entropy-source review vocabulary |
| NIST FIPS 203 | ML-KEM post-quantum key-establishment planning vocabulary |
| NIST FIPS 204 | ML-DSA post-quantum signature planning vocabulary |
| NIST FIPS 205 | SLH-DSA post-quantum signature planning vocabulary |
| Apple Security Research and Apple corecrypto 2026-05 source release | ML-KEM/ML-DSA reference implementation and formal-verification research source; direct embedding remains blocked by the evaluation-only license |
| Open Quantum Safe liboqs | candidate open-source prototype provider for future no-effect PQC adapter planning; production use remains blocked until license, notice, validation, and side-channel review |
| NSA CNSA 2.0 and post-quantum cybersecurity resources | post-quantum migration planning and no-premature-deployment posture for high-assurance systems |
| NSA/CISA/NIST Quantum-Readiness guidance | inventory-first post-quantum transition planning |
| CISA/FBI Product Security Bad Practices | known-insecure cryptography, weak defaults, and unsupported cryptographic configurations remain blocked |

Authoritative URLs:

```text
https://csrc.nist.gov/pubs/fips/140-3/final
https://csrc.nist.gov/Projects/cryptographic-module-validation-program/fips-140-3-standards
https://csrc.nist.gov/projects/cryptographic-module-validation-program/validated-modules
https://csrc.nist.gov/pubs/fips/186-5/final
https://www.rfc-editor.org/rfc/rfc8032
https://csrc.nist.gov/pubs/fips/180-4/upd1/final
https://csrc.nist.gov/pubs/sp/800/57/pt1/r5/final
https://csrc.nist.gov/pubs/sp/800/131/a/r2/final
https://csrc.nist.gov/pubs/sp/800/90/a/r1/final
https://csrc.nist.gov/pubs/sp/800/90/b/final
https://csrc.nist.gov/pubs/fips/203/final
https://csrc.nist.gov/pubs/fips/204/final
https://csrc.nist.gov/pubs/fips/205/final
https://security.apple.com/blog/formal-verification-corecrypto/
https://github.com/apple/corecrypto/tree/2026-05
https://github.com/apple/corecrypto/blob/main/License.txt
https://github.com/open-quantum-safe/liboqs
https://openquantumsafe.org/
https://www.nsa.gov/Cybersecurity/Post-Quantum-Cybersecurity-Resources/
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/article/3498776/post-quantum-cryptography-cisa-nist-and-nsa-recommend-how-to-prepare-now/
https://www.nsa.gov/serve-from-netstorage/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3148990/nsa-releases-future-quantum-resistant-qr-algorithm-requirements-for-national-se/index.html
https://www.cisa.gov/resources-tools/resources/product-security-bad-practices
```

## Current Fields

```text
cryptographic_assurance_key_management_baseline_present=1
cryptographic_assurance_key_management_guard_present=1
seal_crypto_graduation_gate_present=1
seal_crypto_graduation_gate_guard_present=1
seal_pqc_integration_frame_present=1
seal_pqc_integration_frame_guard_present=1
seal_pqc_provider_adapter_present=1
seal_pqc_provider_adapter_guard_present=1
fips_140_3_boundary_required_before_production_crypto=1
cmvp_validation_path_required_before_fips_claim=1
validated_module_claim_requires_certificate=1
algorithm_parameter_inventory_required=1
approved_algorithm_transition_review_required=1
known_insecure_crypto_forbidden=1
ed25519_rfc8032_test_vector_required=1
authority_neutral_crypto_graduation_required=1
fips_186_5_signature_standard_tracked=1
fips_180_4_digest_standard_tracked=1
fips_203_ml_kem_planning_tracked=1
fips_204_ml_dsa_planning_tracked=1
fips_205_slh_dsa_planning_tracked=1
apple_corecrypto_pqc_reference_tracked=1
apple_corecrypto_embedding_allowed=0
apple_corecrypto_redistribution_allowed=0
apple_corecrypto_code_copied=0
oqs_liboqs_candidate_provider_tracked=1
oqs_liboqs_comparison_provider_allowed=1
oqs_liboqs_linked=0
oqs_liboqs_runtime_used=0
oqs_liboqs_production_use_blocked_until_review=1
hybrid_classical_pqc_transition_required=1
clean_room_pqc_provider_adapter_required=1
clean_room_pqc_provider_adapter_present=1
key_lifecycle_contract_required=1
key_inventory_required=1
key_metadata_protection_required=1
key_storage_contract_required=1
key_zeroization_contract_required=1
key_compromise_response_required=1
randomness_entropy_source_contract_required=1
drbg_review_required=1
self_test_failure_behavior_required=1
side_channel_sensitive_data_review_required=1
post_quantum_migration_inventory_required=1
cnsa_2_pq_planning_tracked=1
non_fips_disclosure_required_if_not_validated=1
seal_crypto_metadata_only_current=1
implementation_behavior_changed=0
production_crypto_added=0
signing_authority_granted=0
key_storage_added=0
key_generation_added=0
entropy_collection_added=0
fips_validation_claimed=0
cmvp_submission_performed=0
cavp_testing_claimed=0
post_quantum_migration_performed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
compliance_claim_allowed=0
external_endorsement_claimed=0
```

## Required Cryptographic Promotion Gate

No future cryptographic verification, signing, encryption, key storage, key generation, key derivation, randomness, release-signing, update-signing, receipt-signing, post-quantum migration, FIPS, CMVP, or production-cryptography claim may be promoted until this gate is complete:

```text
cryptographic_module_boundary_recorded=1
module_interface_inventory_recorded=1
approved_algorithm_inventory_recorded=1
algorithm_parameters_recorded=1
security_strength_recorded=1
algorithm_transition_review_recorded=1
key_types_and_usage_periods_recorded=1
key_generation_path_recorded=1
key_storage_path_recorded=1
key_access_control_recorded=1
key_rotation_and_expiration_recorded=1
key_zeroization_behavior_recorded=1
key_compromise_response_recorded=1
entropy_source_recorded=1
drbg_or_random_bit_generator_recorded=1
self_test_behavior_recorded=1
self_test_failure_mode_recorded=1
sensitive_data_logging_reviewed=1
side_channel_review_recorded=1
validated_module_certificate_recorded_before_fips_claim=1
non_fips_disclosure_recorded_if_unvalidated=1
post_quantum_inventory_recorded=1
pqc_provider_license_review_recorded=1
pqc_clean_room_source_boundary_recorded=1
pqc_provider_adapter_contract_recorded=1
pqc_known_answer_tests_recorded=1
pqc_side_channel_review_recorded=1
pqc_hybrid_transition_review_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
production_crypto_allowed=0
fips_claim_allowed=0
cmvp_claim_allowed=0
release_signing_allowed=0
update_signing_allowed=0
receipt_signing_allowed=0
key_generation_allowed=0
key_storage_allowed=0
key_derivation_allowed=0
entropy_collection_allowed=0
random_bit_generation_allowed=0
post_quantum_migration_claim_allowed=0
post_quantum_key_establishment_allowed=0
post_quantum_signature_allowed=0
cryptographic_module_validation_claim_allowed=0
```

## Seal Boundary

Current Seal crypto-related records remain evidence and metadata oriented.

```text
seal_crypto_verify_backend_metadata_only=1
seal_ed25519_verify_only_authority_neutral=1
seal_crypto_graduation_gate_authority_neutral=1
seal_pqc_integration_frame_authority_neutral=1
seal_pqc_provider_adapter_authority_neutral=1
seal_signing_metadata_only=1
seal_key_material_metadata_only=1
seal_runtime_authority_granted=0
seal_production_crypto_enforcement_claimed=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md
docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_IMPLEMENTATION.md
docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md
docs/status/SEAL_ED25519_VERIFY_STATUS.md
docs/LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_IMPLEMENTATION.md
docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
docs/LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md
docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md
SECURITY.md
scripts/test-high-assurance-security-baseline.sh
scripts/test-cryptographic-assurance-key-management-baseline.sh
scripts/test-latticra-seal-crypto-graduation-gate.sh
scripts/test-latticra-seal-pqc-integration-frame.sh
scripts/test-latticra-seal-pqc-provider-adapter.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-cryptographic-assurance-key-management-baseline.sh
```
