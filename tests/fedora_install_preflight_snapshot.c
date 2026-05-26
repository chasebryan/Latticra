#include "latticra/fedora_install_preflight_snapshot.h"

#include <assert.h>
#include <string.h>

#define LOCAL_RPM_FIXTURE "fixtures/latticra.rpm"
#define LOCAL_RPM_FIXTURE_LEN (sizeof(LOCAL_RPM_FIXTURE) - 1u)

static void mutable_fedora_snapshot_reaches_classifier_candidate(void)
{
    const char os_release[] = "NAME=Fedora Linux\nID=fedora\nID_LIKE=\"rhel fedora\"\n";
    char report[LATTICRA_FEDORA_SNAPSHOT_REPORT_MAX];
    latticra_fedora_snapshot_capture_result_t result;
    latticra_fedora_snapshot_capture_input_t input = {
        os_release,
        sizeof(os_release) - 1u,
        1,
        1,
        0,
        1,
        1,
        1,
        0,
        LOCAL_RPM_FIXTURE,
        LOCAL_RPM_FIXTURE_LEN,
        1,
        1,
        0,
        0,
        1,
        0
    };

    assert(latticra_fedora_install_preflight_snapshot_capture(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.capture_status == LATTICRA_FEDORA_SNAPSHOT_CAPTURED);
    assert(strcmp(result.capture_status_label, "captured") == 0);
    assert(strcmp(result.os_id, "fedora") == 0);
    assert(strcmp(result.os_id_like, "rhel fedora") == 0);
    assert(strcmp(result.local_rpm_path, LOCAL_RPM_FIXTURE) == 0);
    assert(result.snapshot_forwarded_to_classifier == 1);
    assert(result.no_effect == 1);
    assert(result.sudo_validation_allowed == 0);
    assert(result.install_command_allowed == 0);
    assert(result.package_build_allowed == 0);
    assert(result.network_allowed == 0);
    assert(result.host_mutation_performed == 0);
    assert(result.host_install_performed == 0);
    assert(result.preflight.classification == LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM);
    assert(result.preflight.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE);
    assert(result.preflight.host_install_candidate == 1);
    assert(result.preflight.host_install_performed == 0);

    assert(latticra_fedora_install_preflight_snapshot_report(&result, report, sizeof(report)) ==
           LATTICRA_STATUS_OK);
    assert(strstr(report, "FEDORA INSTALL PREFLIGHT SNAPSHOT CAPTURE") != NULL);
    assert(strstr(report, "snapshot_capture_status=captured") != NULL);
    assert(strstr(report, "os_id=fedora") != NULL);
    assert(strstr(report, "classifier_classification=ready-local-rpm") != NULL);
    assert(strstr(report, "snapshot_forwarded_to_classifier=1") != NULL);
    assert(strstr(report, "sudo_validation_allowed=0") != NULL);
    assert(strstr(report, "install_command_allowed=0") != NULL);
    assert(strstr(report, "package_build_allowed=0") != NULL);
    assert(strstr(report, "network_allowed=0") != NULL);
    assert(strstr(report, "host_mutation_performed=0") != NULL);
    assert(strstr(report, "host_install_performed=0") != NULL);
    assert(strstr(report, "no_effect=1") != NULL);
}

static void immutable_fedora_snapshot_is_future_gated(void)
{
    const char os_release[] = "ID=\"fedora\"\n";
    latticra_fedora_snapshot_capture_result_t result;
    latticra_fedora_snapshot_capture_input_t input = {
        os_release,
        sizeof(os_release) - 1u,
        1,
        1,
        1,
        1,
        1,
        0,
        0,
        LOCAL_RPM_FIXTURE,
        LOCAL_RPM_FIXTURE_LEN,
        1,
        1,
        0,
        0,
        1,
        0
    };

    assert(latticra_fedora_install_preflight_snapshot_capture(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(strcmp(result.os_id, "fedora") == 0);
    assert(result.snapshot.immutable_host == 1);
    assert(result.preflight.classification == LATTICRA_FEDORA_PREFLIGHT_FUTURE_GATED);
    assert(result.preflight.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_IMMUTABLE_HOST);
    assert(strcmp(result.preflight.install_lane, "future-gated-rpm-ostree-host-install") == 0);
    assert(result.host_mutation_performed == 0);
    assert(result.host_install_performed == 0);
}

static void partial_unreadable_os_release_blocks_as_non_fedora(void)
{
    latticra_fedora_snapshot_capture_result_t result;
    latticra_fedora_snapshot_capture_input_t input = {
        NULL,
        0u,
        0,
        1,
        0,
        1,
        1,
        0,
        0,
        LOCAL_RPM_FIXTURE,
        LOCAL_RPM_FIXTURE_LEN,
        1,
        1,
        0,
        0,
        1,
        0
    };

    assert(latticra_fedora_install_preflight_snapshot_capture(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.capture_status == LATTICRA_FEDORA_SNAPSHOT_PARTIAL);
    assert(strcmp(result.capture_status_label, "partial") == 0);
    assert(strcmp(result.os_id, "") == 0);
    assert(result.snapshot_forwarded_to_classifier == 1);
    assert(result.preflight.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.preflight.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NON_FEDORA_HOST);
    assert(result.no_effect == 1);
}

static void doc_only_package_blocks_runtime_command_expectation(void)
{
    const char os_release[] = "ID=fedora\n";
    latticra_fedora_snapshot_capture_result_t result;
    latticra_fedora_snapshot_capture_input_t input = {
        os_release,
        sizeof(os_release) - 1u,
        1,
        1,
        0,
        1,
        1,
        1,
        1,
        LOCAL_RPM_FIXTURE,
        LOCAL_RPM_FIXTURE_LEN,
        1,
        1,
        0,
        0,
        1,
        1
    };

    assert(latticra_fedora_install_preflight_snapshot_capture(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.preflight.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.preflight.denial ==
           LATTICRA_FEDORA_PREFLIGHT_DENIAL_RUNTIME_ENTRYPOINT_NOT_PRESENT);
    assert(strcmp(result.preflight.install_lane,
                  "blocked-doc-only-package-runtime-command") == 0);
    assert(result.host_mutation_performed == 0);
    assert(result.host_install_performed == 0);
}

static void network_requirement_is_forwarded_and_blocked(void)
{
    const char os_release[] = "ID=fedora\n";
    latticra_fedora_snapshot_capture_result_t result;
    latticra_fedora_snapshot_capture_input_t input = {
        os_release,
        sizeof(os_release) - 1u,
        1,
        1,
        0,
        1,
        1,
        1,
        1,
        LOCAL_RPM_FIXTURE,
        LOCAL_RPM_FIXTURE_LEN,
        1,
        1,
        0,
        1,
        1,
        0
    };

    assert(latticra_fedora_install_preflight_snapshot_capture(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.snapshot.network_required == 1);
    assert(result.network_allowed == 0);
    assert(result.preflight.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.preflight.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NETWORK_REQUIRED);
}

static void null_arguments_and_small_reports_are_rejected(void)
{
    const char os_release[] = "ID=fedora\n";
    char tiny[8];
    latticra_fedora_snapshot_capture_result_t result;
    latticra_fedora_snapshot_capture_input_t input = {
        os_release,
        sizeof(os_release) - 1u,
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        NULL,
        0u,
        0,
        0,
        0,
        0,
        1,
        0
    };

    assert(latticra_fedora_install_preflight_snapshot_capture(NULL, &result) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_install_preflight_snapshot_capture(&input, NULL) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_install_preflight_snapshot_capture(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(latticra_fedora_install_preflight_snapshot_report(NULL, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_install_preflight_snapshot_report(&result, NULL, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_install_preflight_snapshot_report(&result, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_BUFFER_TOO_SMALL);
}

int main(void)
{
    mutable_fedora_snapshot_reaches_classifier_candidate();
    immutable_fedora_snapshot_is_future_gated();
    partial_unreadable_os_release_blocks_as_non_fedora();
    doc_only_package_blocks_runtime_command_expectation();
    network_requirement_is_forwarded_and_blocked();
    null_arguments_and_small_reports_are_rejected();
    return 0;
}
