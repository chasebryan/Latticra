#!/usr/bin/env sh
set -eu

doc="docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md"
status_doc="docs/status/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'cryptographic assurance key management baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'cryptographic assurance key management baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md
require_file docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
require_file docs/LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md
require_file docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md
require_file docs/status/SEAL_ED25519_VERIFY_STATUS.md
require_file docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_file docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
require_file docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-latticra-seal-crypto-graduation-gate.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: cryptographic assurance and key management baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Cryptographic Sources' "$doc"
require_contains 'NIST FIPS 140-3' "$doc"
require_contains 'NIST CMVP FIPS 140-3 standards and validated modules guidance' "$doc"
require_contains 'NIST FIPS 186-5' "$doc"
require_contains 'RFC 8032' "$doc"
require_contains 'NIST FIPS 180-4' "$doc"
require_contains 'NIST SP 800-57 Part 1 Rev. 5' "$doc"
require_contains 'NIST SP 800-131A Rev. 2' "$doc"
require_contains 'NIST SP 800-90A Rev. 1 and SP 800-90B' "$doc"
require_contains 'NIST FIPS 203' "$doc"
require_contains 'NIST FIPS 204' "$doc"
require_contains 'NIST FIPS 205' "$doc"
require_contains 'Apple Security Research and Apple corecrypto 2026-05 source release' "$doc"
require_contains 'Open Quantum Safe liboqs' "$doc"
require_contains 'NSA CNSA 2.0 and post-quantum cybersecurity resources' "$doc"
require_contains 'NSA/CISA/NIST Quantum-Readiness guidance' "$doc"
require_contains 'CISA/FBI Product Security Bad Practices' "$doc"
require_contains 'https://csrc.nist.gov/pubs/fips/140-3/final' "$doc"
require_contains 'https://csrc.nist.gov/Projects/cryptographic-module-validation-program/fips-140-3-standards' "$doc"
require_contains 'https://csrc.nist.gov/projects/cryptographic-module-validation-program/validated-modules' "$doc"
require_contains 'https://csrc.nist.gov/pubs/fips/186-5/final' "$doc"
require_contains 'https://www.rfc-editor.org/rfc/rfc8032' "$doc"
require_contains 'https://csrc.nist.gov/pubs/fips/180-4/upd1/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/57/pt1/r5/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/131/a/r2/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/90/a/r1/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/90/b/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/fips/203/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/fips/204/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/fips/205/final' "$doc"
require_contains 'https://security.apple.com/blog/formal-verification-corecrypto/' "$doc"
require_contains 'https://github.com/apple/corecrypto/tree/2026-05' "$doc"
require_contains 'https://github.com/apple/corecrypto/blob/main/License.txt' "$doc"
require_contains 'https://github.com/open-quantum-safe/liboqs' "$doc"
require_contains 'https://openquantumsafe.org/' "$doc"
require_contains 'https://www.nsa.gov/Cybersecurity/Post-Quantum-Cybersecurity-Resources/' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/article/3498776/post-quantum-cryptography-cisa-nist-and-nsa-recommend-how-to-prepare-now/' "$doc"
require_contains 'https://www.nsa.gov/serve-from-netstorage/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3148990/nsa-releases-future-quantum-resistant-qr-algorithm-requirements-for-national-se/index.html' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/resources/product-security-bad-practices' "$doc"

for field in \
  'cryptographic_assurance_key_management_baseline_present=1' \
  'cryptographic_assurance_key_management_guard_present=1' \
  'seal_crypto_graduation_gate_present=1' \
  'seal_crypto_graduation_gate_guard_present=1' \
  'seal_pqc_integration_frame_present=1' \
  'seal_pqc_integration_frame_guard_present=1' \
  'seal_pqc_provider_adapter_present=1' \
  'seal_pqc_provider_adapter_guard_present=1' \
  'fips_140_3_boundary_required_before_production_crypto=1' \
  'cmvp_validation_path_required_before_fips_claim=1' \
  'validated_module_claim_requires_certificate=1' \
  'algorithm_parameter_inventory_required=1' \
  'approved_algorithm_transition_review_required=1' \
  'known_insecure_crypto_forbidden=1' \
  'ed25519_rfc8032_test_vector_required=1' \
  'authority_neutral_crypto_graduation_required=1' \
  'fips_186_5_signature_standard_tracked=1' \
  'fips_180_4_digest_standard_tracked=1' \
  'fips_203_ml_kem_planning_tracked=1' \
  'fips_204_ml_dsa_planning_tracked=1' \
  'fips_205_slh_dsa_planning_tracked=1' \
  'apple_corecrypto_pqc_reference_tracked=1' \
  'apple_corecrypto_embedding_allowed=0' \
  'apple_corecrypto_redistribution_allowed=0' \
  'apple_corecrypto_code_copied=0' \
  'oqs_liboqs_candidate_provider_tracked=1' \
  'oqs_liboqs_comparison_provider_allowed=1' \
  'oqs_liboqs_linked=0' \
  'oqs_liboqs_runtime_used=0' \
  'oqs_liboqs_production_use_blocked_until_review=1' \
  'hybrid_classical_pqc_transition_required=1' \
  'clean_room_pqc_provider_adapter_required=1' \
  'clean_room_pqc_provider_adapter_present=1' \
  'key_lifecycle_contract_required=1' \
  'key_inventory_required=1' \
  'key_metadata_protection_required=1' \
  'key_storage_contract_required=1' \
  'key_zeroization_contract_required=1' \
  'key_compromise_response_required=1' \
  'randomness_entropy_source_contract_required=1' \
  'drbg_review_required=1' \
  'self_test_failure_behavior_required=1' \
  'side_channel_sensitive_data_review_required=1' \
  'post_quantum_migration_inventory_required=1' \
  'cnsa_2_pq_planning_tracked=1' \
  'non_fips_disclosure_required_if_not_validated=1' \
  'seal_crypto_metadata_only_current=1' \
  'implementation_behavior_changed=0' \
  'production_crypto_added=0' \
  'signing_authority_granted=0' \
  'key_storage_added=0' \
  'key_generation_added=0' \
  'entropy_collection_added=0' \
  'fips_validation_claimed=0' \
  'cmvp_submission_performed=0' \
  'cavp_testing_claimed=0' \
  'post_quantum_migration_performed=0' \
  'production_crypto_claim_allowed=0' \
  'fips_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'cryptographic_assurance_key_management_status_present=1' "$status_doc"

for gate in \
  'cryptographic_module_boundary_recorded=1' \
  'module_interface_inventory_recorded=1' \
  'approved_algorithm_inventory_recorded=1' \
  'algorithm_parameters_recorded=1' \
  'security_strength_recorded=1' \
  'algorithm_transition_review_recorded=1' \
  'key_types_and_usage_periods_recorded=1' \
  'key_generation_path_recorded=1' \
  'key_storage_path_recorded=1' \
  'key_access_control_recorded=1' \
  'key_rotation_and_expiration_recorded=1' \
  'key_zeroization_behavior_recorded=1' \
  'key_compromise_response_recorded=1' \
  'entropy_source_recorded=1' \
  'drbg_or_random_bit_generator_recorded=1' \
  'self_test_behavior_recorded=1' \
  'self_test_failure_mode_recorded=1' \
  'sensitive_data_logging_reviewed=1' \
  'side_channel_review_recorded=1' \
  'validated_module_certificate_recorded_before_fips_claim=1' \
  'non_fips_disclosure_recorded_if_unvalidated=1' \
  'post_quantum_inventory_recorded=1' \
  'pqc_provider_license_review_recorded=1' \
  'pqc_clean_room_source_boundary_recorded=1' \
  'pqc_provider_adapter_contract_recorded=1' \
  'pqc_known_answer_tests_recorded=1' \
  'pqc_side_channel_review_recorded=1' \
  'pqc_hybrid_transition_review_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'production_crypto_allowed=0' \
  'fips_claim_allowed=0' \
  'cmvp_claim_allowed=0' \
  'release_signing_allowed=0' \
  'update_signing_allowed=0' \
  'receipt_signing_allowed=0' \
  'key_generation_allowed=0' \
  'key_storage_allowed=0' \
  'key_derivation_allowed=0' \
  'entropy_collection_allowed=0' \
  'random_bit_generation_allowed=0' \
  'post_quantum_migration_claim_allowed=0' \
  'post_quantum_key_establishment_allowed=0' \
  'post_quantum_signature_allowed=0' \
  'cryptographic_module_validation_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for seal_field in \
  'seal_crypto_verify_backend_metadata_only=1' \
  'seal_ed25519_verify_only_authority_neutral=1' \
  'seal_crypto_graduation_gate_authority_neutral=1' \
  'seal_pqc_integration_frame_authority_neutral=1' \
  'seal_pqc_provider_adapter_authority_neutral=1' \
  'seal_signing_metadata_only=1' \
  'seal_key_material_metadata_only=1' \
  'seal_runtime_authority_granted=0' \
  'seal_production_crypto_enforcement_claimed=0'
do
  require_contains "$seal_field" "$doc"
done

require_contains 'crypto_verify_state=unsupported' docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md
require_contains 'ed25519_authority_usable=0' docs/status/SEAL_ED25519_VERIFY_STATUS.md
require_contains 'seal_crypto_graduation_gate_present=1' docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_contains 'authority_promotion_allowed=0' docs/status/SEAL_CRYPTO_GRADUATION_GATE_STATUS.md
require_contains 'seal_pqc_integration_frame_present=1' docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
require_contains 'apple_corecrypto_embedding_allowed=0' docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
require_contains 'seal_pqc_provider_adapter_present=1' docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md
require_contains 'apple_corecrypto_code_copied=0' docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md
require_contains 'liboqs_linked=0' docs/status/SEAL_PQC_PROVIDER_ADAPTER_STATUS.md
require_contains 'cryptographic_assurance_key_management_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-cryptographic-assurance-key-management-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md' SECURITY.md
require_contains 'cryptographic_assurance_key_management_baseline_present=1' README.md
require_contains 'cryptographic_assurance_key_management_baseline_present=1' STATUS.md
require_contains 'CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE_STATUS.md' docs/status/README.md
require_contains 'cryptographic_assurance_key_management_baseline_present=1' docs/status/README.md
require_contains 'SEAL_PQC_INTEGRATION_FRAME_STATUS.md' docs/status/README.md
require_contains 'SEAL_PQC_PROVIDER_ADAPTER_STATUS.md' docs/status/README.md
require_contains 'Latest cryptographic assurance and key management baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_PQC_PROVIDER_ADAPTER.md' docs/FOUNDATION_INDEX.md
require_contains 'Cryptographic assurance and key management baseline' docs/security.html
require_contains 'CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-cryptographic-assurance-key-management-baseline.sh' Makefile
require_contains 'sh ./scripts/test-latticra-seal-crypto-graduation-gate.sh' Makefile
require_contains 'sh ./scripts/test-latticra-seal-pqc-integration-frame.sh' Makefile
require_contains 'sh ./scripts/test-latticra-seal-pqc-provider-adapter.sh' Makefile
require_contains 'cryptographic-assurance-key-management-baseline:' Makefile
require_contains 'latticra-seal-crypto-graduation-gate:' Makefile
require_contains 'latticra-seal-pqc-integration-frame:' Makefile
require_contains 'latticra-seal-pqc-provider-adapter:' Makefile
require_contains 'sh ./scripts/test-cryptographic-assurance-key-management-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-cryptographic-assurance-key-management-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'cryptographic_assurance_key_management_baseline: ok\n'
