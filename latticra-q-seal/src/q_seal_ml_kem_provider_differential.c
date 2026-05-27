#include "latticra/q_seal_ml_kem_provider_differential.h"

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

static unsigned parameter_set_is_recorded(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set) {
    latticra_q_seal_ml_kem_parameters_t parameters;

    if (latticra_q_seal_ml_kem_parameters(parameter_set, &parameters) !=
        LATTICRA_Q_SEAL_STATUS_OK) {
        return 0u;
    }

    return parameters.error == LATTICRA_Q_SEAL_ML_KEM_OK &&
           latticra_q_seal_ml_kem_parameters_are_authority_neutral(&parameters) == 1;
}

static unsigned required_items_satisfied(
    const latticra_q_seal_ml_kem_provider_differential_t *differential) {
    unsigned satisfied = 0u;

    satisfied += one_if(differential->provider_candidate_recorded);
    satisfied += one_if(differential->provider_comparison_only);
    satisfied += one_if(differential->parameter_sets_recorded);
    satisfied += one_if(differential->provider_license_review_recorded);
    satisfied += one_if(differential->provider_pinned_version_recorded);
    satisfied += one_if(differential->provider_source_digest_recorded);
    satisfied += one_if(differential->provider_build_reproducibility_recorded);
    satisfied += one_if(differential->positive_vector_comparison_recorded);
    satisfied += one_if(differential->negative_vector_comparison_recorded);
    satisfied += one_if(differential->mismatch_triage_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_provider_differential_error_label(
    latticra_q_seal_ml_kem_provider_differential_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_differential_prepare(
    latticra_q_seal_ml_kem_provider_differential_t *out) {
    unsigned parameter_512;
    unsigned parameter_768;
    unsigned parameter_1024;

    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->differential_profile,
        sizeof(out->differential_profile),
        "latticra-q-seal-ml-kem-provider-differential/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Provider Differential");
    copy_literal(out->candidate_provider, sizeof(out->candidate_provider), "liboqs-comparison-only");
    copy_literal(out->comparison_scope, sizeof(out->comparison_scope), "ML-KEM-FIPS203-keygen-encap-decap");
    copy_literal(out->differential_state, sizeof(out->differential_state), "comparison-contract-only");

    parameter_512 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512);
    parameter_768 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768);
    parameter_1024 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024);

    out->provider_differential_contract_present = 1u;
    out->provider_candidate_recorded = 1u;
    out->provider_comparison_only = 1u;
    out->provider_license_review_required = 1u;
    out->provider_license_review_recorded = 0u;
    out->provider_pinned_version_required = 1u;
    out->provider_pinned_version_recorded = 0u;
    out->provider_source_digest_required = 1u;
    out->provider_source_digest_recorded = 0u;
    out->provider_build_reproducibility_required = 1u;
    out->provider_build_reproducibility_recorded = 0u;
    out->provider_linking_enabled = 0u;
    out->provider_runtime_used = 0u;
    out->parameter_sets_recorded =
        parameter_512 == 1u && parameter_768 == 1u && parameter_1024 == 1u;
    out->ml_kem_512_comparison_required = 1u;
    out->ml_kem_768_comparison_required = 1u;
    out->ml_kem_1024_comparison_required = 1u;
    out->positive_vector_comparison_required = 1u;
    out->positive_vector_comparison_recorded = 0u;
    out->negative_vector_comparison_required = 1u;
    out->negative_vector_comparison_recorded = 0u;
    out->mismatch_triage_required = 1u;
    out->mismatch_triage_recorded = 0u;
    out->differential_keygen_enabled = 0u;
    out->differential_encap_decap_enabled = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_comparison_items_total = 10u;
    out->required_comparison_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "provider-license-version-digest-build-vector-and-mismatch-triage-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-provider-differential-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_provider_differential_is_comparison_only(
    const latticra_q_seal_ml_kem_provider_differential_t *differential) {
    if (differential == NULL) {
        return 0;
    }

    return differential->provider_comparison_only == 1u &&
           differential->provider_linking_enabled == 0u &&
           differential->provider_runtime_used == 0u &&
           differential->differential_keygen_enabled == 0u &&
           differential->differential_encap_decap_enabled == 0u &&
           differential->operation_execution_allowed == 0u &&
           differential->production_crypto_claim_allowed == 0u &&
           differential->fips_claim_allowed == 0u &&
           differential->runtime_authority_granted == 0u;
}

int latticra_q_seal_ml_kem_provider_differential_allows_provider_execution(
    const latticra_q_seal_ml_kem_provider_differential_t *differential) {
    if (differential == NULL) {
        return 0;
    }

    return differential->provider_candidate_recorded == 1u &&
           differential->provider_comparison_only == 1u &&
           differential->parameter_sets_recorded == 1u &&
           differential->provider_license_review_recorded == 1u &&
           differential->provider_pinned_version_recorded == 1u &&
           differential->provider_source_digest_recorded == 1u &&
           differential->provider_build_reproducibility_recorded == 1u &&
           differential->positive_vector_comparison_recorded == 1u &&
           differential->negative_vector_comparison_recorded == 1u &&
           differential->mismatch_triage_recorded == 1u &&
           differential->provider_linking_enabled == 0u &&
           differential->provider_runtime_used == 0u &&
           differential->operation_execution_allowed == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_differential_report(
    const latticra_q_seal_ml_kem_provider_differential_t *differential,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (differential == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM PROVIDER DIFFERENTIAL\n"
        "differential_profile=%s\n"
        "formal_title=%s\n"
        "candidate_provider=%s\n"
        "comparison_scope=%s\n"
        "differential_state=%s\n"
        "provider_differential_contract_present=%u\n"
        "provider_candidate_recorded=%u\n"
        "provider_comparison_only=%u\n"
        "provider_license_review_required=%u\n"
        "provider_license_review_recorded=%u\n"
        "provider_pinned_version_required=%u\n"
        "provider_pinned_version_recorded=%u\n"
        "provider_source_digest_required=%u\n"
        "provider_source_digest_recorded=%u\n"
        "provider_build_reproducibility_required=%u\n"
        "provider_build_reproducibility_recorded=%u\n"
        "provider_linking_enabled=%u\n"
        "provider_runtime_used=%u\n"
        "parameter_sets_recorded=%u\n"
        "ml_kem_512_comparison_required=%u\n"
        "ml_kem_768_comparison_required=%u\n"
        "ml_kem_1024_comparison_required=%u\n"
        "positive_vector_comparison_required=%u\n"
        "positive_vector_comparison_recorded=%u\n"
        "negative_vector_comparison_required=%u\n"
        "negative_vector_comparison_recorded=%u\n"
        "mismatch_triage_required=%u\n"
        "mismatch_triage_recorded=%u\n"
        "differential_keygen_enabled=%u\n"
        "differential_encap_decap_enabled=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_comparison_items_total=%u\n"
        "required_comparison_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        differential->differential_profile,
        differential->formal_title,
        differential->candidate_provider,
        differential->comparison_scope,
        differential->differential_state,
        differential->provider_differential_contract_present,
        differential->provider_candidate_recorded,
        differential->provider_comparison_only,
        differential->provider_license_review_required,
        differential->provider_license_review_recorded,
        differential->provider_pinned_version_required,
        differential->provider_pinned_version_recorded,
        differential->provider_source_digest_required,
        differential->provider_source_digest_recorded,
        differential->provider_build_reproducibility_required,
        differential->provider_build_reproducibility_recorded,
        differential->provider_linking_enabled,
        differential->provider_runtime_used,
        differential->parameter_sets_recorded,
        differential->ml_kem_512_comparison_required,
        differential->ml_kem_768_comparison_required,
        differential->ml_kem_1024_comparison_required,
        differential->positive_vector_comparison_required,
        differential->positive_vector_comparison_recorded,
        differential->negative_vector_comparison_required,
        differential->negative_vector_comparison_recorded,
        differential->mismatch_triage_required,
        differential->mismatch_triage_recorded,
        differential->differential_keygen_enabled,
        differential->differential_encap_decap_enabled,
        differential->operation_execution_allowed,
        differential->production_crypto_claim_allowed,
        differential->fips_claim_allowed,
        differential->runtime_authority_granted,
        differential->required_comparison_items_total,
        differential->required_comparison_items_satisfied,
        differential->blocked_reason,
        latticra_q_seal_ml_kem_provider_differential_error_label(differential->error),
        differential->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
