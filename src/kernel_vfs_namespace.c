#include "latticra/kernel_vfs_namespace.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void vfs_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_vfs_namespace_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    vfs_copy(result->namespace_status, sizeof(result->namespace_status), "pending");
    vfs_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->path_lookup_allowed = 0;
    result->file_read_allowed = 0;
    result->file_write_allowed = 0;
    result->namespace_mutation_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 11u;
}

latticra_status_t latticra_kernel_vfs_namespace_default_request(
    latticra_kernel_vfs_namespace_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_ipc_table_default_request(&request->ipc_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_mount_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_mount(
    latticra_kernel_vfs_namespace_mount_t *mount,
    size_t index,
    unsigned long mount_token,
    const char *label,
    const char *path,
    const char *role,
    const char *backing_status) {
    memset(mount, 0, sizeof(*mount));
    mount->mount_index = index;
    mount->mount_token = mount_token;
    vfs_copy(mount->label, sizeof(mount->label), label);
    vfs_copy(mount->path, sizeof(mount->path), path);
    vfs_copy(mount->role, sizeof(mount->role), role);
    vfs_copy(mount->backing_status, sizeof(mount->backing_status), backing_status);
    vfs_copy(mount->authority_status, sizeof(mount->authority_status),
        "filesystem-access-denied");
    mount->declared = 1;
    mount->mounted = 0;
    mount->lookup_allowed = 0;
    mount->read_allowed = 0;
    mount->write_allowed = 0;
    mount->namespace_mutation_allowed = 0;
    mount->no_effect = 1;
    mount->evidence_level = 11u;
}

static void fill_mounts(
    latticra_kernel_vfs_namespace_result_t *result,
    size_t requested_mount_count) {
    size_t count = requested_mount_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_VFS_NAMESPACE_MOUNT_MAX) {
        count = LATTICRA_KERNEL_VFS_NAMESPACE_MOUNT_MAX;
    }

    result->mount_count = count;
    if (count > 0u) {
        fill_mount(&result->mounts[0], 0u, 0ul, "root-namespace-metadata",
            "/", "root-namespace-label", "metadata-backing-only");
    }
    if (count > 1u) {
        fill_mount(&result->mounts[1], 1u, 1ul, "process-namespace-metadata",
            "/proc", "process-table-label", "process-table-metadata");
    }
    if (count > 2u) {
        fill_mount(&result->mounts[2], 2u, 2ul, "syscall-namespace-metadata",
            "/syscall", "syscall-table-label", "syscall-table-metadata");
    }
    if (count > 3u) {
        fill_mount(&result->mounts[3], 3u, 3ul, "ipc-namespace-metadata",
            "/ipc", "ipc-table-label", "ipc-table-metadata");
    }
    for (i = 4u; i < count; ++i) {
        fill_mount(&result->mounts[i], i, 1000ul + (unsigned long)i,
            "reserved-vfs-namespace-metadata", "/reserved",
            "reserved-namespace-label", "reserved-metadata");
    }
}

latticra_status_t latticra_kernel_vfs_namespace_evaluate(
    const latticra_kernel_vfs_namespace_request_t *request,
    latticra_kernel_vfs_namespace_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        vfs_copy(result->namespace_status, sizeof(result->namespace_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_ipc_table_evaluate(&request->ipc_table_request,
        &result->ipc_table);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        vfs_copy(result->namespace_status, sizeof(result->namespace_status),
            "ipc-table-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_mounts(result, request->requested_mount_count);
    result->no_effect = result->ipc_table.no_effect;
    vfs_copy(result->namespace_status, sizeof(result->namespace_status),
        result->no_effect ? "vfs-namespace-seed-ready" : "vfs-namespace-seed-blocked");
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

latticra_status_t latticra_kernel_vfs_namespace_report(
    const latticra_kernel_vfs_namespace_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL VFS NAMESPACE REPORT\n"
        "namespace_status=%s\n"
        "policy_status=%s\n"
        "ipc_table_status=%s\n"
        "syscall_table_status=%s\n"
        "mount_count=%lu\n"
        "no_effect=%d\n"
        "path_lookup_allowed=%d\n"
        "file_read_allowed=%d\n"
        "file_write_allowed=%d\n"
        "namespace_mutation_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->namespace_status,
        result->policy_status,
        result->ipc_table.table_status,
        result->ipc_table.syscall_table.table_status,
        (unsigned long)result->mount_count,
        result->no_effect,
        result->path_lookup_allowed,
        result->file_read_allowed,
        result->file_write_allowed,
        result->namespace_mutation_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->mount_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "mount[%lu].label=%s\n"
            "mount[%lu].token=%lu\n"
            "mount[%lu].path=%s\n"
            "mount[%lu].role=%s\n"
            "mount[%lu].backing_status=%s\n"
            "mount[%lu].authority_status=%s\n"
            "mount[%lu].declared=%d\n"
            "mount[%lu].mounted=%d\n"
            "mount[%lu].lookup_allowed=%d\n"
            "mount[%lu].read_allowed=%d\n"
            "mount[%lu].write_allowed=%d\n"
            "mount[%lu].namespace_mutation_allowed=%d\n"
            "mount[%lu].no_effect=%d\n",
            (unsigned long)i, result->mounts[i].label,
            (unsigned long)i, result->mounts[i].mount_token,
            (unsigned long)i, result->mounts[i].path,
            (unsigned long)i, result->mounts[i].role,
            (unsigned long)i, result->mounts[i].backing_status,
            (unsigned long)i, result->mounts[i].authority_status,
            (unsigned long)i, result->mounts[i].declared,
            (unsigned long)i, result->mounts[i].mounted,
            (unsigned long)i, result->mounts[i].lookup_allowed,
            (unsigned long)i, result->mounts[i].read_allowed,
            (unsigned long)i, result->mounts[i].write_allowed,
            (unsigned long)i, result->mounts[i].namespace_mutation_allowed,
            (unsigned long)i, result->mounts[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
