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

static latticra_nucleus_kernel_coupling_request_t coupling_request(
    const latticra_nucleus_task_plan_result_t *plan,
    const latticra_kernel_subsystem_registry_result_t *registry,
    const latticra_kernel_runtime_entry_register_view_result_t *register_view) {
    latticra_nucleus_kernel_coupling_request_t request;
    (void)latticra_nucleus_kernel_coupling_default_request(&request);
    request.nucleus_plan = plan;
    request.kernel_registry = registry;
    request.runtime_register_view = register_view;
    request.source_identity = "coupling-test";
    request.source_identity_len = strlen("coupling-test");
    request.source_span = span_ok();
    return request;
}

static int ready_evidence_produces_os_metadata_ready_report(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");

    request = coupling_request(&plan, &registry, &register_view);
    EXPECT_TRUE(latticra_nucleus_kernel_coupling_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "coupling evaluates");
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
    EXPECT_STR_EQ(result.record.runtime_register_view_status,
        "runtime-entry-register-view-seed-ready", "runtime register status");
    EXPECT_TRUE(result.record.task_count == 1u, "task count");
    EXPECT_TRUE(result.record.accepted_task_count == 1u, "accepted task count");
    EXPECT_TRUE(result.record.subsystem_count == LATTICRA_KERNEL_SUBSYSTEM_COUNT,
        "subsystem count");
    EXPECT_TRUE(result.record.register_view_count == 4u, "register view count");
    EXPECT_TRUE(result.record.prerequisites_satisfied == 1, "prereq ok");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 1, "no effect chain");
    EXPECT_TRUE(result.record.no_effect == 1, "no effect");
    EXPECT_TRUE(result.record.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(result.record.boot_allowed == 0, "boot denied");
    EXPECT_TRUE(result.record.runtime_entry_allowed == 0, "runtime entry denied");
    EXPECT_TRUE(result.record.scheduler_run_entry_allowed == 0,
        "scheduler run entry denied");
    EXPECT_TRUE(result.record.register_save_allowed == 0, "register save denied");
    EXPECT_TRUE(result.record.register_restore_allowed == 0,
        "register restore denied");
    EXPECT_TRUE(result.record.evidence_level == 30u, "evidence level");

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
    EXPECT_TRUE(strstr(report, "runtime_entry_allowed=0\n") != 0,
        "runtime entry flag emitted");
    EXPECT_TRUE(strstr(report, "register_save_allowed=0\n") != 0,
        "register save flag emitted");
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
    EXPECT_TRUE(result.record.register_view_count == 4u,
        "default register view count");
    EXPECT_TRUE(result.record.runtime_entry_allowed == 0,
        "default runtime entry denied");
    EXPECT_TRUE(result.record.boot_allowed == 0, "default boot denied");
    EXPECT_TRUE(result.record.host_effect_allowed == 0,
        "default host effect denied");

    EXPECT_TRUE(latticra_nucleus_kernel_coupling_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "default report writes");
    EXPECT_TRUE(strstr(report, "classification=report-only-ready\n") != 0,
        "default classification emitted");
    EXPECT_TRUE(strstr(report, "source_identity=nucleus-kernel-coupling-default\n") != 0,
        "default source identity emitted");
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
    request = coupling_request(&plan, &registry, &register_view);

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

    request = coupling_request(&plan, &registry, &register_view);
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

static int runtime_register_view_effect_flags_block_coupling(void) {
    latticra_nucleus_task_plan_result_t plan;
    latticra_kernel_subsystem_registry_result_t registry;
    latticra_kernel_runtime_entry_register_view_result_t register_view;
    latticra_nucleus_kernel_coupling_request_t request;
    latticra_nucleus_kernel_coupling_result_t result;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    EXPECT_TRUE(build_ready_plan(&plan) == LATTICRA_STATUS_OK, "ready plan");
    EXPECT_TRUE(build_ready_registry(&registry) == LATTICRA_STATUS_OK,
        "ready registry");
    EXPECT_TRUE(build_ready_register_view(&register_view) == LATTICRA_STATUS_OK,
        "ready register view");
    register_view.register_views[0].register_save_allowed = 1;

    request = coupling_request(&plan, &registry, &register_view);
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
    if (missing_nucleus_plan_blocks_coupling() != 0) return 1;
    if (future_gated_plan_blocks_coupling() != 0) return 1;
    if (kernel_registry_effect_flags_block_coupling() != 0) return 1;
    if (runtime_register_view_effect_flags_block_coupling() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("nucleus_kernel_coupling: ok");
    return 0;
}
