#ifndef LATTICRA_NUCLEUS_KERNEL_COUPLING_H
#define LATTICRA_NUCLEUS_KERNEL_COUPLING_H

#include "latticra/kernel_runtime_entry_register_view.h"
#include "latticra/kernel_subsystem_registry.h"
#include "latticra/nucleus_task_plan.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_NUCLEUS_KERNEL_COUPLING_ID_MAX 64u
#define LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX 64u
#define LATTICRA_NUCLEUS_KERNEL_COUPLING_SOURCE_IDENTITY_MAX 128u
#define LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX 32768u

typedef enum {
    LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_ONLY_READY = 0,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_BLOCKED = 1,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_INVALID = 2
} latticra_nucleus_kernel_coupling_classification_t;

typedef enum {
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_OK = 0,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NULL_ARGUMENT = 1,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_MISSING = 2,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_BLOCKED = 3,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_REGISTRY_MISSING = 4,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_REGISTRY_BLOCKED = 5,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_MISSING = 6,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_BLOCKED = 7,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NON_NO_EFFECT_CHAIN = 8,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_INTERNAL_ERROR = 9
} latticra_nucleus_kernel_coupling_denial_t;

typedef struct {
    char coupling_id[LATTICRA_NUCLEUS_KERNEL_COUPLING_ID_MAX];
    const latticra_nucleus_task_plan_result_t *nucleus_plan;
    const latticra_kernel_subsystem_registry_result_t *kernel_registry;
    const latticra_kernel_runtime_entry_register_view_result_t *runtime_register_view;
    const char *source_identity;
    size_t source_identity_len;
    latticra_l_ui_source_span_t source_span;
} latticra_nucleus_kernel_coupling_request_t;

typedef struct {
    char coupling_id[LATTICRA_NUCLEUS_KERNEL_COUPLING_ID_MAX];
    latticra_nucleus_kernel_coupling_classification_t classification;
    latticra_nucleus_kernel_coupling_denial_t denial;
    char readiness_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char os_readiness_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char nucleus_plan_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char kernel_registry_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char kernel_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_register_view_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_entry_frame_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char scheduler_run_entry_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    size_t task_count;
    size_t accepted_task_count;
    size_t blocked_task_count;
    size_t subsystem_count;
    size_t register_view_count;
    int prerequisites_satisfied;
    int no_effect_chain_ok;
    int report_only;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int network_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
    int boot_allowed;
    int runtime_entry_allowed;
    int scheduler_run_entry_allowed;
    int context_switch_allowed;
    int register_save_allowed;
    int register_restore_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
    char source_identity[LATTICRA_NUCLEUS_KERNEL_COUPLING_SOURCE_IDENTITY_MAX];
    latticra_l_ui_source_span_t source_span;
} latticra_nucleus_kernel_coupling_record_t;

typedef struct {
    latticra_status_t status;
    latticra_nucleus_kernel_coupling_record_t record;
    size_t record_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int network_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
    int boot_allowed;
    int runtime_entry_allowed;
    int scheduler_run_entry_allowed;
    int context_switch_allowed;
    int register_save_allowed;
    int register_restore_allowed;
    int host_effect_allowed;
} latticra_nucleus_kernel_coupling_result_t;

const char *latticra_nucleus_kernel_coupling_classification_label(
    latticra_nucleus_kernel_coupling_classification_t classification);
const char *latticra_nucleus_kernel_coupling_denial_label(
    latticra_nucleus_kernel_coupling_denial_t denial);

latticra_status_t latticra_nucleus_kernel_coupling_default_request(
    latticra_nucleus_kernel_coupling_request_t *request);

latticra_status_t latticra_nucleus_kernel_coupling_default_nucleus_plan(
    latticra_nucleus_task_plan_result_t *plan);

latticra_status_t latticra_nucleus_kernel_coupling_evaluate(
    const latticra_nucleus_kernel_coupling_request_t *request,
    latticra_nucleus_kernel_coupling_result_t *result);

latticra_status_t latticra_nucleus_kernel_coupling_evaluate_default(
    latticra_nucleus_kernel_coupling_result_t *result);

latticra_status_t latticra_nucleus_kernel_coupling_report(
    const latticra_nucleus_kernel_coupling_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
