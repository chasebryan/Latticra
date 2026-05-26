#ifndef LATTICRA_KERNEL_DEVICE_REGISTRY_H
#define LATTICRA_KERNEL_DEVICE_REGISTRY_H

#include "latticra/kernel_vfs_namespace.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX 64u
#define LATTICRA_KERNEL_DEVICE_REGISTRY_DEVICE_MAX 8u
#define LATTICRA_KERNEL_DEVICE_REGISTRY_REPORT_MAX 24576u

typedef struct {
    latticra_kernel_vfs_namespace_request_t vfs_namespace_request;
    size_t requested_device_count;
} latticra_kernel_device_registry_request_t;

typedef struct {
    size_t device_index;
    unsigned long device_token;
    char path[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    char label[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    char device_class[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    char backing[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    char registry_status[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    int declared;
    int registered;
    int open_allowed;
    int read_allowed;
    int write_allowed;
    int driver_bind_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_device_registry_entry_t;

typedef struct {
    latticra_status_t status;
    char registry_status[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_DEVICE_REGISTRY_LABEL_MAX];
    latticra_kernel_vfs_namespace_result_t vfs_namespace;
    latticra_kernel_device_registry_entry_t devices[
        LATTICRA_KERNEL_DEVICE_REGISTRY_DEVICE_MAX];
    size_t device_count;
    int no_effect;
    int device_open_allowed;
    int device_read_allowed;
    int device_write_allowed;
    int driver_bind_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_device_registry_result_t;

latticra_status_t latticra_kernel_device_registry_default_request(
    latticra_kernel_device_registry_request_t *request);

latticra_status_t latticra_kernel_device_registry_evaluate(
    const latticra_kernel_device_registry_request_t *request,
    latticra_kernel_device_registry_result_t *result);

latticra_status_t latticra_kernel_device_registry_report(
    const latticra_kernel_device_registry_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
