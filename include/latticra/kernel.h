#ifndef LATTICRA_KERNEL_H
#define LATTICRA_KERNEL_H

#include "latticra/system_bootstrap.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_ID_MAX 64u
#define LATTICRA_KERNEL_LABEL_MAX 64u
#define LATTICRA_KERNEL_SOURCE_IDENTITY_MAX 128u
#define LATTICRA_KERNEL_REPORT_MAX 16384u

typedef struct {
    char kernel_id[LATTICRA_KERNEL_ID_MAX];
    const char *source_identity;
    size_t source_identity_len;
    latticra_l_ui_source_span_t source_span;
} latticra_kernel_request_t;

typedef struct {
    latticra_status_t status;
    char kernel_id[LATTICRA_KERNEL_ID_MAX];
    char kernel_mode[LATTICRA_KERNEL_LABEL_MAX];
    char kernel_status[LATTICRA_KERNEL_LABEL_MAX];
    char boot_status[LATTICRA_KERNEL_LABEL_MAX];
    char runtime_status[LATTICRA_KERNEL_LABEL_MAX];
    char scheduler_status[LATTICRA_KERNEL_LABEL_MAX];
    char memory_status[LATTICRA_KERNEL_LABEL_MAX];
    char process_status[LATTICRA_KERNEL_LABEL_MAX];
    char filesystem_status[LATTICRA_KERNEL_LABEL_MAX];
    char network_status[LATTICRA_KERNEL_LABEL_MAX];
    char device_status[LATTICRA_KERNEL_LABEL_MAX];
    char security_status[LATTICRA_KERNEL_LABEL_MAX];
    char source_identity[LATTICRA_KERNEL_SOURCE_IDENTITY_MAX];
    latticra_l_ui_source_span_t source_span;
    latticra_system_bootstrap_result_t bootstrap;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int file_io_allowed;
    int network_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
    int boot_allowed;
    unsigned int evidence_level;
} latticra_kernel_result_t;

latticra_status_t latticra_kernel_default_request(
    latticra_kernel_request_t *request);

latticra_status_t latticra_kernel_initialize(
    const latticra_kernel_request_t *request,
    latticra_kernel_result_t *result);

latticra_status_t latticra_kernel_report(
    const latticra_kernel_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
