#include "latticra/q_seal_ml_kem_source_digest_manifest.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static unsigned one_if(unsigned value) {
    return value != 0u ? 1u : 0u;
}

static unsigned required_items_satisfied(
    const latticra_q_seal_ml_kem_source_digest_manifest_t *manifest) {
    unsigned satisfied = 0u;

    satisfied += one_if(manifest->source_digest_manifest_present);
    satisfied += one_if(manifest->fips_203_algorithm_bound);
    satisfied += one_if(manifest->ssdf_source_integrity_bound);
    satisfied += one_if(manifest->digest_algorithm_sha256_recorded);
    satisfied += one_if(manifest->clean_room_source_boundary_recorded);
    satisfied += one_if(manifest->planned_source_units_count == 9u);
    satisfied += one_if(manifest->planned_test_units_count == 9u);
    satisfied += one_if(manifest->implementation_binding_manifest_bound);
    satisfied += one_if(manifest->ci_promotion_evidence_bound);
    satisfied += one_if(manifest->digest_template_recorded);
    satisfied += one_if(manifest->hash_command_policy_recorded);
    satisfied += one_if(manifest->third_party_source_denial_recorded);
    satisfied += one_if(manifest->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(manifest->external_provider_code_copied == 0u);
    satisfied += one_if(manifest->source_file_digests_recorded);
    satisfied += one_if(manifest->test_file_digests_recorded);
    satisfied += one_if(manifest->build_script_digests_recorded);
    satisfied += one_if(manifest->reviewed_digest_receipt_recorded);
    satisfied += one_if(manifest->reproducible_source_snapshot_recorded);
    satisfied += one_if(manifest->digest_verification_ci_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_source_digest_manifest_error_label(
    latticra_q_seal_ml_kem_source_digest_manifest_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_manifest_prepare(
    latticra_q_seal_ml_kem_source_digest_manifest_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->digest_profile,
        sizeof(out->digest_profile),
        "latticra-q-seal-ml-kem-source-digest-manifest/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Source Digest Manifest");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(out->digest_algorithm, sizeof(out->digest_algorithm), "SHA-256");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(out->digest_state, sizeof(out->digest_state), "source-digest-template-blocked");

    out->source_digest_manifest_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->ssdf_source_integrity_bound = 1u;
    out->digest_algorithm_sha256_recorded = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->planned_source_units_count = 9u;
    out->planned_test_units_count = 9u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->digest_template_recorded = 1u;
    out->hash_command_policy_recorded = 1u;
    out->third_party_source_denial_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->implementation_files_created = 0u;
    out->source_file_digests_recorded = 0u;
    out->test_file_digests_recorded = 0u;
    out->build_script_digests_recorded = 0u;
    out->reviewed_digest_receipt_recorded = 0u;
    out->reproducible_source_snapshot_recorded = 0u;
    out->digest_verification_ci_recorded = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_digest_items_total = 20u;
    out->required_digest_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "source-test-build-digests-reproducible-snapshot-ci-and-review-receipts-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-source-digest-manifest-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_source_digest_manifest_is_clean_room_no_effect(
    const latticra_q_seal_ml_kem_source_digest_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->source_digest_manifest_present == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->implementation_files_created == 0u &&
           manifest->operation_execution_allowed == 0u &&
           manifest->production_crypto_claim_allowed == 0u &&
           manifest->fips_claim_allowed == 0u &&
           manifest->runtime_authority_granted == 0u &&
           manifest->error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_BLOCKED;
}

int latticra_q_seal_ml_kem_source_digest_manifest_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_source_digest_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->source_digest_manifest_present == 1u &&
           manifest->fips_203_algorithm_bound == 1u &&
           manifest->ssdf_source_integrity_bound == 1u &&
           manifest->digest_algorithm_sha256_recorded == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->planned_source_units_count == 9u &&
           manifest->planned_test_units_count == 9u &&
           manifest->implementation_binding_manifest_bound == 1u &&
           manifest->ci_promotion_evidence_bound == 1u &&
           manifest->digest_template_recorded == 1u &&
           manifest->hash_command_policy_recorded == 1u &&
           manifest->third_party_source_denial_recorded == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->implementation_files_created == 1u &&
           manifest->source_file_digests_recorded == 1u &&
           manifest->test_file_digests_recorded == 1u &&
           manifest->build_script_digests_recorded == 1u &&
           manifest->reviewed_digest_receipt_recorded == 1u &&
           manifest->reproducible_source_snapshot_recorded == 1u &&
           manifest->digest_verification_ci_recorded == 1u &&
           manifest->operation_execution_allowed == 1u &&
           manifest->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_manifest_report(
    const latticra_q_seal_ml_kem_source_digest_manifest_t *manifest,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (manifest == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SOURCE DIGEST MANIFEST\n"
        "digest_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "digest_algorithm=%s\n"
        "source_boundary=%s\n"
        "digest_state=%s\n"
        "source_digest_manifest_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "ssdf_source_integrity_bound=%u\n"
        "digest_algorithm_sha256_recorded=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "planned_source_units_count=%u\n"
        "planned_test_units_count=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "digest_template_recorded=%u\n"
        "hash_command_policy_recorded=%u\n"
        "third_party_source_denial_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "implementation_files_created=%u\n"
        "source_file_digests_recorded=%u\n"
        "test_file_digests_recorded=%u\n"
        "build_script_digests_recorded=%u\n"
        "reviewed_digest_receipt_recorded=%u\n"
        "reproducible_source_snapshot_recorded=%u\n"
        "digest_verification_ci_recorded=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_digest_items_total=%u\n"
        "required_digest_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        manifest->digest_profile,
        manifest->formal_title,
        manifest->standards_basis,
        manifest->digest_algorithm,
        manifest->source_boundary,
        manifest->digest_state,
        manifest->source_digest_manifest_present,
        manifest->fips_203_algorithm_bound,
        manifest->ssdf_source_integrity_bound,
        manifest->digest_algorithm_sha256_recorded,
        manifest->clean_room_source_boundary_recorded,
        manifest->planned_source_units_count,
        manifest->planned_test_units_count,
        manifest->implementation_binding_manifest_bound,
        manifest->ci_promotion_evidence_bound,
        manifest->digest_template_recorded,
        manifest->hash_command_policy_recorded,
        manifest->third_party_source_denial_recorded,
        manifest->apple_corecrypto_code_copied,
        manifest->external_provider_code_copied,
        manifest->implementation_files_created,
        manifest->source_file_digests_recorded,
        manifest->test_file_digests_recorded,
        manifest->build_script_digests_recorded,
        manifest->reviewed_digest_receipt_recorded,
        manifest->reproducible_source_snapshot_recorded,
        manifest->digest_verification_ci_recorded,
        manifest->operation_execution_allowed,
        manifest->production_crypto_claim_allowed,
        manifest->fips_claim_allowed,
        manifest->runtime_authority_granted,
        manifest->required_digest_items_total,
        manifest->required_digest_items_satisfied,
        manifest->blocked_reason,
        latticra_q_seal_ml_kem_source_digest_manifest_error_label(manifest->error),
        manifest->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
