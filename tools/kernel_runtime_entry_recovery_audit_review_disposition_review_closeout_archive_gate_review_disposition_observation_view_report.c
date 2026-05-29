#include "latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_result_t
        result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_OBSERVATION_VIEW_REPORT_MAX];

    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_default_request(
            &request) != LATTICRA_STATUS_OK) {
        fputs("kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_report: default request failed\n",
            stderr);
        return 1;
    }

    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_evaluate(
            &request, &result) != LATTICRA_STATUS_OK) {
        fputs("kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_report: evaluation failed\n",
            stderr);
        return 1;
    }

    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_report(
            &result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fputs("kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_report: report render failed\n",
            stderr);
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
