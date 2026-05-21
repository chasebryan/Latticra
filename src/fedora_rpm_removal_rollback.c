#include "latticra/fedora_rpm_removal_rollback.h"

#include <stdio.h>
#include <string.h>

static int bit(int v) { return v == 0 || v == 1; }

static void copy_slice(char *dst, size_t dst_len, const char *src, size_t src_len)
{
    size_t n;
    if (dst == NULL || dst_len == 0u) {
        return;
    }
    if (src == NULL) {
        dst[0] = '\0';
        return;
    }
    n = src_len;
    if (n >= dst_len) {
        n = dst_len - 1u;
    }
    if (n > 0u) {
        memcpy(dst, src, n);
    }
    dst[n] = '\0';
}

static int slice_eq(const char *src, size_t src_len, const char *want)
{
    size_t want_len;
    if (src == NULL || want == NULL) {
        return 0;
    }
    want_len = strlen(want);
    return src_len == want_len && memcmp(src, want, want_len) == 0;
}

const char *latticra_fedora_rpm_removal_rollback_status_label(
    latticra_fedora_rpm_removal_rollback_status_t status)
{
    switch (status) {
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_READY:
        return "removal-ready";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIED:
        return "denied";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL:
        return "partial";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_INVALID:
        return "invalid";
    default:
        return "unknown";
    }
}

const char *latticra_fedora_rpm_removal_rollback_denial_label(
    latticra_fedora_rpm_removal_rollback_denial_t denial)
{
    switch (denial) {
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NONE:
        return "none";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OPERATOR_CONFIRMATION_MISSING:
        return "operator-confirmation-missing";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NAME_MISMATCH:
        return "package-name-mismatch";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_IDENTITY_MISSING:
        return "package-identity-missing";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_QUERY_NOT_READY:
        return "package-query-not-ready";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NOT_INSTALLED:
        return "package-not-installed";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OWNED_FILE_LIST_MISSING:
        return "owned-file-list-missing";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_README_OWNERSHIP_MISSING:
        return "readme-ownership-missing";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_UNEXPECTED_RUNTIME_SURFACE_PRESENT:
        return "unexpected-runtime-surface-present";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_POST_REMOVAL_CHECK_MISSING:
        return "post-removal-check-missing";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_FAILURE_REPORT_MISSING:
        return "failure-report-missing";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NETWORK_REQUIRED:
        return "network-required";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_SERVICE_OPERATION_REQUESTED:
        return "service-operation-requested";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_BOOT_OPERATION_REQUESTED:
        return "boot-operation-requested";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_KERNEL_OPERATION_REQUESTED:
        return "kernel-operation-requested";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_POLICY_OPERATION_REQUESTED:
        return "policy-operation-requested";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_INVALID_INPUT:
        return "invalid-classifier-input";
    default:
        return "unknown";
    }
}

const char *latticra_fedora_rpm_removal_rollback_partial_label(
    latticra_fedora_rpm_removal_rollback_partial_t partial_state)
{
    switch (partial_state) {
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_NONE:
        return "none";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_PACKAGE_INSTALLED_OWNERSHIP_UNKNOWN:
        return "package-installed-but-ownership-unknown";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_OWNED_FILES_PRESENT_PACKAGE_QUERY_FAILED:
        return "owned-files-present-but-package-query-failed";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_RUNTIME_SURFACE_PRESENT_BEFORE_REMOVAL:
        return "runtime-surface-present-before-removal";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_ABSENCE_CHECK_NOT_READY:
        return "absence-check-not-ready";
    case LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_UNKNOWN_HOST_STATE:
        return "unknown-host-state";
    default:
        return "unknown";
    }
}

static void deny(latticra_fedora_rpm_removal_rollback_result_t *r,
    latticra_fedora_rpm_removal_rollback_denial_t d)
{
    r->status = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIED;
    r->denial = d;
    r->partial_state = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_NONE;
    r->removal_allowed = 0;
    r->rollback_planned = 0;
}

static void partial(latticra_fedora_rpm_removal_rollback_result_t *r,
    latticra_fedora_rpm_removal_rollback_denial_t d,
    latticra_fedora_rpm_removal_rollback_partial_t p)
{
    r->status = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL;
    r->denial = d;
    r->partial_state = p;
    r->removal_allowed = 0;
    r->rollback_planned = 1;
    r->partial_failure_report_required = 1;
}

static void invalid(latticra_fedora_rpm_removal_rollback_result_t *r)
{
    r->status = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_INVALID;
    r->denial = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_INVALID_INPUT;
    r->partial_state = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_UNKNOWN_HOST_STATE;
    r->removal_allowed = 0;
    r->rollback_planned = 0;
}

static int valid_input(const latticra_fedora_rpm_removal_rollback_input_t *in)
{
    return in->package_name != NULL && in->package_name_len > 0u &&
           in->package_name_len < LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PACKAGE_MAX &&
           bit(in->operator_removal_confirmation) && bit(in->package_identity_present) &&
           bit(in->package_query_ready) && bit(in->installed_package_detected) &&
           bit(in->owned_file_list_available) && bit(in->readme_owned_by_package) &&
           bit(in->unexpected_runtime_surface_absent) &&
           bit(in->post_removal_absence_check_planned) && bit(in->failure_report_planned) &&
           bit(in->network_required) && bit(in->service_operation_requested) &&
           bit(in->boot_operation_requested) && bit(in->kernel_operation_requested) &&
           bit(in->policy_operation_requested);
}

static void mirror_input(
    const latticra_fedora_rpm_removal_rollback_input_t *in,
    latticra_fedora_rpm_removal_rollback_result_t *r)
{
    copy_slice(r->package_name, sizeof(r->package_name), in->package_name, in->package_name_len);
    r->operator_removal_confirmation = in->operator_removal_confirmation;
    r->package_identity_present = in->package_identity_present;
    r->package_query_ready = in->package_query_ready;
    r->installed_package_detected = in->installed_package_detected;
    r->owned_file_list_available = in->owned_file_list_available;
    r->readme_owned_by_package = in->readme_owned_by_package;
    r->unexpected_runtime_surface_absent = in->unexpected_runtime_surface_absent;
    r->post_removal_absence_check_planned = in->post_removal_absence_check_planned;
    r->failure_report_planned = in->failure_report_planned;
    r->network_required = in->network_required;
    r->service_operation_requested = in->service_operation_requested;
    r->boot_operation_requested = in->boot_operation_requested;
    r->kernel_operation_requested = in->kernel_operation_requested;
    r->policy_operation_requested = in->policy_operation_requested;
}

latticra_status_t latticra_fedora_rpm_removal_rollback_classify(
    const latticra_fedora_rpm_removal_rollback_input_t *in,
    latticra_fedora_rpm_removal_rollback_result_t *r)
{
    if (in == NULL || r == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(r, 0, sizeof(*r));
    r->classifier_evaluated = 1;
    r->removal_performed = 0;
    r->host_mutation_performed = 0;
    r->network_allowed = 0;
    r->service_operation_allowed = 0;
    r->boot_operation_allowed = 0;
    r->kernel_operation_allowed = 0;
    r->policy_operation_allowed = 0;
    r->evidence_level = 5u;

    if (!valid_input(in)) {
        invalid(r);
        return LATTICRA_STATUS_OK;
    }

    mirror_input(in, r);

    if (!slice_eq(in->package_name, in->package_name_len, "latticra")) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NAME_MISMATCH);
    } else if (r->network_required) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NETWORK_REQUIRED);
    } else if (r->service_operation_requested) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_SERVICE_OPERATION_REQUESTED);
    } else if (r->boot_operation_requested) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_BOOT_OPERATION_REQUESTED);
    } else if (r->kernel_operation_requested) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_KERNEL_OPERATION_REQUESTED);
    } else if (r->policy_operation_requested) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_POLICY_OPERATION_REQUESTED);
    } else if (!r->operator_removal_confirmation) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OPERATOR_CONFIRMATION_MISSING);
    } else if (!r->package_identity_present) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_IDENTITY_MISSING);
    } else if (!r->package_query_ready && r->owned_file_list_available) {
        partial(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_QUERY_NOT_READY,
            LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_OWNED_FILES_PRESENT_PACKAGE_QUERY_FAILED);
    } else if (!r->package_query_ready) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_QUERY_NOT_READY);
    } else if (!r->installed_package_detected) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NOT_INSTALLED);
    } else if (!r->owned_file_list_available) {
        partial(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OWNED_FILE_LIST_MISSING,
            LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_PACKAGE_INSTALLED_OWNERSHIP_UNKNOWN);
    } else if (!r->readme_owned_by_package) {
        partial(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_README_OWNERSHIP_MISSING,
            LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_PACKAGE_INSTALLED_OWNERSHIP_UNKNOWN);
    } else if (!r->unexpected_runtime_surface_absent) {
        partial(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_UNEXPECTED_RUNTIME_SURFACE_PRESENT,
            LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_RUNTIME_SURFACE_PRESENT_BEFORE_REMOVAL);
    } else if (!r->post_removal_absence_check_planned) {
        partial(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_POST_REMOVAL_CHECK_MISSING,
            LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_ABSENCE_CHECK_NOT_READY);
    } else if (!r->failure_report_planned) {
        deny(r, LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_FAILURE_REPORT_MISSING);
    } else {
        r->status = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_READY;
        r->denial = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NONE;
        r->partial_state = LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_NONE;
        r->removal_allowed = 1;
        r->rollback_planned = 1;
        r->partial_failure_report_required = 0;
    }

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_fedora_rpm_removal_rollback_report(
    const latticra_fedora_rpm_removal_rollback_result_t *r,
    char *buffer,
    size_t buffer_len)
{
    int n;
    if (r == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    n = snprintf(buffer, buffer_len,
        "FEDORA RPM REMOVAL ROLLBACK CLASSIFIER\n"
        "removal_rollback_status=%s\n"
        "removal_rollback_denial=%s\n"
        "partial_state=%s\n"
        "package_name=%s\n"
        "operator_removal_confirmation=%d\n"
        "package_identity_present=%d\n"
        "package_query_ready=%d\n"
        "installed_package_detected=%d\n"
        "owned_file_list_available=%d\n"
        "readme_owned_by_package=%d\n"
        "unexpected_runtime_surface_absent=%d\n"
        "post_removal_absence_check_planned=%d\n"
        "failure_report_planned=%d\n"
        "network_required=%d\n"
        "service_operation_requested=%d\n"
        "boot_operation_requested=%d\n"
        "kernel_operation_requested=%d\n"
        "policy_operation_requested=%d\n"
        "classifier_evaluated=%d\n"
        "removal_allowed=%d\n"
        "rollback_planned=%d\n"
        "partial_failure_report_required=%d\n"
        "removal_performed=%d\n"
        "host_mutation_performed=%d\n"
        "network_allowed=%d\n"
        "service_operation_allowed=%d\n"
        "boot_operation_allowed=%d\n"
        "kernel_operation_allowed=%d\n"
        "policy_operation_allowed=%d\n"
        "evidence_level=%u\n",
        latticra_fedora_rpm_removal_rollback_status_label(r->status),
        latticra_fedora_rpm_removal_rollback_denial_label(r->denial),
        latticra_fedora_rpm_removal_rollback_partial_label(r->partial_state),
        r->package_name, r->operator_removal_confirmation, r->package_identity_present,
        r->package_query_ready, r->installed_package_detected, r->owned_file_list_available,
        r->readme_owned_by_package, r->unexpected_runtime_surface_absent,
        r->post_removal_absence_check_planned, r->failure_report_planned,
        r->network_required, r->service_operation_requested, r->boot_operation_requested,
        r->kernel_operation_requested, r->policy_operation_requested, r->classifier_evaluated,
        r->removal_allowed, r->rollback_planned, r->partial_failure_report_required,
        r->removal_performed, r->host_mutation_performed, r->network_allowed,
        r->service_operation_allowed, r->boot_operation_allowed, r->kernel_operation_allowed,
        r->policy_operation_allowed, r->evidence_level);
    if (n < 0 || (size_t)n >= buffer_len) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
