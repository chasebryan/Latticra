#include "latticra/latticra_console.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static const latticra_console_command_t lc_commands[] = {
    {
        "help",
        "help",
        "Show the registry-backed LC command map.",
        "lc.core.help",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "status",
        "status",
        "Report LC identity, profile, and authority posture.",
        "lc.core.status",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "plan",
        "plan",
        "Refresh the Panel install plan view.",
        "lc.panel.plan",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA,
        1,
        1,
        0,
        0
    },
    {
        "save",
        "save",
        "Write Panel configuration metadata through the guarded Panel path.",
        "lc.panel.save",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA,
        1,
        1,
        0,
        0
    },
    {
        "dry-run",
        "dry-run",
        "Launch the Panel dry-install engine for evidence collection.",
        "lc.panel.dry_run",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA,
        1,
        1,
        0,
        0
    },
    {
        "reset",
        "reset",
        "Run the guarded Panel reset workflow.",
        "lc.panel.reset",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA,
        1,
        1,
        0,
        0
    },
    {
        "uninstall",
        "uninstall",
        "Run the guarded Panel uninstall workflow.",
        "lc.panel.uninstall",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA,
        1,
        1,
        0,
        0
    },
    {
        "clear",
        "clear",
        "Clear the embedded Panel console transcript.",
        "lc.panel.clear",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA,
        1,
        1,
        0,
        0
    },
    {
        "lc status",
        "lc status",
        "Report LC component metadata from the Panel console.",
        "lc.core.status",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc commands",
        "lc commands",
        "Show the LC seed command registry.",
        "lc.core.registry",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc install-config",
        "lc install-config",
        "Report LC install configuration metadata from the Panel console.",
        "lc.install.config",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc profiles",
        "lc profiles",
        "Show installed LC configuration profile presets.",
        "lc.core.profiles",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc receipts",
        "lc receipts",
        "Inspect LC profile and contract receipt requirements without signing.",
        "lc.receipts.inspect",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc receipt-request",
        "lc receipt-request",
        "Inspect the metadata-only Seal receipt request contract without signing.",
        "lc.receipt.request",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc receipt-payload",
        "lc receipt-payload",
        "Inspect the metadata-only LC receipt payload schema before Seal binding.",
        "lc.receipt.payload",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc receipt-artifact",
        "lc receipt-artifact",
        "Inspect the no-write LC receipt payload artifact draft before materialization.",
        "lc.receipt.artifact",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc receipt-artifact-review",
        "lc receipt-artifact-review",
        "Inspect the metadata-only review gate before LC receipt payload artifact materialization.",
        "lc.receipt.artifact.review",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc receipt-materialization-plan",
        "lc receipt-materialization-plan",
        "Inspect the metadata-only LC receipt payload materialization plan before writes exist.",
        "lc.receipt.materialization.plan",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc signature-request",
        "lc signature-request",
        "Inspect the metadata-only LC binding contract for a future Seal signature request.",
        "lc.signature.request",
        LATTICRA_CONSOLE_COMMAND_CORE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc substrate",
        "lc substrate",
        "Inspect the metadata bridge to Lat, LIR, Nucleus, Runtime Boundary, and Seal.",
        "lc.substrate.inspect",
        LATTICRA_CONSOLE_COMMAND_SUBSTRATE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc host",
        "lc host",
        "Inspect future host-embedding posture without host access.",
        "lc.host.inspect",
        LATTICRA_CONSOLE_COMMAND_HOST,
        LATTICRA_CONSOLE_COMMAND_EFFECT_FUTURE_GATED,
        1,
        1,
        0,
        1
    },
    {
        "lc host-contract",
        "lc host-contract",
        "Inspect the no-effect host-embedding contract before any host integration.",
        "lc.host.contract",
        LATTICRA_CONSOLE_COMMAND_HOST,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc host-inventory",
        "lc host-inventory",
        "Inspect the read-only host inventory contract without reading the host.",
        "lc.host.inventory",
        LATTICRA_CONSOLE_COMMAND_HOST,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc host-adapter",
        "lc host-adapter",
        "Inspect the no-effect host adapter contract before Host embedding.",
        "lc.host.adapter",
        LATTICRA_CONSOLE_COMMAND_HOST,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc os-contract",
        "lc os-contract",
        "Inspect the no-effect OS-base planning contract before boot work.",
        "lc.os.contract",
        LATTICRA_CONSOLE_COMMAND_OS_BASE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc vm-evidence",
        "lc vm-evidence",
        "Inspect the no-effect VM evidence contract before OS-base promotion.",
        "lc.vm.evidence",
        LATTICRA_CONSOLE_COMMAND_OS_BASE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "lc os",
        "lc os",
        "Inspect future OS-base posture without boot authority.",
        "lc.os.inspect",
        LATTICRA_CONSOLE_COMMAND_OS_BASE,
        LATTICRA_CONSOLE_COMMAND_EFFECT_FUTURE_GATED,
        1,
        1,
        0,
        1
    },
    {
        "pwd",
        "pwd",
        "Show the Panel console navigation directory.",
        "lc.panel.navigation",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    },
    {
        "cd",
        "cd <path>",
        "Change Panel console navigation context only.",
        "lc.panel.navigation",
        LATTICRA_CONSOLE_COMMAND_PANEL,
        LATTICRA_CONSOLE_COMMAND_EFFECT_NONE,
        1,
        1,
        0,
        0
    }
};

static void lc_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static latticra_l_ui_source_span_t lc_default_span(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 0u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 1u;
    return span;
}

const char *latticra_console_profile_label(latticra_console_profile_t profile) {
    switch (profile) {
        case LATTICRA_CONSOLE_PROFILE_HOSTED_REFERENCE:
            return "hosted-reference";
        case LATTICRA_CONSOLE_PROFILE_PANEL_EMBEDDED:
            return "panel-embedded";
        case LATTICRA_CONSOLE_PROFILE_HOST_EMBEDDED:
            return "host-embedded-planning";
        case LATTICRA_CONSOLE_PROFILE_OS_BASE_PLANNING:
            return "os-base-planning";
        default:
            return "unknown";
    }
}

const char *latticra_console_command_category_label(
    latticra_console_command_category_t category) {
    switch (category) {
        case LATTICRA_CONSOLE_COMMAND_CORE:
            return "core";
        case LATTICRA_CONSOLE_COMMAND_PANEL:
            return "panel";
        case LATTICRA_CONSOLE_COMMAND_SUBSTRATE:
            return "substrate";
        case LATTICRA_CONSOLE_COMMAND_HOST:
            return "host";
        case LATTICRA_CONSOLE_COMMAND_OS_BASE:
            return "os-base";
        default:
            return "unknown";
    }
}

const char *latticra_console_command_effect_label(
    latticra_console_command_effect_t effect) {
    switch (effect) {
        case LATTICRA_CONSOLE_COMMAND_EFFECT_NONE:
            return "none";
        case LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA:
            return "local-metadata";
        case LATTICRA_CONSOLE_COMMAND_EFFECT_FUTURE_GATED:
            return "future-gated";
        default:
            return "unknown";
    }
}

size_t latticra_console_command_count(void) {
    return sizeof(lc_commands) / sizeof(lc_commands[0]);
}

const latticra_console_command_t *latticra_console_command_at(size_t index) {
    if (index >= latticra_console_command_count()) return 0;
    return &lc_commands[index];
}

const latticra_console_command_t *latticra_console_find_command(const char *name) {
    size_t i;
    if (name == 0) return 0;
    for (i = 0u; i < latticra_console_command_count(); ++i) {
        if (strcmp(lc_commands[i].name, name) == 0) return &lc_commands[i];
    }
    return 0;
}

static const char *lc_seal_capability_label_for_command(
    const latticra_console_command_t *command) {
    if (command == 0) return "seal.capability.report";
    if (strcmp(command->name, "dry-run") == 0 ||
        strcmp(command->name, "save") == 0 ||
        strcmp(command->name, "reset") == 0 ||
        strcmp(command->name, "uninstall") == 0) {
        return "seal.capability.dry_run";
    }
    if (command->category == LATTICRA_CONSOLE_COMMAND_SUBSTRATE ||
        command->category == LATTICRA_CONSOLE_COMMAND_HOST ||
        command->category == LATTICRA_CONSOLE_COMMAND_OS_BASE) {
        return "seal.capability.inspect";
    }
    return "seal.capability.report";
}

static latticra_runtime_boundary_request_kind_t lc_runtime_kind_for_command(
    const latticra_console_command_t *command) {
    if (command == 0) return LATTICRA_RUNTIME_BOUNDARY_UNKNOWN;
    if (command->category == LATTICRA_CONSOLE_COMMAND_OS_BASE &&
        command->requires_future_gate) {
        return LATTICRA_RUNTIME_BOUNDARY_BOOT_ACTION;
    }
    if ((command->category == LATTICRA_CONSOLE_COMMAND_HOST ||
         command->effect == LATTICRA_CONSOLE_COMMAND_EFFECT_FUTURE_GATED) &&
        command->requires_future_gate) {
        return LATTICRA_RUNTIME_BOUNDARY_COMMAND_EXECUTE;
    }
    return LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK;
}

static latticra_runtime_boundary_mode_t lc_runtime_mode_for_command(
    const latticra_console_command_t *command) {
    if (command != 0 && command->requires_future_gate) {
        return LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE;
    }
    return LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
}

static void lc_boundary_authority(
    const latticra_console_command_t *command,
    latticra_runtime_boundary_authority_summary_t *authority) {
    memset(authority, 0, sizeof(*authority));
    authority->status = LATTICRA_STATUS_OK;
    lc_copy(authority->status_label, sizeof(authority->status_label), "ok");
    lc_copy(authority->validator_label, sizeof(authority->validator_label), "latticra-console");
    lc_copy(authority->requested_effect_label, sizeof(authority->requested_effect_label),
        command != 0 ? command->capability_label : "unknown");
    lc_copy(authority->denial_reason, sizeof(authority->denial_reason), "ok");
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static latticra_status_t lc_appendf(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const char *fmt,
    ...) {
    int written;
    va_list args;

    if (buffer == 0 || used == 0 || fmt == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (*used >= buffer_len) return LATTICRA_STATUS_BUFFER_TOO_SMALL;

    va_start(args, fmt);
    written = vsnprintf(buffer + *used, buffer_len - *used, fmt, args);
    va_end(args);

    if (written < 0 || (size_t)written >= buffer_len - *used) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    *used += (size_t)written;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_console_command_boundary_classify(
    const latticra_console_command_t *command,
    latticra_console_command_boundary_t *boundary) {
    latticra_runtime_boundary_authority_summary_t authority;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    latticra_status_t status;

    if (command == 0 || boundary == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    memset(boundary, 0, sizeof(*boundary));
    lc_copy(boundary->command_name, sizeof(boundary->command_name), command->name);
    lc_copy(boundary->capability_label, sizeof(boundary->capability_label), command->capability_label);
    lc_copy(boundary->seal_capability_label, sizeof(boundary->seal_capability_label),
        lc_seal_capability_label_for_command(command));

    lc_boundary_authority(command, &authority);
    memset(&request, 0, sizeof(request));
    lc_copy(request.runtime_id, sizeof(request.runtime_id), command->capability_label);
    request.request_kind = lc_runtime_kind_for_command(command);
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = lc_runtime_mode_for_command(command);
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.source_identity = command->name;
    request.source_identity_len = strlen(command->name);
    request.source_span = lc_default_span();

    status = latticra_runtime_boundary_classify(&request, &result);
    if (status != LATTICRA_STATUS_OK) return status;

    boundary->runtime_request_kind = result.record.request_kind;
    boundary->runtime_requested_effect = result.record.requested_effect;
    boundary->runtime_mode = result.record.mode;
    boundary->runtime_policy = result.record.policy;
    boundary->runtime_denial = result.record.denial;
    boundary->runtime_policy_matrix_cell = result.record.policy_matrix_cell;
    boundary->no_effect = result.no_effect;
    boundary->execution_allowed = result.execution_allowed;
    boundary->host_mutation_allowed = result.mutation_allowed;
    boundary->network_allowed = result.network_allowed;
    boundary->runtime_enforcement_allowed = result.server_allowed;
    boundary->boot_allowed = result.boot_allowed;
    boundary->requires_future_gate = result.record.matrix_requires_future_gate;
    boundary->seal_capability_grants_authority = 0;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_console_default_request(
    latticra_console_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    memset(request, 0, sizeof(*request));
    lc_copy(request->console_id, sizeof(request->console_id), "latticra-console");
    request->profile = LATTICRA_CONSOLE_PROFILE_PANEL_EMBEDDED;
    request->panel_installable = 1;
    request->host_embeddable = 1;
    request->source_identity = "latticra-console-default";
    request->source_identity_len = strlen("latticra-console-default");
    request->source_span = lc_default_span();
    return LATTICRA_STATUS_OK;
}

static void lc_seed_result(
    const latticra_console_request_t *request,
    latticra_console_result_t *result) {
    size_t n;

    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    lc_copy(result->console_name, sizeof(result->console_name), "Latticra Console");
    lc_copy(result->short_name, sizeof(result->short_name), "LC");
    lc_copy(result->component_key, sizeof(result->component_key), "latticra_console");
    lc_copy(result->console_status, sizeof(result->console_status), "initializing");
    lc_copy(result->command_registry_status, sizeof(result->command_registry_status), "seed-registry");
    lc_copy(result->substrate_bridge_status, sizeof(result->substrate_bridge_status), "metadata-bound");
    lc_copy(result->panel_install_status, sizeof(result->panel_install_status), "panel-installable");
    lc_copy(result->host_embedding_status, sizeof(result->host_embedding_status), "planned");
    lc_copy(result->host_embedding_contract_status, sizeof(result->host_embedding_contract_status),
        "metadata-only-contract");
    lc_copy(result->host_inventory_contract_status, sizeof(result->host_inventory_contract_status),
        "metadata-only-contract");
    lc_copy(result->host_adapter_contract_status, sizeof(result->host_adapter_contract_status),
        "metadata-only-contract");
    lc_copy(result->receipt_request_contract_status, sizeof(result->receipt_request_contract_status),
        "metadata-only-contract");
    lc_copy(result->receipt_payload_schema_status, sizeof(result->receipt_payload_schema_status),
        "metadata-only-schema");
    lc_copy(result->receipt_payload_artifact_draft_status, sizeof(result->receipt_payload_artifact_draft_status),
        "metadata-only-draft");
    lc_copy(result->receipt_payload_artifact_review_status, sizeof(result->receipt_payload_artifact_review_status),
        "metadata-only-review-gate");
    lc_copy(result->receipt_payload_materialization_plan_status, sizeof(result->receipt_payload_materialization_plan_status),
        "metadata-only-plan");
    lc_copy(result->signature_request_binding_status, sizeof(result->signature_request_binding_status),
        "metadata-only-contract");
    lc_copy(result->receipt_contract_status, sizeof(result->receipt_contract_status),
        "metadata-only-contract");
    lc_copy(result->os_base_contract_status, sizeof(result->os_base_contract_status),
        "metadata-only-contract");
    lc_copy(result->vm_evidence_contract_status, sizeof(result->vm_evidence_contract_status),
        "metadata-only-contract");
    lc_copy(result->os_base_status, sizeof(result->os_base_status), "planned-no-boot-authority");
    result->source_span = lc_default_span();
    result->no_effect = 1;
    result->configurable = 1;
    result->panel_installable = 1;
    result->command_registry_present = 1;
    result->substrate_bridge_present = 1;
    result->host_embeddable = 1;
    result->host_embedding_contract_present = 1;
    result->host_inventory_contract_present = 1;
    result->host_adapter_contract_present = 1;
    result->receipt_request_contract_present = 1;
    result->receipt_payload_schema_present = 1;
    result->receipt_payload_artifact_draft_present = 1;
    result->receipt_payload_artifact_review_present = 1;
    result->receipt_payload_materialization_plan_present = 1;
    result->signature_request_binding_present = 1;
    result->receipt_contract_present = 1;
    result->os_base_contract_present = 1;
    result->vm_evidence_contract_present = 1;
    result->host_embedded_now = 0;
    result->operator_shell_present = 1;
    result->command_count = (unsigned int)latticra_console_command_count();
    result->evidence_level = 4u;

    if (request == 0) return;

    lc_copy(result->console_id, sizeof(result->console_id), request->console_id);
    lc_copy(result->profile_label, sizeof(result->profile_label),
        latticra_console_profile_label(request->profile));
    result->panel_installable = request->panel_installable ? 1 : 0;
    result->host_embeddable = request->host_embeddable ? 1 : 0;
    if (request->source_identity != 0 && request->source_identity_len > 0u) {
        n = request->source_identity_len;
        if (n >= sizeof(result->source_identity)) n = sizeof(result->source_identity) - 1u;
        memcpy(result->source_identity, request->source_identity, n);
        result->source_identity[n] = '\0';
    }
    result->source_span = request->source_span;
}

static latticra_status_t lc_run_kernel(
    const latticra_console_request_t *request,
    latticra_console_result_t *result) {
    latticra_kernel_request_t kernel_request;
    latticra_status_t status;

    status = latticra_kernel_default_request(&kernel_request);
    if (status != LATTICRA_STATUS_OK) return status;

    lc_copy(kernel_request.kernel_id, sizeof(kernel_request.kernel_id), "latticra-console-kernel");
    kernel_request.source_identity = request->source_identity;
    kernel_request.source_identity_len = request->source_identity_len;
    kernel_request.source_span = request->source_span;

    return latticra_kernel_initialize(&kernel_request, &result->kernel);
}

static void lc_finalize(latticra_console_result_t *result) {
    result->execution_allowed = 0;
    result->host_mutation_allowed = 0;
    result->file_io_allowed = 0;
    result->network_allowed = 0;
    result->runtime_enforcement_allowed = 0;
    result->boot_allowed = 0;

    if (result->kernel.status != LATTICRA_STATUS_OK || result->kernel.no_effect != 1) {
        result->status = result->kernel.status;
        result->no_effect = 0;
        lc_copy(result->console_status, sizeof(result->console_status), "kernel-not-ready");
        return;
    }

    result->no_effect = 1;
    lc_copy(result->console_status, sizeof(result->console_status), "ready-report-only");
    lc_copy(result->command_registry_status, sizeof(result->command_registry_status), "seed-registry-ready");
    lc_copy(result->substrate_bridge_status, sizeof(result->substrate_bridge_status), "metadata-bound-ready");
    lc_copy(result->host_embedding_contract_status, sizeof(result->host_embedding_contract_status),
        "metadata-only-contract-ready");
    lc_copy(result->host_inventory_contract_status, sizeof(result->host_inventory_contract_status),
        "metadata-only-contract-ready");
    lc_copy(result->host_adapter_contract_status, sizeof(result->host_adapter_contract_status),
        "metadata-only-contract-ready");
    lc_copy(result->receipt_request_contract_status, sizeof(result->receipt_request_contract_status),
        "metadata-only-contract-ready");
    lc_copy(result->receipt_payload_schema_status, sizeof(result->receipt_payload_schema_status),
        "metadata-only-schema-ready");
    lc_copy(result->receipt_payload_artifact_draft_status, sizeof(result->receipt_payload_artifact_draft_status),
        "metadata-only-draft-ready");
    lc_copy(result->receipt_payload_artifact_review_status, sizeof(result->receipt_payload_artifact_review_status),
        "metadata-only-review-gate-ready");
    lc_copy(result->receipt_payload_materialization_plan_status, sizeof(result->receipt_payload_materialization_plan_status),
        "metadata-only-plan-ready");
    lc_copy(result->signature_request_binding_status, sizeof(result->signature_request_binding_status),
        "metadata-only-contract-ready");
    lc_copy(result->receipt_contract_status, sizeof(result->receipt_contract_status),
        "metadata-only-contract-ready");
    lc_copy(result->os_base_contract_status, sizeof(result->os_base_contract_status),
        "metadata-only-contract-ready");
    lc_copy(result->vm_evidence_contract_status, sizeof(result->vm_evidence_contract_status),
        "metadata-only-contract-ready");
    lc_copy(result->panel_install_status, sizeof(result->panel_install_status),
        result->panel_installable ? "panel-installable" : "panel-disabled");
}

latticra_status_t latticra_console_initialize(
    const latticra_console_request_t *request,
    latticra_console_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    lc_seed_result(request, result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        lc_copy(result->console_status, sizeof(result->console_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = lc_run_kernel(request, result);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        lc_copy(result->console_status, sizeof(result->console_status), "kernel-failed");
        return status;
    }

    lc_finalize(result);
    return result->status;
}

latticra_status_t latticra_console_command_registry_report(
    char *buffer,
    size_t buffer_len) {
    size_t i;
    size_t used;
    int written;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    written = snprintf(buffer, buffer_len,
        "LATTICRA CONSOLE COMMAND REGISTRY\n"
        "registry_source=c-static-table\n"
        "command_count=%u\n"
        "no_effect_registry=1\n"
        "host_process_launch_allowed=0\n",
        (unsigned int)latticra_console_command_count());
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    used = (size_t)written;

    for (i = 0u; i < latticra_console_command_count(); ++i) {
        const latticra_console_command_t *command = &lc_commands[i];
        written = snprintf(buffer + used, buffer_len - used,
            "command=%s category=%s effect=%s capability=%s no_effect=%d panel_visible=%d launches_host_process=%d requires_future_gate=%d usage=\"%s\"\n",
            command->name,
            latticra_console_command_category_label(command->category),
            latticra_console_command_effect_label(command->effect),
            command->capability_label,
            command->no_effect,
            command->panel_visible,
            command->launches_host_process,
            command->requires_future_gate,
            command->usage);
        if (written < 0 || (size_t)written >= buffer_len - used) {
            buffer[0] = '\0';
            return LATTICRA_STATUS_BUFFER_TOO_SMALL;
        }
        used += (size_t)written;
    }

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_console_help_report(
    char *buffer,
    size_t buffer_len) {
    size_t i;
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE HELP\n"
        "short_name=LC\n"
        "registry_source=c-static-table\n"
        "command_count=%u\n"
        "host_process_launch_allowed=0\n"
        "\n"
        "Commands:\n",
        (unsigned int)latticra_console_command_count());
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < latticra_console_command_count(); ++i) {
        const latticra_console_command_t *command = &lc_commands[i];
        status = lc_appendf(buffer, buffer_len, &used,
            "  %-14s category=%s effect=%s capability=%s\n",
            command->usage,
            latticra_console_command_category_label(command->category),
            latticra_console_command_effect_label(command->effect),
            command->capability_label);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    status = lc_appendf(buffer, buffer_len, &used,
        "\n"
        "Authority:\n"
        "  execution_allowed=0\n"
        "  host_mutation_allowed=0\n"
        "  network_allowed=0\n"
        "  runtime_enforcement_allowed=0\n"
        "  boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_manpage_report(
    char *buffer,
    size_t buffer_len) {
    size_t i;
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA-CONSOLE(1)\n"
        "\n"
        "NAME\n"
        "  latticra-lc - Latticra Console metadata and operator-base surface\n"
        "\n"
        "SYNOPSIS\n"
        "  latticra-lc status\n"
        "  latticra-lc help\n"
        "  latticra-lc commands\n"
        "  latticra-lc install-config\n"
        "  latticra-lc profiles\n"
        "  latticra-lc receipts\n"
        "  latticra-lc receipt-request\n"
        "  latticra-lc receipt-payload\n"
        "  latticra-lc receipt-artifact\n"
        "  latticra-lc receipt-artifact-review\n"
        "  latticra-lc receipt-materialization-plan\n"
        "  latticra-lc signature-request\n"
        "  latticra-lc substrate\n"
        "  latticra-lc host\n"
        "  latticra-lc host-contract\n"
        "  latticra-lc host-inventory\n"
        "  latticra-lc host-adapter\n"
        "  latticra-lc os-contract\n"
        "  latticra-lc vm-evidence\n"
        "  latticra-lc os\n"
        "\n"
        "DESCRIPTION\n"
        "  LC is the configurable Panel-installable console foundation for\n"
        "  Latticra substrate interaction, host embedding planning, and future\n"
        "  OS-base work. This Stage-0 manpage is rendered from the C command\n"
        "  registry and is metadata-only.\n"
        "\n"
        "COMMANDS\n");
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < latticra_console_command_count(); ++i) {
        const latticra_console_command_t *command = &lc_commands[i];
        status = lc_appendf(buffer, buffer_len, &used,
            "  %s\n"
            "    category=%s effect=%s capability=%s future_gate=%d\n"
            "    %s\n",
            command->usage,
            latticra_console_command_category_label(command->category),
            latticra_console_command_effect_label(command->effect),
            command->capability_label,
            command->requires_future_gate,
            command->description);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    status = lc_appendf(buffer, buffer_len, &used,
        "\n"
        "AUTHORITY\n"
        "  shell_execution_authority=0\n"
        "  external_host_process_launch=0\n"
        "  host_mutation_authority=0\n"
        "  network_authority=0\n"
        "  runtime_enforcement_authority=0\n"
        "  boot_authority=0\n"
        "  production_os_claim=0\n"
        "\n"
        "SEE ALSO\n"
        "  LATTICRA_CONSOLE_FOUNDATION.md\n");
    return status;
}

latticra_status_t latticra_console_command_boundary_report(
    char *buffer,
    size_t buffer_len) {
    size_t i;
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE COMMAND BOUNDARY REPORT\n"
        "registry_source=c-static-table\n"
        "runtime_boundary_bound=1\n"
        "seal_capability_labels_bound=1\n"
        "command_count=%u\n"
        "no_effect_registry=1\n"
        "host_process_launch_allowed=0\n",
        (unsigned int)latticra_console_command_count());
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < latticra_console_command_count(); ++i) {
        const latticra_console_command_t *command = &lc_commands[i];
        latticra_console_command_boundary_t boundary;

        status = latticra_console_command_boundary_classify(command, &boundary);
        if (status != LATTICRA_STATUS_OK) return status;

        status = lc_appendf(buffer, buffer_len, &used,
            "command=%s capability=%s seal_capability=%s runtime_request=%s runtime_effect=%s runtime_mode=%s runtime_policy=%s runtime_reason=%s policy_matrix_cell=%s requires_future_gate=%d no_effect=%d execution_allowed=%d host_mutation_allowed=%d network_allowed=%d runtime_enforcement_allowed=%d boot_allowed=%d seal_capability_grants_authority=%d\n",
            boundary.command_name,
            boundary.capability_label,
            boundary.seal_capability_label,
            latticra_runtime_boundary_request_kind_label(boundary.runtime_request_kind),
            latticra_runtime_boundary_effect_label(boundary.runtime_requested_effect),
            latticra_runtime_boundary_mode_label(boundary.runtime_mode),
            latticra_runtime_boundary_policy_label(boundary.runtime_policy),
            latticra_runtime_boundary_denial_label(boundary.runtime_denial),
            latticra_runtime_boundary_policy_matrix_cell_label(boundary.runtime_policy_matrix_cell),
            boundary.requires_future_gate,
            boundary.no_effect,
            boundary.execution_allowed,
            boundary.host_mutation_allowed,
            boundary.network_allowed,
            boundary.runtime_enforcement_allowed,
            boundary.boot_allowed,
            boundary.seal_capability_grants_authority);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_console_host_contract_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE HOST EMBEDDING CONTRACT\n"
        "contract_profile=lc-host-embedding-v0\n"
        "contract_status=metadata-only\n"
        "contract_present=1\n"
        "host_embedding_profile=host-embedded-planning\n"
        "host_adapter_required=1\n"
        "panel_install_required=1\n"
        "runtime_boundary_required=1\n"
        "seal_capability_labels_required=1\n"
        "operator_consent_required=1\n"
        "read_only_host_inventory_required_before_embedding=1\n"
        "receipt_required_before_embedding=1\n"
        "promotion_gate=contract_receipt_and_read_only_host_inventory\n"
        "command_surface=lc host-contract\n"
        "future_embedding_command=lc host\n"
        "no_effect=1\n"
        "host_embedded_now=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_host_inventory_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE READ-ONLY HOST INVENTORY CONTRACT\n"
        "contract_profile=lc-host-inventory-v0\n"
        "contract_status=metadata-only\n"
        "contract_present=1\n"
        "required_before_host_embedding=1\n"
        "host_adapter_present=0\n"
        "inventory_schema_status=planned\n"
        "inventory_performed=0\n"
        "inventory_artifact_present=0\n"
        "inventory_receipt_required=1\n"
        "operator_consent_required=1\n"
        "runtime_boundary_required=1\n"
        "seal_capability_labels_required=1\n"
        "allowed_future_scope=os_family,kernel_version,cpu_arch,memory_class,filesystem_roots,user_scope,prefix_scope\n"
        "excluded_future_scope=secrets,private_files,network_scan,process_launch,kernel_change,system_mutation\n"
        "promotion_gate=host_inventory_contract_receipt_before_host_adapter\n"
        "command_surface=lc host-inventory\n"
        "future_embedding_command=lc host\n"
        "no_effect=1\n"
        "host_embedded_now=0\n"
        "host_process_launch_allowed=0\n"
        "host_probe_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_host_adapter_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE HOST ADAPTER CONTRACT\n"
        "contract_profile=lc-host-adapter-v0\n"
        "contract_status=metadata-only\n"
        "contract_present=1\n"
        "host_adapter_enabled=0\n"
        "host_adapter_present=0\n"
        "host_adapter_loaded=0\n"
        "adapter_api_status=planned\n"
        "adapter_abi_status=planned\n"
        "host_embedding_contract_required=1\n"
        "read_only_host_inventory_contract_required=1\n"
        "host_embedding_contract_receipt_required=1\n"
        "host_inventory_contract_receipt_required=1\n"
        "operator_consent_required=1\n"
        "runtime_boundary_required=1\n"
        "seal_capability_labels_required=1\n"
        "receipt_required_before_host_adapter=1\n"
        "promotion_gate=host_adapter_contract_receipts_and_inventory\n"
        "command_surface=lc host-adapter\n"
        "future_embedding_command=lc host\n"
        "no_effect=1\n"
        "host_embedded_now=0\n"
        "host_process_launch_allowed=0\n"
        "host_probe_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_receipt_request_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE SEAL RECEIPT REQUEST CONTRACT\n"
        "request_profile=lc-receipt-request-v0\n"
        "request_contract_status=metadata-only\n"
        "request_contract_present=1\n"
        "receipt_contract_profile=lc-receipts-v0\n"
        "signature_request_profile=latticra-seal-signature-request/0.1\n"
        "requested_receipt_profile=latticra-seal-verified-receipt/0.1\n"
        "requested_capability=verified-receipt-report\n"
        "requested_surfaces=profile,host-contract,host-inventory,host-adapter,runtime-boundary\n"
        "receipt_payload_schema_profile=lc-receipt-payload-schema-v0\n"
        "receipt_payload_schema_required=1\n"
        "receipt_payload_schema_present=1\n"
        "receipt_payload_schema_command=lc receipt-payload\n"
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0\n"
        "receipt_payload_artifact_draft_required=1\n"
        "receipt_payload_artifact_draft_present=1\n"
        "receipt_payload_artifact_draft_command=lc receipt-artifact\n"
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0\n"
        "receipt_payload_artifact_review_required=1\n"
        "receipt_payload_artifact_review_present=1\n"
        "receipt_payload_artifact_review_command=lc receipt-artifact-review\n"
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0\n"
        "receipt_payload_materialization_plan_required=1\n"
        "receipt_payload_materialization_plan_present=1\n"
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan\n"
        "draft_review_receipt_present=0\n"
        "materialization_preconditions_met=0\n"
        "materialization_allowed=0\n"
        "payload_artifact_present=0\n"
        "payload_materialized=0\n"
        "signature_request_binding_profile=lc-signature-request-binding-v0\n"
        "signature_request_binding_required=1\n"
        "signature_request_binding_contract_present=1\n"
        "signature_request_binding_command=lc signature-request\n"
        "receipt_payload_profile=lc-receipts-v0\n"
        "receipt_payload_hash_recorded=0\n"
        "receipt_payload_path_recorded=0\n"
        "seal_signature_planned=1\n"
        "seal_signature_request_ready=0\n"
        "seal_signature_request_present=0\n"
        "seal_signing_authority_present=0\n"
        "seal_signer_handoff_allowed=0\n"
        "seal_signing_operation_allowed=0\n"
        "receipt_write_allowed=0\n"
        "receipt_signed=0\n"
        "receipt_verification_allowed=0\n"
        "promotion_gate=lc_receipt_request_review_before_signing\n"
        "command_surface=lc receipt-request\n"
        "related_contract_command=lc receipts\n"
        "no_effect=1\n"
        "file_write_allowed=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_receipt_payload_schema_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE RECEIPT PAYLOAD SCHEMA\n"
        "schema_profile=lc-receipt-payload-schema-v0\n"
        "schema_status=metadata-only\n"
        "schema_present=1\n"
        "receipt_request_profile=lc-receipt-request-v0\n"
        "receipt_contract_profile=lc-receipts-v0\n"
        "signature_request_profile=latticra-seal-signature-request/0.1\n"
        "requested_receipt_profile=latticra-seal-verified-receipt/0.1\n"
        "requested_capability=verified-receipt-report\n"
        "payload_fields=console_id,profile,command_registry,host_contract,host_inventory,host_adapter,runtime_boundary,seal_capability_labels,authority_denials\n"
        "required_contract_fields=host_embedding_contract_status,host_inventory_contract_status,host_adapter_contract_status,receipt_request_contract_status,receipt_contract_status\n"
        "required_authority_fields=no_effect,execution_allowed,host_mutation_allowed,network_allowed,runtime_enforcement_allowed,boot_allowed\n"
        "payload_artifact_present=0\n"
        "payload_hash_computed=0\n"
        "payload_path_recorded=0\n"
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0\n"
        "receipt_payload_artifact_draft_present=1\n"
        "receipt_payload_artifact_draft_command=lc receipt-artifact\n"
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0\n"
        "receipt_payload_artifact_review_present=1\n"
        "receipt_payload_artifact_review_command=lc receipt-artifact-review\n"
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0\n"
        "receipt_payload_materialization_plan_present=1\n"
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan\n"
        "materialization_preconditions_met=0\n"
        "materialization_allowed=0\n"
        "signature_request_binding_present=0\n"
        "signature_request_binding_allowed=0\n"
        "signature_request_binding_contract_present=1\n"
        "signature_request_binding_command=lc signature-request\n"
        "seal_signature_request_ready=0\n"
        "seal_signature_request_present=0\n"
        "seal_signing_authority_present=0\n"
        "receipt_write_allowed=0\n"
        "receipt_signed=0\n"
        "promotion_gate=lc_receipt_payload_schema_before_signature_request_binding\n"
        "command_surface=lc receipt-payload\n"
        "related_request_command=lc receipt-request\n"
        "no_effect=1\n"
        "file_write_allowed=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_receipt_payload_artifact_draft_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT DRAFT\n"
        "draft_profile=lc-receipt-payload-artifact-draft-v0\n"
        "draft_status=metadata-only\n"
        "draft_contract_present=1\n"
        "receipt_request_profile=lc-receipt-request-v0\n"
        "receipt_payload_schema_profile=lc-receipt-payload-schema-v0\n"
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0\n"
        "receipt_payload_artifact_review_present=1\n"
        "receipt_payload_artifact_review_command=lc receipt-artifact-review\n"
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0\n"
        "receipt_payload_materialization_plan_present=1\n"
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan\n"
        "signature_request_binding_profile=lc-signature-request-binding-v0\n"
        "receipt_contract_profile=lc-receipts-v0\n"
        "signature_request_profile=latticra-seal-signature-request/0.1\n"
        "signing_authorization_profile=latticra-seal-signing-authorization/0.1\n"
        "canonicalization_profile=lc-receipt-payload-canonical-text-v0\n"
        "artifact_fields=console_id,profile,command_registry,host_contract,host_inventory,host_adapter,runtime_boundary,seal_capability_labels,authority_denials\n"
        "artifact_field_order=console_id,profile,command_registry,host_contract,host_inventory,host_adapter,runtime_boundary,seal_capability_labels,authority_denials\n"
        "required_prior_contracts=receipt-request,receipt-payload-schema,signature-request-binding,receipt-contract\n"
        "receipt_payload_artifact_draft_present=1\n"
        "draft_review_required=1\n"
        "draft_review_present=0\n"
        "draft_review_receipt_required=1\n"
        "draft_review_receipt_present=0\n"
        "draft_review_approval_recorded=0\n"
        "materialization_preconditions_met=0\n"
        "materialization_allowed=0\n"
        "payload_artifact_present=0\n"
        "payload_materialized=0\n"
        "payload_write_allowed=0\n"
        "payload_hash_computed=0\n"
        "payload_hash_recorded=0\n"
        "payload_path_recorded=0\n"
        "signature_request_binding_artifact_present=0\n"
        "signature_request_binding_allowed=0\n"
        "seal_signature_request_ready=0\n"
        "seal_signature_request_present=0\n"
        "seal_signing_authority_present=0\n"
        "receipt_write_allowed=0\n"
        "receipt_signed=0\n"
        "promotion_gate=lc_receipt_payload_artifact_draft_before_materialization_and_signature_request\n"
        "command_surface=lc receipt-artifact\n"
        "related_review_command=lc receipt-artifact-review\n"
        "related_materialization_plan_command=lc receipt-materialization-plan\n"
        "related_schema_command=lc receipt-payload\n"
        "related_binding_command=lc signature-request\n"
        "related_request_command=lc receipt-request\n"
        "no_effect=1\n"
        "file_write_allowed=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_receipt_payload_artifact_review_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT REVIEW GATE\n"
        "review_profile=lc-receipt-payload-artifact-review-v0\n"
        "review_status=metadata-only\n"
        "review_gate_present=1\n"
        "receipt_request_profile=lc-receipt-request-v0\n"
        "receipt_payload_schema_profile=lc-receipt-payload-schema-v0\n"
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0\n"
        "receipt_payload_artifact_draft_required=1\n"
        "receipt_payload_artifact_draft_present=1\n"
        "receipt_payload_artifact_draft_command=lc receipt-artifact\n"
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0\n"
        "receipt_payload_materialization_plan_present=1\n"
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan\n"
        "signature_request_binding_profile=lc-signature-request-binding-v0\n"
        "receipt_contract_profile=lc-receipts-v0\n"
        "draft_review_required=1\n"
        "draft_review_present=0\n"
        "draft_review_receipt_required=1\n"
        "draft_review_receipt_present=0\n"
        "draft_review_approval_recorded=0\n"
        "draft_reviewer_identity_recorded=0\n"
        "draft_review_timestamp_recorded=0\n"
        "materialization_plan_required=1\n"
        "materialization_plan_present=1\n"
        "materialization_preconditions_met=0\n"
        "materialization_allowed=0\n"
        "payload_artifact_present=0\n"
        "payload_materialized=0\n"
        "payload_write_allowed=0\n"
        "payload_hash_computed=0\n"
        "payload_hash_recorded=0\n"
        "payload_path_recorded=0\n"
        "signature_request_binding_allowed=0\n"
        "signature_request_binding_artifact_present=0\n"
        "seal_signature_request_ready=0\n"
        "seal_signature_request_present=0\n"
        "seal_signing_authority_present=0\n"
        "receipt_write_allowed=0\n"
        "receipt_signed=0\n"
        "promotion_gate=lc_receipt_payload_artifact_review_before_materialization\n"
        "command_surface=lc receipt-artifact-review\n"
        "related_materialization_plan_command=lc receipt-materialization-plan\n"
        "related_artifact_command=lc receipt-artifact\n"
        "related_schema_command=lc receipt-payload\n"
        "related_binding_command=lc signature-request\n"
        "related_request_command=lc receipt-request\n"
        "no_effect=1\n"
        "file_write_allowed=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_receipt_payload_materialization_plan_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE RECEIPT PAYLOAD MATERIALIZATION PLAN\n"
        "materialization_plan_profile=lc-receipt-payload-materialization-plan-v0\n"
        "materialization_plan_status=metadata-only\n"
        "materialization_plan_present=1\n"
        "receipt_request_profile=lc-receipt-request-v0\n"
        "receipt_payload_schema_profile=lc-receipt-payload-schema-v0\n"
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0\n"
        "receipt_payload_artifact_draft_present=1\n"
        "receipt_payload_artifact_draft_command=lc receipt-artifact\n"
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0\n"
        "receipt_payload_artifact_review_required=1\n"
        "receipt_payload_artifact_review_present=1\n"
        "receipt_payload_artifact_review_command=lc receipt-artifact-review\n"
        "receipt_contract_profile=lc-receipts-v0\n"
        "signature_request_binding_profile=lc-signature-request-binding-v0\n"
        "draft_review_receipt_required=1\n"
        "draft_review_receipt_present=0\n"
        "draft_review_approval_recorded=0\n"
        "materialization_preconditions_met=0\n"
        "materialization_allowed=0\n"
        "materialization_execution_planned=0\n"
        "payload_artifact_present=0\n"
        "payload_materialized=0\n"
        "payload_write_allowed=0\n"
        "payload_file_open_allowed=0\n"
        "payload_hash_computed=0\n"
        "payload_hash_recorded=0\n"
        "payload_path_recorded=0\n"
        "signature_request_binding_allowed=0\n"
        "signature_request_binding_artifact_present=0\n"
        "seal_signature_request_ready=0\n"
        "seal_signature_request_present=0\n"
        "seal_signing_authority_present=0\n"
        "receipt_write_allowed=0\n"
        "receipt_signed=0\n"
        "promotion_gate=lc_receipt_payload_materialization_plan_after_review_receipt\n"
        "command_surface=lc receipt-materialization-plan\n"
        "related_review_command=lc receipt-artifact-review\n"
        "related_artifact_command=lc receipt-artifact\n"
        "related_schema_command=lc receipt-payload\n"
        "related_binding_command=lc signature-request\n"
        "related_request_command=lc receipt-request\n"
        "no_effect=1\n"
        "file_write_allowed=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_signature_request_binding_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE SIGNATURE REQUEST BINDING CONTRACT\n"
        "binding_profile=lc-signature-request-binding-v0\n"
        "binding_status=metadata-only\n"
        "binding_contract_present=1\n"
        "receipt_request_profile=lc-receipt-request-v0\n"
        "receipt_payload_schema_profile=lc-receipt-payload-schema-v0\n"
        "receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0\n"
        "receipt_payload_artifact_draft_required=1\n"
        "receipt_payload_artifact_draft_present=1\n"
        "receipt_payload_artifact_draft_command=lc receipt-artifact\n"
        "receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0\n"
        "receipt_payload_artifact_review_required=1\n"
        "receipt_payload_artifact_review_present=1\n"
        "receipt_payload_artifact_review_command=lc receipt-artifact-review\n"
        "receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0\n"
        "receipt_payload_materialization_plan_required=1\n"
        "receipt_payload_materialization_plan_present=1\n"
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan\n"
        "draft_review_receipt_present=0\n"
        "materialization_preconditions_met=0\n"
        "materialization_allowed=0\n"
        "receipt_contract_profile=lc-receipts-v0\n"
        "signature_request_profile=latticra-seal-signature-request/0.1\n"
        "signing_authorization_profile=latticra-seal-signing-authorization/0.1\n"
        "requested_signature=Ed25519-development\n"
        "requested_signing_authorization=metadata-only\n"
        "requested_receipt_profile=latticra-seal-verified-receipt/0.1\n"
        "requested_capability=verified-receipt-report\n"
        "required_surfaces=receipt-request,receipt-payload-schema,receipt-payload-artifact-draft,receipt-payload-artifact-review,receipt-payload-materialization-plan,receipt-contract,runtime-boundary,seal-capability-labels\n"
        "payload_artifact_present=0\n"
        "required_payload_state=payload_artifact_present=0,payload_hash_computed=0,payload_path_recorded=0\n"
        "signature_request_binding_artifact_present=0\n"
        "signature_request_binding_artifact_path_recorded=0\n"
        "signature_request_binding_hash_recorded=0\n"
        "signature_request_binding_allowed=0\n"
        "seal_signature_request_metadata_referenced=1\n"
        "seal_signature_request_ready=0\n"
        "seal_signature_request_present=0\n"
        "seal_signature_request_written=0\n"
        "seal_signing_authorization_metadata_referenced=1\n"
        "seal_signing_authority_present=0\n"
        "seal_signer_handoff_allowed=0\n"
        "seal_signing_operation_allowed=0\n"
        "receipt_write_allowed=0\n"
        "receipt_signed=0\n"
        "promotion_gate=lc_signature_request_binding_after_payload_artifact_and_signing_authority\n"
        "command_surface=lc signature-request\n"
        "related_payload_command=lc receipt-payload\n"
        "related_request_command=lc receipt-request\n"
        "no_effect=1\n"
        "file_write_allowed=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_receipt_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE RECEIPT CONTRACT\n"
        "receipt_profile=lc-receipts-v0\n"
        "receipt_contract_status=metadata-only\n"
        "receipt_contract_present=1\n"
        "profile_receipt_required=1\n"
        "host_embedding_contract_receipt_required=1\n"
        "host_inventory_contract_receipt_required=1\n"
        "host_adapter_contract_receipt_required=1\n"
        "receipt_request_contract_required=1\n"
        "receipt_request_contract_present=1\n"
        "receipt_payload_schema_required=1\n"
        "receipt_payload_schema_present=1\n"
        "receipt_payload_artifact_draft_required=1\n"
        "receipt_payload_artifact_draft_present=1\n"
        "receipt_payload_artifact_review_required=1\n"
        "receipt_payload_artifact_review_present=1\n"
        "receipt_payload_materialization_plan_required=1\n"
        "receipt_payload_materialization_plan_present=1\n"
        "draft_review_receipt_present=0\n"
        "signature_request_binding_required=1\n"
        "signature_request_binding_contract_present=1\n"
        "runtime_boundary_receipt_required=1\n"
        "seal_capability_labels_required=1\n"
        "signature_request_profile=latticra-seal-signature-request/0.1\n"
        "receipt_request_command=lc receipt-request\n"
        "receipt_payload_schema_command=lc receipt-payload\n"
        "receipt_payload_artifact_draft_command=lc receipt-artifact\n"
        "receipt_payload_artifact_review_command=lc receipt-artifact-review\n"
        "receipt_payload_materialization_plan_command=lc receipt-materialization-plan\n"
        "signature_request_binding_command=lc signature-request\n"
        "seal_signature_planned=1\n"
        "seal_signature_present=0\n"
        "seal_signing_authority_present=0\n"
        "receipt_written=0\n"
        "receipt_signed=0\n"
        "receipt_hash_recorded=0\n"
        "receipt_path_recorded=0\n"
        "receipt_format=metadata-only-contract\n"
        "receipt_surfaces=profile,host-contract,host-inventory,host-adapter,runtime-boundary\n"
        "promotion_gate=lc_receipts_before_host_adapter_or_os_base\n"
        "command_surface=lc receipts\n"
        "no_effect=1\n"
        "file_write_allowed=0\n"
        "host_process_launch_allowed=0\n"
        "host_file_read_allowed=0\n"
        "host_file_write_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n");
    return status;
}

latticra_status_t latticra_console_os_contract_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE OS-BASE PLANNING CONTRACT\n"
        "contract_profile=lc-os-base-v0\n"
        "contract_status=metadata-only\n"
        "contract_present=1\n"
        "os_base_enabled=0\n"
        "production_os_claim=0\n"
        "boot_allowed=0\n"
        "boot_authority_present=0\n"
        "kernel_change_allowed=0\n"
        "kernel_enforcement_allowed=0\n"
        "hardware_access_allowed=0\n"
        "bootloader_write_allowed=0\n"
        "partition_mutation_allowed=0\n"
        "driver_load_allowed=0\n"
        "service_install_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "read_only_host_inventory_receipt_required=1\n"
        "vm_evidence_contract_required=1\n"
        "vm_evidence_required=1\n"
        "operator_consent_required=1\n"
        "runtime_boundary_required=1\n"
        "seal_capability_labels_required=1\n"
        "receipt_required_before_os_base=1\n"
        "promotion_gate=os_base_contract_receipt_and_vm_evidence\n"
        "command_surface=lc os-contract\n"
        "future_os_base_command=lc os\n"
        "no_effect=1\n");
    return status;
}

latticra_status_t latticra_console_vm_evidence_report(
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    latticra_status_t status;

    if (buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = lc_appendf(buffer, buffer_len, &used,
        "LATTICRA CONSOLE VM EVIDENCE CONTRACT\n"
        "contract_profile=lc-vm-evidence-v0\n"
        "contract_status=metadata-only\n"
        "contract_present=1\n"
        "vm_evidence_required=1\n"
        "vm_evidence_capture_enabled=0\n"
        "vm_evidence_artifact_present=0\n"
        "vm_launcher_present=0\n"
        "vm_launch_allowed=0\n"
        "hypervisor_access_allowed=0\n"
        "disk_image_open_allowed=0\n"
        "disk_image_write_allowed=0\n"
        "snapshot_capture_allowed=0\n"
        "guest_agent_allowed=0\n"
        "guest_network_allowed=0\n"
        "host_probe_allowed=0\n"
        "os_base_contract_required=1\n"
        "read_only_host_inventory_receipt_required=1\n"
        "operator_consent_required=1\n"
        "runtime_boundary_required=1\n"
        "seal_capability_labels_required=1\n"
        "receipt_required_before_vm_evidence=1\n"
        "promotion_gate=vm_evidence_contract_before_boot_adjacency\n"
        "command_surface=lc vm-evidence\n"
        "future_os_base_command=lc os\n"
        "no_effect=1\n"
        "execution_allowed=0\n"
        "host_mutation_allowed=0\n"
        "network_allowed=0\n"
        "runtime_enforcement_allowed=0\n"
        "boot_allowed=0\n"
        "production_os_claim=0\n");
    return status;
}

latticra_status_t latticra_console_report(
    const latticra_console_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    written = snprintf(buffer, buffer_len,
        "LATTICRA CONSOLE REPORT\n"
        "console_id=%s\n"
        "console_name=%s\n"
        "short_name=%s\n"
        "component_key=%s\n"
        "profile=%s\n"
        "console_status=%s\n"
        "command_registry_status=%s\n"
        "substrate_bridge_status=%s\n"
        "panel_install_status=%s\n"
        "host_embedding_status=%s\n"
        "host_embedding_contract_status=%s\n"
        "host_inventory_contract_status=%s\n"
        "host_adapter_contract_status=%s\n"
        "receipt_request_contract_status=%s\n"
        "receipt_payload_schema_status=%s\n"
        "receipt_payload_artifact_draft_status=%s\n"
        "receipt_payload_artifact_review_status=%s\n"
        "receipt_payload_materialization_plan_status=%s\n"
        "signature_request_binding_status=%s\n"
        "receipt_contract_status=%s\n"
        "os_base_contract_status=%s\n"
        "vm_evidence_contract_status=%s\n"
        "os_base_status=%s\n"
        "configurable=%d\n"
        "panel_installable=%d\n"
        "command_registry_present=%d\n"
        "substrate_bridge_present=%d\n"
        "operator_shell_present=%d\n"
        "host_embeddable=%d\n"
        "host_embedding_contract_present=%d\n"
        "host_inventory_contract_present=%d\n"
        "host_adapter_contract_present=%d\n"
        "receipt_request_contract_present=%d\n"
        "receipt_payload_schema_present=%d\n"
        "receipt_payload_artifact_draft_present=%d\n"
        "receipt_payload_artifact_review_present=%d\n"
        "receipt_payload_materialization_plan_present=%d\n"
        "signature_request_binding_present=%d\n"
        "receipt_contract_present=%d\n"
        "os_base_contract_present=%d\n"
        "vm_evidence_contract_present=%d\n"
        "host_embedded_now=%d\n"
        "command_count=%u\n"
        "command_registry_source=c-static-table\n"
        "command_registry_no_effect=1\n"
        "command_registry_host_process_launch_allowed=0\n"
        "runtime_boundary_bound=1\n"
        "seal_capability_labels_bound=1\n"
        "kernel_status=%s\n"
        "kernel_runtime_status=%s\n"
        "kernel_boot_status=%s\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "host_mutation_allowed=%d\n"
        "file_io_allowed=%d\n"
        "network_allowed=%d\n"
        "runtime_enforcement_allowed=%d\n"
        "boot_allowed=%d\n"
        "os_base_enabled=0\n"
        "production_os_claim=0\n"
        "future_os_base_claim=planned_not_claimed\n"
        "phase1_reference_lessons=registry_help_guarded_boundary_os_track\n"
        "evidence_level=%u\n"
        "source_identity=%s\n",
        result->console_id,
        result->console_name,
        result->short_name,
        result->component_key,
        result->profile_label,
        result->console_status,
        result->command_registry_status,
        result->substrate_bridge_status,
        result->panel_install_status,
        result->host_embedding_status,
        result->host_embedding_contract_status,
        result->host_inventory_contract_status,
        result->host_adapter_contract_status,
        result->receipt_request_contract_status,
        result->receipt_payload_schema_status,
        result->receipt_payload_artifact_draft_status,
        result->receipt_payload_artifact_review_status,
        result->receipt_payload_materialization_plan_status,
        result->signature_request_binding_status,
        result->receipt_contract_status,
        result->os_base_contract_status,
        result->vm_evidence_contract_status,
        result->os_base_status,
        result->configurable,
        result->panel_installable,
        result->command_registry_present,
        result->substrate_bridge_present,
        result->operator_shell_present,
        result->host_embeddable,
        result->host_embedding_contract_present,
        result->host_inventory_contract_present,
        result->host_adapter_contract_present,
        result->receipt_request_contract_present,
        result->receipt_payload_schema_present,
        result->receipt_payload_artifact_draft_present,
        result->receipt_payload_artifact_review_present,
        result->receipt_payload_materialization_plan_present,
        result->signature_request_binding_present,
        result->receipt_contract_present,
        result->os_base_contract_present,
        result->vm_evidence_contract_present,
        result->host_embedded_now,
        result->command_count,
        result->kernel.kernel_status,
        result->kernel.runtime_status,
        result->kernel.boot_status,
        result->no_effect,
        result->execution_allowed,
        result->host_mutation_allowed,
        result->file_io_allowed,
        result->network_allowed,
        result->runtime_enforcement_allowed,
        result->boot_allowed,
        result->evidence_level,
        result->source_identity);

    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
