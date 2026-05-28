#include "latticra/q_seal_ml_kem_sp800_227_usage_profile.h"

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
    const latticra_q_seal_ml_kem_sp800_227_usage_profile_t *profile) {
    unsigned satisfied = 0u;

    satisfied += one_if(profile->sp800_227_usage_profile_present);
    satisfied += one_if(profile->sp_800_227_source_bound);
    satisfied += one_if(profile->sp_800_227_publication_date_recorded);
    satisfied += one_if(profile->kem_definition_bound);
    satisfied += one_if(profile->shared_secret_establishment_scope_bound);
    satisfied += one_if(profile->encapsulation_role_bound);
    satisfied += one_if(profile->decapsulation_role_bound);
    satisfied += one_if(profile->approved_kem_algorithm_required);
    satisfied += one_if(profile->fips_203_ml_kem_bound);
    satisfied += one_if(profile->key_establishment_context_required);
    satisfied += one_if(profile->application_protocol_binding_required);
    satisfied += one_if(profile->key_confirmation_decision_required);
    satisfied += one_if(profile->kdf_boundary_required);
    satisfied += one_if(profile->domain_separation_required);
    satisfied += one_if(profile->shared_secret_lifecycle_required);
    satisfied += one_if(profile->failure_handling_required);
    satisfied += one_if(profile->key_separation_required);
    satisfied += one_if(profile->algorithm_agility_policy_required);
    satisfied += one_if(profile->clean_room_source_boundary_recorded);
    satisfied += one_if(profile->implementation_binding_required);
    satisfied += one_if(profile->kem_use_case_review_recorded);
    satisfied += one_if(profile->application_protocol_binding_recorded);
    satisfied += one_if(profile->key_confirmation_decision_recorded);
    satisfied += one_if(profile->kdf_binding_recorded);
    satisfied += one_if(profile->domain_separation_reviewed);
    satisfied += one_if(profile->shared_secret_lifecycle_reviewed);
    satisfied += one_if(profile->failure_handling_reviewed);
    satisfied += one_if(profile->key_separation_reviewed);
    satisfied += one_if(profile->algorithm_agility_reviewed);
    satisfied += one_if(profile->kem_usage_profile_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_sp800_227_usage_profile_error_label(
    latticra_q_seal_ml_kem_sp800_227_usage_profile_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare(
    latticra_q_seal_ml_kem_sp800_227_usage_profile_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->usage_profile,
        sizeof(out->usage_profile),
        "latticra-q-seal-ml-kem-sp800-227-usage-profile/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM SP 800-227 Usage Profile");
    copy_literal(out->standards_basis, sizeof(out->standards_basis), "NIST-SP-800-227");
    copy_literal(
        out->sp_800_227_source_url,
        sizeof(out->sp_800_227_source_url),
        "https://csrc.nist.gov/pubs/sp/800/227/final");
    copy_literal(
        out->sp_800_227_publication_date,
        sizeof(out->sp_800_227_publication_date),
        "September-2025");
    copy_literal(
        out->usage_scope,
        sizeof(out->usage_scope),
        "ML-KEM-SP-800-227-usage-before-shared-secret-emission");
    copy_literal(
        out->usage_state,
        sizeof(out->usage_state),
        "sp800-227-usage-profile-accepted-for-seal-hybrid-envelope-binding");

    out->sp800_227_usage_profile_present = 1u;
    out->sp_800_227_source_bound = 1u;
    out->sp_800_227_publication_date_recorded = 1u;
    out->kem_definition_bound = 1u;
    out->shared_secret_establishment_scope_bound = 1u;
    out->encapsulation_role_bound = 1u;
    out->decapsulation_role_bound = 1u;
    out->approved_kem_algorithm_required = 1u;
    out->fips_203_ml_kem_bound = 1u;
    out->key_establishment_context_required = 1u;
    out->application_protocol_binding_required = 1u;
    out->key_confirmation_decision_required = 1u;
    out->kdf_boundary_required = 1u;
    out->domain_separation_required = 1u;
    out->shared_secret_lifecycle_required = 1u;
    out->failure_handling_required = 1u;
    out->key_separation_required = 1u;
    out->algorithm_agility_policy_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->implementation_binding_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->kem_use_case_review_recorded = 1u;
    out->application_protocol_binding_recorded = 1u;
    out->key_confirmation_decision_recorded = 1u;
    out->kdf_binding_recorded = 1u;
    out->domain_separation_reviewed = 1u;
    out->shared_secret_lifecycle_reviewed = 1u;
    out->failure_handling_reviewed = 1u;
    out->key_separation_reviewed = 1u;
    out->algorithm_agility_reviewed = 1u;
    out->kem_usage_profile_accepted = 1u;
    out->operation_execution_allowed = 0u;
    out->shared_secret_emission_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_usage_items_total = 30u;
    out->required_usage_items_satisfied = required_items_satisfied(out);
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "none");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_OK;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-sp800-227-usage-profile-accepted-runtime-closed");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_sp800_227_usage_profile_is_no_effect(
    const latticra_q_seal_ml_kem_sp800_227_usage_profile_t *profile) {
    if (profile == NULL) {
        return 0;
    }

    return profile->sp800_227_usage_profile_present == 1u &&
           profile->clean_room_source_boundary_recorded == 1u &&
           profile->apple_corecrypto_code_copied == 0u &&
           profile->external_provider_code_copied == 0u &&
           profile->operation_execution_allowed == 0u &&
           profile->shared_secret_emission_allowed == 0u &&
           profile->production_crypto_claim_allowed == 0u &&
           profile->fips_claim_allowed == 0u &&
           profile->runtime_authority_granted == 0u;
}

int latticra_q_seal_ml_kem_sp800_227_usage_profile_allows_kem_usage_acceptance(
    const latticra_q_seal_ml_kem_sp800_227_usage_profile_t *profile) {
    if (profile == NULL) {
        return 0;
    }

    return profile->sp800_227_usage_profile_present == 1u &&
           profile->sp_800_227_source_bound == 1u &&
           profile->sp_800_227_publication_date_recorded == 1u &&
           profile->kem_definition_bound == 1u &&
           profile->shared_secret_establishment_scope_bound == 1u &&
           profile->encapsulation_role_bound == 1u &&
           profile->decapsulation_role_bound == 1u &&
           profile->approved_kem_algorithm_required == 1u &&
           profile->fips_203_ml_kem_bound == 1u &&
           profile->key_establishment_context_required == 1u &&
           profile->application_protocol_binding_required == 1u &&
           profile->key_confirmation_decision_required == 1u &&
           profile->kdf_boundary_required == 1u &&
           profile->domain_separation_required == 1u &&
           profile->shared_secret_lifecycle_required == 1u &&
           profile->failure_handling_required == 1u &&
           profile->key_separation_required == 1u &&
           profile->algorithm_agility_policy_required == 1u &&
           profile->clean_room_source_boundary_recorded == 1u &&
           profile->implementation_binding_required == 1u &&
           profile->apple_corecrypto_code_copied == 0u &&
           profile->external_provider_code_copied == 0u &&
           profile->kem_use_case_review_recorded == 1u &&
           profile->application_protocol_binding_recorded == 1u &&
           profile->key_confirmation_decision_recorded == 1u &&
           profile->kdf_binding_recorded == 1u &&
           profile->domain_separation_reviewed == 1u &&
           profile->shared_secret_lifecycle_reviewed == 1u &&
           profile->failure_handling_reviewed == 1u &&
           profile->key_separation_reviewed == 1u &&
           profile->algorithm_agility_reviewed == 1u &&
           profile->kem_usage_profile_accepted == 1u &&
           profile->operation_execution_allowed == 0u &&
           profile->shared_secret_emission_allowed == 0u &&
           profile->production_crypto_claim_allowed == 0u &&
           profile->fips_claim_allowed == 0u &&
           profile->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_sp800_227_usage_profile_report(
    const latticra_q_seal_ml_kem_sp800_227_usage_profile_t *profile,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (profile == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SP 800-227 USAGE PROFILE\n"
        "usage_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "sp_800_227_source_url=%s\n"
        "sp_800_227_publication_date=%s\n"
        "usage_scope=%s\n"
        "usage_state=%s\n"
        "sp800_227_usage_profile_present=%u\n"
        "sp_800_227_source_bound=%u\n"
        "sp_800_227_publication_date_recorded=%u\n"
        "kem_definition_bound=%u\n"
        "shared_secret_establishment_scope_bound=%u\n"
        "encapsulation_role_bound=%u\n"
        "decapsulation_role_bound=%u\n"
        "approved_kem_algorithm_required=%u\n"
        "fips_203_ml_kem_bound=%u\n"
        "key_establishment_context_required=%u\n"
        "application_protocol_binding_required=%u\n"
        "key_confirmation_decision_required=%u\n"
        "kdf_boundary_required=%u\n"
        "domain_separation_required=%u\n"
        "shared_secret_lifecycle_required=%u\n"
        "failure_handling_required=%u\n"
        "key_separation_required=%u\n"
        "algorithm_agility_policy_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "implementation_binding_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "kem_use_case_review_recorded=%u\n"
        "application_protocol_binding_recorded=%u\n"
        "key_confirmation_decision_recorded=%u\n"
        "kdf_binding_recorded=%u\n"
        "domain_separation_reviewed=%u\n"
        "shared_secret_lifecycle_reviewed=%u\n"
        "failure_handling_reviewed=%u\n"
        "key_separation_reviewed=%u\n"
        "algorithm_agility_reviewed=%u\n"
        "kem_usage_profile_accepted=%u\n"
        "operation_execution_allowed=%u\n"
        "shared_secret_emission_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_usage_items_total=%u\n"
        "required_usage_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        profile->usage_profile,
        profile->formal_title,
        profile->standards_basis,
        profile->sp_800_227_source_url,
        profile->sp_800_227_publication_date,
        profile->usage_scope,
        profile->usage_state,
        profile->sp800_227_usage_profile_present,
        profile->sp_800_227_source_bound,
        profile->sp_800_227_publication_date_recorded,
        profile->kem_definition_bound,
        profile->shared_secret_establishment_scope_bound,
        profile->encapsulation_role_bound,
        profile->decapsulation_role_bound,
        profile->approved_kem_algorithm_required,
        profile->fips_203_ml_kem_bound,
        profile->key_establishment_context_required,
        profile->application_protocol_binding_required,
        profile->key_confirmation_decision_required,
        profile->kdf_boundary_required,
        profile->domain_separation_required,
        profile->shared_secret_lifecycle_required,
        profile->failure_handling_required,
        profile->key_separation_required,
        profile->algorithm_agility_policy_required,
        profile->clean_room_source_boundary_recorded,
        profile->implementation_binding_required,
        profile->apple_corecrypto_code_copied,
        profile->external_provider_code_copied,
        profile->kem_use_case_review_recorded,
        profile->application_protocol_binding_recorded,
        profile->key_confirmation_decision_recorded,
        profile->kdf_binding_recorded,
        profile->domain_separation_reviewed,
        profile->shared_secret_lifecycle_reviewed,
        profile->failure_handling_reviewed,
        profile->key_separation_reviewed,
        profile->algorithm_agility_reviewed,
        profile->kem_usage_profile_accepted,
        profile->operation_execution_allowed,
        profile->shared_secret_emission_allowed,
        profile->production_crypto_claim_allowed,
        profile->fips_claim_allowed,
        profile->runtime_authority_granted,
        profile->required_usage_items_total,
        profile->required_usage_items_satisfied,
        profile->blocked_reason,
        latticra_q_seal_ml_kem_sp800_227_usage_profile_error_label(profile->error),
        profile->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
