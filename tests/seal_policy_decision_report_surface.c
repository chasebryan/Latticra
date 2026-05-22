#include "latticra/seal_policy_decision.h"

#include <stdio.h>
#include <string.h>

static latticra_seal_signed_request_t fixture_signed_request(void) {
    latticra_seal_signed_request_t signed_request;
    memset(&signed_request, 0, sizeof(signed_request));
    (void)snprintf(signed_request.signed_request_profile,
                   sizeof(signed_request.signed_request_profile),
                   "%s",
                   "latticra-seal-signed-request/0.1");
    (void)snprintf(signed_request.signed_request_id,
                   sizeof(signed_request.signed_request_id),
                   "%s",
                   "unset");
    (void)snprintf(signed_request.signature_algorithm,
                   sizeof(signed_request.signature_algorithm),
                   "%s",
                   "unset");
    (void)snprintf(signed_request.signing_key_id,
                   sizeof(signed_request.signing_key_id),
                   "%s",
                   "unset");
    (void)snprintf(signed_request.signature_hash,
                   sizeof(signed_request.signature_hash),
                   "%s",
                   "unset");
    signed_request.signed_request_supported = 0u;
    signed_request.signature_generation_supported = 0u;
    signed_request.signature_verification_supported = 0u;
    signed_request.signature_present = 0u;
    signed_request.signature_valid = 0u;
    signed_request.signature_algorithm_declared = 0u;
    signed_request.signing_key_id_present = 0u;
    signed_request.signature_hash_present = 0u;
    signed_request.signed_request_id_present = 0u;
    signed_request.identity_binding_declared = 0u;
    signed_request.context_binding_declared = 0u;
    signed_request.parameter_binding_declared = 0u;
    signed_request.freshness_binding_declared = 0u;
    signed_request.policy_binding_declared = 0u;
    signed_request.trust_store_supported = 0u;
    signed_request.revocation_lookup_supported = 0u;
    signed_request.runtime_authority_granted = 0u;
    signed_request.host_read_performed = 0u;
    signed_request.host_write_performed = 0u;
    signed_request.network_performed = 0u;
    (void)snprintf(signed_request.mode, sizeof(signed_request.mode), "%s", "report-only");
    (void)snprintf(signed_request.decision, sizeof(signed_request.decision), "%s", "report-only");
    (void)snprintf(signed_request.reason,
                   sizeof(signed_request.reason),
                   "%s",
                   "signed-request-metadata-only");
    signed_request.error = LATTICRA_SEAL_SIGNED_REQUEST_OK;
    (void)snprintf(signed_request.status,
                   sizeof(signed_request.status),
                   "%s",
                   "signed-request-metadata");
    return signed_request;
}

int main(void) {
    latticra_seal_signed_request_t signed_request = fixture_signed_request();
    latticra_seal_policy_decision_t policy_decision;
    char rendered[LATTICRA_SEAL_POLICY_DECISION_REPORT_MAX];

    if (latticra_seal_policy_decision_from_signed_request(&signed_request, &policy_decision) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal policy decision metadata\n");
        return 1;
    }

    if (policy_decision.error != LATTICRA_SEAL_POLICY_DECISION_OK) {
        fprintf(stderr,
                "invalid Seal policy decision metadata: %s\n",
                latticra_seal_policy_decision_error_label(policy_decision.error));
        return 1;
    }

    if (latticra_seal_policy_decision_report(&policy_decision, rendered, sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal policy decision report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}
