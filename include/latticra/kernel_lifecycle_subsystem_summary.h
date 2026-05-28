// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_H
#define LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_H

#include "latticra/kernel_lifecycle.h"
#include "latticra/kernel_subsystem_registry.h"
#include "latticra/nucleus_kernel_coupling.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX 128u
#define LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_REPORT_MAX 65536u
#define LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_ENTRY_MAX \
    LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_ENTRY_MAX

typedef struct {
    latticra_kernel_lifecycle_request_t lifecycle_request;
    latticra_kernel_subsystem_registry_request_t registry_request;
} latticra_kernel_lifecycle_subsystem_summary_request_t;

typedef struct {
    latticra_kernel_subsystem_kind_t kind;
    char name[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char registry_status[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char lifecycle_relation[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char effect_boundary[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    int lifecycle_ready;
    int authority_allowed;
    int network_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_lifecycle_subsystem_summary_entry_t;

typedef struct {
    latticra_status_t status;
    char summary_status[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char final_state[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char nucleus_coupling_status[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char os_readiness_status[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_nucleus_kernel_coupling_result_t nucleus_coupling;
    latticra_kernel_lifecycle_subsystem_summary_entry_t entries[
        LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_ENTRY_MAX];
    size_t entry_count;
    size_t lifecycle_step_count;
    size_t lifecycle_state_change_count;
    int lifecycle_complete;
    int lifecycle_state_mutated;
    int external_effect_performed;
    int network_allowed;
    int registry_no_effect;
    int nucleus_coupling_ready;
    int nucleus_no_effect_chain_ok;
    int nucleus_boot_allowed;
    int nucleus_runtime_entry_allowed;
    int nucleus_scheduler_run_entry_allowed;
    int nucleus_context_switch_allowed;
    int nucleus_register_save_allowed;
    int nucleus_register_restore_allowed;
    int nucleus_host_effect_allowed;
    int runtime_entry_recovery_audit_review_disposition_observation_view_allowed;
    int runtime_entry_recovery_audit_review_disposition_review_observation_view_allowed;
    int runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed;
    int runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed;
    int runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed;
    int runtime_entry_recovery_audit_review_observation_view_allowed;
    int runtime_entry_recovery_audit_observation_view_allowed;
    int runtime_entry_recovery_closeout_observation_view_allowed;
    int runtime_entry_recovery_outcome_observation_view_allowed;
    int runtime_entry_recovery_disposition_observation_view_allowed;
    int runtime_entry_recovery_plan_observation_view_allowed;
    int runtime_entry_recovery_boundary_observation_view_allowed;
    int runtime_entry_persistence_boundary_observation_view_allowed;
    int runtime_entry_quiescent_return_observation_view_allowed;
    int runtime_entry_idle_return_observation_view_allowed;
    int runtime_entry_process_return_observation_view_allowed;
    int runtime_entry_scheduler_return_observation_view_allowed;
    int runtime_entry_post_resume_observation_view_allowed;
    int runtime_entry_user_mode_resume_view_allowed;
    int runtime_entry_syscall_exit_view_allowed;
    int runtime_entry_syscall_return_view_allowed;
    int runtime_entry_syscall_dispatch_view_allowed;
    int runtime_entry_syscall_gate_view_allowed;
    int runtime_entry_privilege_level_view_allowed;
    int runtime_entry_address_space_view_allowed;
    int runtime_entry_stack_view_allowed;
    int runtime_entry_register_view_allowed;
    int runtime_entry_frame_allowed;
    int runtime_entry_admission_allowed;
    int runtime_entry_allowed;
    int recovery_boundary_observation_allowed;
    int recovery_boundary_allowed;
    int recovery_plan_allowed;
    int recovery_plan_observation_allowed;
    int recovery_disposition_allowed;
    int recovery_disposition_observation_allowed;
    int recovery_outcome_allowed;
    int recovery_outcome_observation_allowed;
    int recovery_audit_review_disposition_allowed;
    int recovery_audit_review_disposition_observation_allowed;
    int recovery_audit_review_disposition_review_allowed;
    int recovery_audit_review_disposition_review_observation_allowed;
    int recovery_audit_review_disposition_review_closeout_allowed;
    int recovery_audit_review_disposition_review_closeout_observation_allowed;
    int recovery_audit_review_disposition_review_closeout_archive_gate_allowed;
    int recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed;
    int recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed;
    int recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed;
    int recovery_audit_review_allowed;
    int recovery_audit_review_observation_allowed;
    int recovery_audit_allowed;
    int recovery_audit_observation_allowed;
    int recovery_closeout_allowed;
    int recovery_closeout_observation_allowed;
    int persistence_boundary_observation_allowed;
    int persistence_boundary_allowed;
    int persistence_commit_allowed;
    int quiescent_return_observation_allowed;
    int quiescent_return_allowed;
    int quiescent_state_read_allowed;
    int scheduler_execution_allowed;
    int scheduler_selection_allowed;
    int scheduler_dispatch_allowed;
    int scheduler_handoff_allowed;
    int scheduler_activation_allowed;
    int scheduler_run_entry_allowed;
    int memory_allocation_allowed;
    int process_spawn_allowed;
    int syscall_dispatch_allowed;
    int ipc_send_allowed;
    int ipc_receive_allowed;
    int ipc_queue_mutation_allowed;
    int filesystem_lookup_allowed;
    int filesystem_read_allowed;
    int filesystem_write_allowed;
    int namespace_mutation_allowed;
    int device_open_allowed;
    int device_read_allowed;
    int device_write_allowed;
    int driver_probe_allowed;
    int driver_load_allowed;
    int driver_bind_allowed;
    int interrupt_allowed;
    int interrupt_mask_allowed;
    int interrupt_unmask_allowed;
    int interrupt_dispatch_allowed;
    int interrupt_ack_allowed;
    int timer_tick_allowed;
    int timer_arm_allowed;
    int timer_disarm_allowed;
    int scheduler_tick_allowed;
    int run_queue_mutation_allowed;
    int enqueue_allowed;
    int dequeue_allowed;
    int dispatch_allowed;
    int context_switch_allowed;
    int register_save_allowed;
    int register_restore_allowed;
    int stack_switch_allowed;
    int address_space_switch_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int cpu_usage_write_allowed;
    int quota_update_allowed;
    int scheduler_credit_update_allowed;
    int process_wake_allowed;
    int persistence_allowed;
    int recovery_authority_allowed;
    int dma_allowed;
    int hardware_effect_allowed;
    int no_external_effect_chain;
    unsigned int evidence_level;
} latticra_kernel_lifecycle_subsystem_summary_result_t;

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_default_request(
    latticra_kernel_lifecycle_subsystem_summary_request_t *request);

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_evaluate(
    const latticra_kernel_lifecycle_subsystem_summary_request_t *request,
    latticra_kernel_lifecycle_subsystem_summary_result_t *result);

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_report(
    const latticra_kernel_lifecycle_subsystem_summary_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
