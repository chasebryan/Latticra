#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

#define CHECK_TRUE(value, label) \
    do { \
        if (!(value)) { \
            fprintf(stderr, "FAIL: %s\n", label); \
            return 1; \
        } \
    } while (0)

static latticra_runtime_boundary_authority_summary_t ok_authority(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    authority.no_effect = 1;
    return authority;
}

static latticra_runtime_boundary_request_t request_base(const latticra_runtime_boundary_authority_summary_t *authority) {
    latticra_runtime_boundary_request_t request;
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.runtime_id, sizeof(request.runtime_id), "%s", "runtime-allow");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.authority = authority;
    return request;
}

static int report_mode_allows_report_request(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request = request_base(&authority);
    latticra_runtime_boundary_result_t result;
    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "report status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT, "report policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "report reason");
    CHECK_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED, "report gate");
    CHECK_TRUE(result.record.executed == 0, "report no execution");
    return 0;
}

static int validation_mode_allows_validation_request(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request = request_base(&authority);
    latticra_runtime_boundary_result_t result;
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "validation status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION, "validation policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "validation reason");
    CHECK_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED, "validation gate");
    CHECK_TRUE(result.record.executed == 0, "validation no execution");
    return 0;
}

static int classification_mode_allows_classification_request(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request = request_base(&authority);
    latticra_runtime_boundary_result_t result;
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY;
    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "classification status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION, "classification policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "classification reason");
    CHECK_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED, "classification gate");
    CHECK_TRUE(result.record.executed == 0, "classification no execution");
    return 0;
}

static int mismatched_mode_remains_denied(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request = request_base(&authority);
    latticra_runtime_boundary_result_t result;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "mismatch status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "mismatch policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED, "mismatch reason");
    CHECK_TRUE(result.record.executed == 0, "mismatch no execution");
    return 0;
}

int main(void) {
    if (report_mode_allows_report_request() != 0) return 1;
    if (validation_mode_allows_validation_request() != 0) return 1;
    if (classification_mode_allows_classification_request() != 0) return 1;
    if (mismatched_mode_remains_denied() != 0) return 1;
    puts("runtime_boundary_allow_modes: ok");
    return 0;
}
