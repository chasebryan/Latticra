#include "latticra/runtime_boundary_domain_matrix.h"

#include <stdio.h>

latticra_status_t latticra_runtime_boundary_domain_matrix_report(
    const latticra_runtime_boundary_domain_matrix_result_t *m,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (m == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA RBDM REPORT\n"
        "status=%d\n"
        "cell=%s\n"
        "domain=%s\n"
        "known=%d\n"
        "operational=%d\n"
        "declarative=%d\n"
        "future_gated=%d\n"
        "effect_allowed=%d\n"
        "authority_available=%d\n"
        "evidence_level=%u\n"
        "effect_blocked=%d\n",
        (int)m->status,
        latticra_runtime_boundary_domain_matrix_cell_label(m->cell),
        latticra_runtime_boundary_domain_label(m->domain),
        m->domain_known,
        m->domain_operational,
        m->domain_declarative,
        m->domain_future_gated,
        m->domain_effect_allowed,
        m->domain_authority_available,
        m->evidence_level,
        latticra_runtime_boundary_domain_matrix_effect_is_blocked(m));
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}

int latticra_runtime_boundary_domain_matrix_effect_is_blocked(
    const latticra_runtime_boundary_domain_matrix_result_t *m)
{
    if (m == 0) return 1;

    if (m->cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED ||
        m->cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID ||
        m->cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN) {
        return 1;
    }

    if (m->domain_future_gated) return 1;
    if (!m->domain_effect_allowed) return 1;

    return 0;
}

int latticra_runtime_boundary_domain_matrix_is_declarative(
    const latticra_runtime_boundary_domain_matrix_result_t *m)
{
    return m && m->cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE;
}

int latticra_runtime_boundary_domain_matrix_is_operational(
    const latticra_runtime_boundary_domain_matrix_result_t *m)
{
    return m && m->cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_OPERATIONAL;
}

int latticra_runtime_boundary_domain_matrix_is_future_gated(
    const latticra_runtime_boundary_domain_matrix_result_t *m)
{
    return m && m->cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_FUTURE_GATED;
}
