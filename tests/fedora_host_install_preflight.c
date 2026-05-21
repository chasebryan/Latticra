#include "latticra/fedora_host_install_preflight.h"

#include <assert.h>
#include <string.h>

static void ready_local_doc_rpm_preflight_is_no_effect(void)
{
    char report[LATTICRA_FEDORA_PREFLIGHT_REPORT_MAX];
    latticra_fedora_host_install_preflight_result_t result;
    latticra_fedora_host_install_preflight_snapshot_t snapshot = {
        "fedora",
        6u,
        "",
        0u,
        1,
        0,
        1,
        1,
        1,
        0,
        1,
        1,
        0,
        1,
        0
    };

    assert(latticra_fedora_host_install_preflight_classify(&snapshot, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.classification == LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM);
    assert(result.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE);
    assert(result.no_effect == 1);
    assert(result.fedora_host == 1);
    assert(result.mutable_fedora_host == 1);
    assert(result.immutable_host == 0);
    assert(result.preflight_passed == 1);
    assert(result.host_install_candidate == 1);
    assert(result.host_install_performed == 0);
    assert(result.host_mutation_performed == 0);
    assert(result.network_allowed == 0);
    assert(result.local_only == 1);
    assert(strcmp(result.host_classification, "mutable-fedora-host") == 0);
    assert(strcmp(result.install_lane, "local-doc-rpm") == 0);

    assert(latticra_fedora_host_install_preflight_report(
               &result,
               report,
               sizeof(report)) == LATTICRA_STATUS_OK);
    assert(strstr(report, "FEDORA HOST INSTALL PREFLIGHT") != NULL);
    assert(strstr(report, "classification=ready-local-rpm") != NULL);
    assert(strstr(report, "host_install_candidate=1") != NULL);
    assert(strstr(report, "host_install_performed=0") != NULL);
    assert(strstr(report, "host_mutation_performed=0") != NULL);
    assert(strstr(report, "network_allowed=0") != NULL);
    assert(strstr(report, "install_lane=local-doc-rpm") != NULL);
}

static void non_fedora_host_is_blocked(void)
{
    latticra_fedora_host_install_preflight_result_t result;
    latticra_fedora_host_install_preflight_snapshot_t snapshot = {
        "ubuntu",
        6u,
        "debian",
        6u,
        1,
        0,
        1,
        1,
        1,
        1,
        1,
        1,
        0,
        1,
        0
    };

    assert(latticra_fedora_host_install_preflight_classify(&snapshot, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NON_FEDORA_HOST);
    assert(result.fedora_host == 0);
    assert(result.preflight_passed == 0);
    assert(result.host_install_candidate == 0);
    assert(result.host_install_performed == 0);
    assert(strcmp(result.host_classification, "non-fedora-host") == 0);
}

static void immutable_fedora_host_is_future_gated(void)
{
    latticra_fedora_host_install_preflight_result_t result;
    latticra_fedora_host_install_preflight_snapshot_t snapshot = {
        "fedora",
        6u,
        "",
        0u,
        1,
        1,
        1,
        0,
        0,
        0,
        1,
        1,
        0,
        1,
        0
    };

    assert(latticra_fedora_host_install_preflight_classify(&snapshot, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.classification == LATTICRA_FEDORA_PREFLIGHT_FUTURE_GATED);
    assert(result.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_IMMUTABLE_HOST);
    assert(result.fedora_host == 1);
    assert(result.mutable_fedora_host == 0);
    assert(result.immutable_host == 1);
    assert(result.preflight_passed == 0);
    assert(strcmp(result.install_lane, "future-gated-rpm-ostree-host-install") == 0);
}

static void local_only_lane_blocks_network_requirement(void)
{
    latticra_fedora_host_install_preflight_result_t result;
    latticra_fedora_host_install_preflight_snapshot_t snapshot = {
        "fedora",
        6u,
        "",
        0u,
        1,
        0,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        0
    };

    assert(latticra_fedora_host_install_preflight_classify(&snapshot, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NETWORK_REQUIRED);
    assert(result.network_allowed == 0);
    assert(result.local_only == 0);
    assert(result.host_install_performed == 0);
    assert(strcmp(result.install_lane, "blocked-network-required") == 0);
}

static void required_tooling_is_classified_before_candidate(void)
{
    latticra_fedora_host_install_preflight_result_t result;
    latticra_fedora_host_install_preflight_snapshot_t snapshot = {
        "fedora",
        6u,
        "",
        0u,
        1,
        0,
        1,
        0,
        1,
        1,
        1,
        1,
        0,
        1,
        0
    };

    assert(latticra_fedora_host_install_preflight_classify(&snapshot, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_REQUIRED_TOOLING_MISSING);
    assert(result.preflight_passed == 0);
    assert(result.host_install_candidate == 0);
    assert(strcmp(result.install_lane, "blocked-missing-rpm-dnf") == 0);
}

static void doc_only_package_blocks_expected_runtime_command(void)
{
    latticra_fedora_host_install_preflight_result_t result;
    latticra_fedora_host_install_preflight_snapshot_t snapshot = {
        "fedora",
        6u,
        "",
        0u,
        1,
        0,
        1,
        1,
        1,
        1,
        1,
        1,
        0,
        1,
        1
    };

    assert(latticra_fedora_host_install_preflight_classify(&snapshot, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.denial ==
           LATTICRA_FEDORA_PREFLIGHT_DENIAL_RUNTIME_ENTRYPOINT_NOT_PRESENT);
    assert(result.host_install_candidate == 0);
    assert(result.host_install_performed == 0);
    assert(strcmp(result.install_lane, "blocked-doc-only-package-runtime-command") == 0);
}

static void null_arguments_are_rejected(void)
{
    latticra_fedora_host_install_preflight_result_t result;
    latticra_fedora_host_install_preflight_snapshot_t snapshot = {
        "fedora",
        6u,
        "",
        0u,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    };

    assert(latticra_fedora_host_install_preflight_classify(NULL, &result) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_host_install_preflight_classify(&snapshot, NULL) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_host_install_preflight_report(NULL, NULL, 0u) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
}

int main(void)
{
    ready_local_doc_rpm_preflight_is_no_effect();
    non_fedora_host_is_blocked();
    immutable_fedora_host_is_future_gated();
    local_only_lane_blocks_network_requirement();
    required_tooling_is_classified_before_candidate();
    doc_only_package_blocks_expected_runtime_command();
    null_arguments_are_rejected();
    return 0;
}
