#include "latticra/seal_report.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int default_report_is_no_effect(void) {
    latticra_seal_report_t report = latticra_seal_report_default();

    EXPECT_TRUE(strcmp(report.seal_profile, "latticra-seal/0.1-report") == 0, "profile");
    EXPECT_TRUE(report.contract_present == 1u, "contract flag");
    EXPECT_TRUE(report.implementation_plan_present == 1u, "plan flag");
    EXPECT_TRUE(report.report_only_supported == 1u, "report flag");
    EXPECT_TRUE(report.measurement_supported == 1u, "measurement flag");
    EXPECT_TRUE(report.signing_supported == 0u, "signing flag");
    EXPECT_TRUE(report.capability_gate_supported == 0u, "capability flag");
    EXPECT_TRUE(report.sealed_objects_supported == 0u, "sealed flag");
    EXPECT_TRUE(latticra_seal_report_is_no_effect(&report) == 1, "no-effect helper");
    EXPECT_TRUE(latticra_seal_report_is_no_effect(0) == 0, "null helper");
    return 0;
}

static int render_report_is_bounded(void) {
    latticra_seal_report_t report = latticra_seal_report_default();
    char rendered[LATTICRA_SEAL_REPORT_MAX];
    char tiny[1];

    EXPECT_TRUE(latticra_seal_report_render(&report, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL REPORT") != 0, "header");
    EXPECT_TRUE(strstr(rendered, "seal_profile=latticra-seal/0.1-report") != 0, "profile render");
    EXPECT_TRUE(strstr(rendered, "report_only_supported=1") != 0, "report render");
    EXPECT_TRUE(strstr(rendered, "measurement_supported=1") != 0, "measurement render");
    EXPECT_TRUE(strstr(rendered, "signing_supported=0") != 0, "signing render");
    EXPECT_TRUE(strstr(rendered, "runtime_granted=0") != 0, "runtime render");
    EXPECT_TRUE(strstr(rendered, "status=report-and-measurement") != 0, "status render");
    EXPECT_TRUE(latticra_seal_report_render(&report, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_report_render(0, rendered, sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report");
    EXPECT_TRUE(latticra_seal_report_render(&report, 0, sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (default_report_is_no_effect() != 0) {
        return 1;
    }
    if (render_report_is_bounded() != 0) {
        return 1;
    }
    printf("seal report invariants: ok\n");
    return 0;
}
