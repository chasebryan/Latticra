#include "latticra/seal_public_key_parsing.h"

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
    size_t i;

    if (terminated != 1 || len == 0u) {
        return 0;
    }
    for (i = 0u; i < len; ++i) {
        if (value[i] == '\n' || value[i] == '\r') {
            return 0;
        }
    }
    return 1;
}

static int text_field_terminated(const char *value, size_t max_len) {
    int terminated = 0;
    size_t len = bounded_string_len(value, max_len, &terminated);
    size_t i;

    if (terminated != 1) {
        return 0;
    }
    for (i = 0u; i < len; ++i) {
        if (value[i] == '\n' || value[i] == '\r') {
            return 0;
        }
    }
    return 1;
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

static int is_allowed_signature(const char *signature) {
    return bounded_string_is(signature,
                             LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX,
                             "Ed25519-development");
}

static int is_allowed_metadata_label(const char *label) {
    return bounded_string_is(label,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
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

static int key_material_error_valid(latticra_seal_key_material_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_KEY_MATERIAL_OK:
    case LATTICRA_SEAL_KEY_MATERIAL_INVALID_INPUT:
    case LATTICRA_SEAL_KEY_MATERIAL_INVALID_KEY_HANDLING:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_HANDLING:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_OPERATION:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_INVOCATION:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_HANDOFF:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_AUTHORIZATION:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNATURE_ALGORITHM:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_TRUST_STORE:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_NETWORK_EFFECT:
        return 1;
    default:
        return 0;
    }
}

static int key_material_flags_valid(
    const latticra_seal_key_material_t *key_material) {
    if (key_material == NULL) {
        return 0;
    }

    return boolean_flag_valid(key_material->signing_authorization_ready) &&
           boolean_flag_valid(key_material->signer_handoff_ready) &&
           boolean_flag_valid(key_material->signer_invocation_ready) &&
           boolean_flag_valid(key_material->signing_operation_ready) &&
           boolean_flag_valid(key_material->key_handling_ready) &&
           boolean_flag_valid(key_material->key_material_ready) &&
           boolean_flag_valid(key_material->signature_performed) &&
           boolean_flag_valid(key_material->verification_performed) &&
           boolean_flag_valid(key_material->signer_invoked) &&
           boolean_flag_valid(key_material->public_key_parsed) &&
           boolean_flag_valid(key_material->key_material_loaded) &&
           boolean_flag_valid(key_material->private_key_handling) &&
           boolean_flag_valid(key_material->key_generation_performed) &&
           boolean_flag_valid(key_material->hardware_key_used) &&
           boolean_flag_valid(key_material->trust_store_loaded) &&
           boolean_flag_valid(key_material->revocation_lookup_performed) &&
           boolean_flag_valid(key_material->handoff_performed) &&
           boolean_flag_valid(key_material->effect_performed) &&
           boolean_flag_valid(key_material->runtime_authority_granted) &&
           boolean_flag_valid(key_material->host_read_performed) &&
           boolean_flag_valid(key_material->host_write_performed) &&
           boolean_flag_valid(key_material->network_performed);
}

static int key_material_state_fields_valid(
    const latticra_seal_key_material_t *key_material) {
    if (key_material == NULL) {
        return 0;
    }

    return text_field_valid(key_material->signing_authorization_state,
                            LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX) &&
           text_field_valid(key_material->signer_handoff_state,
                            LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX) &&
           text_field_valid(key_material->signer_invocation_state,
                            LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX) &&
           text_field_valid(key_material->signing_operation_state,
                            LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX) &&
           text_field_valid(key_material->key_handling_state,
                            LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX) &&
           text_field_valid(key_material->key_material_state,
                            LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX) &&
           text_field_valid(key_material->status,
                            LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX);
}

static int key_material_strings_valid(
    const latticra_seal_key_material_t *key_material) {
    if (key_material == NULL) {
        return 0;
    }

    return bounded_string_is(key_material->key_material_profile,
                             LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX,
                             "latticra-seal-key-material/0.1") &&
           text_field_terminated(key_material->key_handling_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->signing_operation_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->signer_invocation_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->signer_handoff_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->signing_authorization_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->signature_request_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->envelope_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->report_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->handoff_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->decision_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->gate_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->receipt_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->verify_profile,
                                 LATTICRA_SEAL_KEY_MATERIAL_PROFILE_MAX) &&
           text_field_terminated(key_material->message_digest_algorithm,
                                 LATTICRA_SEAL_KEY_MATERIAL_ALGORITHM_MAX) &&
           text_field_terminated(key_material->message_digest_hex,
                                 LATTICRA_SEAL_KEY_MATERIAL_DIGEST_MAX) &&
           text_field_terminated(key_material->public_key_identity_label,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_capability,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_effect,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_handoff,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_report,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_envelope,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_signature,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_signing_authorization,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_signer_handoff,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_signer_invocation,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_signing_operation,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_key_handling,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_key_material,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           text_field_terminated(key_material->requested_scope,
                                 LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) &&
           bounded_string_is(key_material->mode,
                             LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX,
                             "metadata-only") &&
           key_material_error_valid(key_material->error) &&
           key_material_flags_valid(key_material) &&
           key_material_state_fields_valid(key_material);
}

static int requested_public_key_parsing_present(
    const char *requested_public_key_parsing) {
    return requested_public_key_parsing != NULL &&
           requested_public_key_parsing[0] != '\0';
}

static const char *safe_requested_public_key_parsing_for_copy(
    const char *requested_public_key_parsing) {
    if (!requested_public_key_parsing_present(requested_public_key_parsing)) {
        return NULL;
    }
    if (!text_field_valid(requested_public_key_parsing,
                          LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX)) {
        return "invalid-public-key-parsing";
    }
    return requested_public_key_parsing;
}

const char *latticra_seal_public_key_parsing_error_label(
    latticra_seal_public_key_parsing_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK:
        return "ok";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_KEY_MATERIAL:
        return "invalid-key-material";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL:
        return "denied-key-material";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_HANDLING:
        return "denied-key-handling";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_OPERATION:
        return "denied-signing-operation";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_INVOCATION:
        return "denied-signer-invocation";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_HANDOFF:
        return "denied-signer-handoff";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_AUTHORIZATION:
        return "denied-signing-authorization";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING:
        return "denied-public-key-parsing";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_TRUST_STORE:
        return "denied-trust-store";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    default:
        return "unknown";
    }
}

static void public_key_parsing_init(
    latticra_seal_public_key_parsing_t *public_key_parsing) {
    memset(public_key_parsing, 0, sizeof(*public_key_parsing));
    copy_literal(
        public_key_parsing->public_key_parsing_profile,
        sizeof(public_key_parsing->public_key_parsing_profile),
        "latticra-seal-public-key-parsing/0.1");
    copy_literal(
        public_key_parsing->public_key_parsing_state,
        sizeof(public_key_parsing->public_key_parsing_state),
        "denied-key-material");
    copy_literal(
        public_key_parsing->mode,
        sizeof(public_key_parsing->mode),
        "metadata-only");
    public_key_parsing->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_INPUT;
    copy_literal(
        public_key_parsing->status,
        sizeof(public_key_parsing->status),
        "invalid-input");
}

static void copy_key_material_metadata(
    const latticra_seal_key_material_t *key_material,
    const char *requested_public_key_parsing,
    latticra_seal_public_key_parsing_t *out) {
    copy_literal(out->key_material_profile, sizeof(out->key_material_profile), key_material->key_material_profile);
    copy_literal(out->key_handling_profile, sizeof(out->key_handling_profile), key_material->key_handling_profile);
    copy_literal(out->signing_operation_profile, sizeof(out->signing_operation_profile), key_material->signing_operation_profile);
    copy_literal(out->signer_invocation_profile, sizeof(out->signer_invocation_profile), key_material->signer_invocation_profile);
    copy_literal(out->signer_handoff_profile, sizeof(out->signer_handoff_profile), key_material->signer_handoff_profile);
    copy_literal(
        out->signing_authorization_profile,
        sizeof(out->signing_authorization_profile),
        key_material->signing_authorization_profile);
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), key_material->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), key_material->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), key_material->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), key_material->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), key_material->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), key_material->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), key_material->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), key_material->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), key_material->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), key_material->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), key_material->public_key_identity_label);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), key_material->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), key_material->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), key_material->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), key_material->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), key_material->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), key_material->requested_signature);
    copy_literal(
        out->requested_signing_authorization,
        sizeof(out->requested_signing_authorization),
        key_material->requested_signing_authorization);
    copy_literal(out->requested_signer_handoff, sizeof(out->requested_signer_handoff), key_material->requested_signer_handoff);
    copy_literal(out->requested_signer_invocation, sizeof(out->requested_signer_invocation), key_material->requested_signer_invocation);
    copy_literal(
        out->requested_signing_operation,
        sizeof(out->requested_signing_operation),
        key_material->requested_signing_operation);
    copy_literal(out->requested_key_handling, sizeof(out->requested_key_handling), key_material->requested_key_handling);
    copy_literal(out->requested_key_material, sizeof(out->requested_key_material), key_material->requested_key_material);
    copy_literal(
        out->requested_public_key_parsing,
        sizeof(out->requested_public_key_parsing),
        safe_requested_public_key_parsing_for_copy(requested_public_key_parsing));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), key_material->requested_scope);
    copy_literal(
        out->signing_authorization_state,
        sizeof(out->signing_authorization_state),
        key_material->signing_authorization_state);
    out->signing_authorization_ready = key_material->signing_authorization_ready;
    copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), key_material->signer_handoff_state);
    out->signer_handoff_ready = key_material->signer_handoff_ready;
    copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), key_material->signer_invocation_state);
    out->signer_invocation_ready = key_material->signer_invocation_ready;
    copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), key_material->signing_operation_state);
    out->signing_operation_ready = key_material->signing_operation_ready;
    copy_literal(out->key_handling_state, sizeof(out->key_handling_state), key_material->key_handling_state);
    out->key_handling_ready = key_material->key_handling_ready;
    copy_literal(out->key_material_state, sizeof(out->key_material_state), key_material->key_material_state);
    out->key_material_ready = key_material->key_material_ready;
    out->signature_performed = key_material->signature_performed;
    out->verification_performed = key_material->verification_performed;
    out->signer_invoked = key_material->signer_invoked;
    out->public_key_parsed = key_material->public_key_parsed;
    out->key_material_loaded = key_material->key_material_loaded;
    out->private_key_handling = key_material->private_key_handling;
    out->key_generation_performed = key_material->key_generation_performed;
    out->hardware_key_used = key_material->hardware_key_used;
    out->trust_store_loaded = key_material->trust_store_loaded;
    out->revocation_lookup_performed = key_material->revocation_lookup_performed;
    out->handoff_performed = key_material->handoff_performed;
    out->effect_performed = key_material->effect_performed;
    out->runtime_authority_granted = key_material->runtime_authority_granted;
    out->host_read_performed = key_material->host_read_performed;
    out->host_write_performed = key_material->host_write_performed;
    out->network_performed = key_material->network_performed;
}

static int request_is_public_key_parsing(const char *requested_public_key_parsing) {
    return bounded_string_is(requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "parse-public-key") ||
           bounded_string_is(requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "parse-ed25519-public-key") ||
           bounded_string_is(requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "public-key-parsing");
}

static int request_is_key_material_loading(const char *requested_public_key_parsing) {
    return bounded_string_is(requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "load-key-material");
}

static int request_is_private_key(const char *requested_public_key_parsing) {
    return bounded_string_is(requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "handle-private-key") ||
           bounded_string_is(requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "generate-key") ||
           bounded_string_is(requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "use-hardware-key");
}

latticra_status_t latticra_seal_public_key_parsing_from_key_material(
    const latticra_seal_key_material_t *key_material,
    const char *requested_public_key_parsing,
    latticra_seal_public_key_parsing_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    public_key_parsing_init(out);

    if (key_material == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!key_material_strings_valid(key_material)) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_KEY_MATERIAL;
        copy_literal(
            out->public_key_parsing_state,
            sizeof(out->public_key_parsing_state),
            "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "invalid-key-material");
        return LATTICRA_STATUS_OK;
    }

    copy_key_material_metadata(key_material, requested_public_key_parsing, out);

    if (key_material->error != LATTICRA_SEAL_KEY_MATERIAL_OK) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_KEY_MATERIAL;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "invalid-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->key_material_ready != 1u ||
        !bounded_string_is(key_material->key_material_state,
                           LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX,
                           "key-material-metadata-only") ||
        !bounded_string_is(key_material->requested_key_material,
                           LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "denied-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->key_handling_ready != 1u ||
        !bounded_string_is(key_material->key_handling_state,
                           LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX,
                           "key-handling-metadata-only") ||
        !bounded_string_is(key_material->requested_key_handling,
                           LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_HANDLING;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-key-handling");
        copy_literal(out->status, sizeof(out->status), "denied-key-handling");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->signing_operation_ready != 1u ||
        !bounded_string_is(key_material->signing_operation_state,
                           LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX,
                           "operation-metadata-only") ||
        !bounded_string_is(key_material->requested_signing_operation,
                           LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_OPERATION;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-signing-operation");
        copy_literal(out->status, sizeof(out->status), "denied-signing-operation");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->signer_invocation_ready != 1u ||
        !bounded_string_is(key_material->signer_invocation_state,
                           LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX,
                           "invocation-metadata-only") ||
        !bounded_string_is(key_material->requested_signer_invocation,
                           LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_INVOCATION;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "denied-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->signer_handoff_ready != 1u ||
        !bounded_string_is(key_material->signer_handoff_state,
                           LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX,
                           "handoff-metadata-only") ||
        !bounded_string_is(key_material->requested_signer_handoff,
                           LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_HANDOFF;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->signing_authorization_ready != 1u ||
        !bounded_string_is(key_material->signing_authorization_state,
                           LATTICRA_SEAL_KEY_MATERIAL_STATE_MAX,
                           "authorized-metadata-only") ||
        !bounded_string_is(key_material->requested_signing_authorization,
                           LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_AUTHORIZATION;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "denied-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(key_material->requested_signature,
                          LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX) ||
        !is_allowed_signature(key_material->requested_signature)) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_public_key_parsing_present(requested_public_key_parsing)) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-public-key-parsing");
        copy_literal(out->status, sizeof(out->status), "missing-requested-public-key-parsing");
        return LATTICRA_STATUS_OK;
    }

    if (request_is_public_key_parsing(requested_public_key_parsing)) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-public-key-parsing");
        copy_literal(out->status, sizeof(out->status), "denied-public-key-parsing");
        return LATTICRA_STATUS_OK;
    }

    if (request_is_key_material_loading(requested_public_key_parsing)) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "denied-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (request_is_private_key(requested_public_key_parsing)) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (bounded_string_is(requested_public_key_parsing,
                          LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                          "load-trust-store")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_TRUST_STORE;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-trust-store");
        copy_literal(out->status, sizeof(out->status), "denied-trust-store");
        return LATTICRA_STATUS_OK;
    }

    if (bounded_string_is(requested_public_key_parsing,
                          LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                          "revocation-lookup")) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_metadata_label(requested_public_key_parsing)) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-public-key-parsing");
        copy_literal(out->status, sizeof(out->status), "denied-public-key-parsing");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->public_key_parsed != 0u) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-public-key-parsing");
        copy_literal(out->status, sizeof(out->status), "denied-public-key-parsing");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->key_material_loaded != 0u) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "denied-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->private_key_handling != 0u ||
        key_material->key_generation_performed != 0u ||
        key_material->hardware_key_used != 0u) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->trust_store_loaded != 0u) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_TRUST_STORE;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-trust-store");
        copy_literal(out->status, sizeof(out->status), "denied-trust-store");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->revocation_lookup_performed != 0u ||
        key_material->network_performed != 0u) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (key_material->signature_performed != 0u ||
        key_material->verification_performed != 0u ||
        key_material->signer_invoked != 0u ||
        key_material->handoff_performed != 0u ||
        key_material->effect_performed != 0u ||
        key_material->host_read_performed != 0u ||
        key_material->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT;
        copy_literal(out->public_key_parsing_state, sizeof(out->public_key_parsing_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    out->public_key_parsing_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->signer_invoked = 0u;
    out->public_key_parsed = 0u;
    out->key_material_loaded = 0u;
    out->private_key_handling = 0u;
    out->key_generation_performed = 0u;
    out->hardware_key_used = 0u;
    out->trust_store_loaded = 0u;
    out->revocation_lookup_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK;
    copy_literal(
        out->public_key_parsing_state,
        sizeof(out->public_key_parsing_state),
        "public-key-parsing-metadata-only");
    copy_literal(out->status, sizeof(out->status), "public-key-parsing-metadata");
    return LATTICRA_STATUS_OK;
}

static int public_key_parsing_ready_state_valid(
    const latticra_seal_public_key_parsing_t *public_key_parsing) {
    if (public_key_parsing == NULL ||
        !boolean_flag_valid(public_key_parsing->public_key_parsing_ready)) {
        return 0;
    }
    if (public_key_parsing->public_key_parsing_ready == 0u) {
        return public_key_parsing->error != LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK &&
               text_field_valid(public_key_parsing->public_key_parsing_state,
                                LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
               text_field_valid(public_key_parsing->status,
                                LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX);
    }

    return public_key_parsing->error == LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK &&
           public_key_parsing->signing_authorization_ready == 1u &&
           public_key_parsing->signer_handoff_ready == 1u &&
           public_key_parsing->signer_invocation_ready == 1u &&
           public_key_parsing->signing_operation_ready == 1u &&
           public_key_parsing->key_handling_ready == 1u &&
           public_key_parsing->key_material_ready == 1u &&
           bounded_string_is(public_key_parsing->requested_signature,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "Ed25519-development") &&
           bounded_string_is(public_key_parsing->requested_signing_authorization,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(public_key_parsing->requested_signer_handoff,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(public_key_parsing->requested_signer_invocation,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(public_key_parsing->requested_signing_operation,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(public_key_parsing->requested_key_handling,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(public_key_parsing->requested_key_material,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(public_key_parsing->requested_public_key_parsing,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(public_key_parsing->signing_authorization_state,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "authorized-metadata-only") &&
           bounded_string_is(public_key_parsing->signer_handoff_state,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "handoff-metadata-only") &&
           bounded_string_is(public_key_parsing->signer_invocation_state,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "invocation-metadata-only") &&
           bounded_string_is(public_key_parsing->signing_operation_state,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "operation-metadata-only") &&
           bounded_string_is(public_key_parsing->key_handling_state,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "key-handling-metadata-only") &&
           bounded_string_is(public_key_parsing->key_material_state,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "key-material-metadata-only") &&
           bounded_string_is(public_key_parsing->public_key_parsing_state,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "public-key-parsing-metadata-only") &&
           bounded_string_is(public_key_parsing->status,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "public-key-parsing-metadata");
}

int latticra_seal_public_key_parsing_is_metadata_only(
    const latticra_seal_public_key_parsing_t *public_key_parsing) {
    if (public_key_parsing == NULL) {
        return 0;
    }

    return public_key_parsing->signature_performed == 0u &&
           public_key_parsing->verification_performed == 0u &&
           public_key_parsing->signer_invoked == 0u &&
           public_key_parsing->public_key_parsed == 0u &&
           public_key_parsing->key_material_loaded == 0u &&
           public_key_parsing->private_key_handling == 0u &&
           public_key_parsing->key_generation_performed == 0u &&
           public_key_parsing->hardware_key_used == 0u &&
           public_key_parsing->trust_store_loaded == 0u &&
           public_key_parsing->revocation_lookup_performed == 0u &&
           public_key_parsing->handoff_performed == 0u &&
           public_key_parsing->effect_performed == 0u &&
           public_key_parsing->runtime_authority_granted == 0u &&
           public_key_parsing->host_read_performed == 0u &&
           public_key_parsing->host_write_performed == 0u &&
           public_key_parsing->network_performed == 0u &&
           public_key_parsing_error_valid(public_key_parsing->error) &&
           boolean_flag_valid(public_key_parsing->signing_authorization_ready) &&
           boolean_flag_valid(public_key_parsing->signer_handoff_ready) &&
           boolean_flag_valid(public_key_parsing->signer_invocation_ready) &&
           boolean_flag_valid(public_key_parsing->signing_operation_ready) &&
           boolean_flag_valid(public_key_parsing->key_handling_ready) &&
           boolean_flag_valid(public_key_parsing->key_material_ready) &&
           public_key_parsing_ready_state_valid(public_key_parsing) &&
           bounded_string_is(public_key_parsing->public_key_parsing_profile,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX,
                             "latticra-seal-public-key-parsing/0.1") &&
           text_field_terminated(public_key_parsing->key_material_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->key_handling_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->signing_operation_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->signer_invocation_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->signer_handoff_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->signing_authorization_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->signature_request_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->envelope_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->report_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->handoff_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->decision_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->gate_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->receipt_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->verify_profile,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX) &&
           text_field_terminated(public_key_parsing->message_digest_algorithm,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_ALGORITHM_MAX) &&
           text_field_terminated(public_key_parsing->message_digest_hex,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_DIGEST_MAX) &&
           text_field_terminated(public_key_parsing->public_key_identity_label,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_capability,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_effect,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_handoff,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_report,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_envelope,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_signature,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_signing_authorization,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_signer_handoff,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_signer_invocation,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_signing_operation,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_key_handling,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_key_material,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_public_key_parsing,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->requested_scope,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX) &&
           text_field_terminated(public_key_parsing->signing_authorization_state,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_terminated(public_key_parsing->signer_handoff_state,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_terminated(public_key_parsing->signer_invocation_state,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_terminated(public_key_parsing->signing_operation_state,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_terminated(public_key_parsing->key_handling_state,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_terminated(public_key_parsing->key_material_state,
                                 LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           text_field_valid(public_key_parsing->public_key_parsing_state,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX) &&
           bounded_string_is(public_key_parsing->mode,
                             LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX,
                             "metadata-only") &&
           text_field_valid(public_key_parsing->status,
                            LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX);
}

latticra_status_t latticra_seal_public_key_parsing_render(
    const latticra_seal_public_key_parsing_t *public_key_parsing,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (public_key_parsing == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_public_key_parsing_is_metadata_only(public_key_parsing)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL PUBLIC KEY PARSING\n"
        "public_key_parsing_profile=%s\n"
        "key_material_profile=%s\n"
        "key_handling_profile=%s\n"
        "signing_operation_profile=%s\n"
        "signer_invocation_profile=%s\n"
        "signer_handoff_profile=%s\n"
        "signing_authorization_profile=%s\n"
        "signature_request_profile=%s\n"
        "envelope_profile=%s\n"
        "report_profile=%s\n"
        "handoff_profile=%s\n"
        "decision_profile=%s\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_handoff=%s\n"
        "requested_report=%s\n"
        "requested_envelope=%s\n"
        "requested_signature=%s\n"
        "requested_signing_authorization=%s\n"
        "requested_signer_handoff=%s\n"
        "requested_signer_invocation=%s\n"
        "requested_signing_operation=%s\n"
        "requested_key_handling=%s\n"
        "requested_key_material=%s\n"
        "requested_public_key_parsing=%s\n"
        "requested_scope=%s\n"
        "signing_authorization_state=%s\n"
        "signing_authorization_ready=%u\n"
        "signer_handoff_state=%s\n"
        "signer_handoff_ready=%u\n"
        "signer_invocation_state=%s\n"
        "signer_invocation_ready=%u\n"
        "signing_operation_state=%s\n"
        "signing_operation_ready=%u\n"
        "key_handling_state=%s\n"
        "key_handling_ready=%u\n"
        "key_material_state=%s\n"
        "key_material_ready=%u\n"
        "public_key_parsing_state=%s\n"
        "public_key_parsing_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "signer_invoked=%u\n"
        "public_key_parsed=%u\n"
        "key_material_loaded=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
        "hardware_key_used=%u\n"
        "trust_store_loaded=%u\n"
        "revocation_lookup_performed=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "error=%s\n"
        "status=%s\n",
        public_key_parsing->public_key_parsing_profile,
        public_key_parsing->key_material_profile,
        public_key_parsing->key_handling_profile,
        public_key_parsing->signing_operation_profile,
        public_key_parsing->signer_invocation_profile,
        public_key_parsing->signer_handoff_profile,
        public_key_parsing->signing_authorization_profile,
        public_key_parsing->signature_request_profile,
        public_key_parsing->envelope_profile,
        public_key_parsing->report_profile,
        public_key_parsing->handoff_profile,
        public_key_parsing->decision_profile,
        public_key_parsing->gate_profile,
        public_key_parsing->receipt_profile,
        public_key_parsing->verify_profile,
        public_key_parsing->message_digest_algorithm,
        public_key_parsing->message_digest_hex,
        public_key_parsing->public_key_identity_label,
        public_key_parsing->requested_capability,
        public_key_parsing->requested_effect,
        public_key_parsing->requested_handoff,
        public_key_parsing->requested_report,
        public_key_parsing->requested_envelope,
        public_key_parsing->requested_signature,
        public_key_parsing->requested_signing_authorization,
        public_key_parsing->requested_signer_handoff,
        public_key_parsing->requested_signer_invocation,
        public_key_parsing->requested_signing_operation,
        public_key_parsing->requested_key_handling,
        public_key_parsing->requested_key_material,
        public_key_parsing->requested_public_key_parsing,
        public_key_parsing->requested_scope,
        public_key_parsing->signing_authorization_state,
        public_key_parsing->signing_authorization_ready,
        public_key_parsing->signer_handoff_state,
        public_key_parsing->signer_handoff_ready,
        public_key_parsing->signer_invocation_state,
        public_key_parsing->signer_invocation_ready,
        public_key_parsing->signing_operation_state,
        public_key_parsing->signing_operation_ready,
        public_key_parsing->key_handling_state,
        public_key_parsing->key_handling_ready,
        public_key_parsing->key_material_state,
        public_key_parsing->key_material_ready,
        public_key_parsing->public_key_parsing_state,
        public_key_parsing->public_key_parsing_ready,
        public_key_parsing->signature_performed,
        public_key_parsing->verification_performed,
        public_key_parsing->signer_invoked,
        public_key_parsing->public_key_parsed,
        public_key_parsing->key_material_loaded,
        public_key_parsing->private_key_handling,
        public_key_parsing->key_generation_performed,
        public_key_parsing->hardware_key_used,
        public_key_parsing->trust_store_loaded,
        public_key_parsing->revocation_lookup_performed,
        public_key_parsing->handoff_performed,
        public_key_parsing->effect_performed,
        public_key_parsing->runtime_authority_granted,
        public_key_parsing->host_read_performed,
        public_key_parsing->host_write_performed,
        public_key_parsing->network_performed,
        public_key_parsing->mode,
        latticra_seal_public_key_parsing_error_label(public_key_parsing->error),
        public_key_parsing->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
