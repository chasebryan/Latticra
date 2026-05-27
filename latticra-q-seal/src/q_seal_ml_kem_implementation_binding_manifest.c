#include "latticra/q_seal_ml_kem_implementation_binding_manifest.h"

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
    const latticra_q_seal_ml_kem_implementation_binding_manifest_t *manifest) {
    unsigned satisfied = 0u;

    satisfied += one_if(manifest->implementation_binding_manifest_present);
    satisfied += one_if(manifest->clean_room_source_boundary_recorded);
    satisfied += one_if(manifest->planned_source_units_count == 9u);
    satisfied += one_if(manifest->planned_test_units_count == 9u);
    satisfied += one_if(manifest->fips_203_algorithm_bound);
    satisfied += one_if(manifest->sp_800_227_kem_usage_bound);
    satisfied += one_if(manifest->kat_manifest_bound);
    satisfied += one_if(manifest->acvp_intake_bound);
    satisfied += one_if(manifest->vector_schema_bound);
    satisfied += one_if(manifest->vector_source_bound);
    satisfied += one_if(manifest->negative_test_evidence_bound);
    satisfied += one_if(manifest->memory_safety_evidence_bound);
    satisfied += one_if(manifest->api_misuse_resistance_bound);
    satisfied += one_if(manifest->constant_time_review_bound);
    satisfied += one_if(manifest->randomness_source_bound);
    satisfied += one_if(manifest->zeroization_evidence_bound);
    satisfied += one_if(manifest->side_channel_review_bound);
    satisfied += one_if(manifest->provider_differential_bound);
    satisfied += one_if(manifest->secret_state_contract_bound);
    satisfied += one_if(manifest->ci_promotion_evidence_bound);
    satisfied += one_if(manifest->module_to_gate_matrix_recorded);
    satisfied += one_if(manifest->keygen_binding_approved);
    satisfied += one_if(manifest->encaps_binding_approved);
    satisfied += one_if(manifest->decaps_binding_approved);
    satisfied += one_if(manifest->implementation_file_digest_manifest_recorded);
    satisfied += one_if(manifest->code_owner_review_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_implementation_binding_manifest_error_label(
    latticra_q_seal_ml_kem_implementation_binding_manifest_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_binding_manifest_prepare(
    latticra_q_seal_ml_kem_implementation_binding_manifest_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->binding_profile,
        sizeof(out->binding_profile),
        "latticra-q-seal-ml-kem-implementation-binding-manifest/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Implementation Binding Manifest");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-SP-800-227");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(
        out->manifest_scope,
        sizeof(out->manifest_scope),
        "ML-KEM-module-to-evidence-binding-before-primitive-code");
    copy_literal(out->binding_state, sizeof(out->binding_state), "implementation-binding-blocked");

    out->implementation_binding_manifest_present = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->planned_source_units_count = 9u;
    out->planned_test_units_count = 9u;
    out->fips_203_algorithm_bound = 1u;
    out->sp_800_227_kem_usage_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->acvp_intake_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->memory_safety_evidence_bound = 1u;
    out->api_misuse_resistance_bound = 1u;
    out->constant_time_review_bound = 1u;
    out->randomness_source_bound = 1u;
    out->zeroization_evidence_bound = 1u;
    out->side_channel_review_bound = 1u;
    out->provider_differential_bound = 1u;
    out->secret_state_contract_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->module_to_gate_matrix_recorded = 1u;
    out->implementation_files_created = 0u;
    out->implementation_code_present = 0u;
    out->primitive_operations_bound = 0u;
    out->keygen_binding_approved = 0u;
    out->encaps_binding_approved = 0u;
    out->decaps_binding_approved = 0u;
    out->implementation_file_digest_manifest_recorded = 0u;
    out->code_owner_review_recorded = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_binding_items_total = 26u;
    out->required_binding_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "implementation-file-digest-keygen-encap-decap-code-owner-and-runtime-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-implementation-binding-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_implementation_binding_manifest_is_clean_room_no_effect(
    const latticra_q_seal_ml_kem_implementation_binding_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->implementation_binding_manifest_present == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->implementation_code_present == 0u &&
           manifest->operation_execution_allowed == 0u &&
           manifest->production_crypto_claim_allowed == 0u &&
           manifest->fips_claim_allowed == 0u &&
           manifest->runtime_authority_granted == 0u &&
           manifest->error == LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_BLOCKED;
}

int latticra_q_seal_ml_kem_implementation_binding_manifest_allows_implementation(
    const latticra_q_seal_ml_kem_implementation_binding_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->implementation_binding_manifest_present == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->planned_source_units_count == 9u &&
           manifest->planned_test_units_count == 9u &&
           manifest->fips_203_algorithm_bound == 1u &&
           manifest->sp_800_227_kem_usage_bound == 1u &&
           manifest->kat_manifest_bound == 1u &&
           manifest->acvp_intake_bound == 1u &&
           manifest->vector_schema_bound == 1u &&
           manifest->vector_source_bound == 1u &&
           manifest->negative_test_evidence_bound == 1u &&
           manifest->memory_safety_evidence_bound == 1u &&
           manifest->api_misuse_resistance_bound == 1u &&
           manifest->constant_time_review_bound == 1u &&
           manifest->randomness_source_bound == 1u &&
           manifest->zeroization_evidence_bound == 1u &&
           manifest->side_channel_review_bound == 1u &&
           manifest->provider_differential_bound == 1u &&
           manifest->secret_state_contract_bound == 1u &&
           manifest->ci_promotion_evidence_bound == 1u &&
           manifest->module_to_gate_matrix_recorded == 1u &&
           manifest->implementation_files_created == 1u &&
           manifest->implementation_code_present == 1u &&
           manifest->primitive_operations_bound == 1u &&
           manifest->keygen_binding_approved == 1u &&
           manifest->encaps_binding_approved == 1u &&
           manifest->decaps_binding_approved == 1u &&
           manifest->implementation_file_digest_manifest_recorded == 1u &&
           manifest->code_owner_review_recorded == 1u &&
           manifest->operation_execution_allowed == 1u &&
           manifest->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_binding_manifest_report(
    const latticra_q_seal_ml_kem_implementation_binding_manifest_t *manifest,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (manifest == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION BINDING MANIFEST\n"
        "binding_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "source_boundary=%s\n"
        "manifest_scope=%s\n"
        "binding_state=%s\n"
        "implementation_binding_manifest_present=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "planned_source_units_count=%u\n"
        "planned_test_units_count=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "sp_800_227_kem_usage_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "acvp_intake_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "memory_safety_evidence_bound=%u\n"
        "api_misuse_resistance_bound=%u\n"
        "constant_time_review_bound=%u\n"
        "randomness_source_bound=%u\n"
        "zeroization_evidence_bound=%u\n"
        "side_channel_review_bound=%u\n"
        "provider_differential_bound=%u\n"
        "secret_state_contract_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "module_to_gate_matrix_recorded=%u\n"
        "implementation_files_created=%u\n"
        "implementation_code_present=%u\n"
        "primitive_operations_bound=%u\n"
        "keygen_binding_approved=%u\n"
        "encaps_binding_approved=%u\n"
        "decaps_binding_approved=%u\n"
        "implementation_file_digest_manifest_recorded=%u\n"
        "code_owner_review_recorded=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_binding_items_total=%u\n"
        "required_binding_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        manifest->binding_profile,
        manifest->formal_title,
        manifest->standards_basis,
        manifest->source_boundary,
        manifest->manifest_scope,
        manifest->binding_state,
        manifest->implementation_binding_manifest_present,
        manifest->clean_room_source_boundary_recorded,
        manifest->apple_corecrypto_code_copied,
        manifest->external_provider_code_copied,
        manifest->planned_source_units_count,
        manifest->planned_test_units_count,
        manifest->fips_203_algorithm_bound,
        manifest->sp_800_227_kem_usage_bound,
        manifest->kat_manifest_bound,
        manifest->acvp_intake_bound,
        manifest->vector_schema_bound,
        manifest->vector_source_bound,
        manifest->negative_test_evidence_bound,
        manifest->memory_safety_evidence_bound,
        manifest->api_misuse_resistance_bound,
        manifest->constant_time_review_bound,
        manifest->randomness_source_bound,
        manifest->zeroization_evidence_bound,
        manifest->side_channel_review_bound,
        manifest->provider_differential_bound,
        manifest->secret_state_contract_bound,
        manifest->ci_promotion_evidence_bound,
        manifest->module_to_gate_matrix_recorded,
        manifest->implementation_files_created,
        manifest->implementation_code_present,
        manifest->primitive_operations_bound,
        manifest->keygen_binding_approved,
        manifest->encaps_binding_approved,
        manifest->decaps_binding_approved,
        manifest->implementation_file_digest_manifest_recorded,
        manifest->code_owner_review_recorded,
        manifest->operation_execution_allowed,
        manifest->production_crypto_claim_allowed,
        manifest->fips_claim_allowed,
        manifest->runtime_authority_granted,
        manifest->required_binding_items_total,
        manifest->required_binding_items_satisfied,
        manifest->blocked_reason,
        latticra_q_seal_ml_kem_implementation_binding_manifest_error_label(manifest->error),
        manifest->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
