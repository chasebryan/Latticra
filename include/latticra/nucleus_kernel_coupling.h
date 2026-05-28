#ifndef LATTICRA_NUCLEUS_KERNEL_COUPLING_H
#define LATTICRA_NUCLEUS_KERNEL_COUPLING_H

#include "latticra/kernel_lifecycle.h"
#include "latticra/kernel_runtime_entry_idle_return_observation_view.h"
#include "latticra/kernel_runtime_entry_persistence_boundary_observation_view.h"
#include "latticra/kernel_runtime_entry_process_return_observation_view.h"
#include "latticra/kernel_runtime_entry_quiescent_return_observation_view.h"
#include "latticra/kernel_runtime_entry_recovery_boundary_observation_view.h"
#include "latticra/kernel_runtime_entry_recovery_audit_observation_view.h"
#include "latticra/kernel_runtime_entry_recovery_closeout_observation_view.h"
#include "latticra/kernel_runtime_entry_recovery_outcome_observation_view.h"
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
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_MISSING = 6,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_BLOCKED = 7,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_MISSING = 8,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_BLOCKED = 9,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NON_NO_EFFECT_CHAIN = 10,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_MISSING = 11,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_BLOCKED = 12,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_MISSING = 13,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_BLOCKED = 14,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_MISSING = 15,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_BLOCKED = 16,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_MISSING = 17,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_BLOCKED = 18,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_MISSING = 19,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_BLOCKED = 20,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_MISSING = 21,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_BLOCKED = 22,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_MISSING = 23,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_BLOCKED = 24,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_MISSING = 25,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_BLOCKED = 26,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_MISSING = 27,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_BLOCKED = 28,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_MISSING = 29,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_BLOCKED = 30,
    LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_INTERNAL_ERROR = 31
} latticra_nucleus_kernel_coupling_denial_t;

typedef struct {
    char coupling_id[LATTICRA_NUCLEUS_KERNEL_COUPLING_ID_MAX];
    const latticra_nucleus_task_plan_result_t *nucleus_plan;
    const latticra_kernel_subsystem_registry_result_t *kernel_registry;
    const latticra_kernel_lifecycle_result_t *kernel_lifecycle;
    const latticra_kernel_runtime_entry_register_view_result_t *runtime_register_view;
    const latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *runtime_process_return_observation_view;
    const latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        *runtime_idle_return_observation_view;
    const
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *runtime_quiescent_return_observation_view;
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *runtime_persistence_boundary_observation_view;
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *runtime_recovery_boundary_observation_view;
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_recovery_plan_observation_view;
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_recovery_disposition_observation_view;
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_recovery_outcome_observation_view;
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_recovery_closeout_observation_view;
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_recovery_audit_observation_view;
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
    char kernel_lifecycle_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char kernel_lifecycle_final_state[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_register_view_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_entry_frame_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char scheduler_run_entry_status[LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_process_return_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_scheduler_return_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_post_resume_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_user_mode_resume_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_idle_return_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_quiescent_return_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_persistence_boundary_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_recovery_boundary_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_recovery_plan_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_recovery_disposition_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_recovery_outcome_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_recovery_closeout_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    char runtime_recovery_audit_observation_view_status[
        LATTICRA_NUCLEUS_KERNEL_COUPLING_LABEL_MAX];
    size_t task_count;
    size_t accepted_task_count;
    size_t blocked_task_count;
    size_t subsystem_count;
    size_t lifecycle_step_count;
    size_t lifecycle_state_change_count;
    size_t register_view_count;
    size_t process_return_observation_view_count;
    size_t scheduler_return_observation_view_count;
    size_t post_resume_observation_view_count;
    size_t user_mode_resume_view_count;
    size_t idle_return_observation_view_count;
    size_t quiescent_return_observation_view_count;
    size_t persistence_boundary_observation_view_count;
    size_t recovery_boundary_observation_view_count;
    size_t recovery_plan_observation_view_count;
    size_t recovery_disposition_observation_view_count;
    size_t recovery_outcome_observation_view_count;
    size_t recovery_closeout_observation_view_count;
    size_t recovery_audit_observation_view_count;
    int prerequisites_satisfied;
    int no_effect_chain_ok;
    int lifecycle_complete;
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
    int runtime_process_return_observation_view_allowed;
    int runtime_scheduler_return_observation_view_allowed;
    int runtime_post_resume_observation_view_allowed;
    int runtime_idle_return_observation_view_allowed;
    int runtime_quiescent_return_observation_view_allowed;
    int runtime_persistence_boundary_observation_view_allowed;
    int runtime_recovery_boundary_observation_view_allowed;
    int runtime_recovery_plan_observation_view_allowed;
    int runtime_recovery_disposition_observation_view_allowed;
    int runtime_recovery_outcome_observation_view_allowed;
    int runtime_recovery_closeout_observation_view_allowed;
    int runtime_recovery_audit_observation_view_allowed;
    int scheduler_return_observation_allowed;
    int process_return_observation_allowed;
    int process_return_allowed;
    int idle_return_observation_allowed;
    int idle_return_allowed;
    int idle_state_read_allowed;
    int quiescent_return_observation_allowed;
    int quiescent_return_allowed;
    int quiescent_state_read_allowed;
    int persistence_boundary_observation_allowed;
    int persistence_boundary_allowed;
    int persistence_commit_allowed;
    int recovery_boundary_observation_allowed;
    int recovery_boundary_allowed;
    int recovery_plan_allowed;
    int recovery_plan_observation_allowed;
    int recovery_disposition_allowed;
    int recovery_disposition_observation_allowed;
    int recovery_outcome_allowed;
    int recovery_outcome_observation_allowed;
    int recovery_closeout_allowed;
    int recovery_closeout_observation_allowed;
    int recovery_audit_allowed;
    int recovery_audit_observation_allowed;
    int process_state_read_allowed;
    int scheduler_execution_allowed;
    int scheduler_dispatch_allowed;
    int run_queue_mutation_allowed;
    int process_wake_allowed;
    int persistence_allowed;
    int recovery_authority_allowed;
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
    int runtime_process_return_observation_view_allowed;
    int runtime_scheduler_return_observation_view_allowed;
    int runtime_post_resume_observation_view_allowed;
    int runtime_idle_return_observation_view_allowed;
    int runtime_quiescent_return_observation_view_allowed;
    int runtime_persistence_boundary_observation_view_allowed;
    int runtime_recovery_boundary_observation_view_allowed;
    int runtime_recovery_plan_observation_view_allowed;
    int runtime_recovery_disposition_observation_view_allowed;
    int runtime_recovery_outcome_observation_view_allowed;
    int runtime_recovery_closeout_observation_view_allowed;
    int runtime_recovery_audit_observation_view_allowed;
    int scheduler_return_observation_allowed;
    int process_return_observation_allowed;
    int process_return_allowed;
    int idle_return_observation_allowed;
    int idle_return_allowed;
    int idle_state_read_allowed;
    int quiescent_return_observation_allowed;
    int quiescent_return_allowed;
    int quiescent_state_read_allowed;
    int persistence_boundary_observation_allowed;
    int persistence_boundary_allowed;
    int persistence_commit_allowed;
    int recovery_boundary_observation_allowed;
    int recovery_boundary_allowed;
    int recovery_plan_allowed;
    int recovery_plan_observation_allowed;
    int recovery_disposition_allowed;
    int recovery_disposition_observation_allowed;
    int recovery_outcome_allowed;
    int recovery_outcome_observation_allowed;
    int recovery_closeout_allowed;
    int recovery_closeout_observation_allowed;
    int recovery_audit_allowed;
    int recovery_audit_observation_allowed;
    int process_state_read_allowed;
    int scheduler_execution_allowed;
    int scheduler_dispatch_allowed;
    int run_queue_mutation_allowed;
    int process_wake_allowed;
    int persistence_allowed;
    int recovery_authority_allowed;
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
