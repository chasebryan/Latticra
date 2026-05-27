#include "latticra/q_seal_ml_kem_randomness_source.h"

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
    const latticra_q_seal_ml_kem_randomness_source_t *source) {
    unsigned satisfied = 0u;

    satisfied += one_if(source->fips_203_source_verified);
    satisfied += one_if(source->sp_800_90a_tracked);
    satisfied += one_if(source->sp_800_90b_tracked);
    satisfied += one_if(source->keygen_seed_material_required);
    satisfied += one_if(source->encapsulation_seed_material_required);
    satisfied += one_if(source->deterministic_test_seed_separation_required);
    satisfied += one_if(source->entropy_source_inventory_recorded);
    satisfied += one_if(source->entropy_source_validation_recorded);
    satisfied += one_if(source->drbg_selection_recorded);
    satisfied += one_if(source->drbg_security_strength_recorded);
    satisfied += one_if(source->seed_derivation_policy_recorded);
    satisfied += one_if(source->reseed_policy_recorded);
    satisfied += one_if(source->prediction_resistance_policy_recorded);
    satisfied += one_if(source->health_tests_policy_recorded);
    satisfied += one_if(source->failure_mode_policy_recorded);
    satisfied += one_if(source->platform_rng_boundary_recorded);
    satisfied += one_if(source->entropy_review_signoff_recorded);
    satisfied += one_if(source->implementation_binding_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_randomness_source_error_label(
    latticra_q_seal_ml_kem_randomness_source_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_randomness_source_prepare(
    latticra_q_seal_ml_kem_randomness_source_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->randomness_profile,
        sizeof(out->randomness_profile),
        "latticra-q-seal-ml-kem-randomness-source/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Randomness Source Contract");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(
        out->random_bit_generation_source,
        sizeof(out->random_bit_generation_source),
        "NIST-SP-800-90A-and-NIST-SP-800-90B");
    copy_literal(
        out->randomness_scope,
        sizeof(out->randomness_scope),
        "ML-KEM-keygen-encapsulation-seed-material");
    copy_literal(
        out->randomness_state,
        sizeof(out->randomness_state),
        "policy-recorded-random-bit-generation-blocked");

    out->randomness_source_contract_present = 1u;
    out->fips_203_source_verified = 1u;
    out->sp_800_90a_tracked = 1u;
    out->sp_800_90b_tracked = 1u;
    out->keygen_seed_material_required = 1u;
    out->encapsulation_seed_material_required = 1u;
    out->deterministic_test_seed_separation_required = 1u;
    out->entropy_source_inventory_recorded = 0u;
    out->entropy_source_validation_recorded = 0u;
    out->drbg_selection_recorded = 0u;
    out->drbg_security_strength_recorded = 0u;
    out->seed_derivation_policy_recorded = 0u;
    out->reseed_policy_recorded = 0u;
    out->prediction_resistance_policy_recorded = 0u;
    out->health_tests_policy_recorded = 0u;
    out->failure_mode_policy_recorded = 0u;
    out->platform_rng_boundary_recorded = 0u;
    out->entropy_review_signoff_recorded = 0u;
    out->implementation_binding_recorded = 0u;
    out->random_bytes_generated = 0u;
    out->deterministic_test_seed_loaded = 0u;
    out->deterministic_rng_mode_enabled = 0u;
    out->random_bit_generation_allowed = 0u;
    out->key_generation_randomness_allowed = 0u;
    out->encapsulation_randomness_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_randomness_items_total = 18u;
    out->required_randomness_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "entropy-source-drbg-strength-reseed-health-failure-platform-review-and-binding-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-randomness-source-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_randomness_source_is_policy_only(
    const latticra_q_seal_ml_kem_randomness_source_t *source) {
    if (source == NULL) {
        return 0;
    }

    return source->randomness_source_contract_present == 1u &&
           source->fips_203_source_verified == 1u &&
           source->sp_800_90a_tracked == 1u &&
           source->sp_800_90b_tracked == 1u &&
           source->random_bytes_generated == 0u &&
           source->deterministic_test_seed_loaded == 0u &&
           source->deterministic_rng_mode_enabled == 0u &&
           source->random_bit_generation_allowed == 0u &&
           source->key_generation_randomness_allowed == 0u &&
           source->encapsulation_randomness_allowed == 0u &&
           source->operation_execution_allowed == 0u &&
           source->production_crypto_claim_allowed == 0u &&
           source->fips_claim_allowed == 0u &&
           source->runtime_authority_granted == 0u &&
           source->error == LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_BLOCKED;
}

int latticra_q_seal_ml_kem_randomness_source_allows_random_generation(
    const latticra_q_seal_ml_kem_randomness_source_t *source) {
    if (source == NULL) {
        return 0;
    }

    return source->fips_203_source_verified == 1u &&
           source->sp_800_90a_tracked == 1u &&
           source->sp_800_90b_tracked == 1u &&
           source->keygen_seed_material_required == 1u &&
           source->encapsulation_seed_material_required == 1u &&
           source->deterministic_test_seed_separation_required == 1u &&
           source->entropy_source_inventory_recorded == 1u &&
           source->entropy_source_validation_recorded == 1u &&
           source->drbg_selection_recorded == 1u &&
           source->drbg_security_strength_recorded == 1u &&
           source->seed_derivation_policy_recorded == 1u &&
           source->reseed_policy_recorded == 1u &&
           source->prediction_resistance_policy_recorded == 1u &&
           source->health_tests_policy_recorded == 1u &&
           source->failure_mode_policy_recorded == 1u &&
           source->platform_rng_boundary_recorded == 1u &&
           source->entropy_review_signoff_recorded == 1u &&
           source->implementation_binding_recorded == 1u &&
           source->random_bit_generation_allowed == 1u &&
           source->key_generation_randomness_allowed == 1u &&
           source->encapsulation_randomness_allowed == 1u &&
           source->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_randomness_source_report(
    const latticra_q_seal_ml_kem_randomness_source_t *source,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (source == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM RANDOMNESS SOURCE CONTRACT\n"
        "randomness_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "random_bit_generation_source=%s\n"
        "randomness_scope=%s\n"
        "randomness_state=%s\n"
        "randomness_source_contract_present=%u\n"
        "fips_203_source_verified=%u\n"
        "sp_800_90a_tracked=%u\n"
        "sp_800_90b_tracked=%u\n"
        "keygen_seed_material_required=%u\n"
        "encapsulation_seed_material_required=%u\n"
        "deterministic_test_seed_separation_required=%u\n"
        "entropy_source_inventory_recorded=%u\n"
        "entropy_source_validation_recorded=%u\n"
        "drbg_selection_recorded=%u\n"
        "drbg_security_strength_recorded=%u\n"
        "seed_derivation_policy_recorded=%u\n"
        "reseed_policy_recorded=%u\n"
        "prediction_resistance_policy_recorded=%u\n"
        "health_tests_policy_recorded=%u\n"
        "failure_mode_policy_recorded=%u\n"
        "platform_rng_boundary_recorded=%u\n"
        "entropy_review_signoff_recorded=%u\n"
        "implementation_binding_recorded=%u\n"
        "random_bytes_generated=%u\n"
        "deterministic_test_seed_loaded=%u\n"
        "deterministic_rng_mode_enabled=%u\n"
        "random_bit_generation_allowed=%u\n"
        "key_generation_randomness_allowed=%u\n"
        "encapsulation_randomness_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_randomness_items_total=%u\n"
        "required_randomness_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        source->randomness_profile,
        source->formal_title,
        source->standards_source,
        source->random_bit_generation_source,
        source->randomness_scope,
        source->randomness_state,
        source->randomness_source_contract_present,
        source->fips_203_source_verified,
        source->sp_800_90a_tracked,
        source->sp_800_90b_tracked,
        source->keygen_seed_material_required,
        source->encapsulation_seed_material_required,
        source->deterministic_test_seed_separation_required,
        source->entropy_source_inventory_recorded,
        source->entropy_source_validation_recorded,
        source->drbg_selection_recorded,
        source->drbg_security_strength_recorded,
        source->seed_derivation_policy_recorded,
        source->reseed_policy_recorded,
        source->prediction_resistance_policy_recorded,
        source->health_tests_policy_recorded,
        source->failure_mode_policy_recorded,
        source->platform_rng_boundary_recorded,
        source->entropy_review_signoff_recorded,
        source->implementation_binding_recorded,
        source->random_bytes_generated,
        source->deterministic_test_seed_loaded,
        source->deterministic_rng_mode_enabled,
        source->random_bit_generation_allowed,
        source->key_generation_randomness_allowed,
        source->encapsulation_randomness_allowed,
        source->operation_execution_allowed,
        source->production_crypto_claim_allowed,
        source->fips_claim_allowed,
        source->runtime_authority_granted,
        source->required_randomness_items_total,
        source->required_randomness_items_satisfied,
        source->blocked_reason,
        latticra_q_seal_ml_kem_randomness_source_error_label(source->error),
        source->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
