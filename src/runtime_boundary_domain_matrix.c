#include "latticra/runtime_boundary_domain_matrix.h"

#include <stdio.h>
#include <string.h>

const char *latticra_runtime_boundary_domain_matrix_cell_label(
    latticra_runtime_boundary_domain_matrix_cell_t cell) {
    switch (cell) {
    case LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE: return "declarative";
    case LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_OPERATIONAL: return "operational";
    case LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_FUTURE_GATED: return "future-gated";
    case LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED: return "blocked";
    case LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID: return "invalid";
    case LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN:
    default: return "unknown";
    }
}

static int known_domain(latticra_runtime_boundary_domain_t domain) {
    return domain != LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN;
}

static int operational_domain(latticra_runtime_boundary_domain_t domain) {
    return domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_FILESYSTEM ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PROCESS ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_DEVICE ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_EXTERNAL_CALL ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PERSISTENCE;
}

static int declarative_domain(latticra_runtime_boundary_domain_t domain) {
    return domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MEMORY ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_CLOCK ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_RANDOMNESS ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST ||
           domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_SCHEDULER;
}
