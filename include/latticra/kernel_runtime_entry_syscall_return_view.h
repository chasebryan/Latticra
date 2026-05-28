#ifndef LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_H
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_H

#include "latticra/kernel_runtime_entry_syscall_dispatch_view.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_LABEL_MAX 64u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_MAX 8u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_REPORT_MAX 65536u

typedef struct {
    latticra_kernel_runtime_entry_syscall_dispatch_view_request_t
        runtime_entry_syscall_dispatch_view_request;
    size_t requested_syscall_return_view_count;
} latticra_kernel_runtime_entry_syscall_return_view_request_t;

typedef struct {
    size_t syscall_return_view_index;
    unsigned long syscall_return_view_token;
    unsigned long syscall_dispatch_view_token;
    unsigned long syscall_gate_view_token;
    unsigned long privilege_level_view_token;
    unsigned long pid_token;
    unsigned long syscall_return_view_rank;
    unsigned long syscall_dispatch_view_rank;
    unsigned long syscall_number;
    unsigned long handler_slot;
    unsigned long dispatch_slot;
    unsigned long return_slot;
    unsigned long result_register_slot;
    unsigned long errno_slot;
    unsigned long argument_count;
    int syscall_dispatch_view_declared;
    int syscall_return_view_declared;
    int syscall_return_declared;
    int syscall_result_window_declared;
    int user_mode_return_declared;
    int kernel_mode_exit_declared;
    char process_label[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_LABEL_MAX];
    char syscall_return_view_class[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_LABEL_MAX];
    char syscall_return_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_LABEL_MAX];
    char authority_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_LABEL_MAX];
    int declared;
    int syscall_return_view_planned;
    int syscall_return_planned;
    int syscall_result_copy_planned;
    int privilege_return_planned;
    int interrupt_return_planned;
    int runtime_entry_exited;
    int execution_entered;
    int context_switch_planned;
    int runtime_entry_syscall_return_view_allowed;
    int runtime_entry_syscall_dispatch_view_allowed;
    int runtime_entry_syscall_gate_view_allowed;
    int runtime_entry_privilege_level_view_allowed;
    int runtime_entry_allowed;
    int context_switch_allowed;
    int privilege_transition_allowed;
    int syscall_gate_allowed;
    int syscall_dispatch_allowed;
    int syscall_argument_copy_allowed;
    int syscall_instruction_allowed;
    int syscall_handler_allowed;
    int syscall_return_allowed;
    int syscall_result_copy_allowed;
    int interrupt_return_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_syscall_return_view_entry_t;

typedef struct {
    latticra_status_t status;
    char syscall_return_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_LABEL_MAX];
    char policy_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_LABEL_MAX];
    latticra_kernel_runtime_entry_syscall_dispatch_view_result_t
        runtime_entry_syscall_dispatch_view;
    latticra_kernel_runtime_entry_syscall_return_view_entry_t
        syscall_return_views[
            LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_MAX];
    size_t syscall_return_view_count;
    int no_effect;
    int runtime_entry_syscall_return_view_allowed;
    int runtime_entry_syscall_dispatch_view_allowed;
    int runtime_entry_syscall_gate_view_allowed;
    int runtime_entry_privilege_level_view_allowed;
    int runtime_entry_allowed;
    int context_switch_allowed;
    int privilege_transition_allowed;
    int syscall_gate_allowed;
    int syscall_dispatch_allowed;
    int syscall_argument_copy_allowed;
    int syscall_instruction_allowed;
    int syscall_handler_allowed;
    int syscall_return_allowed;
    int syscall_result_copy_allowed;
    int interrupt_return_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_syscall_return_view_result_t;

latticra_status_t
latticra_kernel_runtime_entry_syscall_return_view_default_request(
    latticra_kernel_runtime_entry_syscall_return_view_request_t *request);

latticra_status_t
latticra_kernel_runtime_entry_syscall_return_view_evaluate(
    const latticra_kernel_runtime_entry_syscall_return_view_request_t *request,
    latticra_kernel_runtime_entry_syscall_return_view_result_t *result);

latticra_status_t latticra_kernel_runtime_entry_syscall_return_view_report(
    const latticra_kernel_runtime_entry_syscall_return_view_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
