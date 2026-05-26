#include "latticra/latticra_console.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    latticra_console_request_t request;
    latticra_console_result_t result;
    char report[LATTICRA_CONSOLE_REPORT_MAX];
    char registry_report[LATTICRA_CONSOLE_COMMAND_REGISTRY_REPORT_MAX];
    char help_report[LATTICRA_CONSOLE_HELP_REPORT_MAX];
    char manpage_report[LATTICRA_CONSOLE_MANPAGE_REPORT_MAX];
    char boundary_report[LATTICRA_CONSOLE_BOUNDARY_REPORT_MAX];
    char standalone_contract_report[LATTICRA_CONSOLE_STANDALONE_CONTRACT_REPORT_MAX];
    char host_contract_report[LATTICRA_CONSOLE_HOST_CONTRACT_REPORT_MAX];
    char host_inventory_report[LATTICRA_CONSOLE_HOST_INVENTORY_REPORT_MAX];
    char host_adapter_report[LATTICRA_CONSOLE_HOST_ADAPTER_REPORT_MAX];
    char receipt_request_report[LATTICRA_CONSOLE_RECEIPT_REQUEST_REPORT_MAX];
    char receipt_payload_schema_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_SCHEMA_REPORT_MAX];
    char receipt_payload_artifact_draft_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_DRAFT_REPORT_MAX];
    char receipt_payload_artifact_review_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_REPORT_MAX];
    char receipt_payload_artifact_review_receipt_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_RECEIPT_REPORT_MAX];
    char receipt_payload_artifact_review_receipt_draft_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_RECEIPT_DRAFT_REPORT_MAX];
    char receipt_payload_materialization_plan_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_MATERIALIZATION_PLAN_REPORT_MAX];
    char signature_request_binding_report[LATTICRA_CONSOLE_SIGNATURE_REQUEST_BINDING_REPORT_MAX];
    char receipt_report[LATTICRA_CONSOLE_RECEIPT_REPORT_MAX];
    char os_contract_report[LATTICRA_CONSOLE_OS_CONTRACT_REPORT_MAX];
    char vm_evidence_report[LATTICRA_CONSOLE_VM_EVIDENCE_REPORT_MAX];

    if (argc > 2) {
        fputs("usage: latticra_console_report [report|registry|help|man|boundary|standalone|host-contract|host-inventory|host-adapter|receipt-request|receipt-payload|receipt-artifact|receipt-artifact-review|receipt-review-receipt|receipt-review-draft|receipt-materialization-plan|signature-request|receipts|os-contract|vm-evidence]\n", stderr);
        return 64;
    }

    if (latticra_console_default_request(&request) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: default request failed\n", stderr);
        return 1;
    }

    if (latticra_console_initialize(&request, &result) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: initialize failed\n", stderr);
        return 1;
    }

    if (argc == 2 && strcmp(argv[1], "registry") == 0) {
        if (latticra_console_command_registry_report(registry_report, sizeof(registry_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: registry report render failed\n", stderr);
            return 1;
        }
        fputs(registry_report, stdout);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        if (latticra_console_help_report(help_report, sizeof(help_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: help report render failed\n", stderr);
            return 1;
        }
        fputs(help_report, stdout);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "man") == 0) {
        if (latticra_console_manpage_report(manpage_report, sizeof(manpage_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: manpage report render failed\n", stderr);
            return 1;
        }
        fputs(manpage_report, stdout);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "boundary") == 0) {
        if (latticra_console_command_boundary_report(boundary_report, sizeof(boundary_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: boundary report render failed\n", stderr);
            return 1;
        }
        fputs(boundary_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "standalone") == 0 ||
         strcmp(argv[1], "standalone-contract") == 0 ||
         strcmp(argv[1], "lc-standalone") == 0)) {
        if (latticra_console_standalone_contract_report(
                standalone_contract_report,
                sizeof(standalone_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: standalone contract report render failed\n", stderr);
            return 1;
        }
        fputs(standalone_contract_report, stdout);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "host-contract") == 0) {
        if (latticra_console_host_contract_report(host_contract_report, sizeof(host_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: host contract report render failed\n", stderr);
            return 1;
        }
        fputs(host_contract_report, stdout);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "host-inventory") == 0) {
        if (latticra_console_host_inventory_report(host_inventory_report, sizeof(host_inventory_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: host inventory report render failed\n", stderr);
            return 1;
        }
        fputs(host_inventory_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "host-adapter") == 0 || strcmp(argv[1], "adapter-contract") == 0)) {
        if (latticra_console_host_adapter_report(host_adapter_report, sizeof(host_adapter_report)) !=
            LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: host adapter report render failed\n", stderr);
            return 1;
        }
        fputs(host_adapter_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipts") == 0 || strcmp(argv[1], "receipt-contract") == 0)) {
        if (latticra_console_receipt_report(receipt_report, sizeof(receipt_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipt-request") == 0 || strcmp(argv[1], "seal-receipt-request") == 0)) {
        if (latticra_console_receipt_request_report(
                receipt_request_report,
                sizeof(receipt_request_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt request report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_request_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipt-payload") == 0 || strcmp(argv[1], "receipt-payload-schema") == 0 ||
         strcmp(argv[1], "payload-schema") == 0)) {
        if (latticra_console_receipt_payload_schema_report(
                receipt_payload_schema_report,
                sizeof(receipt_payload_schema_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt payload schema report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_payload_schema_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipt-artifact") == 0 ||
         strcmp(argv[1], "receipt-payload-artifact") == 0 ||
         strcmp(argv[1], "receipt-artifact-draft") == 0 ||
         strcmp(argv[1], "receipt-payload-artifact-draft") == 0 ||
         strcmp(argv[1], "payload-artifact") == 0)) {
        if (latticra_console_receipt_payload_artifact_draft_report(
                receipt_payload_artifact_draft_report,
                sizeof(receipt_payload_artifact_draft_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt payload artifact draft report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_payload_artifact_draft_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipt-artifact-review") == 0 ||
         strcmp(argv[1], "receipt-review") == 0 ||
         strcmp(argv[1], "artifact-review") == 0 ||
         strcmp(argv[1], "payload-artifact-review") == 0)) {
        if (latticra_console_receipt_payload_artifact_review_report(
                receipt_payload_artifact_review_report,
                sizeof(receipt_payload_artifact_review_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt payload artifact review report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_payload_artifact_review_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipt-review-receipt") == 0 ||
         strcmp(argv[1], "artifact-review-receipt") == 0 ||
         strcmp(argv[1], "payload-artifact-review-receipt") == 0 ||
         strcmp(argv[1], "receipt-payload-artifact-review-receipt") == 0)) {
        if (latticra_console_receipt_payload_artifact_review_receipt_report(
                receipt_payload_artifact_review_receipt_report,
                sizeof(receipt_payload_artifact_review_receipt_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt payload artifact review receipt report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_payload_artifact_review_receipt_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipt-review-draft") == 0 ||
         strcmp(argv[1], "review-receipt-draft") == 0 ||
         strcmp(argv[1], "artifact-review-receipt-draft") == 0 ||
         strcmp(argv[1], "payload-artifact-review-receipt-draft") == 0 ||
         strcmp(argv[1], "receipt-payload-artifact-review-receipt-draft") == 0)) {
        if (latticra_console_receipt_payload_artifact_review_receipt_draft_report(
                receipt_payload_artifact_review_receipt_draft_report,
                sizeof(receipt_payload_artifact_review_receipt_draft_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt payload artifact review receipt draft report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_payload_artifact_review_receipt_draft_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "receipt-materialization-plan") == 0 ||
         strcmp(argv[1], "materialization-plan") == 0 ||
         strcmp(argv[1], "payload-materialization-plan") == 0 ||
         strcmp(argv[1], "receipt-payload-materialization-plan") == 0)) {
        if (latticra_console_receipt_payload_materialization_plan_report(
                receipt_payload_materialization_plan_report,
                sizeof(receipt_payload_materialization_plan_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt payload materialization plan report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_payload_materialization_plan_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "signature-request") == 0 || strcmp(argv[1], "receipt-signature-request") == 0 ||
         strcmp(argv[1], "signature-request-binding") == 0)) {
        if (latticra_console_signature_request_binding_report(
                signature_request_binding_report,
                sizeof(signature_request_binding_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: signature request binding report render failed\n", stderr);
            return 1;
        }
        fputs(signature_request_binding_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "os-contract") == 0 || strcmp(argv[1], "base-contract") == 0)) {
        if (latticra_console_os_contract_report(os_contract_report, sizeof(os_contract_report)) !=
            LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: OS-base contract report render failed\n", stderr);
            return 1;
        }
        fputs(os_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "vm-evidence") == 0 || strcmp(argv[1], "vm-contract") == 0)) {
        if (latticra_console_vm_evidence_report(vm_evidence_report, sizeof(vm_evidence_report)) !=
            LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: VM evidence report render failed\n", stderr);
            return 1;
        }
        fputs(vm_evidence_report, stdout);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "report") != 0) {
        fputs("usage: latticra_console_report [report|registry|help|man|boundary|standalone|host-contract|host-inventory|host-adapter|receipt-request|receipt-payload|receipt-artifact|receipt-artifact-review|receipt-review-receipt|receipt-review-draft|receipt-materialization-plan|signature-request|receipts|os-contract|vm-evidence]\n", stderr);
        return 64;
    }

    if (latticra_console_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: report render failed\n", stderr);
        return 1;
    }

    fputs(report, stdout);
    fputc('\n', stdout);

    if (latticra_console_command_registry_report(registry_report, sizeof(registry_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: registry report render failed\n", stderr);
        return 1;
    }

    fputs(registry_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_help_report(help_report, sizeof(help_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: help report render failed\n", stderr);
        return 1;
    }

    fputs(help_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_command_boundary_report(boundary_report, sizeof(boundary_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: boundary report render failed\n", stderr);
        return 1;
    }

    fputs(boundary_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_standalone_contract_report(
            standalone_contract_report,
            sizeof(standalone_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: standalone contract report render failed\n", stderr);
        return 1;
    }

    fputs(standalone_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_host_contract_report(host_contract_report, sizeof(host_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: host contract report render failed\n", stderr);
        return 1;
    }

    fputs(host_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_host_inventory_report(host_inventory_report, sizeof(host_inventory_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: host inventory report render failed\n", stderr);
        return 1;
    }

    fputs(host_inventory_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_host_adapter_report(host_adapter_report, sizeof(host_adapter_report)) !=
        LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: host adapter report render failed\n", stderr);
        return 1;
    }

    fputs(host_adapter_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_request_report(receipt_request_report, sizeof(receipt_request_report)) !=
        LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt request report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_request_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_payload_schema_report(
            receipt_payload_schema_report,
            sizeof(receipt_payload_schema_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt payload schema report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_payload_schema_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_payload_artifact_draft_report(
            receipt_payload_artifact_draft_report,
            sizeof(receipt_payload_artifact_draft_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt payload artifact draft report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_payload_artifact_draft_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_payload_artifact_review_report(
            receipt_payload_artifact_review_report,
            sizeof(receipt_payload_artifact_review_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt payload artifact review report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_payload_artifact_review_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_payload_artifact_review_receipt_report(
            receipt_payload_artifact_review_receipt_report,
            sizeof(receipt_payload_artifact_review_receipt_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt payload artifact review receipt report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_payload_artifact_review_receipt_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_payload_artifact_review_receipt_draft_report(
            receipt_payload_artifact_review_receipt_draft_report,
            sizeof(receipt_payload_artifact_review_receipt_draft_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt payload artifact review receipt draft report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_payload_artifact_review_receipt_draft_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_payload_materialization_plan_report(
            receipt_payload_materialization_plan_report,
            sizeof(receipt_payload_materialization_plan_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt payload materialization plan report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_payload_materialization_plan_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_signature_request_binding_report(
            signature_request_binding_report,
            sizeof(signature_request_binding_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: signature request binding report render failed\n", stderr);
        return 1;
    }

    fputs(signature_request_binding_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_receipt_report(receipt_report, sizeof(receipt_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: receipt report render failed\n", stderr);
        return 1;
    }

    fputs(receipt_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_os_contract_report(os_contract_report, sizeof(os_contract_report)) !=
        LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: OS-base contract report render failed\n", stderr);
        return 1;
    }

    fputs(os_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_vm_evidence_report(vm_evidence_report, sizeof(vm_evidence_report)) !=
        LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: VM evidence report render failed\n", stderr);
        return 1;
    }

    fputs(vm_evidence_report, stdout);
    return 0;
}
