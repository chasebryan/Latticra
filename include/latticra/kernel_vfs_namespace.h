#ifndef LATTICRA_KERNEL_VFS_NAMESPACE_H
#define LATTICRA_KERNEL_VFS_NAMESPACE_H

#include "latticra/kernel_ipc_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX 64u
#define LATTICRA_KERNEL_VFS_NAMESPACE_MOUNT_MAX 8u
#define LATTICRA_KERNEL_VFS_NAMESPACE_REPORT_MAX 24576u

typedef struct {
    latticra_kernel_ipc_table_request_t ipc_table_request;
    size_t requested_mount_count;
} latticra_kernel_vfs_namespace_request_t;

typedef struct {
    size_t mount_index;
    unsigned long mount_token;
    char path[LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX];
    char source[LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX];
    char kind[LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX];
    char mount_status[LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX];
    int declared;
    int mounted;
    int lookup_allowed;
    int read_allowed;
    int write_allowed;
    int namespace_mutation_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_vfs_namespace_mount_t;

typedef struct {
    latticra_status_t status;
    char namespace_status[LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_VFS_NAMESPACE_LABEL_MAX];
    latticra_kernel_ipc_table_result_t ipc_table;
    latticra_kernel_vfs_namespace_mount_t mounts[
        LATTICRA_KERNEL_VFS_NAMESPACE_MOUNT_MAX];
    size_t mount_count;
    int no_effect;
    int filesystem_lookup_allowed;
    int filesystem_read_allowed;
    int filesystem_write_allowed;
    int namespace_mutation_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_vfs_namespace_result_t;

latticra_status_t latticra_kernel_vfs_namespace_default_request(
    latticra_kernel_vfs_namespace_request_t *request);

latticra_status_t latticra_kernel_vfs_namespace_evaluate(
    const latticra_kernel_vfs_namespace_request_t *request,
    latticra_kernel_vfs_namespace_result_t *result);

latticra_status_t latticra_kernel_vfs_namespace_report(
    const latticra_kernel_vfs_namespace_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
