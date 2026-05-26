#include "latticra/seal_operator_receipt_report.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

typedef struct {
    latticra_seal_capability_metadata_result_t capability_metadata;
    latticra_seal_policy_decision_t policy_decision;
    latticra_seal_request_freshness_t request_freshness;
    latticra_seal_signed_request_t signed_request;
    latticra_seal_runtime_dry_run_t runtime_dry_run;
    latticra_seal_operator_receipt_report_sources_t sources;
} operator_receipt_fixture_t;

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static void fill_policy_decision(latticra_seal_policy_decision_t *policy_decision) {
    memset(policy_decision, 0, sizeof(*policy_decision));
    copy_literal(policy_decision->policy_decision_profile,
                 sizeof(policy_decision->policy_decision_profile),
                 "latticra-seal-policy-decision/0.1");
    copy_literal(policy_decision->default_decision,
                 sizeof(policy_decision->default_decision),
                 "deny");
    copy_literal(policy_decision->decision_state,
                 sizeof(policy_decision->decision_state),
                 "report-only");
    policy_decision->decision_denied = 1u;
    policy_decision->operator_review_required = 1u;
    policy_decision->unknown_tool_denied = 1u;
    policy_decision->unsigned_request_denied = 1u;
    policy_decision->invalid_schema_denied = 1u;
    policy_decision->stale_request_denied = 1u;
    policy_decision->replayed_request_denied = 1u;
    policy_decision->invalid_signature_denied = 1u;
    copy_literal(policy_decision->mode, sizeof(policy_decision->mode), "report-only");
    copy_literal(policy_decision->decision, sizeof(policy_decision->decision), "report-only");
    copy_literal(policy_decision->reason,
                 sizeof(policy_decision->reason),
                 "default-deny-policy-decision");
    policy_decision->error = LATTICRA_SEAL_POLICY_DECISION_OK;
    copy_literal(policy_decision->status,
                 sizeof(policy_decision->status),
                 "policy-decision-metadata");
}

static void fill_request_freshness(latticra_seal_request_freshness_t *freshness) {
    memset(freshness, 0, sizeof(*freshness));
    copy_literal(freshness->freshness_profile,
                 sizeof(freshness->freshness_profile),
                 "latticra-seal-request-freshness/0.1");
    copy_literal(freshness->mode, sizeof(freshness->mode), "report-only");
    copy_literal(freshness->decision, sizeof(freshness->decision), "report-only");
    copy_literal(freshness->reason,
                 sizeof(freshness->reason),
                 "request-freshness-metadata");
    freshness->error = LATTICRA_SEAL_REQUEST_FRESHNESS_OK;
    copy_literal(freshness->status,
                 sizeof(freshness->status),
                 "request-freshness-metadata");
}

static void fill_signed_request(latticra_seal_signed_request_t *signed_request) {
    memset(signed_request, 0, sizeof(*signed_request));
    copy_literal(signed_request->signed_request_profile,
                 sizeof(signed_request->signed_request_profile),
                 "latticra-seal-signed-request/0.1");
    copy_literal(signed_request->mode, sizeof(signed_request->mode), "report-only");
    copy_literal(signed_request->decision, sizeof(signed_request->decision), "report-only");
    copy_literal(signed_request->reason,
                 sizeof(signed_request->reason),
                 "signed-request-metadata");
    signed_request->error = LATTICRA_SEAL_SIGNED_REQUEST_OK;
    copy_literal(signed_request->status,
                 sizeof(signed_request->status),
                 "signed-request-metadata");
}

static void fill_runtime_dry_run(latticra_seal_runtime_dry_run_t *dry_run) {
    memset(dry_run, 0, sizeof(*dry_run));
    copy_literal(dry_run->runtime_dry_run_profile,
                 sizeof(dry_run->runtime_dry_run_profile),
                 "latticra-seal-runtime-dry-run/0.1");
    copy_literal(dry_run->request_class, sizeof(dry_run->request_class), "seal.capability.report");
    copy_literal(dry_run->policy_decision_state,
                 sizeof(dry_run->policy_decision_state),
                 "report-only");
    copy_literal(dry_run->runtime_gate_state,
                 sizeof(dry_run->runtime_gate_state),
                 "report-only");
    copy_literal(dry_run->blocked_reason,
                 sizeof(dry_run->blocked_reason),
                 "default-deny-dry-run");
    copy_literal(dry_run->status, sizeof(dry_run->status), "runtime-dry-run-metadata");
    dry_run->dry_run_supported = 1u;
    dry_run->dry_run_performed = 1u;
    dry_run->input_policy_decision_present = 1u;
    dry_run->input_runtime_gate_present = 1u;
    dry_run->policy_decision_report_only = 1u;
    dry_run->runtime_gate_report_only = 1u;
    dry_run->default_action_deny = 1u;
    dry_run->would_deny = 1u;
    dry_run->would_require_operator_review = 1u;
    dry_run->unknown_tool_denied = 1u;
    dry_run->unsigned_request_denied = 1u;
    dry_run->invalid_schema_denied = 1u;
    dry_run->stale_request_denied = 1u;
    dry_run->replayed_request_denied = 1u;
    dry_run->invalid_signature_denied = 1u;
    dry_run->report_only = 1u;
    copy_literal(dry_run->mode, sizeof(dry_run->mode), "report-only");
    dry_run->error = LATTICRA_SEAL_RUNTIME_DRY_RUN_OK;
}

static int fixture_init(operator_receipt_fixture_t *fixture) {
    memset(fixture, 0, sizeof(*fixture));
    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate(
                    "seal.capability.report",
                    &fixture->capability_metadata) == LATTICRA_STATUS_OK,
                "capability metadata fixture");
    fill_policy_decision(&fixture->policy_decision);
    fill_request_freshness(&fixture->request_freshness);
    fill_signed_request(&fixture->signed_request);
    fill_runtime_dry_run(&fixture->runtime_dry_run);
    fixture->sources.capability_metadata = &fixture->capability_metadata;
    fixture->sources.policy_decision = &fixture->policy_decision;
    fixture->sources.request_freshness = &fixture->request_freshness;
    fixture->sources.signed_request = &fixture->signed_request;
    fixture->sources.runtime_dry_run = &fixture->runtime_dry_run;
    return 0;
}

static int complete_sources_produce_denied_receipt(void) {
    operator_receipt_fixture_t fixture;
    latticra_seal_operator_receipt_report_t receipt;

    EXPECT_TRUE(fixture_init(&fixture) == 0, "fixture init");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    &fixture.sources,
                    &receipt) == LATTICRA_STATUS_OK,
                "receipt status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK, "receipt ok");
    EXPECT_TRUE(strcmp(receipt.operator_receipt_profile,
                       "latticra-seal-operator-receipt-report/0.1") == 0,
                "receipt profile");
    EXPECT_TRUE(strcmp(receipt.receipt_mode, "report-only") == 0, "receipt mode");
    EXPECT_TRUE(strcmp(receipt.receipt_status, "denied-report-only") == 0, "receipt status field");
    EXPECT_TRUE(receipt.source_capability_metadata_present == 1u, "capability present");
    EXPECT_TRUE(receipt.source_policy_decision_present == 1u, "policy present");
    EXPECT_TRUE(receipt.source_request_freshness_present == 1u, "freshness present");
    EXPECT_TRUE(receipt.source_signed_request_present == 1u, "signed present");
    EXPECT_TRUE(receipt.source_runtime_dry_run_present == 1u, "dry run present");
    EXPECT_TRUE(receipt.source_denial_reason_present == 1u, "denial reason present");
    EXPECT_TRUE(strcmp(receipt.capability_name, "seal.capability.report") == 0, "capability name");
    EXPECT_TRUE(receipt.capability_known == 1u, "capability known");
    EXPECT_TRUE(receipt.capability_candidate == 1u, "capability candidate");
    EXPECT_TRUE(strcmp(receipt.policy_decision_state, "report-only") == 0, "policy state");
    EXPECT_TRUE(strcmp(receipt.request_freshness_state, "report-only") == 0, "freshness state");
    EXPECT_TRUE(strcmp(receipt.signed_request_state, "report-only") == 0, "signed state");
    EXPECT_TRUE(strcmp(receipt.runtime_dry_run_state, "report-only") == 0, "dry-run state");
    EXPECT_TRUE(receipt.default_action_deny == 1u, "default deny");
    EXPECT_TRUE(receipt.would_allow == 0u, "would allow");
    EXPECT_TRUE(receipt.would_deny == 1u, "would deny");
    EXPECT_TRUE(receipt.would_require_operator_review == 1u, "operator review");
    EXPECT_TRUE(receipt.would_execute_tool == 0u, "execute");
    EXPECT_TRUE(receipt.would_read_host == 0u, "read");
    EXPECT_TRUE(receipt.would_write_host == 0u, "write");
    EXPECT_TRUE(receipt.would_use_network == 0u, "network");
    EXPECT_TRUE(receipt.would_grant_runtime_authority == 0u, "authority");
    EXPECT_TRUE(strcmp(receipt.blocked_reason, "known-capability-candidate-still-denied") == 0,
                "blocked reason");
    EXPECT_TRUE(receipt.receipt_complete == 1u, "complete");
    EXPECT_TRUE(receipt.receipt_invalid == 0u, "invalid");
    EXPECT_TRUE(receipt.report_only == 1u, "report only");
    EXPECT_TRUE(receipt.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(receipt.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(receipt.host_read_performed == 0u, "host read");
    EXPECT_TRUE(receipt.host_write_performed == 0u, "host write");
    EXPECT_TRUE(receipt.network_performed == 0u, "network performed");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_is_report_only(&receipt) == 1,
                "helper");
    return 0;
}

static int render_contains_required_fields(void) {
    operator_receipt_fixture_t fixture;
    latticra_seal_operator_receipt_report_t receipt;
    char rendered[LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MAX];

    EXPECT_TRUE(fixture_init(&fixture) == 0, "fixture init render");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    &fixture.sources,
                    &receipt) == LATTICRA_STATUS_OK,
                "receipt render status");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_render(
                    &receipt,
                    rendered,
                    sizeof(rendered)) == LATTICRA_STATUS_OK,
                "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL OPERATOR RECEIPT REPORT") != 0,
                "render header");
    EXPECT_TRUE(strstr(rendered,
                       "operator_receipt_profile=latticra-seal-operator-receipt-report/0.1") != 0,
                "render profile");
    EXPECT_TRUE(strstr(rendered, "receipt_mode=report-only") != 0, "render mode");
    EXPECT_TRUE(strstr(rendered, "receipt_status=denied-report-only") != 0, "render status");
    EXPECT_TRUE(strstr(rendered, "source_capability_metadata_present=1") != 0,
                "render capability source");
    EXPECT_TRUE(strstr(rendered, "source_policy_decision_present=1") != 0,
                "render policy source");
    EXPECT_TRUE(strstr(rendered, "source_request_freshness_present=1") != 0,
                "render freshness source");
    EXPECT_TRUE(strstr(rendered, "source_signed_request_present=1") != 0,
                "render signed source");
    EXPECT_TRUE(strstr(rendered, "source_runtime_dry_run_present=1") != 0,
                "render dry-run source");
    EXPECT_TRUE(strstr(rendered, "source_denial_reason_present=1") != 0,
                "render denial reason source");
    EXPECT_TRUE(strstr(rendered, "capability_name=seal.capability.report") != 0,
                "render capability");
    EXPECT_TRUE(strstr(rendered, "policy_decision_state=report-only") != 0,
                "render policy");
    EXPECT_TRUE(strstr(rendered, "request_freshness_state=report-only") != 0,
                "render freshness");
    EXPECT_TRUE(strstr(rendered, "signed_request_state=report-only") != 0,
                "render signed");
    EXPECT_TRUE(strstr(rendered, "runtime_dry_run_state=report-only") != 0,
                "render dry run");
    EXPECT_TRUE(strstr(rendered, "would_allow=0") != 0, "render allow");
    EXPECT_TRUE(strstr(rendered, "would_execute_tool=0") != 0, "render execute");
    EXPECT_TRUE(strstr(rendered, "would_grant_runtime_authority=0") != 0,
                "render authority");
    EXPECT_TRUE(strstr(rendered, "receipt_complete=1") != 0, "render complete");
    EXPECT_TRUE(strstr(rendered, "receipt_invalid=0") != 0, "render invalid");
    EXPECT_TRUE(strstr(rendered, "report_only=1") != 0, "render report only");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render no effect");
    EXPECT_TRUE(strstr(rendered, "error=ok") != 0, "render error");
    return 0;
}

static int missing_sources_fail_closed(void) {
    operator_receipt_fixture_t fixture;
    latticra_seal_operator_receipt_report_sources_t sources;
    latticra_seal_operator_receipt_report_t receipt;

    EXPECT_TRUE(fixture_init(&fixture) == 0, "fixture init missing");
    sources = fixture.sources;
    sources.capability_metadata = 0;
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    &sources,
                    &receipt) == LATTICRA_STATUS_OK,
                "missing capability status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA,
                "missing capability error");
    EXPECT_TRUE(receipt.source_capability_metadata_present == 0u, "missing capability present");
    EXPECT_TRUE(receipt.source_policy_decision_present == 1u, "missing policy still present");
    EXPECT_TRUE(receipt.receipt_complete == 0u, "missing complete");
    EXPECT_TRUE(receipt.receipt_invalid == 1u, "missing invalid");
    EXPECT_TRUE(receipt.would_allow == 0u, "missing allow");
    EXPECT_TRUE(receipt.would_deny == 1u, "missing deny");
    EXPECT_TRUE(receipt.runtime_authority_granted == 0u, "missing authority");
    EXPECT_TRUE(receipt.effect_performed == 0u, "missing effect");
    EXPECT_TRUE(strcmp(receipt.blocked_reason, "missing-capability-metadata") == 0,
                "missing reason");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_is_report_only(&receipt) == 0,
                "missing helper");

    sources = fixture.sources;
    sources.runtime_dry_run = 0;
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    &sources,
                    &receipt) == LATTICRA_STATUS_OK,
                "missing dry run status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_RUNTIME_DRY_RUN,
                "missing dry run error");
    EXPECT_TRUE(strcmp(receipt.blocked_reason, "missing-runtime-dry-run") == 0,
                "missing dry run reason");
    return 0;
}

static int effect_allowing_sources_fail_closed(void) {
    operator_receipt_fixture_t fixture;
    latticra_seal_operator_receipt_report_t receipt;

    EXPECT_TRUE(fixture_init(&fixture) == 0, "fixture init effect");
    fixture.capability_metadata.would_allow = 1u;
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    &fixture.sources,
                    &receipt) == LATTICRA_STATUS_OK,
                "effect status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT,
                "effect error");
    EXPECT_TRUE(strcmp(receipt.blocked_reason, "source-would-allow-effect-denied") == 0,
                "effect reason");
    EXPECT_TRUE(receipt.receipt_complete == 0u, "effect complete");
    EXPECT_TRUE(receipt.receipt_invalid == 1u, "effect invalid");
    EXPECT_TRUE(receipt.would_allow == 0u, "effect allow sealed");
    EXPECT_TRUE(receipt.effect_performed == 0u, "effect performed sealed");
    return 0;
}

static int non_report_only_sources_fail_closed(void) {
    operator_receipt_fixture_t fixture;
    latticra_seal_operator_receipt_report_t receipt;

    EXPECT_TRUE(fixture_init(&fixture) == 0, "fixture init non report");
    fixture.runtime_dry_run.dry_run_performed = 0u;
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    &fixture.sources,
                    &receipt) == LATTICRA_STATUS_OK,
                "non report status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE,
                "non report error");
    EXPECT_TRUE(strcmp(receipt.blocked_reason, "non-report-only-source-denied") == 0,
                "non report reason");
    EXPECT_TRUE(receipt.receipt_complete == 0u, "non report complete");
    EXPECT_TRUE(receipt.receipt_invalid == 1u, "non report invalid");
    EXPECT_TRUE(receipt.would_allow == 0u, "non report allow");
    EXPECT_TRUE(receipt.effect_performed == 0u, "non report effect");
    return 0;
}

static int receipt_api_fails_closed(void) {
    operator_receipt_fixture_t fixture;
    latticra_seal_operator_receipt_report_t receipt;
    char tiny[1];

    EXPECT_TRUE(fixture_init(&fixture) == 0, "fixture init api");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    0,
                    &receipt) == LATTICRA_STATUS_OK,
                "null sources status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_INVALID_INPUT,
                "null sources error");
    EXPECT_TRUE(receipt.receipt_invalid == 1u, "null sources invalid");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_from_sources(
                    &fixture.sources,
                    0) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null output");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_is_report_only(0) == 0,
                "null helper");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_render(
                    &receipt,
                    tiny,
                    sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_render(
                    0,
                    tiny,
                    sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null receipt render");
    EXPECT_TRUE(latticra_seal_operator_receipt_report_render(
                    &receipt,
                    0,
                    sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null buffer render");
    return 0;
}

int main(void) {
    if (complete_sources_produce_denied_receipt() != 0) {
        return 1;
    }
    if (render_contains_required_fields() != 0) {
        return 1;
    }
    if (missing_sources_fail_closed() != 0) {
        return 1;
    }
    if (effect_allowing_sources_fail_closed() != 0) {
        return 1;
    }
    if (non_report_only_sources_fail_closed() != 0) {
        return 1;
    }
    if (receipt_api_fails_closed() != 0) {
        return 1;
    }
    printf("seal operator receipt report invariants: ok\n");
    return 0;
}
