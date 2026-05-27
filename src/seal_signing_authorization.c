#include "latticra/seal_signing_authorization.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_signature(const char *signature) {
    return strcmp(signature, "Ed25519-development") == 0;
}

static int is_allowed_authorization(const char *authorization) {
    return strcmp(authorization, "metadata-only") == 0;
}

const char *latticra_seal_signing_authorization_error_label(
    latticra_seal_signing_authorization_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST:
        return "invalid-signature-request";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST:
        return "denied-signature-request";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST:
        return "denied-authorization-request";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void authorization_init(latticra_seal_signing_authorization_t *authorization) {
    memset(authorization, 0, sizeof(*authorization));
    copy_literal(
        authorization->signing_authorization_profile,
        sizeof(authorization->signing_authorization_profile),
        "latticra-seal-signing-authorization/0.1");
    copy_literal(
        authorization->signing_authorization_state,
        sizeof(authorization->signing_authorization_state),
        "denied-signature-request");
    copy_literal(authorization->crypto_graduation_gate_state, sizeof(authorization->crypto_graduation_gate_state), "not-required");
    authorization->crypto_graduation_gate_present = 0u;
    authorization->crypto_graduation_gate_passed = 0u;
    authorization->standard_expectations_met = 0u;
    authorization->local_verify_graduated = 0u;
    authorization->receipt_promotion_graduated = 0u;
    authorization->authority_promotion_allowed = 0u;
    copy_literal(authorization->mode, sizeof(authorization->mode), "metadata-only");
    authorization->signature_request_ready = 0u;
    authorization->signing_authorization_ready = 0u;
    authorization->signature_performed = 0u;
    authorization->verification_performed = 0u;
    authorization->private_key_handling = 0u;
    authorization->key_generation_performed = 0u;
    authorization->trust_store_loaded = 0u;
    authorization->revocation_lookup_performed = 0u;
    authorization->handoff_performed = 0u;
    authorization->effect_performed = 0u;
    authorization->runtime_authority_granted = 0u;
    authorization->host_read_performed = 0u;
    authorization->host_write_performed = 0u;
    authorization->network_performed = 0u;
    authorization->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_INPUT;
    copy_literal(authorization->status, sizeof(authorization->status), "invalid-input");
}

static void copy_request_metadata(
    const latticra_seal_signature_request_t *request,
    const char *requested_signing_authorization,
    latticra_seal_signing_authorization_t *out) {
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), request->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), request->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), request->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), request->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), request->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), request->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), request->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), request->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), request->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), request->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), request->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), request->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), request->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), request->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), request->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), request->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), request->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), request->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), request->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), request->requested_signature);
    copy_literal(out->requested_signing_authorization, sizeof(out->requested_signing_authorization), requested_signing_authorization);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), request->requested_scope);
    out->crypto_graduation_gate_present = request->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = request->crypto_graduation_gate_passed;
    out->standard_expectations_met = request->standard_expectations_met;
    out->local_verify_graduated = request->local_verify_graduated;
    out->receipt_promotion_graduated = request->receipt_promotion_graduated;
    out->authority_promotion_allowed = request->authority_promotion_allowed;
    copy_literal(out->signature_request_state, sizeof(out->signature_request_state), request->signature_request_state);
    out->signature_request_ready = request->signature_request_ready;
    out->signature_performed = request->signature_performed;
    out->verification_performed = request->verification_performed;
    out->private_key_handling = request->private_key_handling;
    out->handoff_performed = request->handoff_performed;
    out->effect_performed = request->effect_performed;
    out->runtime_authority_granted = request->runtime_authority_granted;
    out->host_read_performed = request->host_read_performed;
    out->host_write_performed = request->host_write_performed;
    out->network_performed = request->network_performed;
}

latticra_status_t latticra_seal_signing_authorization_from_request(
    const latticra_seal_signature_request_t *request,
    const char *requested_signing_authorization,
    latticra_seal_signing_authorization_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    authorization_init(out);

    if (request == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_request_metadata(request, requested_signing_authorization, out);

    if (request->error != LATTICRA_SEAL_SIGNATURE_REQUEST_OK) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "invalid-signature-request");
        return LATTICRA_STATUS_OK;
    }

    if (request->crypto_graduation_gate_present != 0u &&
        (request->crypto_graduation_gate_passed != 1u ||
         request->standard_expectations_met != 1u ||
         request->local_verify_graduated != 1u ||
         request->receipt_promotion_graduated != 1u ||
         request->authority_promotion_allowed != 0u ||
         strcmp(request->crypto_graduation_gate_state, "graduated-authority-neutral") != 0)) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (request->signature_request_ready != 1u ||
        strcmp(request->signature_request_state, "requested-metadata-only") != 0) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "denied-signature-request");
        return LATTICRA_STATUS_OK;
    }

    if (request->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (request->private_key_handling != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_PRIVATE_KEY;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (request->signature_performed != 0u ||
        request->verification_performed != 0u ||
        request->handoff_performed != 0u ||
        request->effect_performed != 0u ||
        request->host_read_performed != 0u ||
        request->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (request->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_NETWORK_EFFECT;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (request->requested_signature[0] == '\0' || !is_allowed_signature(request->requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (requested_signing_authorization == NULL || requested_signing_authorization[0] == '\0') {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-authorization-request");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_authorization(requested_signing_authorization)) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-authorization-request");
        copy_literal(out->status, sizeof(out->status), "denied-authorization-request");
        return LATTICRA_STATUS_OK;
    }

    out->signing_authorization_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->private_key_handling = 0u;
    out->key_generation_performed = 0u;
    out->trust_store_loaded = 0u;
    out->revocation_lookup_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK;
    copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "authorized-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signing-authorization-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signing_authorization_is_metadata_only(
    const latticra_seal_signing_authorization_t *authorization) {
    if (authorization == NULL) {
        return 0;
    }

    return authorization->signature_performed == 0u &&
           authorization->verification_performed == 0u &&
           authorization->private_key_handling == 0u &&
           authorization->key_generation_performed == 0u &&
           authorization->trust_store_loaded == 0u &&
           authorization->revocation_lookup_performed == 0u &&
           authorization->handoff_performed == 0u &&
           authorization->effect_performed == 0u &&
           authorization->runtime_authority_granted == 0u &&
           authorization->host_read_performed == 0u &&
           authorization->host_write_performed == 0u &&
           authorization->network_performed == 0u;
}

latticra_status_t latticra_seal_signing_authorization_render(
    const latticra_seal_signing_authorization_t *authorization,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (authorization == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNING AUTHORIZATION\n"
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
        "crypto_graduation_profile=%s\n"
        "assurance_baseline_profile=%s\n"
        "crypto_graduation_gate_state=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_handoff=%s\n"
        "requested_report=%s\n"
        "requested_envelope=%s\n"
        "requested_signature=%s\n"
        "requested_signing_authorization=%s\n"
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "signature_request_state=%s\n"
        "signature_request_ready=%u\n"
        "signing_authorization_state=%s\n"
        "signing_authorization_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
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
        authorization->signing_authorization_profile,
        authorization->signature_request_profile,
        authorization->envelope_profile,
        authorization->report_profile,
        authorization->handoff_profile,
        authorization->decision_profile,
        authorization->gate_profile,
        authorization->receipt_profile,
        authorization->verify_profile,
        authorization->message_digest_algorithm,
        authorization->message_digest_hex,
        authorization->public_key_identity_label,
        authorization->crypto_graduation_profile,
        authorization->assurance_baseline_profile,
        authorization->crypto_graduation_gate_state,
        authorization->requested_capability,
        authorization->requested_effect,
        authorization->requested_handoff,
        authorization->requested_report,
        authorization->requested_envelope,
        authorization->requested_signature,
        authorization->requested_signing_authorization,
        authorization->requested_scope,
        authorization->crypto_graduation_gate_present,
        authorization->crypto_graduation_gate_passed,
        authorization->standard_expectations_met,
        authorization->local_verify_graduated,
        authorization->receipt_promotion_graduated,
        authorization->authority_promotion_allowed,
        authorization->signature_request_state,
        authorization->signature_request_ready,
        authorization->signing_authorization_state,
        authorization->signing_authorization_ready,
        authorization->signature_performed,
        authorization->verification_performed,
        authorization->private_key_handling,
        authorization->key_generation_performed,
        authorization->trust_store_loaded,
        authorization->revocation_lookup_performed,
        authorization->handoff_performed,
        authorization->effect_performed,
        authorization->runtime_authority_granted,
        authorization->host_read_performed,
        authorization->host_write_performed,
        authorization->network_performed,
        authorization->mode,
        latticra_seal_signing_authorization_error_label(authorization->error),
        authorization->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
