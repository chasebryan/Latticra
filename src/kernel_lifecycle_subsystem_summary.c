// SPDX-License-Identifier: AGPL-3.0-or-later

#include "latticra/kernel_lifecycle_subsystem_summary.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void summary_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_summary_result(
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    summary_copy(result->summary_status, sizeof(result->summary_status), "pending");
    summary_copy(result->final_state, sizeof(result->final_state), "created");
    summary_copy(result->nucleus_coupling_status,
        sizeof(result->nucleus_coupling_status), "pending");
    summary_copy(result->os_readiness_status, sizeof(result->os_readiness_status),
        "os-metadata-pending");
    result->nucleus_coupling_ready = 0;
    result->nucleus_no_effect_chain_ok = 0;
    result->nucleus_boot_allowed = 0;
    result->nucleus_runtime_entry_allowed = 0;
    result->nucleus_scheduler_run_entry_allowed = 0;
    result->nucleus_context_switch_allowed = 0;
    result->nucleus_register_save_allowed = 0;
    result->nucleus_register_restore_allowed = 0;
    result->nucleus_host_effect_allowed = 0;
    result->runtime_entry_recovery_audit_observation_view_allowed = 0;
    result->runtime_entry_recovery_closeout_observation_view_allowed = 0;
    result->runtime_entry_recovery_outcome_observation_view_allowed = 0;
    result->runtime_entry_recovery_disposition_observation_view_allowed = 0;
    result->runtime_entry_recovery_plan_observation_view_allowed = 0;
    result->runtime_entry_recovery_boundary_observation_view_allowed = 0;
    result->runtime_entry_persistence_boundary_observation_view_allowed = 0;
    result->runtime_entry_quiescent_return_observation_view_allowed = 0;
    result->runtime_entry_idle_return_observation_view_allowed = 0;
    result->runtime_entry_process_return_observation_view_allowed = 0;
    result->runtime_entry_scheduler_return_observation_view_allowed = 0;
    result->runtime_entry_post_resume_observation_view_allowed = 0;
    result->runtime_entry_user_mode_resume_view_allowed = 0;
    result->runtime_entry_syscall_exit_view_allowed = 0;
    result->runtime_entry_syscall_return_view_allowed = 0;
    result->runtime_entry_syscall_dispatch_view_allowed = 0;
    result->runtime_entry_syscall_gate_view_allowed = 0;
    result->runtime_entry_privilege_level_view_allowed = 0;
    result->runtime_entry_address_space_view_allowed = 0;
    result->runtime_entry_stack_view_allowed = 0;
    result->runtime_entry_register_view_allowed = 0;
    result->runtime_entry_frame_allowed = 0;
    result->runtime_entry_admission_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->recovery_boundary_observation_allowed = 0;
    result->recovery_boundary_allowed = 0;
    result->recovery_plan_allowed = 0;
    result->recovery_plan_observation_allowed = 0;
    result->recovery_disposition_allowed = 0;
    result->recovery_disposition_observation_allowed = 0;
    result->recovery_outcome_allowed = 0;
    result->recovery_outcome_observation_allowed = 0;
    result->recovery_audit_allowed = 0;
    result->recovery_audit_observation_allowed = 0;
    result->recovery_closeout_allowed = 0;
    result->recovery_closeout_observation_allowed = 0;
    result->persistence_boundary_observation_allowed = 0;
    result->persistence_boundary_allowed = 0;
    result->persistence_commit_allowed = 0;
    result->quiescent_return_observation_allowed = 0;
    result->quiescent_return_allowed = 0;
    result->quiescent_state_read_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->scheduler_selection_allowed = 0;
    result->scheduler_dispatch_allowed = 0;
    result->scheduler_handoff_allowed = 0;
    result->scheduler_activation_allowed = 0;
    result->scheduler_run_entry_allowed = 0;
    result->memory_allocation_allowed = 0;
    result->process_spawn_allowed = 0;
    result->syscall_dispatch_allowed = 0;
    result->ipc_send_allowed = 0;
    result->ipc_receive_allowed = 0;
    result->ipc_queue_mutation_allowed = 0;
    result->filesystem_lookup_allowed = 0;
    result->filesystem_read_allowed = 0;
    result->filesystem_write_allowed = 0;
    result->namespace_mutation_allowed = 0;
    result->device_open_allowed = 0;
    result->device_read_allowed = 0;
    result->device_write_allowed = 0;
    result->driver_probe_allowed = 0;
    result->driver_load_allowed = 0;
    result->driver_bind_allowed = 0;
    result->network_allowed = 0;
    result->interrupt_allowed = 0;
    result->interrupt_mask_allowed = 0;
    result->interrupt_unmask_allowed = 0;
    result->interrupt_dispatch_allowed = 0;
    result->interrupt_ack_allowed = 0;
    result->timer_tick_allowed = 0;
    result->timer_arm_allowed = 0;
    result->timer_disarm_allowed = 0;
    result->scheduler_tick_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->enqueue_allowed = 0;
    result->dequeue_allowed = 0;
    result->dispatch_allowed = 0;
    result->context_switch_allowed = 0;
    result->register_save_allowed = 0;
    result->register_restore_allowed = 0;
    result->stack_switch_allowed = 0;
    result->address_space_switch_allowed = 0;
    result->preemption_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->cpu_usage_write_allowed = 0;
    result->quota_update_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->process_wake_allowed = 0;
    result->persistence_allowed = 0;
    result->recovery_authority_allowed = 0;
    result->dma_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->no_external_effect_chain = 1;
    result->evidence_level = 11u;
}

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_default_request(
    latticra_kernel_lifecycle_subsystem_summary_request_t *request) {
    latticra_status_t status;

    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));

    status = latticra_kernel_lifecycle_default_request(&request->lifecycle_request);
    if (status != LATTICRA_STATUS_OK) return status;

    status = latticra_kernel_subsystem_registry_default_request(&request->registry_request);
    if (status != LATTICRA_STATUS_OK) return status;

    request->lifecycle_request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request->lifecycle_request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY;
    request->lifecycle_request.max_steps = LATTICRA_KERNEL_LIFECYCLE_STEP_MAX;
    return LATTICRA_STATUS_OK;
}

static int state_at_or_after(
    latticra_kernel_state_kind_t final_state,
    latticra_kernel_state_kind_t required_state) {
    return final_state >= required_state;
}

static int lifecycle_ready_for_subsystem(
    latticra_kernel_state_kind_t final_state,
    latticra_kernel_subsystem_kind_t kind) {
    switch (kind) {
        case LATTICRA_KERNEL_SUBSYSTEM_BOOT:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_INITIALIZED);
        case LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SCHEDULER_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_MEMORY:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_MEMORY_MAP_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_PROCESS:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_DEVICE:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_NETWORK:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_RUNTIME:
        case LATTICRA_KERNEL_SUBSYSTEM_SECURITY:
        case LATTICRA_KERNEL_SUBSYSTEM_COUNT:
        default:
            return 0;
    }
}

static const char *lifecycle_relation_for(
    latticra_kernel_state_kind_t final_state,
    latticra_kernel_subsystem_kind_t kind) {
    switch (kind) {
        case LATTICRA_KERNEL_SUBSYSTEM_BOOT:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_INITIALIZED) ?
                "boot-sequence-seeded" : "boot-sequence-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_RUNTIME:
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-recovery-audit-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-recovery-closeout-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-recovery-outcome-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-recovery-disposition-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-recovery-plan-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-recovery-boundary-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-persistence-boundary-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-quiescent-return-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-idle-return-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-process-return-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-scheduler-return-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_READY)) {
                return "runtime-entry-post-resume-observation-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_READY)) {
                return "runtime-entry-user-mode-resume-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_READY)) {
                return "runtime-entry-syscall-exit-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_READY)) {
                return "runtime-entry-syscall-return-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_READY)) {
                return "runtime-entry-syscall-dispatch-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_READY)) {
                return "runtime-entry-syscall-gate-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_READY)) {
                return "runtime-entry-privilege-level-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_READY)) {
                return "runtime-entry-address-space-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_STACK_VIEW_READY)) {
                return "runtime-entry-stack-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_REGISTER_VIEW_READY)) {
                return "runtime-entry-register-view-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_FRAME_READY)) {
                return "runtime-entry-frame-ready";
            }
            return state_at_or_after(final_state,
                LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADMISSION_READY) ?
                "runtime-entry-admission-ready" : "runtime-not-entered";
        case LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER:
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_SCHEDULER_RUN_ENTRY_READY)) {
                return "scheduler-run-entry-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_SCHEDULER_ACTIVATION_READY)) {
                return "scheduler-activation-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_SCHEDULER_HANDOFF_READY)) {
                return "scheduler-handoff-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY)) {
                return "scheduler-dispatch-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY)) {
                return "scheduler-selection-ready";
            }
            if (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY)) {
                return "scheduler-credit-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_PREEMPTION_READY)) {
                return "preemption-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY)) {
                return "time-accounting-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY)) {
                return "context-switch-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_RUN_QUEUE_READY)) {
                return "run-queue-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY)) {
                return "scheduler-tick-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY)) {
                return "timer-source-ready";
            }
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SCHEDULER_READY) ?
                "scheduler-ready-metadata" : "scheduler-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_MEMORY:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_MEMORY_MAP_READY) ?
                "memory-map-ready" : "memory-map-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_PROCESS:
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_IPC_TABLE_READY)) {
                return "ipc-table-ready";
            }
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY) ?
                "process-table-ready" : "process-table-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY) ?
                "vfs-namespace-ready" : "vfs-namespace-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_NETWORK:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY) ?
                "network-syscall-metadata-ready" : "network-syscall-metadata-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_DEVICE:
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY)) {
                return "interrupt-table-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY)) {
                return "driver-catalog-ready";
            }
            if (state_at_or_after(final_state, LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY)) {
                return "device-registry-ready";
            }
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY) ?
                "device-syscall-metadata-ready" : "device-syscall-metadata-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_SECURITY:
            return "security-not-production-boundary";
        case LATTICRA_KERNEL_SUBSYSTEM_COUNT:
        default:
            return "unknown";
    }
}

static const char *authority_status_for(latticra_kernel_subsystem_kind_t kind) {
    switch (kind) {
        case LATTICRA_KERNEL_SUBSYSTEM_BOOT:
            return "boot-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_RUNTIME:
            return "runtime-entry-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER:
            return "scheduler-execution-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_MEMORY:
            return "memory-allocation-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_PROCESS:
            return "process-execution-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM:
            return "filesystem-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_NETWORK:
            return "network-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_DEVICE:
            return "device-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_SECURITY:
            return "not-production-boundary";
        case LATTICRA_KERNEL_SUBSYSTEM_COUNT:
        default:
            return "unknown-denied";
    }
}

static void fill_summary_entries(
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    size_t i;
    size_t count = result->registry.entry_count;

    if (count > LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_ENTRY_MAX) {
        count = LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_ENTRY_MAX;
    }

    result->entry_count = count;

    for (i = 0u; i < count; ++i) {
        latticra_kernel_lifecycle_subsystem_summary_entry_t *entry = &result->entries[i];
        const latticra_kernel_subsystem_entry_t *registry_entry = &result->registry.entries[i];

        memset(entry, 0, sizeof(*entry));
        entry->kind = registry_entry->kind;
        summary_copy(entry->name, sizeof(entry->name), registry_entry->name);
        summary_copy(entry->registry_status, sizeof(entry->registry_status), registry_entry->status);
        summary_copy(entry->lifecycle_relation, sizeof(entry->lifecycle_relation),
            lifecycle_relation_for(result->lifecycle.final_state, registry_entry->kind));
        summary_copy(entry->authority_status, sizeof(entry->authority_status),
            authority_status_for(registry_entry->kind));
        summary_copy(entry->effect_boundary, sizeof(entry->effect_boundary), registry_entry->effect_boundary);
        entry->lifecycle_ready = lifecycle_ready_for_subsystem(
            result->lifecycle.final_state,
            registry_entry->kind);
        entry->authority_allowed = 0;
        entry->network_allowed = registry_entry->network_allowed;
        entry->no_effect = registry_entry->no_effect;
        entry->evidence_level = registry_entry->evidence_level;
    }
}

static latticra_status_t evaluate_nucleus_coupling(
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_request_t
        persistence_boundary_request;
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        persistence_boundary_view;
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_request_t
        recovery_boundary_request;
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        recovery_boundary_view;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        recovery_plan_request;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        recovery_plan_view;
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_request_t
        recovery_disposition_request;
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        recovery_disposition_view;
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_request_t
        recovery_outcome_request;
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        recovery_outcome_view;
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_request_t
        recovery_closeout_request;
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        recovery_closeout_view;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        recovery_audit_request;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        recovery_audit_view;
    latticra_nucleus_kernel_coupling_request_t coupling_request;
    latticra_status_t status;

    status = latticra_nucleus_kernel_coupling_default_nucleus_plan(&plan);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_default_request(
            &persistence_boundary_request);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_evaluate(
            &persistence_boundary_request, &persistence_boundary_view);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_default_request(
            &recovery_boundary_request);
    if (status != LATTICRA_STATUS_OK) return status;

    recovery_boundary_request.
        runtime_entry_persistence_boundary_observation_view_request =
        persistence_boundary_request;
    status =
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_evaluate(
            &recovery_boundary_request, &recovery_boundary_view);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &recovery_plan_request);
    if (status != LATTICRA_STATUS_OK) return status;
    recovery_plan_request.runtime_entry_recovery_boundary_observation_view_request =
        recovery_boundary_request;
    status =
        latticra_kernel_runtime_entry_recovery_plan_observation_view_evaluate(
            &recovery_plan_request, &recovery_plan_view);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_recovery_disposition_observation_view_default_request(
            &recovery_disposition_request);
    if (status != LATTICRA_STATUS_OK) return status;
    recovery_disposition_request.
        runtime_entry_recovery_plan_observation_view_request =
        recovery_plan_request;
    status =
        latticra_kernel_runtime_entry_recovery_disposition_observation_view_evaluate(
            &recovery_disposition_request, &recovery_disposition_view);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_recovery_outcome_observation_view_default_request(
            &recovery_outcome_request);
    if (status != LATTICRA_STATUS_OK) return status;
    recovery_outcome_request.
        runtime_entry_recovery_disposition_observation_view_request =
        recovery_disposition_request;
    status =
        latticra_kernel_runtime_entry_recovery_outcome_observation_view_evaluate(
            &recovery_outcome_request, &recovery_outcome_view);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_recovery_closeout_observation_view_default_request(
            &recovery_closeout_request);
    if (status != LATTICRA_STATUS_OK) return status;
    recovery_closeout_request.
        runtime_entry_recovery_outcome_observation_view_request =
        recovery_outcome_request;
    status =
        latticra_kernel_runtime_entry_recovery_closeout_observation_view_evaluate(
            &recovery_closeout_request, &recovery_closeout_view);
    if (status != LATTICRA_STATUS_OK) return status;

    status =
        latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &recovery_audit_request);
    if (status != LATTICRA_STATUS_OK) return status;
    recovery_audit_request.
        runtime_entry_recovery_closeout_observation_view_request =
        recovery_closeout_request;
    status =
        latticra_kernel_runtime_entry_recovery_audit_observation_view_evaluate(
            &recovery_audit_request, &recovery_audit_view);
    if (status != LATTICRA_STATUS_OK) return status;

    status = latticra_nucleus_kernel_coupling_default_request(&coupling_request);
    if (status != LATTICRA_STATUS_OK) return status;

    coupling_request.nucleus_plan = &plan;
    coupling_request.kernel_registry = &result->registry;
    coupling_request.kernel_lifecycle = &result->lifecycle;
    coupling_request.runtime_register_view =
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view.
            runtime_entry_scheduler_return_observation_view.
            runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.
            runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.
            runtime_entry_address_space_view.
            runtime_entry_stack_view.
            runtime_entry_register_view;
    coupling_request.runtime_process_return_observation_view =
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view;
    coupling_request.runtime_idle_return_observation_view =
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view;
    coupling_request.runtime_quiescent_return_observation_view =
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view;
    coupling_request.runtime_persistence_boundary_observation_view =
        &persistence_boundary_view;
    coupling_request.runtime_recovery_boundary_observation_view =
        &recovery_boundary_view;
    coupling_request.runtime_recovery_plan_observation_view =
        &recovery_plan_view;
    coupling_request.runtime_recovery_disposition_observation_view =
        &recovery_disposition_view;
    coupling_request.runtime_recovery_outcome_observation_view =
        &recovery_outcome_view;
    coupling_request.runtime_recovery_closeout_observation_view =
        &recovery_closeout_view;
    coupling_request.runtime_recovery_audit_observation_view =
        &recovery_audit_view;
    return latticra_nucleus_kernel_coupling_evaluate(
        &coupling_request, &result->nucleus_coupling);
}

static void finalize_summary(
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    const latticra_nucleus_kernel_coupling_record_t *coupling =
        &result->nucleus_coupling.record;

    summary_copy(result->final_state, sizeof(result->final_state),
        latticra_kernel_state_label(result->lifecycle.final_state));
    summary_copy(result->nucleus_coupling_status,
        sizeof(result->nucleus_coupling_status), coupling->readiness_status);
    summary_copy(result->os_readiness_status, sizeof(result->os_readiness_status),
        coupling->os_readiness_status);

    result->lifecycle_step_count = result->lifecycle.step_count;
    result->lifecycle_state_change_count = result->lifecycle.state_change_count;
    result->lifecycle_complete = result->lifecycle.lifecycle_complete;
    result->lifecycle_state_mutated = result->lifecycle.state_change_count > 0u;
    result->external_effect_performed = result->lifecycle.external_effect_performed;
    result->network_allowed = result->lifecycle.network_allowed;
    result->registry_no_effect = result->registry.no_effect;
    result->nucleus_coupling_ready =
        coupling->classification ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_ONLY_READY &&
        coupling->denial == LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_OK;
    result->nucleus_no_effect_chain_ok = coupling->no_effect_chain_ok;
    result->nucleus_boot_allowed = coupling->boot_allowed;
    result->nucleus_runtime_entry_allowed = coupling->runtime_entry_allowed;
    result->nucleus_scheduler_run_entry_allowed =
        coupling->scheduler_run_entry_allowed;
    result->nucleus_context_switch_allowed = coupling->context_switch_allowed;
    result->nucleus_register_save_allowed = coupling->register_save_allowed;
    result->nucleus_register_restore_allowed = coupling->register_restore_allowed;
    result->nucleus_host_effect_allowed = coupling->host_effect_allowed;
    result->runtime_entry_recovery_audit_observation_view_allowed = 0;
    result->runtime_entry_recovery_closeout_observation_view_allowed = 0;
    result->runtime_entry_recovery_outcome_observation_view_allowed = 0;
    result->runtime_entry_recovery_disposition_observation_view_allowed = 0;
    result->runtime_entry_recovery_plan_observation_view_allowed = 0;
    result->runtime_entry_recovery_boundary_observation_view_allowed = 0;
    result->runtime_entry_persistence_boundary_observation_view_allowed = 0;
    result->runtime_entry_quiescent_return_observation_view_allowed = 0;
    result->runtime_entry_idle_return_observation_view_allowed = 0;
    result->runtime_entry_process_return_observation_view_allowed = 0;
    result->runtime_entry_scheduler_return_observation_view_allowed = 0;
    result->runtime_entry_post_resume_observation_view_allowed = 0;
    result->runtime_entry_user_mode_resume_view_allowed = 0;
    result->runtime_entry_syscall_exit_view_allowed = 0;
    result->runtime_entry_syscall_return_view_allowed = 0;
    result->runtime_entry_syscall_dispatch_view_allowed = 0;
    result->runtime_entry_syscall_gate_view_allowed = 0;
    result->runtime_entry_privilege_level_view_allowed = 0;
    result->runtime_entry_address_space_view_allowed = 0;
    result->runtime_entry_stack_view_allowed = 0;
    result->runtime_entry_register_view_allowed = 0;
    result->runtime_entry_frame_allowed = 0;
    result->runtime_entry_admission_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->recovery_boundary_observation_allowed = 0;
    result->recovery_boundary_allowed = 0;
    result->recovery_plan_allowed = 0;
    result->recovery_plan_observation_allowed = 0;
    result->recovery_disposition_allowed = 0;
    result->recovery_disposition_observation_allowed = 0;
    result->recovery_outcome_allowed = 0;
    result->recovery_outcome_observation_allowed = 0;
    result->recovery_audit_allowed = 0;
    result->recovery_audit_observation_allowed = 0;
    result->recovery_closeout_allowed = 0;
    result->recovery_closeout_observation_allowed = 0;
    result->persistence_boundary_observation_allowed = 0;
    result->persistence_boundary_allowed = 0;
    result->persistence_commit_allowed = 0;
    result->quiescent_return_observation_allowed = 0;
    result->quiescent_return_allowed = 0;
    result->quiescent_state_read_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->scheduler_selection_allowed = 0;
    result->scheduler_dispatch_allowed = 0;
    result->scheduler_handoff_allowed = 0;
    result->scheduler_activation_allowed = 0;
    result->scheduler_run_entry_allowed = 0;
    result->memory_allocation_allowed = 0;
    result->process_spawn_allowed = 0;
    result->syscall_dispatch_allowed = 0;
    result->ipc_send_allowed = 0;
    result->ipc_receive_allowed = 0;
    result->ipc_queue_mutation_allowed = 0;
    result->filesystem_lookup_allowed = 0;
    result->filesystem_read_allowed = 0;
    result->filesystem_write_allowed = 0;
    result->namespace_mutation_allowed = 0;
    result->device_open_allowed = 0;
    result->device_read_allowed = 0;
    result->device_write_allowed = 0;
    result->driver_probe_allowed = 0;
    result->driver_load_allowed = 0;
    result->driver_bind_allowed = 0;
    result->interrupt_allowed = 0;
    result->interrupt_mask_allowed = 0;
    result->interrupt_unmask_allowed = 0;
    result->interrupt_dispatch_allowed = 0;
    result->interrupt_ack_allowed = 0;
    result->timer_tick_allowed = 0;
    result->timer_arm_allowed = 0;
    result->timer_disarm_allowed = 0;
    result->scheduler_tick_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->enqueue_allowed = 0;
    result->dequeue_allowed = 0;
    result->dispatch_allowed = 0;
    result->context_switch_allowed = 0;
    result->register_save_allowed = 0;
    result->register_restore_allowed = 0;
    result->stack_switch_allowed = 0;
    result->address_space_switch_allowed = 0;
    result->preemption_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->cpu_usage_write_allowed = 0;
    result->quota_update_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->process_wake_allowed = 0;
    result->persistence_allowed = 0;
    result->recovery_authority_allowed = 0;
    result->dma_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->no_external_effect_chain =
        result->external_effect_performed == 0 &&
        result->network_allowed == 0 &&
        result->registry_no_effect == 1 &&
        result->nucleus_no_effect_chain_ok == 1 &&
        result->nucleus_boot_allowed == 0 &&
        result->nucleus_runtime_entry_allowed == 0 &&
        result->nucleus_scheduler_run_entry_allowed == 0 &&
        result->nucleus_context_switch_allowed == 0 &&
        result->nucleus_register_save_allowed == 0 &&
        result->nucleus_register_restore_allowed == 0 &&
        result->nucleus_host_effect_allowed == 0 &&
        result->runtime_entry_recovery_audit_observation_view_allowed == 0 &&
        result->runtime_entry_recovery_closeout_observation_view_allowed == 0 &&
        result->runtime_entry_recovery_outcome_observation_view_allowed == 0 &&
        result->recovery_outcome_allowed == 0 &&
        result->recovery_outcome_observation_allowed == 0 &&
        result->recovery_audit_allowed == 0 &&
        result->recovery_audit_observation_allowed == 0 &&
        result->recovery_closeout_allowed == 0 &&
        result->recovery_closeout_observation_allowed == 0;

    fill_summary_entries(result);

    summary_copy(result->summary_status, sizeof(result->summary_status),
        (result->lifecycle_complete == 1 &&
         result->lifecycle.final_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY &&
         result->registry_no_effect == 1 &&
         result->nucleus_coupling_ready == 1 &&
         strcmp(result->os_readiness_status, "os-metadata-ready") == 0 &&
         result->external_effect_performed == 0 &&
         result->network_allowed == 0) ?
            "summary-ready" : "summary-incomplete");
}

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_evaluate(
    const latticra_kernel_lifecycle_subsystem_summary_request_t *request,
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_summary_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        summary_copy(result->summary_status, sizeof(result->summary_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_lifecycle_run(&request->lifecycle_request, &result->lifecycle);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        summary_copy(result->summary_status, sizeof(result->summary_status), "lifecycle-failed");
        return status;
    }

    status = latticra_kernel_subsystem_registry_evaluate(&request->registry_request, &result->registry);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        summary_copy(result->summary_status, sizeof(result->summary_status), "registry-failed");
        return status;
    }

    status = evaluate_nucleus_coupling(result);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        summary_copy(result->summary_status, sizeof(result->summary_status),
            "nucleus-coupling-failed");
        return status;
    }

    finalize_summary(result);
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

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_report(
    const latticra_kernel_lifecycle_subsystem_summary_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL LIFECYCLE SUBSYSTEM SUMMARY REPORT\n"
        "summary_status=%s\n"
        "final_state=%s\n"
        "lifecycle_status=%s\n"
        "registry_status=%s\n"
        "lifecycle_complete=%d\n"
        "lifecycle_step_count=%lu\n"
        "lifecycle_state_change_count=%lu\n"
        "lifecycle_state_mutated=%d\n"
        "external_effect_performed=%d\n"
        "network_allowed=%d\n"
        "lifecycle_network_allowed=%d\n"
        "machine_network_allowed=%d\n"
        "registry_no_effect=%d\n"
        "nucleus_coupling_status=%s\n"
        "os_readiness_status=%s\n"
        "nucleus_coupling_ready=%d\n"
        "nucleus_no_effect_chain_ok=%d\n"
        "nucleus_boot_allowed=%d\n"
        "nucleus_runtime_entry_allowed=%d\n"
        "nucleus_scheduler_run_entry_allowed=%d\n"
        "nucleus_context_switch_allowed=%d\n"
        "nucleus_register_save_allowed=%d\n"
        "nucleus_register_restore_allowed=%d\n"
        "nucleus_host_effect_allowed=%d\n"
        "runtime_entry_recovery_audit_observation_view_allowed=%d\n"
        "runtime_entry_recovery_closeout_observation_view_allowed=%d\n"
        "runtime_entry_recovery_outcome_observation_view_allowed=%d\n"
        "runtime_entry_recovery_disposition_observation_view_allowed=%d\n"
        "runtime_entry_recovery_plan_observation_view_allowed=%d\n"
        "runtime_entry_recovery_boundary_observation_view_allowed=%d\n"
        "runtime_entry_persistence_boundary_observation_view_allowed=%d\n"
        "runtime_entry_quiescent_return_observation_view_allowed=%d\n"
        "runtime_entry_idle_return_observation_view_allowed=%d\n"
        "runtime_entry_process_return_observation_view_allowed=%d\n"
        "runtime_entry_scheduler_return_observation_view_allowed=%d\n"
        "runtime_entry_post_resume_observation_view_allowed=%d\n"
        "runtime_entry_user_mode_resume_view_allowed=%d\n"
        "runtime_entry_syscall_exit_view_allowed=%d\n"
        "runtime_entry_syscall_return_view_allowed=%d\n"
        "runtime_entry_syscall_dispatch_view_allowed=%d\n"
        "runtime_entry_syscall_gate_view_allowed=%d\n"
        "runtime_entry_privilege_level_view_allowed=%d\n"
        "runtime_entry_address_space_view_allowed=%d\n"
        "runtime_entry_stack_view_allowed=%d\n"
        "runtime_entry_register_view_allowed=%d\n"
        "runtime_entry_frame_allowed=%d\n"
        "runtime_entry_admission_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "recovery_boundary_observation_allowed=%d\n"
        "recovery_boundary_allowed=%d\n"
        "recovery_plan_allowed=%d\n"
        "recovery_plan_observation_allowed=%d\n"
        "recovery_disposition_allowed=%d\n"
        "recovery_disposition_observation_allowed=%d\n"
        "recovery_outcome_allowed=%d\n"
        "recovery_outcome_observation_allowed=%d\n"
        "recovery_audit_allowed=%d\n"
        "recovery_audit_observation_allowed=%d\n"
        "recovery_closeout_allowed=%d\n"
        "recovery_closeout_observation_allowed=%d\n"
        "persistence_boundary_observation_allowed=%d\n"
        "persistence_boundary_allowed=%d\n"
        "persistence_commit_allowed=%d\n"
        "quiescent_return_observation_allowed=%d\n"
        "quiescent_return_allowed=%d\n"
        "quiescent_state_read_allowed=%d\n"
        "scheduler_execution_allowed=%d\n"
        "scheduler_selection_allowed=%d\n"
        "scheduler_dispatch_allowed=%d\n"
        "scheduler_handoff_allowed=%d\n"
        "scheduler_activation_allowed=%d\n"
        "scheduler_run_entry_allowed=%d\n"
        "memory_allocation_allowed=%d\n"
        "process_spawn_allowed=%d\n"
        "syscall_dispatch_allowed=%d\n"
        "ipc_send_allowed=%d\n"
        "ipc_receive_allowed=%d\n"
        "ipc_queue_mutation_allowed=%d\n"
        "filesystem_lookup_allowed=%d\n"
        "filesystem_read_allowed=%d\n"
        "filesystem_write_allowed=%d\n"
        "namespace_mutation_allowed=%d\n"
        "device_open_allowed=%d\n"
        "device_read_allowed=%d\n"
        "device_write_allowed=%d\n"
        "driver_probe_allowed=%d\n"
        "driver_load_allowed=%d\n"
        "driver_bind_allowed=%d\n"
        "interrupt_allowed=%d\n"
        "interrupt_mask_allowed=%d\n"
        "interrupt_unmask_allowed=%d\n"
        "interrupt_dispatch_allowed=%d\n"
        "interrupt_ack_allowed=%d\n"
        "timer_tick_allowed=%d\n"
        "timer_arm_allowed=%d\n"
        "timer_disarm_allowed=%d\n"
        "scheduler_tick_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "enqueue_allowed=%d\n"
        "dequeue_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "register_save_allowed=%d\n"
        "register_restore_allowed=%d\n"
        "stack_switch_allowed=%d\n"
        "address_space_switch_allowed=%d\n"
        "preemption_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "cpu_usage_write_allowed=%d\n"
        "quota_update_allowed=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "persistence_allowed=%d\n"
        "recovery_authority_allowed=%d\n"
        "dma_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "no_external_effect_chain=%d\n"
        "entry_count=%lu\n"
        "evidence_level=%u\n",
        result->summary_status,
        result->final_state,
        result->lifecycle.lifecycle_status,
        result->registry.registry_status,
        result->lifecycle_complete,
        (unsigned long)result->lifecycle_step_count,
        (unsigned long)result->lifecycle_state_change_count,
        result->lifecycle_state_mutated,
        result->external_effect_performed,
        result->network_allowed,
        result->lifecycle.network_allowed,
        result->lifecycle.machine.network_allowed,
        result->registry_no_effect,
        result->nucleus_coupling_status,
        result->os_readiness_status,
        result->nucleus_coupling_ready,
        result->nucleus_no_effect_chain_ok,
        result->nucleus_boot_allowed,
        result->nucleus_runtime_entry_allowed,
        result->nucleus_scheduler_run_entry_allowed,
        result->nucleus_context_switch_allowed,
        result->nucleus_register_save_allowed,
        result->nucleus_register_restore_allowed,
        result->nucleus_host_effect_allowed,
        result->runtime_entry_recovery_audit_observation_view_allowed,
        result->runtime_entry_recovery_closeout_observation_view_allowed,
        result->runtime_entry_recovery_outcome_observation_view_allowed,
        result->runtime_entry_recovery_disposition_observation_view_allowed,
        result->runtime_entry_recovery_plan_observation_view_allowed,
        result->runtime_entry_recovery_boundary_observation_view_allowed,
        result->runtime_entry_persistence_boundary_observation_view_allowed,
        result->runtime_entry_quiescent_return_observation_view_allowed,
        result->runtime_entry_idle_return_observation_view_allowed,
        result->runtime_entry_process_return_observation_view_allowed,
        result->runtime_entry_scheduler_return_observation_view_allowed,
        result->runtime_entry_post_resume_observation_view_allowed,
        result->runtime_entry_user_mode_resume_view_allowed,
        result->runtime_entry_syscall_exit_view_allowed,
        result->runtime_entry_syscall_return_view_allowed,
        result->runtime_entry_syscall_dispatch_view_allowed,
        result->runtime_entry_syscall_gate_view_allowed,
        result->runtime_entry_privilege_level_view_allowed,
        result->runtime_entry_address_space_view_allowed,
        result->runtime_entry_stack_view_allowed,
        result->runtime_entry_register_view_allowed,
        result->runtime_entry_frame_allowed,
        result->runtime_entry_admission_allowed,
        result->runtime_entry_allowed,
        result->recovery_boundary_observation_allowed,
        result->recovery_boundary_allowed,
        result->recovery_plan_allowed,
        result->recovery_plan_observation_allowed,
        result->recovery_disposition_allowed,
        result->recovery_disposition_observation_allowed,
        result->recovery_outcome_allowed,
        result->recovery_outcome_observation_allowed,
        result->recovery_audit_allowed,
        result->recovery_audit_observation_allowed,
        result->recovery_closeout_allowed,
        result->recovery_closeout_observation_allowed,
        result->persistence_boundary_observation_allowed,
        result->persistence_boundary_allowed,
        result->persistence_commit_allowed,
        result->quiescent_return_observation_allowed,
        result->quiescent_return_allowed,
        result->quiescent_state_read_allowed,
        result->scheduler_execution_allowed,
        result->scheduler_selection_allowed,
        result->scheduler_dispatch_allowed,
        result->scheduler_handoff_allowed,
        result->scheduler_activation_allowed,
        result->scheduler_run_entry_allowed,
        result->memory_allocation_allowed,
        result->process_spawn_allowed,
        result->syscall_dispatch_allowed,
        result->ipc_send_allowed,
        result->ipc_receive_allowed,
        result->ipc_queue_mutation_allowed,
        result->filesystem_lookup_allowed,
        result->filesystem_read_allowed,
        result->filesystem_write_allowed,
        result->namespace_mutation_allowed,
        result->device_open_allowed,
        result->device_read_allowed,
        result->device_write_allowed,
        result->driver_probe_allowed,
        result->driver_load_allowed,
        result->driver_bind_allowed,
        result->interrupt_allowed,
        result->interrupt_mask_allowed,
        result->interrupt_unmask_allowed,
        result->interrupt_dispatch_allowed,
        result->interrupt_ack_allowed,
        result->timer_tick_allowed,
        result->timer_arm_allowed,
        result->timer_disarm_allowed,
        result->scheduler_tick_allowed,
        result->run_queue_mutation_allowed,
        result->enqueue_allowed,
        result->dequeue_allowed,
        result->dispatch_allowed,
        result->context_switch_allowed,
        result->register_save_allowed,
        result->register_restore_allowed,
        result->stack_switch_allowed,
        result->address_space_switch_allowed,
        result->preemption_allowed,
        result->time_accounting_allowed,
        result->time_read_allowed,
        result->cpu_usage_write_allowed,
        result->quota_update_allowed,
        result->scheduler_credit_update_allowed,
        result->process_wake_allowed,
        result->persistence_allowed,
        result->recovery_authority_allowed,
        result->dma_allowed,
        result->hardware_effect_allowed,
        result->no_external_effect_chain,
        (unsigned long)result->entry_count,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->entry_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "subsystem[%lu].name=%s\n"
            "subsystem[%lu].registry_status=%s\n"
            "subsystem[%lu].lifecycle_relation=%s\n"
            "subsystem[%lu].authority_status=%s\n"
            "subsystem[%lu].effect_boundary=%s\n"
            "subsystem[%lu].lifecycle_ready=%d\n"
            "subsystem[%lu].authority_allowed=%d\n"
            "subsystem[%lu].network_allowed=%d\n"
            "subsystem[%lu].no_effect=%d\n"
            "subsystem[%lu].evidence_level=%u\n",
            (unsigned long)i,
            result->entries[i].name,
            (unsigned long)i,
            result->entries[i].registry_status,
            (unsigned long)i,
            result->entries[i].lifecycle_relation,
            (unsigned long)i,
            result->entries[i].authority_status,
            (unsigned long)i,
            result->entries[i].effect_boundary,
            (unsigned long)i,
            result->entries[i].lifecycle_ready,
            (unsigned long)i,
            result->entries[i].authority_allowed,
            (unsigned long)i,
            result->entries[i].network_allowed,
            (unsigned long)i,
            result->entries[i].no_effect,
            (unsigned long)i,
            result->entries[i].evidence_level);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
