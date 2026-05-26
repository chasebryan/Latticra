#include "latticra/kernel.h"

#include <stdio.h>
#include <string.h>

static void kernel_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static latticra_l_ui_source_span_t kernel_default_span(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 0u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 1u;
    return span;
}

static void kernel_seed_result(
    const latticra_kernel_request_t *request,
    latticra_kernel_result_t *result) {
    size_t n;

    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    kernel_copy(result->kernel_mode, sizeof(result->kernel_mode), "seed-kernel");
    kernel_copy(result->kernel_status, sizeof(result->kernel_status), "initializing");
    kernel_copy(result->boot_status, sizeof(result->boot_status), "not-booted");
    kernel_copy(result->runtime_status, sizeof(result->runtime_status), "not-entered");
    kernel_copy(result->scheduler_status, sizeof(result->scheduler_status), "not-started");
    kernel_copy(result->memory_status, sizeof(result->memory_status), "metadata-only");
    kernel_copy(result->process_status, sizeof(result->process_status), "not-started");
    kernel_copy(result->filesystem_status, sizeof(result->filesystem_status), "disabled");
    kernel_copy(result->network_status, sizeof(result->network_status), "disabled");
    kernel_copy(result->device_status, sizeof(result->device_status), "disabled");
    kernel_copy(result->security_status, sizeof(result->security_status), "not-production-boundary");
    result->source_span = kernel_default_span();
    result->no_effect = 1;
    result->evidence_level = 4u;

    if (request == 0) return;

    kernel_copy(result->kernel_id, sizeof(result->kernel_id), request->kernel_id);
    if (request->source_identity != 0 && request->source_identity_len > 0u) {
        n = request->source_identity_len;
        if (n >= sizeof(result->source_identity)) n = sizeof(result->source_identity) - 1u;
        memcpy(result->source_identity, request->source_identity, n);
        result->source_identity[n] = '\0';
    }
    result->source_span = request->source_span;
}

latticra_status_t latticra_kernel_default_request(
    latticra_kernel_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    memset(request, 0, sizeof(*request));
    kernel_copy(request->kernel_id, sizeof(request->kernel_id), "latticra-kernel-seed");
    request->source_identity = "kernel-default";
    request->source_identity_len = strlen("kernel-default");
    request->source_span = kernel_default_span();
    return LATTICRA_STATUS_OK;
}

static latticra_status_t kernel_run_bootstrap(
    const latticra_kernel_request_t *request,
    latticra_kernel_result_t *result) {
    latticra_system_bootstrap_request_t bootstrap_request;
    latticra_status_t status;

    status = latticra_system_bootstrap_default_request(&bootstrap_request);
    if (status != LATTICRA_STATUS_OK) return status;

    bootstrap_request.source_identity = request->source_identity;
    bootstrap_request.source_identity_len = request->source_identity_len;
    bootstrap_request.source_span = request->source_span;

    return latticra_system_bootstrap_run(&bootstrap_request, &result->bootstrap);
}

static void kernel_finalize(latticra_kernel_result_t *result) {
    result->execution_allowed = result->bootstrap.execution_allowed;
    result->mutation_allowed = result->bootstrap.mutation_allowed;
    result->file_io_allowed = result->bootstrap.file_io_allowed;
    result->network_allowed = result->bootstrap.network_allowed;
    result->server_allowed = result->bootstrap.server_allowed;
    result->recovery_allowed = result->bootstrap.recovery_allowed;
    result->hardware_allowed = result->bootstrap.hardware_allowed;
    result->boot_allowed = 0;

    if (result->bootstrap.status != LATTICRA_STATUS_OK || result->bootstrap.no_effect != 1 ||
        result->execution_allowed != 0 || result->mutation_allowed != 0 ||
        result->file_io_allowed != 0 || result->network_allowed != 0 ||
        result->server_allowed != 0 || result->recovery_allowed != 0 ||
        result->hardware_allowed != 0) {
        result->status = result->bootstrap.status;
        kernel_copy(result->kernel_status, sizeof(result->kernel_status), "bootstrap-not-ready");
        result->no_effect = 0;
        return;
    }

    result->no_effect = 1;
    kernel_copy(result->kernel_status, sizeof(result->kernel_status), "initialized-report-only");
    kernel_copy(result->boot_status, sizeof(result->boot_status), "not-booted");
    kernel_copy(result->runtime_status, sizeof(result->runtime_status), "not-entered");
    kernel_copy(result->scheduler_status, sizeof(result->scheduler_status), "not-started");
    kernel_copy(result->memory_status, sizeof(result->memory_status), "metadata-only");
    kernel_copy(result->process_status, sizeof(result->process_status), "not-started");
    kernel_copy(result->filesystem_status, sizeof(result->filesystem_status), "disabled");
    kernel_copy(result->network_status, sizeof(result->network_status), "disabled");
    kernel_copy(result->device_status, sizeof(result->device_status), "disabled");
    kernel_copy(result->security_status, sizeof(result->security_status), "not-production-boundary");
}

latticra_status_t latticra_kernel_initialize(
    const latticra_kernel_request_t *request,
    latticra_kernel_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    kernel_seed_result(request, result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        kernel_copy(result->kernel_status, sizeof(result->kernel_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = kernel_run_bootstrap(request, result);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        kernel_copy(result->kernel_status, sizeof(result->kernel_status), "bootstrap-failed");
        return status;
    }

    kernel_finalize(result);
    return result->status;
}

latticra_status_t latticra_kernel_report(
    const latticra_kernel_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    written = snprintf(buffer, buffer_len,
        "LATTICRA KERNEL REPORT\n"
        "kernel_id=%s\n"
        "kernel_mode=%s\n"
        "kernel_status=%s\n"
        "boot_status=%s\n"
        "runtime_status=%s\n"
        "scheduler_status=%s\n"
        "memory_status=%s\n"
        "process_status=%s\n"
        "filesystem_status=%s\n"
        "network_status=%s\n"
        "device_status=%s\n"
        "security_status=%s\n"
        "bootstrap_status=%s\n"
        "bootstrap_runtime_entry_status=%s\n"
        "bootstrap_no_effect=%d\n"
        "bootstrap_network_allowed=%d\n"
        "bootstrap_server_allowed=%d\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "file_io_allowed=%d\n"
        "network_allowed=%d\n"
        "server_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n"
        "boot_allowed=%d\n"
        "evidence_level=%u\n"
        "source_identity=%s\n",
        result->kernel_id,
        result->kernel_mode,
        result->kernel_status,
        result->boot_status,
        result->runtime_status,
        result->scheduler_status,
        result->memory_status,
        result->process_status,
        result->filesystem_status,
        result->network_status,
        result->device_status,
        result->security_status,
        result->bootstrap.system_status,
        result->bootstrap.runtime_entry_status,
        result->bootstrap.no_effect,
        result->bootstrap.network_allowed,
        result->bootstrap.server_allowed,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->file_io_allowed,
        result->network_allowed,
        result->server_allowed,
        result->recovery_allowed,
        result->hardware_allowed,
        result->boot_allowed,
        result->evidence_level,
        result->source_identity);

    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
