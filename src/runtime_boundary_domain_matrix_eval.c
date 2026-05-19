#include "latticra/runtime_boundary_domain_matrix.h"

#include <string.h>

static int rb_known(latticra_runtime_boundary_domain_t d) {
    return d != LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN;
}

static int rb_op(latticra_runtime_boundary_domain_t d) {
    return d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_FILESYSTEM ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PROCESS ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_DEVICE ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_EXTERNAL_CALL ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PERSISTENCE;
}

static int rb_decl(latticra_runtime_boundary_domain_t d) {
    return d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MEMORY ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_CLOCK ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_RANDOMNESS ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST ||
           d == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_SCHEDULER;
}

static int rb_invalid(const latticra_runtime_boundary_result_t *r) {
    return r == 0 ||
           r->record.report_classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_INVALID ||
           r->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT ||
           r->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST ||
           r->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT;
}

static int rb_future(const latticra_runtime_boundary_result_t *r) {
    return r != 0 &&
           (r->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE ||
            r->record.policy_matrix_cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION ||
            r->record.authorization_state == LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE);
}
