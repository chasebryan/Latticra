#include "latticra/seal_capability_metadata.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int missing_capability_stays_denied(void) {
    latticra_seal_capability_metadata_result_t result;

    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate(0, &result) == LATTICRA_STATUS_OK,
                "missing evaluate status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_CAPABILITY_METADATA_OK, "missing ok");
    EXPECT_TRUE(strcmp(result.capability_metadata_profile, "latticra-seal-capability-metadata/0.1") == 0,
                "missing profile");
    EXPECT_TRUE(strcmp(result.capability_fixture_source, "deterministic-local-fixture") == 0,
                "missing source");
    EXPECT_TRUE(result.capability_fixture_entry_count == 3u, "missing entry count");
    EXPECT_TRUE(result.capability_lookup_performed == 1u, "missing lookup");
    EXPECT_TRUE(result.capability_name_present == 0u, "missing name present");
    EXPECT_TRUE(result.capability_known == 0u, "missing known");
    EXPECT_TRUE(result.capability_unknown == 1u, "missing unknown");
    EXPECT_TRUE(result.capability_candidate == 0u, "missing candidate");
    EXPECT_TRUE(result.capability_requires_guarded_allowlist == 1u, "missing allowlist prereq");
    EXPECT_TRUE(result.capability_requires_policy_decision == 1u, "missing policy prereq");
    EXPECT_TRUE(result.capability_requires_runtime_gate == 1u, "missing gate prereq");
    EXPECT_TRUE(result.capability_requires_runtime_dry_run == 1u, "missing dry-run prereq");
    EXPECT_TRUE(result.capability_requires_operator_review == 1u, "missing operator prereq");
    EXPECT_TRUE(result.capability_grants_authority == 0u, "missing authority");
    EXPECT_TRUE(result.capability_executes_tool == 0u, "missing execution");
    EXPECT_TRUE(result.capability_reads_host == 0u, "missing read");
    EXPECT_TRUE(result.capability_writes_host == 0u, "missing write");
    EXPECT_TRUE(result.capability_uses_network == 0u, "missing network");
    EXPECT_TRUE(result.default_action_deny == 1u, "missing default deny");
    EXPECT_TRUE(result.would_allow == 0u, "missing allow");
    EXPECT_TRUE(result.would_deny == 1u, "missing deny");
    EXPECT_TRUE(result.would_require_operator_review == 1u, "missing review");
    EXPECT_TRUE(result.unknown_capability_denied == 1u, "missing unknown cap denied");
    EXPECT_TRUE(result.missing_capability_denied == 1u, "missing cap denied");
    EXPECT_TRUE(result.invalid_capability_denied == 0u, "missing invalid cap denied");
    EXPECT_TRUE(strcmp(result.blocked_reason, "missing-capability-denied") == 0, "missing reason");
    EXPECT_TRUE(result.report_only == 1u, "missing report only");
    EXPECT_TRUE(strcmp(result.mode, "report-only") == 0, "missing mode");
    EXPECT_TRUE(strcmp(result.status, "capability-metadata") == 0, "missing status");
    EXPECT_TRUE(latticra_seal_capability_metadata_is_report_only(&result) == 1, "missing helper");
    return 0;
}

static int unknown_capability_stays_denied(void) {
    latticra_seal_capability_metadata_result_t result;
    char rendered[LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate("unknown.capability", &result) == LATTICRA_STATUS_OK,
                "unknown evaluate status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_CAPABILITY_METADATA_OK, "unknown ok");
    EXPECT_TRUE(strcmp(result.capability_name, "unknown.capability") == 0, "unknown name");
    EXPECT_TRUE(result.capability_name_present == 1u, "unknown name present");
    EXPECT_TRUE(result.capability_known == 0u, "unknown known");
    EXPECT_TRUE(result.capability_unknown == 1u, "unknown unknown");
    EXPECT_TRUE(result.capability_candidate == 0u, "unknown candidate");
    EXPECT_TRUE(result.capability_grants_authority == 0u, "unknown authority");
    EXPECT_TRUE(result.capability_executes_tool == 0u, "unknown execution");
    EXPECT_TRUE(result.capability_reads_host == 0u, "unknown read");
    EXPECT_TRUE(result.capability_writes_host == 0u, "unknown write");
    EXPECT_TRUE(result.capability_uses_network == 0u, "unknown network");
    EXPECT_TRUE(result.would_allow == 0u, "unknown allow");
    EXPECT_TRUE(result.would_deny == 1u, "unknown deny");
    EXPECT_TRUE(result.would_require_operator_review == 1u, "unknown review");
    EXPECT_TRUE(result.unknown_capability_denied == 1u, "unknown denied");
    EXPECT_TRUE(result.missing_capability_denied == 0u, "unknown missing");
    EXPECT_TRUE(strcmp(result.blocked_reason, "default-deny-capability-metadata") == 0, "unknown reason");
    EXPECT_TRUE(latticra_seal_capability_metadata_report(&result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
                "unknown render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL CAPABILITY METADATA") != 0, "unknown render header");
    EXPECT_TRUE(strstr(rendered, "capability_metadata_profile=latticra-seal-capability-metadata/0.1") != 0,
                "unknown render profile");
    EXPECT_TRUE(strstr(rendered, "capability_name=unknown.capability") != 0, "unknown render name");
    EXPECT_TRUE(strstr(rendered, "capability_known=0") != 0, "unknown render known");
    EXPECT_TRUE(strstr(rendered, "capability_unknown=1") != 0, "unknown render unknown");
    EXPECT_TRUE(strstr(rendered, "capability_candidate=0") != 0, "unknown render candidate");
    EXPECT_TRUE(strstr(rendered, "capability_grants_authority=0") != 0, "unknown render authority");
    EXPECT_TRUE(strstr(rendered, "capability_executes_tool=0") != 0, "unknown render execution");
    EXPECT_TRUE(strstr(rendered, "capability_reads_host=0") != 0, "unknown render read");
    EXPECT_TRUE(strstr(rendered, "capability_writes_host=0") != 0, "unknown render write");
    EXPECT_TRUE(strstr(rendered, "capability_uses_network=0") != 0, "unknown render network");
    EXPECT_TRUE(strstr(rendered, "would_allow=0") != 0, "unknown render allow");
    EXPECT_TRUE(strstr(rendered, "would_deny=1") != 0, "unknown render deny");
    return 0;
}

static int known_capability_becomes_candidate_only(void) {
    latticra_seal_capability_metadata_result_t result;
    char rendered[LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate("seal.capability.report", &result) == LATTICRA_STATUS_OK,
                "known evaluate status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_CAPABILITY_METADATA_OK, "known ok");
    EXPECT_TRUE(result.capability_name_present == 1u, "known name present");
    EXPECT_TRUE(result.capability_known == 1u, "known known");
    EXPECT_TRUE(result.capability_unknown == 0u, "known unknown");
    EXPECT_TRUE(result.capability_candidate == 1u, "known candidate");
    EXPECT_TRUE(strcmp(result.capability_scope, "evidence-boundary") == 0, "known scope");
    EXPECT_TRUE(strcmp(result.capability_effect_class, "none") == 0, "known effect");
    EXPECT_TRUE(result.capability_grants_authority == 0u, "known authority");
    EXPECT_TRUE(result.capability_executes_tool == 0u, "known execution");
    EXPECT_TRUE(result.capability_reads_host == 0u, "known read");
    EXPECT_TRUE(result.capability_writes_host == 0u, "known write");
    EXPECT_TRUE(result.capability_uses_network == 0u, "known network");
    EXPECT_TRUE(result.would_allow == 0u, "known allow");
    EXPECT_TRUE(result.would_deny == 1u, "known deny");
    EXPECT_TRUE(result.would_require_operator_review == 1u, "known review");
    EXPECT_TRUE(strcmp(result.blocked_reason, "known-capability-candidate-still-denied") == 0,
                "known reason");
    EXPECT_TRUE(result.report_only == 1u, "known report only");
    EXPECT_TRUE(strcmp(result.mode, "report-only") == 0, "known mode");
    EXPECT_TRUE(latticra_seal_capability_metadata_is_report_only(&result) == 1, "known helper");
    EXPECT_TRUE(latticra_seal_capability_metadata_report(&result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
                "known render");
    EXPECT_TRUE(strstr(rendered, "capability_name=seal.capability.report") != 0, "known render name");
    EXPECT_TRUE(strstr(rendered, "capability_known=1") != 0, "known render known");
    EXPECT_TRUE(strstr(rendered, "capability_unknown=0") != 0, "known render unknown");
    EXPECT_TRUE(strstr(rendered, "capability_candidate=1") != 0, "known render candidate");
    EXPECT_TRUE(strstr(rendered, "blocked_reason=known-capability-candidate-still-denied") != 0,
                "known render reason");
    return 0;
}

static int capability_metadata_fails_closed(void) {
    latticra_seal_capability_metadata_result_t result;
    char tiny[1];
    char rendered[LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_MAX];
    char oversized[LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX + 1u];
    char unterminated[LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX];
    size_t i;

    for (i = 0u; i < LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX; ++i) {
        oversized[i] = 'x';
        unterminated[i] = 'y';
    }
    oversized[LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX] = '\0';

    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate("", &result) == LATTICRA_STATUS_OK,
                "empty capability status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_CAPABILITY_METADATA_OK, "empty capability error");
    EXPECT_TRUE(result.missing_capability_denied == 1u, "empty capability missing");
    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate(oversized, &result) == LATTICRA_STATUS_OK,
                "oversized capability status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME,
                "oversized capability error");
    EXPECT_TRUE(result.invalid_capability_denied == 1u, "oversized invalid denied");
    EXPECT_TRUE(strcmp(result.capability_name, "invalid-capability") == 0,
                "oversized sanitized name");
    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate(unterminated, &result) ==
                    LATTICRA_STATUS_OK,
                "unterminated capability status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME,
                "unterminated capability error");
    EXPECT_TRUE(strcmp(result.capability_name, "invalid-capability") == 0,
                "unterminated sanitized name");
    EXPECT_TRUE(result.invalid_capability_denied == 1u, "unterminated invalid denied");
    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate("seal.capability.inspect", 0) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null output");
    EXPECT_TRUE(latticra_seal_capability_metadata_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_capability_metadata_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_capability_metadata_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null result report");
    EXPECT_TRUE(latticra_seal_capability_metadata_report(&result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "null buffer report");

    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate("seal.capability.report", &result) ==
                    LATTICRA_STATUS_OK,
                "tamper source");
    memset(result.capability_metadata_profile,
           'z',
           sizeof(result.capability_metadata_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_capability_metadata_report(
                    &result,
                    rendered,
                    sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated result render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated result render cleared");
    EXPECT_TRUE(latticra_seal_capability_metadata_is_report_only(&result) == 0,
                "unterminated helper rejected");

    EXPECT_TRUE(latticra_seal_capability_metadata_evaluate("seal.capability.report", &result) ==
                    LATTICRA_STATUS_OK,
                "effect tamper source");
    result.capability_grants_authority = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_capability_metadata_report(
                    &result,
                    rendered,
                    sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT,
                "authority result render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority result render cleared");
    EXPECT_TRUE(latticra_seal_capability_metadata_is_report_only(&result) == 0,
                "authority helper rejected");
    return 0;
}

int main(void) {
    if (missing_capability_stays_denied() != 0) {
        return 1;
    }
    if (unknown_capability_stays_denied() != 0) {
        return 1;
    }
    if (known_capability_becomes_candidate_only() != 0) {
        return 1;
    }
    if (capability_metadata_fails_closed() != 0) {
        return 1;
    }
    printf("seal capability metadata invariants: ok\n");
    return 0;
}
