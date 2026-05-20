#ifndef LATTICRA_KERNEL_MEMORY_MAP_H
#define LATTICRA_KERNEL_MEMORY_MAP_H

#include "latticra/kernel_scheduler.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_MEMORY_MAP_LABEL_MAX 64u
#define LATTICRA_KERNEL_MEMORY_MAP_REGION_MAX 8u
#define LATTICRA_KERNEL_MEMORY_MAP_REPORT_MAX 16384u

typedef struct {
    latticra_kernel_scheduler_request_t scheduler_request;
    size_t requested_region_count;
} latticra_kernel_memory_map_request_t;

typedef struct {
    size_t region_index;
    char label[LATTICRA_KERNEL_MEMORY_MAP_LABEL_MAX];
    char role[LATTICRA_KERNEL_MEMORY_MAP_LABEL_MAX];
    char map_status[LATTICRA_KERNEL_MEMORY_MAP_LABEL_MAX];
    unsigned long base_token;
    unsigned long size_token;
    int mapped;
    int writable;
    int executable;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_memory_map_region_t;

typedef struct {
    latticra_status_t status;
    char map_status[LATTICRA_KERNEL_MEMORY_MAP_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_MEMORY_MAP_LABEL_MAX];
    latticra_kernel_scheduler_result_t scheduler;
    latticra_kernel_memory_map_region_t regions[LATTICRA_KERNEL_MEMORY_MAP_REGION_MAX];
    size_t region_count;
    int no_effect;
    int mapping_allowed;
    int write_allowed;
    int execute_allowed;
    unsigned int evidence_level;
} latticra_kernel_memory_map_result_t;

latticra_status_t latticra_kernel_memory_map_default_request(
    latticra_kernel_memory_map_request_t *request);

latticra_status_t latticra_kernel_memory_map_evaluate(
    const latticra_kernel_memory_map_request_t *request,
    latticra_kernel_memory_map_result_t *result);

latticra_status_t latticra_kernel_memory_map_report(
    const latticra_kernel_memory_map_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
