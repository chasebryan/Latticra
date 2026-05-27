// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_H
#define LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_H

#include "latticra/kernel_lifecycle.h"
#include "latticra/kernel_subsystem_registry.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX 64u
#define LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_REPORT_MAX 24576u
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
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_lifecycle_subsystem_summary_entry_t;

typedef struct {
    latticra_status_t status;
    char summary_status[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    char final_state[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_LABEL_MAX];
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_subsystem_registry_result_t registry;
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
    int runtime_entry_allowed;
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
