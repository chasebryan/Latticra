#include "latticra/seal_signed_receipt_proof_path.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

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
    set_string(result.message_label, sizeof(result.message_label), "signed-receipt-proof-fixture");
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
    set_string(invocation.message_digest_algorithm, sizeof(invocation.message_digest_algorithm), "SHA-256");
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
    set_string(invocation.requested_scope, sizeof(invocation.requested_scope), "local-proof-fixture");
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

static latticra_seal_signing_operation_t fixture_operation(void) {
    latticra_seal_signer_invocation_t invocation = fixture_invocation();
    latticra_seal_signing_operation_t operation;

    (void)latticra_seal_signing_operation_from_invocation(&invocation, "metadata-only", &operation);
    return operation;
}

static int proof_path_allows_verification_only_summary(void) {
    latticra_seal_verified_receipt_promotion_t receipt = fixture_receipt();
    latticra_seal_signing_operation_t operation = fixture_operation();
    latticra_seal_signed_receipt_proof_path_t proof_path;
    char rendered[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_REPORT_MAX];

    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK, "fixture receipt");
    EXPECT_TRUE(operation.error == LATTICRA_SEAL_SIGNING_OPERATION_OK, "fixture operation");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_from_metadata(
                    &receipt,
                    &operation,
                    &proof_path) == LATTICRA_STATUS_OK,
                "proof path status");
    EXPECT_TRUE(proof_path.error == LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_OK, "proof path ok");
    EXPECT_TRUE(strcmp(proof_path.proof_path_profile,
                       "latticra-seal-signed-receipt-proof-path/0.1") == 0,
                "proof path profile");
    EXPECT_TRUE(strcmp(proof_path.receipt_profile, "latticra-seal-verified-receipt/0.1") == 0,
                "receipt profile");
    EXPECT_TRUE(strcmp(proof_path.verify_profile, "latticra-seal-ed25519-verify/0.1") == 0,
                "verify profile");
    EXPECT_TRUE(strcmp(proof_path.signing_operation_profile,
                       "latticra-seal-signing-operation/0.1") == 0,
                "operation profile");
    EXPECT_TRUE(strcmp(proof_path.message_digest_hex, receipt.message_digest_hex) == 0,
                "digest copy");
    EXPECT_TRUE(strcmp(proof_path.public_key_identity_label,
                       "local-development-proof-key") == 0,
                "public key copy");
    EXPECT_TRUE(strcmp(proof_path.proof_path_state, "verification-only") == 0,
                "proof path state");
    EXPECT_TRUE(proof_path.local_verify_result_present == 1u, "local verify present");
    EXPECT_TRUE(proof_path.receipt_promotion_present == 1u, "receipt promotion present");
    EXPECT_TRUE(proof_path.signing_operation_present == 1u, "operation present");
    EXPECT_TRUE(proof_path.receipt_verified == 1u, "receipt verified");
    EXPECT_TRUE(proof_path.signing_operation_ready == 1u, "operation ready");
    EXPECT_TRUE(proof_path.signing_operation_metadata_only == 1u, "operation metadata only");
    EXPECT_TRUE(proof_path.digest_matches == 1u, "digest matches");
    EXPECT_TRUE(proof_path.public_key_matches == 1u, "public key matches");
    EXPECT_TRUE(proof_path.trust_root_required == 1u, "trust root required");
    EXPECT_TRUE(proof_path.trust_root_verified == 0u, "trust root absent");
    EXPECT_TRUE(proof_path.revocation_required == 1u, "revocation required");
    EXPECT_TRUE(proof_path.revocation_checked == 0u, "revocation absent");
    EXPECT_TRUE(proof_path.verification_only == 1u, "verification only");
    EXPECT_TRUE(proof_path.proof_path_verified == 0u, "production proof absent");
    EXPECT_TRUE(proof_path.authority_usable == 0u, "authority absent");
    EXPECT_TRUE(proof_path.capability_gate_allowed == 0u, "capability absent");
    EXPECT_TRUE(proof_path.runtime_authority_granted == 0u, "runtime absent");
    EXPECT_TRUE(proof_path.signature_performed == 0u, "signature absent");
    EXPECT_TRUE(proof_path.signer_invoked == 0u, "signer absent");
    EXPECT_TRUE(proof_path.private_key_handling == 0u, "private key absent");
    EXPECT_TRUE(proof_path.key_generation_performed == 0u, "keygen absent");
    EXPECT_TRUE(proof_path.trust_store_loaded == 0u, "trust store absent");
    EXPECT_TRUE(proof_path.revocation_lookup_performed == 0u, "revocation lookup absent");
    EXPECT_TRUE(proof_path.effect_performed == 0u, "effect absent");
    EXPECT_TRUE(proof_path.host_read_performed == 0u, "host read absent");
    EXPECT_TRUE(proof_path.host_write_performed == 0u, "host write absent");
    EXPECT_TRUE(proof_path.network_performed == 0u, "network absent");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_is_verification_only(&proof_path) == 1,
                "verification-only helper");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_render(
                    &proof_path,
                    rendered,
                    sizeof(rendered)) == LATTICRA_STATUS_OK,
                "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNED RECEIPT PROOF PATH") != NULL,
                "render header");
    EXPECT_TRUE(strstr(rendered, "proof_path_state=verification-only") != NULL,
                "render state");
    EXPECT_TRUE(strstr(rendered, "digest_matches=1") != NULL, "render digest");
    EXPECT_TRUE(strstr(rendered, "public_key_matches=1") != NULL, "render key");
    EXPECT_TRUE(strstr(rendered, "trust_root_verified=0") != NULL, "render trust root");
    EXPECT_TRUE(strstr(rendered, "revocation_checked=0") != NULL, "render revocation");
    EXPECT_TRUE(strstr(rendered, "proof_path_verified=0") != NULL, "render proof");
    EXPECT_TRUE(strstr(rendered, "authority_usable=0") != NULL, "render authority");
    EXPECT_TRUE(strstr(rendered, "signature_performed=0") != NULL, "render signature");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != NULL, "render network");
    EXPECT_TRUE(strstr(rendered, "status=signed-receipt-proof-path-verification-only") != NULL,
                "render status field");
    proof_path.signer_invocation_profile[0] = '\0';
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_is_verification_only(&proof_path) == 0,
                "empty proof path metadata rejected");
    return 0;
}

static int expect_error(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    const latticra_seal_signing_operation_t *operation,
    latticra_seal_signed_receipt_proof_path_error_t expected_error,
    const char *expected_state,
    const char *message) {
    latticra_seal_signed_receipt_proof_path_t proof_path;

    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_from_metadata(
                    receipt,
                    operation,
                    &proof_path) == LATTICRA_STATUS_OK,
                message);
    EXPECT_TRUE(proof_path.error == expected_error, "expected error");
    EXPECT_TRUE(strcmp(proof_path.proof_path_state, expected_state) == 0, "expected state");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_is_verification_only(&proof_path) == 0,
                "denied helper");
    return 0;
}

static int proof_path_fails_closed(void) {
    latticra_seal_verified_receipt_promotion_t receipt = fixture_receipt();
    latticra_seal_signing_operation_t operation = fixture_operation();
    latticra_seal_signed_receipt_proof_path_t proof_path;
    char tiny[1];
    char rendered[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_from_metadata(
                    NULL,
                    &operation,
                    &proof_path) == LATTICRA_STATUS_OK,
                "null receipt status");
    EXPECT_TRUE(proof_path.error == LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_INPUT,
                "null receipt error");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_from_metadata(
                    &receipt,
                    &operation,
                    NULL) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null output");
    receipt = fixture_receipt();
    receipt.verified = 0u;
    if (expect_error(&receipt,
                     &operation,
                     LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_NOT_VERIFIED,
                     "receipt-not-verified",
                     "receipt not verified") != 0) {
        return 1;
    }
    receipt = fixture_receipt();
    receipt.authority_usable = 1u;
    if (expect_error(&receipt,
                     &operation,
                     LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_AUTHORITY_NOT_NEUTRAL,
                     "receipt-authority-not-neutral",
                     "receipt authority") != 0) {
        return 1;
    }
    receipt = fixture_receipt();
    operation = fixture_operation();
    set_string(operation.message_digest_hex, sizeof(operation.message_digest_hex), "bbbb");
    if (expect_error(&receipt,
                     &operation,
                     LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MISMATCH,
                     "digest-mismatch",
                     "digest mismatch") != 0) {
        return 1;
    }
    operation = fixture_operation();
    set_string(operation.public_key_identity_label,
               sizeof(operation.public_key_identity_label),
               "different-key");
    if (expect_error(&receipt,
                     &operation,
                     LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PUBLIC_KEY_MISMATCH,
                     "public-key-mismatch",
                     "public key mismatch") != 0) {
        return 1;
    }
    operation = fixture_operation();
    operation.private_key_handling = 1u;
    if (expect_error(&receipt,
                     &operation,
                     LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SIGNING_OPERATION_NOT_METADATA_ONLY,
                     "signing-operation-not-metadata-only",
                     "operation not metadata") != 0) {
        return 1;
    }
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_error_label(
                    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PUBLIC_KEY_MISMATCH) != NULL,
                "error label");
    EXPECT_TRUE(strcmp(latticra_seal_signed_receipt_proof_path_error_label(
                           (latticra_seal_signed_receipt_proof_path_error_t)99),
                       "unknown") == 0,
                "unknown label");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_render(NULL,
                                                               rendered,
                                                               sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null render proof");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_render(&proof_path,
                                                               NULL,
                                                               sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null render buffer");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_render(&proof_path,
                                                               rendered,
                                                               0u) ==
                    LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "zero render buffer");
    receipt = fixture_receipt();
    operation = fixture_operation();
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_from_metadata(
                    &receipt,
                    &operation,
                    &proof_path) == LATTICRA_STATUS_OK,
                "small render fixture");
    EXPECT_TRUE(latticra_seal_signed_receipt_proof_path_render(&proof_path,
                                                               tiny,
                                                               sizeof(tiny)) ==
                    LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "small render buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small render cleared");
    return 0;
}

int main(void) {
    if (proof_path_allows_verification_only_summary() != 0) {
        return 1;
    }
    if (proof_path_fails_closed() != 0) {
        return 1;
    }
    printf("seal signed receipt proof path invariants: ok\n");
    return 0;
}
