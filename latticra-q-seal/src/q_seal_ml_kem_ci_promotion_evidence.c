#include "latticra/q_seal_ml_kem_ci_promotion_evidence.h"

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
    const latticra_q_seal_ml_kem_ci_promotion_evidence_t *evidence) {
    unsigned satisfied = 0u;

    satisfied += one_if(evidence->ci_promotion_evidence_present);
    satisfied += one_if(evidence->ssdf_secure_build_gate_recorded);
    satisfied += one_if(evidence->fips_203_parameter_gate_bound);
    satisfied += one_if(evidence->sp_800_227_kem_usage_gate_bound);
    satisfied += one_if(evidence->make_quality_security_standards_bound);
    satisfied += one_if(evidence->local_wrapper_scripts_recorded);
    satisfied += one_if(evidence->qseal_subsystem_scripts_recorded);
    satisfied += one_if(evidence->readiness_gate_bound);
    satisfied += one_if(evidence->implementation_binding_manifest_bound);
    satisfied += one_if(evidence->kat_acvp_gate_passing_recorded);
    satisfied += one_if(evidence->constant_time_gate_passing_recorded);
    satisfied += one_if(evidence->memory_safety_gate_passing_recorded);
    satisfied += one_if(evidence->side_channel_gate_passing_recorded);
    satisfied += one_if(evidence->negative_test_gate_passing_recorded);
    satisfied += one_if(evidence->provider_differential_gate_passing_recorded);
    satisfied += one_if(evidence->implementation_binding_ci_result_recorded);
    satisfied += one_if(evidence->promotion_workflow_recorded);
    satisfied += one_if(evidence->release_claim_gate_recorded);
    satisfied += one_if(evidence->signed_artifact_receipt_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_ci_promotion_evidence_error_label(
    latticra_q_seal_ml_kem_ci_promotion_evidence_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_ci_promotion_evidence_prepare(
    latticra_q_seal_ml_kem_ci_promotion_evidence_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->promotion_profile,
        sizeof(out->promotion_profile),
        "latticra-q-seal-ml-kem-ci-promotion-evidence/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM CI Promotion Evidence");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203-and-SP-800-227");
    copy_literal(
        out->promotion_scope,
        sizeof(out->promotion_scope),
        "ML-KEM-evidence-gates-before-implementation-promotion");
    copy_literal(out->promotion_state, sizeof(out->promotion_state), "ci-promotion-blocked");

    out->ci_promotion_evidence_present = 1u;
    out->ssdf_secure_build_gate_recorded = 1u;
    out->fips_203_parameter_gate_bound = 1u;
    out->sp_800_227_kem_usage_gate_bound = 1u;
    out->make_quality_security_standards_bound = 1u;
    out->local_wrapper_scripts_recorded = 1u;
    out->qseal_subsystem_scripts_recorded = 1u;
    out->readiness_gate_bound = 1u;
    out->implementation_binding_manifest_required = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->kat_acvp_gate_passing_recorded = 0u;
    out->constant_time_gate_passing_recorded = 0u;
    out->memory_safety_gate_passing_recorded = 0u;
    out->side_channel_gate_passing_recorded = 0u;
    out->negative_test_gate_passing_recorded = 0u;
    out->provider_differential_gate_passing_recorded = 0u;
    out->implementation_binding_ci_result_recorded = 0u;
    out->promotion_workflow_recorded = 0u;
    out->release_claim_gate_recorded = 0u;
    out->signed_artifact_receipt_recorded = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_promotion_items_total = 19u;
    out->required_promotion_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "ci-vector-constant-time-memory-side-channel-provider-binding-workflow-release-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-ci-promotion-evidence-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_ci_promotion_evidence_is_no_effect(
    const latticra_q_seal_ml_kem_ci_promotion_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->ci_promotion_evidence_present == 1u &&
           evidence->operation_execution_allowed == 0u &&
           evidence->production_crypto_claim_allowed == 0u &&
           evidence->fips_claim_allowed == 0u &&
           evidence->runtime_authority_granted == 0u &&
           evidence->error == LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_BLOCKED;
}

int latticra_q_seal_ml_kem_ci_promotion_evidence_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_ci_promotion_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->ci_promotion_evidence_present == 1u &&
           evidence->ssdf_secure_build_gate_recorded == 1u &&
           evidence->fips_203_parameter_gate_bound == 1u &&
           evidence->sp_800_227_kem_usage_gate_bound == 1u &&
           evidence->make_quality_security_standards_bound == 1u &&
           evidence->local_wrapper_scripts_recorded == 1u &&
           evidence->qseal_subsystem_scripts_recorded == 1u &&
           evidence->readiness_gate_bound == 1u &&
           evidence->implementation_binding_manifest_bound == 1u &&
           evidence->kat_acvp_gate_passing_recorded == 1u &&
           evidence->constant_time_gate_passing_recorded == 1u &&
           evidence->memory_safety_gate_passing_recorded == 1u &&
           evidence->side_channel_gate_passing_recorded == 1u &&
           evidence->negative_test_gate_passing_recorded == 1u &&
           evidence->provider_differential_gate_passing_recorded == 1u &&
           evidence->implementation_binding_ci_result_recorded == 1u &&
           evidence->promotion_workflow_recorded == 1u &&
           evidence->release_claim_gate_recorded == 1u &&
           evidence->signed_artifact_receipt_recorded == 1u &&
           evidence->operation_execution_allowed == 1u &&
           evidence->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_ci_promotion_evidence_report(
    const latticra_q_seal_ml_kem_ci_promotion_evidence_t *evidence,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (evidence == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM CI PROMOTION EVIDENCE\n"
        "promotion_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "promotion_scope=%s\n"
        "promotion_state=%s\n"
        "ci_promotion_evidence_present=%u\n"
        "ssdf_secure_build_gate_recorded=%u\n"
        "fips_203_parameter_gate_bound=%u\n"
        "sp_800_227_kem_usage_gate_bound=%u\n"
        "make_quality_security_standards_bound=%u\n"
        "local_wrapper_scripts_recorded=%u\n"
        "qseal_subsystem_scripts_recorded=%u\n"
        "readiness_gate_bound=%u\n"
        "implementation_binding_manifest_required=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "kat_acvp_gate_passing_recorded=%u\n"
        "constant_time_gate_passing_recorded=%u\n"
        "memory_safety_gate_passing_recorded=%u\n"
        "side_channel_gate_passing_recorded=%u\n"
        "negative_test_gate_passing_recorded=%u\n"
        "provider_differential_gate_passing_recorded=%u\n"
        "implementation_binding_ci_result_recorded=%u\n"
        "promotion_workflow_recorded=%u\n"
        "release_claim_gate_recorded=%u\n"
        "signed_artifact_receipt_recorded=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_promotion_items_total=%u\n"
        "required_promotion_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        evidence->promotion_profile,
        evidence->formal_title,
        evidence->standards_basis,
        evidence->promotion_scope,
        evidence->promotion_state,
        evidence->ci_promotion_evidence_present,
        evidence->ssdf_secure_build_gate_recorded,
        evidence->fips_203_parameter_gate_bound,
        evidence->sp_800_227_kem_usage_gate_bound,
        evidence->make_quality_security_standards_bound,
        evidence->local_wrapper_scripts_recorded,
        evidence->qseal_subsystem_scripts_recorded,
        evidence->readiness_gate_bound,
        evidence->implementation_binding_manifest_required,
        evidence->implementation_binding_manifest_bound,
        evidence->kat_acvp_gate_passing_recorded,
        evidence->constant_time_gate_passing_recorded,
        evidence->memory_safety_gate_passing_recorded,
        evidence->side_channel_gate_passing_recorded,
        evidence->negative_test_gate_passing_recorded,
        evidence->provider_differential_gate_passing_recorded,
        evidence->implementation_binding_ci_result_recorded,
        evidence->promotion_workflow_recorded,
        evidence->release_claim_gate_recorded,
        evidence->signed_artifact_receipt_recorded,
        evidence->operation_execution_allowed,
        evidence->production_crypto_claim_allowed,
        evidence->fips_claim_allowed,
        evidence->runtime_authority_granted,
        evidence->required_promotion_items_total,
        evidence->required_promotion_items_satisfied,
        evidence->blocked_reason,
        latticra_q_seal_ml_kem_ci_promotion_evidence_error_label(evidence->error),
        evidence->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
