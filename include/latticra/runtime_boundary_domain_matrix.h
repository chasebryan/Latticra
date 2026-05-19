#ifndef LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_H
#define LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_H

#include "latticra/runtime_boundary.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_MAX 2048u

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE = 0,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_OPERATIONAL = 1,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_FUTURE_GATED = 2,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED = 3,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID = 4,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN = 5
} latticra_runtime_boundary_domain_matrix_cell_t;

typedef struct {
    latticra_status_t status;
    latticra_runtime_boundary_domain_matrix_cell_t cell;
    latticra_runtime_boundary_domain_t domain;
    int domain_known;
    int domain_operational;
    int domain_declarative;
    int domain_future_gated;
    int domain_effect_allowed;
    int domain_authority_available;
    unsigned int evidence_level;
} latticra_runtime_boundary_domain_matrix_result_t;

const char *latticra_runtime_boundary_domain_matrix_cell_label(
    latticra_runtime_boundary_domain_matrix_cell_t cell);

latticra_status_t latticra_runtime_boundary_domain_matrix_evaluate(
    const latticra_runtime_boundary_result_t *boundary_result,
    latticra_runtime_boundary_domain_matrix_result_t *matrix_result);

latticra_status_t latticra_runtime_boundary_domain_matrix_report(
    const latticra_runtime_boundary_domain_matrix_result_t *matrix_result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
