#ifndef LATTICRA_KERNEL_DRIVER_CATALOG_H
#define LATTICRA_KERNEL_DRIVER_CATALOG_H

#include "latticra/kernel_device_registry.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX 64u
#define LATTICRA_KERNEL_DRIVER_CATALOG_DRIVER_MAX 8u
#define LATTICRA_KERNEL_DRIVER_CATALOG_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_device_registry_request_t device_registry_request;
    size_t requested_driver_count;
} latticra_kernel_driver_catalog_request_t;

typedef struct {
    size_t driver_index;
    unsigned long driver_token;
    char name[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    char device_path[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    char device_class[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    char driver_class[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    char backing[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    char catalog_status[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    int declared;
    int loaded;
    int bound;
    int probe_allowed;
    int load_allowed;
    int bind_allowed;
    int interrupt_allowed;
    int dma_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_driver_catalog_entry_t;

typedef struct {
    latticra_status_t status;
    char catalog_status[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_DRIVER_CATALOG_LABEL_MAX];
    latticra_kernel_device_registry_result_t device_registry;
    latticra_kernel_driver_catalog_entry_t drivers[
        LATTICRA_KERNEL_DRIVER_CATALOG_DRIVER_MAX];
    size_t driver_count;
    int no_effect;
    int driver_probe_allowed;
    int driver_load_allowed;
    int driver_bind_allowed;
    int interrupt_allowed;
    int dma_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_driver_catalog_result_t;

latticra_status_t latticra_kernel_driver_catalog_default_request(
    latticra_kernel_driver_catalog_request_t *request);

latticra_status_t latticra_kernel_driver_catalog_evaluate(
    const latticra_kernel_driver_catalog_request_t *request,
    latticra_kernel_driver_catalog_result_t *result);

latticra_status_t latticra_kernel_driver_catalog_report(
    const latticra_kernel_driver_catalog_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
