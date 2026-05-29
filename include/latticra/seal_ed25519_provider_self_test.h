#ifndef LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_H
#define LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROFILE_MAX 96u
#define LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_LABEL_MAX 128u
#define LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_STATE_MAX 128u
#define LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_REPORT_MAX 4096u
#define LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PUBLIC_KEY_BYTES 32u
#define LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_SIGNATURE_BYTES 64u

typedef enum {
    LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_OK = 0,
    LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE = 1,
    LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_FAILURE = 2
} latticra_seal_ed25519_provider_self_test_error_t;

typedef struct {
    char self_test_profile[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROFILE_MAX];
    char formal_title[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_LABEL_MAX];
    char provider_name[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_LABEL_MAX];
    char signature_algorithm[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_LABEL_MAX];
    char standards_source[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_LABEL_MAX];
    char operation_scope[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_LABEL_MAX];
    unsigned provider_linked;
    unsigned provider_runtime_used;
    unsigned ed25519_key_generation_performed;
    unsigned ed25519_public_key_export_performed;
    unsigned ed25519_public_key_only_verification_performed;
    unsigned ed25519_signature_generation_performed;
    unsigned ed25519_signature_verification_performed;
    unsigned ed25519_signature_valid;
    unsigned ed25519_tampered_message_rejected;
    unsigned ed25519_tampered_signature_rejected;
    unsigned ed25519_public_key_bytes;
    unsigned ed25519_signature_bytes;
    unsigned one_shot_sign_api_used;
    unsigned one_shot_verify_api_used;
    unsigned message_prehashed_before_signing;
    unsigned ed25519_private_key_exported;
    unsigned ed25519_private_key_output_emitted;
    unsigned ed25519_public_key_output_emitted;
    unsigned ed25519_signature_output_emitted;
    unsigned public_key_buffer_zeroized;
    unsigned signature_buffer_zeroized;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned signing_authority_granted;
    unsigned key_storage_allowed;
    unsigned network_lookup_allowed;
    unsigned runtime_authority_granted;
    char operation_state[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_STATE_MAX];
    char blocked_reason[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_STATE_MAX];
    latticra_seal_ed25519_provider_self_test_error_t error;
    char status[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_STATE_MAX];
} latticra_seal_ed25519_provider_self_test_t;

const char *latticra_seal_ed25519_provider_self_test_error_label(
    latticra_seal_ed25519_provider_self_test_error_t error);
latticra_status_t latticra_seal_ed25519_provider_self_test_run(
    latticra_seal_ed25519_provider_self_test_t *out);
int latticra_seal_ed25519_provider_self_test_is_authority_neutral(
    const latticra_seal_ed25519_provider_self_test_t *self_test);
latticra_status_t latticra_seal_ed25519_provider_self_test_report(
    const latticra_seal_ed25519_provider_self_test_t *self_test,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
