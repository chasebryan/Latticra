#include "latticra/latticra_console.h"

#include <stdio.h>
#include <string.h>

static void lc_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static latticra_l_ui_source_span_t lc_default_span(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 0u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 1u;
    return span;
}

const char *latticra_console_profile_label(latticra_console_profile_t profile) {
    switch (profile) {
        case LATTICRA_CONSOLE_PROFILE_HOSTED_REFERENCE:
            return "hosted-reference";
        case LATTICRA_CONSOLE_PROFILE_PANEL_EMBEDDED:
            return "panel-embedded";
        case LATTICRA_CONSOLE_PROFILE_HOST_EMBEDDED:
            return "host-embedded-planning";
        case LATTICRA_CONSOLE_PROFILE_OS_BASE_PLANNING:
            return "os-base-planning";
        default:
            return "unknown";
    }
}

latticra_status_t latticra_console_default_request(
    latticra_console_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    memset(request, 0, sizeof(*request));
    lc_copy(request->console_id, sizeof(request->console_id), "latticra-console");
    request->profile = LATTICRA_CONSOLE_PROFILE_PANEL_EMBEDDED;
    request->panel_installable = 1;
    request->host_embeddable = 1;
    request->source_identity = "latticra-console-default";
    request->source_identity_len = strlen("latticra-console-default");
    request->source_span = lc_default_span();
    return LATTICRA_STATUS_OK;
}

static void lc_seed_result(
    const latticra_console_request_t *request,
    latticra_console_result_t *result) {
    size_t n;

    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    lc_copy(result->console_name, sizeof(result->console_name), "Latticra Console");
    lc_copy(result->short_name, sizeof(result->short_name), "LC");
    lc_copy(result->component_key, sizeof(result->component_key), "latticra_console");
    lc_copy(result->console_status, sizeof(result->console_status), "initializing");
    lc_copy(result->command_registry_status, sizeof(result->command_registry_status), "seed-registry");
    lc_copy(result->substrate_bridge_status, sizeof(result->substrate_bridge_status), "metadata-bound");
    lc_copy(result->panel_install_status, sizeof(result->panel_install_status), "panel-installable");
    lc_copy(result->host_embedding_status, sizeof(result->host_embedding_status), "planned");
    lc_copy(result->os_base_status, sizeof(result->os_base_status), "planned-no-boot-authority");
    result->source_span = lc_default_span();
    result->no_effect = 1;
    result->configurable = 1;
    result->panel_installable = 1;
    result->command_registry_present = 1;
    result->substrate_bridge_present = 1;
    result->host_embeddable = 1;
    result->host_embedded_now = 0;
    result->operator_shell_present = 1;
    result->command_count = 12u;
    result->evidence_level = 4u;

    if (request == 0) return;

    lc_copy(result->console_id, sizeof(result->console_id), request->console_id);
    lc_copy(result->profile_label, sizeof(result->profile_label),
        latticra_console_profile_label(request->profile));
    result->panel_installable = request->panel_installable ? 1 : 0;
    result->host_embeddable = request->host_embeddable ? 1 : 0;
    if (request->source_identity != 0 && request->source_identity_len > 0u) {
        n = request->source_identity_len;
        if (n >= sizeof(result->source_identity)) n = sizeof(result->source_identity) - 1u;
        memcpy(result->source_identity, request->source_identity, n);
        result->source_identity[n] = '\0';
    }
    result->source_span = request->source_span;
}

static latticra_status_t lc_run_kernel(
    const latticra_console_request_t *request,
    latticra_console_result_t *result) {
    latticra_kernel_request_t kernel_request;
    latticra_status_t status;

    status = latticra_kernel_default_request(&kernel_request);
    if (status != LATTICRA_STATUS_OK) return status;

    lc_copy(kernel_request.kernel_id, sizeof(kernel_request.kernel_id), "latticra-console-kernel");
    kernel_request.source_identity = request->source_identity;
    kernel_request.source_identity_len = request->source_identity_len;
    kernel_request.source_span = request->source_span;

    return latticra_kernel_initialize(&kernel_request, &result->kernel);
}

static void lc_finalize(latticra_console_result_t *result) {
    result->execution_allowed = 0;
    result->host_mutation_allowed = 0;
    result->file_io_allowed = 0;
    result->network_allowed = 0;
    result->runtime_enforcement_allowed = 0;
    result->boot_allowed = 0;

    if (result->kernel.status != LATTICRA_STATUS_OK || result->kernel.no_effect != 1) {
        result->status = result->kernel.status;
        result->no_effect = 0;
        lc_copy(result->console_status, sizeof(result->console_status), "kernel-not-ready");
        return;
    }

    result->no_effect = 1;
    lc_copy(result->console_status, sizeof(result->console_status), "ready-report-only");
    lc_copy(result->command_registry_status, sizeof(result->command_registry_status), "seed-registry-ready");
    lc_copy(result->substrate_bridge_status, sizeof(result->substrate_bridge_status), "metadata-bound-ready");
    lc_copy(result->panel_install_status, sizeof(result->panel_install_status),
        result->panel_installable ? "panel-installable" : "panel-disabled");
}

latticra_status_t latticra_console_initialize(
    const latticra_console_request_t *request,
    latticra_console_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    lc_seed_result(request, result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        lc_copy(result->console_status, sizeof(result->console_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = lc_run_kernel(request, result);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        lc_copy(result->console_status, sizeof(result->console_status), "kernel-failed");
        return status;
    }

    lc_finalize(result);
    return result->status;
}

latticra_status_t latticra_console_report(
    const latticra_console_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    written = snprintf(buffer, buffer_len,
        "LATTICRA CONSOLE REPORT\n"
        "console_id=%s\n"
        "console_name=%s\n"
        "short_name=%s\n"
        "component_key=%s\n"
        "profile=%s\n"
        "console_status=%s\n"
        "command_registry_status=%s\n"
        "substrate_bridge_status=%s\n"
        "panel_install_status=%s\n"
        "host_embedding_status=%s\n"
        "os_base_status=%s\n"
        "configurable=%d\n"
        "panel_installable=%d\n"
        "command_registry_present=%d\n"
        "substrate_bridge_present=%d\n"
        "operator_shell_present=%d\n"
        "host_embeddable=%d\n"
        "host_embedded_now=%d\n"
        "command_count=%u\n"
        "kernel_status=%s\n"
        "kernel_runtime_status=%s\n"
        "kernel_boot_status=%s\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "host_mutation_allowed=%d\n"
        "file_io_allowed=%d\n"
        "network_allowed=%d\n"
        "runtime_enforcement_allowed=%d\n"
        "boot_allowed=%d\n"
        "future_os_base_claim=planned_not_claimed\n"
        "phase1_reference_lessons=registry_help_guarded_boundary_os_track\n"
        "evidence_level=%u\n"
        "source_identity=%s\n",
        result->console_id,
        result->console_name,
        result->short_name,
        result->component_key,
        result->profile_label,
        result->console_status,
        result->command_registry_status,
        result->substrate_bridge_status,
        result->panel_install_status,
        result->host_embedding_status,
        result->os_base_status,
        result->configurable,
        result->panel_installable,
        result->command_registry_present,
        result->substrate_bridge_present,
        result->operator_shell_present,
        result->host_embeddable,
        result->host_embedded_now,
        result->command_count,
        result->kernel.kernel_status,
        result->kernel.runtime_status,
        result->kernel.boot_status,
        result->no_effect,
        result->execution_allowed,
        result->host_mutation_allowed,
        result->file_io_allowed,
        result->network_allowed,
        result->runtime_enforcement_allowed,
        result->boot_allowed,
        result->evidence_level,
        result->source_identity);

    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
