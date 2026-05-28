#include "latticra/seal_key_parsing.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static size_t bounded_string_len(const char *value, size_t max_len, int *terminated) {
    size_t i;

    if (terminated != NULL) {
        *terminated = 0;
    }
    if (value == NULL) {
        return 0u;
    }
    for (i = 0u; i < max_len; ++i) {
        if (value[i] == '\0') {
            if (terminated != NULL) {
                *terminated = 1;
            }
            return i;
        }
    }
    return max_len;
}

static int text_field_valid(const char *value, size_t max_len) {
    int terminated = 0;
    size_t len = bounded_string_len(value, max_len, &terminated);

    return terminated == 1 && len > 0u;
}

static int text_field_terminated(const char *value, size_t max_len) {
    int terminated = 0;

    (void)bounded_string_len(value, max_len, &terminated);
    return terminated == 1;
}

static int bounded_string_is(const char *value, size_t max_len, const char *expected) {
    int terminated = 0;
    size_t value_len;
    size_t expected_len;

    if (value == NULL || expected == NULL) {
        return 0;
    }
    value_len = bounded_string_len(value, max_len, &terminated);
    if (terminated != 1) {
        return 0;
    }
    expected_len = strlen(expected);
    return value_len == expected_len && memcmp(value, expected, value_len) == 0;
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
}

static int key_parsing_error_valid(latticra_seal_key_parsing_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_KEY_PARSING_OK:
    case LATTICRA_SEAL_KEY_PARSING_INVALID_INPUT:
    case LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR:
    case LATTICRA_SEAL_KEY_PARSING_PREDECESSOR_NOT_READY:
    case LATTICRA_SEAL_KEY_PARSING_UNSUPPORTED_FORMAT:
    case LATTICRA_SEAL_KEY_PARSING_OVERSIZED_INPUT:
    case LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES:
    case LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED:
    case LATTICRA_SEAL_KEY_PARSING_KEY_MATERIAL_LOADING_DENIED:
    case LATTICRA_SEAL_KEY_PARSING_TRUST_STORE_DENIED:
    case LATTICRA_SEAL_KEY_PARSING_REVOCATION_DENIED:
    case LATTICRA_SEAL_KEY_PARSING_EFFECT_DENIED:
    case LATTICRA_SEAL_KEY_PARSING_BUFFER_TOO_SMALL:
        return 1;
    default:
        return 0;
    }
}

static int public_key_parsing_error_valid(
    latticra_seal_public_key_parsing_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_INPUT:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_KEY_MATERIAL:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_HANDLING:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_OPERATION:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_INVOCATION:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_HANDOFF:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_AUTHORIZATION:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNATURE_ALGORITHM:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_TRUST_STORE:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT:
        return 1;
    default:
        return 0;
    }
}

static int public_key_parsing_flags_valid(
    const latticra_seal_public_key_parsing_t *predecessor) {
    if (predecessor == NULL) {
        return 0;
    }

    return boolean_flag_valid(predecessor->signing_authorization_ready) &&
           boolean_flag_valid(predecessor->signer_handoff_ready) &&
           boolean_flag_valid(predecessor->signer_invocation_ready) &&
           boolean_flag_valid(predecessor->signing_operation_ready) &&
           boolean_flag_valid(predecessor->key_handling_ready) &&
           boolean_flag_valid(predecessor->key_material_ready) &&
           boolean_flag_valid(predecessor->public_key_parsing_ready) &&
           boolean_flag_valid(predecessor->signature_performed) &&
           boolean_flag_valid(predecessor->verification_performed) &&
           boolean_flag_valid(predecessor->signer_invoked) &&
           boolean_flag_valid(predecessor->public_key_parsed) &&
           boolean_flag_valid(predecessor->key_material_loaded) &&
           boolean_flag_valid(predecessor->private_key_handling) &&
           boolean_flag_valid(predecessor->key_generation_performed) &&
           boolean_flag_valid(predecessor->hardware_key_used) &&
           boolean_flag_valid(predecessor->trust_store_loaded) &&
           boolean_flag_valid(predecessor->revocation_lookup_performed) &&
           boolean_flag_valid(predecessor->handoff_performed) &&
           boolean_flag_valid(predecessor->effect_performed) &&
           boolean_flag_valid(predecessor->runtime_authority_granted) &&
           boolean_flag_valid(predecessor->host_read_performed) &&
           boolean_flag_valid(predecessor->host_write_performed) &&
           boolean_flag_valid(predecessor->network_performed);
}

static int public_key_parsing_state_fields_valid(
    const latticra_seal_public_key_parsing_t *predecessor) {
    if (predecessor == NULL) {
        return 0;
    }

    return text_field_valid(predecessor->signing_authorization_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(predecessor->signer_handoff_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(predecessor->signer_invocation_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(predecessor->signing_operation_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(predecessor->key_handling_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(predecessor->key_material_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(predecessor->public_key_parsing_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(predecessor->status,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX);
}

static int public_key_parsing_strings_valid(
    const latticra_seal_public_key_parsing_t *predecessor) {
    if (predecessor == NULL) {
        return 0;
    }

    return bounded_string_is(predecessor->public_key_parsing_profile,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX,
                             "latticra-seal-public-key-parsing/0.1") &&
           text_field_terminated(predecessor->key_material_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->key_handling_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->signing_operation_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->signer_invocation_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->signer_handoff_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->signing_authorization_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->signature_request_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->envelope_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->report_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->handoff_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->decision_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->gate_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->receipt_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->verify_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(predecessor->message_digest_algorithm,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_ALGORITHM_MAX) &&
           text_field_terminated(predecessor->message_digest_hex,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_DIGEST_MAX) &&
           text_field_terminated(predecessor->public_key_identity_label,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_capability,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_effect,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_handoff,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_report,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_envelope,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_signature,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_signing_authorization,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_signer_handoff,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_signer_invocation,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_signing_operation,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_key_handling,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_key_material,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_public_key_parsing,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(predecessor->requested_scope,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           bounded_string_is(predecessor->mode,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "metadata-only") &&
           public_key_parsing_error_valid(predecessor->error) &&
           public_key_parsing_flags_valid(predecessor) &&
           public_key_parsing_state_fields_valid(predecessor);
}

static int key_parsing_input_format_valid(const char *input_format) {
    return bounded_string_is(input_format,
                             LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                             "ed25519-raw-public-key-32") ||
           bounded_string_is(input_format,
                             LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                             "ed25519-hex-public-key-64") ||
           bounded_string_is(input_format,
                             LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                             "pem-public-key-unsupported") ||
           bounded_string_is(input_format,
                             LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                             "der-public-key-unsupported") ||
           bounded_string_is(input_format,
                             LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                             "private-key-denied") ||
           bounded_string_is(input_format,
                             LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                             "unknown");
}

static int is_hex_byte(unsigned char value) {
    return (value >= (unsigned char)'0' && value <= (unsigned char)'9') ||
           (value >= (unsigned char)'a' && value <= (unsigned char)'f') ||
           (value >= (unsigned char)'A' && value <= (unsigned char)'F');
}

static int contains_ascii_marker(const unsigned char *bytes, size_t len, const char *marker) {
    size_t marker_len;
    size_t i;

    if (bytes == NULL || marker == NULL) {
        return 0;
    }

    marker_len = strlen(marker);
    if (marker_len == 0u || len < marker_len) {
        return 0;
    }

    for (i = 0u; i <= len - marker_len; ++i) {
        if (memcmp(bytes + i, marker, marker_len) == 0) {
            return 1;
        }
    }

    return 0;
}

const char *latticra_seal_key_parsing_error_label(
    latticra_seal_key_parsing_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_KEY_PARSING_OK:
        return "ok";
    case LATTICRA_SEAL_KEY_PARSING_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR:
        return "invalid-predecessor";
    case LATTICRA_SEAL_KEY_PARSING_PREDECESSOR_NOT_READY:
        return "predecessor-not-ready";
    case LATTICRA_SEAL_KEY_PARSING_UNSUPPORTED_FORMAT:
        return "unsupported-format";
    case LATTICRA_SEAL_KEY_PARSING_OVERSIZED_INPUT:
        return "oversized-input";
    case LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES:
        return "invalid-public-key-bytes";
    case LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED:
        return "private-key-denied";
    case LATTICRA_SEAL_KEY_PARSING_KEY_MATERIAL_LOADING_DENIED:
        return "key-material-loading-denied";
    case LATTICRA_SEAL_KEY_PARSING_TRUST_STORE_DENIED:
        return "trust-store-denied";
    case LATTICRA_SEAL_KEY_PARSING_REVOCATION_DENIED:
        return "revocation-denied";
    case LATTICRA_SEAL_KEY_PARSING_EFFECT_DENIED:
        return "effect-denied";
    case LATTICRA_SEAL_KEY_PARSING_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

const char *latticra_seal_key_parsing_format_label(
    latticra_seal_key_parsing_format_t format) {
    switch (format) {
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32:
        return "ed25519-raw-public-key-32";
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64:
        return "ed25519-hex-public-key-64";
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_PEM_PUBLIC_KEY_UNSUPPORTED:
        return "pem-public-key-unsupported";
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_DER_PUBLIC_KEY_UNSUPPORTED:
        return "der-public-key-unsupported";
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_PRIVATE_KEY_DENIED:
        return "private-key-denied";
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_UNKNOWN:
    default:
        return "unknown";
    }
}

static void key_parsing_init(latticra_seal_key_parsing_result_t *key_parsing) {
    memset(key_parsing, 0, sizeof(*key_parsing));
    copy_literal(
        key_parsing->key_parsing_profile,
        sizeof(key_parsing->key_parsing_profile),
        "latticra-seal-key-parsing/0.1");
    copy_literal(
        key_parsing->requested_key_parsing,
        sizeof(key_parsing->requested_key_parsing),
        "public-key-bytes-only");
    copy_literal(
        key_parsing->key_parsing_algorithm,
        sizeof(key_parsing->key_parsing_algorithm),
        "Ed25519-development");
    copy_literal(
        key_parsing->key_parsing_input_format,
        sizeof(key_parsing->key_parsing_input_format),
        "unknown");
    copy_literal(
        key_parsing->key_parsing_state,
        sizeof(key_parsing->key_parsing_state),
        "invalid-input");
    copy_literal(
        key_parsing->blocked_reason,
        sizeof(key_parsing->blocked_reason),
        "invalid-input");
    copy_literal(key_parsing->mode, sizeof(key_parsing->mode), "metadata-only");
    copy_literal(key_parsing->status, sizeof(key_parsing->status), "invalid-input");
    key_parsing->error = LATTICRA_SEAL_KEY_PARSING_INVALID_INPUT;
}

static void copy_predecessor_metadata(
    const latticra_seal_public_key_parsing_t *predecessor,
    latticra_seal_key_parsing_result_t *out) {
    copy_literal(
        out->public_key_parsing_profile,
        sizeof(out->public_key_parsing_profile),
        predecessor->public_key_parsing_profile);
    copy_literal(out->key_material_profile, sizeof(out->key_material_profile), predecessor->key_material_profile);
    copy_literal(
        out->requested_public_key_parsing,
        sizeof(out->requested_public_key_parsing),
        predecessor->requested_public_key_parsing);
    copy_literal(
        out->public_key_parsing_state,
        sizeof(out->public_key_parsing_state),
        predecessor->public_key_parsing_state);
    out->public_key_parsing_ready = predecessor->public_key_parsing_ready;
}

static latticra_status_t key_parsing_fail(
    latticra_seal_key_parsing_result_t *out,
    latticra_seal_key_parsing_error_t error,
    const char *state,
    const char *status,
    const char *blocked_reason) {
    out->error = error;
    copy_literal(out->key_parsing_state, sizeof(out->key_parsing_state), state);
    copy_literal(out->status, sizeof(out->status), status);
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), blocked_reason);
    return LATTICRA_STATUS_OK;
}

static int has_predecessor_host_effects(
    const latticra_seal_public_key_parsing_t *predecessor) {
    return predecessor->signature_performed != 0u ||
           predecessor->verification_performed != 0u ||
           predecessor->signer_invoked != 0u ||
           predecessor->handoff_performed != 0u ||
           predecessor->effect_performed != 0u ||
           predecessor->host_read_performed != 0u ||
           predecessor->host_write_performed != 0u ||
           predecessor->runtime_authority_granted != 0u;
}

latticra_status_t latticra_seal_key_parsing_from_public_key_bytes(
    const latticra_seal_public_key_parsing_t *predecessor,
    const unsigned char *public_key_bytes,
    size_t public_key_len,
    latticra_seal_key_parsing_format_t requested_format,
    latticra_seal_key_parsing_result_t *out) {
    size_t i;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    key_parsing_init(out);
    copy_literal(
        out->key_parsing_input_format,
        sizeof(out->key_parsing_input_format),
        latticra_seal_key_parsing_format_label(requested_format));
    out->key_parsing_input_length = public_key_len;

    if (predecessor == NULL) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR,
            "invalid-predecessor",
            "invalid-predecessor",
            "missing-predecessor");
    }

    if (!public_key_parsing_strings_valid(predecessor)) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR,
            "invalid-predecessor",
            "invalid-predecessor",
            "invalid-predecessor-metadata");
    }

    copy_predecessor_metadata(predecessor, out);

    if (predecessor->error != LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR,
            "invalid-predecessor",
            "invalid-predecessor",
            "predecessor-error");
    }

    if (predecessor->public_key_parsing_ready != 1u ||
        !bounded_string_is(predecessor->public_key_parsing_state,
                           LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                           "public-key-parsing-metadata-only") ||
        !bounded_string_is(predecessor->requested_public_key_parsing,
                           LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                           "metadata-only")) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_PREDECESSOR_NOT_READY,
            "predecessor-not-ready",
            "predecessor-not-ready",
            "predecessor-not-ready");
    }

    if (predecessor->public_key_parsed != 0u) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_EFFECT_DENIED,
            "effect-denied",
            "effect-denied",
            "predecessor-public-key-already-parsed");
    }

    if (predecessor->key_material_loaded != 0u) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_KEY_MATERIAL_LOADING_DENIED,
            "key-material-loading-denied",
            "key-material-loading-denied",
            "key-material-loading-denied");
    }

    if (predecessor->private_key_handling != 0u ||
        predecessor->key_generation_performed != 0u ||
        predecessor->hardware_key_used != 0u) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED,
            "private-key-denied",
            "private-key-denied",
            "private-key-denied");
    }

    if (predecessor->trust_store_loaded != 0u) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_TRUST_STORE_DENIED,
            "trust-store-denied",
            "trust-store-denied",
            "trust-store-denied");
    }

    if (predecessor->revocation_lookup_performed != 0u) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_REVOCATION_DENIED,
            "revocation-denied",
            "revocation-denied",
            "revocation-denied");
    }

    if (predecessor->network_performed != 0u || has_predecessor_host_effects(predecessor)) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_EFFECT_DENIED,
            "effect-denied",
            "effect-denied",
            "predecessor-effect");
    }

    if (public_key_bytes == NULL) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_INVALID_INPUT,
            "invalid-input",
            "invalid-input",
            "missing-public-key-bytes");
    }

    if (public_key_len == 0u) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES,
            "invalid-public-key-bytes",
            "invalid-public-key-bytes",
            "empty-public-key-bytes");
    }

    if (public_key_len > LATTICRA_SEAL_KEY_PARSING_INPUT_MAX) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_OVERSIZED_INPUT,
            "oversized-input",
            "oversized-input",
            "oversized-public-key-bytes");
    }

    if (contains_ascii_marker(public_key_bytes, public_key_len, "PRIVATE KEY")) {
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED,
            "private-key-denied",
            "private-key-denied",
            "private-key-marker-denied");
    }

    switch (requested_format) {
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32:
        if (public_key_len != 32u) {
            return key_parsing_fail(
                out,
                LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES,
                "invalid-public-key-bytes",
                "invalid-public-key-bytes",
                "invalid-ed25519-raw-public-key-length");
        }
        break;
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64:
        if (public_key_len != 64u) {
            return key_parsing_fail(
                out,
                LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES,
                "invalid-public-key-bytes",
                "invalid-public-key-bytes",
                "invalid-ed25519-hex-public-key-length");
        }
        for (i = 0u; i < public_key_len; ++i) {
            if (!is_hex_byte(public_key_bytes[i])) {
                return key_parsing_fail(
                    out,
                    LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES,
                    "invalid-public-key-bytes",
                    "invalid-public-key-bytes",
                    "invalid-ed25519-hex-public-key-byte");
            }
        }
        break;
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_PRIVATE_KEY_DENIED:
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED,
            "private-key-denied",
            "private-key-denied",
            "private-key-denied");
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_PEM_PUBLIC_KEY_UNSUPPORTED:
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_DER_PUBLIC_KEY_UNSUPPORTED:
    case LATTICRA_SEAL_KEY_PARSING_FORMAT_UNKNOWN:
    default:
        return key_parsing_fail(
            out,
            LATTICRA_SEAL_KEY_PARSING_UNSUPPORTED_FORMAT,
            "unsupported-format",
            "unsupported-format",
            "unsupported-key-format");
    }

    out->key_parsing_ready = 1u;
    out->public_key_parsed = 1u;
    out->error = LATTICRA_SEAL_KEY_PARSING_OK;
    copy_literal(
        out->key_parsing_state,
        sizeof(out->key_parsing_state),
        "public-key-parsed-metadata-only");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "none");
    copy_literal(out->status, sizeof(out->status), "key-parsing-metadata");
    return LATTICRA_STATUS_OK;
}

static int key_parsing_flags_valid(
    const latticra_seal_key_parsing_result_t *key_parsing) {
    if (key_parsing == NULL) {
        return 0;
    }

    return boolean_flag_valid(key_parsing->key_parsing_ready) &&
           boolean_flag_valid(key_parsing->public_key_parsing_ready) &&
           boolean_flag_valid(key_parsing->public_key_parsed) &&
           boolean_flag_valid(key_parsing->key_material_loaded) &&
           boolean_flag_valid(key_parsing->private_key_handling) &&
           boolean_flag_valid(key_parsing->key_generation_performed) &&
           boolean_flag_valid(key_parsing->hardware_key_used) &&
           boolean_flag_valid(key_parsing->trust_store_loaded) &&
           boolean_flag_valid(key_parsing->revocation_lookup_performed) &&
           boolean_flag_valid(key_parsing->signature_performed) &&
           boolean_flag_valid(key_parsing->verification_performed) &&
           boolean_flag_valid(key_parsing->signer_invoked) &&
           boolean_flag_valid(key_parsing->handoff_performed) &&
           boolean_flag_valid(key_parsing->effect_performed) &&
           boolean_flag_valid(key_parsing->runtime_authority_granted) &&
           boolean_flag_valid(key_parsing->host_read_performed) &&
           boolean_flag_valid(key_parsing->host_write_performed) &&
           boolean_flag_valid(key_parsing->network_performed);
}

static int key_parsing_effects_clear(
    const latticra_seal_key_parsing_result_t *key_parsing) {
    if (key_parsing == NULL) {
        return 0;
    }

    return key_parsing->key_material_loaded == 0u &&
           key_parsing->private_key_handling == 0u &&
           key_parsing->key_generation_performed == 0u &&
           key_parsing->hardware_key_used == 0u &&
           key_parsing->trust_store_loaded == 0u &&
           key_parsing->revocation_lookup_performed == 0u &&
           key_parsing->signature_performed == 0u &&
           key_parsing->verification_performed == 0u &&
           key_parsing->signer_invoked == 0u &&
           key_parsing->handoff_performed == 0u &&
           key_parsing->effect_performed == 0u &&
           key_parsing->runtime_authority_granted == 0u &&
           key_parsing->host_read_performed == 0u &&
           key_parsing->host_write_performed == 0u &&
           key_parsing->network_performed == 0u;
}

static int key_parsing_ready_state_valid(
    const latticra_seal_key_parsing_result_t *key_parsing) {
    if (key_parsing == NULL || !key_parsing_flags_valid(key_parsing)) {
        return 0;
    }
    if (key_parsing->key_parsing_ready == 0u) {
        return key_parsing->error != LATTICRA_SEAL_KEY_PARSING_OK &&
               key_parsing->public_key_parsed == 0u &&
               text_field_valid(key_parsing->key_parsing_state,
                                LATTICRA_SEAL_KEY_PARSING_STATUS_MAX) &&
               text_field_valid(key_parsing->status,
                                LATTICRA_SEAL_KEY_PARSING_STATUS_MAX) &&
               text_field_valid(key_parsing->blocked_reason,
                                LATTICRA_SEAL_KEY_PARSING_REASON_MAX);
    }

    return key_parsing->error == LATTICRA_SEAL_KEY_PARSING_OK &&
           key_parsing->public_key_parsed == 1u &&
           key_parsing->public_key_parsing_ready == 1u &&
           bounded_string_is(key_parsing->key_parsing_state,
                             LATTICRA_SEAL_KEY_PARSING_STATUS_MAX,
                             "public-key-parsed-metadata-only") &&
           bounded_string_is(key_parsing->status,
                             LATTICRA_SEAL_KEY_PARSING_STATUS_MAX,
                             "key-parsing-metadata") &&
           bounded_string_is(key_parsing->blocked_reason,
                             LATTICRA_SEAL_KEY_PARSING_REASON_MAX,
                             "none") &&
           ((bounded_string_is(key_parsing->key_parsing_input_format,
                               LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                               "ed25519-raw-public-key-32") &&
             key_parsing->key_parsing_input_length == 32u) ||
            (bounded_string_is(key_parsing->key_parsing_input_format,
                               LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX,
                               "ed25519-hex-public-key-64") &&
             key_parsing->key_parsing_input_length == 64u));
}

static int key_parsing_result_valid(
    const latticra_seal_key_parsing_result_t *key_parsing) {
    if (key_parsing == NULL) {
        return 0;
    }

    return key_parsing_effects_clear(key_parsing) &&
           key_parsing_error_valid(key_parsing->error) &&
           key_parsing_flags_valid(key_parsing) &&
           key_parsing_ready_state_valid(key_parsing) &&
           bounded_string_is(key_parsing->key_parsing_profile,
                             LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX,
                             "latticra-seal-key-parsing/0.1") &&
           text_field_terminated(key_parsing->public_key_parsing_profile,
                                 LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(key_parsing->key_material_profile,
                                 LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX) &&
           bounded_string_is(key_parsing->requested_key_parsing,
                             LATTICRA_SEAL_KEY_PARSING_LABEL_MAX,
                             "public-key-bytes-only") &&
           text_field_terminated(key_parsing->requested_public_key_parsing,
                                 LATTICRA_SEAL_KEY_PARSING_LABEL_MAX) &&
           key_parsing_input_format_valid(key_parsing->key_parsing_input_format) &&
           bounded_string_is(key_parsing->key_parsing_algorithm,
                             LATTICRA_SEAL_KEY_PARSING_ALGORITHM_MAX,
                             "Ed25519-development") &&
           text_field_valid(key_parsing->key_parsing_state,
                            LATTICRA_SEAL_KEY_PARSING_STATUS_MAX) &&
           text_field_terminated(key_parsing->public_key_parsing_state,
                                 LATTICRA_SEAL_KEY_PARSING_STATUS_MAX) &&
           text_field_valid(key_parsing->blocked_reason,
                            LATTICRA_SEAL_KEY_PARSING_REASON_MAX) &&
           bounded_string_is(key_parsing->mode,
                             LATTICRA_SEAL_KEY_PARSING_STATUS_MAX,
                             "metadata-only") &&
           text_field_valid(key_parsing->status,
                            LATTICRA_SEAL_KEY_PARSING_STATUS_MAX);
}

int latticra_seal_key_parsing_is_no_effect(
    const latticra_seal_key_parsing_result_t *key_parsing) {
    if (key_parsing == NULL) {
        return 0;
    }

    return key_parsing_result_valid(key_parsing) &&
           key_parsing->error == LATTICRA_SEAL_KEY_PARSING_OK &&
           key_parsing->key_parsing_ready == 1u &&
           key_parsing->public_key_parsed == 1u;
}

latticra_status_t latticra_seal_key_parsing_render(
    const latticra_seal_key_parsing_result_t *key_parsing,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (key_parsing == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!key_parsing_result_valid(key_parsing)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL KEY PARSING\n"
        "key_parsing_profile=%s\n"
        "public_key_parsing_profile=%s\n"
        "key_material_profile=%s\n"
        "requested_key_parsing=%s\n"
        "requested_public_key_parsing=%s\n"
        "key_parsing_input_format=%s\n"
        "key_parsing_input_length=%zu\n"
        "key_parsing_algorithm=%s\n"
        "key_parsing_state=%s\n"
        "key_parsing_ready=%u\n"
        "public_key_parsing_state=%s\n"
        "public_key_parsing_ready=%u\n"
        "public_key_parsed=%u\n"
        "key_material_loaded=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
        "hardware_key_used=%u\n"
        "trust_store_loaded=%u\n"
        "revocation_lookup_performed=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "signer_invoked=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "blocked_reason=%s\n"
        "mode=%s\n"
        "status=%s\n"
        "error=%s\n",
        key_parsing->key_parsing_profile,
        key_parsing->public_key_parsing_profile,
        key_parsing->key_material_profile,
        key_parsing->requested_key_parsing,
        key_parsing->requested_public_key_parsing,
        key_parsing->key_parsing_input_format,
        key_parsing->key_parsing_input_length,
        key_parsing->key_parsing_algorithm,
        key_parsing->key_parsing_state,
        key_parsing->key_parsing_ready,
        key_parsing->public_key_parsing_state,
        key_parsing->public_key_parsing_ready,
        key_parsing->public_key_parsed,
        key_parsing->key_material_loaded,
        key_parsing->private_key_handling,
        key_parsing->key_generation_performed,
        key_parsing->hardware_key_used,
        key_parsing->trust_store_loaded,
        key_parsing->revocation_lookup_performed,
        key_parsing->signature_performed,
        key_parsing->verification_performed,
        key_parsing->signer_invoked,
        key_parsing->handoff_performed,
        key_parsing->effect_performed,
        key_parsing->runtime_authority_granted,
        key_parsing->host_read_performed,
        key_parsing->host_write_performed,
        key_parsing->network_performed,
        key_parsing->blocked_reason,
        key_parsing->mode,
        key_parsing->status,
        latticra_seal_key_parsing_error_label(key_parsing->error));

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
