#ifndef LATTICRA_SEAL_KEY_PARSING_H
#define LATTICRA_SEAL_KEY_PARSING_H

#include "latticra/seal_public_key_parsing.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX 64u
#define LATTICRA_SEAL_KEY_PARSING_LABEL_MAX 128u
#define LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX 64u
#define LATTICRA_SEAL_KEY_PARSING_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_KEY_PARSING_REASON_MAX 128u
#define LATTICRA_SEAL_KEY_PARSING_STATUS_MAX 64u
#define LATTICRA_SEAL_KEY_PARSING_INPUT_MAX 4096u
#define LATTICRA_SEAL_KEY_PARSING_REPORT_MAX 8192u

typedef enum {
    LATTICRA_SEAL_KEY_PARSING_OK = 0,
    LATTICRA_SEAL_KEY_PARSING_INVALID_INPUT = 1,
    LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR = 2,
    LATTICRA_SEAL_KEY_PARSING_PREDECESSOR_NOT_READY = 3,
    LATTICRA_SEAL_KEY_PARSING_UNSUPPORTED_FORMAT = 4,
    LATTICRA_SEAL_KEY_PARSING_OVERSIZED_INPUT = 5,
    LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES = 6,
    LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED = 7,
    LATTICRA_SEAL_KEY_PARSING_KEY_MATERIAL_LOADING_DENIED = 8,
    LATTICRA_SEAL_KEY_PARSING_TRUST_STORE_DENIED = 9,
    LATTICRA_SEAL_KEY_PARSING_REVOCATION_DENIED = 10,
    LATTICRA_SEAL_KEY_PARSING_EFFECT_DENIED = 11,
    LATTICRA_SEAL_KEY_PARSING_BUFFER_TOO_SMALL = 12
} latticra_seal_key_parsing_error_t;

typedef enum {
    LATTICRA_SEAL_KEY_PARSING_FORMAT_UNKNOWN = 0,
    LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32 = 1,
    LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64 = 2,
    LATTICRA_SEAL_KEY_PARSING_FORMAT_PEM_PUBLIC_KEY_UNSUPPORTED = 3,
    LATTICRA_SEAL_KEY_PARSING_FORMAT_DER_PUBLIC_KEY_UNSUPPORTED = 4,
    LATTICRA_SEAL_KEY_PARSING_FORMAT_PRIVATE_KEY_DENIED = 5
} latticra_seal_key_parsing_format_t;

typedef struct {
    const unsigned char *bytes;
    size_t length;
    latticra_seal_key_parsing_format_t format;
} latticra_seal_key_parsing_input_t;

typedef struct {
    char key_parsing_profile[LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX];
    char public_key_parsing_profile[LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX];
    char key_material_profile[LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX];
    char requested_key_parsing[LATTICRA_SEAL_KEY_PARSING_LABEL_MAX];
    char requested_public_key_parsing[LATTICRA_SEAL_KEY_PARSING_LABEL_MAX];
    char key_parsing_input_format[LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX];
    size_t key_parsing_input_length;
    char key_parsing_algorithm[LATTICRA_SEAL_KEY_PARSING_ALGORITHM_MAX];
    char key_parsing_state[LATTICRA_SEAL_KEY_PARSING_STATUS_MAX];
    unsigned key_parsing_ready;
    char public_key_parsing_state[LATTICRA_SEAL_KEY_PARSING_STATUS_MAX];
    unsigned public_key_parsing_ready;
    unsigned public_key_parsed;
    unsigned key_material_loaded;
    unsigned private_key_handling;
    unsigned key_generation_performed;
    unsigned hardware_key_used;
    unsigned trust_store_loaded;
    unsigned revocation_lookup_performed;
    unsigned signature_performed;
    unsigned verification_performed;
    unsigned signer_invoked;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char blocked_reason[LATTICRA_SEAL_KEY_PARSING_REASON_MAX];
    char mode[LATTICRA_SEAL_KEY_PARSING_STATUS_MAX];
    char status[LATTICRA_SEAL_KEY_PARSING_STATUS_MAX];
    latticra_seal_key_parsing_error_t error;
} latticra_seal_key_parsing_result_t;

const char *latticra_seal_key_parsing_error_label(
    latticra_seal_key_parsing_error_t error);
const char *latticra_seal_key_parsing_format_label(
    latticra_seal_key_parsing_format_t format);
latticra_status_t latticra_seal_key_parsing_from_public_key_bytes(
    const latticra_seal_public_key_parsing_t *predecessor,
    const unsigned char *public_key_bytes,
    size_t public_key_len,
    latticra_seal_key_parsing_format_t requested_format,
    latticra_seal_key_parsing_result_t *out);
int latticra_seal_key_parsing_is_no_effect(
    const latticra_seal_key_parsing_result_t *key_parsing);
latticra_status_t latticra_seal_key_parsing_render(
    const latticra_seal_key_parsing_result_t *key_parsing,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
