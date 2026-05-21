#include "latticra/fedora_rpm_removal_rollback.h"

#include <assert.h>
#include <string.h>

static latticra_fedora_rpm_removal_rollback_input_t ready_input(void)
{
    latticra_fedora_rpm_removal_rollback_input_t input;
    memset(&input, 0, sizeof(input));
    input.operator_removal_confirmation = 1;
    input.package_name = "latticra";
    input.package_name_len = strlen(input.package_name);
    input.package_identity_present = 1;
    input.package_query_ready = 1;
    input.installed_package_detected = 1;
    input.owned_file_list_available = 1;
    input.readme_owned_by_package = 1;
    input.unexpected_runtime_surface_absent = 1;
    input.post_removal_absence_check_planned = 1;
    input.failure_report_planned = 1;
    return input;
}

static latticra_fedora_rpm_removal_rollback_result_t classify(
    latticra_fedora_rpm_removal_rollback_input_t input)
{
    latticra_fedora_rpm_removal_rollback_result_t result;
    assert(latticra_fedora_rpm_removal_rollback_classify(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.removal_performed == 0);
    assert(result.host_mutation_performed == 0);
    assert(result.network_allowed == 0);
    return result;
}

static void ready_case_reports_ready_without_mutation(void)
{
    char report[LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_REPORT_MAX];
    latticra_fedora_rpm_removal_rollback_result_t result = classify(ready_input());

    assert(result.status == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_READY);
    assert(result.denial == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NONE);
    assert(result.partial_state == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_NONE);
    assert(result.removal_allowed == 1);
    assert(result.rollback_planned == 1);
    assert(result.partial_failure_report_required == 0);
    assert(result.service_operation_allowed == 0);
    assert(result.boot_operation_allowed == 0);
    assert(result.kernel_operation_allowed == 0);
    assert(result.policy_operation_allowed == 0);
    assert(result.evidence_level == 5u);

    assert(latticra_fedora_rpm_removal_rollback_report(&result, report, sizeof(report)) ==
           LATTICRA_STATUS_OK);
    assert(strstr(report, "FEDORA RPM REMOVAL ROLLBACK CLASSIFIER") != NULL);
    assert(strstr(report, "removal_rollback_status=removal-ready") != NULL);
    assert(strstr(report, "removal_rollback_denial=none") != NULL);
    assert(strstr(report, "partial_state=none") != NULL);
    assert(strstr(report, "package_name=latticra") != NULL);
    assert(strstr(report, "removal_allowed=1") != NULL);
    assert(strstr(report, "rollback_planned=1") != NULL);
    assert(strstr(report, "removal_performed=0") != NULL);
    assert(strstr(report, "host_mutation_performed=0") != NULL);
    assert(strstr(report, "network_allowed=0") != NULL);
    assert(strstr(report, "evidence_level=5") != NULL);
}

static void denial_cases_fail_closed(void)
{
    latticra_fedora_rpm_removal_rollback_input_t input;
    latticra_fedora_rpm_removal_rollback_result_t result;

    input = ready_input();
    input.operator_removal_confirmation = 0;
    result = classify(input);
    assert(result.status == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIED);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OPERATOR_CONFIRMATION_MISSING);
    assert(result.removal_allowed == 0);

    input = ready_input();
    input.package_name = "not-latticra";
    input.package_name_len = strlen(input.package_name);
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NAME_MISMATCH);
    assert(strcmp(result.package_name, "not-latticra") == 0);

    input = ready_input();
    input.network_required = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NETWORK_REQUIRED);
    assert(result.network_allowed == 0);

    input = ready_input();
    input.service_operation_requested = 1;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_SERVICE_OPERATION_REQUESTED);

    input = ready_input();
    input.boot_operation_requested = 1;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_BOOT_OPERATION_REQUESTED);

    input = ready_input();
    input.kernel_operation_requested = 1;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_KERNEL_OPERATION_REQUESTED);

    input = ready_input();
    input.policy_operation_requested = 1;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_POLICY_OPERATION_REQUESTED);

    input = ready_input();
    input.installed_package_detected = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NOT_INSTALLED);
}

static void partial_cases_require_failure_reporting_without_removal(void)
{
    char report[LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_REPORT_MAX];
    latticra_fedora_rpm_removal_rollback_input_t input;
    latticra_fedora_rpm_removal_rollback_result_t result;

    input = ready_input();
    input.owned_file_list_available = 0;
    result = classify(input);
    assert(result.status == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL);
    assert(result.denial ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OWNED_FILE_LIST_MISSING);
    assert(result.partial_state ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_PACKAGE_INSTALLED_OWNERSHIP_UNKNOWN);
    assert(result.partial_failure_report_required == 1);
    assert(result.removal_allowed == 0);

    assert(latticra_fedora_rpm_removal_rollback_report(&result, report, sizeof(report)) ==
           LATTICRA_STATUS_OK);
    assert(strstr(report, "removal_rollback_status=partial") != NULL);
    assert(strstr(report, "partial_state=package-installed-but-ownership-unknown") != NULL);
    assert(strstr(report, "partial_failure_report_required=1") != NULL);

    input = ready_input();
    input.package_query_ready = 0;
    input.owned_file_list_available = 1;
    result = classify(input);
    assert(result.partial_state ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_OWNED_FILES_PRESENT_PACKAGE_QUERY_FAILED);

    input = ready_input();
    input.unexpected_runtime_surface_absent = 0;
    result = classify(input);
    assert(result.partial_state ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_RUNTIME_SURFACE_PRESENT_BEFORE_REMOVAL);

    input = ready_input();
    input.post_removal_absence_check_planned = 0;
    result = classify(input);
    assert(result.partial_state ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_ABSENCE_CHECK_NOT_READY);
}

static void invalid_and_api_error_cases_are_bounded(void)
{
    char tiny[4];
    latticra_fedora_rpm_removal_rollback_input_t input = ready_input();
    latticra_fedora_rpm_removal_rollback_result_t result;

    input.failure_report_planned = 2;
    result = classify(input);
    assert(result.status == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_INVALID);
    assert(result.denial == LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_INVALID_INPUT);
    assert(result.partial_state ==
           LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_UNKNOWN_HOST_STATE);
    assert(result.removal_allowed == 0);

    assert(latticra_fedora_rpm_removal_rollback_classify(NULL, &result) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_removal_rollback_classify(&input, NULL) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_removal_rollback_report(NULL, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_removal_rollback_report(&result, NULL, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_removal_rollback_report(&result, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_BUFFER_TOO_SMALL);
}

int main(void)
{
    ready_case_reports_ready_without_mutation();
    denial_cases_fail_closed();
    partial_cases_require_failure_reporting_without_removal();
    invalid_and_api_error_cases_are_bounded();
    return 0;
}
