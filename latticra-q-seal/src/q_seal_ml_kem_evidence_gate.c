#include "latticra/q_seal_ml_kem_evidence_gate.h"

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
    const latticra_q_seal_ml_kem_evidence_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->fips_203_source_verified);
    satisfied += one_if(gate->fips_203_errata_review_recorded);
    satisfied += one_if(gate->parameter_sets_recorded);
    satisfied += one_if(gate->known_answer_test_manifest_present);
    satisfied += one_if(gate->known_answer_vectors_verified);
    satisfied += one_if(gate->acvp_vector_review_recorded);
    satisfied += one_if(gate->clean_room_implementation_review_recorded);
    satisfied += one_if(gate->provider_differential_test_contract_recorded);
    satisfied += one_if(gate->constant_time_review_recorded);
    satisfied += one_if(gate->side_channel_review_recorded);
    satisfied += one_if(gate->randomness_source_contract_recorded);
    satisfied += one_if(gate->intermediate_zeroization_contract_recorded);
    satisfied += one_if(gate->memory_safety_review_recorded);
    satisfied += one_if(gate->api_misuse_resistance_review_recorded);
    satisfied += one_if(gate->fuzzing_and_negative_tests_recorded);
    satisfied += one_if(gate->ci_quality_gate_recorded);

    return satisfied;
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

const char *latticra_q_seal_ml_kem_evidence_gate_error_label(
    latticra_q_seal_ml_kem_evidence_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_gate_prepare(
    latticra_q_seal_ml_kem_evidence_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->gate_profile,
        sizeof(out->gate_profile),
        "latticra-q-seal-ml-kem-evidence-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Evidence Gate");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(out->standards_publication_date, sizeof(out->standards_publication_date), "2024-08-13");
    copy_literal(out->standards_errata_state, sizeof(out->standards_errata_state), "errata-review-required");
    copy_literal(
        out->kat_manifest_path,
        sizeof(out->kat_manifest_path),
        "latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md");
    copy_literal(out->acvp_vector_source, sizeof(out->acvp_vector_source), "NIST-ACVP-required");

    out->ml_kem_evidence_gate_present = 1u;
    out->fips_203_source_verified = 1u;
    out->fips_203_errata_review_required = 1u;
    out->fips_203_errata_review_recorded = 0u;
    out->ml_kem_512_parameters_recorded =
        parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512);
    out->ml_kem_768_parameters_recorded =
        parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768);
    out->ml_kem_1024_parameters_recorded =
        parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024);
    out->parameter_sets_recorded =
        out->ml_kem_512_parameters_recorded == 1u &&
        out->ml_kem_768_parameters_recorded == 1u &&
        out->ml_kem_1024_parameters_recorded == 1u;
    out->known_answer_test_manifest_present = 1u;
    out->known_answer_vectors_embedded = 0u;
    out->known_answer_vectors_loaded = 0u;
    out->known_answer_vectors_verified = 0u;
    out->acvp_vector_review_required = 1u;
    out->acvp_vector_review_recorded = 0u;
    out->clean_room_required = 1u;
    out->clean_room_implementation_review_recorded = 0u;
    out->apple_corecrypto_code_copied = 0u;
    out->provider_differential_test_contract_required = 1u;
    out->provider_differential_test_contract_recorded = 0u;
    out->provider_linked = 0u;
    out->constant_time_review_required = 1u;
    out->constant_time_review_recorded = 0u;
    out->side_channel_review_required = 1u;
    out->side_channel_review_recorded = 0u;
    out->randomness_source_contract_required = 1u;
    out->randomness_source_contract_recorded = 0u;
    out->intermediate_zeroization_contract_required = 1u;
    out->intermediate_zeroization_contract_recorded = 0u;
    out->memory_safety_review_required = 1u;
    out->memory_safety_review_recorded = 0u;
    out->api_misuse_resistance_review_required = 1u;
    out->api_misuse_resistance_review_recorded = 0u;
    out->fuzzing_and_negative_tests_required = 1u;
    out->fuzzing_and_negative_tests_recorded = 0u;
    out->ci_quality_gate_required = 1u;
    out->ci_quality_gate_recorded = 0u;
    out->required_evidence_items_total = 16u;
    out->required_evidence_items_satisfied = required_items_satisfied(out);
    out->implementation_present = 0u;
    out->operations_enabled = 0u;
    out->key_generation_enabled = 0u;
    out->encapsulation_enabled = 0u;
    out->decapsulation_enabled = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(out->gate_state, sizeof(out->gate_state), "blocked-awaiting-evidence");
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "kat-acvp-errata-constant-time-side-channel-randomness-zeroization-reviews-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-evidence-gate-fail-closed");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_evidence_gate_is_fail_closed(
    const latticra_q_seal_ml_kem_evidence_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->apple_corecrypto_code_copied == 0u &&
           gate->provider_linked == 0u &&
           gate->known_answer_vectors_embedded == 0u &&
           gate->known_answer_vectors_loaded == 0u &&
           gate->known_answer_vectors_verified == 0u &&
           gate->implementation_present == 0u &&
           gate->operations_enabled == 0u &&
           gate->key_generation_enabled == 0u &&
           gate->encapsulation_enabled == 0u &&
           gate->decapsulation_enabled == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_BLOCKED;
}

int latticra_q_seal_ml_kem_evidence_gate_allows_operations(
    const latticra_q_seal_ml_kem_evidence_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->fips_203_source_verified == 1u &&
           gate->fips_203_errata_review_recorded == 1u &&
           gate->parameter_sets_recorded == 1u &&
           gate->known_answer_vectors_verified == 1u &&
           gate->acvp_vector_review_recorded == 1u &&
           gate->clean_room_implementation_review_recorded == 1u &&
           gate->provider_differential_test_contract_recorded == 1u &&
           gate->constant_time_review_recorded == 1u &&
           gate->side_channel_review_recorded == 1u &&
           gate->randomness_source_contract_recorded == 1u &&
           gate->intermediate_zeroization_contract_recorded == 1u &&
           gate->memory_safety_review_recorded == 1u &&
           gate->api_misuse_resistance_review_recorded == 1u &&
           gate->fuzzing_and_negative_tests_recorded == 1u &&
           gate->ci_quality_gate_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->provider_linked == 0u &&
           gate->implementation_present == 1u &&
           gate->operations_enabled == 1u &&
           gate->production_crypto_claim_allowed == 1u &&
           gate->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_gate_report(
    const latticra_q_seal_ml_kem_evidence_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM EVIDENCE GATE\n"
        "gate_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "standards_publication_date=%s\n"
        "standards_errata_state=%s\n"
        "kat_manifest_path=%s\n"
        "acvp_vector_source=%s\n"
        "ml_kem_evidence_gate_present=%u\n"
        "fips_203_source_verified=%u\n"
        "fips_203_errata_review_required=%u\n"
        "fips_203_errata_review_recorded=%u\n"
        "parameter_sets_recorded=%u\n"
        "ml_kem_512_parameters_recorded=%u\n"
        "ml_kem_768_parameters_recorded=%u\n"
        "ml_kem_1024_parameters_recorded=%u\n"
        "known_answer_test_manifest_present=%u\n"
        "known_answer_vectors_embedded=%u\n"
        "known_answer_vectors_loaded=%u\n"
        "known_answer_vectors_verified=%u\n"
        "acvp_vector_review_required=%u\n"
        "acvp_vector_review_recorded=%u\n"
        "clean_room_required=%u\n"
        "clean_room_implementation_review_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "provider_differential_test_contract_required=%u\n"
        "provider_differential_test_contract_recorded=%u\n"
        "provider_linked=%u\n"
        "constant_time_review_required=%u\n"
        "constant_time_review_recorded=%u\n"
        "side_channel_review_required=%u\n"
        "side_channel_review_recorded=%u\n"
        "randomness_source_contract_required=%u\n"
        "randomness_source_contract_recorded=%u\n"
        "intermediate_zeroization_contract_required=%u\n"
        "intermediate_zeroization_contract_recorded=%u\n"
        "memory_safety_review_required=%u\n"
        "memory_safety_review_recorded=%u\n"
        "api_misuse_resistance_review_required=%u\n"
        "api_misuse_resistance_review_recorded=%u\n"
        "fuzzing_and_negative_tests_required=%u\n"
        "fuzzing_and_negative_tests_recorded=%u\n"
        "ci_quality_gate_required=%u\n"
        "ci_quality_gate_recorded=%u\n"
        "required_evidence_items_total=%u\n"
        "required_evidence_items_satisfied=%u\n"
        "implementation_present=%u\n"
        "operations_enabled=%u\n"
        "key_generation_enabled=%u\n"
        "encapsulation_enabled=%u\n"
        "decapsulation_enabled=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "gate_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->gate_profile,
        gate->formal_title,
        gate->standards_source,
        gate->standards_publication_date,
        gate->standards_errata_state,
        gate->kat_manifest_path,
        gate->acvp_vector_source,
        gate->ml_kem_evidence_gate_present,
        gate->fips_203_source_verified,
        gate->fips_203_errata_review_required,
        gate->fips_203_errata_review_recorded,
        gate->parameter_sets_recorded,
        gate->ml_kem_512_parameters_recorded,
        gate->ml_kem_768_parameters_recorded,
        gate->ml_kem_1024_parameters_recorded,
        gate->known_answer_test_manifest_present,
        gate->known_answer_vectors_embedded,
        gate->known_answer_vectors_loaded,
        gate->known_answer_vectors_verified,
        gate->acvp_vector_review_required,
        gate->acvp_vector_review_recorded,
        gate->clean_room_required,
        gate->clean_room_implementation_review_recorded,
        gate->apple_corecrypto_code_copied,
        gate->provider_differential_test_contract_required,
        gate->provider_differential_test_contract_recorded,
        gate->provider_linked,
        gate->constant_time_review_required,
        gate->constant_time_review_recorded,
        gate->side_channel_review_required,
        gate->side_channel_review_recorded,
        gate->randomness_source_contract_required,
        gate->randomness_source_contract_recorded,
        gate->intermediate_zeroization_contract_required,
        gate->intermediate_zeroization_contract_recorded,
        gate->memory_safety_review_required,
        gate->memory_safety_review_recorded,
        gate->api_misuse_resistance_review_required,
        gate->api_misuse_resistance_review_recorded,
        gate->fuzzing_and_negative_tests_required,
        gate->fuzzing_and_negative_tests_recorded,
        gate->ci_quality_gate_required,
        gate->ci_quality_gate_recorded,
        gate->required_evidence_items_total,
        gate->required_evidence_items_satisfied,
        gate->implementation_present,
        gate->operations_enabled,
        gate->key_generation_enabled,
        gate->encapsulation_enabled,
        gate->decapsulation_enabled,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->runtime_authority_granted,
        gate->gate_state,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_evidence_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
