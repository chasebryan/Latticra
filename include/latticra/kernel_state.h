#ifndef LATTICRA_KERNEL_STATE_H
#define LATTICRA_KERNEL_STATE_H

#include "latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_STATE_LABEL_MAX 128u
#define LATTICRA_KERNEL_STATE_REPORT_MAX 16384u

typedef enum {
    LATTICRA_KERNEL_STATE_CREATED = 0,
    LATTICRA_KERNEL_STATE_INITIALIZED = 1,
    LATTICRA_KERNEL_STATE_REGISTRY_READY = 2,
    LATTICRA_KERNEL_STATE_SCHEDULER_READY = 3,
    LATTICRA_KERNEL_STATE_MEMORY_MAP_READY = 4,
    LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY = 5,
    LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY = 6,
    LATTICRA_KERNEL_STATE_IPC_TABLE_READY = 7,
    LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY = 8,
    LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY = 9,
    LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY = 10,
    LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY = 11,
    LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY = 12,
    LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY = 13,
    LATTICRA_KERNEL_STATE_RUN_QUEUE_READY = 14,
    LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY = 15,
    LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY = 16,
    LATTICRA_KERNEL_STATE_PREEMPTION_READY = 17,
    LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY = 18,
    LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY = 19,
    LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY = 20,
    LATTICRA_KERNEL_STATE_SCHEDULER_HANDOFF_READY = 21,
    LATTICRA_KERNEL_STATE_SCHEDULER_ACTIVATION_READY = 22,
    LATTICRA_KERNEL_STATE_SCHEDULER_RUN_ENTRY_READY = 23,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADMISSION_READY = 24,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_FRAME_READY = 25,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_REGISTER_VIEW_READY = 26,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_STACK_VIEW_READY = 27,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_READY = 28,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_READY = 29,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_READY = 30,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_READY = 31,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_READY = 32,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_READY = 33,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_READY = 34,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_READY = 35,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_READY = 36,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_READY = 37,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_READY = 38,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_READY = 39,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_READY = 40,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_READY = 41,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_READY = 42,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_READY = 43,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_READY = 44,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_READY = 45,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY = 46,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_OBSERVATION_VIEW_READY = 47,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_READY = 48,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_OBSERVATION_VIEW_READY = 49,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_OBSERVATION_VIEW_READY = 50,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_READY = 51,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_OBSERVATION_VIEW_READY = 52,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_OBSERVATION_VIEW_READY = 53,
    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_OBSERVATION_VIEW_READY = 54
} latticra_kernel_state_kind_t;

typedef enum {
    LATTICRA_KERNEL_STATE_GATE_DENY = 0,
    LATTICRA_KERNEL_STATE_GATE_ALLOW = 1
} latticra_kernel_state_gate_t;

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
    latticra_kernel_runtime_entry_recovery_audit_review_observation_view_request_t
        runtime_entry_recovery_audit_review_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_request_t
        runtime_entry_recovery_audit_review_disposition_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_request_t
        runtime_entry_recovery_audit_review_disposition_review_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request;
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
    latticra_kernel_process_table_result_t process_table;
    latticra_kernel_syscall_table_result_t syscall_table;
    latticra_kernel_ipc_table_result_t ipc_table;
    latticra_kernel_vfs_namespace_result_t vfs_namespace;
    latticra_kernel_device_registry_result_t device_registry;
    latticra_kernel_driver_catalog_result_t driver_catalog;
    latticra_kernel_interrupt_table_result_t interrupt_table;
    latticra_kernel_timer_source_result_t timer_source;
    latticra_kernel_scheduler_tick_result_t scheduler_tick;
    latticra_kernel_run_queue_result_t run_queue;
    latticra_kernel_context_switch_result_t context_switch;
    latticra_kernel_time_accounting_result_t time_accounting;
    latticra_kernel_preemption_result_t preemption;
    latticra_kernel_scheduler_credit_result_t scheduler_credit;
    latticra_kernel_scheduler_selection_result_t scheduler_selection;
    latticra_kernel_scheduler_dispatch_result_t scheduler_dispatch;
    latticra_kernel_scheduler_handoff_result_t scheduler_handoff;
    latticra_kernel_scheduler_activation_result_t scheduler_activation;
    latticra_kernel_scheduler_run_entry_result_t scheduler_run_entry;
    latticra_kernel_runtime_entry_admission_result_t runtime_entry_admission;
    latticra_kernel_runtime_entry_frame_result_t runtime_entry_frame;
    latticra_kernel_runtime_entry_register_view_result_t
        runtime_entry_register_view;
    latticra_kernel_runtime_entry_stack_view_result_t runtime_entry_stack_view;
    latticra_kernel_runtime_entry_address_space_view_result_t
        runtime_entry_address_space_view;
    latticra_kernel_runtime_entry_privilege_level_view_result_t
        runtime_entry_privilege_level_view;
    latticra_kernel_runtime_entry_syscall_gate_view_result_t
        runtime_entry_syscall_gate_view;
    latticra_kernel_runtime_entry_syscall_dispatch_view_result_t
        runtime_entry_syscall_dispatch_view;
    latticra_kernel_runtime_entry_syscall_return_view_result_t
        runtime_entry_syscall_return_view;
    latticra_kernel_runtime_entry_syscall_exit_view_result_t
        runtime_entry_syscall_exit_view;
    latticra_kernel_runtime_entry_user_mode_resume_view_result_t
        runtime_entry_user_mode_resume_view;
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        runtime_entry_post_resume_observation_view;
    latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
        runtime_entry_scheduler_return_observation_view;
    latticra_kernel_runtime_entry_process_return_observation_view_result_t
        runtime_entry_process_return_observation_view;
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        runtime_entry_idle_return_observation_view;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        runtime_entry_quiescent_return_observation_view;
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        runtime_entry_persistence_boundary_observation_view;
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        runtime_entry_recovery_boundary_observation_view;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        runtime_entry_recovery_plan_observation_view;
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        runtime_entry_recovery_disposition_observation_view;
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        runtime_entry_recovery_outcome_observation_view;
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        runtime_entry_recovery_closeout_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        runtime_entry_recovery_audit_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_observation_view_result_t
        runtime_entry_recovery_audit_review_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t
        runtime_entry_recovery_audit_review_disposition_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_result_t
        runtime_entry_recovery_audit_review_disposition_review_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_result_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_result_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_result_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_result_t
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view;
    latticra_kernel_state_kind_t previous_state;
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_kind_t next_state;
    int state_change_performed;
    int external_effect_performed;
    int network_allowed;
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
