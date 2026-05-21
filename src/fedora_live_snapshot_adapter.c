#define _POSIX_C_SOURCE 200809L

#include "latticra/fedora_live_snapshot_adapter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void latticra_live_copy_slice(
    char *dest,
    size_t dest_len,
    const char *source,
    size_t source_len)
{
    size_t copy_len;

    if (dest == NULL || dest_len == 0u) {
        return;
    }

    if (source == NULL) {
        dest[0] = '\0';
        return;
    }

    copy_len = source_len;
    if (copy_len >= dest_len) {
        copy_len = dest_len - 1u;
    }

    if (copy_len > 0u) {
        memcpy(dest, source, copy_len);
    }
    dest[copy_len] = '\0';
}

static void latticra_live_copy_cstr(
    char *dest,
    size_t dest_len,
    const char *source)
{
    if (source == NULL) {
        latticra_live_copy_slice(dest, dest_len, "", 0u);
        return;
    }
    latticra_live_copy_slice(dest, dest_len, source, strlen(source));
}

static int latticra_live_read_text_file(
    const char *path,
    char *buffer,
    size_t buffer_len,
    size_t *text_len)
{
    FILE *file;
    size_t read_len;

    if (buffer == NULL || buffer_len == 0u || text_len == NULL) {
        return 0;
    }

    buffer[0] = '\0';
    *text_len = 0u;

    if (path == NULL || path[0] == '\0') {
        return 0;
    }

    file = fopen(path, "rb");
    if (file == NULL) {
        return 0;
    }

    read_len = fread(buffer, 1u, buffer_len - 1u, file);
    buffer[read_len] = '\0';
    *text_len = read_len;

    if (ferror(file)) {
        fclose(file);
        buffer[0] = '\0';
        *text_len = 0u;
        return 0;
    }

    fclose(file);
    return 1;
}

static int latticra_live_path_readable(const char *path)
{
    if (path == NULL || path[0] == '\0') {
        return 0;
    }
    return access(path, R_OK) == 0 ? 1 : 0;
}

static int latticra_live_path_exists(const char *path)
{
    if (path == NULL || path[0] == '\0') {
        return 0;
    }
    return access(path, F_OK) == 0 ? 1 : 0;
}

static int latticra_live_command_present(const char *command)
{
    const char *path_env;
    const char *segment_start;
    const char *segment_end;
    size_t command_len;
    char candidate[LATTICRA_FEDORA_LIVE_ADAPTER_PATH_MAX];

    if (command == NULL || command[0] == '\0') {
        return 0;
    }

    path_env = getenv("PATH");
    if (path_env == NULL || path_env[0] == '\0') {
        return 0;
    }

    command_len = strlen(command);
    segment_start = path_env;

    while (*segment_start != '\0') {
        size_t segment_len;
        size_t needed_len;

        segment_end = segment_start;
        while (*segment_end != '\0' && *segment_end != ':') {
            ++segment_end;
        }

        segment_len = (size_t)(segment_end - segment_start);
        needed_len = segment_len + 1u + command_len;

        if (segment_len > 0u && needed_len < sizeof(candidate)) {
            memcpy(candidate, segment_start, segment_len);
            candidate[segment_len] = '/';
            memcpy(candidate + segment_len + 1u, command, command_len);
            candidate[needed_len] = '\0';
            if (access(candidate, X_OK) == 0) {
                return 1;
            }
        }

        if (*segment_end == '\0') {
            break;
        }
        segment_start = segment_end + 1;
    }

    return 0;
}

const char *latticra_fedora_live_snapshot_adapter_status_label(
    latticra_fedora_live_adapter_status_t status)
{
    switch (status) {
    case LATTICRA_FEDORA_LIVE_ADAPTER_CAPTURED:
        return "captured";
    case LATTICRA_FEDORA_LIVE_ADAPTER_PARTIAL:
        return "partial";
    case LATTICRA_FEDORA_LIVE_ADAPTER_INVALID:
        return "invalid";
    default:
        return "unknown";
    }
}

latticra_status_t latticra_fedora_live_snapshot_adapter_capture(
    const latticra_fedora_live_snapshot_adapter_request_t *request,
    latticra_fedora_live_snapshot_adapter_result_t *result)
{
    const char *default_os_release_path = "/etc/os-release";
    latticra_status_t status;

    if (request == NULL || result == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(result, 0, sizeof(*result));

    result->no_effect = 1;
    result->sudo_validation_allowed = 0;
    result->install_command_allowed = 0;
    result->package_build_allowed = 0;
    result->network_allowed = 0;
    result->host_mutation_performed = 0;
    result->host_install_performed = 0;
    result->live_probe_performed = 1;
    result->os_release_read_attempted = 1;
    result->command_probe_performed = 1;
    result->local_rpm_probe_performed = 1;
    result->ostree_marker_probe_performed = 1;
    result->id_probe_performed = 1;
    result->evidence_level = 3u;

    if (request->os_release_path != NULL && request->os_release_path_len > 0u) {
        latticra_live_copy_slice(
            result->os_release_path,
            sizeof(result->os_release_path),
            request->os_release_path,
            request->os_release_path_len);
    } else {
        latticra_live_copy_cstr(
            result->os_release_path,
            sizeof(result->os_release_path),
            default_os_release_path);
    }

    latticra_live_copy_slice(
        result->local_rpm_path,
        sizeof(result->local_rpm_path),
        request->local_rpm_path,
        request->local_rpm_path_len);

    result->os_release_readable = latticra_live_read_text_file(
        result->os_release_path,
        result->os_release_text,
        sizeof(result->os_release_text),
        &result->os_release_text_len);

    result->rpm_command_present = latticra_live_command_present("rpm");
    result->dnf_command_present = latticra_live_command_present("dnf");
    result->rpmbuild_command_present = latticra_live_command_present("rpmbuild");
    result->rpmlint_command_present = latticra_live_command_present("rpmlint");
    result->ostree_booted_marker_present = latticra_live_path_exists("/run/ostree-booted");
    result->local_rpm_readable = latticra_live_path_readable(result->local_rpm_path);
    result->running_as_root = getuid() == 0u ? 1 : 0;

    result->adapter_status = result->os_release_readable ?
        LATTICRA_FEDORA_LIVE_ADAPTER_CAPTURED :
        LATTICRA_FEDORA_LIVE_ADAPTER_PARTIAL;
    latticra_live_copy_cstr(
        result->adapter_status_label,
        sizeof(result->adapter_status_label),
        latticra_fedora_live_snapshot_adapter_status_label(result->adapter_status));

    result->capture_input.os_release_text = result->os_release_text;
    result->capture_input.os_release_text_len = result->os_release_text_len;
    result->capture_input.os_release_readable = result->os_release_readable;
    result->capture_input.host_install_requested = request->host_install_requested ? 1 : 0;
    result->capture_input.ostree_booted_marker_present = result->ostree_booted_marker_present;
    result->capture_input.rpm_command_present = result->rpm_command_present;
    result->capture_input.dnf_command_present = result->dnf_command_present;
    result->capture_input.rpmbuild_command_present = result->rpmbuild_command_present;
    result->capture_input.rpmlint_command_present = result->rpmlint_command_present;
    result->capture_input.local_rpm_path = result->local_rpm_path;
    result->capture_input.local_rpm_path_len = strlen(result->local_rpm_path);
    result->capture_input.local_rpm_readable = result->local_rpm_readable;
    result->capture_input.running_as_root = result->running_as_root;
    result->capture_input.operator_privilege_assertion =
        request->operator_privilege_assertion ? 1 : 0;
    result->capture_input.network_required = request->network_required ? 1 : 0;
    result->capture_input.package_is_doc_only = request->package_is_doc_only ? 1 : 0;
    result->capture_input.command_entrypoint_expected =
        request->command_entrypoint_expected ? 1 : 0;

    status = latticra_fedora_install_preflight_snapshot_capture(
        &result->capture_input,
        &result->capture);
    if (status != LATTICRA_STATUS_OK) {
        result->adapter_status = LATTICRA_FEDORA_LIVE_ADAPTER_INVALID;
        latticra_live_copy_cstr(
            result->adapter_status_label,
            sizeof(result->adapter_status_label),
            "invalid");
        return status;
    }

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_fedora_live_snapshot_adapter_report(
    const latticra_fedora_live_snapshot_adapter_result_t *result,
    char *buffer,
    size_t buffer_len)
{
    int written;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "FEDORA LIVE READ-ONLY SNAPSHOT ADAPTER\n"
        "adapter_status=%s\n"
        "os_release_path=%s\n"
        "local_rpm_path=%s\n"
        "live_probe_performed=%d\n"
        "os_release_read_attempted=%d\n"
        "os_release_readable=%d\n"
        "command_probe_performed=%d\n"
        "local_rpm_probe_performed=%d\n"
        "ostree_marker_probe_performed=%d\n"
        "id_probe_performed=%d\n"
        "rpm_command_present=%d\n"
        "dnf_command_present=%d\n"
        "rpmbuild_command_present=%d\n"
        "rpmlint_command_present=%d\n"
        "local_rpm_readable=%d\n"
        "running_as_root=%d\n"
        "capture_status=%s\n"
        "classifier_classification=%s\n"
        "classifier_denial=%s\n"
        "snapshot_forwarded_to_classifier=%d\n"
        "sudo_validation_allowed=%d\n"
        "install_command_allowed=%d\n"
        "package_build_allowed=%d\n"
        "network_allowed=%d\n"
        "host_mutation_performed=%d\n"
        "host_install_performed=%d\n"
        "no_effect=%d\n"
        "evidence_level=%u\n",
        result->adapter_status_label,
        result->os_release_path,
        result->local_rpm_path,
        result->live_probe_performed,
        result->os_release_read_attempted,
        result->os_release_readable,
        result->command_probe_performed,
        result->local_rpm_probe_performed,
        result->ostree_marker_probe_performed,
        result->id_probe_performed,
        result->rpm_command_present,
        result->dnf_command_present,
        result->rpmbuild_command_present,
        result->rpmlint_command_present,
        result->local_rpm_readable,
        result->running_as_root,
        result->capture.capture_status_label,
        latticra_fedora_preflight_classification_label(result->capture.preflight.classification),
        latticra_fedora_preflight_denial_label(result->capture.preflight.denial),
        result->capture.snapshot_forwarded_to_classifier,
        result->sudo_validation_allowed,
        result->install_command_allowed,
        result->package_build_allowed,
        result->network_allowed,
        result->host_mutation_performed,
        result->host_install_performed,
        result->no_effect,
        result->evidence_level);

    if (written < 0 || (size_t)written >= buffer_len) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
