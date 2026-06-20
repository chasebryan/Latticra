#include "latticra/kernel_state_machine.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void machine_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

latticra_status_t latticra_kernel_state_machine_init(
    latticra_kernel_state_machine_t *machine) {
    if (machine == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(machine, 0, sizeof(*machine));
    machine->current_state = LATTICRA_KERNEL_STATE_CREATED;
    machine_copy(machine->machine_status, sizeof(machine->machine_status), "created");
    machine->state_mutated = 0;
    machine->external_effect_performed = 0;
    machine->network_allowed = 0;
    machine->evidence_level = 9u;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_kernel_state_machine_default_step_request(
    latticra_kernel_state_machine_step_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_memory_map_default_request(&request->memory_map_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_process_table_default_request(&request->process_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_syscall_table_default_request(&request->syscall_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_ipc_table_default_request(&request->ipc_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_vfs_namespace_default_request(&request->vfs_namespace_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_device_registry_default_request(&request->device_registry_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_driver_catalog_default_request(&request->driver_catalog_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_interrupt_table_default_request(&request->interrupt_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_timer_source_default_request(&request->timer_source_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->timer_source_request.interrupt_table_request = request->interrupt_table_request;
    if (latticra_kernel_scheduler_tick_default_request(&request->scheduler_tick_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_tick_request.timer_source_request = request->timer_source_request;
    if (latticra_kernel_run_queue_default_request(&request->run_queue_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->run_queue_request.scheduler_tick_request = request->scheduler_tick_request;
    if (latticra_kernel_context_switch_default_request(&request->context_switch_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->context_switch_request.run_queue_request = request->run_queue_request;
    if (latticra_kernel_time_accounting_default_request(&request->time_accounting_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->time_accounting_request.context_switch_request = request->context_switch_request;
    if (latticra_kernel_preemption_default_request(&request->preemption_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->preemption_request.time_accounting_request = request->time_accounting_request;
    if (latticra_kernel_scheduler_credit_default_request(
            &request->scheduler_credit_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_credit_request.preemption_request = request->preemption_request;
    if (latticra_kernel_scheduler_selection_default_request(
            &request->scheduler_selection_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_selection_request.scheduler_credit_request =
        request->scheduler_credit_request;
    if (latticra_kernel_scheduler_dispatch_default_request(
            &request->scheduler_dispatch_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_dispatch_request.scheduler_selection_request =
        request->scheduler_selection_request;
    if (latticra_kernel_scheduler_handoff_default_request(
            &request->scheduler_handoff_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_handoff_request.scheduler_dispatch_request =
        request->scheduler_dispatch_request;
    if (latticra_kernel_scheduler_activation_default_request(
            &request->scheduler_activation_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_activation_request.scheduler_handoff_request =
        request->scheduler_handoff_request;
    if (latticra_kernel_scheduler_run_entry_default_request(
            &request->scheduler_run_entry_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_run_entry_request.scheduler_activation_request =
        request->scheduler_activation_request;
    if (latticra_kernel_runtime_entry_admission_default_request(
            &request->runtime_entry_admission_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_admission_request.scheduler_run_entry_request =
        request->scheduler_run_entry_request;
    if (latticra_kernel_runtime_entry_frame_default_request(
            &request->runtime_entry_frame_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_frame_request.runtime_entry_admission_request =
        request->runtime_entry_admission_request;
    if (latticra_kernel_runtime_entry_register_view_default_request(
            &request->runtime_entry_register_view_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_register_view_request.runtime_entry_frame_request =
        request->runtime_entry_frame_request;
    if (latticra_kernel_runtime_entry_stack_view_default_request(
            &request->runtime_entry_stack_view_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_stack_view_request.
        runtime_entry_register_view_request =
        request->runtime_entry_register_view_request;
    if (latticra_kernel_runtime_entry_address_space_view_default_request(
            &request->runtime_entry_address_space_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_address_space_view_request.
        runtime_entry_stack_view_request =
        request->runtime_entry_stack_view_request;
    if (latticra_kernel_runtime_entry_privilege_level_view_default_request(
            &request->runtime_entry_privilege_level_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_privilege_level_view_request.
        runtime_entry_address_space_view_request =
        request->runtime_entry_address_space_view_request;
    if (latticra_kernel_runtime_entry_syscall_gate_view_default_request(
            &request->runtime_entry_syscall_gate_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_syscall_gate_view_request.
        runtime_entry_privilege_level_view_request =
        request->runtime_entry_privilege_level_view_request;
    if (latticra_kernel_runtime_entry_syscall_dispatch_view_default_request(
            &request->runtime_entry_syscall_dispatch_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_syscall_dispatch_view_request.
        runtime_entry_syscall_gate_view_request =
        request->runtime_entry_syscall_gate_view_request;
    if (latticra_kernel_runtime_entry_syscall_return_view_default_request(
            &request->runtime_entry_syscall_return_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_syscall_return_view_request.
        runtime_entry_syscall_dispatch_view_request =
        request->runtime_entry_syscall_dispatch_view_request;
    if (latticra_kernel_runtime_entry_syscall_exit_view_default_request(
            &request->runtime_entry_syscall_exit_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_syscall_exit_view_request.
        runtime_entry_syscall_return_view_request =
        request->runtime_entry_syscall_return_view_request;
    if (latticra_kernel_runtime_entry_user_mode_resume_view_default_request(
            &request->runtime_entry_user_mode_resume_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_user_mode_resume_view_request.
        runtime_entry_syscall_exit_view_request =
        request->runtime_entry_syscall_exit_view_request;
    if (latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
            &request->runtime_entry_post_resume_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_post_resume_observation_view_request.
        runtime_entry_user_mode_resume_view_request =
        request->runtime_entry_user_mode_resume_view_request;
    if (latticra_kernel_runtime_entry_scheduler_return_observation_view_default_request(
            &request->runtime_entry_scheduler_return_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_scheduler_return_observation_view_request.
        runtime_entry_post_resume_observation_view_request =
        request->runtime_entry_post_resume_observation_view_request;
    if (latticra_kernel_runtime_entry_process_return_observation_view_default_request(
            &request->runtime_entry_process_return_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_process_return_observation_view_request.
        runtime_entry_scheduler_return_observation_view_request =
        request->runtime_entry_scheduler_return_observation_view_request;
    if (latticra_kernel_runtime_entry_idle_return_observation_view_default_request(
            &request->runtime_entry_idle_return_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_idle_return_observation_view_request.
        runtime_entry_process_return_observation_view_request =
        request->runtime_entry_process_return_observation_view_request;
    if (latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            &request->runtime_entry_quiescent_return_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_quiescent_return_observation_view_request.
        runtime_entry_idle_return_observation_view_request =
        request->runtime_entry_idle_return_observation_view_request;
    if (latticra_kernel_runtime_entry_persistence_boundary_observation_view_default_request(
            &request->runtime_entry_persistence_boundary_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_persistence_boundary_observation_view_request.
        runtime_entry_quiescent_return_observation_view_request =
        request->runtime_entry_quiescent_return_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_boundary_observation_view_default_request(
            &request->runtime_entry_recovery_boundary_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_boundary_observation_view_request.
        runtime_entry_persistence_boundary_observation_view_request =
        request->runtime_entry_persistence_boundary_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &request->runtime_entry_recovery_plan_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_plan_observation_view_request.
        runtime_entry_recovery_boundary_observation_view_request =
        request->runtime_entry_recovery_boundary_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_disposition_observation_view_default_request(
            &request->runtime_entry_recovery_disposition_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_disposition_observation_view_request.
        runtime_entry_recovery_plan_observation_view_request =
        request->runtime_entry_recovery_plan_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_outcome_observation_view_default_request(
            &request->runtime_entry_recovery_outcome_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_outcome_observation_view_request.
        runtime_entry_recovery_disposition_observation_view_request =
        request->runtime_entry_recovery_disposition_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_closeout_observation_view_default_request(
            &request->runtime_entry_recovery_closeout_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_closeout_observation_view_request.
        runtime_entry_recovery_outcome_observation_view_request =
        request->runtime_entry_recovery_outcome_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &request->runtime_entry_recovery_audit_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_observation_view_request.
        runtime_entry_recovery_closeout_observation_view_request =
        request->runtime_entry_recovery_closeout_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_observation_view_request.
        runtime_entry_recovery_audit_observation_view_request =
        request->runtime_entry_recovery_audit_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_observation_view_request.
        runtime_entry_recovery_audit_review_observation_view_request =
        request->runtime_entry_recovery_audit_review_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request;
    request->target_state = LATTICRA_KERNEL_STATE_INITIALIZED;
    request->gate = LATTICRA_KERNEL_STATE_GATE_DENY;
    return LATTICRA_STATUS_OK;
}

static void append_log(
    latticra_kernel_state_machine_t *machine,
    const latticra_kernel_state_machine_step_result_t *result) {
    latticra_kernel_state_machine_log_entry_t *entry;
    if (machine->log_count >= LATTICRA_KERNEL_STATE_MACHINE_LOG_MAX) return;
    entry = &machine->log[machine->log_count];
    memset(entry, 0, sizeof(*entry));
    entry->from_state = result->machine_state_before;
    entry->to_state = result->machine_state_after;
    machine_copy(entry->status, sizeof(entry->status), result->step_status);
    entry->state_change_performed = result->state_mutated;
    entry->external_effect_performed = result->external_effect_performed;
    entry->network_allowed = result->network_allowed;
    machine->log_count += 1u;
}

static void seed_step_result(
    const latticra_kernel_state_machine_t *machine,
    latticra_kernel_state_machine_step_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    machine_copy(result->step_status, sizeof(result->step_status), "pending");
    result->machine_state_before = machine ? machine->current_state : LATTICRA_KERNEL_STATE_CREATED;
    result->machine_state_after = result->machine_state_before;
    result->state_mutated = 0;
    result->external_effect_performed = 0;
    result->network_allowed = 0;
    result->evidence_level = 9u;
}

latticra_status_t latticra_kernel_state_machine_step(
    latticra_kernel_state_machine_t *machine,
    const latticra_kernel_state_machine_step_request_t *request,
    latticra_kernel_state_machine_step_result_t *result) {
    latticra_kernel_state_request_t *transition_request_storage;
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_step_result(machine, result);

    if (machine == 0 || request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        machine_copy(result->step_status, sizeof(result->step_status), "null-argument");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    transition_request_storage =
        (latticra_kernel_state_request_t *)calloc(1u, sizeof(*transition_request_storage));
    if (transition_request_storage == 0) {
        result->status = LATTICRA_STATUS_ALLOCATION_FAILED;
        machine_copy(result->step_status, sizeof(result->step_status),
            "transition-storage-unavailable");
        return result->status;
    }

#define transition_request (*transition_request_storage)
    transition_request.memory_map_request = request->memory_map_request;
    transition_request.process_table_request = request->process_table_request;
    transition_request.syscall_table_request = request->syscall_table_request;
    transition_request.ipc_table_request = request->ipc_table_request;
    transition_request.vfs_namespace_request = request->vfs_namespace_request;
    transition_request.device_registry_request = request->device_registry_request;
    transition_request.driver_catalog_request = request->driver_catalog_request;
    transition_request.interrupt_table_request = request->interrupt_table_request;
    transition_request.timer_source_request = request->timer_source_request;
    transition_request.scheduler_tick_request = request->scheduler_tick_request;
    transition_request.run_queue_request = request->run_queue_request;
    transition_request.context_switch_request = request->context_switch_request;
    transition_request.time_accounting_request = request->time_accounting_request;
    transition_request.preemption_request = request->preemption_request;
    transition_request.scheduler_credit_request = request->scheduler_credit_request;
    transition_request.scheduler_selection_request =
        request->scheduler_selection_request;
    transition_request.scheduler_dispatch_request =
        request->scheduler_dispatch_request;
    transition_request.scheduler_handoff_request =
        request->scheduler_handoff_request;
    transition_request.scheduler_activation_request =
        request->scheduler_activation_request;
    transition_request.scheduler_run_entry_request =
        request->scheduler_run_entry_request;
    transition_request.runtime_entry_admission_request =
        request->runtime_entry_admission_request;
    transition_request.runtime_entry_frame_request =
        request->runtime_entry_frame_request;
    transition_request.runtime_entry_register_view_request =
        request->runtime_entry_register_view_request;
    transition_request.runtime_entry_stack_view_request =
        request->runtime_entry_stack_view_request;
    transition_request.runtime_entry_address_space_view_request =
        request->runtime_entry_address_space_view_request;
    transition_request.runtime_entry_privilege_level_view_request =
        request->runtime_entry_privilege_level_view_request;
    transition_request.runtime_entry_syscall_gate_view_request =
        request->runtime_entry_syscall_gate_view_request;
    transition_request.runtime_entry_syscall_dispatch_view_request =
        request->runtime_entry_syscall_dispatch_view_request;
    transition_request.runtime_entry_syscall_return_view_request =
        request->runtime_entry_syscall_return_view_request;
    transition_request.runtime_entry_syscall_exit_view_request =
        request->runtime_entry_syscall_exit_view_request;
    transition_request.runtime_entry_user_mode_resume_view_request =
        request->runtime_entry_user_mode_resume_view_request;
    transition_request.runtime_entry_post_resume_observation_view_request =
        request->runtime_entry_post_resume_observation_view_request;
    transition_request.runtime_entry_scheduler_return_observation_view_request =
        request->runtime_entry_scheduler_return_observation_view_request;
    transition_request.runtime_entry_process_return_observation_view_request =
        request->runtime_entry_process_return_observation_view_request;
    transition_request.runtime_entry_idle_return_observation_view_request =
        request->runtime_entry_idle_return_observation_view_request;
    transition_request.runtime_entry_quiescent_return_observation_view_request =
        request->runtime_entry_quiescent_return_observation_view_request;
    transition_request.runtime_entry_persistence_boundary_observation_view_request =
        request->runtime_entry_persistence_boundary_observation_view_request;
    transition_request.runtime_entry_recovery_boundary_observation_view_request =
        request->runtime_entry_recovery_boundary_observation_view_request;
    transition_request.runtime_entry_recovery_plan_observation_view_request =
        request->runtime_entry_recovery_plan_observation_view_request;
    transition_request.runtime_entry_recovery_disposition_observation_view_request =
        request->runtime_entry_recovery_disposition_observation_view_request;
    transition_request.runtime_entry_recovery_outcome_observation_view_request =
        request->runtime_entry_recovery_outcome_observation_view_request;
    transition_request.runtime_entry_recovery_closeout_observation_view_request =
        request->runtime_entry_recovery_closeout_observation_view_request;
    transition_request.runtime_entry_recovery_audit_observation_view_request =
        request->runtime_entry_recovery_audit_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_observation_view_request =
        request->runtime_entry_recovery_audit_review_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_review_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request;
    transition_request.runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_request =
        request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_request;
    transition_request.current_state = machine->current_state;
    transition_request.target_state = request->target_state;
    transition_request.gate = request->gate;

    status = latticra_kernel_state_transition(&transition_request, &result->transition);
#undef transition_request
    free(transition_request_storage);
    result->status = status;
    result->machine_state_before = machine->current_state;
    result->machine_state_after = result->transition.next_state;
    result->state_mutated = result->transition.state_change_performed;
    result->external_effect_performed = result->transition.external_effect_performed;
    result->network_allowed = result->transition.network_allowed;
    machine->network_allowed = machine->network_allowed || result->network_allowed;

    if (status != LATTICRA_STATUS_OK) {
        machine_copy(result->step_status, sizeof(result->step_status), "transition-error");
        append_log(machine, result);
        return status;
    }

    if (result->transition.denied) {
        machine_copy(result->step_status, sizeof(result->step_status), "transition-denied");
        append_log(machine, result);
        return result->status;
    }

    if (result->state_mutated) {
        machine->current_state = result->transition.next_state;
        machine->state_mutated = 1;
        machine_copy(machine->machine_status, sizeof(machine->machine_status),
            latticra_kernel_state_label(machine->current_state));
        machine_copy(result->step_status, sizeof(result->step_status), "machine-mutated");
    } else {
        machine_copy(result->step_status, sizeof(result->step_status), "machine-unchanged");
    }

    machine->external_effect_performed = machine->external_effect_performed || result->external_effect_performed;
    append_log(machine, result);
    return result->status;
}

static latticra_status_t append_text(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const char *fmt,
    ...) {
    int written;
    va_list args;
    if (*used >= buffer_len) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    va_start(args, fmt);
    written = vsnprintf(buffer + *used, buffer_len - *used, fmt, args);
    va_end(args);
    if (written < 0 || (size_t)written >= buffer_len - *used) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    *used += (size_t)written;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_kernel_state_machine_report(
    const latticra_kernel_state_machine_t *machine,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (machine == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL STATE MACHINE REPORT\n"
        "machine_status=%s\n"
        "current_state=%s\n"
        "log_count=%lu\n"
        "state_mutated=%d\n"
        "external_effect_performed=%d\n"
        "network_allowed=%d\n"
        "evidence_level=%u\n",
        machine->machine_status,
        latticra_kernel_state_label(machine->current_state),
        (unsigned long)machine->log_count,
        machine->state_mutated,
        machine->external_effect_performed,
        machine->network_allowed,
        machine->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < machine->log_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "log[%lu].from=%s\n"
            "log[%lu].to=%s\n"
            "log[%lu].status=%s\n"
            "log[%lu].state_change_performed=%d\n"
            "log[%lu].external_effect_performed=%d\n"
            "log[%lu].network_allowed=%d\n",
            (unsigned long)i,
            latticra_kernel_state_label(machine->log[i].from_state),
            (unsigned long)i,
            latticra_kernel_state_label(machine->log[i].to_state),
            (unsigned long)i,
            machine->log[i].status,
            (unsigned long)i,
            machine->log[i].state_change_performed,
            (unsigned long)i,
            machine->log[i].external_effect_performed,
            (unsigned long)i,
            machine->log[i].network_allowed);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
