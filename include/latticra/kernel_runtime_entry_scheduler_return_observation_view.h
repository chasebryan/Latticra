#ifndef LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_H
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_H

#include "latticra/kernel_runtime_entry_post_resume_observation_view.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_LABEL_MAX 80u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_MAX 8u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_REPORT_MAX 65536u

typedef struct {
    latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        runtime_entry_post_resume_observation_view_request;
    size_t requested_scheduler_return_observation_view_count;
} latticra_kernel_runtime_entry_scheduler_return_observation_view_request_t;

typedef struct {
    size_t scheduler_return_observation_view_index;
    unsigned long scheduler_return_observation_view_token;
    unsigned long post_resume_observation_view_token;
    unsigned long user_mode_resume_view_token;
    unsigned long syscall_exit_view_token;
    unsigned long syscall_return_view_token;
    unsigned long syscall_dispatch_view_token;
    unsigned long syscall_gate_view_token;
    unsigned long privilege_level_view_token;
    unsigned long pid_token;
    unsigned long scheduler_return_observation_view_rank;
    unsigned long post_resume_observation_view_rank;
    unsigned long syscall_number;
    unsigned long resume_slot;
    unsigned long observation_slot;
    unsigned long scheduler_return_slot;
    unsigned long instruction_pointer_slot;
    unsigned long stack_pointer_slot;
    unsigned long cpu_mode_slot;
    unsigned long observation_epoch_slot;
    unsigned long scheduler_return_epoch_slot;
    unsigned long scheduler_return_reason_slot;
    unsigned long argument_count;
    int post_resume_observation_view_declared;
    int scheduler_return_observation_view_declared;
    int post_resume_observation_declared;
    int scheduler_return_observation_declared;
    int scheduler_return_declared;
    int instruction_pointer_observation_declared;
    int stack_pointer_observation_declared;
    int cpu_mode_observation_declared;
    int scheduler_return_reason_declared;
    char process_label[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_LABEL_MAX];
    char scheduler_return_observation_view_class[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_LABEL_MAX];
    char scheduler_return_observation_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_LABEL_MAX];
    char authority_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_LABEL_MAX];
    int declared;
    int scheduler_return_observation_view_planned;
    int scheduler_return_observation_planned;
    int scheduler_return_planned;
    int scheduler_execution_planned;
    int context_switch_planned;
    int dispatch_planned;
    int run_queue_mutation_planned;
    int instruction_pointer_read_planned;
    int stack_pointer_read_planned;
    int cpu_mode_read_planned;
    int runtime_entry_scheduler_return_observation_view_allowed;
    int runtime_entry_post_resume_observation_view_allowed;
    int runtime_entry_user_mode_resume_view_allowed;
    int runtime_entry_allowed;
    int post_resume_observation_allowed;
    int scheduler_return_observation_allowed;
    int scheduler_return_allowed;
    int scheduler_execution_allowed;
    int scheduler_dispatch_allowed;
    int scheduler_handoff_allowed;
    int scheduler_activation_allowed;
    int scheduler_run_entry_allowed;
    int dispatch_allowed;
    int context_switch_allowed;
    int run_queue_mutation_allowed;
    int instruction_pointer_read_allowed;
    int stack_pointer_read_allowed;
    int cpu_mode_read_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_scheduler_return_observation_view_entry_t;

typedef struct {
    latticra_status_t status;
    char scheduler_return_observation_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_LABEL_MAX];
    char policy_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_LABEL_MAX];
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        runtime_entry_post_resume_observation_view;
    latticra_kernel_runtime_entry_scheduler_return_observation_view_entry_t
        scheduler_return_observation_views[
            LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_MAX];
    size_t scheduler_return_observation_view_count;
    int no_effect;
    int runtime_entry_scheduler_return_observation_view_allowed;
    int runtime_entry_post_resume_observation_view_allowed;
    int runtime_entry_user_mode_resume_view_allowed;
    int runtime_entry_allowed;
    int post_resume_observation_allowed;
    int scheduler_return_observation_allowed;
    int scheduler_return_allowed;
    int scheduler_execution_allowed;
    int scheduler_dispatch_allowed;
    int scheduler_handoff_allowed;
    int scheduler_activation_allowed;
    int scheduler_run_entry_allowed;
    int dispatch_allowed;
    int context_switch_allowed;
    int run_queue_mutation_allowed;
    int instruction_pointer_read_allowed;
    int stack_pointer_read_allowed;
    int cpu_mode_read_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t;

latticra_status_t
latticra_kernel_runtime_entry_scheduler_return_observation_view_default_request(
    latticra_kernel_runtime_entry_scheduler_return_observation_view_request_t *request);

latticra_status_t
latticra_kernel_runtime_entry_scheduler_return_observation_view_evaluate(
    const latticra_kernel_runtime_entry_scheduler_return_observation_view_request_t *request,
    latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t *result);

latticra_status_t
latticra_kernel_runtime_entry_scheduler_return_observation_view_report(
    const latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
