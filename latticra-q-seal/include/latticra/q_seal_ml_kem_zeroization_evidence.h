#ifndef LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_H
#define LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_zeroization_evidence_error_t;

typedef struct {
    char zeroization_profile[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_LABEL_MAX];
    char module_security_source[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_LABEL_MAX];
    char zeroization_scope[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_LABEL_MAX];
    char zeroization_state[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_STATE_MAX];
    unsigned zeroization_evidence_present;
    unsigned fips_203_source_verified;
    unsigned fips_140_3_zeroization_tracked;
    unsigned secret_state_contract_bound;
    unsigned zeroization_required;
    unsigned secret_material_inventory_required;
    unsigned compiler_barrier_required;
    unsigned zeroization_primitive_selected;
    unsigned zeroization_primitive_implemented;
    unsigned dead_store_elimination_review_recorded;
    unsigned volatile_or_intrinsic_strategy_recorded;
    unsigned stack_heap_register_clear_policy_recorded;
    unsigned error_path_zeroization_recorded;
    unsigned decapsulation_failure_zeroization_recorded;
    unsigned test_harness_memory_scan_recorded;
    unsigned sanitizer_or_valgrind_review_recorded;
    unsigned generated_assembly_review_recorded;
    unsigned cross_platform_review_recorded;
    unsigned formal_review_recorded;
    unsigned implementation_binding_recorded;
    unsigned zeroization_performed;
    unsigned secret_material_handling_allowed;
    unsigned implementation_promotion_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_zeroization_items_total;
    unsigned required_zeroization_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_STATE_MAX];
    latticra_q_seal_ml_kem_zeroization_evidence_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_STATE_MAX];
} latticra_q_seal_ml_kem_zeroization_evidence_t;

const char *latticra_q_seal_ml_kem_zeroization_evidence_error_label(
    latticra_q_seal_ml_kem_zeroization_evidence_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_zeroization_evidence_prepare(
    latticra_q_seal_ml_kem_zeroization_evidence_t *out);
int latticra_q_seal_ml_kem_zeroization_evidence_is_policy_only(
    const latticra_q_seal_ml_kem_zeroization_evidence_t *evidence);
int latticra_q_seal_ml_kem_zeroization_evidence_allows_secret_material_handling(
    const latticra_q_seal_ml_kem_zeroization_evidence_t *evidence);
latticra_q_seal_status_t latticra_q_seal_ml_kem_zeroization_evidence_report(
    const latticra_q_seal_ml_kem_zeroization_evidence_t *evidence,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
