#ifndef LATTICRA_SEAL_PQC_INTEGRATION_FRAME_H
#define LATTICRA_SEAL_PQC_INTEGRATION_FRAME_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_PQC_FRAME_PROFILE_MAX 64u
#define LATTICRA_SEAL_PQC_FRAME_LABEL_MAX 128u
#define LATTICRA_SEAL_PQC_FRAME_STATE_MAX 96u
#define LATTICRA_SEAL_PQC_FRAME_REPORT_MAX 8192u

typedef enum {
    LATTICRA_SEAL_PQC_INTEGRATION_FRAME_OK = 0,
    LATTICRA_SEAL_PQC_INTEGRATION_FRAME_INVALID_INPUT = 1,
    LATTICRA_SEAL_PQC_INTEGRATION_FRAME_BUFFER_TOO_SMALL = 2
} latticra_seal_pqc_integration_frame_error_t;

typedef struct {
    char pqc_integration_profile[LATTICRA_SEAL_PQC_FRAME_PROFILE_MAX];
    char research_date[LATTICRA_SEAL_PQC_FRAME_LABEL_MAX];
    char apple_corecrypto_source[LATTICRA_SEAL_PQC_FRAME_LABEL_MAX];
    char apple_corecrypto_license[LATTICRA_SEAL_PQC_FRAME_LABEL_MAX];
    char candidate_provider[LATTICRA_SEAL_PQC_FRAME_LABEL_MAX];
    char candidate_provider_source[LATTICRA_SEAL_PQC_FRAME_LABEL_MAX];
    char candidate_provider_license[LATTICRA_SEAL_PQC_FRAME_LABEL_MAX];
    unsigned apple_corecrypto_ml_kem_published;
    unsigned apple_corecrypto_ml_dsa_published;
    unsigned apple_corecrypto_formal_verification_published;
    unsigned apple_corecrypto_reference_allowed;
    unsigned apple_corecrypto_embedding_allowed;
    unsigned apple_corecrypto_redistribution_allowed;
    unsigned nist_fips_203_ml_kem_tracked;
    unsigned nist_fips_204_ml_dsa_tracked;
    unsigned nist_fips_205_slh_dsa_backup_tracked;
    unsigned ml_kem_key_establishment_planned;
    unsigned ml_dsa_signature_planned;
    unsigned hybrid_classical_pqc_transition_required;
    unsigned liboqs_candidate_tracked;
    unsigned liboqs_mit_license_tracked;
    unsigned liboqs_prototype_only_warning_tracked;
    unsigned candidate_provider_production_use_allowed;
    unsigned cryptographic_module_boundary_required;
    unsigned algorithm_parameter_inventory_required;
    unsigned known_answer_tests_required;
    unsigned cavp_acvp_vector_review_required;
    unsigned constant_time_review_required;
    unsigned side_channel_review_required;
    unsigned fips_140_3_claim_gate_required;
    unsigned sp_800_57_key_management_required;
    unsigned source_notice_review_required;
    unsigned third_party_code_vendored;
    unsigned cryptographic_behavior_changed;
    unsigned post_quantum_migration_claim_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned key_generation_allowed;
    unsigned key_storage_allowed;
    unsigned encryption_performed;
    unsigned signing_performed;
    unsigned network_lookup_allowed;
    unsigned runtime_authority_granted;
    char frame_state[LATTICRA_SEAL_PQC_FRAME_STATE_MAX];
    char blocked_reason[LATTICRA_SEAL_PQC_FRAME_STATE_MAX];
    latticra_seal_pqc_integration_frame_error_t error;
    char status[LATTICRA_SEAL_PQC_FRAME_STATE_MAX];
} latticra_seal_pqc_integration_frame_t;

const char *latticra_seal_pqc_integration_frame_error_label(
    latticra_seal_pqc_integration_frame_error_t error);
latticra_status_t latticra_seal_pqc_integration_frame_prepare(
    latticra_seal_pqc_integration_frame_t *out);
int latticra_seal_pqc_integration_frame_is_authority_neutral(
    const latticra_seal_pqc_integration_frame_t *frame);
latticra_status_t latticra_seal_pqc_integration_frame_report(
    const latticra_seal_pqc_integration_frame_t *frame,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
