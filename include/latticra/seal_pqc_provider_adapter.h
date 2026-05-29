#ifndef LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_H
#define LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_H

#include "latticra/seal_pqc_integration_frame.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_PROFILE_MAX 64u
#define LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_LABEL_MAX 128u
#define LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_STATE_MAX 96u
#define LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_REPORT_MAX 8192u

typedef enum {
    LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_OK = 0,
    LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_INVALID_INPUT = 1,
    LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_MISSING_FRAME = 2,
    LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_INVALID_FRAME = 3,
    LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_PROVIDER_NOT_ALLOWED = 4,
    LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_APPLE_BOUNDARY_VIOLATION = 5,
    LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_BUFFER_TOO_SMALL = 6
} latticra_seal_pqc_provider_adapter_error_t;

typedef struct {
    char adapter_profile[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_PROFILE_MAX];
    char integration_profile[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_PROFILE_MAX];
    char clean_room_profile[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_PROFILE_MAX];
    char provider_name[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_LABEL_MAX];
    char provider_role[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_LABEL_MAX];
    char provider_license[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_LABEL_MAX];
    char source_boundary[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_LABEL_MAX];
    char adapter_state[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_STATE_MAX];
    char blocked_reason[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_STATE_MAX];
    unsigned integration_frame_present;
    unsigned clean_room_design_required;
    unsigned nist_fips_203_ml_kem_required;
    unsigned nist_fips_204_ml_dsa_required;
    unsigned nist_fips_205_slh_dsa_backup_tracked;
    unsigned ml_kem_512_planned;
    unsigned ml_kem_768_planned;
    unsigned ml_kem_1024_planned;
    unsigned ml_dsa_44_planned;
    unsigned ml_dsa_65_planned;
    unsigned ml_dsa_87_planned;
    unsigned liboqs_comparison_provider_allowed;
    unsigned liboqs_linked;
    unsigned liboqs_runtime_used;
    unsigned apple_corecrypto_reference_allowed;
    unsigned apple_corecrypto_code_copied;
    unsigned apple_corecrypto_proof_artifacts_copied;
    unsigned apple_corecrypto_symbols_reused;
    unsigned permissive_reference_code_required;
    unsigned third_party_notice_review_required;
    unsigned compile_time_gate_required;
    unsigned default_build_enabled;
    unsigned known_answer_tests_required;
    unsigned differential_tests_allowed;
    unsigned differential_tests_performed;
    unsigned fuzzing_required;
    unsigned constant_time_review_required;
    unsigned side_channel_review_required;
    unsigned memory_safe_implementation_preferred;
    unsigned c_abi_boundary_required;
    unsigned cryptographic_module_boundary_required;
    unsigned fips_140_3_claim_gate_required;
    unsigned cavp_acvp_vector_review_required;
    unsigned key_generation_performed;
    unsigned key_storage_performed;
    unsigned encapsulation_performed;
    unsigned decapsulation_performed;
    unsigned signing_performed;
    unsigned verification_performed;
    unsigned encryption_performed;
    unsigned network_lookup_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned post_quantum_migration_claim_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_pqc_provider_adapter_error_t error;
    char status[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_STATE_MAX];
} latticra_seal_pqc_provider_adapter_t;

const char *latticra_seal_pqc_provider_adapter_error_label(
    latticra_seal_pqc_provider_adapter_error_t error);
latticra_status_t latticra_seal_pqc_provider_adapter_from_frame(
    const latticra_seal_pqc_integration_frame_t *frame,
    latticra_seal_pqc_provider_adapter_t *out);
int latticra_seal_pqc_provider_adapter_is_clean_room(
    const latticra_seal_pqc_provider_adapter_t *adapter);
int latticra_seal_pqc_provider_adapter_is_authority_neutral(
    const latticra_seal_pqc_provider_adapter_t *adapter);
latticra_status_t latticra_seal_pqc_provider_adapter_report(
    const latticra_seal_pqc_provider_adapter_t *adapter,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
