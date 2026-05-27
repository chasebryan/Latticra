#ifndef LATTICRA_KERNEL_LIFECYCLE_H
#define LATTICRA_KERNEL_LIFECYCLE_H

#include "latticra/kernel_state_machine.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_LIFECYCLE_LABEL_MAX 64u
#define LATTICRA_KERNEL_LIFECYCLE_REPORT_MAX 16384u
#define LATTICRA_KERNEL_LIFECYCLE_STEP_MAX 23u

typedef struct {
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_gate_t gate;
    size_t max_steps;
} latticra_kernel_lifecycle_request_t;

typedef struct {
    latticra_status_t status;
    char lifecycle_status[LATTICRA_KERNEL_LIFECYCLE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_LIFECYCLE_LABEL_MAX];
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_kind_t final_state;
    size_t step_count;
    size_t state_change_count;
    int lifecycle_complete;
    int external_effect_performed;
    int network_allowed;
    unsigned int evidence_level;
} latticra_kernel_lifecycle_result_t;

latticra_status_t latticra_kernel_lifecycle_default_request(
    latticra_kernel_lifecycle_request_t *request);

latticra_status_t latticra_kernel_lifecycle_run(
    const latticra_kernel_lifecycle_request_t *request,
    latticra_kernel_lifecycle_result_t *result);

latticra_status_t latticra_kernel_lifecycle_report(
    const latticra_kernel_lifecycle_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
