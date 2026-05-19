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

static int rb_denied(const latticra_runtime_boundary_result_t *r) {
    return r != 0 &&
           r->record.denial != LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK &&
           !rb_future(r) && !rb_invalid(r);
}

static void rb_dm_default(latticra_runtime_boundary_domain_matrix_result_t *m) {
    if (m == 0) return;
    memset(m, 0, sizeof(*m));
    m->status = LATTICRA_STATUS_OK;
    m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN;
    m->domain = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN;
}

latticra_status_t latticra_runtime_boundary_domain_matrix_evaluate(
    const latticra_runtime_boundary_result_t *r,
    latticra_runtime_boundary_domain_matrix_result_t *m) {
    if (m == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    rb_dm_default(m);
    if (r == 0) {
        m->status = LATTICRA_STATUS_NULL_ARGUMENT;
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    m->domain = r->record.boundary_domain;
    m->domain_known = rb_known(m->domain);
    m->domain_operational = rb_op(m->domain);
    m->domain_declarative = rb_decl(m->domain);
    m->domain_future_gated = rb_future(r);
    m->domain_effect_allowed = r->record.matrix_effect_allowed;
    m->domain_authority_available =
        r->record.authorization_state != LATTICRA_RUNTIME_BOUNDARY_AUTH_UNAVAILABLE &&
        r->record.denial != LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED;

    if (rb_invalid(r)) {
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID;
        m->evidence_level = 0u;
    } else if (!m->domain_known) {
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN;
        m->evidence_level = 0u;
    } else if (m->domain_future_gated) {
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_FUTURE_GATED;
        m->evidence_level = 1u;
    } else if (rb_denied(r)) {
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED;
        m->evidence_level = 1u;
    } else if (m->domain_operational) {
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_OPERATIONAL;
        m->evidence_level = 2u;
    } else if (m->domain_declarative) {
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE;
        m->evidence_level = 2u;
    } else {
        m->cell = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN;
        m->evidence_level = 0u;
    }
    return LATTICRA_STATUS_OK;
}
