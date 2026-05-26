#include "latticra/fedora_rpm_gate.h"

#include <assert.h>
#include <string.h>

#define LOCAL_RPM_FIXTURE "fixtures/latticra.rpm"

static latticra_fedora_rpm_gate_input_t allowed_input(void)
{
    latticra_fedora_rpm_gate_input_t input;

    memset(&input, 0, sizeof(input));
    input.fedora_host = 1;
    input.mutable_fedora_host = 1;
    input.immutable_host = 0;
    input.local_rpm_present = 1;
    input.local_rpm_path = LOCAL_RPM_FIXTURE;
    input.local_rpm_path_len = strlen(input.local_rpm_path);
    input.root_or_sudo_available = 1;
    input.network_required = 0;
    input.operator_install_confirmation = 1;
    input.dry_run_passed = 1;
    input.rollback_or_remove_plan_present = 1;
    input.preflight_classification = LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM;
    input.preflight_denial = LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE;
    input.snapshot_captured = 1;
    input.live_probe_performed = 1;

    return input;
}

static void allowed_gate_reports_allowed_without_performing_mutation(void)
{
    char report[LATTICRA_FEDORA_RPM_GATE_REPORT_MAX];
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(result.gate_status == LATTICRA_FEDORA_RPM_GATE_ALLOWED);
    assert(result.denial == LATTICRA_FEDORA_RPM_GATE_DENIAL_NONE);
    assert(result.install_mutation_allowed == 1);
    assert(result.install_mutation_performed == 0);
    assert(result.host_mutation_performed == 0);
    assert(result.network_allowed == 0);
    assert(result.evidence_level == 4u);
    assert(strcmp(result.local_rpm_path, LOCAL_RPM_FIXTURE) == 0);

    assert(latticra_fedora_rpm_gate_report(&result, report, sizeof(report)) ==
           LATTICRA_STATUS_OK);
    assert(strstr(report, "FEDORA LOCAL RPM INSTALL MUTATION GATE") != NULL);
    assert(strstr(report, "install_gate_status=allowed") != NULL);
    assert(strstr(report, "install_gate_denial=none") != NULL);
    assert(strstr(report, "install_mutation_allowed=1") != NULL);
    assert(strstr(report, "install_mutation_performed=0") != NULL);
    assert(strstr(report, "host_mutation_performed=0") != NULL);
    assert(strstr(report, "network_allowed=0") != NULL);
    assert(strstr(report, "evidence_level=4") != NULL);
}

static void missing_confirmation_denies_gate(void)
{
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    input.operator_install_confirmation = 0;
    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(result.gate_status == LATTICRA_FEDORA_RPM_GATE_DENIED);
    assert(result.denial == LATTICRA_FEDORA_RPM_GATE_DENIAL_OPERATOR_CONFIRMATION_MISSING);
    assert(result.install_mutation_allowed == 0);
    assert(result.install_mutation_performed == 0);
    assert(result.host_mutation_performed == 0);
}

static void missing_dry_run_denies_gate(void)
{
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    input.dry_run_passed = 0;
    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(result.gate_status == LATTICRA_FEDORA_RPM_GATE_DENIED);
    assert(result.denial == LATTICRA_FEDORA_RPM_GATE_DENIAL_DRY_RUN_MISSING);
    assert(result.install_mutation_allowed == 0);
}

static void missing_rollback_plan_denies_gate(void)
{
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    input.rollback_or_remove_plan_present = 0;
    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(result.gate_status == LATTICRA_FEDORA_RPM_GATE_DENIED);
    assert(result.denial == LATTICRA_FEDORA_RPM_GATE_DENIAL_ROLLBACK_PLAN_MISSING);
    assert(result.install_mutation_allowed == 0);
}

static void non_fedora_host_denies_gate(void)
{
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    input.fedora_host = 0;
    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(result.gate_status == LATTICRA_FEDORA_RPM_GATE_DENIED);
    assert(result.denial == LATTICRA_FEDORA_RPM_GATE_DENIAL_NOT_FEDORA_HOST);
    assert(result.install_mutation_allowed == 0);
}

static void immutable_fedora_host_denies_gate(void)
{
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    input.immutable_host = 1;
    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(result.gate_status == LATTICRA_FEDORA_RPM_GATE_DENIED);
    assert(result.denial == LATTICRA_FEDORA_RPM_GATE_DENIAL_IMMUTABLE_FEDORA_HOST);
    assert(result.install_mutation_allowed == 0);
}

static void preflight_denial_denies_gate(void)
{
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    input.preflight_denial = LATTICRA_FEDORA_PREFLIGHT_DENIAL_LOCAL_RPM_MISSING;
    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(result.gate_status == LATTICRA_FEDORA_RPM_GATE_DENIED);
    assert(result.denial == LATTICRA_FEDORA_RPM_GATE_DENIAL_PREFLIGHT_DENIED);
    assert(result.install_mutation_allowed == 0);
}

static void null_arguments_and_small_report_are_rejected(void)
{
    char tiny[8];
    latticra_fedora_rpm_gate_result_t result;
    latticra_fedora_rpm_gate_input_t input = allowed_input();

    assert(latticra_fedora_rpm_gate_classify(NULL, &result) == LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_gate_classify(&input, NULL) == LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_gate_classify(&input, &result) == LATTICRA_STATUS_OK);
    assert(latticra_fedora_rpm_gate_report(NULL, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_gate_report(&result, NULL, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_rpm_gate_report(&result, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_BUFFER_TOO_SMALL);
}

int main(void)
{
    allowed_gate_reports_allowed_without_performing_mutation();
    missing_confirmation_denies_gate();
    missing_dry_run_denies_gate();
    missing_rollback_plan_denies_gate();
    non_fedora_host_denies_gate();
    immutable_fedora_host_denies_gate();
    preflight_denial_denies_gate();
    null_arguments_and_small_report_are_rejected();
    return 0;
}
