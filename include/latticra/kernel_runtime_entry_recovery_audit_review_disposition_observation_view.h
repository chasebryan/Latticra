#ifndef LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_H
#define LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_H

#include "latticra/kernel_runtime_entry_recovery_audit_review_observation_view.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_LABEL_MAX 128u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_MAX 8u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_REPORT_MAX 65536u

typedef struct {
    latticra_kernel_runtime_entry_recovery_audit_review_observation_view_request_t
        runtime_entry_recovery_audit_review_observation_view_request;
    size_t requested_recovery_audit_review_disposition_observation_view_count;
} latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_request_t;

typedef struct {
    size_t recovery_audit_review_disposition_observation_view_index;
    unsigned long recovery_audit_review_disposition_observation_view_token;
    unsigned long recovery_audit_review_observation_view_token;
    unsigned long recovery_audit_observation_view_token;
    unsigned long recovery_closeout_observation_view_token;
    unsigned long recovery_outcome_observation_view_token;
    unsigned long recovery_audit_review_disposition_observation_slot;
    unsigned long recovery_audit_review_observation_slot;
    unsigned long recovery_audit_observation_slot;
    unsigned long recovery_closeout_observation_slot;
    unsigned long recovery_outcome_observation_slot;
    unsigned long recovery_audit_review_disposition_slot;
    unsigned long recovery_audit_review_slot;
    unsigned long recovery_audit_slot;
    unsigned long recovery_closeout_slot;
    unsigned long recovery_outcome_slot;
    unsigned long pid_token;
    int recovery_audit_review_disposition_observation_view_declared;
    int recovery_audit_review_observation_view_declared;
    int recovery_audit_observation_view_declared;
    int recovery_closeout_observation_view_declared;
    int recovery_outcome_observation_view_declared;
    int recovery_audit_review_disposition_observation_declared;
    int recovery_audit_review_disposition_declared;
    int recovery_audit_review_observation_declared;
    int recovery_audit_review_declared;
    int recovery_audit_observation_declared;
    int recovery_audit_declared;
    int recovery_closeout_observation_declared;
    int recovery_closeout_declared;
    int recovery_outcome_observation_declared;
    int recovery_outcome_declared;
    int recovery_authority_observation_declared;
    char process_label[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_LABEL_MAX];
    char recovery_audit_review_disposition_observation_view_class[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_LABEL_MAX];
    char recovery_audit_review_disposition_observation_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_LABEL_MAX];
    char authority_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_LABEL_MAX];
    int declared;
    int recovery_audit_review_disposition_observation_view_planned;
    int recovery_audit_review_disposition_observation_planned;
    int recovery_audit_review_disposition_planned;
    int recovery_audit_review_observation_planned;
    int recovery_audit_review_planned;
    int recovery_audit_observation_planned;
    int recovery_audit_planned;
    int recovery_closeout_observation_planned;
    int recovery_closeout_planned;
    int recovery_outcome_observation_planned;
    int recovery_outcome_planned;
    int recovery_authority_planned;
    int scheduler_execution_planned;
    int context_switch_planned;
    int run_queue_mutation_planned;
    int runtime_entry_recovery_audit_review_disposition_observation_view_allowed;
    int runtime_entry_recovery_audit_review_observation_view_allowed;
    int runtime_entry_recovery_audit_observation_view_allowed;
    int runtime_entry_recovery_closeout_observation_view_allowed;
    int runtime_entry_recovery_outcome_observation_view_allowed;
    int runtime_entry_allowed;
    int recovery_audit_review_disposition_observation_allowed;
    int recovery_audit_review_disposition_allowed;
    int recovery_audit_review_observation_allowed;
    int recovery_audit_review_allowed;
    int recovery_audit_observation_allowed;
    int recovery_audit_allowed;
    int recovery_closeout_observation_allowed;
    int recovery_closeout_allowed;
    int recovery_outcome_observation_allowed;
    int recovery_outcome_allowed;
    int recovery_authority_allowed;
    int scheduler_execution_allowed;
    int scheduler_dispatch_allowed;
    int context_switch_allowed;
    int run_queue_mutation_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_entry_t;

typedef struct {
    latticra_status_t status;
    char recovery_audit_review_disposition_observation_view_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_LABEL_MAX];
    char policy_status[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_LABEL_MAX];
    latticra_kernel_runtime_entry_recovery_audit_review_observation_view_result_t
        runtime_entry_recovery_audit_review_observation_view;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_entry_t
        recovery_audit_review_disposition_observation_views[
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_MAX];
    size_t recovery_audit_review_disposition_observation_view_count;
    int no_effect;
    int runtime_entry_recovery_audit_review_disposition_observation_view_allowed;
    int runtime_entry_recovery_audit_review_observation_view_allowed;
    int runtime_entry_recovery_audit_observation_view_allowed;
    int runtime_entry_recovery_closeout_observation_view_allowed;
    int runtime_entry_recovery_outcome_observation_view_allowed;
    int runtime_entry_allowed;
    int recovery_audit_review_disposition_observation_allowed;
    int recovery_audit_review_disposition_allowed;
    int recovery_audit_review_observation_allowed;
    int recovery_audit_review_allowed;
    int recovery_audit_observation_allowed;
    int recovery_audit_allowed;
    int recovery_closeout_observation_allowed;
    int recovery_closeout_allowed;
    int recovery_outcome_observation_allowed;
    int recovery_outcome_allowed;
    int recovery_authority_allowed;
    int scheduler_execution_allowed;
    int scheduler_dispatch_allowed;
    int context_switch_allowed;
    int run_queue_mutation_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t;

latticra_status_t
latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_default_request(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_request_t
        *request);

latticra_status_t
latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_evaluate(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_request_t
        *request,
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t
        *result);

latticra_status_t
latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_report(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_observation_view_result_t
        *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
