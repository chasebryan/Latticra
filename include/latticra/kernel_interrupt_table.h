#ifndef LATTICRA_KERNEL_INTERRUPT_TABLE_H
#define LATTICRA_KERNEL_INTERRUPT_TABLE_H

#include "latticra/kernel_driver_catalog.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX 64u
#define LATTICRA_KERNEL_INTERRUPT_TABLE_ROUTE_MAX 8u
#define LATTICRA_KERNEL_INTERRUPT_TABLE_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_driver_catalog_request_t driver_catalog_request;
    size_t requested_route_count;
} latticra_kernel_interrupt_table_request_t;

typedef struct {
    size_t route_index;
    unsigned long irq_vector;
    char driver_name[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    char device_path[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    char route_class[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    char backing[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    char table_status[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    int declared;
    int connected;
    int enabled;
    int mask_allowed;
    int unmask_allowed;
    int dispatch_allowed;
    int ack_allowed;
    int dma_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_interrupt_table_entry_t;

typedef struct {
    latticra_status_t status;
    char table_status[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_INTERRUPT_TABLE_LABEL_MAX];
    latticra_kernel_driver_catalog_result_t driver_catalog;
    latticra_kernel_interrupt_table_entry_t routes[
        LATTICRA_KERNEL_INTERRUPT_TABLE_ROUTE_MAX];
    size_t route_count;
    int no_effect;
    int interrupt_mask_allowed;
    int interrupt_unmask_allowed;
    int interrupt_dispatch_allowed;
    int interrupt_ack_allowed;
    int dma_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_interrupt_table_result_t;

latticra_status_t latticra_kernel_interrupt_table_default_request(
    latticra_kernel_interrupt_table_request_t *request);

latticra_status_t latticra_kernel_interrupt_table_evaluate(
    const latticra_kernel_interrupt_table_request_t *request,
    latticra_kernel_interrupt_table_result_t *result);

latticra_status_t latticra_kernel_interrupt_table_report(
    const latticra_kernel_interrupt_table_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
