#ifndef LATTICRA_KERNEL_STATE_MACHINE_H
#define LATTICRA_KERNEL_STATE_MACHINE_H

#include "latticra/kernel_state.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX 64u
#define LATTICRA_KERNEL_STATE_MACHINE_LOG_MAX 8u
#define LATTICRA_KERNEL_STATE_MACHINE_REPORT_MAX 16384u

typedef struct {
    latticra_kernel_state_kind_t from_state;
    latticra_kernel_state_kind_t to_state;
    char status[LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX];
    int state_change_performed;
    int external_effect_performed;
} latticra_kernel_state_machine_log_entry_t;

typedef struct {
    latticra_kernel_state_kind_t current_state;
    char machine_status[LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX];
    latticra_kernel_state_machine_log_entry_t log[LATTICRA_KERNEL_STATE_MACHINE_LOG_MAX];
    size_t log_count;
    int state_mutated;
    int external_effect_performed;
    unsigned int evidence_level;
} latticra_kernel_state_machine_t;

typedef struct {
    latticra_kernel_memory_map_request_t memory_map_request;
    latticra_kernel_process_table_request_t process_table_request;
    latticra_kernel_syscall_table_request_t syscall_table_request;
    latticra_kernel_ipc_table_request_t ipc_table_request;
    latticra_kernel_vfs_namespace_request_t vfs_namespace_request;
    latticra_kernel_state_kind_t target_state;
    latticra_kernel_state_gate_t gate;
} latticra_kernel_state_machine_step_request_t;

typedef struct {
    latticra_status_t status;
    char step_status[LATTICRA_KERNEL_STATE_MACHINE_LABEL_MAX];
    latticra_kernel_state_result_t transition;
    latticra_kernel_state_kind_t machine_state_before;
    latticra_kernel_state_kind_t machine_state_after;
    int state_mutated;
    int external_effect_performed;
    unsigned int evidence_level;
} latticra_kernel_state_machine_step_result_t;

latticra_status_t latticra_kernel_state_machine_init(
    latticra_kernel_state_machine_t *machine);

latticra_status_t latticra_kernel_state_machine_default_step_request(
    latticra_kernel_state_machine_step_request_t *request);

latticra_status_t latticra_kernel_state_machine_step(
    latticra_kernel_state_machine_t *machine,
    const latticra_kernel_state_machine_step_request_t *request,
    latticra_kernel_state_machine_step_result_t *result);

latticra_status_t latticra_kernel_state_machine_report(
    const latticra_kernel_state_machine_t *machine,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
