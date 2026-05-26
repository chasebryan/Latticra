#include "latticra/latticra_console.h"

#include <stdio.h>
#include <string.h>

static int require_int(const char *label, int actual, int expected) {
    if (actual != expected) {
        fprintf(stderr, "%s: expected %d got %d\n", label, expected, actual);
        return 1;
    }
    return 0;
}

static int require_text(const char *label, const char *actual, const char *expected) {
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "%s: expected %s got %s\n", label, expected, actual);
        return 1;
    }
    return 0;
}

static int require_contains(const char *label, const char *haystack, const char *needle) {
    if (strstr(haystack, needle) == 0) {
        fprintf(stderr, "%s: missing %s\n", label, needle);
        return 1;
    }
    return 0;
}

int main(void) {
    latticra_console_request_t request;
    latticra_console_result_t result;
    const latticra_console_command_t *command;
    latticra_console_command_boundary_t boundary;
    size_t i;
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
    char host_contract_report[LATTICRA_CONSOLE_HOST_CONTRACT_REPORT_MAX];
    char host_inventory_report[LATTICRA_CONSOLE_HOST_INVENTORY_REPORT_MAX];
    char host_adapter_report[LATTICRA_CONSOLE_HOST_ADAPTER_REPORT_MAX];
    char receipt_request_report[LATTICRA_CONSOLE_RECEIPT_REQUEST_REPORT_MAX];
    char receipt_payload_schema_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_SCHEMA_REPORT_MAX];
    char receipt_payload_artifact_draft_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_DRAFT_REPORT_MAX];
    char receipt_payload_artifact_review_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_REPORT_MAX];
    char receipt_payload_artifact_review_receipt_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_RECEIPT_REPORT_MAX];
    char receipt_payload_artifact_review_receipt_draft_report
        [LATTICRA_CONSOLE_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_RECEIPT_DRAFT_REPORT_MAX];
    char receipt_payload_materialization_plan_report[LATTICRA_CONSOLE_RECEIPT_PAYLOAD_MATERIALIZATION_PLAN_REPORT_MAX];
    char signature_request_binding_report[LATTICRA_CONSOLE_SIGNATURE_REQUEST_BINDING_REPORT_MAX];
    char receipt_report[LATTICRA_CONSOLE_RECEIPT_REPORT_MAX];
    char os_contract_report[LATTICRA_CONSOLE_OS_CONTRACT_REPORT_MAX];
    char vm_evidence_report[LATTICRA_CONSOLE_VM_EVIDENCE_REPORT_MAX];
    int failures = 0;

    failures += require_int(
        "default_request",
        latticra_console_default_request(&request),
        LATTICRA_STATUS_OK);
    failures += require_text("request.console_id", request.console_id, "latticra-console");
    failures += require_int("request.panel_installable", request.panel_installable, 1);
    failures += require_int("request.host_embeddable", request.host_embeddable, 1);

    failures += require_int(
        "initialize",
        latticra_console_initialize(&request, &result),
        LATTICRA_STATUS_OK);
    failures += require_text("result.short_name", result.short_name, "LC");
    failures += require_text("result.component_key", result.component_key, "latticra_console");
    failures += require_text("result.console_status", result.console_status, "ready-report-only");
    failures += require_text(
        "result.command_registry_status",
        result.command_registry_status,
        "seed-registry-ready");
    failures += require_text(
        "result.standalone_console_status",
        result.standalone_console_status,
        "metadata-only-standalone-contract-ready");
    failures += require_text(
        "result.session_contract_status",
        result.session_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.workspace_contract_status",
        result.workspace_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.namespace_contract_status",
        result.namespace_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.rootfs_contract_status",
        result.rootfs_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.substrate_bridge_status",
        result.substrate_bridge_status,
        "metadata-bound-ready");
    failures += require_text(
        "result.host_embedding_contract_status",
        result.host_embedding_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.host_inventory_contract_status",
        result.host_inventory_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.host_adapter_contract_status",
        result.host_adapter_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.receipt_request_contract_status",
        result.receipt_request_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.receipt_payload_schema_status",
        result.receipt_payload_schema_status,
        "metadata-only-schema-ready");
    failures += require_text(
        "result.receipt_payload_artifact_draft_status",
        result.receipt_payload_artifact_draft_status,
        "metadata-only-draft-ready");
    failures += require_text(
        "result.receipt_payload_artifact_review_status",
        result.receipt_payload_artifact_review_status,
        "metadata-only-review-gate-ready");
    failures += require_text(
        "result.receipt_payload_artifact_review_receipt_status",
        result.receipt_payload_artifact_review_receipt_status,
        "metadata-only-receipt-contract-ready");
    failures += require_text(
        "result.receipt_payload_artifact_review_receipt_draft_status",
        result.receipt_payload_artifact_review_receipt_draft_status,
        "metadata-only-review-receipt-draft-ready");
    failures += require_text(
        "result.receipt_payload_materialization_plan_status",
        result.receipt_payload_materialization_plan_status,
        "metadata-only-plan-ready");
    failures += require_text(
        "result.signature_request_binding_status",
        result.signature_request_binding_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.receipt_contract_status",
        result.receipt_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.os_base_contract_status",
        result.os_base_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.vm_evidence_contract_status",
        result.vm_evidence_contract_status,
        "metadata-only-contract-ready");
    failures += require_text(
        "result.os_base_status",
        result.os_base_status,
        "planned-no-boot-authority");
    failures += require_int("result.no_effect", result.no_effect, 1);
    failures += require_int("result.configurable", result.configurable, 1);
    failures += require_int("result.panel_installable", result.panel_installable, 1);
    failures += require_int("result.standalone_installable", result.standalone_installable, 1);
    failures += require_int("result.standalone_requires_panel", result.standalone_requires_panel, 0);
    failures += require_int("result.standalone_contract_present", result.standalone_contract_present, 1);
    failures += require_int("result.session_contract_present", result.session_contract_present, 1);
    failures += require_int("result.workspace_contract_present", result.workspace_contract_present, 1);
    failures += require_int("result.namespace_contract_present", result.namespace_contract_present, 1);
    failures += require_int("result.rootfs_contract_present", result.rootfs_contract_present, 1);
    failures += require_int("result.command_registry_present", result.command_registry_present, 1);
    failures += require_int("result.substrate_bridge_present", result.substrate_bridge_present, 1);
    failures += require_int(
        "result.host_embedding_contract_present",
        result.host_embedding_contract_present,
        1);
    failures += require_int(
        "result.host_inventory_contract_present",
        result.host_inventory_contract_present,
        1);
    failures += require_int(
        "result.host_adapter_contract_present",
        result.host_adapter_contract_present,
        1);
    failures += require_int(
        "result.receipt_request_contract_present",
        result.receipt_request_contract_present,
        1);
    failures += require_int(
        "result.receipt_payload_schema_present",
        result.receipt_payload_schema_present,
        1);
    failures += require_int(
        "result.receipt_payload_artifact_draft_present",
        result.receipt_payload_artifact_draft_present,
        1);
    failures += require_int(
        "result.receipt_payload_artifact_review_present",
        result.receipt_payload_artifact_review_present,
        1);
    failures += require_int(
        "result.receipt_payload_artifact_review_receipt_present",
        result.receipt_payload_artifact_review_receipt_present,
        1);
    failures += require_int(
        "result.receipt_payload_artifact_review_receipt_draft_present",
        result.receipt_payload_artifact_review_receipt_draft_present,
        1);
    failures += require_int(
        "result.receipt_payload_materialization_plan_present",
        result.receipt_payload_materialization_plan_present,
        1);
    failures += require_int(
        "result.signature_request_binding_present",
        result.signature_request_binding_present,
        1);
    failures += require_int(
        "result.receipt_contract_present",
        result.receipt_contract_present,
        1);
    failures += require_int(
        "result.os_base_contract_present",
        result.os_base_contract_present,
        1);
    failures += require_int(
        "result.vm_evidence_contract_present",
        result.vm_evidence_contract_present,
        1);
    failures += require_int("result.operator_shell_present", result.operator_shell_present, 1);
    failures += require_int("result.execution_allowed", result.execution_allowed, 0);
    failures += require_int("result.host_mutation_allowed", result.host_mutation_allowed, 0);
    failures += require_int("result.file_io_allowed", result.file_io_allowed, 0);
    failures += require_int("result.network_allowed", result.network_allowed, 0);
    failures += require_int("result.runtime_enforcement_allowed", result.runtime_enforcement_allowed, 0);
    failures += require_int("result.boot_allowed", result.boot_allowed, 0);
    failures += require_int(
        "command_count",
        (int)latticra_console_command_count(),
        (int)result.command_count);
    failures += require_int("command_count_min", result.command_count >= 22u, 1);
    failures += require_text(
        "standalone profile label",
        latticra_console_profile_label(LATTICRA_CONSOLE_PROFILE_STANDALONE),
        "standalone");

    command = latticra_console_find_command("lc substrate");
    failures += require_int("find lc substrate", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc substrate capability",
            command->capability_label,
            "lc.substrate.inspect");
        failures += require_int("lc substrate no_effect", command->no_effect, 1);
        failures += require_int("lc substrate host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc profiles");
    failures += require_int("find lc profiles", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc profiles capability",
            command->capability_label,
            "lc.core.profiles");
        failures += require_int("lc profiles no_effect", command->no_effect, 1);
    }

    command = latticra_console_find_command("lc install-config");
    failures += require_int("find lc install-config", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc install-config capability",
            command->capability_label,
            "lc.install.config");
        failures += require_int("lc install-config no_effect", command->no_effect, 1);
        failures += require_int("lc install-config host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc standalone");
    failures += require_int("find lc standalone", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc standalone capability",
            command->capability_label,
            "lc.standalone.inspect");
        failures += require_int("lc standalone no_effect", command->no_effect, 1);
        failures += require_int("lc standalone host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc session");
    failures += require_int("find lc session", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc session capability",
            command->capability_label,
            "lc.session.contract");
        failures += require_int("lc session no_effect", command->no_effect, 1);
        failures += require_int("lc session host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc workspace");
    failures += require_int("find lc workspace", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc workspace capability",
            command->capability_label,
            "lc.workspace.contract");
        failures += require_int("lc workspace no_effect", command->no_effect, 1);
        failures += require_int("lc workspace host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc namespace");
    failures += require_int("find lc namespace", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc namespace capability",
            command->capability_label,
            "lc.namespace.contract");
        failures += require_int("lc namespace no_effect", command->no_effect, 1);
        failures += require_int("lc namespace host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc rootfs");
    failures += require_int("find lc rootfs", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc rootfs capability",
            command->capability_label,
            "lc.rootfs.contract");
        failures += require_int("lc rootfs no_effect", command->no_effect, 1);
        failures += require_int("lc rootfs host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipts");
    failures += require_int("find lc receipts", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipts capability",
            command->capability_label,
            "lc.receipts.inspect");
        failures += require_int("lc receipts no_effect", command->no_effect, 1);
        failures += require_int("lc receipts host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipt-request");
    failures += require_int("find lc receipt-request", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipt-request capability",
            command->capability_label,
            "lc.receipt.request");
        failures += require_int("lc receipt-request no_effect", command->no_effect, 1);
        failures += require_int("lc receipt-request host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipt-payload");
    failures += require_int("find lc receipt-payload", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipt-payload capability",
            command->capability_label,
            "lc.receipt.payload");
        failures += require_int("lc receipt-payload no_effect", command->no_effect, 1);
        failures += require_int("lc receipt-payload host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipt-artifact");
    failures += require_int("find lc receipt-artifact", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipt-artifact capability",
            command->capability_label,
            "lc.receipt.artifact");
        failures += require_int("lc receipt-artifact no_effect", command->no_effect, 1);
        failures += require_int("lc receipt-artifact host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipt-artifact-review");
    failures += require_int("find lc receipt-artifact-review", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipt-artifact-review capability",
            command->capability_label,
            "lc.receipt.artifact.review");
        failures += require_int("lc receipt-artifact-review no_effect", command->no_effect, 1);
        failures += require_int("lc receipt-artifact-review host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipt-review-receipt");
    failures += require_int("find lc receipt-review-receipt", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipt-review-receipt capability",
            command->capability_label,
            "lc.receipt.review.receipt");
        failures += require_int("lc receipt-review-receipt no_effect", command->no_effect, 1);
        failures += require_int("lc receipt-review-receipt host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipt-review-draft");
    failures += require_int("find lc receipt-review-draft", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipt-review-draft capability",
            command->capability_label,
            "lc.receipt.review.receipt.draft");
        failures += require_int("lc receipt-review-draft no_effect", command->no_effect, 1);
        failures += require_int("lc receipt-review-draft host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc receipt-materialization-plan");
    failures += require_int("find lc receipt-materialization-plan", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc receipt-materialization-plan capability",
            command->capability_label,
            "lc.receipt.materialization.plan");
        failures += require_int("lc receipt-materialization-plan no_effect", command->no_effect, 1);
        failures += require_int("lc receipt-materialization-plan host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc signature-request");
    failures += require_int("find lc signature-request", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc signature-request capability",
            command->capability_label,
            "lc.signature.request");
        failures += require_int("lc signature-request no_effect", command->no_effect, 1);
        failures += require_int("lc signature-request host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc os");
    failures += require_int("find lc os", command != 0, 1);
    if (command != 0) {
        failures += require_int("lc os future gate", command->requires_future_gate, 1);
        failures += require_int("lc os host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc os-contract");
    failures += require_int("find lc os-contract", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc os-contract capability",
            command->capability_label,
            "lc.os.contract");
        failures += require_int("lc os-contract future gate", command->requires_future_gate, 0);
        failures += require_int("lc os-contract host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc vm-evidence");
    failures += require_int("find lc vm-evidence", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc vm-evidence capability",
            command->capability_label,
            "lc.vm.evidence");
        failures += require_int("lc vm-evidence future gate", command->requires_future_gate, 0);
        failures += require_int("lc vm-evidence host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc host-contract");
    failures += require_int("find lc host-contract", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc host-contract capability",
            command->capability_label,
            "lc.host.contract");
        failures += require_int("lc host-contract future gate", command->requires_future_gate, 0);
        failures += require_int("lc host-contract host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc host-inventory");
    failures += require_int("find lc host-inventory", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc host-inventory capability",
            command->capability_label,
            "lc.host.inventory");
        failures += require_int("lc host-inventory future gate", command->requires_future_gate, 0);
        failures += require_int("lc host-inventory host launch", command->launches_host_process, 0);
    }

    command = latticra_console_find_command("lc host-adapter");
    failures += require_int("find lc host-adapter", command != 0, 1);
    if (command != 0) {
        failures += require_text(
            "lc host-adapter capability",
            command->capability_label,
            "lc.host.adapter");
        failures += require_int("lc host-adapter future gate", command->requires_future_gate, 0);
        failures += require_int("lc host-adapter host launch", command->launches_host_process, 0);
    }

    for (i = 0u; i < latticra_console_command_count(); ++i) {
        command = latticra_console_command_at(i);
        failures += require_int("command_at", command != 0, 1);
        if (command != 0) {
            failures += require_int("registry command no_effect", command->no_effect, 1);
            failures += require_int("registry command host launch", command->launches_host_process, 0);
        }
    }

    failures += require_int(
        "report",
        latticra_console_report(&result, report, sizeof(report)),
        LATTICRA_STATUS_OK);
    failures += require_contains("report", report, "LATTICRA CONSOLE REPORT");
    failures += require_contains("report", report, "short_name=LC");
    failures += require_contains("report", report, "component_key=latticra_console");
    failures += require_contains("report", report, "panel_installable=1");
    failures += require_contains("report", report, "standalone_installable=1");
    failures += require_contains("report", report, "standalone_requires_panel=0");
    failures += require_contains("report", report, "standalone_command_wrapper=latticra-lc");
    failures += require_contains("report", report, "standalone_console_status=metadata-only-standalone-contract-ready");
    failures += require_contains("report", report, "standalone_contract_present=1");
    failures += require_contains("report", report, "session_contract_status=metadata-only-contract-ready");
    failures += require_contains("report", report, "session_contract_present=1");
    failures += require_contains("report", report, "workspace_contract_status=metadata-only-contract-ready");
    failures += require_contains("report", report, "workspace_contract_present=1");
    failures += require_contains("report", report, "namespace_contract_status=metadata-only-contract-ready");
    failures += require_contains("report", report, "namespace_contract_present=1");
    failures += require_contains("report", report, "rootfs_contract_status=metadata-only-contract-ready");
    failures += require_contains("report", report, "rootfs_contract_present=1");
    failures += require_contains("report", report, "workspace_contract_status=metadata-only-contract-ready");
    failures += require_contains("report", report, "workspace_contract_present=1");
    failures += require_contains("report", report, "substrate_bridge_present=1");
    failures += require_contains("report", report, "host_embedding_contract_present=1");
    failures += require_contains("report", report, "host_inventory_contract_present=1");
    failures += require_contains("report", report, "host_adapter_contract_present=1");
    failures += require_contains("report", report, "receipt_request_contract_present=1");
    failures += require_contains("report", report, "receipt_payload_schema_present=1");
    failures += require_contains("report", report, "receipt_payload_artifact_draft_present=1");
    failures += require_contains("report", report, "receipt_payload_artifact_review_present=1");
    failures += require_contains("report", report, "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains("report", report, "receipt_payload_artifact_review_receipt_draft_present=1");
    failures += require_contains("report", report, "receipt_payload_materialization_plan_present=1");
    failures += require_contains("report", report, "signature_request_binding_present=1");
    failures += require_contains("report", report, "receipt_contract_present=1");
    failures += require_contains("report", report, "os_base_contract_present=1");
    failures += require_contains("report", report, "vm_evidence_contract_present=1");
    failures += require_contains(
        "report",
        report,
        "host_embedding_contract_status=metadata-only-contract-ready");
    failures += require_contains(
        "report",
        report,
        "host_inventory_contract_status=metadata-only-contract-ready");
    failures += require_contains(
        "report",
        report,
        "host_adapter_contract_status=metadata-only-contract-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_request_contract_status=metadata-only-contract-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_payload_schema_status=metadata-only-schema-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_payload_artifact_draft_status=metadata-only-draft-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_payload_artifact_review_status=metadata-only-review-gate-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_payload_artifact_review_receipt_status=metadata-only-receipt-contract-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_payload_artifact_review_receipt_draft_status=metadata-only-review-receipt-draft-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_payload_materialization_plan_status=metadata-only-plan-ready");
    failures += require_contains(
        "report",
        report,
        "signature_request_binding_status=metadata-only-contract-ready");
    failures += require_contains(
        "report",
        report,
        "receipt_contract_status=metadata-only-contract-ready");
    failures += require_contains(
        "report",
        report,
        "os_base_contract_status=metadata-only-contract-ready");
    failures += require_contains(
        "report",
        report,
        "vm_evidence_contract_status=metadata-only-contract-ready");
    failures += require_contains("report", report, "future_os_base_claim=planned_not_claimed");
    failures += require_contains("report", report, "phase1_reference_lessons=registry_help_guarded_boundary_os_track");
    failures += require_contains("report", report, "command_registry_source=c-static-table");
    failures += require_contains("report", report, "command_registry_no_effect=1");
    failures += require_contains("report", report, "runtime_boundary_bound=1");
    failures += require_contains("report", report, "seal_capability_labels_bound=1");
    failures += require_contains("report", report, "network_allowed=0");
    failures += require_contains("report", report, "boot_allowed=0");
    failures += require_contains("report", report, "os_base_enabled=0");
    failures += require_contains("report", report, "production_os_claim=0");

    failures += require_int(
        "registry_report",
        latticra_console_command_registry_report(registry_report, sizeof(registry_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "registry_report",
        registry_report,
        "LATTICRA CONSOLE COMMAND REGISTRY");
    failures += require_contains("registry_report", registry_report, "command=lc substrate");
    failures += require_contains("registry_report", registry_report, "command=lc host-contract");
    failures += require_contains("registry_report", registry_report, "capability=lc.host.contract");
    failures += require_contains("registry_report", registry_report, "command=lc host-inventory");
    failures += require_contains("registry_report", registry_report, "capability=lc.host.inventory");
    failures += require_contains("registry_report", registry_report, "command=lc host-adapter");
    failures += require_contains("registry_report", registry_report, "capability=lc.host.adapter");
    failures += require_contains("registry_report", registry_report, "command=lc receipts");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipts.inspect");
    failures += require_contains("registry_report", registry_report, "command=lc receipt-request");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipt.request");
    failures += require_contains("registry_report", registry_report, "command=lc receipt-payload");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipt.payload");
    failures += require_contains("registry_report", registry_report, "command=lc receipt-artifact");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipt.artifact");
    failures += require_contains("registry_report", registry_report, "command=lc receipt-artifact-review");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipt.artifact.review");
    failures += require_contains("registry_report", registry_report, "command=lc receipt-review-receipt");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipt.review.receipt");
    failures += require_contains("registry_report", registry_report, "command=lc receipt-review-draft");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipt.review.receipt.draft");
    failures += require_contains("registry_report", registry_report, "command=lc receipt-materialization-plan");
    failures += require_contains("registry_report", registry_report, "capability=lc.receipt.materialization.plan");
    failures += require_contains("registry_report", registry_report, "command=lc signature-request");
    failures += require_contains("registry_report", registry_report, "capability=lc.signature.request");
    failures += require_contains("registry_report", registry_report, "command=lc os-contract");
    failures += require_contains("registry_report", registry_report, "capability=lc.os.contract");
    failures += require_contains("registry_report", registry_report, "command=lc vm-evidence");
    failures += require_contains("registry_report", registry_report, "capability=lc.vm.evidence");
    failures += require_contains("registry_report", registry_report, "command=lc profiles");
    failures += require_contains("registry_report", registry_report, "capability=lc.core.profiles");
    failures += require_contains("registry_report", registry_report, "command=lc install-config");
    failures += require_contains("registry_report", registry_report, "command=lc standalone");
    failures += require_contains("registry_report", registry_report, "command=lc session");
    failures += require_contains("registry_report", registry_report, "capability=lc.session.contract");
    failures += require_contains("registry_report", registry_report, "command=lc workspace");
    failures += require_contains("registry_report", registry_report, "capability=lc.workspace.contract");
    failures += require_contains("registry_report", registry_report, "command=lc namespace");
    failures += require_contains("registry_report", registry_report, "capability=lc.namespace.contract");
    failures += require_contains("registry_report", registry_report, "command=lc rootfs");
    failures += require_contains("registry_report", registry_report, "capability=lc.rootfs.contract");
    failures += require_contains("registry_report", registry_report, "capability=lc.install.config");
    failures += require_contains("registry_report", registry_report, "capability=lc.substrate.inspect");
    failures += require_contains("registry_report", registry_report, "launches_host_process=0");
    failures += require_contains("registry_report", registry_report, "requires_future_gate=1");

    failures += require_int(
        "help_report",
        latticra_console_help_report(help_report, sizeof(help_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains("help_report", help_report, "LATTICRA CONSOLE HELP");
    failures += require_contains("help_report", help_report, "registry_source=c-static-table");
    failures += require_contains("help_report", help_report, "lc substrate");
    failures += require_contains("help_report", help_report, "lc install-config");
    failures += require_contains("help_report", help_report, "lc standalone");
    failures += require_contains("help_report", help_report, "lc session");
    failures += require_contains("help_report", help_report, "lc workspace");
    failures += require_contains("help_report", help_report, "lc namespace");
    failures += require_contains("help_report", help_report, "lc rootfs");
    failures += require_contains("help_report", help_report, "lc host-contract");
    failures += require_contains("help_report", help_report, "lc host-inventory");
    failures += require_contains("help_report", help_report, "lc host-adapter");
    failures += require_contains("help_report", help_report, "lc receipts");
    failures += require_contains("help_report", help_report, "lc receipt-request");
    failures += require_contains("help_report", help_report, "lc receipt-payload");
    failures += require_contains("help_report", help_report, "lc receipt-artifact");
    failures += require_contains("help_report", help_report, "lc receipt-artifact-review");
    failures += require_contains("help_report", help_report, "lc receipt-review-receipt");
    failures += require_contains("help_report", help_report, "lc receipt-review-draft");
    failures += require_contains("help_report", help_report, "lc receipt-materialization-plan");
    failures += require_contains("help_report", help_report, "lc signature-request");
    failures += require_contains("help_report", help_report, "lc os-contract");
    failures += require_contains("help_report", help_report, "lc vm-evidence");
    failures += require_contains("help_report", help_report, "capability=lc.substrate.inspect");
    failures += require_contains("help_report", help_report, "host_process_launch_allowed=0");

    failures += require_int(
        "manpage_report",
        latticra_console_manpage_report(manpage_report, sizeof(manpage_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains("manpage_report", manpage_report, "LATTICRA-CONSOLE(1)");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc - Latticra Console");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc install-config");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc standalone");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc session");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc workspace");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc namespace");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc rootfs");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc host-contract");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc host-inventory");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc host-adapter");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipts");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipt-request");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipt-payload");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipt-artifact");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipt-artifact-review");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipt-review-receipt");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipt-review-draft");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc receipt-materialization-plan");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc signature-request");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc os-contract");
    failures += require_contains("manpage_report", manpage_report, "latticra-lc vm-evidence");
    failures += require_contains("manpage_report", manpage_report, "lc os");
    failures += require_contains("manpage_report", manpage_report, "production_os_claim=0");

    command = latticra_console_find_command("lc substrate");
    failures += require_int(
        "lc substrate boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc substrate seal capability",
        boundary.seal_capability_label,
        "seal.capability.inspect");
    failures += require_int(
        "lc substrate runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc substrate boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc substrate boundary no effect", boundary.no_effect, 1);

    command = latticra_console_find_command("lc install-config");
    failures += require_int(
        "lc install-config boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc install-config seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc install-config runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc install-config boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc install-config boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc install-config boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc standalone");
    failures += require_int(
        "lc standalone boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc standalone seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc standalone runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc standalone boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc standalone boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc standalone boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc session");
    failures += require_int(
        "lc session boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc session seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc session runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc session boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc session boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc session boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc workspace");
    failures += require_int(
        "lc workspace boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc workspace seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc workspace runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc workspace boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc workspace boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc workspace boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc namespace");
    failures += require_int(
        "lc namespace boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc namespace seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc namespace runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc namespace boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc namespace boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc namespace boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc rootfs");
    failures += require_int(
        "lc rootfs boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc rootfs seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc rootfs runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc rootfs boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc rootfs boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc rootfs boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc host-contract");
    failures += require_int(
        "lc host-contract boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc host-contract seal capability",
        boundary.seal_capability_label,
        "seal.capability.inspect");
    failures += require_int(
        "lc host-contract runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int(
        "lc host-contract boundary future gate",
        boundary.requires_future_gate,
        0);
    failures += require_int("lc host-contract boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc host-contract boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc host-inventory");
    failures += require_int(
        "lc host-inventory boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc host-inventory seal capability",
        boundary.seal_capability_label,
        "seal.capability.inspect");
    failures += require_int(
        "lc host-inventory runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int(
        "lc host-inventory boundary future gate",
        boundary.requires_future_gate,
        0);
    failures += require_int("lc host-inventory boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc host-inventory boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc host-adapter");
    failures += require_int(
        "lc host-adapter boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc host-adapter seal capability",
        boundary.seal_capability_label,
        "seal.capability.inspect");
    failures += require_int(
        "lc host-adapter runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc host-adapter boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc host-adapter boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc host-adapter boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc receipts");
    failures += require_int(
        "lc receipts boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipts seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipts runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipts boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipts boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc receipts boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc receipt-request");
    failures += require_int(
        "lc receipt-request boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipt-request seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipt-request runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipt-request boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipt-request boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc receipt-request boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc receipt-payload");
    failures += require_int(
        "lc receipt-payload boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipt-payload seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipt-payload runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipt-payload boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipt-payload boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc receipt-payload boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc receipt-artifact");
    failures += require_int(
        "lc receipt-artifact boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipt-artifact seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipt-artifact runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipt-artifact boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipt-artifact boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc receipt-artifact boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc receipt-artifact-review");
    failures += require_int(
        "lc receipt-artifact-review boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipt-artifact-review seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipt-artifact-review runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipt-artifact-review boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipt-artifact-review boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc receipt-artifact-review boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc receipt-review-receipt");
    failures += require_int(
        "lc receipt-review-receipt boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipt-review-receipt seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipt-review-receipt runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipt-review-receipt boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipt-review-receipt boundary no effect", boundary.no_effect, 1);
    failures += require_int(
        "lc receipt-review-receipt boundary host mutation allowed",
        boundary.host_mutation_allowed,
        0);

    command = latticra_console_find_command("lc receipt-review-draft");
    failures += require_int(
        "lc receipt-review-draft boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipt-review-draft seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipt-review-draft runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipt-review-draft boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipt-review-draft boundary no effect", boundary.no_effect, 1);
    failures += require_int(
        "lc receipt-review-draft boundary host mutation allowed",
        boundary.host_mutation_allowed,
        0);

    command = latticra_console_find_command("lc receipt-materialization-plan");
    failures += require_int(
        "lc receipt-materialization-plan boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc receipt-materialization-plan seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc receipt-materialization-plan runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc receipt-materialization-plan boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc receipt-materialization-plan boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc receipt-materialization-plan boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc signature-request");
    failures += require_int(
        "lc signature-request boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc signature-request seal capability",
        boundary.seal_capability_label,
        "seal.capability.report");
    failures += require_int(
        "lc signature-request runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc signature-request boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc signature-request boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc signature-request boundary host mutation allowed", boundary.host_mutation_allowed, 0);

    command = latticra_console_find_command("lc os-contract");
    failures += require_int(
        "lc os-contract boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc os-contract seal capability",
        boundary.seal_capability_label,
        "seal.capability.inspect");
    failures += require_int(
        "lc os-contract runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc os-contract boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc os-contract boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc os-contract boundary boot allowed", boundary.boot_allowed, 0);

    command = latticra_console_find_command("lc vm-evidence");
    failures += require_int(
        "lc vm-evidence boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc vm-evidence seal capability",
        boundary.seal_capability_label,
        "seal.capability.inspect");
    failures += require_int(
        "lc vm-evidence runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK);
    failures += require_int("lc vm-evidence boundary future gate", boundary.requires_future_gate, 0);
    failures += require_int("lc vm-evidence boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc vm-evidence boundary boot allowed", boundary.boot_allowed, 0);

    command = latticra_console_find_command("lc os");
    failures += require_int(
        "lc os boundary",
        latticra_console_command_boundary_classify(command, &boundary),
        LATTICRA_STATUS_OK);
    failures += require_text(
        "lc os seal capability",
        boundary.seal_capability_label,
        "seal.capability.inspect");
    failures += require_int(
        "lc os runtime kind",
        boundary.runtime_request_kind,
        LATTICRA_RUNTIME_BOUNDARY_BOOT_ACTION);
    failures += require_int("lc os boundary future gate", boundary.requires_future_gate, 1);
    failures += require_int("lc os boundary no effect", boundary.no_effect, 1);
    failures += require_int("lc os boundary boot allowed", boundary.boot_allowed, 0);

    failures += require_int(
        "boundary_report",
        latticra_console_command_boundary_report(boundary_report, sizeof(boundary_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "boundary_report",
        boundary_report,
        "LATTICRA CONSOLE COMMAND BOUNDARY REPORT");
    failures += require_contains("boundary_report", boundary_report, "runtime_boundary_bound=1");
    failures += require_contains("boundary_report", boundary_report, "seal_capability_labels_bound=1");
    failures += require_contains("boundary_report", boundary_report, "command=lc substrate");
    failures += require_contains("boundary_report", boundary_report, "command=lc install-config");
    failures += require_contains("boundary_report", boundary_report, "command=lc standalone");
    failures += require_contains("boundary_report", boundary_report, "command=lc session");
    failures += require_contains("boundary_report", boundary_report, "command=lc workspace");
    failures += require_contains("boundary_report", boundary_report, "command=lc namespace");
    failures += require_contains("boundary_report", boundary_report, "command=lc rootfs");
    failures += require_contains("boundary_report", boundary_report, "command=lc host-contract");
    failures += require_contains("boundary_report", boundary_report, "command=lc host-inventory");
    failures += require_contains("boundary_report", boundary_report, "command=lc host-adapter");
    failures += require_contains("boundary_report", boundary_report, "command=lc receipts");
    failures += require_contains("boundary_report", boundary_report, "command=lc receipt-request");
    failures += require_contains("boundary_report", boundary_report, "command=lc receipt-payload");
    failures += require_contains("boundary_report", boundary_report, "command=lc receipt-artifact");
    failures += require_contains("boundary_report", boundary_report, "command=lc receipt-artifact-review");
    failures += require_contains("boundary_report", boundary_report, "command=lc receipt-review-receipt");
    failures += require_contains("boundary_report", boundary_report, "command=lc receipt-materialization-plan");
    failures += require_contains("boundary_report", boundary_report, "command=lc signature-request");
    failures += require_contains("boundary_report", boundary_report, "runtime_request=authority-check");
    failures += require_contains("boundary_report", boundary_report, "command=lc os-contract");
    failures += require_contains("boundary_report", boundary_report, "command=lc vm-evidence");
    failures += require_contains("boundary_report", boundary_report, "command=lc os");
    failures += require_contains("boundary_report", boundary_report, "runtime_request=future-gated");
    failures += require_contains("boundary_report", boundary_report, "policy_matrix_cell=future-gated-operation");
    failures += require_contains("boundary_report", boundary_report, "seal_capability=seal.capability.inspect");
    failures += require_contains("boundary_report", boundary_report, "network_allowed=0");
    failures += require_contains("boundary_report", boundary_report, "boot_allowed=0");

    for (i = 0u; i < latticra_console_command_count(); ++i) {
        command = latticra_console_command_at(i);
        failures += require_int(
            "command boundary network classify",
            latticra_console_command_boundary_classify(command, &boundary),
            LATTICRA_STATUS_OK);
        failures += require_int("command boundary network denied", boundary.network_allowed, 0);
        failures += require_int(
            "command boundary runtime enforcement denied",
            boundary.runtime_enforcement_allowed,
            0);
    }

    failures += require_int(
        "standalone_contract_report",
        latticra_console_standalone_contract_report(standalone_contract_report, sizeof(standalone_contract_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "standalone_contract_report",
        standalone_contract_report,
        "LATTICRA CONSOLE STANDALONE CONTRACT");
    failures += require_contains(
        "standalone_contract_report",
        standalone_contract_report,
        "standalone_console_profile=lc-standalone-console-v0");
    failures += require_contains(
        "standalone_contract_report",
        standalone_contract_report,
        "standalone_requires_panel=0");
    failures += require_contains(
        "standalone_contract_report",
        standalone_contract_report,
        "command_surface=lc standalone");
    failures += require_contains(
        "standalone_contract_report",
        standalone_contract_report,
        "host_process_launch_allowed=0");
    failures += require_contains(
        "standalone_contract_report",
        standalone_contract_report,
        "production_os_claim=0");

    failures += require_int(
        "session_contract_report",
        latticra_console_session_contract_report(session_contract_report, sizeof(session_contract_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "session_contract_report",
        session_contract_report,
        "LATTICRA CONSOLE SESSION CONTRACT");
    failures += require_contains(
        "session_contract_report",
        session_contract_report,
        "session_profile=lc-session-v0");
    failures += require_contains(
        "session_contract_report",
        session_contract_report,
        "runtime_session_created=0");
    failures += require_contains(
        "session_contract_report",
        session_contract_report,
        "runtime_process_spawn_allowed=0");
    failures += require_contains(
        "session_contract_report",
        session_contract_report,
        "command_surface=lc session");
    failures += require_contains(
        "session_contract_report",
        session_contract_report,
        "host_process_launch_allowed=0");
    failures += require_contains(
        "session_contract_report",
        session_contract_report,
        "production_os_claim=0");

    failures += require_int(
        "workspace_contract_report",
        latticra_console_workspace_contract_report(workspace_contract_report, sizeof(workspace_contract_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "LATTICRA CONSOLE WORKSPACE CONTRACT");
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "workspace_profile=lc-workspace-v0");
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "workspace_contract_present=1");
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "workspace_mount_allowed=0");
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "workspace_file_write_allowed=0");
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "command_surface=lc workspace");
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "host_process_launch_allowed=0");
    failures += require_contains(
        "workspace_contract_report",
        workspace_contract_report,
        "production_os_claim=0");

    failures += require_int(
        "namespace_contract_report",
        latticra_console_namespace_contract_report(namespace_contract_report, sizeof(namespace_contract_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "LATTICRA CONSOLE NAMESPACE CONTRACT");
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "namespace_profile=lc-namespace-v0");
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "namespace_contract_present=1");
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "namespace_mount_allowed=0");
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "rootfs_mount_allowed=0");
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "command_surface=lc namespace");
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "host_process_launch_allowed=0");
    failures += require_contains(
        "namespace_contract_report",
        namespace_contract_report,
        "production_os_claim=0");

    failures += require_int(
        "rootfs_contract_report",
        latticra_console_rootfs_contract_report(rootfs_contract_report, sizeof(rootfs_contract_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "LATTICRA CONSOLE ROOTFS CONTRACT");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "rootfs_profile=lc-rootfs-v0");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "rootfs_contract_present=1");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "rootfs_image_create_allowed=0");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "rootfs_mount_allowed=0");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "rootfs_package_install_allowed=0");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "command_surface=lc rootfs");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "host_process_launch_allowed=0");
    failures += require_contains(
        "rootfs_contract_report",
        rootfs_contract_report,
        "production_os_claim=0");

    failures += require_int(
        "host_contract_report",
        latticra_console_host_contract_report(host_contract_report, sizeof(host_contract_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "host_contract_report",
        host_contract_report,
        "LATTICRA CONSOLE HOST EMBEDDING CONTRACT");
    failures += require_contains(
        "host_contract_report",
        host_contract_report,
        "contract_profile=lc-host-embedding-v0");
    failures += require_contains(
        "host_contract_report",
        host_contract_report,
        "host_process_launch_allowed=0");
    failures += require_contains(
        "host_contract_report",
        host_contract_report,
        "host_file_read_allowed=0");
    failures += require_contains(
        "host_contract_report",
        host_contract_report,
        "promotion_gate=contract_receipt_and_read_only_host_inventory");

    failures += require_int(
        "host_inventory_report",
        latticra_console_host_inventory_report(host_inventory_report, sizeof(host_inventory_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "host_inventory_report",
        host_inventory_report,
        "LATTICRA CONSOLE READ-ONLY HOST INVENTORY CONTRACT");
    failures += require_contains(
        "host_inventory_report",
        host_inventory_report,
        "contract_profile=lc-host-inventory-v0");
    failures += require_contains(
        "host_inventory_report",
        host_inventory_report,
        "inventory_performed=0");
    failures += require_contains(
        "host_inventory_report",
        host_inventory_report,
        "host_probe_allowed=0");
    failures += require_contains(
        "host_inventory_report",
        host_inventory_report,
        "host_file_read_allowed=0");
    failures += require_contains(
        "host_inventory_report",
        host_inventory_report,
        "promotion_gate=host_inventory_contract_receipt_before_host_adapter");

    failures += require_int(
        "host_adapter_report",
        latticra_console_host_adapter_report(host_adapter_report, sizeof(host_adapter_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "host_adapter_report",
        host_adapter_report,
        "LATTICRA CONSOLE HOST ADAPTER CONTRACT");
    failures += require_contains(
        "host_adapter_report",
        host_adapter_report,
        "contract_profile=lc-host-adapter-v0");
    failures += require_contains(
        "host_adapter_report",
        host_adapter_report,
        "host_adapter_enabled=0");
    failures += require_contains(
        "host_adapter_report",
        host_adapter_report,
        "host_process_launch_allowed=0");
    failures += require_contains(
        "host_adapter_report",
        host_adapter_report,
        "host_file_read_allowed=0");
    failures += require_contains(
        "host_adapter_report",
        host_adapter_report,
        "promotion_gate=host_adapter_contract_receipts_and_inventory");

    failures += require_int(
        "receipt_request_report",
        latticra_console_receipt_request_report(receipt_request_report, sizeof(receipt_request_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "LATTICRA CONSOLE SEAL RECEIPT REQUEST CONTRACT");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "request_profile=lc-receipt-request-v0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_schema_profile=lc-receipt-payload-schema-v0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_draft_command=lc receipt-artifact");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_review_present=1");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_review_command=lc receipt-artifact-review");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_review_receipt_required=1");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "draft_review_receipt_present=0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "materialization_preconditions_met=0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "materialization_allowed=0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "payload_artifact_present=0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "signature_request_binding_profile=lc-signature-request-binding-v0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "signature_request_profile=latticra-seal-signature-request/0.1");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "requested_receipt_profile=latticra-seal-verified-receipt/0.1");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "seal_signature_request_present=0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "receipt_write_allowed=0");
    failures += require_contains(
        "receipt_request_report",
        receipt_request_report,
        "promotion_gate=lc_receipt_request_review_before_signing");

    failures += require_int(
        "receipt_payload_schema_report",
        latticra_console_receipt_payload_schema_report(
            receipt_payload_schema_report,
            sizeof(receipt_payload_schema_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "LATTICRA CONSOLE RECEIPT PAYLOAD SCHEMA");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "schema_profile=lc-receipt-payload-schema-v0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "payload_fields=console_id,profile,command_registry");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "payload_artifact_present=0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_artifact_draft_command=lc receipt-artifact");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_artifact_review_command=lc receipt-artifact-review");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "materialization_preconditions_met=0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "materialization_allowed=0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "signature_request_binding_allowed=0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "signature_request_binding_contract_present=1");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "receipt_write_allowed=0");
    failures += require_contains(
        "receipt_payload_schema_report",
        receipt_payload_schema_report,
        "promotion_gate=lc_receipt_payload_schema_before_signature_request_binding");

    failures += require_int(
        "receipt_payload_artifact_draft_report",
        latticra_console_receipt_payload_artifact_draft_report(
            receipt_payload_artifact_draft_report,
            sizeof(receipt_payload_artifact_draft_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT DRAFT");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "draft_profile=lc-receipt-payload-artifact-draft-v0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "draft_contract_present=1");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "related_review_command=lc receipt-artifact-review");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "related_materialization_plan_command=lc receipt-materialization-plan");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "draft_review_receipt_present=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "materialization_preconditions_met=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "materialization_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "payload_artifact_present=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "payload_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "payload_hash_computed=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "payload_path_recorded=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "signature_request_binding_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "seal_signature_request_ready=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "receipt_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "command_surface=lc receipt-artifact");
    failures += require_contains(
        "receipt_payload_artifact_draft_report",
        receipt_payload_artifact_draft_report,
        "promotion_gate=lc_receipt_payload_artifact_draft_before_materialization_and_signature_request");

    failures += require_int(
        "receipt_payload_artifact_review_report",
        latticra_console_receipt_payload_artifact_review_report(
            receipt_payload_artifact_review_report,
            sizeof(receipt_payload_artifact_review_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT REVIEW GATE");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "review_profile=lc-receipt-payload-artifact-review-v0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_payload_artifact_draft_present=1");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_payload_artifact_review_receipt_required=1");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "materialization_preconditions_met=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "draft_review_present=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "draft_review_receipt_present=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "materialization_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "payload_artifact_present=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "payload_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "signature_request_binding_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "seal_signature_request_ready=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "receipt_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "command_surface=lc receipt-artifact-review");
    failures += require_contains(
        "receipt_payload_artifact_review_report",
        receipt_payload_artifact_review_report,
        "promotion_gate=lc_receipt_payload_artifact_review_before_materialization");

    failures += require_int(
        "receipt_payload_artifact_review_receipt_report",
        latticra_console_receipt_payload_artifact_review_receipt_report(
            receipt_payload_artifact_review_receipt_report,
            sizeof(receipt_payload_artifact_review_receipt_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT REVIEW RECEIPT CONTRACT");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "draft_review_receipt_present=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "draft_review_receipt_artifact_present=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "draft_review_receipt_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "draft_review_receipt_signed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "materialization_preconditions_met=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "materialization_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "payload_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "signature_request_binding_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "receipt_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "command_surface=lc receipt-review-receipt");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_report",
        receipt_payload_artifact_review_receipt_report,
        "promotion_gate=lc_receipt_payload_artifact_review_receipt_before_materialization_preconditions");

    failures += require_int(
        "receipt_payload_artifact_review_receipt_draft_report",
        latticra_console_receipt_payload_artifact_review_receipt_draft_report(
            receipt_payload_artifact_review_receipt_draft_report,
            sizeof(receipt_payload_artifact_review_receipt_draft_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_draft_report",
        receipt_payload_artifact_review_receipt_draft_report,
        "LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT REVIEW RECEIPT DRAFT CONTRACT");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_draft_report",
        receipt_payload_artifact_review_receipt_draft_report,
        "review_receipt_draft_profile=lc-receipt-payload-artifact-review-receipt-draft-v0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_draft_report",
        receipt_payload_artifact_review_receipt_draft_report,
        "draft_review_receipt_write_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_draft_report",
        receipt_payload_artifact_review_receipt_draft_report,
        "review_receipt_materialization_allowed=0");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_draft_report",
        receipt_payload_artifact_review_receipt_draft_report,
        "command_surface=lc receipt-review-draft");
    failures += require_contains(
        "receipt_payload_artifact_review_receipt_draft_report",
        receipt_payload_artifact_review_receipt_draft_report,
        "promotion_gate=lc_receipt_payload_artifact_review_receipt_draft_before_review_receipt_creation");

    failures += require_int(
        "receipt_payload_materialization_plan_report",
        latticra_console_receipt_payload_materialization_plan_report(
            receipt_payload_materialization_plan_report,
            sizeof(receipt_payload_materialization_plan_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "LATTICRA CONSOLE RECEIPT PAYLOAD MATERIALIZATION PLAN");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "materialization_plan_profile=lc-receipt-payload-materialization-plan-v0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "receipt_payload_artifact_review_receipt_required=1");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "draft_review_receipt_required=1");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "draft_review_receipt_present=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "materialization_preconditions_met=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "materialization_allowed=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "payload_artifact_present=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "payload_write_allowed=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "payload_file_open_allowed=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "signature_request_binding_allowed=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "receipt_write_allowed=0");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "command_surface=lc receipt-materialization-plan");
    failures += require_contains(
        "receipt_payload_materialization_plan_report",
        receipt_payload_materialization_plan_report,
        "promotion_gate=lc_receipt_payload_materialization_plan_after_review_receipt");

    failures += require_int(
        "signature_request_binding_report",
        latticra_console_signature_request_binding_report(
            signature_request_binding_report,
            sizeof(signature_request_binding_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "LATTICRA CONSOLE SIGNATURE REQUEST BINDING CONTRACT");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "binding_profile=lc-signature-request-binding-v0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_schema_profile=lc-receipt-payload-schema-v0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_artifact_draft_present=1");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_artifact_review_present=1");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_artifact_review_receipt_required=1");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_payload_materialization_plan_present=1");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "draft_review_receipt_present=0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "materialization_preconditions_met=0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "materialization_allowed=0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "signing_authorization_profile=latticra-seal-signing-authorization/0.1");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "signature_request_binding_artifact_present=0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "seal_signature_request_ready=0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "seal_signing_authority_present=0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "receipt_write_allowed=0");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "required_surfaces=receipt-request,receipt-payload-schema,receipt-payload-artifact-draft,receipt-payload-artifact-review,receipt-payload-artifact-review-receipt,receipt-payload-artifact-review-receipt-draft,receipt-payload-materialization-plan,receipt-contract,runtime-boundary,seal-capability-labels");
    failures += require_contains(
        "signature_request_binding_report",
        signature_request_binding_report,
        "promotion_gate=lc_signature_request_binding_after_payload_artifact_and_signing_authority");

    failures += require_int(
        "receipt_report",
        latticra_console_receipt_report(receipt_report, sizeof(receipt_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "LATTICRA CONSOLE RECEIPT CONTRACT");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_profile=lc-receipts-v0");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "host_inventory_contract_receipt_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "host_adapter_contract_receipt_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "session_contract_receipt_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "session_contract_command=lc session");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "workspace_contract_receipt_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "workspace_contract_present=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "workspace_contract_command=lc workspace");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "namespace_contract_receipt_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "namespace_contract_present=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "namespace_contract_command=lc namespace");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "rootfs_contract_receipt_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "rootfs_contract_present=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "rootfs_contract_command=lc rootfs");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_request_contract_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_payload_schema_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_payload_artifact_draft_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_payload_artifact_review_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_payload_artifact_review_receipt_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_payload_artifact_review_receipt_present=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_payload_materialization_plan_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "signature_request_binding_required=1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "signature_request_profile=latticra-seal-signature-request/0.1");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "seal_signature_present=0");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_signed=0");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "receipt_surfaces=profile,session,workspace,namespace,rootfs,host-contract,host-inventory,host-adapter,runtime-boundary");
    failures += require_contains(
        "receipt_report",
        receipt_report,
        "promotion_gate=lc_receipts_before_host_adapter_or_os_base");

    failures += require_int(
        "os_contract_report",
        latticra_console_os_contract_report(os_contract_report, sizeof(os_contract_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "os_contract_report",
        os_contract_report,
        "LATTICRA CONSOLE OS-BASE PLANNING CONTRACT");
    failures += require_contains(
        "os_contract_report",
        os_contract_report,
        "contract_profile=lc-os-base-v0");
    failures += require_contains(
        "os_contract_report",
        os_contract_report,
        "boot_authority_present=0");
    failures += require_contains(
        "os_contract_report",
        os_contract_report,
        "kernel_change_allowed=0");
    failures += require_contains(
        "os_contract_report",
        os_contract_report,
        "vm_evidence_contract_required=1");
    failures += require_contains(
        "os_contract_report",
        os_contract_report,
        "vm_evidence_required=1");
    failures += require_contains(
        "os_contract_report",
        os_contract_report,
        "promotion_gate=os_base_contract_receipt_and_vm_evidence");

    failures += require_int(
        "vm_evidence_report",
        latticra_console_vm_evidence_report(vm_evidence_report, sizeof(vm_evidence_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "vm_evidence_report",
        vm_evidence_report,
        "LATTICRA CONSOLE VM EVIDENCE CONTRACT");
    failures += require_contains(
        "vm_evidence_report",
        vm_evidence_report,
        "contract_profile=lc-vm-evidence-v0");
    failures += require_contains(
        "vm_evidence_report",
        vm_evidence_report,
        "vm_launch_allowed=0");
    failures += require_contains(
        "vm_evidence_report",
        vm_evidence_report,
        "hypervisor_access_allowed=0");
    failures += require_contains(
        "vm_evidence_report",
        vm_evidence_report,
        "disk_image_write_allowed=0");
    failures += require_contains(
        "vm_evidence_report",
        vm_evidence_report,
        "promotion_gate=vm_evidence_contract_before_boot_adjacency");

    if (failures != 0) return 1;
    puts("latticra_console_foundation: ok");
    return 0;
}
