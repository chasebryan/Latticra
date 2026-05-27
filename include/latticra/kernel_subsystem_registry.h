#ifndef LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_H
#define LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_H

#include "latticra/kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_LABEL_MAX 64u
#define LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_REPORT_MAX 16384u
#define LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_ENTRY_MAX 12u

typedef enum {
    LATTICRA_KERNEL_SUBSYSTEM_BOOT = 0,
    LATTICRA_KERNEL_SUBSYSTEM_RUNTIME = 1,
    LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER = 2,
    LATTICRA_KERNEL_SUBSYSTEM_MEMORY = 3,
    LATTICRA_KERNEL_SUBSYSTEM_PROCESS = 4,
    LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM = 5,
    LATTICRA_KERNEL_SUBSYSTEM_NETWORK = 6,
    LATTICRA_KERNEL_SUBSYSTEM_DEVICE = 7,
    LATTICRA_KERNEL_SUBSYSTEM_SECURITY = 8,
    LATTICRA_KERNEL_SUBSYSTEM_COUNT = 9
} latticra_kernel_subsystem_kind_t;

typedef struct {
    latticra_kernel_subsystem_kind_t kind;
    char name[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_LABEL_MAX];
    char status[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_LABEL_MAX];
    char effect_boundary[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_LABEL_MAX];
    int network_allowed;
    int no_effect;
    int active;
    unsigned int evidence_level;
} latticra_kernel_subsystem_entry_t;

typedef struct {
    latticra_kernel_request_t kernel_request;
} latticra_kernel_subsystem_registry_request_t;

typedef struct {
    latticra_status_t status;
    char registry_status[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_LABEL_MAX];
    latticra_kernel_result_t kernel;
    latticra_kernel_subsystem_entry_t entries[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_ENTRY_MAX];
    size_t entry_count;
    int network_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_subsystem_registry_result_t;

const char *latticra_kernel_subsystem_kind_label(
    latticra_kernel_subsystem_kind_t kind);

latticra_status_t latticra_kernel_subsystem_registry_default_request(
    latticra_kernel_subsystem_registry_request_t *request);

latticra_status_t latticra_kernel_subsystem_registry_evaluate(
    const latticra_kernel_subsystem_registry_request_t *request,
    latticra_kernel_subsystem_registry_result_t *result);

latticra_status_t latticra_kernel_subsystem_registry_report(
    const latticra_kernel_subsystem_registry_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
