#ifndef LATTICRA_Q_SEAL_H
#define LATTICRA_Q_SEAL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_PROFILE_MAX 64u
#define LATTICRA_Q_SEAL_LABEL_MAX 128u
#define LATTICRA_Q_SEAL_STATE_MAX 96u
#define LATTICRA_Q_SEAL_REPORT_MAX 4096u

typedef enum {
    LATTICRA_Q_SEAL_STATUS_OK = 0,
    LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT = 1,
    LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL = 2,
    LATTICRA_Q_SEAL_STATUS_INVALID_ARGUMENT = 3
} latticra_q_seal_status_t;

typedef enum {
    LATTICRA_Q_SEAL_FOUNDATION_OK = 0,
    LATTICRA_Q_SEAL_FOUNDATION_INVALID_INPUT = 1
} latticra_q_seal_foundation_error_t;

typedef struct {
    char formal_title[LATTICRA_Q_SEAL_LABEL_MAX];
    char subsystem_directory[LATTICRA_Q_SEAL_LABEL_MAX];
    char q_seal_profile[LATTICRA_Q_SEAL_PROFILE_MAX];
    char clean_room_profile[LATTICRA_Q_SEAL_PROFILE_MAX];
    char source_boundary[LATTICRA_Q_SEAL_LABEL_MAX];
    char implementation_lane[LATTICRA_Q_SEAL_LABEL_MAX];
    unsigned latticra_q_seal_present;
    unsigned nist_fips_203_ml_kem_tracked;
    unsigned nist_fips_204_ml_dsa_tracked;
    unsigned nist_fips_205_slh_dsa_backup_tracked;
    unsigned ml_kem_work_packet_next;
    unsigned ml_dsa_work_packet_planned;
    unsigned liboqs_comparison_provider_allowed;
    unsigned apple_corecrypto_reference_allowed;
    unsigned apple_corecrypto_code_copied;
    unsigned apple_corecrypto_proof_artifacts_copied;
    unsigned provider_linked;
    unsigned provider_runtime_used;
    unsigned key_generation_performed;
    unsigned key_storage_performed;
    unsigned encapsulation_performed;
    unsigned decapsulation_performed;
    unsigned signing_performed;
    unsigned verification_performed;
    unsigned encryption_performed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned post_quantum_migration_claim_allowed;
    unsigned runtime_authority_granted;
    char foundation_state[LATTICRA_Q_SEAL_STATE_MAX];
    char blocked_reason[LATTICRA_Q_SEAL_STATE_MAX];
    latticra_q_seal_foundation_error_t error;
    char status[LATTICRA_Q_SEAL_STATE_MAX];
} latticra_q_seal_foundation_t;

const char *latticra_q_seal_foundation_error_label(
    latticra_q_seal_foundation_error_t error);
latticra_q_seal_status_t latticra_q_seal_foundation_prepare(
    latticra_q_seal_foundation_t *out);
int latticra_q_seal_foundation_is_clean_room(
    const latticra_q_seal_foundation_t *foundation);
int latticra_q_seal_foundation_is_authority_neutral(
    const latticra_q_seal_foundation_t *foundation);
latticra_q_seal_status_t latticra_q_seal_foundation_report(
    const latticra_q_seal_foundation_t *foundation,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
