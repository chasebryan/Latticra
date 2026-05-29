#ifndef LATTICRA_KERNEL_IPC_TABLE_H
#define LATTICRA_KERNEL_IPC_TABLE_H

#include "latticra/kernel_syscall_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_IPC_TABLE_LABEL_MAX 64u
#define LATTICRA_KERNEL_IPC_TABLE_PORT_MAX 10u
#define LATTICRA_KERNEL_IPC_TABLE_REPORT_MAX 24576u

typedef struct {
    latticra_kernel_syscall_table_request_t syscall_table_request;
    size_t requested_port_count;
} latticra_kernel_ipc_table_request_t;

typedef struct {
    size_t port_index;
    unsigned long port_token;
    char label[LATTICRA_KERNEL_IPC_TABLE_LABEL_MAX];
    char domain[LATTICRA_KERNEL_IPC_TABLE_LABEL_MAX];
    char endpoint_status[LATTICRA_KERNEL_IPC_TABLE_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_IPC_TABLE_LABEL_MAX];
    int declared;
    int bound;
    int send_allowed;
    int receive_allowed;
    int queue_mutation_allowed;
    int host_effect_allowed;
    int network_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_ipc_table_entry_t;

typedef struct {
    latticra_status_t status;
    char table_status[LATTICRA_KERNEL_IPC_TABLE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_IPC_TABLE_LABEL_MAX];
    latticra_kernel_syscall_table_result_t syscall_table;
    latticra_kernel_ipc_table_entry_t ports[LATTICRA_KERNEL_IPC_TABLE_PORT_MAX];
    size_t port_count;
    int no_effect;
    int ipc_send_allowed;
    int ipc_receive_allowed;
    int queue_mutation_allowed;
    int endpoint_bind_allowed;
    int host_effect_allowed;
    int network_allowed;
    unsigned int evidence_level;
} latticra_kernel_ipc_table_result_t;

latticra_status_t latticra_kernel_ipc_table_default_request(
    latticra_kernel_ipc_table_request_t *request);

latticra_status_t latticra_kernel_ipc_table_evaluate(
    const latticra_kernel_ipc_table_request_t *request,
    latticra_kernel_ipc_table_result_t *result);

latticra_status_t latticra_kernel_ipc_table_report(
    const latticra_kernel_ipc_table_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
