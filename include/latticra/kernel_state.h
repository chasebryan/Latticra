#ifndef LATTICRA_KERNEL_STATE_H
#define LATTICRA_KERNEL_STATE_H

#include "latticra/kernel_interrupt_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_STATE_LABEL_MAX 64u
#define LATTICRA_KERNEL_STATE_REPORT_MAX 16384u

typedef enum {
    LATTICRA_KERNEL_STATE_CREATED = 0,
    LATTICRA_KERNEL_STATE_INITIALIZED = 1,
    LATTICRA_KERNEL_STATE_REGISTRY_READY = 2,
    LATTICRA_KERNEL_STATE_SCHEDULER_READY = 3,
    LATTICRA_KERNEL_STATE_MEMORY_MAP_READY = 4,
    LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY = 5,
    LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY = 6,
    LATTICRA_KERNEL_STATE_IPC_TABLE_READY = 7,
    LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY = 8,
    LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY = 9,
    LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY = 10,
    LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY = 11
} latticra_kernel_state_kind_t;

typedef enum {
    LATTICRA_KERNEL_STATE_GATE_DENY = 0,
    LATTICRA_KERNEL_STATE_GATE_ALLOW = 1
} latticra_kernel_state_gate_t;

typedef struct {
    latticra_kernel_memory_map_request_t memory_map_request;
    latticra_kernel_process_table_request_t process_table_request;
    latticra_kernel_syscall_table_request_t syscall_table_request;
    latticra_kernel_ipc_table_request_t ipc_table_request;
    latticra_kernel_vfs_namespace_request_t vfs_namespace_request;
    latticra_kernel_device_registry_request_t device_registry_request;
    latticra_kernel_driver_catalog_request_t driver_catalog_request;
    latticra_kernel_interrupt_table_request_t interrupt_table_request;
    latticra_kernel_state_kind_t current_state;
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_gate_t gate;
} latticra_kernel_state_request_t;

typedef struct {
    latticra_status_t status;
    char state_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    char gate_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    char transition_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    char effect_status[LATTICRA_KERNEL_STATE_LABEL_MAX];
    latticra_kernel_memory_map_result_t memory_map;
    latticra_kernel_process_table_result_t process_table;
    latticra_kernel_syscall_table_result_t syscall_table;
    latticra_kernel_ipc_table_result_t ipc_table;
    latticra_kernel_vfs_namespace_result_t vfs_namespace;
    latticra_kernel_device_registry_result_t device_registry;
    latticra_kernel_driver_catalog_result_t driver_catalog;
    latticra_kernel_interrupt_table_result_t interrupt_table;
    latticra_kernel_state_kind_t previous_state;
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_kind_t next_state;
    int state_change_performed;
    int external_effect_performed;
    int denied;
    unsigned int evidence_level;
} latticra_kernel_state_result_t;

const char *latticra_kernel_state_label(latticra_kernel_state_kind_t state);

latticra_status_t latticra_kernel_state_default_request(
    latticra_kernel_state_request_t *request);

latticra_status_t latticra_kernel_state_transition(
    const latticra_kernel_state_request_t *request,
    latticra_kernel_state_result_t *result);

latticra_status_t latticra_kernel_state_report(
    const latticra_kernel_state_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
