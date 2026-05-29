#ifndef LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_H
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_H

#include "latticra/kernel_runtime_entry_privilege_level_view.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_LABEL_MAX 64u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_MAX 8u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_REPORT_MAX 65536u

typedef struct {
    latticra_kernel_runtime_entry_privilege_level_view_request_t
        runtime_entry_privilege_level_view_request;
    size_t requested_syscall_gate_view_count;
} latticra_kernel_runtime_entry_syscall_gate_view_request_t;

typedef struct {
    size_t syscall_gate_view_index;
    unsigned long syscall_gate_view_token;
    unsigned long privilege_level_view_token;
    unsigned long address_space_view_token;
    unsigned long stack_view_token;
    unsigned long register_view_token;
    unsigned long frame_token;
    unsigned long admission_token;
    unsigned long run_entry_token;
    unsigned long activation_token;
    unsigned long pid_token;
    unsigned long run_entry_rank;
    unsigned long admission_rank;
    unsigned long frame_rank;
    unsigned long register_view_rank;
    unsigned long stack_view_rank;
    unsigned long address_space_view_rank;
    unsigned long privilege_level_view_rank;
    unsigned long syscall_gate_view_rank;
    unsigned long remaining_budget_ns;
    unsigned long privilege_level;
    unsigned long ring_number;
    unsigned long syscall_number;
    unsigned long gate_vector;
    unsigned long handler_slot;
    int privilege_level_view_declared;
    int syscall_gate_view_declared;
    int syscall_number_declared;
    int syscall_vector_declared;
    int syscall_handler_declared;
    int user_mode_declared;
    int kernel_mode_declared;
    int privilege_boundary_declared;
    char process_label[LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_LABEL_MAX];
    char syscall_gate_view_class[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_LABEL_MAX];
    char syscall_gate_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_LABEL_MAX];
    char authority_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_LABEL_MAX];
    int declared;
    int syscall_gate_view_planned;
    int syscall_gate_view_built;
    int syscall_gate_view_installed;
    int syscall_dispatch_planned;
    int syscall_instruction_planned;
    int syscall_handler_planned;
    int syscall_return_planned;
    int privilege_transition_planned;
    int interrupt_return_planned;
    int admitted;
    int runtime_entry_planned;
    int runtime_entry_entered;
    int execution_entered;
    int context_switch_planned;
    int runtime_entry_syscall_gate_view_allowed;
    int runtime_entry_privilege_level_view_allowed;
    int runtime_entry_address_space_view_allowed;
    int runtime_entry_stack_view_allowed;
    int runtime_entry_register_view_allowed;
    int runtime_entry_frame_allowed;
    int runtime_entry_admission_allowed;
    int runtime_entry_allowed;
    int scheduler_run_entry_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int register_save_allowed;
    int register_restore_allowed;
    int stack_switch_allowed;
    int address_space_switch_allowed;
    int page_table_write_allowed;
    int tlb_flush_allowed;
    int mmu_update_allowed;
    int privilege_transition_allowed;
    int syscall_gate_allowed;
    int syscall_dispatch_allowed;
    int syscall_instruction_allowed;
    int syscall_handler_allowed;
    int syscall_return_allowed;
    int interrupt_return_allowed;
    int preemption_allowed;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_syscall_gate_view_entry_t;

typedef struct {
    latticra_status_t status;
    char syscall_gate_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_LABEL_MAX];
    char policy_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_LABEL_MAX];
    latticra_kernel_runtime_entry_privilege_level_view_result_t
        runtime_entry_privilege_level_view;
    latticra_kernel_runtime_entry_syscall_gate_view_entry_t
        syscall_gate_views[
            LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_MAX];
    size_t syscall_gate_view_count;
    int no_effect;
    int runtime_entry_syscall_gate_view_allowed;
    int runtime_entry_privilege_level_view_allowed;
    int runtime_entry_address_space_view_allowed;
    int runtime_entry_stack_view_allowed;
    int runtime_entry_register_view_allowed;
    int runtime_entry_frame_allowed;
    int runtime_entry_admission_allowed;
    int runtime_entry_allowed;
    int scheduler_run_entry_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int register_save_allowed;
    int register_restore_allowed;
    int stack_switch_allowed;
    int address_space_switch_allowed;
    int page_table_write_allowed;
    int tlb_flush_allowed;
    int mmu_update_allowed;
    int privilege_transition_allowed;
    int syscall_gate_allowed;
    int syscall_dispatch_allowed;
    int syscall_instruction_allowed;
    int syscall_handler_allowed;
    int syscall_return_allowed;
    int interrupt_return_allowed;
    int preemption_allowed;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_syscall_gate_view_result_t;

latticra_status_t
latticra_kernel_runtime_entry_syscall_gate_view_default_request(
    latticra_kernel_runtime_entry_syscall_gate_view_request_t *request);

latticra_status_t
latticra_kernel_runtime_entry_syscall_gate_view_evaluate(
    const latticra_kernel_runtime_entry_syscall_gate_view_request_t *request,
    latticra_kernel_runtime_entry_syscall_gate_view_result_t *result);

latticra_status_t latticra_kernel_runtime_entry_syscall_gate_view_report(
    const latticra_kernel_runtime_entry_syscall_gate_view_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
