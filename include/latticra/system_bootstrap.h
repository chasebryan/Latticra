#ifndef LATTICRA_SYSTEM_BOOTSTRAP_H
#define LATTICRA_SYSTEM_BOOTSTRAP_H

#include "latticra/runtime_boundary.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SYSTEM_BOOTSTRAP_ID_MAX 64u
#define LATTICRA_SYSTEM_BOOTSTRAP_LABEL_MAX 64u
#define LATTICRA_SYSTEM_BOOTSTRAP_SOURCE_IDENTITY_MAX 128u
#define LATTICRA_SYSTEM_BOOTSTRAP_REPORT_MAX 16384u

typedef struct {
    char bootstrap_id[LATTICRA_SYSTEM_BOOTSTRAP_ID_MAX];
    const char *source_identity;
    size_t source_identity_len;
    latticra_l_ui_source_span_t source_span;
} latticra_system_bootstrap_request_t;

typedef struct {
    latticra_status_t status;
    char bootstrap_id[LATTICRA_SYSTEM_BOOTSTRAP_ID_MAX];
    char phase[LATTICRA_SYSTEM_BOOTSTRAP_LABEL_MAX];
    char system_status[LATTICRA_SYSTEM_BOOTSTRAP_LABEL_MAX];
    char effect_boundary[LATTICRA_SYSTEM_BOOTSTRAP_LABEL_MAX];
    char runtime_entry_status[LATTICRA_SYSTEM_BOOTSTRAP_LABEL_MAX];
    char source_identity[LATTICRA_SYSTEM_BOOTSTRAP_SOURCE_IDENTITY_MAX];
    latticra_l_ui_source_span_t source_span;
    latticra_nucleus_task_result_t nucleus_task;
    latticra_runtime_boundary_result_t runtime_boundary;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int file_io_allowed;
    int network_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
    unsigned int evidence_level;
} latticra_system_bootstrap_result_t;

latticra_status_t latticra_system_bootstrap_default_request(
    latticra_system_bootstrap_request_t *request);

latticra_status_t latticra_system_bootstrap_run(
    const latticra_system_bootstrap_request_t *request,
    latticra_system_bootstrap_result_t *result);

latticra_status_t latticra_system_bootstrap_report(
    const latticra_system_bootstrap_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
