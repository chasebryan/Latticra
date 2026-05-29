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

/* Note: domain classification helpers (known_domain etc.) removed from this slice.
   They were unused in current no-effect report paths. Re-add with call sites
   when the full runtime boundary domain matrix evaluator is implemented. */
