#ifndef LATTICRA_STATE_LATTICE_H
#define LATTICRA_STATE_LATTICE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_ORIGIN_MAX 16u
#define LATTICRA_ROUTE_MAX 32u
#define LATTICRA_AXIS_MAX 32u
#define LATTICRA_PATH_MAX 128u
#define LATTICRA_BREADCRUMB_MAX 128u
#define LATTICRA_TRACE_MAX 64u
#define LATTICRA_LABEL_MAX 32u
#define LATTICRA_REPORT_MAX 768u

typedef enum {
    LATTICRA_EFFECT_NONE = 0,
    LATTICRA_EFFECT_READ = 1,
    LATTICRA_EFFECT_LOCAL_MUTATION = 2,
    LATTICRA_EFFECT_HOST_MUTATION = 3,
    LATTICRA_EFFECT_NETWORK = 4,
    LATTICRA_EFFECT_HARDWARE = 5,
    LATTICRA_EFFECT_BOOT = 6,
    LATTICRA_EFFECT_RECOVERY = 7,
    LATTICRA_EFFECT_EXTERNAL = 8
} latticra_effect_t;

typedef enum {
    LATTICRA_STATUS_OK = 0,
    LATTICRA_STATUS_NULL_ARGUMENT = 1,
    LATTICRA_STATUS_BUFFER_TOO_SMALL = 2,
    LATTICRA_STATUS_ALLOCATION_FAILED = 3
} latticra_status_t;

typedef struct {
    char origin[LATTICRA_ORIGIN_MAX];
    char route[LATTICRA_ROUTE_MAX];
    char axis[LATTICRA_AXIS_MAX];
    char path[LATTICRA_PATH_MAX];
    char breadcrumb[LATTICRA_BREADCRUMB_MAX];
    char trace[LATTICRA_TRACE_MAX];
    char safe_portal[LATTICRA_LABEL_MAX];
    char rollback[LATTICRA_LABEL_MAX];
    char health[LATTICRA_LABEL_MAX];
    char risk[LATTICRA_LABEL_MAX];
    char lock[LATTICRA_LABEL_MAX];
    char dark_phase[LATTICRA_LABEL_MAX];
    latticra_effect_t host_effect;
    latticra_effect_t external_effect;
} latticra_state_lattice_t;

latticra_state_lattice_t latticra_state_lattice_default(void);
const char *latticra_effect_label(latticra_effect_t effect);
int latticra_state_lattice_is_no_effect(const latticra_state_lattice_t *state);
latticra_status_t latticra_state_lattice_report(
    const latticra_state_lattice_t *state,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
