#include "latticra/seal_signed_receipt_proof_path.h"

#include <stdio.h>
#include <string.h>

static int fail(const char *message) {
    fprintf(stderr, "FAIL: %s\n", message);
    return 1;
}

static void set_string(char *destination, size_t destination_len, const char *source) {
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static latticra_seal_ed25519_verify_result_t fixture_verified_result(void) {
    latticra_seal_ed25519_verify_result_t result;

    memset(&result, 0, sizeof(result));
    set_string(result.ed25519_verify_profile,
               sizeof(result.ed25519_verify_profile),
               "latticra-seal-ed25519-verify/0.1");
    set_string(result.backend_profile,
               sizeof(result.backend_profile),
               "latticra-seal-crypto-verify-backend/0.1");
    set_string(result.verification_policy_profile,
               sizeof(result.verification_policy_profile),
               "latticra-seal-verification-policy/0.1");
    set_string(result.message_label, sizeof(result.message_label), "signed-receipt-proof-surface");
    result.message_size_bytes = 64u;
    set_string(result.message_digest_algorithm, sizeof(result.message_digest_algorithm), "SHA-256");
    set_string(result.message_digest_hex,
               sizeof(result.message_digest_hex),
               "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    set_string(result.public_key_identity_label,
               sizeof(result.public_key_identity_label),
               "local-development-proof-key");
    result.public_key_size_bytes = LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES;
    set_string(result.signature_algorithm, sizeof(result.signature_algorithm), "Ed25519-development");
    result.signature_size_bytes = LATTICRA_SEAL_ED25519_SIGNATURE_BYTES;
    set_string(result.trust_source, sizeof(result.trust_source), "local-test-vector");
    set_string(result.crypto_verify_state, sizeof(result.crypto_verify_state), "verified");
    result.cryptographic_verification_supported = 1u;
    result.cryptographic_verification_performed = 1u;
    result.verified = 1u;
    result.invalid = 0u;
    result.authority_usable = 0u;
    result.capability_gate_allowed = 0u;
    result.runtime_authority_granted = 0u;
    result.error = LATTICRA_SEAL_ED25519_VERIFY_OK;
    set_string(result.status, sizeof(result.status), "ed25519-verified");
    return result;
}

static latticra_seal_verified_receipt_promotion_t fixture_receipt(void) {
    latticra_seal_ed25519_verify_result_t result = fixture_verified_result();
    latticra_seal_verified_receipt_promotion_t receipt;

    (void)latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt);
    return receipt;
}

static latticra_seal_signer_invocation_t fixture_invocation(void) {
    latticra_seal_signer_invocation_t invocation;

    memset(&invocation, 0, sizeof(invocation));
    set_string(invocation.signer_invocation_profile,
               sizeof(invocation.signer_invocation_profile),
               "latticra-seal-signer-invocation/0.1");
    set_string(invocation.signer_handoff_profile,
               sizeof(invocation.signer_handoff_profile),
               "latticra-seal-signer-handoff/0.1");
    set_string(invocation.signing_authorization_profile,
               sizeof(invocation.signing_authorization_profile),
               "latticra-seal-signing-authorization/0.1");
    set_string(invocation.signature_request_profile,
               sizeof(invocation.signature_request_profile),
               "latticra-seal-signature-request/0.1");
    set_string(invocation.envelope_profile,
               sizeof(invocation.envelope_profile),
               "latticra-seal-report-envelope/0.1");
    set_string(invocation.report_profile,
               sizeof(invocation.report_profile),
               "latticra-seal-runtime-handoff-report/0.1");
    set_string(invocation.handoff_profile,
               sizeof(invocation.handoff_profile),
               "latticra-seal-runtime-handoff-evaluation/0.1");
    set_string(invocation.decision_profile,
               sizeof(invocation.decision_profile),
               "latticra-seal-verified-effect-decision/0.1");
    set_string(invocation.gate_profile,
               sizeof(invocation.gate_profile),
               "latticra-seal-verified-capability-gate/0.1");
    set_string(invocation.receipt_profile,
               sizeof(invocation.receipt_profile),
               "latticra-seal-verified-receipt/0.1");
    set_string(invocation.verify_profile,
               sizeof(invocation.verify_profile),
               "latticra-seal-ed25519-verify/0.1");
    set_string(invocation.message_digest_algorithm,
               sizeof(invocation.message_digest_algorithm),
               "SHA-256");
    set_string(invocation.message_digest_hex,
               sizeof(invocation.message_digest_hex),
               "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    set_string(invocation.public_key_identity_label,
               sizeof(invocation.public_key_identity_label),
               "local-development-proof-key");
    set_string(invocation.crypto_graduation_gate_state,
               sizeof(invocation.crypto_graduation_gate_state),
               "not-required");
    set_string(invocation.requested_capability,
               sizeof(invocation.requested_capability),
               "signed-receipt-proof-path");
    set_string(invocation.requested_effect, sizeof(invocation.requested_effect), "verification-only");
    set_string(invocation.requested_handoff, sizeof(invocation.requested_handoff), "verification-only");
    set_string(invocation.requested_report, sizeof(invocation.requested_report), "verification-only");
    set_string(invocation.requested_envelope, sizeof(invocation.requested_envelope), "verification-only");
    set_string(invocation.requested_signature, sizeof(invocation.requested_signature), "Ed25519-development");
    set_string(invocation.requested_signing_authorization,
               sizeof(invocation.requested_signing_authorization),
               "metadata-only");
    set_string(invocation.requested_signer_handoff,
               sizeof(invocation.requested_signer_handoff),
               "metadata-only");
    set_string(invocation.requested_signer_invocation,
               sizeof(invocation.requested_signer_invocation),
               "metadata-only");
    set_string(invocation.requested_scope, sizeof(invocation.requested_scope), "local-proof-surface");
    set_string(invocation.signing_authorization_state,
               sizeof(invocation.signing_authorization_state),
               "authorized-metadata-only");
    invocation.signing_authorization_ready = 1u;
    set_string(invocation.signer_handoff_state,
               sizeof(invocation.signer_handoff_state),
               "handoff-metadata-only");
    invocation.signer_handoff_ready = 1u;
    set_string(invocation.signer_invocation_state,
               sizeof(invocation.signer_invocation_state),
               "invocation-metadata-only");
    invocation.signer_invocation_ready = 1u;
    invocation.signature_performed = 0u;
    invocation.verification_performed = 0u;
    invocation.signer_invoked = 0u;
    invocation.private_key_handling = 0u;
    invocation.key_generation_performed = 0u;
    invocation.trust_store_loaded = 0u;
    invocation.revocation_lookup_performed = 0u;
    invocation.handoff_performed = 0u;
    invocation.effect_performed = 0u;
    invocation.runtime_authority_granted = 0u;
    invocation.host_read_performed = 0u;
    invocation.host_write_performed = 0u;
    invocation.network_performed = 0u;
    set_string(invocation.mode, sizeof(invocation.mode), "metadata-only");
    invocation.error = LATTICRA_SEAL_SIGNER_INVOCATION_OK;
    set_string(invocation.status, sizeof(invocation.status), "signer-invocation-metadata");
    return invocation;
}

int main(void) {
    latticra_seal_verified_receipt_promotion_t receipt = fixture_receipt();
    latticra_seal_signer_invocation_t invocation = fixture_invocation();
    latticra_seal_signing_operation_t operation;
    latticra_seal_signed_receipt_proof_path_t proof_path;
    char rendered[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_REPORT_MAX];

    if (receipt.error != LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK) {
        return fail("fixture receipt");
    }
    if (latticra_seal_signing_operation_from_invocation(&invocation, "metadata-only", &operation) !=
        LATTICRA_STATUS_OK) {
        return fail("fixture signing operation build");
    }
    if (operation.error != LATTICRA_SEAL_SIGNING_OPERATION_OK) {
        return fail("fixture signing operation");
    }
    if (latticra_seal_signed_receipt_proof_path_from_metadata(&receipt, &operation, &proof_path) !=
        LATTICRA_STATUS_OK) {
        return fail("proof path build");
    }
    if (latticra_seal_signed_receipt_proof_path_is_verification_only(&proof_path) != 1) {
        return fail("proof path verification-only");
    }
    if (latticra_seal_signed_receipt_proof_path_render(&proof_path, rendered, sizeof(rendered)) !=
        LATTICRA_STATUS_OK) {
        return fail("proof path render");
    }

    printf("%s", rendered);
    return 0;
}
