#ifndef LATTICRA_KERNEL_SCHEDULER_H
#define LATTICRA_KERNEL_SCHEDULER_H

#include "latticra/kernel_subsystem_registry.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SCHEDULER_LABEL_MAX 64u
#define LATTICRA_KERNEL_SCHEDULER_SLOT_MAX 8u
#define LATTICRA_KERNEL_SCHEDULER_REPORT_MAX 16384u

typedef struct {
    latticra_kernel_subsystem_registry_request_t registry_request;
    size_t requested_slot_count;
} latticra_kernel_scheduler_request_t;

typedef struct {
    size_t slot_index;
    char label[LATTICRA_KERNEL_SCHEDULER_LABEL_MAX];
    char state[LATTICRA_KERNEL_SCHEDULER_LABEL_MAX];
    char dispatch_status[LATTICRA_KERNEL_SCHEDULER_LABEL_MAX];
    int runnable;
    int dispatched;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_scheduler_slot_t;

typedef struct {
    latticra_status_t status;
    char scheduler_status[LATTICRA_KERNEL_SCHEDULER_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_SCHEDULER_LABEL_MAX];
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_scheduler_slot_t slots[LATTICRA_KERNEL_SCHEDULER_SLOT_MAX];
    size_t slot_count;
    int no_effect;
    int dispatch_allowed;
    int context_switch_allowed;
    unsigned int evidence_level;
} latticra_kernel_scheduler_result_t;

latticra_status_t latticra_kernel_scheduler_default_request(
    latticra_kernel_scheduler_request_t *request);

latticra_status_t latticra_kernel_scheduler_evaluate(
    const latticra_kernel_scheduler_request_t *request,
    latticra_kernel_scheduler_result_t *result);

latticra_status_t latticra_kernel_scheduler_report(
    const latticra_kernel_scheduler_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
