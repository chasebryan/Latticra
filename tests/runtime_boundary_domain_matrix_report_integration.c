#include "latticra/runtime_boundary_domain_matrix.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int rbdm_report_renders_known_operational_domain(void) {
    latticra_runtime_boundary_domain_matrix_result_t matrix;
    char report[LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_MAX];

    memset(&matrix, 0, sizeof(matrix));
    matrix.status = LATTICRA_STATUS_OK;
    matrix.cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_OPERATIONAL;
    matrix.domain = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK;
    matrix.domain_known = 1;
    matrix.domain_operational = 1;
    matrix.domain_declarative = 0;
    matrix.domain_future_gated = 0;
    matrix.domain_effect_allowed = 0;
    matrix.domain_authority_available = 1;
    matrix.evidence_level = 2u;

    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_report(&matrix, report, sizeof(report)) == LATTICRA_STATUS_OK, "report status ok");
    EXPECT_TRUE(strstr(report, "LATTICRA RBDM REPORT\n") != 0, "header present");
    EXPECT_TRUE(strstr(report, "cell=operational\n") != 0, "cell present");
    EXPECT_TRUE(strstr(report, "domain=network\n") != 0, "domain present");
    EXPECT_TRUE(strstr(report, "known=1\n") != 0, "known present");
    EXPECT_TRUE(strstr(report, "operational=1\n") != 0, "operational present");
    EXPECT_TRUE(strstr(report, "effect_allowed=0\n") != 0, "effect allowed present");
    EXPECT_TRUE(strstr(report, "evidence_level=2\n") != 0, "evidence present");
    return 0;
}

static int rbdm_report_is_deterministic(void) {
    latticra_runtime_boundary_domain_matrix_result_t matrix;
    char first[LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_MAX];
    char second[LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_MAX];

    memset(&matrix, 0, sizeof(matrix));
    matrix.status = LATTICRA_STATUS_OK;
    matrix.cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE;
    matrix.domain = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST;
    matrix.domain_known = 1;
    matrix.domain_declarative = 1;
    matrix.domain_effect_allowed = 1;
    matrix.domain_authority_available = 1;
    matrix.evidence_level = 2u;

    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_report(&matrix, first, sizeof(first)) == LATTICRA_STATUS_OK, "first report ok");
    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_report(&matrix, second, sizeof(second)) == LATTICRA_STATUS_OK, "second report ok");
    EXPECT_TRUE(strcmp(first, second) == 0, "report deterministic");
    return 0;
}

static int rbdm_report_rejects_null_arguments(void) {
    char report[LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_MAX];
    latticra_runtime_boundary_domain_matrix_result_t matrix;

    memset(&matrix, 0, sizeof(matrix));
    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "null matrix rejected");
    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_report(&matrix, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer rejected");
    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_report(&matrix, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "zero buffer rejected");
    return 0;
}

int main(void) {
    if (rbdm_report_renders_known_operational_domain() != 0) return 1;
    if (rbdm_report_is_deterministic() != 0) return 1;
    if (rbdm_report_rejects_null_arguments() != 0) return 1;
    puts("runtime_boundary_domain_matrix_report_integration: ok");
    return 0;
}
