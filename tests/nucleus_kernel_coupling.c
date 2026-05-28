#include "latticra/nucleus_kernel_coupling.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

#define EXPECT_STR_EQ(actual, expected, message) \
    do { \
        if (strcmp((actual), (expected)) != 0) { \
            fprintf(stderr, "FAIL: %s: expected '%s' got '%s'\n", \
                message, expected, actual); \
            return 1; \
        } \
    } while (0)

static latticra_l_ui_source_span_t span_ok(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 12u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 13u;
    return span;
}

static void authority_ok(latticra_nucleus_task_authority_summary_t *authority) {
    memset(authority, 0, sizeof(*authority));
    authority->status = LATTICRA_STATUS_OK;
    (void)snprintf(authority->status_label, sizeof(authority->status_label),
        "%s", "ok");
    (void)snprintf(authority->validator_label, sizeof(authority->validator_label),
        "%s", "nucleus-kernel-coupling");
    (void)snprintf(authority->requested_effect_label,
        sizeof(authority->requested_effect_label), "%s", "none");
    (void)snprintf(authority->denial_reason, sizeof(authority->denial_reason),
        "%s", "ok");
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->network_allowed = 0;
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static latticra_nucleus_task_request_t task_request(
    latticra_nucleus_task_request_kind_t kind,
    latticra_nucleus_task_effect_t effect,
    const latticra_nucleus_task_authority_summary_t *authority) {
    latticra_nucleus_task_request_t request;
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.task_id, sizeof(request.task_id), "%s",
        "coupling-task");
    request.request_kind = kind;
    request.requested_effect = effect;
    request.operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    request.rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    request.authority = authority;
    request.source_identity = "coupling-test";
    request.source_identity_len = strlen("coupling-test");
    request.source_span = span_ok();
    return request;
}

static latticra_status_t build_ready_plan(
    latticra_nucleus_task_plan_result_t *plan) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t task;
    latticra_nucleus_task_plan_request_t plan_request;

    authority_ok(&authority);
    memset(&preview, 0, sizeof(preview));
    if (latticra_nucleus_classify_preview(LATTICRA_REQUEST_STATE_REPORT,
            LATTICRA_EFFECT_NONE, &preview) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    request = task_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT,
        LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;
    if (latticra_nucleus_task_classify(&request, &task) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(&plan_request, 0, sizeof(plan_request));
    (void)snprintf(plan_request.plan_id, sizeof(plan_request.plan_id), "%s",
        "coupling-plan");
    plan_request.tasks = &task;
    plan_request.task_count = 1u;
    return latticra_nucleus_task_plan_evaluate(&plan_request, plan);
}

static latticra_status_t build_future_gated_plan(
    latticra_nucleus_task_plan_result_t *plan) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t task;
    latticra_nucleus_task_plan_request_t plan_request;

    authority_ok(&authority);
    request = task_request(LATTICRA_NUCLEUS_TASK_BOOT_ACTION,
        LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    if (latticra_nucleus_task_classify(&request, &task) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(&plan_request, 0, sizeof(plan_request));
    (void)snprintf(plan_request.plan_id, sizeof(plan_request.plan_id), "%s",
        "coupling-future-plan");
    plan_request.tasks = &task;
    plan_request.task_count = 1u;
    return latticra_nucleus_task_plan_evaluate(&plan_request, plan);
}

static latticra_status_t build_ready_registry(
    latticra_kernel_subsystem_registry_result_t *registry) {
    latticra_kernel_subsystem_registry_request_t request;
    if (latticra_kernel_subsystem_registry_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return latticra_kernel_subsystem_registry_evaluate(&request, registry);
}

static latticra_status_t build_ready_lifecycle(
    latticra_kernel_lifecycle_result_t *lifecycle) {
    latticra_kernel_lifecycle_request_t request;
    if (latticra_kernel_lifecycle_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_OBSERVATION_VIEW_READY;
    request.max_steps = LATTICRA_KERNEL_LIFECYCLE_STEP_MAX;
    return latticra_kernel_lifecycle_run(&request, lifecycle);
}

static latticra_status_t build_process_return_lifecycle(
    latticra_kernel_lifecycle_result_t *lifecycle) {
    latticra_kernel_lifecycle_request_t request;
    if (latticra_kernel_lifecycle_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_READY;
    request.max_steps = LATTICRA_KERNEL_LIFECYCLE_STEP_MAX;
    return latticra_kernel_lifecycle_run(&request, lifecycle);
}

static latticra_status_t build_ready_register_view(
    latticra_kernel_runtime_entry_register_view_result_t *register_view) {
    latticra_kernel_runtime_entry_register_view_request_t request;
    if (latticra_kernel_runtime_entry_register_view_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return latticra_kernel_runtime_entry_register_view_evaluate(&request,
        register_view);
}

static latticra_status_t build_ready_process_return_observation_view(
    latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *process_return_view) {
    latticra_kernel_runtime_entry_process_return_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_process_return_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return latticra_kernel_runtime_entry_process_return_observation_view_evaluate(
        &request, process_return_view);
}

static latticra_status_t build_ready_idle_return_observation_view(
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        *idle_return_view) {
    latticra_kernel_runtime_entry_idle_return_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_idle_return_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return latticra_kernel_runtime_entry_idle_return_observation_view_evaluate(
        &request, idle_return_view);
}

static latticra_status_t build_ready_quiescent_return_observation_view(
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *quiescent_return_view) {
    latticra_kernel_runtime_entry_quiescent_return_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return latticra_kernel_runtime_entry_quiescent_return_observation_view_evaluate(
        &request, quiescent_return_view);
}

static latticra_status_t build_ready_persistence_boundary_observation_view(
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view) {
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_persistence_boundary_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_persistence_boundary_observation_view_evaluate(
            &request, persistence_boundary_view);
}

static latticra_status_t build_ready_recovery_boundary_observation_view(
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view) {
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_boundary_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_boundary_observation_view_evaluate(
            &request, recovery_boundary_view);
}

static latticra_status_t build_ready_recovery_plan_observation_view(
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view) {
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_plan_observation_view_evaluate(
            &request, recovery_plan_view);
}

static latticra_status_t build_ready_recovery_disposition_observation_view(
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view) {
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_disposition_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_disposition_observation_view_evaluate(
            &request, recovery_disposition_view);
}

static latticra_status_t build_ready_recovery_outcome_observation_view(
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *recovery_outcome_view) {
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_outcome_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_outcome_observation_view_evaluate(
            &request, recovery_outcome_view);
}

static latticra_status_t build_ready_recovery_closeout_observation_view(
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *recovery_closeout_view) {
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_closeout_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_closeout_observation_view_evaluate(
            &request, recovery_closeout_view);
}

static latticra_status_t build_ready_recovery_audit_observation_view(
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *recovery_audit_view) {
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_audit_observation_view_evaluate(
            &request, recovery_audit_view);
}

static latticra_status_t
build_ready_recovery_audit_review_disposition_observation_view(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t
        *recovery_audit_review_disposition_view) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_evaluate(
            &request, recovery_audit_review_disposition_view);
}

static latticra_status_t
build_ready_recovery_audit_review_disposition_review_observation_view(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_result_t
        *recovery_audit_review_disposition_review_view) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_evaluate(
            &request, recovery_audit_review_disposition_review_view);
}

static latticra_status_t
build_ready_recovery_audit_review_disposition_review_closeout_observation_view(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_result_t
        *recovery_audit_review_disposition_review_closeout_view) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_evaluate(
            &request, recovery_audit_review_disposition_review_closeout_view);
}

static latticra_status_t
build_ready_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        *recovery_audit_review_disposition_review_closeout_archive_gate_view) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_evaluate(
            &request,
            recovery_audit_review_disposition_review_closeout_archive_gate_view);
}

static latticra_status_t
build_ready_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_result_t
        *recovery_audit_review_disposition_review_closeout_archive_gate_review_view) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_request_t
        request;
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    return
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_evaluate(
            &request,
            recovery_audit_review_disposition_review_closeout_archive_gate_review_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_idle_return_observation(
    const latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        *idle_return_view) {
    return &idle_return_view->runtime_entry_process_return_observation_view.
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
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_quiescent_return_observation(
    const latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *quiescent_return_view) {
    return register_view_from_idle_return_observation(
        &quiescent_return_view->runtime_entry_idle_return_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_persistence_boundary_observation(
    const
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view) {
    return register_view_from_quiescent_return_observation(
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_boundary_observation(
    const
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view) {
    return register_view_from_persistence_boundary_observation(
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_plan_observation(
    const
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view) {
    return register_view_from_recovery_boundary_observation(
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_disposition_observation(
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view) {
    return register_view_from_recovery_plan_observation(
        &recovery_disposition_view->runtime_entry_recovery_plan_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_outcome_observation(
    const
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *recovery_outcome_view) {
    return register_view_from_recovery_disposition_observation(
        &recovery_outcome_view->runtime_entry_recovery_disposition_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_closeout_observation(
    const
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *recovery_closeout_view) {
    return register_view_from_recovery_outcome_observation(
        &recovery_closeout_view->runtime_entry_recovery_outcome_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_audit_observation(
    const
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *recovery_audit_view) {
    return register_view_from_recovery_closeout_observation(
        &recovery_audit_view->runtime_entry_recovery_closeout_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_audit_review_disposition_observation(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t
        *recovery_audit_review_disposition_view) {
    return register_view_from_recovery_audit_observation(
        &recovery_audit_review_disposition_view->
            runtime_entry_recovery_audit_review_observation_view.
            runtime_entry_recovery_audit_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_audit_review_disposition_review_observation(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_result_t
        *recovery_audit_review_disposition_review_view) {
    return register_view_from_recovery_audit_review_disposition_observation(
        &recovery_audit_review_disposition_review_view->
            runtime_entry_recovery_audit_review_disposition_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_audit_review_disposition_review_closeout_observation(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_result_t
        *recovery_audit_review_disposition_review_closeout_view) {
    return register_view_from_recovery_audit_review_disposition_review_observation(
        &recovery_audit_review_disposition_review_closeout_view->
            runtime_entry_recovery_audit_review_disposition_review_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_audit_review_disposition_review_closeout_archive_gate_observation(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        *recovery_audit_review_disposition_review_closeout_archive_gate_view) {
    return register_view_from_recovery_audit_review_disposition_review_closeout_observation(
        &recovery_audit_review_disposition_review_closeout_archive_gate_view->
            runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view);
}

static const latticra_kernel_runtime_entry_register_view_result_t *
register_view_from_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_result_t
        *recovery_audit_review_disposition_review_closeout_archive_gate_review_view) {
    return register_view_from_recovery_audit_review_disposition_review_closeout_archive_gate_observation(
        &recovery_audit_review_disposition_review_closeout_archive_gate_review_view->
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view);
}

static latticra_nucleus_kernel_coupling_request_t coupling_request(
    const latticra_nucleus_task_plan_result_t *plan,
    const latticra_kernel_subsystem_registry_result_t *registry,
    const latticra_kernel_lifecycle_result_t *lifecycle,
    const latticra_kernel_runtime_entry_register_view_result_t *register_view,
    const latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *process_return_view,
    const latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        *idle_return_view,
    const latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        *quiescent_return_view) {
    latticra_nucleus_kernel_coupling_request_t request;
    (void)latticra_nucleus_kernel_coupling_default_request(&request);
    request.nucleus_plan = plan;
    request.kernel_registry = registry;
    request.kernel_lifecycle = lifecycle;
    request.runtime_register_view = register_view;
    request.runtime_process_return_observation_view = process_return_view;
    request.runtime_idle_return_observation_view = idle_return_view;
    request.runtime_quiescent_return_observation_view = quiescent_return_view;
    request.source_identity = "coupling-test";
    request.source_identity_len = strlen("coupling-test");
    request.source_span = span_ok();
    return request;
}

typedef struct {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_result_t
        recovery_audit_review_disposition_review_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_result_t
        recovery_audit_review_disposition_review_closeout_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        recovery_audit_review_disposition_review_closeout_archive_gate_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_result_t
        recovery_audit_review_disposition_review_closeout_archive_gate_review_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t
        *recovery_audit_review_disposition_view;
    latticra_kernel_runtime_entry_recovery_audit_review_observation_view_result_t
        *recovery_audit_review_view;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *recovery_audit_view;
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *recovery_closeout_view;
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *recovery_outcome_view;
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
} recovery_tail_fixture_t;

static int build_ready_recovery_tail_fixture(recovery_tail_fixture_t *fixture) {
    if (fixture == 0) return 1;
    memset(fixture, 0, sizeof(*fixture));
    if (build_ready_plan(&fixture->plan) != LATTICRA_STATUS_OK) return 1;
    if (build_ready_registry(&fixture->registry) != LATTICRA_STATUS_OK) return 1;
    if (build_ready_lifecycle(&fixture->lifecycle) != LATTICRA_STATUS_OK) return 1;
    if (build_ready_recovery_audit_review_disposition_review_observation_view(
            &fixture->recovery_audit_review_disposition_review_view) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (build_ready_recovery_audit_review_disposition_review_closeout_observation_view(
            &fixture->recovery_audit_review_disposition_review_closeout_view) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (build_ready_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view(
            &fixture->recovery_audit_review_disposition_review_closeout_archive_gate_view) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (build_ready_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view(
            &fixture->recovery_audit_review_disposition_review_closeout_archive_gate_review_view) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fixture->recovery_audit_review_disposition_view =
        &fixture->recovery_audit_review_disposition_review_view.
            runtime_entry_recovery_audit_review_disposition_observation_view;
    fixture->recovery_audit_review_view =
        &fixture->recovery_audit_review_disposition_view->
            runtime_entry_recovery_audit_review_observation_view;
    fixture->recovery_audit_view =
        &fixture->recovery_audit_review_view->
            runtime_entry_recovery_audit_observation_view;
    fixture->recovery_closeout_view =
        &fixture->recovery_audit_view->
            runtime_entry_recovery_closeout_observation_view;
    fixture->recovery_outcome_view =
        &fixture->recovery_closeout_view->
            runtime_entry_recovery_outcome_observation_view;
    fixture->recovery_disposition_view =
        &fixture->recovery_outcome_view->
            runtime_entry_recovery_disposition_observation_view;
    fixture->recovery_plan_view =
        &fixture->recovery_disposition_view->
            runtime_entry_recovery_plan_observation_view;
    fixture->recovery_boundary_view =
        &fixture->recovery_plan_view->
            runtime_entry_recovery_boundary_observation_view;
    fixture->persistence_boundary_view =
        &fixture->recovery_boundary_view->
            runtime_entry_persistence_boundary_observation_view;

    fixture->request = coupling_request(&fixture->plan, &fixture->registry,
        &fixture->lifecycle,
        register_view_from_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation(
            &fixture->recovery_audit_review_disposition_review_closeout_archive_gate_review_view),
        &fixture->persistence_boundary_view->
            runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &fixture->persistence_boundary_view->
            runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &fixture->persistence_boundary_view->
            runtime_entry_quiescent_return_observation_view);
    fixture->request.runtime_persistence_boundary_observation_view =
        fixture->persistence_boundary_view;
    fixture->request.runtime_recovery_boundary_observation_view =
        fixture->recovery_boundary_view;
    fixture->request.runtime_recovery_plan_observation_view =
        fixture->recovery_plan_view;
    fixture->request.runtime_recovery_disposition_observation_view =
        fixture->recovery_disposition_view;
    fixture->request.runtime_recovery_outcome_observation_view =
        fixture->recovery_outcome_view;
    fixture->request.runtime_recovery_closeout_observation_view =
        fixture->recovery_closeout_view;
    fixture->request.runtime_recovery_audit_observation_view =
        fixture->recovery_audit_view;
    fixture->request.runtime_recovery_audit_review_observation_view =
        fixture->recovery_audit_review_view;
    fixture->request.runtime_recovery_audit_review_disposition_observation_view =
        fixture->recovery_audit_review_disposition_view;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_observation_view =
        &fixture->recovery_audit_review_disposition_review_view;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_observation_view =
        &fixture->recovery_audit_review_disposition_review_closeout_view;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        &fixture->recovery_audit_review_disposition_review_closeout_archive_gate_view;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        &fixture->recovery_audit_review_disposition_review_closeout_archive_gate_review_view;
    return 0;
}

static int ready_evidence_produces_os_metadata_ready_report(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t
        recovery_audit_review_disposition_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_result_t
        recovery_audit_review_disposition_review_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_result_t
        recovery_audit_review_disposition_review_closeout_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        recovery_audit_review_disposition_review_closeout_archive_gate_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_result_t
        recovery_audit_review_disposition_review_closeout_archive_gate_review_view;
    const latticra_kernel_runtime_entry_recovery_audit_review_observation_view_result_t
        *recovery_audit_review_view;
    const latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        *recovery_audit_view;
    const latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *recovery_closeout_view;
    const latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *recovery_outcome_view;
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view;
    const latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_audit_review_disposition_observation_view(
            &recovery_audit_review_disposition_view) ==
            LATTICRA_STATUS_OK,
        "ready recovery audit review disposition observation view");
    EXPECT_TRUE(build_ready_recovery_audit_review_disposition_review_observation_view(
            &recovery_audit_review_disposition_review_view) ==
            LATTICRA_STATUS_OK,
        "ready recovery audit review disposition review observation view");
    EXPECT_TRUE(build_ready_recovery_audit_review_disposition_review_closeout_observation_view(
            &recovery_audit_review_disposition_review_closeout_view) ==
            LATTICRA_STATUS_OK,
        "ready recovery audit review disposition review closeout observation view");
    EXPECT_TRUE(build_ready_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view(
            &recovery_audit_review_disposition_review_closeout_archive_gate_view) ==
            LATTICRA_STATUS_OK,
        "ready recovery audit review disposition review closeout archive gate observation view");
    EXPECT_TRUE(build_ready_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view(
            &recovery_audit_review_disposition_review_closeout_archive_gate_review_view) ==
            LATTICRA_STATUS_OK,
        "ready recovery audit review disposition review closeout archive gate review observation view");
    recovery_audit_review_view =
        &recovery_audit_review_disposition_review_view.
            runtime_entry_recovery_audit_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_observation_view;
    recovery_audit_view =
        &recovery_audit_review_view->runtime_entry_recovery_audit_observation_view;
    recovery_closeout_view =
        &recovery_audit_view->runtime_entry_recovery_closeout_observation_view;
    recovery_outcome_view =
        &recovery_closeout_view->runtime_entry_recovery_outcome_observation_view;
    recovery_disposition_view =
        &recovery_outcome_view->runtime_entry_recovery_disposition_observation_view;
    recovery_plan_view =
        &recovery_disposition_view->runtime_entry_recovery_plan_observation_view;
    recovery_boundary_view =
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation(
            &recovery_audit_review_disposition_review_closeout_archive_gate_review_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        recovery_plan_view;
    request.runtime_recovery_disposition_observation_view =
        recovery_disposition_view;
    request.runtime_recovery_outcome_observation_view =
        recovery_outcome_view;
    request.runtime_recovery_closeout_observation_view =
        recovery_closeout_view;
    request.runtime_recovery_audit_observation_view =
        recovery_audit_view;
    request.runtime_recovery_audit_review_observation_view =
        recovery_audit_review_view;
    request.runtime_recovery_audit_review_disposition_observation_view =
        &recovery_audit_review_disposition_view;
    request.runtime_recovery_audit_review_disposition_review_observation_view =
        &recovery_audit_review_disposition_review_view;
    request.runtime_recovery_audit_review_disposition_review_closeout_observation_view =
        &recovery_audit_review_disposition_review_closeout_view;
    request.runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        &recovery_audit_review_disposition_review_closeout_archive_gate_view;
    request.runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        &recovery_audit_review_disposition_review_closeout_archive_gate_review_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "coupling evaluates");
    if (result.record.classification !=
            LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_ONLY_READY) {
        fprintf(stderr, "ready denial: %s\n",
            latticra_nucleus_kernel_coupling_denial_label(result.record.denial));
    }
    EXPECT_TRUE(result.record.classification ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_ONLY_READY,
        "coupling ready classification");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_OK,
        "coupling ready reason");
    EXPECT_STR_EQ(result.record.readiness_status,
        "nucleus-kernel-coupling-ready", "readiness status");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-ready",
        "os readiness status");
    EXPECT_STR_EQ(result.record.nucleus_plan_status, "allow-no-effect-sequence",
        "plan status");
    EXPECT_STR_EQ(result.record.kernel_registry_status, "registry-ready",
        "registry status");
    EXPECT_STR_EQ(result.record.kernel_lifecycle_status, "lifecycle-complete",
        "lifecycle status");
    EXPECT_STR_EQ(result.record.kernel_lifecycle_final_state,
        "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-ready",
        "lifecycle final state");
    EXPECT_STR_EQ(result.record.runtime_register_view_status,
        "runtime-entry-register-view-seed-ready", "runtime register status");
    EXPECT_STR_EQ(result.record.runtime_process_return_observation_view_status,
        "runtime-entry-process-return-observation-view-seed-ready",
        "process return observation status");
    EXPECT_STR_EQ(result.record.runtime_scheduler_return_observation_view_status,
        "runtime-entry-scheduler-return-observation-view-seed-ready",
        "scheduler return observation status");
    EXPECT_STR_EQ(result.record.runtime_post_resume_observation_view_status,
        "runtime-entry-post-resume-observation-view-seed-ready",
        "post resume observation status");
    EXPECT_STR_EQ(result.record.runtime_user_mode_resume_view_status,
        "runtime-entry-user-mode-resume-view-seed-ready",
        "user mode resume status");
    EXPECT_STR_EQ(result.record.runtime_idle_return_observation_view_status,
        "runtime-entry-idle-return-observation-view-seed-ready",
        "idle return observation status");
    EXPECT_STR_EQ(result.record.runtime_quiescent_return_observation_view_status,
        "runtime-entry-quiescent-return-observation-view-seed-ready",
        "quiescent return observation status");
    EXPECT_STR_EQ(
        result.record.runtime_persistence_boundary_observation_view_status,
        "runtime-entry-persistence-boundary-observation-view-seed-ready",
        "persistence boundary observation status");
    EXPECT_STR_EQ(
        result.record.runtime_recovery_boundary_observation_view_status,
        "runtime-entry-recovery-boundary-observation-view-seed-ready",
        "recovery boundary observation status");
    EXPECT_STR_EQ(
        result.record.runtime_recovery_plan_observation_view_status,
        "runtime-entry-recovery-plan-observation-view-seed-ready",
        "recovery plan observation status");
    EXPECT_STR_EQ(
        result.record.runtime_recovery_disposition_observation_view_status,
        "runtime-entry-recovery-disposition-observation-view-seed-ready",
        "recovery disposition observation status");
    EXPECT_STR_EQ(
        result.record.runtime_recovery_outcome_observation_view_status,
        "runtime-entry-recovery-outcome-observation-view-seed-ready",
        "recovery outcome observation status");
    EXPECT_STR_EQ(
        result.record.runtime_recovery_closeout_observation_view_status,
        "runtime-entry-recovery-closeout-observation-view-seed-ready",
        "recovery closeout observation status");
    EXPECT_STR_EQ(
        result.record.runtime_recovery_audit_observation_view_status,
        "runtime-entry-recovery-audit-observation-view-seed-ready",
        "recovery audit observation status");
    EXPECT_STR_EQ(
        result.record.runtime_recovery_audit_review_observation_view_status,
        "runtime-entry-recovery-audit-review-observation-view-seed-ready",
        "recovery audit review observation status");
    EXPECT_STR_EQ(
        result.record.
            runtime_recovery_audit_review_disposition_observation_view_status,
        "runtime-entry-recovery-audit-review-disposition-observation-view-seed-ready",
        "recovery audit review disposition observation status");
    EXPECT_STR_EQ(
        result.record.
            runtime_recovery_audit_review_disposition_review_observation_view_status,
        "runtime-entry-recovery-audit-review-disposition-review-observation-view-seed-ready",
        "recovery audit review disposition review observation status");
    EXPECT_STR_EQ(
        result.record.
            runtime_recovery_audit_review_disposition_review_closeout_observation_view_status,
        "runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-seed-ready",
        "recovery audit review disposition review closeout observation status");
    EXPECT_STR_EQ(
        result.record.
            runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status,
        "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-seed-ready",
        "recovery audit review disposition review closeout archive gate observation status");
    EXPECT_TRUE(result.record.task_count == 1u, "task count");
    EXPECT_TRUE(result.record.accepted_task_count == 1u, "accepted task count");
    EXPECT_TRUE(result.record.subsystem_count == LATTICRA_KERNEL_SUBSYSTEM_COUNT,
        "subsystem count");
    EXPECT_TRUE(result.record.lifecycle_step_count == 52u,
        "lifecycle step count");
    EXPECT_TRUE(result.record.lifecycle_state_change_count == 52u,
        "lifecycle state change count");
    EXPECT_TRUE(result.record.register_view_count == 4u, "register view count");
    EXPECT_TRUE(result.record.process_return_observation_view_count == 4u,
        "process return observation count");
    EXPECT_TRUE(result.record.scheduler_return_observation_view_count == 4u,
        "scheduler return observation count");
    EXPECT_TRUE(result.record.post_resume_observation_view_count == 4u,
        "post resume observation count");
    EXPECT_TRUE(result.record.user_mode_resume_view_count == 4u,
        "user mode resume count");
    EXPECT_TRUE(result.record.idle_return_observation_view_count == 4u,
        "idle return observation count");
    EXPECT_TRUE(result.record.quiescent_return_observation_view_count == 4u,
        "quiescent return observation count");
    EXPECT_TRUE(result.record.persistence_boundary_observation_view_count == 4u,
        "persistence boundary observation count");
    EXPECT_TRUE(result.record.recovery_boundary_observation_view_count == 4u,
        "recovery boundary observation count");
    EXPECT_TRUE(result.record.recovery_plan_observation_view_count == 4u,
        "recovery plan observation count");
    EXPECT_TRUE(result.record.recovery_disposition_observation_view_count == 4u,
        "recovery disposition observation count");
    EXPECT_TRUE(result.record.recovery_outcome_observation_view_count == 4u,
        "recovery outcome observation count");
    EXPECT_TRUE(result.record.recovery_closeout_observation_view_count == 4u,
        "recovery closeout observation count");
    EXPECT_TRUE(result.record.recovery_audit_observation_view_count == 4u,
        "recovery audit observation count");
    EXPECT_TRUE(result.record.recovery_audit_review_observation_view_count == 4u,
        "recovery audit review observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_observation_view_count ==
            4u,
        "recovery audit review disposition observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_observation_view_count ==
            4u,
        "recovery audit review disposition review observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_observation_view_count ==
            4u,
        "recovery audit review disposition review closeout observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count ==
            4u,
        "recovery audit review disposition review closeout archive gate observation count");
    EXPECT_TRUE(result.record.prerequisites_satisfied == 1, "prereq ok");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 1, "no effect chain");
    EXPECT_TRUE(result.record.lifecycle_complete == 1, "lifecycle complete");
    EXPECT_TRUE(result.record.no_effect == 1, "no effect");
    EXPECT_TRUE(result.record.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(result.record.boot_allowed == 0, "boot denied");
    EXPECT_TRUE(result.record.runtime_entry_allowed == 0, "runtime entry denied");
    EXPECT_TRUE(result.record.scheduler_run_entry_allowed == 0,
        "scheduler run entry denied");
    EXPECT_TRUE(result.record.register_save_allowed == 0, "register save denied");
    EXPECT_TRUE(result.record.register_restore_allowed == 0,
        "register restore denied");
    EXPECT_TRUE(result.record.process_return_allowed == 0,
        "process return denied");
    EXPECT_TRUE(result.record.idle_return_allowed == 0,
        "idle return denied");
    EXPECT_TRUE(result.record.idle_state_read_allowed == 0,
        "idle state read denied");
    EXPECT_TRUE(result.record.scheduler_execution_allowed == 0,
        "scheduler execution denied");
    EXPECT_TRUE(result.record.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.record.persistence_boundary_allowed == 0,
        "persistence boundary denied");
    EXPECT_TRUE(result.record.persistence_commit_allowed == 0,
        "persistence commit denied");
    EXPECT_TRUE(result.record.recovery_boundary_allowed == 0,
        "recovery boundary denied");
    EXPECT_TRUE(result.record.recovery_plan_allowed == 0,
        "recovery plan denied");
    EXPECT_TRUE(result.record.recovery_plan_observation_allowed == 0,
        "recovery plan observation denied");
    EXPECT_TRUE(result.record.recovery_disposition_allowed == 0,
        "recovery disposition denied");
    EXPECT_TRUE(result.record.recovery_disposition_observation_allowed == 0,
        "recovery disposition observation denied");
    EXPECT_TRUE(result.record.recovery_outcome_allowed == 0,
        "recovery outcome denied");
    EXPECT_TRUE(result.record.recovery_outcome_observation_allowed == 0,
        "recovery outcome observation denied");
    EXPECT_TRUE(result.record.recovery_closeout_allowed == 0,
        "recovery closeout denied");
    EXPECT_TRUE(result.record.recovery_closeout_observation_allowed == 0,
        "recovery closeout observation denied");
    EXPECT_TRUE(result.record.recovery_audit_allowed == 0,
        "recovery audit denied");
    EXPECT_TRUE(result.record.recovery_audit_observation_allowed == 0,
        "recovery audit observation denied");
    EXPECT_TRUE(result.record.recovery_audit_review_allowed == 0,
        "recovery audit review denied");
    EXPECT_TRUE(result.record.recovery_audit_review_observation_allowed == 0,
        "recovery audit review observation denied");
    EXPECT_TRUE(result.record.recovery_audit_review_disposition_allowed == 0,
        "recovery audit review disposition denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_observation_allowed == 0,
        "recovery audit review disposition observation denied");
    EXPECT_TRUE(result.record.recovery_audit_review_disposition_review_allowed == 0,
        "recovery audit review disposition review denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_observation_allowed == 0,
        "recovery audit review disposition review observation denied");
    EXPECT_TRUE(result.record.recovery_audit_review_disposition_review_closeout_allowed == 0,
        "recovery audit review disposition review closeout denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_observation_allowed == 0,
        "recovery audit review disposition review closeout observation denied");
    EXPECT_TRUE(
        result.record.runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed == 0,
        "runtime recovery audit review disposition review closeout archive gate observation view denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_archive_gate_allowed == 0,
        "recovery audit review disposition review closeout archive gate denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed == 0,
        "recovery audit review disposition review closeout archive gate observation denied");
    EXPECT_TRUE(result.record.evidence_level == 55u, "evidence level");

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");
    EXPECT_TRUE(strstr(report,
            "LATTICRA NUCLEUS KERNEL COUPLING REPORT\n") != 0,
        "report header");
    EXPECT_TRUE(strstr(report, "classification=report-only-ready\n") != 0,
        "classification emitted");
    EXPECT_TRUE(strstr(report, "os_readiness_status=os-metadata-ready\n") != 0,
        "os readiness emitted");
    EXPECT_TRUE(strstr(report,
            "kernel_lifecycle_status=lifecycle-complete\n") != 0,
        "lifecycle status emitted");
    EXPECT_TRUE(strstr(report,
            "kernel_lifecycle_final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-ready\n") != 0,
        "lifecycle final state emitted");
    EXPECT_TRUE(strstr(report, "lifecycle_step_count=52\n") != 0,
        "lifecycle step count emitted");
    EXPECT_TRUE(strstr(report, "lifecycle_complete=1\n") != 0,
        "lifecycle complete emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_allowed=0\n") != 0,
        "runtime entry flag emitted");
    EXPECT_TRUE(strstr(report, "register_save_allowed=0\n") != 0,
        "register save flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_process_return_observation_view_status=runtime-entry-process-return-observation-view-seed-ready\n") != 0,
        "process return observation status emitted");
    EXPECT_TRUE(strstr(report, "process_return_observation_view_count=4\n") != 0,
        "process return observation count emitted");
    EXPECT_TRUE(strstr(report, "process_return_allowed=0\n") != 0,
        "process return flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_idle_return_observation_view_status=runtime-entry-idle-return-observation-view-seed-ready\n") != 0,
        "idle return observation status emitted");
    EXPECT_TRUE(strstr(report, "idle_return_observation_view_count=4\n") != 0,
        "idle return observation count emitted");
    EXPECT_TRUE(strstr(report, "idle_return_allowed=0\n") != 0,
        "idle return flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_quiescent_return_observation_view_status=runtime-entry-quiescent-return-observation-view-seed-ready\n") != 0,
        "quiescent return observation status emitted");
    EXPECT_TRUE(strstr(report, "quiescent_return_observation_view_count=4\n") != 0,
        "quiescent return observation count emitted");
    EXPECT_TRUE(strstr(report, "quiescent_return_allowed=0\n") != 0,
        "quiescent return flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_persistence_boundary_observation_view_status=runtime-entry-persistence-boundary-observation-view-seed-ready\n") != 0,
        "persistence boundary observation status emitted");
    EXPECT_TRUE(strstr(report,
            "persistence_boundary_observation_view_count=4\n") != 0,
        "persistence boundary observation count emitted");
    EXPECT_TRUE(strstr(report, "persistence_commit_allowed=0\n") != 0,
        "persistence commit flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_boundary_observation_view_status=runtime-entry-recovery-boundary-observation-view-seed-ready\n") != 0,
        "recovery boundary observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_boundary_observation_view_count=4\n") != 0,
        "recovery boundary observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_plan_observation_view_status=runtime-entry-recovery-plan-observation-view-seed-ready\n") != 0,
        "recovery plan observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view_count=4\n") != 0,
        "recovery plan observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_disposition_observation_view_status=runtime-entry-recovery-disposition-observation-view-seed-ready\n") != 0,
        "recovery disposition observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_disposition_observation_view_count=4\n") != 0,
        "recovery disposition observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_outcome_observation_view_status=runtime-entry-recovery-outcome-observation-view-seed-ready\n") != 0,
        "recovery outcome observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_outcome_observation_view_count=4\n") != 0,
        "recovery outcome observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_closeout_observation_view_status=runtime-entry-recovery-closeout-observation-view-seed-ready\n") != 0,
        "recovery closeout observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_closeout_observation_view_count=4\n") != 0,
        "recovery closeout observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_observation_view_status=runtime-entry-recovery-audit-observation-view-seed-ready\n") != 0,
        "recovery audit observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_observation_view_count=4\n") != 0,
        "recovery audit observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_observation_view_status=runtime-entry-recovery-audit-review-observation-view-seed-ready\n") != 0,
        "recovery audit review observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_observation_view_count=4\n") != 0,
        "recovery audit review observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_disposition_observation_view_status=runtime-entry-recovery-audit-review-disposition-observation-view-seed-ready\n") != 0,
        "recovery audit review disposition observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_observation_view_count=4\n") != 0,
        "recovery audit review disposition observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_disposition_review_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-observation-view-seed-ready\n") != 0,
        "recovery audit review disposition review observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_observation_view_count=4\n") != 0,
        "recovery audit review disposition review observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_disposition_review_closeout_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-seed-ready\n") != 0,
        "recovery audit review disposition review closeout observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_observation_view_count=4\n") != 0,
        "recovery audit review disposition review closeout observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-seed-ready\n") != 0,
        "recovery audit review disposition review closeout archive gate observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count=4\n") != 0,
        "recovery audit review disposition review closeout archive gate observation count emitted");
    EXPECT_TRUE(strstr(report, "recovery_plan_allowed=0\n") != 0,
        "recovery plan flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_plan_observation_allowed=0\n") != 0,
        "recovery plan observation flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_disposition_allowed=0\n") != 0,
        "recovery disposition flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_disposition_observation_allowed=0\n") != 0,
        "recovery disposition observation flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_outcome_allowed=0\n") != 0,
        "recovery outcome flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_outcome_observation_allowed=0\n") != 0,
        "recovery outcome observation flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_closeout_allowed=0\n") != 0,
        "recovery closeout flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_closeout_observation_allowed=0\n") != 0,
        "recovery closeout observation flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_allowed=0\n") != 0,
        "recovery audit flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_observation_allowed=0\n") != 0,
        "recovery audit observation flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_review_allowed=0\n") != 0,
        "recovery audit review flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_review_observation_allowed=0\n") != 0,
        "recovery audit review observation flag emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_review_disposition_allowed=0\n") != 0,
        "recovery audit review disposition flag emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_observation_allowed=0\n") != 0,
        "recovery audit review disposition observation flag emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_allowed=0\n") != 0,
        "recovery audit review disposition review flag emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_observation_allowed=0\n") != 0,
        "recovery audit review disposition review observation flag emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_allowed=0\n") != 0,
        "recovery audit review disposition review closeout flag emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_observation_allowed=0\n") != 0,
        "recovery audit review disposition review closeout observation flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0\n") != 0,
        "runtime recovery audit review disposition review closeout archive gate observation view flag emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0\n") != 0,
        "recovery audit review disposition review closeout archive gate flag emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0\n") != 0,
        "recovery audit review disposition review closeout archive gate observation flag emitted");
    return 0;
}

static int default_evaluator_builds_ready_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_default_nucleus_plan(&plan) ==
            LATTICRA_STATUS_OK,
        "default coupling nucleus plan evaluates");
    EXPECT_TRUE(plan.record.policy ==
            LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE,
        "default coupling nucleus plan no-effect");
    EXPECT_TRUE(plan.record.accepted_count == 1u,
        "default coupling nucleus plan accepted task");

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate_default(&result) ==
            LATTICRA_STATUS_OK,
        "default coupling evaluates");
    EXPECT_TRUE(result.record.classification ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_ONLY_READY,
        "default coupling ready");
    EXPECT_STR_EQ(result.record.readiness_status,
        "nucleus-kernel-coupling-ready", "default readiness status");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-ready",
        "default os readiness");
    EXPECT_TRUE(result.record.task_count == 1u, "default task count");
    EXPECT_TRUE(result.record.subsystem_count == LATTICRA_KERNEL_SUBSYSTEM_COUNT,
        "default subsystem count");
    EXPECT_STR_EQ(result.record.kernel_lifecycle_final_state,
        "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-ready",
        "default lifecycle final state");
    EXPECT_TRUE(result.record.lifecycle_step_count == 52u,
        "default lifecycle step count");
    EXPECT_TRUE(result.record.lifecycle_state_change_count == 52u,
        "default lifecycle state change count");
    EXPECT_TRUE(result.record.lifecycle_complete == 1,
        "default lifecycle complete");
    EXPECT_TRUE(result.record.register_view_count == 4u,
        "default register view count");
    EXPECT_TRUE(result.record.process_return_observation_view_count == 4u,
        "default process return observation count");
    EXPECT_TRUE(result.record.user_mode_resume_view_count == 4u,
        "default user mode resume count");
    EXPECT_TRUE(result.record.idle_return_observation_view_count == 4u,
        "default idle return observation count");
    EXPECT_TRUE(result.record.quiescent_return_observation_view_count == 4u,
        "default quiescent return observation count");
    EXPECT_TRUE(result.record.persistence_boundary_observation_view_count == 4u,
        "default persistence boundary observation count");
    EXPECT_TRUE(result.record.recovery_boundary_observation_view_count == 4u,
        "default recovery boundary observation count");
    EXPECT_TRUE(result.record.recovery_plan_observation_view_count == 4u,
        "default recovery plan observation count");
    EXPECT_TRUE(result.record.recovery_disposition_observation_view_count == 4u,
        "default recovery disposition observation count");
    EXPECT_TRUE(result.record.recovery_outcome_observation_view_count == 4u,
        "default recovery outcome observation count");
    EXPECT_TRUE(result.record.recovery_closeout_observation_view_count == 4u,
        "default recovery closeout observation count");
    EXPECT_TRUE(result.record.recovery_audit_observation_view_count == 4u,
        "default recovery audit observation count");
    EXPECT_TRUE(result.record.recovery_audit_review_observation_view_count == 4u,
        "default recovery audit review observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_observation_view_count ==
            4u,
        "default recovery audit review disposition observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_observation_view_count ==
            4u,
        "default recovery audit review disposition review observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_observation_view_count ==
            4u,
        "default recovery audit review disposition review closeout observation count");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count ==
            4u,
        "default recovery audit review disposition review closeout archive gate observation count");
    EXPECT_TRUE(result.record.persistence_commit_allowed == 0,
        "default persistence commit denied");
    EXPECT_TRUE(result.record.recovery_plan_allowed == 0,
        "default recovery plan denied");
    EXPECT_TRUE(result.record.recovery_disposition_allowed == 0,
        "default recovery disposition denied");
    EXPECT_TRUE(result.record.recovery_outcome_allowed == 0,
        "default recovery outcome denied");
    EXPECT_TRUE(result.record.recovery_closeout_allowed == 0,
        "default recovery closeout denied");
    EXPECT_TRUE(result.record.recovery_audit_allowed == 0,
        "default recovery audit denied");
    EXPECT_TRUE(result.record.recovery_audit_review_allowed == 0,
        "default recovery audit review denied");
    EXPECT_TRUE(result.record.recovery_audit_review_disposition_allowed == 0,
        "default recovery audit review disposition denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_observation_allowed == 0,
        "default recovery audit review disposition observation denied");
    EXPECT_TRUE(result.record.recovery_audit_review_disposition_review_allowed == 0,
        "default recovery audit review disposition review denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_observation_allowed == 0,
        "default recovery audit review disposition review observation denied");
    EXPECT_TRUE(
        result.record.
            runtime_recovery_audit_review_disposition_review_closeout_observation_view_allowed == 0,
        "default runtime recovery audit review disposition review closeout observation view denied");
    EXPECT_TRUE(
        result.record.recovery_audit_review_disposition_review_closeout_allowed ==
            0,
        "default recovery audit review disposition review closeout denied");
    EXPECT_TRUE(
        result.record.
            recovery_audit_review_disposition_review_closeout_observation_allowed ==
            0,
        "default recovery audit review disposition review closeout observation denied");
    EXPECT_TRUE(
        result.record.
            runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed == 0,
        "default runtime recovery audit review disposition review closeout archive gate observation view denied");
    EXPECT_TRUE(
        result.record.
            recovery_audit_review_disposition_review_closeout_archive_gate_allowed ==
            0,
        "default recovery audit review disposition review closeout archive gate denied");
    EXPECT_TRUE(
        result.record.
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed ==
            0,
        "default recovery audit review disposition review closeout archive gate observation denied");
    EXPECT_TRUE(result.record.runtime_entry_allowed == 0,
        "default runtime entry denied");
    EXPECT_TRUE(result.record.process_return_allowed == 0,
        "default process return denied");
    EXPECT_TRUE(result.record.idle_return_allowed == 0,
        "default idle return denied");
    EXPECT_TRUE(result.record.boot_allowed == 0, "default boot denied");
    EXPECT_TRUE(result.record.host_effect_allowed == 0,
        "default host effect denied");
    EXPECT_TRUE(result.record.evidence_level == 55u,
        "default evidence level");

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "default report writes");
    EXPECT_TRUE(strstr(report, "classification=report-only-ready\n") != 0,
        "default classification emitted");
    EXPECT_TRUE(strstr(report, "source_identity=nucleus-kernel-coupling-default\n") != 0,
        "default source identity emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_disposition_review_closeout_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-seed-ready\n") != 0,
        "default closeout observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_observation_view_count=4\n") != 0,
        "default closeout observation count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-seed-ready\n") != 0,
        "default archive gate observation status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count=4\n") != 0,
        "default archive gate observation count emitted");
    EXPECT_TRUE(strstr(report, "evidence_level=55\n") != 0,
        "default evidence level emitted");
    return 0;
}

static int process_return_lifecycle_blocks_idle_return_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        idle_return_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK,
        "process return lifecycle plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "process return lifecycle registry");
    EXPECT_TRUE(build_process_return_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "process return lifecycle");
    EXPECT_TRUE(build_ready_idle_return_observation_view(&idle_return_view) ==
            LATTICRA_STATUS_OK,
        "process return lifecycle idle return observation view");

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_idle_return_observation(&idle_return_view),
        &idle_return_view.runtime_entry_process_return_observation_view,
        &idle_return_view,
        0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "process return lifecycle coupling evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_BLOCKED,
        "process return lifecycle blocked");
    EXPECT_STR_EQ(result.record.kernel_lifecycle_final_state,
        "runtime-entry-process-return-observation-view-ready",
        "process return lifecycle final state");
    EXPECT_TRUE(result.record.lifecycle_step_count == 37u,
        "process return lifecycle step count");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "process return lifecycle no effect chain blocked");
    return 0;
}

static int missing_nucleus_plan_blocks_coupling(void) {
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing plan evaluates");
    EXPECT_TRUE(result.record.classification ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_BLOCKED,
        "missing plan blocked");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_MISSING,
        "missing plan reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing plan os status");
    EXPECT_TRUE(result.record.no_effect == 1, "missing plan no effect");
    return 0;
}

static int future_gated_plan_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_future_gated_plan(&plan) == LATTICRA_STATUS_OK,
        "future plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");
    request = coupling_request(&plan, &registry, 0, &register_view, 0, 0, 0);

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "future coupling evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_NUCLEUS_PLAN_BLOCKED,
        "future plan reason");
    EXPECT_TRUE(result.record.accepted_task_count == 0u,
        "future accepted count");
    EXPECT_TRUE(result.record.blocked_task_count == 1u,
        "future blocked count");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "future no effect chain blocked");
    EXPECT_TRUE(result.record.boot_allowed == 0, "future boot still denied");
    return 0;
}

static int kernel_registry_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");
    registry.network_allowed = 1;
    registry.entries[LATTICRA_KERNEL_SUBSYSTEM_NETWORK].network_allowed = 1;
    registry.entries[LATTICRA_KERNEL_SUBSYSTEM_NETWORK].no_effect = 0;

    request = coupling_request(&plan, &registry, 0, &register_view, 0, 0, 0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "registry blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_REGISTRY_BLOCKED,
        "registry blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "registry no effect chain blocked");
    EXPECT_TRUE(result.record.network_allowed == 0,
        "coupling does not grant network");
    return 0;
}

static int missing_lifecycle_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");

    request = coupling_request(&plan, &registry, 0, &register_view, 0, 0, 0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing lifecycle evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_MISSING,
        "missing lifecycle reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing lifecycle os status");
    return 0;
}

static int incomplete_lifecycle_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");
    lifecycle.lifecycle_complete = 0;
    lifecycle.final_state = LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_READY;

    request = coupling_request(&plan, &registry, &lifecycle, &register_view,
        0, 0, 0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "incomplete lifecycle evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_KERNEL_LIFECYCLE_BLOCKED,
        "incomplete lifecycle reason");
    EXPECT_TRUE(result.record.lifecycle_complete == 0,
        "incomplete lifecycle captured");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "incomplete lifecycle chain blocked");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "incomplete lifecycle report writes");
    EXPECT_TRUE(strstr(report, "reason=kernel-lifecycle-blocked\n") != 0,
        "lifecycle blocked reason emitted");
    return 0;
}

static int runtime_register_view_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");
    register_view.register_views[0].register_save_allowed = 1;

    request = coupling_request(&plan, &registry, &lifecycle, &register_view,
        0, 0, 0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "runtime blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_REGISTER_VIEW_BLOCKED,
        "runtime blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "runtime no effect chain blocked");
    EXPECT_TRUE(result.record.register_save_allowed == 0,
        "coupling does not grant register save");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "blocked report writes");
    EXPECT_TRUE(strstr(report, "reason=runtime-register-view-blocked\n") != 0,
        "runtime blocked reason emitted");
    EXPECT_TRUE(strstr(report, "no_effect_chain_ok=0\n") != 0,
        "runtime blocked chain emitted");
    return 0;
}

static int missing_process_return_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");

    request = coupling_request(&plan, &registry, &lifecycle, &register_view,
        0, 0, 0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing process return observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_MISSING,
        "missing process return observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing process return observation os status");
    return 0;
}

static int process_return_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_process_return_observation_view_result_t
        process_return_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_process_return_observation_view(
            &process_return_view) == LATTICRA_STATUS_OK,
        "ready process return observation view");
    process_return_view.process_return_observation_views[0].
        process_return_allowed = 1;

    request = coupling_request(&plan, &registry, &lifecycle,
        &process_return_view.runtime_entry_scheduler_return_observation_view.
            runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.
            runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.
            runtime_entry_address_space_view.
            runtime_entry_stack_view.
            runtime_entry_register_view,
        &process_return_view, 0, 0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "process return observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PROCESS_RETURN_OBSERVATION_VIEW_BLOCKED,
        "process return observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "process return observation chain blocked");
    EXPECT_TRUE(result.record.process_return_allowed == 0,
        "coupling does not grant process return");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "process return blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-process-return-observation-view-blocked\n") != 0,
        "process return blocked reason emitted");
    return 0;
}

static int missing_idle_return_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_process_return_observation_view_result_t
        process_return_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_process_return_observation_view(
            &process_return_view) == LATTICRA_STATUS_OK,
        "ready process return observation view");

    request = coupling_request(&plan, &registry, &lifecycle,
        &process_return_view.runtime_entry_scheduler_return_observation_view.
            runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.
            runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.
            runtime_entry_address_space_view.
            runtime_entry_stack_view.
            runtime_entry_register_view,
        &process_return_view, 0, 0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing idle return observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_MISSING,
        "missing idle return observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing idle return observation os status");
    return 0;
}

static int idle_return_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        idle_return_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_idle_return_observation_view(&idle_return_view) ==
            LATTICRA_STATUS_OK,
        "ready idle return observation view");
    idle_return_view.idle_return_observation_views[0].idle_return_allowed = 1;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_idle_return_observation(&idle_return_view),
        &idle_return_view.runtime_entry_process_return_observation_view,
        &idle_return_view,
        0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "idle return observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_IDLE_RETURN_OBSERVATION_VIEW_BLOCKED,
        "idle return observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "idle return observation chain blocked");
    EXPECT_TRUE(result.record.idle_return_allowed == 0,
        "coupling does not grant idle return");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "idle return blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-idle-return-observation-view-blocked\n") != 0,
        "idle return blocked reason emitted");
    return 0;
}

static int missing_quiescent_return_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        idle_return_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_idle_return_observation_view(&idle_return_view) ==
            LATTICRA_STATUS_OK,
        "ready idle return observation view");

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_idle_return_observation(&idle_return_view),
        &idle_return_view.runtime_entry_process_return_observation_view,
        &idle_return_view,
        0);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing quiescent return observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_MISSING,
        "missing quiescent return observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing quiescent return observation os status");
    return 0;
}

static int quiescent_return_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        quiescent_return_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_quiescent_return_observation_view(
            &quiescent_return_view) == LATTICRA_STATUS_OK,
        "ready quiescent return observation view");
    quiescent_return_view.quiescent_return_observation_views[0].
        quiescent_return_allowed = 1;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_quiescent_return_observation(&quiescent_return_view),
        &quiescent_return_view.runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &quiescent_return_view.runtime_entry_idle_return_observation_view,
        &quiescent_return_view);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "quiescent return observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_QUIESCENT_RETURN_OBSERVATION_VIEW_BLOCKED,
        "quiescent return observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "quiescent return observation chain blocked");
    EXPECT_TRUE(result.record.quiescent_return_allowed == 0,
        "coupling does not grant quiescent return");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "quiescent return blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-quiescent-return-observation-view-blocked\n") != 0,
        "quiescent return blocked reason emitted");
    return 0;
}

static int missing_persistence_boundary_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        quiescent_return_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_quiescent_return_observation_view(
            &quiescent_return_view) == LATTICRA_STATUS_OK,
        "ready quiescent return observation view");

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_quiescent_return_observation(&quiescent_return_view),
        &quiescent_return_view.runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &quiescent_return_view.runtime_entry_idle_return_observation_view,
        &quiescent_return_view);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing persistence boundary observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_MISSING,
        "missing persistence boundary observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing persistence boundary observation os status");
    return 0;
}

static int persistence_boundary_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_persistence_boundary_observation_view(
            &persistence_boundary_view) == LATTICRA_STATUS_OK,
        "ready persistence boundary observation view");
    persistence_boundary_view.persistence_boundary_observation_views[0].
        persistence_commit_allowed = 1;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_persistence_boundary_observation(
            &persistence_boundary_view),
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        &persistence_boundary_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "persistence boundary observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_BLOCKED,
        "persistence boundary observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "persistence boundary observation chain blocked");
    EXPECT_TRUE(result.record.persistence_commit_allowed == 0,
        "coupling does not grant persistence commit");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "persistence boundary blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-persistence-boundary-observation-view-blocked\n") != 0,
        "persistence boundary blocked reason emitted");
    return 0;
}

static int missing_recovery_boundary_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_persistence_boundary_observation_view(
            &persistence_boundary_view) == LATTICRA_STATUS_OK,
        "ready persistence boundary observation view");

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_persistence_boundary_observation(
            &persistence_boundary_view),
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view.runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        &persistence_boundary_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing recovery boundary observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_MISSING,
        "missing recovery boundary observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing recovery boundary observation os status");
    return 0;
}

static int recovery_boundary_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_boundary_observation_view(
            &recovery_boundary_view) == LATTICRA_STATUS_OK,
        "ready recovery boundary observation view");
    recovery_boundary_view.recovery_boundary_observation_views[0].
        recovery_plan_allowed = 1;
    persistence_boundary_view =
        &recovery_boundary_view.runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_boundary_observation(
            &recovery_boundary_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        &recovery_boundary_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "recovery boundary observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_BOUNDARY_OBSERVATION_VIEW_BLOCKED,
        "recovery boundary observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "recovery boundary observation chain blocked");
    EXPECT_TRUE(result.record.recovery_plan_allowed == 0,
        "coupling does not grant recovery plan");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "recovery boundary blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-recovery-boundary-observation-view-blocked\n") != 0,
        "recovery boundary blocked reason emitted");
    return 0;
}

static int missing_recovery_plan_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_boundary_observation_view(
            &recovery_boundary_view) == LATTICRA_STATUS_OK,
        "ready recovery boundary observation view");
    persistence_boundary_view =
        &recovery_boundary_view.runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_boundary_observation(
            &recovery_boundary_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        &recovery_boundary_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing recovery plan observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_MISSING,
        "missing recovery plan observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing recovery plan observation os status");
    return 0;
}

static int recovery_plan_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_plan_observation_view(
            &recovery_plan_view) == LATTICRA_STATUS_OK,
        "ready recovery plan observation view");
    recovery_plan_view.recovery_plan_observation_views[0].
        recovery_plan_observation_allowed = 1;
    recovery_boundary_view =
        &recovery_plan_view.runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_plan_observation(
            &recovery_plan_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        &recovery_plan_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "recovery plan observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_PLAN_OBSERVATION_VIEW_BLOCKED,
        "recovery plan observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "recovery plan observation chain blocked");
    EXPECT_TRUE(result.record.recovery_plan_observation_allowed == 0,
        "coupling does not grant recovery plan observation");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "recovery plan blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-recovery-plan-observation-view-blocked\n") != 0,
        "recovery plan blocked reason emitted");
    return 0;
}

static int missing_recovery_outcome_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        recovery_disposition_view;
    const latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_disposition_observation_view(
            &recovery_disposition_view) == LATTICRA_STATUS_OK,
        "ready recovery disposition observation view");
    recovery_plan_view =
        &recovery_disposition_view.runtime_entry_recovery_plan_observation_view;
    recovery_boundary_view =
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_disposition_observation(
            &recovery_disposition_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        recovery_plan_view;
    request.runtime_recovery_disposition_observation_view =
        &recovery_disposition_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing recovery outcome observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_MISSING,
        "missing recovery outcome observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing recovery outcome observation os status");
    return 0;
}

static int recovery_outcome_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        recovery_outcome_view;
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view;
    const latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_outcome_observation_view(
            &recovery_outcome_view) == LATTICRA_STATUS_OK,
        "ready recovery outcome observation view");
    recovery_outcome_view.recovery_outcome_observation_views[0].
        recovery_outcome_allowed = 1;
    recovery_disposition_view =
        &recovery_outcome_view.runtime_entry_recovery_disposition_observation_view;
    recovery_plan_view =
        &recovery_disposition_view->runtime_entry_recovery_plan_observation_view;
    recovery_boundary_view =
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_outcome_observation(&recovery_outcome_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        recovery_plan_view;
    request.runtime_recovery_disposition_observation_view =
        recovery_disposition_view;
    request.runtime_recovery_outcome_observation_view =
        &recovery_outcome_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "recovery outcome observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_OUTCOME_OBSERVATION_VIEW_BLOCKED,
        "recovery outcome observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "recovery outcome observation chain blocked");
    EXPECT_TRUE(result.record.recovery_outcome_allowed == 0,
        "coupling does not grant recovery outcome");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "recovery outcome blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-recovery-outcome-observation-view-blocked\n") != 0,
        "recovery outcome blocked reason emitted");
    return 0;
}

static int missing_recovery_closeout_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        recovery_outcome_view;
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view;
    const latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_outcome_observation_view(
            &recovery_outcome_view) == LATTICRA_STATUS_OK,
        "ready recovery outcome observation view");
    recovery_disposition_view =
        &recovery_outcome_view.runtime_entry_recovery_disposition_observation_view;
    recovery_plan_view =
        &recovery_disposition_view->runtime_entry_recovery_plan_observation_view;
    recovery_boundary_view =
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_outcome_observation(&recovery_outcome_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        recovery_plan_view;
    request.runtime_recovery_disposition_observation_view =
        recovery_disposition_view;
    request.runtime_recovery_outcome_observation_view =
        &recovery_outcome_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing recovery closeout observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_MISSING,
        "missing recovery closeout observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing recovery closeout observation os status");
    return 0;
}

static int recovery_closeout_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        recovery_closeout_view;
    const latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *recovery_outcome_view;
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view;
    const latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_closeout_observation_view(
            &recovery_closeout_view) == LATTICRA_STATUS_OK,
        "ready recovery closeout observation view");
    recovery_closeout_view.recovery_closeout_observation_views[0].
        recovery_closeout_observation_allowed = 1;
    recovery_outcome_view =
        &recovery_closeout_view.runtime_entry_recovery_outcome_observation_view;
    recovery_disposition_view =
        &recovery_outcome_view->runtime_entry_recovery_disposition_observation_view;
    recovery_plan_view =
        &recovery_disposition_view->runtime_entry_recovery_plan_observation_view;
    recovery_boundary_view =
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_closeout_observation(
            &recovery_closeout_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        recovery_plan_view;
    request.runtime_recovery_disposition_observation_view =
        recovery_disposition_view;
    request.runtime_recovery_outcome_observation_view =
        recovery_outcome_view;
    request.runtime_recovery_closeout_observation_view =
        &recovery_closeout_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "recovery closeout observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_BLOCKED,
        "recovery closeout observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "recovery closeout observation chain blocked");
    EXPECT_TRUE(result.record.recovery_closeout_observation_allowed == 0,
        "coupling does not grant recovery closeout observation");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "recovery closeout blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-recovery-closeout-observation-view-blocked\n") != 0,
        "recovery closeout blocked reason emitted");
    return 0;
}

static int missing_recovery_audit_observation_blocks_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        recovery_closeout_view;
    const latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *recovery_outcome_view;
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view;
    const latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_closeout_observation_view(
            &recovery_closeout_view) == LATTICRA_STATUS_OK,
        "ready recovery closeout observation view");
    recovery_outcome_view =
        &recovery_closeout_view.runtime_entry_recovery_outcome_observation_view;
    recovery_disposition_view =
        &recovery_outcome_view->runtime_entry_recovery_disposition_observation_view;
    recovery_plan_view =
        &recovery_disposition_view->runtime_entry_recovery_plan_observation_view;
    recovery_boundary_view =
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_closeout_observation(
            &recovery_closeout_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        recovery_plan_view;
    request.runtime_recovery_disposition_observation_view =
        recovery_disposition_view;
    request.runtime_recovery_outcome_observation_view =
        recovery_outcome_view;
    request.runtime_recovery_closeout_observation_view =
        &recovery_closeout_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "missing recovery audit observation evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_MISSING,
        "missing recovery audit observation reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "missing recovery audit observation os status");
    return 0;
}

static int recovery_audit_observation_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_lifecycle_result_t lifecycle;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        recovery_audit_view;
    const latticra_kernel_runtime_entry_recovery_closeout_observation_view_result_t
        *recovery_closeout_view;
    const latticra_kernel_runtime_entry_recovery_outcome_observation_view_result_t
        *recovery_outcome_view;
    const
    latticra_kernel_runtime_entry_recovery_disposition_observation_view_result_t
        *recovery_disposition_view;
    const latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        *recovery_plan_view;
    const latticra_kernel_runtime_entry_recovery_boundary_observation_view_result_t
        *recovery_boundary_view;
    const latticra_kernel_runtime_entry_persistence_boundary_observation_view_result_t
        *persistence_boundary_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_lifecycle(&lifecycle) == LATTICRA_STATUS_OK,
        "ready lifecycle");
    EXPECT_TRUE(build_ready_recovery_audit_observation_view(
            &recovery_audit_view) == LATTICRA_STATUS_OK,
        "ready recovery audit observation view");
    recovery_audit_view.recovery_audit_observation_views[0].
        recovery_audit_observation_allowed = 1;
    recovery_closeout_view =
        &recovery_audit_view.runtime_entry_recovery_closeout_observation_view;
    recovery_outcome_view =
        &recovery_closeout_view->runtime_entry_recovery_outcome_observation_view;
    recovery_disposition_view =
        &recovery_outcome_view->runtime_entry_recovery_disposition_observation_view;
    recovery_plan_view =
        &recovery_disposition_view->runtime_entry_recovery_plan_observation_view;
    recovery_boundary_view =
        &recovery_plan_view->runtime_entry_recovery_boundary_observation_view;
    persistence_boundary_view =
        &recovery_boundary_view->runtime_entry_persistence_boundary_observation_view;

    request = coupling_request(&plan, &registry, &lifecycle,
        register_view_from_recovery_audit_observation(&recovery_audit_view),
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view,
        &persistence_boundary_view->runtime_entry_quiescent_return_observation_view);
    request.runtime_persistence_boundary_observation_view =
        persistence_boundary_view;
    request.runtime_recovery_boundary_observation_view =
        recovery_boundary_view;
    request.runtime_recovery_plan_observation_view =
        recovery_plan_view;
    request.runtime_recovery_disposition_observation_view =
        recovery_disposition_view;
    request.runtime_recovery_outcome_observation_view =
        recovery_outcome_view;
    request.runtime_recovery_closeout_observation_view =
        recovery_closeout_view;
    request.runtime_recovery_audit_observation_view =
        &recovery_audit_view;
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "recovery audit observation blocked evaluates");
    EXPECT_TRUE(result.record.denial ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_OBSERVATION_VIEW_BLOCKED,
        "recovery audit observation blocked reason");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "recovery audit observation chain blocked");
    EXPECT_TRUE(result.record.recovery_audit_observation_allowed == 0,
        "coupling does not grant recovery audit observation");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "recovery audit blocked report writes");
    EXPECT_TRUE(strstr(report,
            "reason=runtime-recovery-audit-observation-view-blocked\n") != 0,
        "recovery audit blocked reason emitted");
    return 0;
}

static int expect_tail_denial(
    const latticra_nucleus_kernel_coupling_request_t *request,
    latticra_nucleus_kernel_coupling_denial_t expected_denial,
    const char *expected_reason) {
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(request, &result) ==
            LATTICRA_STATUS_OK,
        "tail denial evaluates");
    EXPECT_TRUE(result.record.denial == expected_denial,
        "tail denial reason");
    EXPECT_STR_EQ(result.record.os_readiness_status, "os-metadata-blocked",
        "tail os status");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 0,
        "tail no-effect chain blocked");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "tail denial report writes");
    EXPECT_TRUE(strstr(report, expected_reason) != 0,
        "tail denial reason emitted");
    return 0;
}

static void clear_after_recovery_disposition(recovery_tail_fixture_t *fixture) {
    fixture->request.runtime_recovery_outcome_observation_view = 0;
    fixture->request.runtime_recovery_closeout_observation_view = 0;
    fixture->request.runtime_recovery_audit_observation_view = 0;
    fixture->request.runtime_recovery_audit_review_observation_view = 0;
    fixture->request.runtime_recovery_audit_review_disposition_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_observation_view = 0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        0;
}

static void clear_after_recovery_audit(recovery_tail_fixture_t *fixture) {
    fixture->request.runtime_recovery_audit_review_observation_view = 0;
    fixture->request.runtime_recovery_audit_review_disposition_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_observation_view = 0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        0;
}

static void clear_after_recovery_audit_review(
    recovery_tail_fixture_t *fixture) {
    fixture->request.runtime_recovery_audit_review_disposition_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_observation_view = 0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        0;
    fixture->request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        0;
}

static int missing_recovery_disposition_observation_blocks_coupling(void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.request.runtime_recovery_disposition_observation_view = 0;
    clear_after_recovery_disposition(&fixture);
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_MISSING,
        "reason=runtime-recovery-disposition-observation-view-missing\n");
}

static int recovery_disposition_observation_effect_flags_block_coupling(void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.recovery_disposition_view->recovery_disposition_observation_allowed =
        1;
    clear_after_recovery_disposition(&fixture);
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_DISPOSITION_OBSERVATION_VIEW_BLOCKED,
        "reason=runtime-recovery-disposition-observation-view-blocked\n");
}

static int missing_recovery_audit_review_observation_blocks_coupling(void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    clear_after_recovery_audit(&fixture);
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_OBSERVATION_VIEW_MISSING,
        "reason=runtime-recovery-audit-review-observation-view-missing\n");
}

static int recovery_audit_review_observation_effect_flags_block_coupling(void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.recovery_audit_review_view->recovery_audit_review_observation_allowed =
        1;
    clear_after_recovery_audit(&fixture);
    fixture.request.runtime_recovery_audit_review_observation_view =
        fixture.recovery_audit_review_view;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_OBSERVATION_VIEW_BLOCKED,
        "reason=runtime-recovery-audit-review-observation-view-blocked\n");
}

static int
missing_recovery_audit_review_disposition_observation_blocks_coupling(void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    clear_after_recovery_audit_review(&fixture);
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_MISSING,
        "reason=runtime-recovery-audit-review-disposition-observation-view-missing\n");
}

static int
recovery_audit_review_disposition_observation_effect_flags_block_coupling(void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.recovery_audit_review_disposition_view->
        recovery_audit_review_disposition_observation_allowed = 1;
    clear_after_recovery_audit_review(&fixture);
    fixture.request.runtime_recovery_audit_review_disposition_observation_view =
        fixture.recovery_audit_review_disposition_view;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_BLOCKED,
        "reason=runtime-recovery-audit-review-disposition-observation-view-blocked\n");
}

static int
missing_recovery_audit_review_disposition_review_observation_blocks_coupling(
    void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.request.
        runtime_recovery_audit_review_disposition_review_observation_view = 0;
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_observation_view =
        0;
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        0;
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        0;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_OBSERVATION_VIEW_MISSING,
        "reason=runtime-recovery-audit-review-disposition-review-observation-view-missing\n");
}

static int
recovery_audit_review_disposition_review_observation_effect_flags_block_coupling(
    void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.recovery_audit_review_disposition_review_view.
        recovery_audit_review_disposition_review_observation_allowed = 1;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_OBSERVATION_VIEW_BLOCKED,
        "reason=runtime-recovery-audit-review-disposition-review-observation-view-blocked\n");
}

static int
missing_recovery_audit_review_disposition_review_closeout_observation_blocks_coupling(
    void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_observation_view =
        0;
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        0;
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        0;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_OBSERVATION_VIEW_MISSING,
        "reason=runtime-recovery-audit-review-disposition-review-closeout-observation-view-missing\n");
}

static int
recovery_audit_review_disposition_review_closeout_observation_effect_flags_block_coupling(
    void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.recovery_audit_review_disposition_review_closeout_view.
        recovery_audit_review_disposition_review_closeout_observation_allowed = 1;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_OBSERVATION_VIEW_BLOCKED,
        "reason=runtime-recovery-audit-review-disposition-review-closeout-observation-view-blocked\n");
}

static int
missing_recovery_audit_review_disposition_review_closeout_archive_gate_observation_blocks_coupling(
    void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view =
        0;
    fixture.request.
        runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view =
        0;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_MISSING,
        "reason=runtime-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-missing\n");
}

static int
recovery_audit_review_disposition_review_closeout_archive_gate_observation_effect_flags_block_coupling(
    void) {
    recovery_tail_fixture_t fixture;

    EXPECT_TRUE(build_ready_recovery_tail_fixture(&fixture) == 0,
        "ready tail fixture");
    fixture.recovery_audit_review_disposition_review_closeout_archive_gate_view.
        recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed = 1;
    return expect_tail_denial(&fixture.request,
        LATTICRA_NUCLEUS_KERNEL_COUPLING_DENIAL_RUNTIME_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_BLOCKED,
        "reason=runtime-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-blocked\n");
}

static int null_guards_are_safe(void) {
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char tiny[8];

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_default_nucleus_plan(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default nucleus plan");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate_default(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default evaluator");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request ok");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(result.record.classification ==
            LATTICRA_NUCLEUS_KERNEL_COUPLING_INVALID,
        "null evaluate invalid");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, 0,
            sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, tiny,
            sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "tiny report cleared");
    return 0;
}

int main(void) {
    if (ready_evidence_produces_os_metadata_ready_report() != 0) return 1;
    if (default_evaluator_builds_ready_coupling() != 0) return 1;
    if (process_return_lifecycle_blocks_idle_return_coupling() != 0) return 1;
    if (missing_nucleus_plan_blocks_coupling() != 0) return 1;
    if (future_gated_plan_blocks_coupling() != 0) return 1;
    if (kernel_registry_effect_flags_block_coupling() != 0) return 1;
    if (missing_lifecycle_blocks_coupling() != 0) return 1;
    if (incomplete_lifecycle_blocks_coupling() != 0) return 1;
    if (runtime_register_view_effect_flags_block_coupling() != 0) return 1;
    if (missing_process_return_observation_blocks_coupling() != 0) return 1;
    if (process_return_observation_effect_flags_block_coupling() != 0) return 1;
    if (missing_idle_return_observation_blocks_coupling() != 0) return 1;
    if (idle_return_observation_effect_flags_block_coupling() != 0) return 1;
    if (missing_quiescent_return_observation_blocks_coupling() != 0) return 1;
    if (quiescent_return_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_persistence_boundary_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (persistence_boundary_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_boundary_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (recovery_boundary_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_plan_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (recovery_plan_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_disposition_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (recovery_disposition_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_outcome_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (recovery_outcome_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_closeout_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (recovery_closeout_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_audit_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (recovery_audit_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_audit_review_observation_blocks_coupling() != 0) {
        return 1;
    }
    if (recovery_audit_review_observation_effect_flags_block_coupling() != 0) {
        return 1;
    }
    if (missing_recovery_audit_review_disposition_observation_blocks_coupling() !=
            0) {
        return 1;
    }
    if (recovery_audit_review_disposition_observation_effect_flags_block_coupling() !=
            0) {
        return 1;
    }
    if (missing_recovery_audit_review_disposition_review_observation_blocks_coupling() !=
            0) {
        return 1;
    }
    if (recovery_audit_review_disposition_review_observation_effect_flags_block_coupling() !=
            0) {
        return 1;
    }
    if (missing_recovery_audit_review_disposition_review_closeout_observation_blocks_coupling() !=
            0) {
        return 1;
    }
    if (recovery_audit_review_disposition_review_closeout_observation_effect_flags_block_coupling() !=
            0) {
        return 1;
    }
    if (missing_recovery_audit_review_disposition_review_closeout_archive_gate_observation_blocks_coupling() !=
            0) {
        return 1;
    }
    if (recovery_audit_review_disposition_review_closeout_archive_gate_observation_effect_flags_block_coupling() !=
            0) {
        return 1;
    }
    if (null_guards_are_safe() != 0) return 1;

    puts("nucleus_kernel_coupling: ok");
    return 0;
}
