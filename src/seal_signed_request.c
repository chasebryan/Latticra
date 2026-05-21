#include "latticra/seal_signed_request.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_signed_request_error_label(
    latticra_seal_signed_request_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNED_REQUEST_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNED_REQUEST_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNED_REQUEST_INVALID_FRESHNESS:
        return "invalid-freshness";
    default:
        return "unknown";
    }
}

static void signed_request_init(latticra_seal_signed_request_t *signed_request) {
    memset(signed_request, 0, sizeof(*signed_request));
    copy_literal(signed_request->signed_request_profile, sizeof(signed_request->signed_request_profile), "latticra-seal-signed-request/0.1");
    copy_literal(signed_request->signed_request_id, sizeof(signed_request->signed_request_id), "unset");
    copy_literal(signed_request->signature_algorithm, sizeof(signed_request->signature_algorithm), "unset");
    copy_literal(signed_request->signing_key_id, sizeof(signed_request->signing_key_id), "unset");
    copy_literal(signed_request->signature_hash, sizeof(signed_request->signature_hash), "unset");
    signed_request->signed_request_supported = 0u;
    signed_request->signature_generation_supported = 0u;
    signed_request->signature_verification_supported = 0u;
    signed_request->signature_present = 0u;
    signed_request->signature_valid = 0u;
    signed_request->signature_algorithm_declared = 0u;
    signed_request->signing_key_id_present = 0u;
    signed_request->signature_hash_present = 0u;
    signed_request->signed_request_id_present = 0u;
    signed_request->identity_binding_declared = 0u;
    signed_request->context_binding_declared = 0u;
    signed_request->parameter_binding_declared = 0u;
    signed_request->freshness_binding_declared = 0u;
    signed_request->policy_binding_declared = 0u;
    signed_request->trust_store_supported = 0u;
    signed_request->revocation_lookup_supported = 0u;
    signed_request->runtime_authority_granted = 0u;
    signed_request->host_read_performed = 0u;
    signed_request->host_write_performed = 0u;
    signed_request->network_performed = 0u;
    copy_literal(signed_request->mode, sizeof(signed_request->mode), "report-only");
    copy_literal(signed_request->decision, sizeof(signed_request->decision), "report-only");
    copy_literal(signed_request->reason, sizeof(signed_request->reason), "signed-request-metadata-only");
    signed_request->error = LATTICRA_SEAL_SIGNED_REQUEST_INVALID_INPUT;
    copy_literal(signed_request->status, sizeof(signed_request->status), "invalid-input");
}

latticra_status_t latticra_seal_signed_request_from_freshness(
    const latticra_seal_request_freshness_t *freshness,
    latticra_seal_signed_request_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    signed_request_init(out);

    if (freshness == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (freshness->error != LATTICRA_SEAL_REQUEST_FRESHNESS_OK ||
        latticra_seal_request_freshness_is_report_only(freshness) != 1) {
        out->error = LATTICRA_SEAL_SIGNED_REQUEST_INVALID_FRESHNESS;
        copy_literal(out->reason, sizeof(out->reason), "invalid-freshness");
        copy_literal(out->status, sizeof(out->status), "invalid-freshness");
        return LATTICRA_STATUS_OK;
    }

    out->runtime_authority_granted = freshness->runtime_authority_granted;
    out->host_read_performed = freshness->host_read_performed;
    out->host_write_performed = freshness->host_write_performed;
    out->network_performed = freshness->network_performed;
    out->error = LATTICRA_SEAL_SIGNED_REQUEST_OK;
    copy_literal(out->status, sizeof(out->status), "signed-request-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signed_request_is_report_only(
    const latticra_seal_signed_request_t *signed_request) {
    if (signed_request == NULL) {
        return 0;
    }

    return signed_request->signed_request_supported == 0u &&
           signed_request->signature_generation_supported == 0u &&
           signed_request->signature_verification_supported == 0u &&
           signed_request->signature_present == 0u &&
           signed_request->signature_valid == 0u &&
           signed_request->signature_algorithm_declared == 0u &&
           signed_request->signing_key_id_present == 0u &&
           signed_request->signature_hash_present == 0u &&
           signed_request->signed_request_id_present == 0u &&
           signed_request->identity_binding_declared == 0u &&
           signed_request->context_binding_declared == 0u &&
           signed_request->parameter_binding_declared == 0u &&
           signed_request->freshness_binding_declared == 0u &&
           signed_request->policy_binding_declared == 0u &&
           signed_request->trust_store_supported == 0u &&
           signed_request->revocation_lookup_supported == 0u &&
           signed_request->runtime_authority_granted == 0u &&
           signed_request->host_read_performed == 0u &&
           signed_request->host_write_performed == 0u &&
           signed_request->network_performed == 0u;
}

latticra_status_t latticra_seal_signed_request_report(
    const latticra_seal_signed_request_t *signed_request,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (signed_request == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNED REQUEST\n"
        "signed_request_profile=%s\n"
        "signed_request_id=%s\n"
        "signature_algorithm=%s\n"
        "signing_key_id=%s\n"
        "signature_hash=%s\n"
        "signed_request_supported=%u\n"
        "signature_generation_supported=%u\n"
        "signature_verification_supported=%u\n"
        "signature_present=%u\n"
        "signature_valid=%u\n"
        "signature_algorithm_declared=%u\n"
        "signing_key_id_present=%u\n"
        "signature_hash_present=%u\n"
        "signed_request_id_present=%u\n"
        "identity_binding_declared=%u\n"
        "context_binding_declared=%u\n"
        "parameter_binding_declared=%u\n"
        "freshness_binding_declared=%u\n"
        "policy_binding_declared=%u\n"
        "trust_store_supported=%u\n"
        "revocation_lookup_supported=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "decision=%s\n"
        "reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        signed_request->signed_request_profile,
        signed_request->signed_request_id,
        signed_request->signature_algorithm,
        signed_request->signing_key_id,
        signed_request->signature_hash,
        signed_request->signed_request_supported,
        signed_request->signature_generation_supported,
        signed_request->signature_verification_supported,
        signed_request->signature_present,
        signed_request->signature_valid,
        signed_request->signature_algorithm_declared,
        signed_request->signing_key_id_present,
        signed_request->signature_hash_present,
        signed_request->signed_request_id_present,
        signed_request->identity_binding_declared,
        signed_request->context_binding_declared,
        signed_request->parameter_binding_declared,
        signed_request->freshness_binding_declared,
        signed_request->policy_binding_declared,
        signed_request->trust_store_supported,
        signed_request->revocation_lookup_supported,
        signed_request->runtime_authority_granted,
        signed_request->host_read_performed,
        signed_request->host_write_performed,
        signed_request->network_performed,
        signed_request->mode,
        signed_request->decision,
        signed_request->reason,
        latticra_seal_signed_request_error_label(signed_request->error),
        signed_request->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
