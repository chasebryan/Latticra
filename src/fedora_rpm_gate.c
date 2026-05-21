#include "latticra/fedora_rpm_gate.h"

#include <stdio.h>
#include <string.h>

static void latticra_fedora_rpm_gate_copy_slice(
    char *dest,
    size_t dest_len,
    const char *source,
    size_t source_len)
{
    size_t copy_len;

    if (dest == NULL || dest_len == 0u) {
        return;
    }

    if (source == NULL) {
        dest[0] = '\0';
        return;
    }

    copy_len = source_len;
    if (copy_len >= dest_len) {
        copy_len = dest_len - 1u;
    }

    if (copy_len > 0u) {
        memcpy(dest, source, copy_len);
    }
    dest[copy_len] = '\0';
}

const char *latticra_fedora_rpm_gate_status_label(
    latticra_fedora_rpm_gate_status_t status)
{
    switch (status) {
    case LATTICRA_FEDORA_RPM_GATE_ALLOWED:
        return "allowed";
    case LATTICRA_FEDORA_RPM_GATE_DENIED:
        return "denied";
    case LATTICRA_FEDORA_RPM_GATE_INVALID:
        return "invalid";
    default:
        return "unknown";
    }
}

const char *latticra_fedora_rpm_gate_denial_label(
    latticra_fedora_rpm_gate_denial_t denial)
{
    switch (denial) {
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_NONE:
        return "none";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_NOT_FEDORA_HOST:
        return "not-fedora-host";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_IMMUTABLE_FEDORA_HOST:
        return "immutable-fedora-host";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_LOCAL_RPM_MISSING:
        return "local-rpm-missing";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_PRIVILEGE_MISSING:
        return "privilege-missing";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_NETWORK_REQUIRED:
        return "network-required";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_OPERATOR_CONFIRMATION_MISSING:
        return "operator-confirmation-missing";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_DRY_RUN_MISSING:
        return "dry-run-missing";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_ROLLBACK_PLAN_MISSING:
        return "rollback-plan-missing";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_PREFLIGHT_NOT_READY:
        return "preflight-not-ready";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_PREFLIGHT_DENIED:
        return "preflight-denied";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_LIVE_PROBE_MISSING:
        return "live-probe-missing";
    case LATTICRA_FEDORA_RPM_GATE_DENIAL_INVALID_INPUT:
        return "invalid-gate-input";
    default:
        return "unknown";
    }
}

static void latticra_fedora_rpm_gate_deny(
    latticra_fedora_rpm_gate_result_t *result,
    latticra_fedora_rpm_gate_denial_t denial)
{
    result->gate_status = LATTICRA_FEDORA_RPM_GATE_DENIED;
    result->denial = denial;
    result->install_mutation_allowed = 0;
}

latticra_status_t latticra_fedora_rpm_gate_classify(
    const latticra_fedora_rpm_gate_input_t *input,
    latticra_fedora_rpm_gate_result_t *result)
{
    if (input == NULL || result == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(result, 0, sizeof(*result));

    result->gate_evaluated = 1;
    result->install_mutation_performed = 0;
    result->host_mutation_performed = 0;
    result->network_allowed = 0;
    result->evidence_level = 4u;

    result->fedora_host = input->fedora_host ? 1 : 0;
    result->mutable_fedora_host = input->mutable_fedora_host ? 1 : 0;
    result->immutable_host = input->immutable_host ? 1 : 0;
    result->local_rpm_present = input->local_rpm_present ? 1 : 0;
    result->root_or_sudo_available = input->root_or_sudo_available ? 1 : 0;
    result->network_required = input->network_required ? 1 : 0;
    result->operator_install_confirmation = input->operator_install_confirmation ? 1 : 0;
    result->dry_run_passed = input->dry_run_passed ? 1 : 0;
    result->rollback_or_remove_plan_present = input->rollback_or_remove_plan_present ? 1 : 0;
    result->preflight_classification = input->preflight_classification;
    result->preflight_denial = input->preflight_denial;
    result->snapshot_captured = input->snapshot_captured ? 1 : 0;
    result->live_probe_performed = input->live_probe_performed ? 1 : 0;

    latticra_fedora_rpm_gate_copy_slice(
        result->local_rpm_path,
        sizeof(result->local_rpm_path),
        input->local_rpm_path,
        input->local_rpm_path_len);

    if (!result->snapshot_captured) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }

    if (!result->live_probe_performed) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_LIVE_PROBE_MISSING);
        return LATTICRA_STATUS_OK;
    }

    if (!result->fedora_host) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_NOT_FEDORA_HOST);
        return LATTICRA_STATUS_OK;
    }

    if (result->immutable_host || !result->mutable_fedora_host) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_IMMUTABLE_FEDORA_HOST);
        return LATTICRA_STATUS_OK;
    }

    if (!result->local_rpm_present) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_LOCAL_RPM_MISSING);
        return LATTICRA_STATUS_OK;
    }

    if (!result->root_or_sudo_available) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_PRIVILEGE_MISSING);
        return LATTICRA_STATUS_OK;
    }

    if (result->network_required) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_NETWORK_REQUIRED);
        return LATTICRA_STATUS_OK;
    }

    if (!result->operator_install_confirmation) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_OPERATOR_CONFIRMATION_MISSING);
        return LATTICRA_STATUS_OK;
    }

    if (!result->dry_run_passed) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_DRY_RUN_MISSING);
        return LATTICRA_STATUS_OK;
    }

    if (!result->rollback_or_remove_plan_present) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_ROLLBACK_PLAN_MISSING);
        return LATTICRA_STATUS_OK;
    }

    if (result->preflight_classification != LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_PREFLIGHT_NOT_READY);
        return LATTICRA_STATUS_OK;
    }

    if (result->preflight_denial != LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE) {
        latticra_fedora_rpm_gate_deny(
            result,
            LATTICRA_FEDORA_RPM_GATE_DENIAL_PREFLIGHT_DENIED);
        return LATTICRA_STATUS_OK;
    }

    result->gate_status = LATTICRA_FEDORA_RPM_GATE_ALLOWED;
    result->denial = LATTICRA_FEDORA_RPM_GATE_DENIAL_NONE;
    result->install_mutation_allowed = 1;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_fedora_rpm_gate_report(
    const latticra_fedora_rpm_gate_result_t *result,
    char *buffer,
    size_t buffer_len)
{
    int written;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "FEDORA LOCAL RPM INSTALL MUTATION GATE\n"
        "install_gate_status=%s\n"
        "install_gate_denial=%s\n"
        "local_rpm_path=%s\n"
        "fedora_host=%d\n"
        "mutable_fedora_host=%d\n"
        "immutable_host=%d\n"
        "local_rpm_present=%d\n"
        "root_or_sudo_available=%d\n"
        "network_required=%d\n"
        "operator_install_confirmation=%d\n"
        "dry_run_passed=%d\n"
        "rollback_or_remove_plan_present=%d\n"
        "preflight_classification=%s\n"
        "preflight_denial=%s\n"
        "snapshot_captured=%d\n"
        "live_probe_performed=%d\n"
        "gate_evaluated=%d\n"
        "install_mutation_allowed=%d\n"
        "install_mutation_performed=%d\n"
        "host_mutation_performed=%d\n"
        "network_allowed=%d\n"
        "evidence_level=%u\n",
        latticra_fedora_rpm_gate_status_label(result->gate_status),
        latticra_fedora_rpm_gate_denial_label(result->denial),
        result->local_rpm_path,
        result->fedora_host,
        result->mutable_fedora_host,
        result->immutable_host,
        result->local_rpm_present,
        result->root_or_sudo_available,
        result->network_required,
        result->operator_install_confirmation,
        result->dry_run_passed,
        result->rollback_or_remove_plan_present,
        latticra_fedora_preflight_classification_label(result->preflight_classification),
        latticra_fedora_preflight_denial_label(result->preflight_denial),
        result->snapshot_captured,
        result->live_probe_performed,
        result->gate_evaluated,
        result->install_mutation_allowed,
        result->install_mutation_performed,
        result->host_mutation_performed,
        result->network_allowed,
        result->evidence_level);

    if (written < 0 || (size_t)written >= buffer_len) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
