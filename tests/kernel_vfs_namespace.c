#include "latticra/kernel_vfs_namespace.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int default_request_is_stable(void) {
    latticra_kernel_vfs_namespace_request_t request;

    EXPECT_TRUE(latticra_kernel_vfs_namespace_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_mount_count == 4u,
        "default mount count");
    EXPECT_TRUE(request.ipc_table_request.requested_port_count == 5u,
        "ipc table seed request preserved");
    EXPECT_TRUE(request.ipc_table_request.syscall_table_request.requested_call_count == 8u,
        "syscall table seed request preserved");
    return 0;
}

static int vfs_namespace_seed_is_metadata_only(void) {
    latticra_kernel_vfs_namespace_request_t request;
    latticra_kernel_vfs_namespace_result_t result;

    EXPECT_TRUE(latticra_kernel_vfs_namespace_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "vfs namespace evaluates");
    EXPECT_TRUE(strcmp(result.namespace_status, "vfs-namespace-seed-ready") == 0,
        "namespace ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.ipc_table.table_status, "ipc-table-seed-ready") == 0,
        "ipc table ready");
    EXPECT_TRUE(strcmp(result.ipc_table.syscall_table.table_status,
            "syscall-table-seed-ready") == 0,
        "syscall table ready");
    EXPECT_TRUE(result.mount_count == 4u,
        "mount count four");
    EXPECT_TRUE(result.no_effect == 1,
        "vfs namespace no-effect");
    EXPECT_TRUE(result.filesystem_lookup_allowed == 0,
        "filesystem lookup denied");
    EXPECT_TRUE(result.filesystem_read_allowed == 0,
        "filesystem read denied");
    EXPECT_TRUE(result.filesystem_write_allowed == 0,
        "filesystem write denied");
    EXPECT_TRUE(result.namespace_mutation_allowed == 0,
        "namespace mutation denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.mounts[0].path, "/") == 0,
        "root mount path");
    EXPECT_TRUE(strcmp(result.mounts[1].path, "/proc") == 0,
        "proc mount path");
    EXPECT_TRUE(strcmp(result.mounts[2].source, "syscall-table-metadata") == 0,
        "syscall mount source");
    EXPECT_TRUE(strcmp(result.mounts[3].authority_status, "namespace-mutation-denied") == 0,
        "ipc mount namespace mutation denied");
    EXPECT_TRUE(result.mounts[0].declared == 1,
        "mount declared");
    EXPECT_TRUE(result.mounts[0].mounted == 0,
        "mount not mounted");
    EXPECT_TRUE(result.mounts[0].lookup_allowed == 0,
        "mount lookup denied");
    EXPECT_TRUE(result.mounts[0].read_allowed == 0,
        "mount read denied");
    EXPECT_TRUE(result.mounts[0].write_allowed == 0,
        "mount write denied");
    EXPECT_TRUE(result.mounts[0].namespace_mutation_allowed == 0,
        "mount namespace mutation denied");
    EXPECT_TRUE(result.mounts[0].host_effect_allowed == 0,
        "mount host effect denied");
    EXPECT_TRUE(result.mounts[0].no_effect == 1,
        "mount no-effect");
    return 0;
}

static int vfs_namespace_caps_mount_count(void) {
    latticra_kernel_vfs_namespace_request_t request;
    latticra_kernel_vfs_namespace_result_t result;

    EXPECT_TRUE(latticra_kernel_vfs_namespace_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_mount_count = 99u;
    EXPECT_TRUE(latticra_kernel_vfs_namespace_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "vfs namespace evaluates cap");
    EXPECT_TRUE(result.mount_count == LATTICRA_KERNEL_VFS_NAMESPACE_MOUNT_MAX,
        "mount count capped");
    EXPECT_TRUE(strcmp(result.mounts[4].source, "reserved-vfs-metadata") == 0,
        "reserved mount source");
    EXPECT_TRUE(result.mounts[4].mount_token == 1004ul,
        "reserved mount token");
    return 0;
}

static int vfs_namespace_report_is_deterministic(void) {
    latticra_kernel_vfs_namespace_request_t request;
    latticra_kernel_vfs_namespace_result_t result;
    char report[LATTICRA_KERNEL_VFS_NAMESPACE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_vfs_namespace_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "vfs namespace evaluates for report");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL VFS NAMESPACE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "namespace_status=vfs-namespace-seed-ready\n") != 0,
        "namespace status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "ipc_table_status=ipc-table-seed-ready\n") != 0,
        "ipc table emitted");
    EXPECT_TRUE(strstr(report, "syscall_table_status=syscall-table-seed-ready\n") != 0,
        "syscall table emitted");
    EXPECT_TRUE(strstr(report, "mount_count=4\n") != 0,
        "mount count emitted");
    EXPECT_TRUE(strstr(report, "filesystem_lookup_allowed=0\n") != 0,
        "lookup flag emitted");
    EXPECT_TRUE(strstr(report, "filesystem_read_allowed=0\n") != 0,
        "read flag emitted");
    EXPECT_TRUE(strstr(report, "filesystem_write_allowed=0\n") != 0,
        "write flag emitted");
    EXPECT_TRUE(strstr(report, "namespace_mutation_allowed=0\n") != 0,
        "namespace flag emitted");
    EXPECT_TRUE(strstr(report, "mount[0].path=/\n") != 0,
        "root mount emitted");
    EXPECT_TRUE(strstr(report, "mount[1].path=/proc\n") != 0,
        "proc mount emitted");
    EXPECT_TRUE(strstr(report, "mount[3].source=ipc-table-metadata\n") != 0,
        "ipc mount emitted");
    EXPECT_TRUE(strstr(report, "mount[0].mounted=0\n") != 0,
        "mounted flag emitted");
    EXPECT_TRUE(strstr(report, "mount[0].no_effect=1\n") != 0,
        "mount no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_vfs_namespace_result_t result;
    char report[LATTICRA_KERNEL_VFS_NAMESPACE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_vfs_namespace_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_vfs_namespace_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (vfs_namespace_seed_is_metadata_only() != 0) return 1;
    if (vfs_namespace_caps_mount_count() != 0) return 1;
    if (vfs_namespace_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_vfs_namespace: ok");
    return 0;
}
