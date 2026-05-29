#include "latticra/q_seal_ml_kem.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_q_seal_ml_kem_error_label(
    latticra_q_seal_ml_kem_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET:
        return "invalid-parameter-set";
    case LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED:
        return "operation-disabled";
    default:
        return "unknown";
    }
}

const char *latticra_q_seal_ml_kem_parameter_set_label(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set) {
    switch (parameter_set) {
    case LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512:
        return "ML-KEM-512";
    case LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768:
        return "ML-KEM-768";
    case LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024:
        return "ML-KEM-1024";
    default:
        return "unknown";
    }
}

static void parameters_init(latticra_q_seal_ml_kem_parameters_t *out) {
    memset(out, 0, sizeof(*out));
    copy_literal(out->ml_kem_profile, sizeof(out->ml_kem_profile), "latticra-q-seal-ml-kem/0.1");
    copy_literal(out->formal_title, sizeof(out->formal_title), "Latticra Q-Seal ML-KEM");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(out->operation_state, sizeof(out->operation_state), "disabled");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "clean-room-implementation-not-present");
    out->fips_203_parameter_set_tracked = 1u;
    out->known_answer_tests_required = 1u;
    out->acvp_vector_review_required = 1u;
    out->clean_room_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->provider_linked = 0u;
    out->key_generation_enabled = 0u;
    out->encapsulation_enabled = 0u;
    out->decapsulation_enabled = 0u;
    out->key_generation_performed = 0u;
    out->encapsulation_performed = 0u;
    out->decapsulation_performed = 0u;
    out->shared_secret_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET;
    copy_literal(out->status, sizeof(out->status), "invalid-parameter-set");
}

static void set_common_parameter_fields(
    latticra_q_seal_ml_kem_parameters_t *out,
    latticra_q_seal_ml_kem_parameter_set_t parameter_set,
    unsigned security_category,
    unsigned k,
    unsigned eta1,
    unsigned eta2,
    unsigned du,
    unsigned dv,
    unsigned required_rbg_strength_bits,
    unsigned encapsulation_key_bytes,
    unsigned decapsulation_key_bytes,
    unsigned ciphertext_bytes) {
    out->parameter_set = (unsigned)parameter_set;
    copy_literal(
        out->parameter_set_name,
        sizeof(out->parameter_set_name),
        latticra_q_seal_ml_kem_parameter_set_label(parameter_set));
    out->security_category = security_category;
    out->n = 256u;
    out->q = 3329u;
    out->k = k;
    out->eta1 = eta1;
    out->eta2 = eta2;
    out->du = du;
    out->dv = dv;
    out->required_rbg_strength_bits = required_rbg_strength_bits;
    out->encapsulation_key_bytes = encapsulation_key_bytes;
    out->decapsulation_key_bytes = decapsulation_key_bytes;
    out->ciphertext_bytes = ciphertext_bytes;
    out->shared_secret_key_bytes = 32u;
    copy_literal(out->operation_state, sizeof(out->operation_state), "operations-disabled");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "clean-room-implementation-not-present");
    out->error = LATTICRA_Q_SEAL_ML_KEM_OK;
    copy_literal(out->status, sizeof(out->status), "ml-kem-parameters-recorded");
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_parameters(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set,
    latticra_q_seal_ml_kem_parameters_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    parameters_init(out);

    switch (parameter_set) {
    case LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512:
        set_common_parameter_fields(out, parameter_set, 1u, 2u, 3u, 2u, 10u, 4u, 128u, 800u, 1632u, 768u);
        return LATTICRA_Q_SEAL_STATUS_OK;
    case LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768:
        set_common_parameter_fields(out, parameter_set, 3u, 3u, 2u, 2u, 10u, 4u, 192u, 1184u, 2400u, 1088u);
        return LATTICRA_Q_SEAL_STATUS_OK;
    case LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024:
        set_common_parameter_fields(out, parameter_set, 5u, 4u, 2u, 2u, 11u, 5u, 256u, 1568u, 3168u, 1568u);
        return LATTICRA_Q_SEAL_STATUS_OK;
    default:
        return LATTICRA_Q_SEAL_STATUS_OK;
    }
}

int latticra_q_seal_ml_kem_parameters_are_authority_neutral(
    const latticra_q_seal_ml_kem_parameters_t *parameters) {
    if (parameters == NULL) {
        return 0;
    }

    return parameters->apple_corecrypto_code_copied == 0u &&
           parameters->provider_linked == 0u &&
           parameters->key_generation_enabled == 0u &&
           parameters->encapsulation_enabled == 0u &&
           parameters->decapsulation_enabled == 0u &&
           parameters->key_generation_performed == 0u &&
           parameters->encapsulation_performed == 0u &&
           parameters->decapsulation_performed == 0u &&
           parameters->shared_secret_emitted == 0u &&
           parameters->production_crypto_claim_allowed == 0u &&
           parameters->fips_claim_allowed == 0u &&
           parameters->runtime_authority_granted == 0u;
}

latticra_q_seal_ml_kem_error_t latticra_q_seal_ml_kem_keygen_disabled(
    const latticra_q_seal_ml_kem_parameters_t *parameters) {
    if (parameters == NULL || parameters->error != LATTICRA_Q_SEAL_ML_KEM_OK) {
        return LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET;
    }
    return LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED;
}

latticra_q_seal_ml_kem_error_t latticra_q_seal_ml_kem_encaps_disabled(
    const latticra_q_seal_ml_kem_parameters_t *parameters) {
    if (parameters == NULL || parameters->error != LATTICRA_Q_SEAL_ML_KEM_OK) {
        return LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET;
    }
    return LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED;
}

latticra_q_seal_ml_kem_error_t latticra_q_seal_ml_kem_decaps_disabled(
    const latticra_q_seal_ml_kem_parameters_t *parameters) {
    if (parameters == NULL || parameters->error != LATTICRA_Q_SEAL_ML_KEM_OK) {
        return LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET;
    }
    return LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_parameters_report(
    const latticra_q_seal_ml_kem_parameters_t *parameters,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (parameters == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM PARAMETERS\n"
        "ml_kem_profile=%s\n"
        "formal_title=%s\n"
        "parameter_set_name=%s\n"
        "standards_source=%s\n"
        "parameter_set=%u\n"
        "security_category=%u\n"
        "n=%u\n"
        "q=%u\n"
        "k=%u\n"
        "eta1=%u\n"
        "eta2=%u\n"
        "du=%u\n"
        "dv=%u\n"
        "required_rbg_strength_bits=%u\n"
        "encapsulation_key_bytes=%u\n"
        "decapsulation_key_bytes=%u\n"
        "ciphertext_bytes=%u\n"
        "shared_secret_key_bytes=%u\n"
        "fips_203_parameter_set_tracked=%u\n"
        "known_answer_tests_required=%u\n"
        "acvp_vector_review_required=%u\n"
        "clean_room_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "provider_linked=%u\n"
        "key_generation_enabled=%u\n"
        "encapsulation_enabled=%u\n"
        "decapsulation_enabled=%u\n"
        "key_generation_performed=%u\n"
        "encapsulation_performed=%u\n"
        "decapsulation_performed=%u\n"
        "shared_secret_emitted=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "operation_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        parameters->ml_kem_profile,
        parameters->formal_title,
        parameters->parameter_set_name,
        parameters->standards_source,
        parameters->parameter_set,
        parameters->security_category,
        parameters->n,
        parameters->q,
        parameters->k,
        parameters->eta1,
        parameters->eta2,
        parameters->du,
        parameters->dv,
        parameters->required_rbg_strength_bits,
        parameters->encapsulation_key_bytes,
        parameters->decapsulation_key_bytes,
        parameters->ciphertext_bytes,
        parameters->shared_secret_key_bytes,
        parameters->fips_203_parameter_set_tracked,
        parameters->known_answer_tests_required,
        parameters->acvp_vector_review_required,
        parameters->clean_room_required,
        parameters->apple_corecrypto_code_copied,
        parameters->provider_linked,
        parameters->key_generation_enabled,
        parameters->encapsulation_enabled,
        parameters->decapsulation_enabled,
        parameters->key_generation_performed,
        parameters->encapsulation_performed,
        parameters->decapsulation_performed,
        parameters->shared_secret_emitted,
        parameters->production_crypto_claim_allowed,
        parameters->fips_claim_allowed,
        parameters->runtime_authority_granted,
        parameters->operation_state,
        parameters->blocked_reason,
        latticra_q_seal_ml_kem_error_label(parameters->error),
        parameters->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
