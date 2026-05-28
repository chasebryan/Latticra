#include "latticra/nucleus_kernel_coupling.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void coupling_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static int coupling_copy_n(char *dst, size_t dst_len, const char *src, size_t src_len) {
    if (dst == 0 || dst_len == 0u) return 0;
    dst[0] = '\0';
    if (src == 0 || src_len == 0u) return 1;
    if (src_len >= dst_len) return 0;
    memcpy(dst, src, src_len);
    dst[src_len] = '\0';
    return 1;
}

static latticra_l_ui_source_span_t coupling_default_span(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 0u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 1u;
    return span;
}

const char *latticra_nucleus_kernel_coupling_classification_label(
    latticra_nucleus_kernel_coupling_classification_t classification) {
    switch (classification) {
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_ONLY_READY:
        return "report-only-ready";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_BLOCKED:
        return "blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_INVALID:
    default:
        return "invalid";
    }
}

const char *latticra_nucleus_kernel_coupling_denial_label(
    latticra_nucleus_kernel_coupling_denial_t denial) {
    switch (denial) {
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_OK:
        return "ok";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NULL_ARGUMENT:
        return "null-argument";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_MISSING:
        return "nucleus-plan-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_BLOCKED:
        return "nucleus-plan-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_REGISTRY_MISSING:
        return "kernel-registry-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_REGISTRY_BLOCKED:
        return "kernel-registry-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_MISSING:
        return "kernel-lifecycle-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_BLOCKED:
        return "kernel-lifecycle-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_MISSING:
        return "runtime-register-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_BLOCKED:
        return "runtime-register-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NON_NO_EFFECT_CHAIN:
        return "non-no-effect-chain";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_MISSING:
        return "runtime-process-return-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_BLOCKED:
        return "runtime-process-return-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_MISSING:
        return "runtime-idle-return-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_BLOCKED:
        return "runtime-idle-return-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_MISSING:
        return "runtime-quiescent-return-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_BLOCKED:
        return "runtime-quiescent-return-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_MISSING:
        return "runtime-persistence-boundary-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_BLOCKED:
        return "runtime-persistence-boundary-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_MISSING:
        return "runtime-recovery-boundary-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_BLOCKED:
        return "runtime-recovery-boundary-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_MISSING:
        return "runtime-recovery-plan-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_BLOCKED:
        return "runtime-recovery-plan-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_MISSING:
        return "runtime-recovery-disposition-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_BLOCKED:
        return "runtime-recovery-disposition-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_MISSING:
        return "runtime-recovery-outcome-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_BLOCKED:
        return "runtime-recovery-outcome-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_MISSING:
        return "runtime-recovery-closeout-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_BLOCKED:
        return "runtime-recovery-closeout-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_MISSING:
        return "runtime-recovery-audit-observation-view-missing";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_BLOCKED:
        return "runtime-recovery-audit-observation-view-blocked";
    case LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_INTERNAL_ERROR:
    default:
        return "internal-error";
    }
}

static void seed_record(latticra_nucleus_kernel_coupling_record_t *record) {
    memset(record, 0, sizeof(*record));
    record->classification = LATTICRA_NUCLEUS_KERNEL_COUPLING_BLOCKED;
    record->denial = LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_MISSING;
    coupling_copy(record->readiness_status, sizeof(record->readiness_status), "pending");
    coupling_copy(record->os_readiness_status, sizeof(record->os_readiness_status),
        "os-metadata-pending");
    coupling_copy(record->nucleus_plan_status, sizeof(record->nucleus_plan_status),
        "missing");
    coupling_copy(record->kernel_registry_status, sizeof(record->kernel_registry_status),
        "missing");
    coupling_copy(record->kernel_status, sizeof(record->kernel_status), "missing");
    coupling_copy(record->kernel_lifecycle_status,
        sizeof(record->kernel_lifecycle_status), "missing");
    coupling_copy(record->kernel_lifecycle_final_state,
        sizeof(record->kernel_lifecycle_final_state), "missing");
    coupling_copy(record->runtime_register_view_status,
        sizeof(record->runtime_register_view_status), "missing");
    coupling_copy(record->runtime_entry_frame_status,
        sizeof(record->runtime_entry_frame_status), "missing");
    coupling_copy(record->scheduler_run_entry_status,
        sizeof(record->scheduler_run_entry_status), "missing");
    coupling_copy(record->runtime_process_return_observation_view_status,
        sizeof(record->runtime_process_return_observation_view_status),
        "missing");
    coupling_copy(record->runtime_scheduler_return_observation_view_status,
        sizeof(record->runtime_scheduler_return_observation_view_status),
        "missing");
    coupling_copy(record->runtime_post_resume_observation_view_status,
        sizeof(record->runtime_post_resume_observation_view_status),
        "missing");
    coupling_copy(record->runtime_user_mode_resume_view_status,
        sizeof(record->runtime_user_mode_resume_view_status),
        "missing");
    coupling_copy(record->runtime_idle_return_observation_view_status,
        sizeof(record->runtime_idle_return_observation_view_status),
        "missing");
    coupling_copy(record->runtime_quiescent_return_observation_view_status,
        sizeof(record->runtime_quiescent_return_observation_view_status),
        "missing");
    coupling_copy(record->runtime_persistence_boundary_observation_view_status,
        sizeof(record->runtime_persistence_boundary_observation_view_status),
        "missing");
    coupling_copy(record->runtime_recovery_boundary_observation_view_status,
        sizeof(record->runtime_recovery_boundary_observation_view_status),
        "missing");
    coupling_copy(record->runtime_recovery_plan_observation_view_status,
        sizeof(record->runtime_recovery_plan_observation_view_status),
        "missing");
    coupling_copy(record->runtime_recovery_disposition_observation_view_status,
        sizeof(record->runtime_recovery_disposition_observation_view_status),
        "missing");
    coupling_copy(record->runtime_recovery_outcome_observation_view_status,
        sizeof(record->runtime_recovery_outcome_observation_view_status),
        "missing");
    coupling_copy(record->runtime_recovery_closeout_observation_view_status,
        sizeof(record->runtime_recovery_closeout_observation_view_status),
        "missing");
    coupling_copy(record->runtime_recovery_audit_observation_view_status,
        sizeof(record->runtime_recovery_audit_observation_view_status),
        "missing");
    record->no_effect_chain_ok = 0;
    record->report_only = 1;
    record->no_effect = 1;
    record->source_span = coupling_default_span();
}

static void seed_result(latticra_nucleus_kernel_coupling_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    seed_record(&result->record);
    result->record_count = 0u;
    result->no_effect = 1;
}

latticra_status_t latticra_nucleus_kernel_coupling_default_request(
    latticra_nucleus_kernel_coupling_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    coupling_copy(request->coupling_id, sizeof(request->coupling_id),
        "latticra-nucleus-kernel-coupling");
    request->source_identity = "nucleus-kernel-coupling-default";
    request->source_identity_len = strlen("nucleus-kernel-coupling-default");
    request->source_span = coupling_default_span();
    return LATTICRA_STATUS_OK;
}

static int task_plan_ready(const latticra_nucleus_task_plan_result_t *plan) {
    return plan != 0 &&
           plan->status == LATTICRA_STATUS_OK &&
           plan->record_count > 0u &&
           plan->record.policy ==
               LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE &&
           plan->record.denial == LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_OK &&
           plan->record.task_count > 0u &&
           plan->record.task_count <= LATTICRA_NUCLEUS_TASK_PLAN_TASK_MAX &&
           plan->record.accepted_count == plan->record.task_count &&
           plan->record.blocked_count == 0u &&
           plan->record.has_blocked_task == 0 &&
           plan->no_effect == 1 &&
           plan->execution_allowed == 0 &&
           plan->mutation_allowed == 0 &&
           plan->server_allowed == 0 &&
           plan->network_allowed == 0 &&
           plan->recovery_allowed == 0 &&
           plan->hardware_allowed == 0 &&
           plan->record.no_effect == 1 &&
           plan->record.execution_allowed == 0 &&
           plan->record.mutation_allowed == 0 &&
           plan->record.server_allowed == 0 &&
           plan->record.network_allowed == 0 &&
           plan->record.recovery_allowed == 0 &&
           plan->record.hardware_allowed == 0;
}

static int kernel_registry_ready(const latticra_kernel_subsystem_registry_result_t *registry) {
    size_t i;
    if (registry == 0 ||
        registry->status != LATTICRA_STATUS_OK ||
        registry->no_effect != 1 ||
        registry->network_allowed != 0 ||
        registry->entry_count < LATTICRA_KERNEL_SUBSYSTEM_COUNT ||
        registry->entry_count > LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_ENTRY_MAX ||
        registry->kernel.status != LATTICRA_STATUS_OK ||
        registry->kernel.no_effect != 1 ||
        registry->kernel.execution_allowed != 0 ||
        registry->kernel.mutation_allowed != 0 ||
        registry->kernel.file_io_allowed != 0 ||
        registry->kernel.network_allowed != 0 ||
        registry->kernel.server_allowed != 0 ||
        registry->kernel.recovery_allowed != 0 ||
        registry->kernel.hardware_allowed != 0 ||
        registry->kernel.boot_allowed != 0) {
        return 0;
    }

    for (i = 0u; i < registry->entry_count; ++i) {
        if (registry->entries[i].no_effect != 1 ||
            registry->entries[i].network_allowed != 0 ||
            registry->entries[i].active != 0) {
            return 0;
        }
    }
    return 1;
}

static int kernel_lifecycle_ready(
    const latticra_kernel_lifecycle_result_t *lifecycle) {
    return lifecycle != 0 &&
           lifecycle->status == LATTICRA_STATUS_OK &&
           lifecycle->lifecycle_complete == 1 &&
           lifecycle->final_state ==
               LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY &&
           lifecycle->step_count == (size_t)lifecycle->final_state &&
           lifecycle->state_change_count == lifecycle->step_count &&
           lifecycle->external_effect_performed == 0 &&
           lifecycle->network_allowed == 0 &&
           lifecycle->machine.network_allowed == 0 &&
           lifecycle->machine.external_effect_performed == 0 &&
           lifecycle->machine.current_state == lifecycle->final_state &&
           lifecycle->machine.log_count == lifecycle->step_count;
}

static int runtime_register_view_entry_ready(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->frame_declared == 1 &&
           entry->register_view_declared == 1 &&
           entry->instruction_pointer_declared == 1 &&
           entry->stack_pointer_declared == 1 &&
           entry->flags_declared == 1 &&
           entry->register_slot_count > 0ul &&
           entry->register_view_planned == 0 &&
           entry->register_view_built == 0 &&
           entry->register_view_installed == 0 &&
           entry->register_capture_planned == 0 &&
           entry->register_save_planned == 0 &&
           entry->register_restore_planned == 0 &&
           entry->admitted == 0 &&
           entry->runtime_entry_planned == 0 &&
           entry->runtime_entry_entered == 0 &&
           entry->execution_entered == 0 &&
           entry->context_switch_planned == 0 &&
           entry->runtime_entry_register_view_allowed == 0 &&
           entry->runtime_entry_frame_allowed == 0 &&
           entry->runtime_entry_admission_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->scheduler_run_entry_allowed == 0 &&
           entry->dispatch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->register_save_allowed == 0 &&
           entry->register_restore_allowed == 0 &&
           entry->stack_switch_allowed == 0 &&
           entry->address_space_switch_allowed == 0 &&
           entry->preemption_allowed == 0 &&
           entry->scheduler_credit_update_allowed == 0 &&
           entry->quota_update_allowed == 0 &&
           entry->time_accounting_allowed == 0 &&
           entry->time_read_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1;
}

static int runtime_register_view_ready(
    const latticra_kernel_runtime_entry_register_view_result_t *runtime_view) {
    size_t i;
    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->register_view_count == 0u ||
        runtime_view->register_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_REGISTER_VIEW_MAX ||
        runtime_view->runtime_entry_frame.no_effect != 1 ||
        runtime_view->runtime_entry_frame.runtime_entry_admission.no_effect != 1 ||
        runtime_view->runtime_entry_frame.runtime_entry_admission.
            scheduler_run_entry.no_effect != 1 ||
        runtime_view->runtime_entry_register_view_allowed != 0 ||
        runtime_view->runtime_entry_frame_allowed != 0 ||
        runtime_view->runtime_entry_admission_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->scheduler_run_entry_allowed != 0 ||
        runtime_view->dispatch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->register_save_allowed != 0 ||
        runtime_view->register_restore_allowed != 0 ||
        runtime_view->stack_switch_allowed != 0 ||
        runtime_view->address_space_switch_allowed != 0 ||
        runtime_view->preemption_allowed != 0 ||
        runtime_view->scheduler_credit_update_allowed != 0 ||
        runtime_view->quota_update_allowed != 0 ||
        runtime_view->time_accounting_allowed != 0 ||
        runtime_view->time_read_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0) {
        return 0;
    }

    for (i = 0u; i < runtime_view->register_view_count; ++i) {
        if (!runtime_register_view_entry_ready(&runtime_view->register_views[i])) {
            return 0;
        }
    }
    return 1;
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_process_return_observation(
    const latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_scheduler_return_observation_view.
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
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_idle_return(
    const latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_process_return_observation_view;
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_idle_return_observation(
    const latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        *runtime_view) {
    return register_view_from_process_return_observation(
        process_return_observation_from_idle_return(runtime_view));
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_quiescent_return(
    const
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_idle_return_observation_view;
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_quiescent_return(
    const
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_idle_return(
        idle_return_observation_from_quiescent_return(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_quiescent_return_observation(
    const
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *runtime_view) {
    return register_view_from_idle_return_observation(
        idle_return_observation_from_quiescent_return(runtime_view));
}

static const
latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t *
quiescent_return_observation_from_persistence_boundary(
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_quiescent_return_observation_view;
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_persistence_boundary(
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *runtime_view) {
    return idle_return_observation_from_quiescent_return(
        quiescent_return_observation_from_persistence_boundary(runtime_view));
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_persistence_boundary(
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_quiescent_return(
        quiescent_return_observation_from_persistence_boundary(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_persistence_boundary_observation(
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *runtime_view) {
    return register_view_from_quiescent_return_observation(
        quiescent_return_observation_from_persistence_boundary(runtime_view));
}

static const
latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t *
persistence_boundary_observation_from_recovery_boundary(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_persistence_boundary_observation_view;
}

static const
latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t *
quiescent_return_observation_from_recovery_boundary(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *runtime_view) {
    return quiescent_return_observation_from_persistence_boundary(
        persistence_boundary_observation_from_recovery_boundary(runtime_view));
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_recovery_boundary(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *runtime_view) {
    return idle_return_observation_from_persistence_boundary(
        persistence_boundary_observation_from_recovery_boundary(runtime_view));
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_recovery_boundary(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_persistence_boundary(
        persistence_boundary_observation_from_recovery_boundary(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_boundary_observation(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *runtime_view) {
    return register_view_from_persistence_boundary_observation(
        persistence_boundary_observation_from_recovery_boundary(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t *
recovery_boundary_observation_from_recovery_plan(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_recovery_boundary_observation_view;
}

static const
latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t *
persistence_boundary_observation_from_recovery_plan(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_view) {
    return persistence_boundary_observation_from_recovery_boundary(
        recovery_boundary_observation_from_recovery_plan(runtime_view));
}

static const
latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t *
quiescent_return_observation_from_recovery_plan(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_view) {
    return quiescent_return_observation_from_recovery_boundary(
        recovery_boundary_observation_from_recovery_plan(runtime_view));
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_recovery_plan(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_view) {
    return idle_return_observation_from_recovery_boundary(
        recovery_boundary_observation_from_recovery_plan(runtime_view));
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_recovery_plan(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_recovery_boundary(
        recovery_boundary_observation_from_recovery_plan(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_plan_observation(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_view) {
    return register_view_from_recovery_boundary_observation(
        recovery_boundary_observation_from_recovery_plan(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t *
recovery_plan_observation_from_recovery_disposition(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_recovery_plan_observation_view;
}

static const
latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t *
recovery_boundary_observation_from_recovery_disposition(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    return recovery_boundary_observation_from_recovery_plan(
        recovery_plan_observation_from_recovery_disposition(runtime_view));
}

static const
latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t *
persistence_boundary_observation_from_recovery_disposition(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    return persistence_boundary_observation_from_recovery_plan(
        recovery_plan_observation_from_recovery_disposition(runtime_view));
}

static const
latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t *
quiescent_return_observation_from_recovery_disposition(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    return quiescent_return_observation_from_recovery_plan(
        recovery_plan_observation_from_recovery_disposition(runtime_view));
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_recovery_disposition(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    return idle_return_observation_from_recovery_plan(
        recovery_plan_observation_from_recovery_disposition(runtime_view));
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_recovery_disposition(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_recovery_plan(
        recovery_plan_observation_from_recovery_disposition(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_disposition_observation(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    return register_view_from_recovery_plan_observation(
        recovery_plan_observation_from_recovery_disposition(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t *
recovery_disposition_observation_from_recovery_outcome(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_recovery_disposition_observation_view;
}

static const
latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t *
recovery_plan_observation_from_recovery_outcome(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    return recovery_plan_observation_from_recovery_disposition(
        recovery_disposition_observation_from_recovery_outcome(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t *
recovery_boundary_observation_from_recovery_outcome(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    return recovery_boundary_observation_from_recovery_disposition(
        recovery_disposition_observation_from_recovery_outcome(runtime_view));
}

static const
latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t *
persistence_boundary_observation_from_recovery_outcome(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    return persistence_boundary_observation_from_recovery_disposition(
        recovery_disposition_observation_from_recovery_outcome(runtime_view));
}

static const
latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t *
quiescent_return_observation_from_recovery_outcome(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    return quiescent_return_observation_from_recovery_disposition(
        recovery_disposition_observation_from_recovery_outcome(runtime_view));
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_recovery_outcome(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    return idle_return_observation_from_recovery_disposition(
        recovery_disposition_observation_from_recovery_outcome(runtime_view));
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_recovery_outcome(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_recovery_disposition(
        recovery_disposition_observation_from_recovery_outcome(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_outcome_observation(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    return register_view_from_recovery_disposition_observation(
        recovery_disposition_observation_from_recovery_outcome(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t *
recovery_outcome_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_recovery_outcome_observation_view;
}

static const
latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t *
recovery_disposition_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return recovery_disposition_observation_from_recovery_outcome(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t *
recovery_plan_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return recovery_plan_observation_from_recovery_outcome(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t *
recovery_boundary_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return recovery_boundary_observation_from_recovery_outcome(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const
latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t *
persistence_boundary_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return persistence_boundary_observation_from_recovery_outcome(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const
latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t *
quiescent_return_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return quiescent_return_observation_from_recovery_outcome(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return idle_return_observation_from_recovery_outcome(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_recovery_closeout(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_recovery_outcome(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_closeout_observation(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    return register_view_from_recovery_outcome_observation(
        recovery_outcome_observation_from_recovery_closeout(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t *
recovery_closeout_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    if (runtime_view == 0) return 0;
    return &runtime_view->runtime_entry_recovery_closeout_observation_view;
}

static const
latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t *
recovery_outcome_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return recovery_outcome_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t *
recovery_disposition_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return recovery_disposition_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t *
recovery_plan_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return recovery_plan_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const
latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t *
recovery_boundary_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return recovery_boundary_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const
latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t *
persistence_boundary_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return persistence_boundary_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const
latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t *
quiescent_return_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return quiescent_return_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const
latticra_kernel_runtime_entry_idle_return_observation_view_result_t *
idle_return_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return idle_return_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const
latticra_kernel_runtime_entry_process_return_observation_view_result_t *
process_return_observation_from_recovery_audit(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return process_return_observation_from_recovery_closeout(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_audit_observation(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    return register_view_from_recovery_closeout_observation(
        recovery_closeout_observation_from_recovery_audit(runtime_view));
}

static int runtime_process_return_observation_entry_ready(
    const latticra_kernel_runtime_entry_process_return_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->scheduler_return_observation_view_declared == 1 &&
           entry->process_return_observation_view_declared == 1 &&
           entry->scheduler_return_observation_declared == 1 &&
           entry->process_return_observation_declared == 1 &&
           entry->process_return_declared == 1 &&
           entry->process_state_observation_declared == 1 &&
           entry->process_return_reason_declared == 1 &&
           entry->process_return_observation_view_planned == 0 &&
           entry->process_return_observation_planned == 0 &&
           entry->process_return_planned == 0 &&
           entry->process_state_read_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_scheduler_return_observation_view_allowed == 0 &&
           entry->runtime_entry_post_resume_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->scheduler_return_observation_allowed == 0 &&
           entry->process_return_observation_allowed == 0 &&
           entry->process_return_allowed == 0 &&
           entry->process_state_read_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1;
}

static int runtime_process_return_observation_ready(
    const latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *runtime_view) {
    size_t i;
    const latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
        *scheduler_view;
    const latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        *post_resume_view;
    const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
        *user_resume_view;
    const latticra_kernel_runtime_entry_register_view_result_t *register_view;

    if (runtime_view == 0) return 0;
    scheduler_view =
        &runtime_view->runtime_entry_scheduler_return_observation_view;
    post_resume_view =
        &scheduler_view->runtime_entry_post_resume_observation_view;
    user_resume_view =
        &post_resume_view->runtime_entry_user_mode_resume_view;
    register_view = register_view_from_process_return_observation(runtime_view);

    if (runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->process_return_observation_view_count == 0u ||
        runtime_view->process_return_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_MAX ||
        scheduler_view->status != LATTICRA_STATUS_OK ||
        scheduler_view->no_effect != 1 ||
        post_resume_view->status != LATTICRA_STATUS_OK ||
        post_resume_view->no_effect != 1 ||
        user_resume_view->status != LATTICRA_STATUS_OK ||
        user_resume_view->no_effect != 1 ||
        !runtime_register_view_ready(register_view) ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_scheduler_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_post_resume_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->scheduler_return_observation_allowed != 0 ||
        runtime_view->process_return_observation_allowed != 0 ||
        runtime_view->process_return_allowed != 0 ||
        runtime_view->process_state_read_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0) {
        return 0;
    }

    for (i = 0u; i < runtime_view->process_return_observation_view_count; ++i) {
        if (!runtime_process_return_observation_entry_ready(
                &runtime_view->process_return_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_idle_return_observation_entry_ready(
    const latticra_kernel_runtime_entry_idle_return_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->process_return_observation_view_declared == 1 &&
           entry->scheduler_return_observation_view_declared == 1 &&
           entry->idle_return_observation_view_declared == 1 &&
           entry->process_return_observation_declared == 1 &&
           entry->scheduler_return_observation_declared == 1 &&
           entry->process_return_declared == 1 &&
           entry->idle_return_observation_declared == 1 &&
           entry->idle_return_declared == 1 &&
           entry->idle_state_observation_declared == 1 &&
           entry->idle_return_reason_declared == 1 &&
           entry->idle_return_observation_view_planned == 0 &&
           entry->idle_return_observation_planned == 0 &&
           entry->idle_return_planned == 0 &&
           entry->process_return_observation_planned == 0 &&
           entry->process_return_planned == 0 &&
           entry->idle_state_read_planned == 0 &&
           entry->process_state_read_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_scheduler_return_observation_view_allowed == 0 &&
           entry->runtime_entry_post_resume_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->scheduler_return_observation_allowed == 0 &&
           entry->process_return_observation_allowed == 0 &&
           entry->process_return_allowed == 0 &&
           entry->idle_return_observation_allowed == 0 &&
           entry->idle_return_allowed == 0 &&
           entry->idle_state_read_allowed == 0 &&
           entry->process_state_read_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1;
}

static int runtime_idle_return_observation_ready(
    const latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->idle_return_observation_view_count == 0u ||
        runtime_view->idle_return_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_MAX ||
        !runtime_process_return_observation_ready(
            &runtime_view->runtime_entry_process_return_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_idle_return_observation(runtime_view)) ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_scheduler_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_post_resume_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->scheduler_return_observation_allowed != 0 ||
        runtime_view->process_return_observation_allowed != 0 ||
        runtime_view->process_return_allowed != 0 ||
        runtime_view->idle_return_observation_allowed != 0 ||
        runtime_view->idle_return_allowed != 0 ||
        runtime_view->idle_state_read_allowed != 0 ||
        runtime_view->process_state_read_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0) {
        return 0;
    }

    for (i = 0u; i < runtime_view->idle_return_observation_view_count; ++i) {
        if (!runtime_idle_return_observation_entry_ready(
                &runtime_view->idle_return_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_quiescent_return_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_quiescent_return_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->idle_return_observation_view_declared == 1 &&
           entry->quiescent_return_observation_view_declared == 1 &&
           entry->idle_return_observation_declared == 1 &&
           entry->idle_return_declared == 1 &&
           entry->quiescent_return_observation_declared == 1 &&
           entry->quiescent_return_declared == 1 &&
           entry->quiescent_state_observation_declared == 1 &&
           entry->quiescent_return_observation_view_planned == 0 &&
           entry->quiescent_return_observation_planned == 0 &&
           entry->quiescent_return_planned == 0 &&
           entry->idle_return_observation_planned == 0 &&
           entry->idle_return_planned == 0 &&
           entry->quiescent_state_read_planned == 0 &&
           entry->idle_state_read_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->persistence_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->quiescent_return_observation_allowed == 0 &&
           entry->quiescent_return_allowed == 0 &&
           entry->quiescent_state_read_allowed == 0 &&
           entry->idle_return_observation_allowed == 0 &&
           entry->idle_return_allowed == 0 &&
           entry->idle_state_read_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 42u;
}

static int runtime_quiescent_return_observation_ready(
    const
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->quiescent_return_observation_view_count == 0u ||
        runtime_view->quiescent_return_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_MAX ||
        !runtime_idle_return_observation_ready(
            &runtime_view->runtime_entry_idle_return_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_quiescent_return_observation(runtime_view)) ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->quiescent_return_observation_allowed != 0 ||
        runtime_view->quiescent_return_allowed != 0 ||
        runtime_view->quiescent_state_read_allowed != 0 ||
        runtime_view->idle_return_observation_allowed != 0 ||
        runtime_view->idle_return_allowed != 0 ||
        runtime_view->idle_state_read_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 42u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->quiescent_return_observation_view_count;
            ++i) {
        if (!runtime_quiescent_return_observation_entry_ready(
                &runtime_view->quiescent_return_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_persistence_boundary_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->quiescent_return_observation_view_declared == 1 &&
           entry->persistence_boundary_observation_view_declared == 1 &&
           entry->quiescent_return_observation_declared == 1 &&
           entry->quiescent_return_declared == 1 &&
           entry->persistence_boundary_observation_declared == 1 &&
           entry->persistence_boundary_declared == 1 &&
           entry->recovery_authority_observation_declared == 1 &&
           entry->persistence_boundary_observation_view_planned == 0 &&
           entry->persistence_boundary_observation_planned == 0 &&
           entry->persistence_boundary_planned == 0 &&
           entry->persistence_commit_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->quiescent_return_observation_planned == 0 &&
           entry->quiescent_return_planned == 0 &&
           entry->quiescent_state_read_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_persistence_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->persistence_boundary_observation_allowed == 0 &&
           entry->persistence_boundary_allowed == 0 &&
           entry->persistence_commit_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->quiescent_return_observation_allowed == 0 &&
           entry->quiescent_return_allowed == 0 &&
           entry->quiescent_state_read_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 43u;
}

static int runtime_persistence_boundary_observation_ready(
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->persistence_boundary_observation_view_count == 0u ||
        runtime_view->persistence_boundary_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_MAX ||
        !runtime_quiescent_return_observation_ready(
            &runtime_view->runtime_entry_quiescent_return_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_persistence_boundary_observation(runtime_view)) ||
        runtime_view->runtime_entry_persistence_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->persistence_boundary_observation_allowed != 0 ||
        runtime_view->persistence_boundary_allowed != 0 ||
        runtime_view->persistence_commit_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->quiescent_return_observation_allowed != 0 ||
        runtime_view->quiescent_return_allowed != 0 ||
        runtime_view->quiescent_state_read_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 43u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->persistence_boundary_observation_view_count;
            ++i) {
        if (!runtime_persistence_boundary_observation_entry_ready(
                &runtime_view->persistence_boundary_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_recovery_boundary_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->persistence_boundary_observation_view_declared == 1 &&
           entry->quiescent_return_observation_view_declared == 1 &&
           entry->recovery_boundary_observation_view_declared == 1 &&
           entry->persistence_boundary_observation_declared == 1 &&
           entry->persistence_boundary_declared == 1 &&
           entry->quiescent_return_observation_declared == 1 &&
           entry->quiescent_return_declared == 1 &&
           entry->recovery_boundary_observation_declared == 1 &&
           entry->recovery_boundary_declared == 1 &&
           entry->recovery_plan_declared == 1 &&
           entry->recovery_authority_observation_declared == 1 &&
           entry->recovery_boundary_observation_view_planned == 0 &&
           entry->recovery_boundary_observation_planned == 0 &&
           entry->recovery_boundary_planned == 0 &&
           entry->recovery_plan_planned == 0 &&
           entry->persistence_boundary_observation_planned == 0 &&
           entry->persistence_boundary_planned == 0 &&
           entry->persistence_commit_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->quiescent_return_observation_planned == 0 &&
           entry->quiescent_return_planned == 0 &&
           entry->quiescent_state_read_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_recovery_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_persistence_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->recovery_boundary_observation_allowed == 0 &&
           entry->recovery_boundary_allowed == 0 &&
           entry->recovery_plan_allowed == 0 &&
           entry->persistence_boundary_observation_allowed == 0 &&
           entry->persistence_boundary_allowed == 0 &&
           entry->persistence_commit_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->quiescent_return_observation_allowed == 0 &&
           entry->quiescent_return_allowed == 0 &&
           entry->quiescent_state_read_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 44u;
}

static int runtime_recovery_boundary_observation_ready(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->recovery_boundary_observation_view_count == 0u ||
        runtime_view->recovery_boundary_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_MAX ||
        !runtime_persistence_boundary_observation_ready(
            &runtime_view->runtime_entry_persistence_boundary_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_recovery_boundary_observation(runtime_view)) ||
        runtime_view->runtime_entry_recovery_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_persistence_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->recovery_boundary_observation_allowed != 0 ||
        runtime_view->recovery_boundary_allowed != 0 ||
        runtime_view->recovery_plan_allowed != 0 ||
        runtime_view->persistence_boundary_observation_allowed != 0 ||
        runtime_view->persistence_boundary_allowed != 0 ||
        runtime_view->persistence_commit_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->quiescent_return_observation_allowed != 0 ||
        runtime_view->quiescent_return_allowed != 0 ||
        runtime_view->quiescent_state_read_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 44u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->recovery_boundary_observation_view_count;
            ++i) {
        if (!runtime_recovery_boundary_observation_entry_ready(
                &runtime_view->recovery_boundary_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_recovery_plan_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->persistence_boundary_observation_view_declared == 1 &&
           entry->quiescent_return_observation_view_declared == 1 &&
           entry->recovery_boundary_observation_view_declared == 1 &&
           entry->recovery_plan_observation_view_declared == 1 &&
           entry->persistence_boundary_observation_declared == 1 &&
           entry->persistence_boundary_declared == 1 &&
           entry->quiescent_return_observation_declared == 1 &&
           entry->quiescent_return_declared == 1 &&
           entry->recovery_boundary_observation_declared == 1 &&
           entry->recovery_boundary_declared == 1 &&
           entry->recovery_plan_observation_declared == 1 &&
           entry->recovery_plan_declared == 1 &&
           entry->recovery_authority_observation_declared == 1 &&
           entry->recovery_plan_observation_view_planned == 0 &&
           entry->recovery_plan_observation_planned == 0 &&
           entry->recovery_boundary_observation_planned == 0 &&
           entry->recovery_boundary_planned == 0 &&
           entry->recovery_plan_planned == 0 &&
           entry->persistence_boundary_observation_planned == 0 &&
           entry->persistence_boundary_planned == 0 &&
           entry->persistence_commit_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->quiescent_return_observation_planned == 0 &&
           entry->quiescent_return_planned == 0 &&
           entry->quiescent_state_read_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_recovery_plan_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_persistence_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->recovery_plan_observation_allowed == 0 &&
           entry->recovery_boundary_observation_allowed == 0 &&
           entry->recovery_boundary_allowed == 0 &&
           entry->recovery_plan_allowed == 0 &&
           entry->persistence_boundary_observation_allowed == 0 &&
           entry->persistence_boundary_allowed == 0 &&
           entry->persistence_commit_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->quiescent_return_observation_allowed == 0 &&
           entry->quiescent_return_allowed == 0 &&
           entry->quiescent_state_read_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 45u;
}

static int runtime_recovery_plan_observation_ready(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->recovery_plan_observation_view_count == 0u ||
        runtime_view->recovery_plan_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_MAX ||
        !runtime_recovery_boundary_observation_ready(
            &runtime_view->runtime_entry_recovery_boundary_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_recovery_plan_observation(runtime_view)) ||
        runtime_view->runtime_entry_recovery_plan_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_persistence_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->recovery_plan_observation_allowed != 0 ||
        runtime_view->recovery_boundary_observation_allowed != 0 ||
        runtime_view->recovery_boundary_allowed != 0 ||
        runtime_view->recovery_plan_allowed != 0 ||
        runtime_view->persistence_boundary_observation_allowed != 0 ||
        runtime_view->persistence_boundary_allowed != 0 ||
        runtime_view->persistence_commit_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->quiescent_return_observation_allowed != 0 ||
        runtime_view->quiescent_return_allowed != 0 ||
        runtime_view->quiescent_state_read_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 45u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->recovery_plan_observation_view_count;
            ++i) {
        if (!runtime_recovery_plan_observation_entry_ready(
                &runtime_view->recovery_plan_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_recovery_disposition_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->recovery_plan_observation_view_declared == 1 &&
           entry->recovery_boundary_observation_view_declared == 1 &&
           entry->recovery_disposition_observation_view_declared == 1 &&
           entry->recovery_plan_observation_declared == 1 &&
           entry->recovery_plan_declared == 1 &&
           entry->recovery_disposition_observation_declared == 1 &&
           entry->recovery_disposition_declared == 1 &&
           entry->recovery_authority_observation_declared == 1 &&
           entry->recovery_disposition_observation_view_planned == 0 &&
           entry->recovery_disposition_observation_planned == 0 &&
           entry->recovery_disposition_planned == 0 &&
           entry->recovery_plan_observation_planned == 0 &&
           entry->recovery_plan_planned == 0 &&
           entry->recovery_boundary_observation_planned == 0 &&
           entry->recovery_boundary_planned == 0 &&
           entry->persistence_boundary_observation_planned == 0 &&
           entry->persistence_boundary_planned == 0 &&
           entry->persistence_commit_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_recovery_disposition_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_plan_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_persistence_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->recovery_disposition_observation_allowed == 0 &&
           entry->recovery_disposition_allowed == 0 &&
           entry->recovery_plan_observation_allowed == 0 &&
           entry->recovery_plan_allowed == 0 &&
           entry->recovery_boundary_observation_allowed == 0 &&
           entry->recovery_boundary_allowed == 0 &&
           entry->persistence_boundary_observation_allowed == 0 &&
           entry->persistence_boundary_allowed == 0 &&
           entry->persistence_commit_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 46u;
}

static int runtime_recovery_disposition_observation_ready(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->recovery_disposition_observation_view_count == 0u ||
        runtime_view->recovery_disposition_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_MAX ||
        !runtime_recovery_plan_observation_ready(
            &runtime_view->runtime_entry_recovery_plan_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_recovery_disposition_observation(runtime_view)) ||
        runtime_view->runtime_entry_recovery_disposition_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_plan_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_persistence_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->recovery_disposition_observation_allowed != 0 ||
        runtime_view->recovery_disposition_allowed != 0 ||
        runtime_view->recovery_plan_observation_allowed != 0 ||
        runtime_view->recovery_plan_allowed != 0 ||
        runtime_view->recovery_boundary_observation_allowed != 0 ||
        runtime_view->recovery_boundary_allowed != 0 ||
        runtime_view->persistence_boundary_observation_allowed != 0 ||
        runtime_view->persistence_boundary_allowed != 0 ||
        runtime_view->persistence_commit_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 46u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->recovery_disposition_observation_view_count;
            ++i) {
        if (!runtime_recovery_disposition_observation_entry_ready(
                &runtime_view->recovery_disposition_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_recovery_outcome_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->recovery_disposition_observation_view_declared == 1 &&
           entry->recovery_plan_observation_view_declared == 1 &&
           entry->recovery_boundary_observation_view_declared == 1 &&
           entry->recovery_outcome_observation_view_declared == 1 &&
           entry->recovery_disposition_observation_declared == 1 &&
           entry->recovery_disposition_declared == 1 &&
           entry->recovery_outcome_observation_declared == 1 &&
           entry->recovery_outcome_declared == 1 &&
           entry->recovery_plan_observation_declared == 1 &&
           entry->recovery_plan_declared == 1 &&
           entry->recovery_authority_observation_declared == 1 &&
           entry->recovery_outcome_observation_view_planned == 0 &&
           entry->recovery_outcome_observation_planned == 0 &&
           entry->recovery_outcome_planned == 0 &&
           entry->recovery_disposition_observation_planned == 0 &&
           entry->recovery_disposition_planned == 0 &&
           entry->recovery_plan_observation_planned == 0 &&
           entry->recovery_plan_planned == 0 &&
           entry->recovery_boundary_observation_planned == 0 &&
           entry->recovery_boundary_planned == 0 &&
           entry->persistence_boundary_observation_planned == 0 &&
           entry->persistence_boundary_planned == 0 &&
           entry->persistence_commit_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_recovery_outcome_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_disposition_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_plan_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_persistence_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->recovery_outcome_observation_allowed == 0 &&
           entry->recovery_outcome_allowed == 0 &&
           entry->recovery_disposition_observation_allowed == 0 &&
           entry->recovery_disposition_allowed == 0 &&
           entry->recovery_plan_observation_allowed == 0 &&
           entry->recovery_plan_allowed == 0 &&
           entry->recovery_boundary_observation_allowed == 0 &&
           entry->recovery_boundary_allowed == 0 &&
           entry->persistence_boundary_observation_allowed == 0 &&
           entry->persistence_boundary_allowed == 0 &&
           entry->persistence_commit_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 47u;
}

static int runtime_recovery_outcome_observation_ready(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->recovery_outcome_observation_view_count == 0u ||
        runtime_view->recovery_outcome_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_MAX ||
        !runtime_recovery_disposition_observation_ready(
            &runtime_view->runtime_entry_recovery_disposition_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_recovery_outcome_observation(runtime_view)) ||
        runtime_view->runtime_entry_recovery_outcome_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_disposition_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_plan_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_persistence_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->recovery_outcome_observation_allowed != 0 ||
        runtime_view->recovery_outcome_allowed != 0 ||
        runtime_view->recovery_disposition_observation_allowed != 0 ||
        runtime_view->recovery_disposition_allowed != 0 ||
        runtime_view->recovery_plan_observation_allowed != 0 ||
        runtime_view->recovery_plan_allowed != 0 ||
        runtime_view->recovery_boundary_observation_allowed != 0 ||
        runtime_view->recovery_boundary_allowed != 0 ||
        runtime_view->persistence_boundary_observation_allowed != 0 ||
        runtime_view->persistence_boundary_allowed != 0 ||
        runtime_view->persistence_commit_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 47u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->recovery_outcome_observation_view_count;
            ++i) {
        if (!runtime_recovery_outcome_observation_entry_ready(
                &runtime_view->recovery_outcome_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_recovery_closeout_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->recovery_outcome_observation_view_declared == 1 &&
           entry->recovery_closeout_observation_view_declared == 1 &&
           entry->recovery_outcome_observation_declared == 1 &&
           entry->recovery_outcome_declared == 1 &&
           entry->recovery_closeout_observation_declared == 1 &&
           entry->recovery_closeout_declared == 1 &&
           entry->recovery_authority_observation_declared == 1 &&
           entry->recovery_closeout_observation_view_planned == 0 &&
           entry->recovery_closeout_observation_planned == 0 &&
           entry->recovery_closeout_planned == 0 &&
           entry->recovery_outcome_observation_planned == 0 &&
           entry->recovery_outcome_planned == 0 &&
           entry->recovery_disposition_observation_planned == 0 &&
           entry->recovery_disposition_planned == 0 &&
           entry->recovery_plan_observation_planned == 0 &&
           entry->recovery_plan_planned == 0 &&
           entry->recovery_boundary_observation_planned == 0 &&
           entry->recovery_boundary_planned == 0 &&
           entry->persistence_boundary_observation_planned == 0 &&
           entry->persistence_boundary_planned == 0 &&
           entry->persistence_commit_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_recovery_closeout_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_outcome_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_disposition_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_plan_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_persistence_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->recovery_closeout_observation_allowed == 0 &&
           entry->recovery_closeout_allowed == 0 &&
           entry->recovery_outcome_observation_allowed == 0 &&
           entry->recovery_outcome_allowed == 0 &&
           entry->recovery_disposition_observation_allowed == 0 &&
           entry->recovery_disposition_allowed == 0 &&
           entry->recovery_plan_observation_allowed == 0 &&
           entry->recovery_plan_allowed == 0 &&
           entry->recovery_boundary_observation_allowed == 0 &&
           entry->recovery_boundary_allowed == 0 &&
           entry->persistence_boundary_observation_allowed == 0 &&
           entry->persistence_boundary_allowed == 0 &&
           entry->persistence_commit_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 48u;
}

static int runtime_recovery_closeout_observation_ready(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->recovery_closeout_observation_view_count == 0u ||
        runtime_view->recovery_closeout_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_MAX ||
        !runtime_recovery_outcome_observation_ready(
            &runtime_view->runtime_entry_recovery_outcome_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_recovery_closeout_observation(runtime_view)) ||
        runtime_view->runtime_entry_recovery_closeout_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_outcome_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_disposition_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_plan_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_persistence_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->recovery_closeout_observation_allowed != 0 ||
        runtime_view->recovery_closeout_allowed != 0 ||
        runtime_view->recovery_outcome_observation_allowed != 0 ||
        runtime_view->recovery_outcome_allowed != 0 ||
        runtime_view->recovery_disposition_observation_allowed != 0 ||
        runtime_view->recovery_disposition_allowed != 0 ||
        runtime_view->recovery_plan_observation_allowed != 0 ||
        runtime_view->recovery_plan_allowed != 0 ||
        runtime_view->recovery_boundary_observation_allowed != 0 ||
        runtime_view->recovery_boundary_allowed != 0 ||
        runtime_view->persistence_boundary_observation_allowed != 0 ||
        runtime_view->persistence_boundary_allowed != 0 ||
        runtime_view->persistence_commit_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 48u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->recovery_closeout_observation_view_count;
            ++i) {
        if (!runtime_recovery_closeout_observation_entry_ready(
                &runtime_view->recovery_closeout_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static int runtime_recovery_audit_observation_entry_ready(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_entry_t
        *entry) {
    return entry != 0 &&
           entry->declared == 1 &&
           entry->recovery_audit_observation_view_declared == 1 &&
           entry->recovery_closeout_observation_view_declared == 1 &&
           entry->recovery_outcome_observation_view_declared == 1 &&
           entry->recovery_audit_observation_declared == 1 &&
           entry->recovery_audit_declared == 1 &&
           entry->recovery_closeout_observation_declared == 1 &&
           entry->recovery_closeout_declared == 1 &&
           entry->recovery_outcome_observation_declared == 1 &&
           entry->recovery_outcome_declared == 1 &&
           entry->recovery_authority_observation_declared == 1 &&
           entry->recovery_audit_observation_view_planned == 0 &&
           entry->recovery_audit_observation_planned == 0 &&
           entry->recovery_audit_planned == 0 &&
           entry->recovery_closeout_observation_planned == 0 &&
           entry->recovery_closeout_planned == 0 &&
           entry->recovery_outcome_observation_planned == 0 &&
           entry->recovery_outcome_planned == 0 &&
           entry->recovery_disposition_observation_planned == 0 &&
           entry->recovery_disposition_planned == 0 &&
           entry->recovery_plan_observation_planned == 0 &&
           entry->recovery_plan_planned == 0 &&
           entry->recovery_boundary_observation_planned == 0 &&
           entry->recovery_boundary_planned == 0 &&
           entry->persistence_boundary_observation_planned == 0 &&
           entry->persistence_boundary_planned == 0 &&
           entry->persistence_commit_planned == 0 &&
           entry->recovery_authority_planned == 0 &&
           entry->scheduler_execution_planned == 0 &&
           entry->context_switch_planned == 0 &&
           entry->run_queue_mutation_planned == 0 &&
           entry->runtime_entry_recovery_audit_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_closeout_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_outcome_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_disposition_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_plan_observation_view_allowed == 0 &&
           entry->runtime_entry_recovery_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_persistence_boundary_observation_view_allowed == 0 &&
           entry->runtime_entry_quiescent_return_observation_view_allowed == 0 &&
           entry->runtime_entry_idle_return_observation_view_allowed == 0 &&
           entry->runtime_entry_process_return_observation_view_allowed == 0 &&
           entry->runtime_entry_allowed == 0 &&
           entry->recovery_audit_observation_allowed == 0 &&
           entry->recovery_audit_allowed == 0 &&
           entry->recovery_closeout_observation_allowed == 0 &&
           entry->recovery_closeout_allowed == 0 &&
           entry->recovery_outcome_observation_allowed == 0 &&
           entry->recovery_outcome_allowed == 0 &&
           entry->recovery_disposition_observation_allowed == 0 &&
           entry->recovery_disposition_allowed == 0 &&
           entry->recovery_plan_observation_allowed == 0 &&
           entry->recovery_plan_allowed == 0 &&
           entry->recovery_boundary_observation_allowed == 0 &&
           entry->recovery_boundary_allowed == 0 &&
           entry->persistence_boundary_observation_allowed == 0 &&
           entry->persistence_boundary_allowed == 0 &&
           entry->persistence_commit_allowed == 0 &&
           entry->persistence_allowed == 0 &&
           entry->recovery_authority_allowed == 0 &&
           entry->scheduler_execution_allowed == 0 &&
           entry->scheduler_dispatch_allowed == 0 &&
           entry->context_switch_allowed == 0 &&
           entry->run_queue_mutation_allowed == 0 &&
           entry->process_wake_allowed == 0 &&
           entry->hardware_effect_allowed == 0 &&
           entry->host_effect_allowed == 0 &&
           entry->no_effect == 1 &&
           entry->evidence_level == 49u;
}

static int runtime_recovery_audit_observation_ready(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *runtime_view) {
    size_t i;

    if (runtime_view == 0 ||
        runtime_view->status != LATTICRA_STATUS_OK ||
        runtime_view->no_effect != 1 ||
        runtime_view->recovery_audit_observation_view_count == 0u ||
        runtime_view->recovery_audit_observation_view_count >
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_MAX ||
        !runtime_recovery_closeout_observation_ready(
            &runtime_view->runtime_entry_recovery_closeout_observation_view) ||
        !runtime_register_view_ready(
            register_view_from_recovery_audit_observation(runtime_view)) ||
        runtime_view->runtime_entry_recovery_audit_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_closeout_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_outcome_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_disposition_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_plan_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_recovery_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_persistence_boundary_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_quiescent_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_idle_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_process_return_observation_view_allowed != 0 ||
        runtime_view->runtime_entry_allowed != 0 ||
        runtime_view->recovery_audit_observation_allowed != 0 ||
        runtime_view->recovery_audit_allowed != 0 ||
        runtime_view->recovery_closeout_observation_allowed != 0 ||
        runtime_view->recovery_closeout_allowed != 0 ||
        runtime_view->recovery_outcome_observation_allowed != 0 ||
        runtime_view->recovery_outcome_allowed != 0 ||
        runtime_view->recovery_disposition_observation_allowed != 0 ||
        runtime_view->recovery_disposition_allowed != 0 ||
        runtime_view->recovery_plan_observation_allowed != 0 ||
        runtime_view->recovery_plan_allowed != 0 ||
        runtime_view->recovery_boundary_observation_allowed != 0 ||
        runtime_view->recovery_boundary_allowed != 0 ||
        runtime_view->persistence_boundary_observation_allowed != 0 ||
        runtime_view->persistence_boundary_allowed != 0 ||
        runtime_view->persistence_commit_allowed != 0 ||
        runtime_view->persistence_allowed != 0 ||
        runtime_view->recovery_authority_allowed != 0 ||
        runtime_view->scheduler_execution_allowed != 0 ||
        runtime_view->scheduler_dispatch_allowed != 0 ||
        runtime_view->context_switch_allowed != 0 ||
        runtime_view->run_queue_mutation_allowed != 0 ||
        runtime_view->process_wake_allowed != 0 ||
        runtime_view->hardware_effect_allowed != 0 ||
        runtime_view->host_effect_allowed != 0 ||
        runtime_view->evidence_level != 49u) {
        return 0;
    }

    for (i = 0u; i < runtime_view->recovery_audit_observation_view_count;
            ++i) {
        if (!runtime_recovery_audit_observation_entry_ready(
                &runtime_view->recovery_audit_observation_views[i])) {
            return 0;
        }
    }
    return 1;
}

static void capture_evidence(
    const latticra_nucleus_kernel_coupling_request_t *request,
    latticra_nucleus_kernel_coupling_result_t *result) {
    if (request->nucleus_plan != 0) {
        const latticra_nucleus_task_plan_result_t *plan = request->nucleus_plan;
        coupling_copy(result->record.nucleus_plan_status,
            sizeof(result->record.nucleus_plan_status),
            latticra_nucleus_task_plan_policy_label(plan->record.policy));
        result->record.task_count = plan->record.task_count;
        result->record.accepted_task_count = plan->record.accepted_count;
        result->record.blocked_task_count = plan->record.blocked_count;
    }

    if (request->kernel_registry != 0) {
        const latticra_kernel_subsystem_registry_result_t *registry =
            request->kernel_registry;
        coupling_copy(result->record.kernel_registry_status,
            sizeof(result->record.kernel_registry_status),
            registry->registry_status);
        coupling_copy(result->record.kernel_status,
            sizeof(result->record.kernel_status),
            registry->kernel.kernel_status);
        result->record.subsystem_count = registry->entry_count;
    }

    if (request->kernel_lifecycle != 0) {
        const latticra_kernel_lifecycle_result_t *lifecycle =
            request->kernel_lifecycle;
        coupling_copy(result->record.kernel_lifecycle_status,
            sizeof(result->record.kernel_lifecycle_status),
            lifecycle->lifecycle_status);
        coupling_copy(result->record.kernel_lifecycle_final_state,
            sizeof(result->record.kernel_lifecycle_final_state),
            latticra_kernel_state_label(lifecycle->final_state));
        result->record.lifecycle_step_count = lifecycle->step_count;
        result->record.lifecycle_state_change_count =
            lifecycle->state_change_count;
        result->record.lifecycle_complete = lifecycle->lifecycle_complete;
    }

    if (request->runtime_register_view != 0) {
        const latticra_kernel_runtime_entry_register_view_result_t *runtime_view =
            request->runtime_register_view;
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            runtime_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            runtime_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            runtime_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.register_view_count = runtime_view->register_view_count;
    }

    if (request->runtime_process_return_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *runtime_view = request->runtime_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &runtime_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;

        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            runtime_view->process_return_observation_view_status);
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        coupling_copy(result->record.runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        result->record.process_return_observation_view_count =
            runtime_view->process_return_observation_view_count;
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
    }

    if (request->runtime_idle_return_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *runtime_view = request->runtime_idle_return_observation_view;
        coupling_copy(result->record.
                runtime_idle_return_observation_view_status,
            sizeof(result->record.
                runtime_idle_return_observation_view_status),
            runtime_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            runtime_view->idle_return_observation_view_count;
    }

    if (request->runtime_quiescent_return_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
            *runtime_view =
                request->runtime_quiescent_return_observation_view;
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *idle_view =
                &runtime_view->runtime_entry_idle_return_observation_view;
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *process_view =
                &idle_view->runtime_entry_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &process_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;
        const latticra_kernel_runtime_entry_register_view_result_t
            *register_view =
                register_view_from_quiescent_return_observation(runtime_view);

        coupling_copy(result->record.
                runtime_quiescent_return_observation_view_status,
            sizeof(result->record.
                runtime_quiescent_return_observation_view_status),
            runtime_view->quiescent_return_observation_view_status);
        result->record.quiescent_return_observation_view_count =
            runtime_view->quiescent_return_observation_view_count;

        coupling_copy(result->record.runtime_idle_return_observation_view_status,
            sizeof(result->record.runtime_idle_return_observation_view_status),
            idle_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            idle_view->idle_return_observation_view_count;

        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            process_view->process_return_observation_view_status);
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        coupling_copy(result->record.runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            register_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            register_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            register_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.process_return_observation_view_count =
            process_view->process_return_observation_view_count;
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
        result->record.register_view_count = register_view->register_view_count;
    }

    if (request->runtime_persistence_boundary_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
            *runtime_view =
                request->runtime_persistence_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
            *quiescent_view =
                &runtime_view->runtime_entry_quiescent_return_observation_view;
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *idle_view =
                &quiescent_view->runtime_entry_idle_return_observation_view;
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *process_view =
                &idle_view->runtime_entry_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &process_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;
        const latticra_kernel_runtime_entry_register_view_result_t
            *register_view =
                register_view_from_persistence_boundary_observation(runtime_view);

        coupling_copy(result->record.
                runtime_persistence_boundary_observation_view_status,
            sizeof(result->record.
                runtime_persistence_boundary_observation_view_status),
            runtime_view->persistence_boundary_observation_view_status);
        result->record.persistence_boundary_observation_view_count =
            runtime_view->persistence_boundary_observation_view_count;

        coupling_copy(result->record.
                runtime_quiescent_return_observation_view_status,
            sizeof(result->record.
                runtime_quiescent_return_observation_view_status),
            quiescent_view->quiescent_return_observation_view_status);
        result->record.quiescent_return_observation_view_count =
            quiescent_view->quiescent_return_observation_view_count;

        coupling_copy(result->record.runtime_idle_return_observation_view_status,
            sizeof(result->record.runtime_idle_return_observation_view_status),
            idle_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            idle_view->idle_return_observation_view_count;

        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            process_view->process_return_observation_view_status);
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        coupling_copy(result->record.runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            register_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            register_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            register_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.process_return_observation_view_count =
            process_view->process_return_observation_view_count;
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
        result->record.register_view_count = register_view->register_view_count;
    }

    if (request->runtime_recovery_boundary_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
            *runtime_view = request->runtime_recovery_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
            *persistence_view =
                &runtime_view->runtime_entry_persistence_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
            *quiescent_view =
                &persistence_view->runtime_entry_quiescent_return_observation_view;
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *idle_view =
                &quiescent_view->runtime_entry_idle_return_observation_view;
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *process_view =
                &idle_view->runtime_entry_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &process_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;
        const latticra_kernel_runtime_entry_register_view_result_t
            *register_view =
                register_view_from_recovery_boundary_observation(runtime_view);

        coupling_copy(result->record.
                runtime_recovery_boundary_observation_view_status,
            sizeof(result->record.
                runtime_recovery_boundary_observation_view_status),
            runtime_view->recovery_boundary_observation_view_status);
        result->record.recovery_boundary_observation_view_count =
            runtime_view->recovery_boundary_observation_view_count;

        coupling_copy(result->record.
                runtime_persistence_boundary_observation_view_status,
            sizeof(result->record.
                runtime_persistence_boundary_observation_view_status),
            persistence_view->persistence_boundary_observation_view_status);
        result->record.persistence_boundary_observation_view_count =
            persistence_view->persistence_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_quiescent_return_observation_view_status,
            sizeof(result->record.
                runtime_quiescent_return_observation_view_status),
            quiescent_view->quiescent_return_observation_view_status);
        result->record.quiescent_return_observation_view_count =
            quiescent_view->quiescent_return_observation_view_count;
        coupling_copy(result->record.runtime_idle_return_observation_view_status,
            sizeof(result->record.runtime_idle_return_observation_view_status),
            idle_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            idle_view->idle_return_observation_view_count;
        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            process_view->process_return_observation_view_status);
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        coupling_copy(result->record.runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            register_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            register_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            register_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.process_return_observation_view_count =
            process_view->process_return_observation_view_count;
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
        result->record.register_view_count = register_view->register_view_count;
    }

    if (request->runtime_recovery_plan_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
            *runtime_view = request->runtime_recovery_plan_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
            *recovery_view =
                &runtime_view->runtime_entry_recovery_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
            *persistence_view =
                &recovery_view->runtime_entry_persistence_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
            *quiescent_view =
                &persistence_view->runtime_entry_quiescent_return_observation_view;
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *idle_view =
                &quiescent_view->runtime_entry_idle_return_observation_view;
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *process_view =
                &idle_view->runtime_entry_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &process_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;
        const latticra_kernel_runtime_entry_register_view_result_t
            *register_view =
                register_view_from_recovery_plan_observation(runtime_view);

        coupling_copy(result->record.
                runtime_recovery_plan_observation_view_status,
            sizeof(result->record.
                runtime_recovery_plan_observation_view_status),
            runtime_view->recovery_plan_observation_view_status);
        result->record.recovery_plan_observation_view_count =
            runtime_view->recovery_plan_observation_view_count;

        coupling_copy(result->record.
                runtime_recovery_boundary_observation_view_status,
            sizeof(result->record.
                runtime_recovery_boundary_observation_view_status),
            recovery_view->recovery_boundary_observation_view_status);
        result->record.recovery_boundary_observation_view_count =
            recovery_view->recovery_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_persistence_boundary_observation_view_status,
            sizeof(result->record.
                runtime_persistence_boundary_observation_view_status),
            persistence_view->persistence_boundary_observation_view_status);
        result->record.persistence_boundary_observation_view_count =
            persistence_view->persistence_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_quiescent_return_observation_view_status,
            sizeof(result->record.
                runtime_quiescent_return_observation_view_status),
            quiescent_view->quiescent_return_observation_view_status);
        result->record.quiescent_return_observation_view_count =
            quiescent_view->quiescent_return_observation_view_count;
        coupling_copy(result->record.runtime_idle_return_observation_view_status,
            sizeof(result->record.runtime_idle_return_observation_view_status),
            idle_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            idle_view->idle_return_observation_view_count;
        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            process_view->process_return_observation_view_status);
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        coupling_copy(result->record.runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            register_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            register_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            register_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.process_return_observation_view_count =
            process_view->process_return_observation_view_count;
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
        result->record.register_view_count = register_view->register_view_count;
    }

    if (request->runtime_recovery_audit_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
            *runtime_view = request->runtime_recovery_audit_observation_view;

        coupling_copy(result->record.
                runtime_recovery_audit_observation_view_status,
            sizeof(result->record.
                runtime_recovery_audit_observation_view_status),
            runtime_view->recovery_audit_observation_view_status);
        result->record.recovery_audit_observation_view_count =
            runtime_view->recovery_audit_observation_view_count;
    }

    if (request->runtime_recovery_closeout_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
            *runtime_view = request->runtime_recovery_closeout_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
            *outcome_view =
                &runtime_view->runtime_entry_recovery_outcome_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
            *disposition_view =
                &outcome_view->runtime_entry_recovery_disposition_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
            *plan_view =
                &disposition_view->runtime_entry_recovery_plan_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
            *recovery_view =
                &plan_view->runtime_entry_recovery_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
            *persistence_view =
                &recovery_view->runtime_entry_persistence_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
            *quiescent_view =
                &persistence_view->runtime_entry_quiescent_return_observation_view;
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *idle_view =
                &quiescent_view->runtime_entry_idle_return_observation_view;
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *process_view =
                &idle_view->runtime_entry_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &process_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;
        const latticra_kernel_runtime_entry_register_view_result_t
            *register_view =
                register_view_from_recovery_closeout_observation(runtime_view);

        coupling_copy(result->record.
                runtime_recovery_closeout_observation_view_status,
            sizeof(result->record.
                runtime_recovery_closeout_observation_view_status),
            runtime_view->recovery_closeout_observation_view_status);
        result->record.recovery_closeout_observation_view_count =
            runtime_view->recovery_closeout_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_outcome_observation_view_status,
            sizeof(result->record.
                runtime_recovery_outcome_observation_view_status),
            outcome_view->recovery_outcome_observation_view_status);
        result->record.recovery_outcome_observation_view_count =
            outcome_view->recovery_outcome_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_disposition_observation_view_status,
            sizeof(result->record.
                runtime_recovery_disposition_observation_view_status),
            disposition_view->recovery_disposition_observation_view_status);
        result->record.recovery_disposition_observation_view_count =
            disposition_view->recovery_disposition_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_plan_observation_view_status,
            sizeof(result->record.
                runtime_recovery_plan_observation_view_status),
            plan_view->recovery_plan_observation_view_status);
        result->record.recovery_plan_observation_view_count =
            plan_view->recovery_plan_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_boundary_observation_view_status,
            sizeof(result->record.
                runtime_recovery_boundary_observation_view_status),
            recovery_view->recovery_boundary_observation_view_status);
        result->record.recovery_boundary_observation_view_count =
            recovery_view->recovery_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_persistence_boundary_observation_view_status,
            sizeof(result->record.
                runtime_persistence_boundary_observation_view_status),
            persistence_view->persistence_boundary_observation_view_status);
        result->record.persistence_boundary_observation_view_count =
            persistence_view->persistence_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_quiescent_return_observation_view_status,
            sizeof(result->record.
                runtime_quiescent_return_observation_view_status),
            quiescent_view->quiescent_return_observation_view_status);
        result->record.quiescent_return_observation_view_count =
            quiescent_view->quiescent_return_observation_view_count;
        coupling_copy(result->record.
                runtime_idle_return_observation_view_status,
            sizeof(result->record.runtime_idle_return_observation_view_status),
            idle_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            idle_view->idle_return_observation_view_count;
        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            process_view->process_return_observation_view_status);
        result->record.process_return_observation_view_count =
            process_view->process_return_observation_view_count;
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        coupling_copy(result->record.
                runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            register_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            register_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            register_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.register_view_count = register_view->register_view_count;
    }

    if (request->runtime_recovery_outcome_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
            *runtime_view = request->runtime_recovery_outcome_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
            *disposition_view =
                &runtime_view->runtime_entry_recovery_disposition_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
            *plan_view =
                &disposition_view->runtime_entry_recovery_plan_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
            *recovery_view =
                &plan_view->runtime_entry_recovery_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
            *persistence_view =
                &recovery_view->runtime_entry_persistence_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
            *quiescent_view =
                &persistence_view->runtime_entry_quiescent_return_observation_view;
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *idle_view =
                &quiescent_view->runtime_entry_idle_return_observation_view;
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *process_view =
                &idle_view->runtime_entry_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &process_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;
        const latticra_kernel_runtime_entry_register_view_result_t
            *register_view =
                register_view_from_recovery_outcome_observation(runtime_view);

        coupling_copy(result->record.
                runtime_recovery_outcome_observation_view_status,
            sizeof(result->record.
                runtime_recovery_outcome_observation_view_status),
            runtime_view->recovery_outcome_observation_view_status);
        result->record.recovery_outcome_observation_view_count =
            runtime_view->recovery_outcome_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_disposition_observation_view_status,
            sizeof(result->record.
                runtime_recovery_disposition_observation_view_status),
            disposition_view->recovery_disposition_observation_view_status);
        result->record.recovery_disposition_observation_view_count =
            disposition_view->recovery_disposition_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_plan_observation_view_status,
            sizeof(result->record.
                runtime_recovery_plan_observation_view_status),
            plan_view->recovery_plan_observation_view_status);
        result->record.recovery_plan_observation_view_count =
            plan_view->recovery_plan_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_boundary_observation_view_status,
            sizeof(result->record.
                runtime_recovery_boundary_observation_view_status),
            recovery_view->recovery_boundary_observation_view_status);
        result->record.recovery_boundary_observation_view_count =
            recovery_view->recovery_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_persistence_boundary_observation_view_status,
            sizeof(result->record.
                runtime_persistence_boundary_observation_view_status),
            persistence_view->persistence_boundary_observation_view_status);
        result->record.persistence_boundary_observation_view_count =
            persistence_view->persistence_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_quiescent_return_observation_view_status,
            sizeof(result->record.
                runtime_quiescent_return_observation_view_status),
            quiescent_view->quiescent_return_observation_view_status);
        result->record.quiescent_return_observation_view_count =
            quiescent_view->quiescent_return_observation_view_count;
        coupling_copy(result->record.
                runtime_idle_return_observation_view_status,
            sizeof(result->record.runtime_idle_return_observation_view_status),
            idle_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            idle_view->idle_return_observation_view_count;
        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            process_view->process_return_observation_view_status);
        result->record.process_return_observation_view_count =
            process_view->process_return_observation_view_count;
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        coupling_copy(result->record.
                runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            register_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            register_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            register_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.register_view_count = register_view->register_view_count;
    }

    if (request->runtime_recovery_disposition_observation_view != 0) {
        const
        latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
            *runtime_view =
                request->runtime_recovery_disposition_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
            *plan_view =
                &runtime_view->runtime_entry_recovery_plan_observation_view;
        const
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
            *recovery_view =
                &plan_view->runtime_entry_recovery_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
            *persistence_view =
                &recovery_view->runtime_entry_persistence_boundary_observation_view;
        const
        latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
            *quiescent_view =
                &persistence_view->runtime_entry_quiescent_return_observation_view;
        const
        latticra_kernel_runtime_entry_idle_return_observation_view_result_t
            *idle_view =
                &quiescent_view->runtime_entry_idle_return_observation_view;
        const
        latticra_kernel_runtime_entry_process_return_observation_view_result_t
            *process_view =
                &idle_view->runtime_entry_process_return_observation_view;
        const
        latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
            *scheduler_view =
                &process_view->runtime_entry_scheduler_return_observation_view;
        const
        latticra_kernel_runtime_entry_post_resume_observation_view_result_t
            *post_resume_view =
                &scheduler_view->runtime_entry_post_resume_observation_view;
        const latticra_kernel_runtime_entry_user_mode_resume_view_result_t
            *user_resume_view =
                &post_resume_view->runtime_entry_user_mode_resume_view;
        const latticra_kernel_runtime_entry_register_view_result_t
            *register_view =
                register_view_from_recovery_disposition_observation(runtime_view);

        coupling_copy(result->record.
                runtime_recovery_disposition_observation_view_status,
            sizeof(result->record.
                runtime_recovery_disposition_observation_view_status),
            runtime_view->recovery_disposition_observation_view_status);
        result->record.recovery_disposition_observation_view_count =
            runtime_view->recovery_disposition_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_plan_observation_view_status,
            sizeof(result->record.
                runtime_recovery_plan_observation_view_status),
            plan_view->recovery_plan_observation_view_status);
        result->record.recovery_plan_observation_view_count =
            plan_view->recovery_plan_observation_view_count;
        coupling_copy(result->record.
                runtime_recovery_boundary_observation_view_status,
            sizeof(result->record.
                runtime_recovery_boundary_observation_view_status),
            recovery_view->recovery_boundary_observation_view_status);
        result->record.recovery_boundary_observation_view_count =
            recovery_view->recovery_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_persistence_boundary_observation_view_status,
            sizeof(result->record.
                runtime_persistence_boundary_observation_view_status),
            persistence_view->persistence_boundary_observation_view_status);
        result->record.persistence_boundary_observation_view_count =
            persistence_view->persistence_boundary_observation_view_count;
        coupling_copy(result->record.
                runtime_quiescent_return_observation_view_status,
            sizeof(result->record.
                runtime_quiescent_return_observation_view_status),
            quiescent_view->quiescent_return_observation_view_status);
        result->record.quiescent_return_observation_view_count =
            quiescent_view->quiescent_return_observation_view_count;
        coupling_copy(result->record.runtime_idle_return_observation_view_status,
            sizeof(result->record.runtime_idle_return_observation_view_status),
            idle_view->idle_return_observation_view_status);
        result->record.idle_return_observation_view_count =
            idle_view->idle_return_observation_view_count;
        coupling_copy(result->record.
                runtime_process_return_observation_view_status,
            sizeof(result->record.
                runtime_process_return_observation_view_status),
            process_view->process_return_observation_view_status);
        coupling_copy(result->record.
                runtime_scheduler_return_observation_view_status,
            sizeof(result->record.
                runtime_scheduler_return_observation_view_status),
            scheduler_view->scheduler_return_observation_view_status);
        coupling_copy(result->record.runtime_post_resume_observation_view_status,
            sizeof(result->record.runtime_post_resume_observation_view_status),
            post_resume_view->post_resume_observation_view_status);
        coupling_copy(result->record.runtime_user_mode_resume_view_status,
            sizeof(result->record.runtime_user_mode_resume_view_status),
            user_resume_view->user_mode_resume_view_status);
        coupling_copy(result->record.runtime_register_view_status,
            sizeof(result->record.runtime_register_view_status),
            register_view->register_view_status);
        coupling_copy(result->record.runtime_entry_frame_status,
            sizeof(result->record.runtime_entry_frame_status),
            register_view->runtime_entry_frame.frame_status);
        coupling_copy(result->record.scheduler_run_entry_status,
            sizeof(result->record.scheduler_run_entry_status),
            register_view->runtime_entry_frame.runtime_entry_admission.
                scheduler_run_entry.run_entry_status);
        result->record.process_return_observation_view_count =
            process_view->process_return_observation_view_count;
        result->record.scheduler_return_observation_view_count =
            scheduler_view->scheduler_return_observation_view_count;
        result->record.post_resume_observation_view_count =
            post_resume_view->post_resume_observation_view_count;
        result->record.user_mode_resume_view_count =
            user_resume_view->user_mode_resume_view_count;
        result->record.register_view_count = register_view->register_view_count;
    }

}

static void set_blocked(latticra_nucleus_kernel_coupling_result_t *result,
                        latticra_nucleus_kernel_coupling_denial_t denial,
                        int no_effect_chain_ok) {
    result->record.classification = LATTICRA_NUCLEUS_KERNEL_COUPLING_BLOCKED;
    result->record.denial = denial;
    coupling_copy(result->record.readiness_status,
        sizeof(result->record.readiness_status),
        "nucleus-kernel-coupling-blocked");
    coupling_copy(result->record.os_readiness_status,
        sizeof(result->record.os_readiness_status), "os-metadata-blocked");
    result->record.prerequisites_satisfied = 0;
    result->record.no_effect_chain_ok = no_effect_chain_ok;
    result->record.report_only = 1;
    result->record.no_effect = 1;
    result->record.evidence_level = 1u;
    result->no_effect = 1;
}

static void set_invalid(latticra_nucleus_kernel_coupling_result_t *result,
                        latticra_nucleus_kernel_coupling_denial_t denial) {
    result->record.classification = LATTICRA_NUCLEUS_KERNEL_COUPLING_INVALID;
    result->record.denial = denial;
    coupling_copy(result->record.readiness_status,
        sizeof(result->record.readiness_status), "invalid");
    coupling_copy(result->record.os_readiness_status,
        sizeof(result->record.os_readiness_status), "os-metadata-invalid");
    result->record.prerequisites_satisfied = 0;
    result->record.no_effect_chain_ok = 0;
    result->record.report_only = 1;
    result->record.no_effect = 1;
    result->record.evidence_level = 0u;
    result->no_effect = 1;
}

static void set_ready(latticra_nucleus_kernel_coupling_result_t *result) {
    result->record.classification =
        LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_ONLY_READY;
    result->record.denial = LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_OK;
    coupling_copy(result->record.readiness_status,
        sizeof(result->record.readiness_status),
        "nucleus-kernel-coupling-ready");
    coupling_copy(result->record.os_readiness_status,
        sizeof(result->record.os_readiness_status), "os-metadata-ready");
    result->record.prerequisites_satisfied = 1;
    result->record.no_effect_chain_ok = 1;
    result->record.report_only = 1;
    result->record.no_effect = 1;
    result->record.runtime_recovery_audit_observation_view_allowed = 0;
    result->record.recovery_audit_allowed = 0;
    result->record.recovery_audit_observation_allowed = 0;
    result->runtime_recovery_audit_observation_view_allowed = 0;
    result->recovery_audit_allowed = 0;
    result->recovery_audit_observation_allowed = 0;
    result->record.evidence_level = 49u;
    result->no_effect = 1;
}

static void coupling_authority_ok(
    latticra_nucleus_task_authority_summary_t *authority) {
    memset(authority, 0, sizeof(*authority));
    authority->status = LATTICRA_STATUS_OK;
    coupling_copy(authority->status_label, sizeof(authority->status_label),
        "ok");
    coupling_copy(authority->validator_label, sizeof(authority->validator_label),
        "nucleus-kernel-coupling");
    coupling_copy(authority->requested_effect_label,
        sizeof(authority->requested_effect_label), "none");
    coupling_copy(authority->denial_reason, sizeof(authority->denial_reason),
        "ok");
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->network_allowed = 0;
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static latticra_status_t build_default_plan(
    latticra_nucleus_task_plan_result_t *plan) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t task_request;
    latticra_nucleus_task_result_t task;
    latticra_nucleus_task_plan_request_t plan_request;
    latticra_status_t status;

    if (plan == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    coupling_authority_ok(&authority);
    memset(&preview, 0, sizeof(preview));
    status = latticra_nucleus_classify_preview(LATTICRA_REQUEST_STATE_REPORT,
        LATTICRA_EFFECT_NONE, &preview);
    if (status != LATTICRA_STATUS_OK) return status;

    memset(&task_request, 0, sizeof(task_request));
    coupling_copy(task_request.task_id, sizeof(task_request.task_id),
        "nucleus-kernel-coupling-task");
    task_request.request_kind = LATTICRA_NUCLEUS_TASK_STATE_REPORT;
    task_request.requested_effect = LATTICRA_NUCLEUS_TASK_EFFECT_NONE;
    task_request.operator_confirmation =
        LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    task_request.rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    task_request.authority = &authority;
    task_request.preview = &preview;
    task_request.source_identity = "nucleus-kernel-coupling-default";
    task_request.source_identity_len = strlen("nucleus-kernel-coupling-default");
    task_request.source_span = coupling_default_span();
    status = latticra_nucleus_task_classify(&task_request, &task);
    if (status != LATTICRA_STATUS_OK) return status;

    memset(&plan_request, 0, sizeof(plan_request));
    coupling_copy(plan_request.plan_id, sizeof(plan_request.plan_id),
        "nucleus-kernel-coupling-plan");
    plan_request.tasks = &task;
    plan_request.task_count = 1u;
    return latticra_nucleus_task_plan_evaluate(&plan_request, plan);
}

latticra_status_t latticra_nucleus_kernel_coupling_default_nucleus_plan(
    latticra_nucleus_task_plan_result_t *plan) {
    return build_default_plan(plan);
}

latticra_status_t latticra_nucleus_kernel_coupling_evaluate(
    const latticra_nucleus_kernel_coupling_request_t *request,
    latticra_nucleus_kernel_coupling_result_t *result) {
    const latticra_kernel_runtime_entry_register_view_result_t
        *runtime_register_view;
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
    latticra_nucleus_kernel_coupling_request_t capture_request;
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);
    result->record_count = 1u;

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        set_invalid(result, LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NULL_ARGUMENT);
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    coupling_copy(result->record.coupling_id, sizeof(result->record.coupling_id),
        request->coupling_id);
    result->record.source_span = request->source_span;
    if (!coupling_copy_n(result->record.source_identity,
            sizeof(result->record.source_identity),
            request->source_identity,
            request->source_identity_len)) {
        set_invalid(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_INTERNAL_ERROR);
        return LATTICRA_STATUS_OK;
    }

    runtime_register_view = request->runtime_register_view;
    runtime_process_return_observation_view =
        request->runtime_process_return_observation_view;
    runtime_idle_return_observation_view =
        request->runtime_idle_return_observation_view;
    runtime_quiescent_return_observation_view =
        request->runtime_quiescent_return_observation_view;
    runtime_persistence_boundary_observation_view =
        request->runtime_persistence_boundary_observation_view;
    runtime_recovery_boundary_observation_view =
        request->runtime_recovery_boundary_observation_view;
    runtime_recovery_plan_observation_view =
        request->runtime_recovery_plan_observation_view;
    runtime_recovery_disposition_observation_view =
        request->runtime_recovery_disposition_observation_view;
    runtime_recovery_outcome_observation_view =
        request->runtime_recovery_outcome_observation_view;
    runtime_recovery_closeout_observation_view =
        request->runtime_recovery_closeout_observation_view;
    runtime_recovery_audit_observation_view =
        request->runtime_recovery_audit_observation_view;
    if (runtime_recovery_audit_observation_view != 0) {
        if (runtime_recovery_closeout_observation_view == 0) {
            runtime_recovery_closeout_observation_view =
                recovery_closeout_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_recovery_outcome_observation_view == 0) {
            runtime_recovery_outcome_observation_view =
                recovery_outcome_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_recovery_disposition_observation_view == 0) {
            runtime_recovery_disposition_observation_view =
                recovery_disposition_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_recovery_plan_observation_view == 0) {
            runtime_recovery_plan_observation_view =
                recovery_plan_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_recovery_boundary_observation_view == 0) {
            runtime_recovery_boundary_observation_view =
                recovery_boundary_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_persistence_boundary_observation_view == 0) {
            runtime_persistence_boundary_observation_view =
                persistence_boundary_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_quiescent_return_observation_view == 0) {
            runtime_quiescent_return_observation_view =
                quiescent_return_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_recovery_audit(
                    runtime_recovery_audit_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_recovery_audit_observation(
                    runtime_recovery_audit_observation_view);
        }
    }
    if (runtime_recovery_closeout_observation_view != 0) {
        if (runtime_recovery_outcome_observation_view == 0) {
            runtime_recovery_outcome_observation_view =
                recovery_outcome_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_recovery_disposition_observation_view == 0) {
            runtime_recovery_disposition_observation_view =
                recovery_disposition_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_recovery_plan_observation_view == 0) {
            runtime_recovery_plan_observation_view =
                recovery_plan_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_recovery_boundary_observation_view == 0) {
            runtime_recovery_boundary_observation_view =
                recovery_boundary_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_persistence_boundary_observation_view == 0) {
            runtime_persistence_boundary_observation_view =
                persistence_boundary_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_quiescent_return_observation_view == 0) {
            runtime_quiescent_return_observation_view =
                quiescent_return_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_recovery_closeout(
                    runtime_recovery_closeout_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_recovery_closeout_observation(
                    runtime_recovery_closeout_observation_view);
        }
    }
    if (runtime_recovery_outcome_observation_view != 0) {
        if (runtime_recovery_disposition_observation_view == 0) {
            runtime_recovery_disposition_observation_view =
                recovery_disposition_observation_from_recovery_outcome(
                    runtime_recovery_outcome_observation_view);
        }
        if (runtime_recovery_plan_observation_view == 0) {
            runtime_recovery_plan_observation_view =
                recovery_plan_observation_from_recovery_outcome(
                    runtime_recovery_outcome_observation_view);
        }
        if (runtime_recovery_boundary_observation_view == 0) {
            runtime_recovery_boundary_observation_view =
                recovery_boundary_observation_from_recovery_outcome(
                    runtime_recovery_outcome_observation_view);
        }
        if (runtime_persistence_boundary_observation_view == 0) {
            runtime_persistence_boundary_observation_view =
                persistence_boundary_observation_from_recovery_outcome(
                    runtime_recovery_outcome_observation_view);
        }
        if (runtime_quiescent_return_observation_view == 0) {
            runtime_quiescent_return_observation_view =
                quiescent_return_observation_from_recovery_outcome(
                    runtime_recovery_outcome_observation_view);
        }
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_recovery_outcome(
                    runtime_recovery_outcome_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_recovery_outcome(
                    runtime_recovery_outcome_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_recovery_outcome_observation(
                    runtime_recovery_outcome_observation_view);
        }
    }
    if (runtime_recovery_disposition_observation_view != 0) {
        if (runtime_recovery_plan_observation_view == 0) {
            runtime_recovery_plan_observation_view =
                recovery_plan_observation_from_recovery_disposition(
                    runtime_recovery_disposition_observation_view);
        }
        if (runtime_recovery_boundary_observation_view == 0) {
            runtime_recovery_boundary_observation_view =
                recovery_boundary_observation_from_recovery_disposition(
                    runtime_recovery_disposition_observation_view);
        }
        if (runtime_persistence_boundary_observation_view == 0) {
            runtime_persistence_boundary_observation_view =
                persistence_boundary_observation_from_recovery_disposition(
                    runtime_recovery_disposition_observation_view);
        }
        if (runtime_quiescent_return_observation_view == 0) {
            runtime_quiescent_return_observation_view =
                quiescent_return_observation_from_recovery_disposition(
                    runtime_recovery_disposition_observation_view);
        }
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_recovery_disposition(
                    runtime_recovery_disposition_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_recovery_disposition(
                    runtime_recovery_disposition_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_recovery_disposition_observation(
                    runtime_recovery_disposition_observation_view);
        }
    }
    if (runtime_recovery_plan_observation_view != 0) {
        if (runtime_recovery_boundary_observation_view == 0) {
            runtime_recovery_boundary_observation_view =
                recovery_boundary_observation_from_recovery_plan(
                    runtime_recovery_plan_observation_view);
        }
        if (runtime_persistence_boundary_observation_view == 0) {
            runtime_persistence_boundary_observation_view =
                persistence_boundary_observation_from_recovery_plan(
                    runtime_recovery_plan_observation_view);
        }
        if (runtime_quiescent_return_observation_view == 0) {
            runtime_quiescent_return_observation_view =
                quiescent_return_observation_from_recovery_plan(
                    runtime_recovery_plan_observation_view);
        }
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_recovery_plan(
                    runtime_recovery_plan_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_recovery_plan(
                    runtime_recovery_plan_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_recovery_plan_observation(
                    runtime_recovery_plan_observation_view);
        }
    }
    if (runtime_recovery_boundary_observation_view != 0) {
        if (runtime_persistence_boundary_observation_view == 0) {
            runtime_persistence_boundary_observation_view =
                persistence_boundary_observation_from_recovery_boundary(
                    runtime_recovery_boundary_observation_view);
        }
        if (runtime_quiescent_return_observation_view == 0) {
            runtime_quiescent_return_observation_view =
                quiescent_return_observation_from_recovery_boundary(
                    runtime_recovery_boundary_observation_view);
        }
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_recovery_boundary(
                    runtime_recovery_boundary_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_recovery_boundary(
                    runtime_recovery_boundary_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_recovery_boundary_observation(
                    runtime_recovery_boundary_observation_view);
        }
    }
    if (runtime_persistence_boundary_observation_view != 0) {
        if (runtime_quiescent_return_observation_view == 0) {
            runtime_quiescent_return_observation_view =
                quiescent_return_observation_from_persistence_boundary(
                    runtime_persistence_boundary_observation_view);
        }
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_persistence_boundary(
                    runtime_persistence_boundary_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_persistence_boundary(
                    runtime_persistence_boundary_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_persistence_boundary_observation(
                    runtime_persistence_boundary_observation_view);
        }
    }
    if (runtime_quiescent_return_observation_view != 0) {
        if (runtime_idle_return_observation_view == 0) {
            runtime_idle_return_observation_view =
                idle_return_observation_from_quiescent_return(
                    runtime_quiescent_return_observation_view);
        }
        if (runtime_process_return_observation_view == 0) {
            runtime_process_return_observation_view =
                process_return_observation_from_quiescent_return(
                    runtime_quiescent_return_observation_view);
        }
        if (runtime_register_view == 0) {
            runtime_register_view =
                register_view_from_quiescent_return_observation(
                    runtime_quiescent_return_observation_view);
        }
    }

    capture_request = *request;
    capture_request.runtime_register_view = runtime_register_view;
    capture_request.runtime_process_return_observation_view =
        runtime_process_return_observation_view;
    capture_request.runtime_idle_return_observation_view =
        runtime_idle_return_observation_view;
    capture_request.runtime_quiescent_return_observation_view =
        runtime_quiescent_return_observation_view;
    capture_request.runtime_persistence_boundary_observation_view =
        runtime_persistence_boundary_observation_view;
    capture_request.runtime_recovery_boundary_observation_view =
        runtime_recovery_boundary_observation_view;
    capture_request.runtime_recovery_plan_observation_view =
        runtime_recovery_plan_observation_view;
    capture_request.runtime_recovery_disposition_observation_view =
        runtime_recovery_disposition_observation_view;
    capture_request.runtime_recovery_outcome_observation_view =
        runtime_recovery_outcome_observation_view;
    capture_request.runtime_recovery_closeout_observation_view =
        runtime_recovery_closeout_observation_view;
    capture_request.runtime_recovery_audit_observation_view =
        runtime_recovery_audit_observation_view;
    capture_evidence(&capture_request, result);

    if (request->nucleus_plan == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_MISSING, 0);
        return LATTICRA_STATUS_OK;
    }
    if (!task_plan_ready(request->nucleus_plan)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_BLOCKED, 0);
        return LATTICRA_STATUS_OK;
    }

    if (request->kernel_registry == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_REGISTRY_MISSING, 0);
        return LATTICRA_STATUS_OK;
    }
    if (!kernel_registry_ready(request->kernel_registry)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_REGISTRY_BLOCKED, 0);
        return LATTICRA_STATUS_OK;
    }

    if (request->kernel_lifecycle == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_MISSING, 0);
        return LATTICRA_STATUS_OK;
    }
    if (!kernel_lifecycle_ready(request->kernel_lifecycle)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_BLOCKED, 0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_register_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_register_view_ready(runtime_register_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_process_return_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_process_return_observation_ready(
            runtime_process_return_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_idle_return_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_idle_return_observation_ready(
            runtime_idle_return_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_quiescent_return_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_quiescent_return_observation_ready(
            runtime_quiescent_return_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_persistence_boundary_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_persistence_boundary_observation_ready(
            runtime_persistence_boundary_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_recovery_boundary_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_recovery_boundary_observation_ready(
            runtime_recovery_boundary_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_recovery_plan_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_recovery_plan_observation_ready(
            runtime_recovery_plan_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_recovery_disposition_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_recovery_disposition_observation_ready(
            runtime_recovery_disposition_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_recovery_outcome_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_recovery_outcome_observation_ready(
            runtime_recovery_outcome_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_recovery_closeout_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_recovery_closeout_observation_ready(
            runtime_recovery_closeout_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    if (runtime_recovery_audit_observation_view == 0) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_MISSING,
            0);
        return LATTICRA_STATUS_OK;
    }
    if (!runtime_recovery_audit_observation_ready(
            runtime_recovery_audit_observation_view)) {
        set_blocked(result,
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_BLOCKED,
            0);
        return LATTICRA_STATUS_OK;
    }

    set_ready(result);
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_nucleus_kernel_coupling_evaluate_default(
    latticra_nucleus_kernel_coupling_result_t *result) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_request_t registry_request;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_request_t lifecycle_request;
    latticra_kernel_lifecycle_result_t lifecycle;
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

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    status = build_default_plan(&plan);
    if (status != LATTICRA_STATUS_OK) return status;

    status = latticra_kernel_subsystem_registry_default_request(
        &registry_request);
    if (status != LATTICRA_STATUS_OK) return status;
    status = latticra_kernel_subsystem_registry_evaluate(&registry_request,
        &registry);
    if (status != LATTICRA_STATUS_OK) return status;

    status = latticra_kernel_lifecycle_default_request(&lifecycle_request);
    if (status != LATTICRA_STATUS_OK) return status;
    lifecycle_request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    lifecycle_request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY;
    lifecycle_request.max_steps = LATTICRA_KERNEL_LIFECYCLE_STEP_MAX;
    status = latticra_kernel_lifecycle_run(&lifecycle_request, &lifecycle);
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
    coupling_request.kernel_registry = &registry;
    coupling_request.kernel_lifecycle = &lifecycle;
    coupling_request.runtime_register_view =
        register_view_from_persistence_boundary_observation(
            &persistence_boundary_view);
    coupling_request.runtime_process_return_observation_view =
        process_return_observation_from_persistence_boundary(
            &persistence_boundary_view);
    coupling_request.runtime_idle_return_observation_view =
        idle_return_observation_from_persistence_boundary(
            &persistence_boundary_view);
    coupling_request.runtime_quiescent_return_observation_view =
        quiescent_return_observation_from_persistence_boundary(
            &persistence_boundary_view);
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
    return latticra_nucleus_kernel_coupling_evaluate(&coupling_request, result);
}

static int append_text(char *buffer,
                       size_t buffer_len,
                       size_t *used,
                       const char *fmt,
                       ...) {
    int written;
    va_list args;
    if (buffer == 0 || used == 0 || fmt == 0 || *used >= buffer_len) return 0;
    va_start(args, fmt);
    written = vsnprintf(buffer + *used, buffer_len - *used, fmt, args);
    va_end(args);
    if (written < 0 || (size_t)written >= buffer_len - *used) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return 0;
    }
    *used += (size_t)written;
    return 1;
}

latticra_status_t latticra_nucleus_kernel_coupling_report(
    const latticra_nucleus_kernel_coupling_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    const latticra_nucleus_kernel_coupling_record_t *record;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    record = &result->record;

    if (!append_text(buffer, buffer_len, &used,
            "LATTICRA NUCLEUS KERNEL COUPLING REPORT\n") ||
        !append_text(buffer, buffer_len, &used, "status=%d\n",
            (int)result->status) ||
        !append_text(buffer, buffer_len, &used, "coupling_id=%s\n",
            record->coupling_id) ||
        !append_text(buffer, buffer_len, &used, "record_count=%lu\n",
            (unsigned long)result->record_count) ||
        !append_text(buffer, buffer_len, &used, "classification=%s\n",
            latticra_nucleus_kernel_coupling_classification_label(
                record->classification)) ||
        !append_text(buffer, buffer_len, &used, "reason=%s\n",
            latticra_nucleus_kernel_coupling_denial_label(record->denial)) ||
        !append_text(buffer, buffer_len, &used, "readiness_status=%s\n",
            record->readiness_status) ||
        !append_text(buffer, buffer_len, &used, "os_readiness_status=%s\n",
            record->os_readiness_status) ||
        !append_text(buffer, buffer_len, &used, "nucleus_plan_status=%s\n",
            record->nucleus_plan_status) ||
        !append_text(buffer, buffer_len, &used, "kernel_registry_status=%s\n",
            record->kernel_registry_status) ||
        !append_text(buffer, buffer_len, &used, "kernel_status=%s\n",
            record->kernel_status) ||
        !append_text(buffer, buffer_len, &used,
            "kernel_lifecycle_status=%s\n",
            record->kernel_lifecycle_status) ||
        !append_text(buffer, buffer_len, &used,
            "kernel_lifecycle_final_state=%s\n",
            record->kernel_lifecycle_final_state) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_register_view_status=%s\n",
            record->runtime_register_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_entry_frame_status=%s\n",
            record->runtime_entry_frame_status) ||
        !append_text(buffer, buffer_len, &used,
            "scheduler_run_entry_status=%s\n",
            record->scheduler_run_entry_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_process_return_observation_view_status=%s\n",
            record->runtime_process_return_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_scheduler_return_observation_view_status=%s\n",
            record->runtime_scheduler_return_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_post_resume_observation_view_status=%s\n",
            record->runtime_post_resume_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_user_mode_resume_view_status=%s\n",
            record->runtime_user_mode_resume_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_idle_return_observation_view_status=%s\n",
            record->runtime_idle_return_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_quiescent_return_observation_view_status=%s\n",
            record->runtime_quiescent_return_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_persistence_boundary_observation_view_status=%s\n",
            record->runtime_persistence_boundary_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_boundary_observation_view_status=%s\n",
            record->runtime_recovery_boundary_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_plan_observation_view_status=%s\n",
            record->runtime_recovery_plan_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_disposition_observation_view_status=%s\n",
            record->runtime_recovery_disposition_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_outcome_observation_view_status=%s\n",
            record->runtime_recovery_outcome_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_closeout_observation_view_status=%s\n",
            record->runtime_recovery_closeout_observation_view_status) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_audit_observation_view_status=%s\n",
            record->runtime_recovery_audit_observation_view_status) ||
        !append_text(buffer, buffer_len, &used, "task_count=%lu\n",
            (unsigned long)record->task_count) ||
        !append_text(buffer, buffer_len, &used, "accepted_task_count=%lu\n",
            (unsigned long)record->accepted_task_count) ||
        !append_text(buffer, buffer_len, &used, "blocked_task_count=%lu\n",
            (unsigned long)record->blocked_task_count) ||
        !append_text(buffer, buffer_len, &used, "subsystem_count=%lu\n",
            (unsigned long)record->subsystem_count) ||
        !append_text(buffer, buffer_len, &used, "lifecycle_step_count=%lu\n",
            (unsigned long)record->lifecycle_step_count) ||
        !append_text(buffer, buffer_len, &used,
            "lifecycle_state_change_count=%lu\n",
            (unsigned long)record->lifecycle_state_change_count) ||
        !append_text(buffer, buffer_len, &used, "register_view_count=%lu\n",
            (unsigned long)record->register_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "process_return_observation_view_count=%lu\n",
            (unsigned long)record->process_return_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "scheduler_return_observation_view_count=%lu\n",
            (unsigned long)record->scheduler_return_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "post_resume_observation_view_count=%lu\n",
            (unsigned long)record->post_resume_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "user_mode_resume_view_count=%lu\n",
            (unsigned long)record->user_mode_resume_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "idle_return_observation_view_count=%lu\n",
            (unsigned long)record->idle_return_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "quiescent_return_observation_view_count=%lu\n",
            (unsigned long)record->quiescent_return_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "persistence_boundary_observation_view_count=%lu\n",
            (unsigned long)record->persistence_boundary_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_boundary_observation_view_count=%lu\n",
            (unsigned long)record->recovery_boundary_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_plan_observation_view_count=%lu\n",
            (unsigned long)record->recovery_plan_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_disposition_observation_view_count=%lu\n",
            (unsigned long)record->recovery_disposition_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_outcome_observation_view_count=%lu\n",
            (unsigned long)record->recovery_outcome_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_closeout_observation_view_count=%lu\n",
            (unsigned long)record->recovery_closeout_observation_view_count) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_audit_observation_view_count=%lu\n",
            (unsigned long)record->recovery_audit_observation_view_count) ||
        !append_text(buffer, buffer_len, &used, "prerequisites_satisfied=%d\n",
            record->prerequisites_satisfied) ||
        !append_text(buffer, buffer_len, &used, "no_effect_chain_ok=%d\n",
            record->no_effect_chain_ok) ||
        !append_text(buffer, buffer_len, &used, "lifecycle_complete=%d\n",
            record->lifecycle_complete) ||
        !append_text(buffer, buffer_len, &used, "report_only=%d\n",
            record->report_only) ||
        !append_text(buffer, buffer_len, &used, "no_effect=%d\n",
            record->no_effect) ||
        !append_text(buffer, buffer_len, &used, "execution_allowed=%d\n",
            record->execution_allowed) ||
        !append_text(buffer, buffer_len, &used, "mutation_allowed=%d\n",
            record->mutation_allowed) ||
        !append_text(buffer, buffer_len, &used, "network_allowed=%d\n",
            record->network_allowed) ||
        !append_text(buffer, buffer_len, &used, "server_allowed=%d\n",
            record->server_allowed) ||
        !append_text(buffer, buffer_len, &used, "recovery_allowed=%d\n",
            record->recovery_allowed) ||
        !append_text(buffer, buffer_len, &used, "hardware_allowed=%d\n",
            record->hardware_allowed) ||
        !append_text(buffer, buffer_len, &used, "boot_allowed=%d\n",
            record->boot_allowed) ||
        !append_text(buffer, buffer_len, &used, "runtime_entry_allowed=%d\n",
            record->runtime_entry_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "scheduler_run_entry_allowed=%d\n",
            record->scheduler_run_entry_allowed) ||
        !append_text(buffer, buffer_len, &used, "context_switch_allowed=%d\n",
            record->context_switch_allowed) ||
        !append_text(buffer, buffer_len, &used, "register_save_allowed=%d\n",
            record->register_save_allowed) ||
        !append_text(buffer, buffer_len, &used, "register_restore_allowed=%d\n",
            record->register_restore_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_process_return_observation_view_allowed=%d\n",
            record->runtime_process_return_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_scheduler_return_observation_view_allowed=%d\n",
            record->runtime_scheduler_return_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_post_resume_observation_view_allowed=%d\n",
            record->runtime_post_resume_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_idle_return_observation_view_allowed=%d\n",
            record->runtime_idle_return_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_quiescent_return_observation_view_allowed=%d\n",
            record->runtime_quiescent_return_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_persistence_boundary_observation_view_allowed=%d\n",
            record->runtime_persistence_boundary_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_boundary_observation_view_allowed=%d\n",
            record->runtime_recovery_boundary_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_plan_observation_view_allowed=%d\n",
            record->runtime_recovery_plan_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_disposition_observation_view_allowed=%d\n",
            record->runtime_recovery_disposition_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_outcome_observation_view_allowed=%d\n",
            record->runtime_recovery_outcome_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_closeout_observation_view_allowed=%d\n",
            record->runtime_recovery_closeout_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "runtime_recovery_audit_observation_view_allowed=%d\n",
            record->runtime_recovery_audit_observation_view_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "scheduler_return_observation_allowed=%d\n",
            record->scheduler_return_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "process_return_observation_allowed=%d\n",
            record->process_return_observation_allowed) ||
        !append_text(buffer, buffer_len, &used, "process_return_allowed=%d\n",
            record->process_return_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "idle_return_observation_allowed=%d\n",
            record->idle_return_observation_allowed) ||
        !append_text(buffer, buffer_len, &used, "idle_return_allowed=%d\n",
            record->idle_return_allowed) ||
        !append_text(buffer, buffer_len, &used, "idle_state_read_allowed=%d\n",
            record->idle_state_read_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "quiescent_return_observation_allowed=%d\n",
            record->quiescent_return_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "quiescent_return_allowed=%d\n",
            record->quiescent_return_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "quiescent_state_read_allowed=%d\n",
            record->quiescent_state_read_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "persistence_boundary_observation_allowed=%d\n",
            record->persistence_boundary_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "persistence_boundary_allowed=%d\n",
            record->persistence_boundary_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "persistence_commit_allowed=%d\n",
            record->persistence_commit_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_boundary_observation_allowed=%d\n",
            record->recovery_boundary_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_boundary_allowed=%d\n",
            record->recovery_boundary_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_plan_allowed=%d\n",
            record->recovery_plan_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_plan_observation_allowed=%d\n",
            record->recovery_plan_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_disposition_allowed=%d\n",
            record->recovery_disposition_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_disposition_observation_allowed=%d\n",
            record->recovery_disposition_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_outcome_allowed=%d\n",
            record->recovery_outcome_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_outcome_observation_allowed=%d\n",
            record->recovery_outcome_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_closeout_allowed=%d\n",
            record->recovery_closeout_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_closeout_observation_allowed=%d\n",
            record->recovery_closeout_observation_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_audit_allowed=%d\n",
            record->recovery_audit_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_audit_observation_allowed=%d\n",
            record->recovery_audit_observation_allowed) ||
        !append_text(buffer, buffer_len, &used, "process_state_read_allowed=%d\n",
            record->process_state_read_allowed) ||
        !append_text(buffer, buffer_len, &used, "scheduler_execution_allowed=%d\n",
            record->scheduler_execution_allowed) ||
        !append_text(buffer, buffer_len, &used, "scheduler_dispatch_allowed=%d\n",
            record->scheduler_dispatch_allowed) ||
        !append_text(buffer, buffer_len, &used, "run_queue_mutation_allowed=%d\n",
            record->run_queue_mutation_allowed) ||
        !append_text(buffer, buffer_len, &used, "process_wake_allowed=%d\n",
            record->process_wake_allowed) ||
        !append_text(buffer, buffer_len, &used, "persistence_allowed=%d\n",
            record->persistence_allowed) ||
        !append_text(buffer, buffer_len, &used,
            "recovery_authority_allowed=%d\n",
            record->recovery_authority_allowed) ||
        !append_text(buffer, buffer_len, &used, "host_effect_allowed=%d\n",
            record->host_effect_allowed) ||
        !append_text(buffer, buffer_len, &used, "evidence_level=%u\n",
            record->evidence_level) ||
        !append_text(buffer, buffer_len, &used, "source_identity=%s\n",
            record->source_identity) ||
        !append_text(buffer, buffer_len, &used, "span_start_offset=%lu\n",
            (unsigned long)record->source_span.start_offset) ||
        !append_text(buffer, buffer_len, &used, "span_end_offset=%lu\n",
            (unsigned long)record->source_span.end_offset)) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
