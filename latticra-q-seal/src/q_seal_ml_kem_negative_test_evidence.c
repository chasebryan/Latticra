#include "latticra/q_seal_ml_kem_negative_test_evidence.h"

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
    const latticra_q_seal_ml_kem_negative_test_evidence_t *evidence) {
    unsigned satisfied = 0u;

    satisfied += one_if(evidence->fips_203_source_verified);
    satisfied += one_if(evidence->acvp_ml_kem_schema_tracked);
    satisfied += one_if(evidence->vector_schema_bound);
    satisfied += one_if(evidence->vector_source_bound);
    satisfied += one_if(evidence->malformed_ciphertext_tests_required);
    satisfied += one_if(evidence->malformed_key_tests_required);
    satisfied += one_if(evidence->negative_replay_tests_required);
    satisfied += one_if(evidence->length_validation_tests_recorded);
    satisfied += one_if(evidence->encoding_canonicality_tests_recorded);
    satisfied += one_if(evidence->invalid_ciphertext_tests_recorded);
    satisfied += one_if(evidence->invalid_public_key_tests_recorded);
    satisfied += one_if(evidence->invalid_secret_key_tests_recorded);
    satisfied += one_if(evidence->decapsulation_failure_tests_recorded);
    satisfied += one_if(evidence->implicit_rejection_tests_recorded);
    satisfied += one_if(evidence->parser_rejection_tests_recorded);
    satisfied += one_if(evidence->fuzzing_corpus_recorded);
    satisfied += one_if(evidence->differential_negative_tests_recorded);
    satisfied += one_if(evidence->implementation_binding_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_negative_test_evidence_error_label(
    latticra_q_seal_ml_kem_negative_test_evidence_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_negative_test_evidence_prepare(
    latticra_q_seal_ml_kem_negative_test_evidence_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->evidence_profile,
        sizeof(out->evidence_profile),
        "latticra-q-seal-ml-kem-negative-test-evidence/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Negative-Test Evidence");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(out->acvp_source, sizeof(out->acvp_source), "NIST-ACVP-ML-KEM");
    copy_literal(
        out->evidence_scope,
        sizeof(out->evidence_scope),
        "ML-KEM-malformed-input-negative-vector-behavior");
    copy_literal(
        out->evidence_state,
        sizeof(out->evidence_state),
        "policy-recorded-test-execution-missing");

    out->negative_test_evidence_present = 1u;
    out->fips_203_source_verified = 1u;
    out->acvp_ml_kem_schema_tracked = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_bound = 1u;
    out->malformed_ciphertext_tests_required = 1u;
    out->malformed_key_tests_required = 1u;
    out->negative_replay_tests_required = 1u;
    out->length_validation_tests_recorded = 0u;
    out->encoding_canonicality_tests_recorded = 0u;
    out->invalid_ciphertext_tests_recorded = 0u;
    out->invalid_public_key_tests_recorded = 0u;
    out->invalid_secret_key_tests_recorded = 0u;
    out->decapsulation_failure_tests_recorded = 0u;
    out->implicit_rejection_tests_recorded = 0u;
    out->parser_rejection_tests_recorded = 0u;
    out->fuzzing_corpus_recorded = 0u;
    out->differential_negative_tests_recorded = 0u;
    out->implementation_binding_recorded = 0u;
    out->negative_tests_executed = 0u;
    out->parser_execution_allowed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_negative_test_items_total = 18u;
    out->required_negative_test_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "malformed-input-length-encoding-rejection-fuzzing-differential-and-binding-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-negative-test-evidence-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_negative_test_evidence_is_policy_only(
    const latticra_q_seal_ml_kem_negative_test_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->negative_test_evidence_present == 1u &&
           evidence->malformed_ciphertext_tests_required == 1u &&
           evidence->malformed_key_tests_required == 1u &&
           evidence->negative_replay_tests_required == 1u &&
           evidence->length_validation_tests_recorded == 0u &&
           evidence->encoding_canonicality_tests_recorded == 0u &&
           evidence->invalid_ciphertext_tests_recorded == 0u &&
           evidence->negative_tests_executed == 0u &&
           evidence->parser_execution_allowed == 0u &&
           evidence->implementation_promotion_allowed == 0u &&
           evidence->operation_execution_allowed == 0u &&
           evidence->production_crypto_claim_allowed == 0u &&
           evidence->fips_claim_allowed == 0u &&
           evidence->runtime_authority_granted == 0u &&
           evidence->error == LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_BLOCKED;
}

int latticra_q_seal_ml_kem_negative_test_evidence_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_negative_test_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->fips_203_source_verified == 1u &&
           evidence->acvp_ml_kem_schema_tracked == 1u &&
           evidence->vector_schema_bound == 1u &&
           evidence->vector_source_bound == 1u &&
           evidence->malformed_ciphertext_tests_required == 1u &&
           evidence->malformed_key_tests_required == 1u &&
           evidence->negative_replay_tests_required == 1u &&
           evidence->length_validation_tests_recorded == 1u &&
           evidence->encoding_canonicality_tests_recorded == 1u &&
           evidence->invalid_ciphertext_tests_recorded == 1u &&
           evidence->invalid_public_key_tests_recorded == 1u &&
           evidence->invalid_secret_key_tests_recorded == 1u &&
           evidence->decapsulation_failure_tests_recorded == 1u &&
           evidence->implicit_rejection_tests_recorded == 1u &&
           evidence->parser_rejection_tests_recorded == 1u &&
           evidence->fuzzing_corpus_recorded == 1u &&
           evidence->differential_negative_tests_recorded == 1u &&
           evidence->implementation_binding_recorded == 1u &&
           evidence->implementation_promotion_allowed == 1u &&
           evidence->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_negative_test_evidence_report(
    const latticra_q_seal_ml_kem_negative_test_evidence_t *evidence,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (evidence == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM NEGATIVE-TEST EVIDENCE\n"
        "evidence_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "acvp_source=%s\n"
        "evidence_scope=%s\n"
        "evidence_state=%s\n"
        "negative_test_evidence_present=%u\n"
        "fips_203_source_verified=%u\n"
        "acvp_ml_kem_schema_tracked=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_bound=%u\n"
        "malformed_ciphertext_tests_required=%u\n"
        "malformed_key_tests_required=%u\n"
        "negative_replay_tests_required=%u\n"
        "length_validation_tests_recorded=%u\n"
        "encoding_canonicality_tests_recorded=%u\n"
        "invalid_ciphertext_tests_recorded=%u\n"
        "invalid_public_key_tests_recorded=%u\n"
        "invalid_secret_key_tests_recorded=%u\n"
        "decapsulation_failure_tests_recorded=%u\n"
        "implicit_rejection_tests_recorded=%u\n"
        "parser_rejection_tests_recorded=%u\n"
        "fuzzing_corpus_recorded=%u\n"
        "differential_negative_tests_recorded=%u\n"
        "implementation_binding_recorded=%u\n"
        "negative_tests_executed=%u\n"
        "parser_execution_allowed=%u\n"
        "implementation_promotion_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_negative_test_items_total=%u\n"
        "required_negative_test_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        evidence->evidence_profile,
        evidence->formal_title,
        evidence->standards_source,
        evidence->acvp_source,
        evidence->evidence_scope,
        evidence->evidence_state,
        evidence->negative_test_evidence_present,
        evidence->fips_203_source_verified,
        evidence->acvp_ml_kem_schema_tracked,
        evidence->vector_schema_bound,
        evidence->vector_source_bound,
        evidence->malformed_ciphertext_tests_required,
        evidence->malformed_key_tests_required,
        evidence->negative_replay_tests_required,
        evidence->length_validation_tests_recorded,
        evidence->encoding_canonicality_tests_recorded,
        evidence->invalid_ciphertext_tests_recorded,
        evidence->invalid_public_key_tests_recorded,
        evidence->invalid_secret_key_tests_recorded,
        evidence->decapsulation_failure_tests_recorded,
        evidence->implicit_rejection_tests_recorded,
        evidence->parser_rejection_tests_recorded,
        evidence->fuzzing_corpus_recorded,
        evidence->differential_negative_tests_recorded,
        evidence->implementation_binding_recorded,
        evidence->negative_tests_executed,
        evidence->parser_execution_allowed,
        evidence->implementation_promotion_allowed,
        evidence->operation_execution_allowed,
        evidence->production_crypto_claim_allowed,
        evidence->fips_claim_allowed,
        evidence->runtime_authority_granted,
        evidence->required_negative_test_items_total,
        evidence->required_negative_test_items_satisfied,
        evidence->blocked_reason,
        latticra_q_seal_ml_kem_negative_test_evidence_error_label(evidence->error),
        evidence->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
