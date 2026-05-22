#include "latticra/seal_runtime_dry_run.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

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

static int dry_run_stays_report_only_and_denied(void) {
    latticra_seal_signed_request_t signed_request = fixture_signed_request();
    latticra_seal_policy_decision_t policy_decision;
    latticra_seal_runtime_gate_t runtime_gate;
    latticra_seal_runtime_dry_run_t dry_run;
    char rendered[LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_policy_decision_from_signed_request(&signed_request, &policy_decision) == LATTICRA_STATUS_OK,
                "policy decision status");
    EXPECT_TRUE(latticra_seal_runtime_gate_from_policy_decision(&policy_decision, &runtime_gate) == LATTICRA_STATUS_OK,
                "runtime gate status");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_from_policy_and_gate(&policy_decision, &runtime_gate, &dry_run) == LATTICRA_STATUS_OK,
                "dry run status");
    EXPECT_TRUE(dry_run.error == LATTICRA_SEAL_RUNTIME_DRY_RUN_OK, "dry run ok");
    EXPECT_TRUE(strcmp(dry_run.runtime_dry_run_profile, "latticra-seal-runtime-dry-run/0.1") == 0,
                "dry run profile");
    EXPECT_TRUE(strcmp(dry_run.request_class, "core-blocked-request") == 0, "request class");
    EXPECT_TRUE(strcmp(dry_run.policy_decision_state, "report-only") == 0, "policy state");
    EXPECT_TRUE(strcmp(dry_run.runtime_gate_state, "report-only") == 0, "gate state");
    EXPECT_TRUE(strcmp(dry_run.blocked_reason, "default-deny-dry-run") == 0, "blocked reason");
    EXPECT_TRUE(strcmp(dry_run.status, "runtime-dry-run-metadata") == 0, "status");
    EXPECT_TRUE(dry_run.dry_run_supported == 1u, "dry run supported");
    EXPECT_TRUE(dry_run.dry_run_performed == 1u, "dry run performed");
    EXPECT_TRUE(dry_run.input_policy_decision_present == 1u, "policy input");
    EXPECT_TRUE(dry_run.input_runtime_gate_present == 1u, "gate input");
    EXPECT_TRUE(dry_run.policy_decision_report_only == 1u, "policy report only");
    EXPECT_TRUE(dry_run.runtime_gate_report_only == 1u, "gate report only");
    EXPECT_TRUE(dry_run.default_action_deny == 1u, "default deny");
    EXPECT_TRUE(dry_run.would_allow == 0u, "would allow");
    EXPECT_TRUE(dry_run.would_deny == 1u, "would deny");
    EXPECT_TRUE(dry_run.would_require_operator_review == 1u, "operator review");
    EXPECT_TRUE(dry_run.would_execute_tool == 0u, "tool execution");
    EXPECT_TRUE(dry_run.would_read_host == 0u, "host read");
    EXPECT_TRUE(dry_run.would_write_host == 0u, "host write");
    EXPECT_TRUE(dry_run.would_use_network == 0u, "network");
    EXPECT_TRUE(dry_run.would_grant_runtime_authority == 0u, "authority");
    EXPECT_TRUE(dry_run.unknown_tool_denied == 1u, "unknown tool");
    EXPECT_TRUE(dry_run.unsigned_request_denied == 1u, "unsigned request");
    EXPECT_TRUE(dry_run.invalid_schema_denied == 1u, "invalid schema");
    EXPECT_TRUE(dry_run.stale_request_denied == 1u, "stale request");
    EXPECT_TRUE(dry_run.replayed_request_denied == 1u, "replayed request");
    EXPECT_TRUE(dry_run.invalid_signature_denied == 1u, "invalid signature");
    EXPECT_TRUE(dry_run.report_only == 1u, "report only");
    EXPECT_TRUE(strcmp(dry_run.mode, "report-only") == 0, "mode");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_is_report_only(&dry_run) == 1, "report-only helper");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_report(&dry_run, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
                "report render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL RUNTIME DRY RUN") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1") != 0,
                "render profile");
    EXPECT_TRUE(strstr(rendered, "request_class=core-blocked-request") != 0, "render request class");
    EXPECT_TRUE(strstr(rendered, "blocked_reason=default-deny-dry-run") != 0, "render reason");
    EXPECT_TRUE(strstr(rendered, "would_allow=0") != 0, "render allow");
    EXPECT_TRUE(strstr(rendered, "would_deny=1") != 0, "render deny");
    EXPECT_TRUE(strstr(rendered, "would_execute_tool=0") != 0, "render tool");
    EXPECT_TRUE(strstr(rendered, "would_read_host=0") != 0, "render read");
    EXPECT_TRUE(strstr(rendered, "would_write_host=0") != 0, "render write");
    EXPECT_TRUE(strstr(rendered, "would_use_network=0") != 0, "render network");
    EXPECT_TRUE(strstr(rendered, "would_grant_runtime_authority=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "status=runtime-dry-run-metadata") != 0, "render status");
    return 0;
}

static int dry_run_fails_closed(void) {
    latticra_seal_signed_request_t signed_request = fixture_signed_request();
    latticra_seal_policy_decision_t policy_decision;
    latticra_seal_runtime_gate_t runtime_gate;
    latticra_seal_runtime_dry_run_t dry_run;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_policy_decision_from_signed_request(&signed_request, &policy_decision) == LATTICRA_STATUS_OK,
                "policy decision status");
    EXPECT_TRUE(latticra_seal_runtime_gate_from_policy_decision(&policy_decision, &runtime_gate) == LATTICRA_STATUS_OK,
                "runtime gate status");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_from_policy_and_gate(0, &runtime_gate, &dry_run) == LATTICRA_STATUS_OK,
                "null policy status");
    EXPECT_TRUE(dry_run.error == LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_INPUT, "null policy error");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_from_policy_and_gate(&policy_decision, 0, &dry_run) == LATTICRA_STATUS_OK,
                "null gate status");
    EXPECT_TRUE(dry_run.error == LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_INPUT, "null gate error");
    policy_decision.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_runtime_dry_run_from_policy_and_gate(&policy_decision, &runtime_gate, &dry_run) == LATTICRA_STATUS_OK,
                "invalid policy status");
    EXPECT_TRUE(dry_run.error == LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_POLICY_DECISION, "invalid policy error");
    policy_decision = (latticra_seal_policy_decision_t){0};
    EXPECT_TRUE(latticra_seal_policy_decision_from_signed_request(&signed_request, &policy_decision) == LATTICRA_STATUS_OK,
                "policy decision reset");
    runtime_gate.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_runtime_dry_run_from_policy_and_gate(&policy_decision, &runtime_gate, &dry_run) == LATTICRA_STATUS_OK,
                "invalid gate status");
    EXPECT_TRUE(dry_run.error == LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_RUNTIME_GATE, "invalid gate error");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_from_policy_and_gate(&policy_decision, &runtime_gate, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null output");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_report(&dry_run, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null dry run");
    EXPECT_TRUE(latticra_seal_runtime_dry_run_report(&dry_run, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null buffer");
    return 0;
}

int main(void) {
    if (dry_run_stays_report_only_and_denied() != 0) {
        return 1;
    }
    if (dry_run_fails_closed() != 0) {
        return 1;
    }
    printf("seal runtime dry-run invariants: ok\n");
    return 0;
}
