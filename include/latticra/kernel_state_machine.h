#ifndef LATTICRA_KERNEL_STATE_MACHINE_H
#define LATTICRA_KERNEL_STATE_MACHINE_H

#include "latticra/kernel_state.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX 64u
#define LATTICRA_KERNEL_STATE_MACHINE_LOG_MAX 46u
#define LATTICRA_KERNEL_STATE_MACHINE_REPORT_MAX 49152u

typedef struct {
    latticra_kernel_state_kind_t from_state;
    latticra_kernel_state_kind_t to_state;
    char status[LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX];
    int state_change_performed;
    int external_effect_performed;
    int network_allowed;
} latticra_kernel_state_machine_log_entry_t;

typedef struct {
    latticra_kernel_state_kind_t current_state;
    char machine_status[LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX];
    latticra_kernel_state_machine_log_entry_t log[LATTICRA_KERNEL_STATE_MACHINE_LOG_MAX];
    size_t log_count;
    int state_mutated;
    int external_effect_performed;
    int network_allowed;
    unsigned int evidence_level;
} latticra_kernel_state_machine_t;

typedef struct {
    latticra_kernel_memory_map_request_t memory_map_request;
    latticra_kernel_process_table_request_t process_table_request;
    latticra_kernel_syscall_table_request_t syscall_table_request;
    latticra_kernel_ipc_table_request_t ipc_table_request;
    latticra_kernel_vfs_namespace_request_t vfs_namespace_request;
    latticra_kernel_device_registry_request_t device_registry_request;
    latticra_kernel_driver_catalog_request_t driver_catalog_request;
    latticra_kernel_interrupt_table_request_t interrupt_table_request;
    latticra_kernel_timer_source_request_t timer_source_request;
    latticra_kernel_scheduler_tick_request_t scheduler_tick_request;
    latticra_kernel_run_queue_request_t run_queue_request;
    latticra_kernel_context_switch_request_t context_switch_request;
    latticra_kernel_time_accounting_request_t time_accounting_request;
    latticra_kernel_preemption_request_t preemption_request;
    latticra_kernel_scheduler_credit_request_t scheduler_credit_request;
    latticra_kernel_scheduler_selection_request_t scheduler_selection_request;
    latticra_kernel_scheduler_dispatch_request_t scheduler_dispatch_request;
    latticra_kernel_scheduler_handoff_request_t scheduler_handoff_request;
    latticra_kernel_scheduler_activation_request_t scheduler_activation_request;
    latticra_kernel_scheduler_run_entry_request_t scheduler_run_entry_request;
    latticra_kernel_runtime_entry_admission_request_t runtime_entry_admission_request;
    latticra_kernel_runtime_entry_frame_request_t runtime_entry_frame_request;
    latticra_kernel_runtime_entry_register_view_request_t
        runtime_entry_register_view_request;
    latticra_kernel_runtime_entry_stack_view_request_t
        runtime_entry_stack_view_request;
    latticra_kernel_runtime_entry_address_space_view_request_t
        runtime_entry_address_space_view_request;
    latticra_kernel_runtime_entry_privilege_level_view_request_t
        runtime_entry_privilege_level_view_request;
    latticra_kernel_runtime_entry_syscall_gate_view_request_t
        runtime_entry_syscall_gate_view_request;
    latticra_kernel_runtime_entry_syscall_dispatch_view_request_t
        runtime_entry_syscall_dispatch_view_request;
    latticra_kernel_runtime_entry_syscall_return_view_request_t
        runtime_entry_syscall_return_view_request;
    latticra_kernel_runtime_entry_syscall_exit_view_request_t
        runtime_entry_syscall_exit_view_request;
    latticra_kernel_runtime_entry_user_mode_resume_view_request_t
        runtime_entry_user_mode_resume_view_request;
    latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        runtime_entry_post_resume_observation_view_request;
    latticra_kernel_runtime_entry_scheduler_return_observation_view_request_t
        runtime_entry_scheduler_return_observation_view_request;
    latticra_kernel_runtime_entry_process_return_observation_view_request_t
        runtime_entry_process_return_observation_view_request;
    latticra_kernel_runtime_entry_idle_return_observation_view_request_t
        runtime_entry_idle_return_observation_view_request;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_request_t
        runtime_entry_quiescent_return_observation_view_request;
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_request_t
        runtime_entry_persistence_boundary_observation_view_request;
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_request_t
        runtime_entry_recovery_boundary_observation_view_request;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        runtime_entry_recovery_plan_observation_view_request;
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_request_t
        runtime_entry_recovery_disposition_observation_view_request;
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_request_t
        runtime_entry_recovery_outcome_observation_view_request;
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_request_t
        runtime_entry_recovery_closeout_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        runtime_entry_recovery_audit_observation_view_request;
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_gate_t gate;
} latticra_kernel_state_machine_step_request_t;

typedef struct {
    latticra_status_t status;
    char step_status[LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX];
    latticra_kernel_state_result_t transition;
    latticra_kernel_state_kind_t machine_state_before;
    latticra_kernel_state_kind_t machine_state_after;
    int state_mutated;
    int external_effect_performed;
    int network_allowed;
    unsigned int evidence_level;
} latticra_kernel_state_machine_step_result_t;

latticra_status_t latticra_kernel_state_machine_init(
    latticra_kernel_state_machine_t *machine);

latticra_status_t latticra_kernel_state_machine_default_step_request(
    latticra_kernel_state_machine_step_request_t *request);

latticra_status_t latticra_kernel_state_machine_step(
    latticra_kernel_state_machine_t *machine,
    const latticra_kernel_state_machine_step_request_t *request,
    latticra_kernel_state_machine_step_result_t *result);

latticra_status_t latticra_kernel_state_machine_report(
    const latticra_kernel_state_machine_t *machine,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
