#include "latticra/seal_verified_capability_gate.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_capability(const char *capability) {
    return strcmp(capability, "verified-receipt-inspection") == 0 ||
           strcmp(capability, "verified-receipt-report") == 0;
}

static int is_allowed_effect(const char *effect) {
    return strcmp(effect, "report-only") == 0 ||
           strcmp(effect, "evaluate-only") == 0;
}

const char *latticra_seal_verified_capability_gate_error_label(
    latticra_seal_verified_capability_gate_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_OK:
        return "ok";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_INVALID_RECEIPT:
        return "invalid-receipt";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNVERIFIED:
        return "denied-unverified";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_INVALID_RECEIPT:
        return "denied-invalid-receipt";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY:
        return "missing-requested-capability";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT:
        return "missing-requested-effect";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNKNOWN_CAPABILITY:
        return "denied-unknown-capability";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNKNOWN_EFFECT:
        return "denied-unknown-effect";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void gate_init(latticra_seal_verified_capability_gate_t *gate) {
    memset(gate, 0, sizeof(*gate));
    copy_literal(gate->gate_profile, sizeof(gate->gate_profile), "latticra-seal-verified-capability-gate/0.1");
    copy_literal(gate->crypto_graduation_gate_state, sizeof(gate->crypto_graduation_gate_state), "not-required");
    copy_literal(gate->gate_state, sizeof(gate->gate_state), "denied-invalid-receipt");
    gate->crypto_graduation_gate_present = 0u;
    gate->crypto_graduation_gate_passed = 0u;
    gate->standard_expectations_met = 0u;
    gate->local_verify_graduated = 0u;
    gate->receipt_promotion_graduated = 0u;
    gate->authority_promotion_allowed = 0u;
    gate->verified = 0u;
    gate->authority_usable = 0u;
    gate->receipt_capability_gate_allowed = 0u;
    gate->gate_allowed = 0u;
    gate->runtime_authority_granted = 0u;
    gate->effect_performed = 0u;
    gate->host_read_performed = 0u;
    gate->host_write_performed = 0u;
    gate->network_performed = 0u;
    gate->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_INVALID_INPUT;
    copy_literal(gate->status, sizeof(gate->status), "invalid-input");
}

static void copy_receipt_metadata(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    latticra_seal_verified_capability_gate_t *out) {
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), receipt->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), receipt->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), receipt->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), receipt->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), receipt->public_key_identity_label);
    copy_literal(out->receipt_state, sizeof(out->receipt_state), receipt->receipt_state);
    copy_literal(out->verification_state, sizeof(out->verification_state), receipt->verification_state);
    out->verified = receipt->verified;
    out->authority_usable = receipt->authority_usable;
    out->receipt_capability_gate_allowed = receipt->capability_gate_allowed;
}

static void copy_crypto_graduation_metadata(
    const latticra_seal_crypto_graduation_gate_t *crypto_gate,
    latticra_seal_verified_capability_gate_t *out) {
    copy_literal(
        out->crypto_graduation_profile,
        sizeof(out->crypto_graduation_profile),
        crypto_gate->crypto_graduation_profile);
    copy_literal(
        out->assurance_baseline_profile,
        sizeof(out->assurance_baseline_profile),
        crypto_gate->assurance_baseline_profile);
    copy_literal(
        out->crypto_graduation_gate_state,
        sizeof(out->crypto_graduation_gate_state),
        crypto_gate->gate_state);
    out->crypto_graduation_gate_present = 1u;
    out->crypto_graduation_gate_passed =
        crypto_gate->error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_OK ? 1u : 0u;
    out->standard_expectations_met = crypto_gate->standard_expectations_met;
    out->local_verify_graduated = crypto_gate->local_verify_graduated;
    out->receipt_promotion_graduated = crypto_gate->receipt_promotion_graduated;
    out->authority_promotion_allowed = crypto_gate->authority_promotion_allowed;
}

static latticra_status_t gate_fail_crypto_graduation(
    latticra_seal_verified_capability_gate_t *out,
    const char *status) {
    out->gate_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_CRYPTO_GRADUATION_GATE;
    copy_literal(out->gate_state, sizeof(out->gate_state), "denied-crypto-graduation-gate");
    copy_literal(out->status, sizeof(out->status), status);
    return LATTICRA_STATUS_OK;
}

static int crypto_gate_matches_receipt(
    const latticra_seal_crypto_graduation_gate_t *crypto_gate,
    const latticra_seal_verified_receipt_promotion_t *receipt) {
    return strcmp(crypto_gate->receipt_profile, receipt->receipt_profile) == 0 &&
           strcmp(crypto_gate->verify_profile, receipt->verify_profile) == 0 &&
           strcmp(crypto_gate->message_digest_algorithm, receipt->message_digest_algorithm) == 0 &&
           strcmp(crypto_gate->message_digest_hex, receipt->message_digest_hex) == 0 &&
           strcmp(crypto_gate->public_key_identity_label, receipt->public_key_identity_label) == 0 &&
           strcmp(crypto_gate->receipt_state, receipt->receipt_state) == 0 &&
           strcmp(crypto_gate->verification_state, receipt->verification_state) == 0;
}

static int crypto_gate_is_acceptable(
    const latticra_seal_crypto_graduation_gate_t *crypto_gate) {
    return crypto_gate->error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_OK &&
           strcmp(crypto_gate->gate_state, "graduated-authority-neutral") == 0 &&
           crypto_gate->crypto_graduation_profile[0] != '\0' &&
           crypto_gate->standard_expectations_met == 1u &&
           crypto_gate->local_verify_graduated == 1u &&
           crypto_gate->receipt_promotion_graduated == 1u &&
           crypto_gate->production_crypto_claim_allowed == 0u &&
           crypto_gate->fips_claim_allowed == 0u &&
           crypto_gate->signing_authority_granted == 0u &&
           crypto_gate->key_generation_allowed == 0u &&
           crypto_gate->key_storage_allowed == 0u &&
           crypto_gate->revocation_lookup_allowed == 0u &&
           crypto_gate->network_lookup_allowed == 0u &&
           crypto_gate->authority_usable == 0u &&
           crypto_gate->authority_promotion_allowed == 0u &&
           crypto_gate->capability_gate_allowed == 0u &&
           crypto_gate->runtime_authority_granted == 0u &&
           latticra_seal_crypto_graduation_gate_is_authority_neutral(crypto_gate) == 1;
}

static latticra_status_t verified_capability_gate_evaluate_receipt(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    const char *requested_capability,
    const char *requested_effect,
    const char *requested_scope,
    latticra_seal_verified_capability_gate_t *out) {
    if (receipt == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_receipt_metadata(receipt, out);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), requested_scope != NULL ? requested_scope : "unspecified-scope");

    if (receipt->error != LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK) {
        out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_INVALID_RECEIPT;
        copy_literal(out->gate_state, sizeof(out->gate_state), "denied-invalid-receipt");
        copy_literal(out->status, sizeof(out->status), "invalid-receipt");
        return LATTICRA_STATUS_OK;
    }

    if (strcmp(receipt->receipt_state, "verified") != 0 ||
        strcmp(receipt->verification_state, "verified") != 0 ||
        receipt->verified != 1u) {
        out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNVERIFIED;
        copy_literal(out->gate_state, sizeof(out->gate_state), "denied-unverified");
        copy_literal(out->status, sizeof(out->status), "denied-unverified");
        return LATTICRA_STATUS_OK;
    }

    if (receipt->invalid != 0u ||
        receipt->message_digest_hex[0] == '\0' ||
        receipt->public_key_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_INVALID_RECEIPT;
        copy_literal(out->gate_state, sizeof(out->gate_state), "denied-invalid-receipt");
        copy_literal(out->status, sizeof(out->status), "denied-invalid-receipt");
        return LATTICRA_STATUS_OK;
    }

    if (requested_capability == NULL || requested_capability[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY;
        copy_literal(out->gate_state, sizeof(out->gate_state), "denied-unknown-capability");
        copy_literal(out->status, sizeof(out->status), "missing-requested-capability");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->requested_capability, sizeof(out->requested_capability), requested_capability);

    if (requested_effect == NULL || requested_effect[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT;
        copy_literal(out->gate_state, sizeof(out->gate_state), "denied-unknown-effect");
        copy_literal(out->status, sizeof(out->status), "missing-requested-effect");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->requested_effect, sizeof(out->requested_effect), requested_effect);

    if (!is_allowed_capability(requested_capability)) {
        out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNKNOWN_CAPABILITY;
        copy_literal(out->gate_state, sizeof(out->gate_state), "denied-unknown-capability");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-capability");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_effect(requested_effect)) {
        out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNKNOWN_EFFECT;
        copy_literal(out->gate_state, sizeof(out->gate_state), "denied-unknown-effect");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-effect");
        return LATTICRA_STATUS_OK;
    }

    out->gate_allowed = 1u;
    out->runtime_authority_granted = 0u;
    out->effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_OK;
    copy_literal(out->gate_state, sizeof(out->gate_state), "allowed-metadata-only");
    copy_literal(out->status, sizeof(out->status), "verified-capability-gate-metadata");
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_verified_capability_gate_from_receipt(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    const char *requested_capability,
    const char *requested_effect,
    const char *requested_scope,
    latticra_seal_verified_capability_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    gate_init(out);
    return verified_capability_gate_evaluate_receipt(
        receipt,
        requested_capability,
        requested_effect,
        requested_scope,
        out);
}

latticra_status_t latticra_seal_verified_capability_gate_from_crypto_graduation_gate(
    const latticra_seal_crypto_graduation_gate_t *crypto_gate,
    const latticra_seal_verified_receipt_promotion_t *receipt,
    const char *requested_capability,
    const char *requested_effect,
    const char *requested_scope,
    latticra_seal_verified_capability_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    gate_init(out);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), "required");

    if (crypto_gate == NULL) {
        return gate_fail_crypto_graduation(out, "missing-crypto-graduation-gate");
    }

    copy_crypto_graduation_metadata(crypto_gate, out);

    if (!crypto_gate_is_acceptable(crypto_gate)) {
        return gate_fail_crypto_graduation(out, "invalid-crypto-graduation-gate");
    }

    if (receipt != NULL && !crypto_gate_matches_receipt(crypto_gate, receipt)) {
        return gate_fail_crypto_graduation(out, "crypto-graduation-receipt-mismatch");
    }

    return verified_capability_gate_evaluate_receipt(
        receipt,
        requested_capability,
        requested_effect,
        requested_scope,
        out);
}

int latticra_seal_verified_capability_gate_is_metadata_only(
    const latticra_seal_verified_capability_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->runtime_authority_granted == 0u &&
           gate->effect_performed == 0u &&
           gate->host_read_performed == 0u &&
           gate->host_write_performed == 0u &&
           gate->network_performed == 0u;
}

latticra_status_t latticra_seal_verified_capability_gate_report(
    const latticra_seal_verified_capability_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL VERIFIED CAPABILITY GATE\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "receipt_state=%s\n"
        "verification_state=%s\n"
        "crypto_graduation_profile=%s\n"
        "assurance_baseline_profile=%s\n"
        "crypto_graduation_gate_state=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "verified=%u\n"
        "authority_usable=%u\n"
        "receipt_capability_gate_allowed=%u\n"
        "gate_allowed=%u\n"
        "gate_state=%s\n"
        "runtime_authority_granted=%u\n"
        "effect_performed=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        gate->gate_profile,
        gate->receipt_profile,
        gate->verify_profile,
        gate->message_digest_algorithm,
        gate->message_digest_hex,
        gate->public_key_identity_label,
        gate->receipt_state,
        gate->verification_state,
        gate->crypto_graduation_profile,
        gate->assurance_baseline_profile,
        gate->crypto_graduation_gate_state,
        gate->requested_capability,
        gate->requested_effect,
        gate->requested_scope,
        gate->crypto_graduation_gate_present,
        gate->crypto_graduation_gate_passed,
        gate->standard_expectations_met,
        gate->local_verify_graduated,
        gate->receipt_promotion_graduated,
        gate->authority_promotion_allowed,
        gate->verified,
        gate->authority_usable,
        gate->receipt_capability_gate_allowed,
        gate->gate_allowed,
        gate->gate_state,
        gate->runtime_authority_granted,
        gate->effect_performed,
        gate->host_read_performed,
        gate->host_write_performed,
        gate->network_performed,
        latticra_seal_verified_capability_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
