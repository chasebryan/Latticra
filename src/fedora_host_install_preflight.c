#include "latticra/fedora_host_install_preflight.h"

#include <stdio.h>
#include <string.h>

static int latticra_fedora_preflight_slice_contains(
    const char *text,
    size_t text_len,
    const char *needle)
{
    size_t needle_len;
    size_t i;

    if (text == NULL || needle == NULL) {
        return 0;
    }

    needle_len = strlen(needle);
    if (needle_len == 0u || text_len < needle_len) {
        return 0;
    }

    for (i = 0u; i <= text_len - needle_len; ++i) {
        if (memcmp(text + i, needle, needle_len) == 0) {
            return 1;
        }
    }

    return 0;
}

static void latticra_fedora_preflight_copy_label(
    char *dest,
    size_t dest_len,
    const char *source)
{
    size_t source_len;
    size_t copy_len;

    if (dest == NULL || dest_len == 0u) {
        return;
    }

    if (source == NULL) {
        dest[0] = '\0';
        return;
    }

    source_len = strlen(source);
    copy_len = source_len;
    if (copy_len >= dest_len) {
        copy_len = dest_len - 1u;
    }

    if (copy_len > 0u) {
        memcpy(dest, source, copy_len);
    }
    dest[copy_len] = '\0';
}

const char *latticra_fedora_preflight_classification_label(
    latticra_fedora_preflight_classification_t classification)
{
    switch (classification) {
    case LATTICRA_FEDORA_PREFLIGHT_REPORT_ONLY:
        return "report-only";
    case LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM:
        return "ready-local-rpm";
    case LATTICRA_FEDORA_PREFLIGHT_BLOCKED:
        return "blocked";
    case LATTICRA_FEDORA_PREFLIGHT_FUTURE_GATED:
        return "future-gated";
    case LATTICRA_FEDORA_PREFLIGHT_INVALID:
        return "invalid";
    default:
        return "unknown";
    }
}

const char *latticra_fedora_preflight_denial_label(
    latticra_fedora_preflight_denial_t denial)
{
    switch (denial) {
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE:
        return "none";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_NOT_REQUESTED:
        return "host-install-not-requested";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_NON_FEDORA_HOST:
        return "non-fedora-host";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_IMMUTABLE_HOST:
        return "immutable-host";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_NETWORK_REQUIRED:
        return "network-required";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_REQUIRED_TOOLING_MISSING:
        return "required-tooling-missing";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_LOCAL_RPM_MISSING:
        return "local-rpm-missing";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_PRIVILEGE_MISSING:
        return "privilege-missing";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_RUNTIME_ENTRYPOINT_NOT_PRESENT:
        return "runtime-entrypoint-not-present";
    case LATTICRA_FEDORA_PREFLIGHT_DENIAL_INVALID_SNAPSHOT:
        return "invalid-snapshot";
    default:
        return "unknown";
    }
}

static void latticra_fedora_preflight_set_result(
    latticra_fedora_host_install_preflight_result_t *result,
    latticra_fedora_preflight_classification_t classification,
    latticra_fedora_preflight_denial_t denial,
    const char *host_classification,
    const char *install_lane)
{
    result->classification = classification;
    result->denial = denial;
    latticra_fedora_preflight_copy_label(
        result->host_classification,
        sizeof(result->host_classification),
        host_classification);
    latticra_fedora_preflight_copy_label(
        result->install_lane,
        sizeof(result->install_lane),
        install_lane);
}

latticra_status_t latticra_fedora_host_install_preflight_classify(
    const latticra_fedora_host_install_preflight_snapshot_t *snapshot,
    latticra_fedora_host_install_preflight_result_t *result)
{
    int fedora_id;
    int fedora_like;

    if (snapshot == NULL || result == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(result, 0, sizeof(*result));
    result->no_effect = 1;
    result->host_install_performed = 0;
    result->host_mutation_performed = 0;
    result->network_allowed = 0;
    result->evidence_level = 1u;

    fedora_id = latticra_fedora_preflight_slice_contains(
        snapshot->os_id,
        snapshot->os_id_len,
        "fedora");
    fedora_like = latticra_fedora_preflight_slice_contains(
        snapshot->os_id_like,
        snapshot->os_id_like_len,
        "fedora");

    result->fedora_host = fedora_id || fedora_like;
    result->immutable_host = snapshot->immutable_host ? 1 : 0;
    result->mutable_fedora_host = (result->fedora_host && !result->immutable_host) ? 1 : 0;
    result->rpm_available = snapshot->rpm_available ? 1 : 0;
    result->dnf_available = snapshot->dnf_available ? 1 : 0;
    result->rpmbuild_available = snapshot->rpmbuild_available ? 1 : 0;
    result->rpmlint_available = snapshot->rpmlint_available ? 1 : 0;
    result->local_rpm_present = snapshot->local_rpm_present ? 1 : 0;
    result->local_only = snapshot->network_required ? 0 : 1;

    if (snapshot->host_install_requested == 0) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_REPORT_ONLY,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_NOT_REQUESTED,
            result->fedora_host ? "fedora-host" : "unknown-host",
            "report-only");
        return LATTICRA_STATUS_OK;
    }

    if (!result->fedora_host) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_BLOCKED,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_NON_FEDORA_HOST,
            "non-fedora-host",
            "blocked-host-install");
        return LATTICRA_STATUS_OK;
    }

    if (result->immutable_host) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_FUTURE_GATED,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_IMMUTABLE_HOST,
            "immutable-fedora-host",
            "future-gated-rpm-ostree-host-install");
        return LATTICRA_STATUS_OK;
    }

    if (snapshot->network_required) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_BLOCKED,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_NETWORK_REQUIRED,
            "mutable-fedora-host",
            "blocked-network-required");
        return LATTICRA_STATUS_OK;
    }

    if (!result->rpm_available || !result->dnf_available) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_BLOCKED,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_REQUIRED_TOOLING_MISSING,
            "mutable-fedora-host",
            "blocked-missing-rpm-dnf");
        return LATTICRA_STATUS_OK;
    }

    if (!result->local_rpm_present) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_BLOCKED,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_LOCAL_RPM_MISSING,
            "mutable-fedora-host",
            "blocked-missing-local-rpm");
        return LATTICRA_STATUS_OK;
    }

    if (!snapshot->root_or_sudo_available) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_BLOCKED,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_PRIVILEGE_MISSING,
            "mutable-fedora-host",
            "blocked-operator-privilege-required");
        return LATTICRA_STATUS_OK;
    }

    if (snapshot->package_is_doc_only && snapshot->command_entrypoint_expected) {
        latticra_fedora_preflight_set_result(
            result,
            LATTICRA_FEDORA_PREFLIGHT_BLOCKED,
            LATTICRA_FEDORA_PREFLIGHT_DENIAL_RUNTIME_ENTRYPOINT_NOT_PRESENT,
            "mutable-fedora-host",
            "blocked-doc-only-package-runtime-command");
        return LATTICRA_STATUS_OK;
    }

    latticra_fedora_preflight_set_result(
        result,
        LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM,
        LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE,
        "mutable-fedora-host",
        snapshot->package_is_doc_only ? "local-doc-rpm" : "local-rpm");
    result->preflight_passed = 1;
    result->host_install_candidate = 1;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_fedora_host_install_preflight_report(
    const latticra_fedora_host_install_preflight_result_t *result,
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
        "FEDORA HOST INSTALL PREFLIGHT\n"
        "classification=%s\n"
        "denial=%s\n"
        "host_classification=%s\n"
        "install_lane=%s\n"
        "preflight_passed=%d\n"
        "host_install_candidate=%d\n"
        "host_install_performed=%d\n"
        "host_mutation_performed=%d\n"
        "network_allowed=%d\n"
        "local_only=%d\n"
        "fedora_host=%d\n"
        "mutable_fedora_host=%d\n"
        "immutable_host=%d\n"
        "rpm_available=%d\n"
        "dnf_available=%d\n"
        "rpmbuild_available=%d\n"
        "rpmlint_available=%d\n"
        "local_rpm_present=%d\n"
        "no_effect=%d\n"
        "evidence_level=%u\n",
        latticra_fedora_preflight_classification_label(result->classification),
        latticra_fedora_preflight_denial_label(result->denial),
        result->host_classification,
        result->install_lane,
        result->preflight_passed,
        result->host_install_candidate,
        result->host_install_performed,
        result->host_mutation_performed,
        result->network_allowed,
        result->local_only,
        result->fedora_host,
        result->mutable_fedora_host,
        result->immutable_host,
        result->rpm_available,
        result->dnf_available,
        result->rpmbuild_available,
        result->rpmlint_available,
        result->local_rpm_present,
        result->no_effect,
        result->evidence_level);

    if (written < 0 || (size_t)written >= buffer_len) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
