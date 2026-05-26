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
    char host_contract_report[LATTICRA_CONSOLE_HOST_CONTRACT_REPORT_MAX];
    char host_inventory_report[LATTICRA_CONSOLE_HOST_INVENTORY_REPORT_MAX];
    char receipt_report[LATTICRA_CONSOLE_RECEIPT_REPORT_MAX];
    char os_contract_report[LATTICRA_CONSOLE_OS_CONTRACT_REPORT_MAX];
    char vm_evidence_report[LATTICRA_CONSOLE_VM_EVIDENCE_REPORT_MAX];

    if (argc > 2) {
        fputs("usage: latticra_console_report [report|registry|help|man|boundary|host-contract|host-inventory|receipts|os-contract|vm-evidence]\n", stderr);
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
        (strcmp(argv[1], "receipts") == 0 || strcmp(argv[1], "receipt-contract") == 0)) {
        if (latticra_console_receipt_report(receipt_report, sizeof(receipt_report)) != LATTICRA_STATUS_OK) {
            fputs("latticra_console_report: receipt report render failed\n", stderr);
            return 1;
        }
        fputs(receipt_report, stdout);
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
        fputs("usage: latticra_console_report [report|registry|help|man|boundary|host-contract|host-inventory|receipts|os-contract|vm-evidence]\n", stderr);
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
