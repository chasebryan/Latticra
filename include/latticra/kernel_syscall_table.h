#ifndef LATTICRA_KERNEL_SYSCALL_TABLE_H
#define LATTICRA_KERNEL_SYSCALL_TABLE_H

#include "latticra/kernel_process_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SYSCALL_TABLE_LABEL_MAX 64u
#define LATTICRA_KERNEL_SYSCALL_TABLE_CALL_MAX 12u
#define LATTICRA_KERNEL_SYSCALL_TABLE_REPORT_MAX 24576u

typedef struct {
    latticra_kernel_process_table_request_t process_table_request;
    size_t requested_call_count;
} latticra_kernel_syscall_table_request_t;

typedef struct {
    size_t call_index;
    unsigned long call_number;
    char name[LATTICRA_KERNEL_SYSCALL_TABLE_LABEL_MAX];
    char domain[LATTICRA_KERNEL_SYSCALL_TABLE_LABEL_MAX];
    char dispatch_status[LATTICRA_KERNEL_SYSCALL_TABLE_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_SYSCALL_TABLE_LABEL_MAX];
    int declared;
    int implemented;
    int dispatch_allowed;
    int host_effect_allowed;
    int network_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_syscall_table_entry_t;

typedef struct {
    latticra_status_t status;
    char table_status[LATTICRA_KERNEL_SYSCALL_TABLE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_SYSCALL_TABLE_LABEL_MAX];
    latticra_kernel_process_table_result_t process_table;
    latticra_kernel_syscall_table_entry_t calls[
        LATTICRA_KERNEL_SYSCALL_TABLE_CALL_MAX];
    size_t call_count;
    int no_effect;
    int syscall_dispatch_allowed;
    int host_effect_allowed;
    int mutation_allowed;
    int file_io_allowed;
    int network_allowed;
    unsigned int evidence_level;
} latticra_kernel_syscall_table_result_t;

latticra_status_t latticra_kernel_syscall_table_default_request(
    latticra_kernel_syscall_table_request_t *request);

latticra_status_t latticra_kernel_syscall_table_evaluate(
    const latticra_kernel_syscall_table_request_t *request,
    latticra_kernel_syscall_table_result_t *result);

latticra_status_t latticra_kernel_syscall_table_report(
    const latticra_kernel_syscall_table_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
