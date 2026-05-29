#include "latticra/seal_guarded_allowlist.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int unknown_tool_stays_denied(void) {
    latticra_seal_guarded_allowlist_result_t result;
    char rendered[LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate("unknown.tool", &result) == LATTICRA_STATUS_OK,
                "unknown evaluate status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_GUARDED_ALLOWLIST_OK, "unknown result ok");
    EXPECT_TRUE(strcmp(result.guarded_allowlist_profile, "latticra-seal-guarded-allowlist/0.1") == 0,
                "unknown profile");
    EXPECT_TRUE(strcmp(result.tool_name, "unknown.tool") == 0, "unknown tool name");
    EXPECT_TRUE(strcmp(result.allowlist_source, "deterministic-local-fixture") == 0,
                "unknown source");
    EXPECT_TRUE(result.allowlist_entry_count == 3u, "unknown entry count");
    EXPECT_TRUE(result.allowlist_lookup_performed == 1u, "unknown lookup");
    EXPECT_TRUE(result.requested_tool_name_present == 1u, "unknown name present");
    EXPECT_TRUE(result.requested_tool_known == 0u, "unknown known");
    EXPECT_TRUE(result.requested_tool_unknown == 1u, "unknown unknown");
    EXPECT_TRUE(result.requested_tool_candidate == 0u, "unknown candidate");
    EXPECT_TRUE(result.requested_tool_allow_candidate == 0u, "unknown allow candidate");
    EXPECT_TRUE(result.allow_candidate_requires_policy_decision == 1u, "unknown policy prereq");
    EXPECT_TRUE(result.allow_candidate_requires_runtime_gate == 1u, "unknown gate prereq");
    EXPECT_TRUE(result.allow_candidate_requires_runtime_dry_run == 1u, "unknown dry-run prereq");
    EXPECT_TRUE(result.allow_candidate_requires_operator_review == 1u, "unknown operator prereq");
    EXPECT_TRUE(result.allow_candidate_grants_authority == 0u, "unknown authority");
    EXPECT_TRUE(result.allow_candidate_executes_tool == 0u, "unknown execution");
    EXPECT_TRUE(result.allow_candidate_reads_host == 0u, "unknown host read");
    EXPECT_TRUE(result.allow_candidate_writes_host == 0u, "unknown host write");
    EXPECT_TRUE(result.allow_candidate_uses_network == 0u, "unknown network");
    EXPECT_TRUE(result.default_action_deny == 1u, "unknown default deny");
    EXPECT_TRUE(result.would_allow == 0u, "unknown would allow");
    EXPECT_TRUE(result.would_deny == 1u, "unknown would deny");
    EXPECT_TRUE(result.would_require_operator_review == 1u, "unknown review");
    EXPECT_TRUE(strcmp(result.blocked_reason, "default-deny-guarded-allowlist") == 0,
                "unknown reason");
    EXPECT_TRUE(result.report_only == 1u, "unknown report only");
    EXPECT_TRUE(strcmp(result.mode, "report-only") == 0, "unknown mode");
    EXPECT_TRUE(strcmp(result.status, "guarded-allowlist-metadata") == 0, "unknown status");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_is_report_only(&result) == 1,
                "unknown helper");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(&result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
                "unknown render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL GUARDED ALLOWLIST") != 0, "unknown render header");
    EXPECT_TRUE(strstr(rendered, "guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1") != 0,
                "unknown render profile");
    EXPECT_TRUE(strstr(rendered, "tool_name=unknown.tool") != 0, "unknown render name");
    EXPECT_TRUE(strstr(rendered, "requested_tool_known=0") != 0, "unknown render known");
    EXPECT_TRUE(strstr(rendered, "requested_tool_unknown=1") != 0, "unknown render unknown");
    EXPECT_TRUE(strstr(rendered, "requested_tool_candidate=0") != 0, "unknown render candidate");
    EXPECT_TRUE(strstr(rendered, "would_allow=0") != 0, "unknown render allow");
    EXPECT_TRUE(strstr(rendered, "would_deny=1") != 0, "unknown render deny");
    EXPECT_TRUE(strstr(rendered, "allow_candidate_grants_authority=0") != 0,
                "unknown render authority");
    EXPECT_TRUE(strstr(rendered, "allow_candidate_executes_tool=0") != 0,
                "unknown render execute");
    EXPECT_TRUE(strstr(rendered, "allow_candidate_reads_host=0") != 0, "unknown render read");
    EXPECT_TRUE(strstr(rendered, "allow_candidate_writes_host=0") != 0, "unknown render write");
    EXPECT_TRUE(strstr(rendered, "allow_candidate_uses_network=0") != 0, "unknown render network");
    return 0;
}

static int known_tool_becomes_candidate_only(void) {
    latticra_seal_guarded_allowlist_result_t result;
    char rendered[LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate("latticra.seal.report", &result) == LATTICRA_STATUS_OK,
                "known evaluate status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_GUARDED_ALLOWLIST_OK, "known result ok");
    EXPECT_TRUE(result.requested_tool_known == 1u, "known known");
    EXPECT_TRUE(result.requested_tool_unknown == 0u, "known unknown");
    EXPECT_TRUE(result.requested_tool_candidate == 1u, "known candidate");
    EXPECT_TRUE(result.requested_tool_allow_candidate == 1u, "known allow candidate");
    EXPECT_TRUE(result.allow_candidate_grants_authority == 0u, "known authority");
    EXPECT_TRUE(result.allow_candidate_executes_tool == 0u, "known execution");
    EXPECT_TRUE(result.allow_candidate_reads_host == 0u, "known read");
    EXPECT_TRUE(result.allow_candidate_writes_host == 0u, "known write");
    EXPECT_TRUE(result.allow_candidate_uses_network == 0u, "known network");
    EXPECT_TRUE(result.would_allow == 0u, "known would allow");
    EXPECT_TRUE(result.would_deny == 1u, "known would deny");
    EXPECT_TRUE(result.would_require_operator_review == 1u, "known review");
    EXPECT_TRUE(strcmp(result.blocked_reason, "known-tool-candidate-still-denied") == 0,
                "known reason");
    EXPECT_TRUE(result.report_only == 1u, "known report only");
    EXPECT_TRUE(strcmp(result.mode, "report-only") == 0, "known mode");
    EXPECT_TRUE(strcmp(result.status, "guarded-allowlist-metadata") == 0, "known status");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_is_report_only(&result) == 1,
                "known helper");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(&result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
                "known render");
    EXPECT_TRUE(strstr(rendered, "tool_name=latticra.seal.report") != 0, "known render name");
    EXPECT_TRUE(strstr(rendered, "requested_tool_known=1") != 0, "known render known");
    EXPECT_TRUE(strstr(rendered, "requested_tool_unknown=0") != 0, "known render unknown");
    EXPECT_TRUE(strstr(rendered, "requested_tool_candidate=1") != 0, "known render candidate");
    EXPECT_TRUE(strstr(rendered, "requested_tool_allow_candidate=1") != 0,
                "known render allow candidate");
    EXPECT_TRUE(strstr(rendered, "blocked_reason=known-tool-candidate-still-denied") != 0,
                "known render reason");
    EXPECT_TRUE(strstr(rendered, "would_allow=0") != 0, "known render allow");
    EXPECT_TRUE(strstr(rendered, "would_deny=1") != 0, "known render deny");
    EXPECT_TRUE(strstr(rendered, "allow_candidate_grants_authority=0") != 0,
                "known render authority");
    return 0;
}

static int guarded_allowlist_fails_closed(void) {
    latticra_seal_guarded_allowlist_result_t result;
    char tiny[1];
    char rendered[LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_MAX];
    char oversized[LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX + 1u];
    char unterminated[LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX];
    size_t i;

    for (i = 0u; i < LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX; ++i) {
        oversized[i] = 'x';
        unterminated[i] = 'y';
    }
    oversized[LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX] = '\0';

    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate(0, &result) == LATTICRA_STATUS_OK,
                "null tool status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME,
                "null tool error");
    EXPECT_TRUE(result.requested_tool_name_present == 0u, "null tool absent");
    EXPECT_TRUE(result.would_deny == 1u, "null tool denied");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate("", &result) == LATTICRA_STATUS_OK,
                "empty tool status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME,
                "empty tool error");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate(oversized, &result) == LATTICRA_STATUS_OK,
                "oversized tool status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME,
                "oversized tool error");
    EXPECT_TRUE(strcmp(result.tool_name, "invalid-tool") == 0, "oversized sanitized name");
    EXPECT_TRUE(result.requested_tool_name_present == 1u, "oversized tool present");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate(unterminated, &result) == LATTICRA_STATUS_OK,
                "unterminated tool status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME,
                "unterminated tool error");
    EXPECT_TRUE(strcmp(result.tool_name, "invalid-tool") == 0, "unterminated sanitized name");
    EXPECT_TRUE(result.requested_tool_name_present == 1u, "unterminated tool present");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate("latticra.seal.inspect", 0) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null output");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null result report");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(&result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null buffer report");

    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate("latticra.seal.report", &result) == LATTICRA_STATUS_OK,
                "tamper source");
    memset(result.guarded_allowlist_profile,
           'z',
           sizeof(result.guarded_allowlist_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(&result, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated result render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated result render cleared");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_is_report_only(&result) == 0,
                "unterminated helper rejected");

    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate("latticra.seal.report", &result) == LATTICRA_STATUS_OK,
                "authority tamper source");
    result.allow_candidate_grants_authority = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(&result, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority result render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority result render cleared");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_is_report_only(&result) == 0,
                "authority helper rejected");

    EXPECT_TRUE(latticra_seal_guarded_allowlist_evaluate("latticra.seal.report", &result) == LATTICRA_STATUS_OK,
                "entry count tamper source");
    result.allowlist_entry_count = LATTICRA_SEAL_GUARDED_ALLOWLIST_ENTRY_MAX + 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_guarded_allowlist_report(&result, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "entry count result render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "entry count result render cleared");
    EXPECT_TRUE(latticra_seal_guarded_allowlist_is_report_only(&result) == 0,
                "entry count helper rejected");
    return 0;
}

int main(void) {
    if (unknown_tool_stays_denied() != 0) {
        return 1;
    }
    if (known_tool_becomes_candidate_only() != 0) {
        return 1;
    }
    if (guarded_allowlist_fails_closed() != 0) {
        return 1;
    }
    printf("seal guarded allowlist invariants: ok\n");
    return 0;
}
