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
    char session_contract_report[LATTICRA_CONSOLE_SESSION_CONTRACT_REPORT_MAX];
    char workspace_contract_report[LATTICRA_CONSOLE_WORKSPACE_CONTRACT_REPORT_MAX];
    char namespace_contract_report[LATTICRA_CONSOLE_NAMESPACE_CONTRACT_REPORT_MAX];
    char rootfs_contract_report[LATTICRA_CONSOLE_ROOTFS_CONTRACT_REPORT_MAX];
    char packages_contract_report[LATTICRA_CONSOLE_PACKAGES_CONTRACT_REPORT_MAX];
    char init_contract_report[LATTICRA_CONSOLE_INIT_CONTRACT_REPORT_MAX];
    char services_contract_report[LATTICRA_CONSOLE_SERVICES_CONTRACT_REPORT_MAX];
    char service_schema_contract_report[LATTICRA_CONSOLE_SERVICE_SCHEMA_CONTRACT_REPORT_MAX];
    char service_definitions_contract_report[LATTICRA_CONSOLE_SERVICE_DEFINITIONS_CONTRACT_REPORT_MAX];
    char service_plan_contract_report[LATTICRA_CONSOLE_SERVICE_PLAN_CONTRACT_REPORT_MAX];
    char service_runtime_contract_report[LATTICRA_CONSOLE_SERVICE_RUNTIME_CONTRACT_REPORT_MAX];
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
        fputs("usage: latticra_console_report [report|registry|help|man|boundary|standalone|session|workspace|namespace|rootfs|packages|init|services|service-schema|service-definitions|service-plan|service-runtime|host-contract|host-inventory|host-adapter|receipt-request|receipt-payload|receipt-artifact|receipt-artifact-review|receipt-review-receipt|receipt-review-draft|receipt-materialization-plan|signature-request|receipts|os-contract|vm-evidence]\n", stderr);
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

    if (argc == 2 &&
        (strcmp(argv[1], "session") == 0 ||
         strcmp(argv[1], "session-contract") == 0 ||
         strcmp(argv[1], "lc-session") == 0)) {
        if (latticra_console_session_contract_report(
                session_contract_report,
                sizeof(session_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: session contract report render failed\n", stderr);
            return 1;
        }
        fputs(session_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "workspace") == 0 ||
         strcmp(argv[1], "workspace-contract") == 0 ||
         strcmp(argv[1], "lc-workspace") == 0)) {
        if (latticra_console_workspace_contract_report(
                workspace_contract_report,
                sizeof(workspace_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: workspace contract report render failed\n", stderr);
            return 1;
        }
        fputs(workspace_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "namespace") == 0 ||
         strcmp(argv[1], "namespace-contract") == 0 ||
         strcmp(argv[1], "lc-namespace") == 0)) {
        if (latticra_console_namespace_contract_report(
                namespace_contract_report,
                sizeof(namespace_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: namespace contract report render failed\n", stderr);
            return 1;
        }
        fputs(namespace_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "rootfs") == 0 ||
         strcmp(argv[1], "rootfs-contract") == 0 ||
         strcmp(argv[1], "lc-rootfs") == 0)) {
        if (latticra_console_rootfs_contract_report(
                rootfs_contract_report,
                sizeof(rootfs_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: rootfs contract report render failed\n", stderr);
            return 1;
        }
        fputs(rootfs_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "packages") == 0 ||
         strcmp(argv[1], "packages-contract") == 0 ||
         strcmp(argv[1], "package-manifest") == 0 ||
         strcmp(argv[1], "lc-packages") == 0)) {
        if (latticra_console_packages_contract_report(
                packages_contract_report,
                sizeof(packages_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: packages contract report render failed\n", stderr);
            return 1;
        }
        fputs(packages_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "init") == 0 ||
         strcmp(argv[1], "init-contract") == 0 ||
         strcmp(argv[1], "lc-init") == 0)) {
        if (latticra_console_init_contract_report(
                init_contract_report,
                sizeof(init_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: init contract report render failed\n", stderr);
            return 1;
        }
        fputs(init_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "services") == 0 ||
         strcmp(argv[1], "services-contract") == 0 ||
         strcmp(argv[1], "service-registry") == 0 ||
         strcmp(argv[1], "lc-services") == 0)) {
        if (latticra_console_services_contract_report(
                services_contract_report,
                sizeof(services_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: services contract report render failed\n", stderr);
            return 1;
        }
        fputs(services_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "service-schema") == 0 ||
         strcmp(argv[1], "service-schema-contract") == 0 ||
         strcmp(argv[1], "service-definition-schema") == 0 ||
         strcmp(argv[1], "lc-service-schema") == 0)) {
        if (latticra_console_service_schema_contract_report(
                service_schema_contract_report,
                sizeof(service_schema_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: service schema contract report render failed\n", stderr);
            return 1;
        }
        fputs(service_schema_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "service-definitions") == 0 ||
         strcmp(argv[1], "service-definitions-contract") == 0 ||
         strcmp(argv[1], "service-definition-stubs") == 0 ||
         strcmp(argv[1], "lc-service-definitions") == 0)) {
        if (latticra_console_service_definitions_contract_report(
                service_definitions_contract_report,
                sizeof(service_definitions_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: service definitions contract report render failed\n", stderr);
            return 1;
        }
        fputs(service_definitions_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "service-plan") == 0 ||
         strcmp(argv[1], "service-plan-contract") == 0 ||
         strcmp(argv[1], "service-activation-plan") == 0 ||
         strcmp(argv[1], "lc-service-plan") == 0)) {
        if (latticra_console_service_plan_contract_report(
                service_plan_contract_report,
                sizeof(service_plan_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: service plan contract report render failed\n", stderr);
            return 1;
        }
        fputs(service_plan_contract_report, stdout);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "service-runtime") == 0 ||
         strcmp(argv[1], "service-runtime-contract") == 0 ||
         strcmp(argv[1], "service-runtime-handoff") == 0 ||
         strcmp(argv[1], "lc-service-runtime") == 0)) {
        if (latticra_console_service_runtime_contract_report(
                service_runtime_contract_report,
                sizeof(service_runtime_contract_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: service runtime contract report render failed\n", stderr);
            return 1;
        }
        fputs(service_runtime_contract_report, stdout);
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
        fputs("usage: latticra_console_report [report|registry|help|man|boundary|standalone|session|workspace|namespace|rootfs|packages|init|services|service-schema|service-definitions|service-plan|service-runtime|host-contract|host-inventory|host-adapter|receipt-request|receipt-payload|receipt-artifact|receipt-artifact-review|receipt-review-receipt|receipt-review-draft|receipt-materialization-plan|signature-request|receipts|os-contract|vm-evidence]\n", stderr);
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

    if (latticra_console_session_contract_report(
            session_contract_report,
            sizeof(session_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: session contract report render failed\n", stderr);
        return 1;
    }

    fputs(session_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_workspace_contract_report(
            workspace_contract_report,
            sizeof(workspace_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: workspace contract report render failed\n", stderr);
        return 1;
    }

    fputs(workspace_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_namespace_contract_report(
            namespace_contract_report,
            sizeof(namespace_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: namespace contract report render failed\n", stderr);
        return 1;
    }

    fputs(namespace_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_rootfs_contract_report(
            rootfs_contract_report,
            sizeof(rootfs_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: rootfs contract report render failed\n", stderr);
        return 1;
    }

    fputs(rootfs_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_packages_contract_report(
            packages_contract_report,
            sizeof(packages_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: packages contract report render failed\n", stderr);
        return 1;
    }

    fputs(packages_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_init_contract_report(
            init_contract_report,
            sizeof(init_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: init contract report render failed\n", stderr);
        return 1;
    }

    fputs(init_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_services_contract_report(
            services_contract_report,
            sizeof(services_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: services contract report render failed\n", stderr);
        return 1;
    }

    fputs(services_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_service_schema_contract_report(
            service_schema_contract_report,
            sizeof(service_schema_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: service schema contract report render failed\n", stderr);
        return 1;
    }

    fputs(service_schema_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_service_definitions_contract_report(
            service_definitions_contract_report,
            sizeof(service_definitions_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: service definitions contract report render failed\n", stderr);
        return 1;
    }

    fputs(service_definitions_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_service_plan_contract_report(
            service_plan_contract_report,
            sizeof(service_plan_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: service plan contract report render failed\n", stderr);
        return 1;
    }

    fputs(service_plan_contract_report, stdout);
    fputc('\n', stdout);

    if (latticra_console_service_runtime_contract_report(
            service_runtime_contract_report,
            sizeof(service_runtime_contract_report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: service runtime contract report render failed\n", stderr);
        return 1;
    }

    fputs(service_runtime_contract_report, stdout);
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
