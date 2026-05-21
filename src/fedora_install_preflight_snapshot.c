#include "latticra/fedora_install_preflight_snapshot.h"

#include <stdio.h>
#include <string.h>

static void latticra_fedora_snapshot_copy_slice(
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

static int latticra_fedora_snapshot_key_matches(
    const char *line,
    size_t line_len,
    const char *key)
{
    size_t key_len;

    if (line == NULL || key == NULL) {
        return 0;
    }

    key_len = strlen(key);
    if (line_len <= key_len) {
        return 0;
    }

    return memcmp(line, key, key_len) == 0 && line[key_len] == '=';
}

static void latticra_fedora_snapshot_copy_os_release_value(
    const char *line,
    size_t line_len,
    const char *key,
    char *dest,
    size_t dest_len)
{
    size_t key_len;
    size_t pos;
    size_t start;
    size_t end;

    if (!latticra_fedora_snapshot_key_matches(line, line_len, key)) {
        return;
    }

    key_len = strlen(key);
    start = key_len + 1u;
    end = line_len;

    while (end > start &&
           (line[end - 1u] == '\r' || line[end - 1u] == ' ' || line[end - 1u] == '\t')) {
        --end;
    }

    if (start < end && line[start] == '"') {
        ++start;
        pos = start;
        while (pos < end && line[pos] != '"') {
            ++pos;
        }
        end = pos;
    }

    latticra_fedora_snapshot_copy_slice(dest, dest_len, line + start, end - start);
}

static void latticra_fedora_snapshot_parse_os_release(
    const char *text,
    size_t text_len,
    char *os_id,
    size_t os_id_len,
    char *os_id_like,
    size_t os_id_like_len)
{
    size_t line_start;
    size_t pos;
    size_t line_len;

    if (os_id != NULL && os_id_len > 0u) {
        os_id[0] = '\0';
    }
    if (os_id_like != NULL && os_id_like_len > 0u) {
        os_id_like[0] = '\0';
    }

    if (text == NULL || text_len == 0u) {
        return;
    }

    line_start = 0u;
    for (pos = 0u; pos <= text_len; ++pos) {
        if (pos == text_len || text[pos] == '\n') {
            line_len = pos - line_start;
            latticra_fedora_snapshot_copy_os_release_value(
                text + line_start,
                line_len,
                "ID",
                os_id,
                os_id_len);
            latticra_fedora_snapshot_copy_os_release_value(
                text + line_start,
                line_len,
                "ID_LIKE",
                os_id_like,
                os_id_like_len);
            line_start = pos + 1u;
        }
    }
}

const char *latticra_fedora_snapshot_capture_status_label(
    latticra_fedora_snapshot_capture_status_t status)
{
    switch (status) {
    case LATTICRA_FEDORA_SNAPSHOT_CAPTURED:
        return "captured";
    case LATTICRA_FEDORA_SNAPSHOT_PARTIAL:
        return "partial";
    case LATTICRA_FEDORA_SNAPSHOT_INVALID:
        return "invalid";
    default:
        return "unknown";
    }
}

latticra_status_t latticra_fedora_install_preflight_snapshot_capture(
    const latticra_fedora_snapshot_capture_input_t *input,
    latticra_fedora_snapshot_capture_result_t *result)
{
    latticra_status_t status;

    if (input == NULL || result == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(result, 0, sizeof(*result));

    result->no_effect = 1;
    result->os_release_read_allowed = 1;
    result->command_probe_allowed = 1;
    result->local_rpm_probe_allowed = 1;
    result->sudo_validation_allowed = 0;
    result->install_command_allowed = 0;
    result->package_build_allowed = 0;
    result->network_allowed = 0;
    result->host_mutation_performed = 0;
    result->host_install_performed = 0;
    result->snapshot_forwarded_to_classifier = 0;
    result->evidence_level = 2u;

    result->capture_status = input->os_release_readable ?
        LATTICRA_FEDORA_SNAPSHOT_CAPTURED :
        LATTICRA_FEDORA_SNAPSHOT_PARTIAL;
    latticra_fedora_snapshot_copy_slice(
        result->capture_status_label,
        sizeof(result->capture_status_label),
        latticra_fedora_snapshot_capture_status_label(result->capture_status),
        strlen(latticra_fedora_snapshot_capture_status_label(result->capture_status)));

    if (input->os_release_readable) {
        latticra_fedora_snapshot_parse_os_release(
            input->os_release_text,
            input->os_release_text_len,
            result->os_id,
            sizeof(result->os_id),
            result->os_id_like,
            sizeof(result->os_id_like));
    }

    latticra_fedora_snapshot_copy_slice(
        result->local_rpm_path,
        sizeof(result->local_rpm_path),
        input->local_rpm_path,
        input->local_rpm_path_len);

    result->snapshot.os_id = result->os_id;
    result->snapshot.os_id_len = strlen(result->os_id);
    result->snapshot.os_id_like = result->os_id_like;
    result->snapshot.os_id_like_len = strlen(result->os_id_like);
    result->snapshot.host_install_requested = input->host_install_requested ? 1 : 0;
    result->snapshot.immutable_host = input->ostree_booted_marker_present ? 1 : 0;
    result->snapshot.rpm_available = input->rpm_command_present ? 1 : 0;
    result->snapshot.dnf_available = input->dnf_command_present ? 1 : 0;
    result->snapshot.rpmbuild_available = input->rpmbuild_command_present ? 1 : 0;
    result->snapshot.rpmlint_available = input->rpmlint_command_present ? 1 : 0;
    result->snapshot.local_rpm_present = input->local_rpm_readable ? 1 : 0;
    result->snapshot.root_or_sudo_available =
        (input->running_as_root || input->operator_privilege_assertion) ? 1 : 0;
    result->snapshot.network_required = input->network_required ? 1 : 0;
    result->snapshot.package_is_doc_only = input->package_is_doc_only ? 1 : 0;
    result->snapshot.command_entrypoint_expected = input->command_entrypoint_expected ? 1 : 0;

    status = latticra_fedora_host_install_preflight_classify(
        &result->snapshot,
        &result->preflight);
    if (status != LATTICRA_STATUS_OK) {
        result->capture_status = LATTICRA_FEDORA_SNAPSHOT_INVALID;
        latticra_fedora_snapshot_copy_slice(
            result->capture_status_label,
            sizeof(result->capture_status_label),
            "invalid",
            strlen("invalid"));
        return status;
    }

    result->snapshot_forwarded_to_classifier = 1;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_fedora_install_preflight_snapshot_report(
    const latticra_fedora_snapshot_capture_result_t *result,
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
        "FEDORA INSTALL PREFLIGHT SNAPSHOT CAPTURE\n"
        "snapshot_capture_status=%s\n"
        "os_id=%s\n"
        "os_id_like=%s\n"
        "local_rpm_path=%s\n"
        "classifier_classification=%s\n"
        "classifier_denial=%s\n"
        "classifier_install_lane=%s\n"
        "snapshot_forwarded_to_classifier=%d\n"
        "os_release_read_allowed=%d\n"
        "command_probe_allowed=%d\n"
        "local_rpm_probe_allowed=%d\n"
        "sudo_validation_allowed=%d\n"
        "install_command_allowed=%d\n"
        "package_build_allowed=%d\n"
        "network_allowed=%d\n"
        "host_mutation_performed=%d\n"
        "host_install_performed=%d\n"
        "no_effect=%d\n"
        "evidence_level=%u\n",
        result->capture_status_label,
        result->os_id,
        result->os_id_like,
        result->local_rpm_path,
        latticra_fedora_preflight_classification_label(result->preflight.classification),
        latticra_fedora_preflight_denial_label(result->preflight.denial),
        result->preflight.install_lane,
        result->snapshot_forwarded_to_classifier,
        result->os_release_read_allowed,
        result->command_probe_allowed,
        result->local_rpm_probe_allowed,
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
