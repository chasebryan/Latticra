#ifndef LATTICRA_KERNEL_STATE_H
#define LATTICRA_KERNEL_STATE_H

#include "latticra/kernel_memory_map.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_STATE_LABEL_MAX 64u
#define LATTICRA_KERNEL_STATE_REPORT_MAX 16384u

typedef enum {
    LATTICRA_KERNEL_STATE_CREATED = 0,
    LATTICRA_KERNEL_STATE_INITIALIZED = 1,
    LATTICRA_KERNEL_STATE_REGISTRY_READY = 2,
    LATTICRA_KERNEL_STATE_SCHEDULER_READY = 3,
    LATTICRA_KERNEL_STATE_MEMORY_MAP_READY = 4
} latticra_kernel_state_kind_t;

typedef enum {
    LATTICRA_KERNEL_STATE_GATE_DENY = 0,
    LATTICRA_KERNEL_STATE_GATE_ALLOW = 1
} latticra_kernel_state_gate_t;

typedef struct {
    latticra_kernel_memory_map_request_t memory_map_request;
    latticra_kernel_state_kind_t current_state;
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_gate_t gate;
} latticra_kernel_state_request_t;

typedef struct {
    latticra_status_t status;
    char state_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    char gate_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    char transition_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    char effect_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    latticra_kernel_memory_map_result_t memory_map;
    latticra_kernel_state_kind_t previous_state;
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_kind_t next_state;
    int state_change_performed;
    int external_effect_performed;
    int denied;
    unsigned int evidence_level;
} latticra_kernel_state_result_t;

const char *latticra_kernel_state_label(latticra_kernel_state_kind_t state);

latticra_status_t latticra_kernel_state_default_request(
    latticra_kernel_state_request_t *request);

latticra_status_t latticra_kernel_state_transition(
    const latticra_kernel_state_request_t *request,
    latticra_kernel_state_result_t *result);

latticra_status_t latticra_kernel_state_report(
    const latticra_kernel_state_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
