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
    size_t i;
    char report[LATTICRA_CONSOLE_REPORT_MAX];
    char registry_report[LATTICRA_CONSOLE_COMMAND_REGISTRY_REPORT_MAX];
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
        "result.substrate_bridge_status",
        result.substrate_bridge_status,
        "metadata-bound-ready");
    failures += require_text(
        "result.os_base_status",
        result.os_base_status,
        "planned-no-boot-authority");
    failures += require_int("result.no_effect", result.no_effect, 1);
    failures += require_int("result.configurable", result.configurable, 1);
    failures += require_int("result.panel_installable", result.panel_installable, 1);
    failures += require_int("result.command_registry_present", result.command_registry_present, 1);
    failures += require_int("result.substrate_bridge_present", result.substrate_bridge_present, 1);
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
    failures += require_int("command_count_min", result.command_count >= 13u, 1);

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

    command = latticra_console_find_command("lc os");
    failures += require_int("find lc os", command != 0, 1);
    if (command != 0) {
        failures += require_int("lc os future gate", command->requires_future_gate, 1);
        failures += require_int("lc os host launch", command->launches_host_process, 0);
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
    failures += require_contains("report", report, "substrate_bridge_present=1");
    failures += require_contains("report", report, "future_os_base_claim=planned_not_claimed");
    failures += require_contains("report", report, "phase1_reference_lessons=registry_help_guarded_boundary_os_track");
    failures += require_contains("report", report, "command_registry_source=c-static-table");
    failures += require_contains("report", report, "command_registry_no_effect=1");
    failures += require_contains("report", report, "network_allowed=0");
    failures += require_contains("report", report, "boot_allowed=0");

    failures += require_int(
        "registry_report",
        latticra_console_command_registry_report(registry_report, sizeof(registry_report)),
        LATTICRA_STATUS_OK);
    failures += require_contains(
        "registry_report",
        registry_report,
        "LATTICRA CONSOLE COMMAND REGISTRY");
    failures += require_contains("registry_report", registry_report, "command=lc substrate");
    failures += require_contains("registry_report", registry_report, "capability=lc.substrate.inspect");
    failures += require_contains("registry_report", registry_report, "launches_host_process=0");
    failures += require_contains("registry_report", registry_report, "requires_future_gate=1");

    if (failures != 0) return 1;
    puts("latticra_console_foundation: ok");
    return 0;
}
