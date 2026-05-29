#if defined(__APPLE__) && !defined(_DARWIN_C_SOURCE)
#define _DARWIN_C_SOURCE
#endif
#define _POSIX_C_SOURCE 200809L
#ifdef __APPLE__
#define _DARWIN_C_SOURCE 1
#endif

#include "latticra/fedora_live_snapshot_adapter.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void write_text_file(const char *path, const char *text)
{
    FILE *file = fopen(path, "wb");
    assert(file != NULL);
    assert(fputs(text, file) >= 0);
    assert(fclose(file) == 0);
}

static void write_executable(const char *path)
{
    write_text_file(path, "#!/bin/sh\nexit 0\n");
    assert(chmod(path, 0700) == 0);
}

static void join_path(char *buffer, size_t buffer_len, const char *dir, const char *name)
{
    int written = snprintf(buffer, buffer_len, "%s/%s", dir, name);
    assert(written > 0);
    assert((size_t)written < buffer_len);
}

static const char *private_tmp_root(void)
{
    const char *root = getenv("TMPDIR");
    return (root != NULL && root[0] != '\0') ? root : "/tmp";
}

static void setup_fake_path(char *dir_template, size_t dir_template_len)
{
    char command_path[512];
    const char *tmp_root = private_tmp_root();
    const char *separator = tmp_root[strlen(tmp_root) - 1u] == '/' ? "" : "/";
    int written;
    char *dir;

    written = snprintf(dir_template,
                       dir_template_len,
                       "%s%slatticra-fedora-live.XXXXXX",
                       tmp_root,
                       separator);
    assert(written > 0);
    assert((size_t)written < dir_template_len);
    dir = mkdtemp(dir_template);
    assert(dir != NULL);

    join_path(command_path, sizeof(command_path), dir, "rpm");
    write_executable(command_path);
    join_path(command_path, sizeof(command_path), dir, "dnf");
    write_executable(command_path);
    join_path(command_path, sizeof(command_path), dir, "rpmbuild");
    write_executable(command_path);
    join_path(command_path, sizeof(command_path), dir, "rpmlint");
    write_executable(command_path);

    assert(setenv("PATH", dir, 1) == 0);
}

static void cleanup_fake_path(const char *dir)
{
    char command_path[512];

    join_path(command_path, sizeof(command_path), dir, "rpm");
    (void)remove(command_path);
    join_path(command_path, sizeof(command_path), dir, "dnf");
    (void)remove(command_path);
    join_path(command_path, sizeof(command_path), dir, "rpmbuild");
    (void)remove(command_path);
    join_path(command_path, sizeof(command_path), dir, "rpmlint");
    (void)remove(command_path);
    join_path(command_path, sizeof(command_path), dir, "os-release");
    (void)remove(command_path);
    join_path(command_path, sizeof(command_path), dir, "latticra.rpm");
    (void)remove(command_path);
    (void)rmdir(dir);
}

static void live_adapter_captures_fixture_and_forwards_to_classifier(void)
{
    char tmp_dir[1024];
    char os_release_path[512];
    char rpm_path[512];
    char report[LATTICRA_FEDORA_LIVE_ADAPTER_REPORT_MAX];
    latticra_fedora_live_snapshot_adapter_result_t result;
    latticra_fedora_live_snapshot_adapter_request_t request;

    setup_fake_path(tmp_dir, sizeof(tmp_dir));
    join_path(os_release_path, sizeof(os_release_path), tmp_dir, "os-release");
    join_path(rpm_path, sizeof(rpm_path), tmp_dir, "latticra.rpm");
    write_text_file(os_release_path, "NAME=Fedora Linux\nID=fedora\nID_LIKE=\"rhel fedora\"\n");
    write_text_file(rpm_path, "not a real rpm fixture\n");

    memset(&request, 0, sizeof(request));
    request.os_release_path = os_release_path;
    request.os_release_path_len = strlen(os_release_path);
    request.local_rpm_path = rpm_path;
    request.local_rpm_path_len = strlen(rpm_path);
    request.host_install_requested = 1;
    request.operator_privilege_assertion = 1;
    request.network_required = 0;
    request.package_is_doc_only = 1;
    request.command_entrypoint_expected = 0;

    assert(latticra_fedora_live_snapshot_adapter_capture(&request, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.adapter_status == LATTICRA_FEDORA_LIVE_ADAPTER_CAPTURED);
    assert(strcmp(result.adapter_status_label, "captured") == 0);
    assert(result.live_probe_performed == 1);
    assert(result.os_release_read_attempted == 1);
    assert(result.os_release_readable == 1);
    assert(result.command_probe_performed == 1);
    assert(result.local_rpm_probe_performed == 1);
    assert(result.rpm_command_present == 1);
    assert(result.dnf_command_present == 1);
    assert(result.rpmbuild_command_present == 1);
    assert(result.rpmlint_command_present == 1);
    assert(result.local_rpm_readable == 1);
    assert(result.no_effect == 1);
    assert(result.sudo_validation_allowed == 0);
    assert(result.install_command_allowed == 0);
    assert(result.package_build_allowed == 0);
    assert(result.network_allowed == 0);
    assert(result.host_mutation_performed == 0);
    assert(result.host_install_performed == 0);
    assert(result.capture.snapshot_forwarded_to_classifier == 1);
    assert(strcmp(result.capture.os_id, "fedora") == 0);
    assert(strcmp(result.capture.os_id_like, "rhel fedora") == 0);
    assert(result.capture.preflight.classification ==
           LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM);
    assert(result.capture.preflight.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE);

    assert(latticra_fedora_live_snapshot_adapter_report(&result, report, sizeof(report)) ==
           LATTICRA_STATUS_OK);
    assert(strstr(report, "FEDORA LIVE READ-ONLY SNAPSHOT ADAPTER") != NULL);
    assert(strstr(report, "adapter_status=captured") != NULL);
    assert(strstr(report, "live_probe_performed=1") != NULL);
    assert(strstr(report, "rpm_command_present=1") != NULL);
    assert(strstr(report, "classifier_classification=ready-local-rpm") != NULL);
    assert(strstr(report, "snapshot_forwarded_to_classifier=1") != NULL);
    assert(strstr(report, "sudo_validation_allowed=0") != NULL);
    assert(strstr(report, "install_command_allowed=0") != NULL);
    assert(strstr(report, "host_mutation_performed=0") != NULL);
    assert(strstr(report, "host_install_performed=0") != NULL);
    cleanup_fake_path(tmp_dir);
}

static void unreadable_os_release_becomes_partial_and_blocked(void)
{
    char tmp_dir[1024];
    char missing_path[512];
    char rpm_path[512];
    latticra_fedora_live_snapshot_adapter_result_t result;
    latticra_fedora_live_snapshot_adapter_request_t request;

    setup_fake_path(tmp_dir, sizeof(tmp_dir));
    join_path(missing_path, sizeof(missing_path), tmp_dir, "missing-os-release");
    join_path(rpm_path, sizeof(rpm_path), tmp_dir, "latticra.rpm");
    write_text_file(rpm_path, "fixture\n");

    memset(&request, 0, sizeof(request));
    request.os_release_path = missing_path;
    request.os_release_path_len = strlen(missing_path);
    request.local_rpm_path = rpm_path;
    request.local_rpm_path_len = strlen(rpm_path);
    request.host_install_requested = 1;
    request.operator_privilege_assertion = 1;
    request.package_is_doc_only = 1;

    assert(latticra_fedora_live_snapshot_adapter_capture(&request, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.adapter_status == LATTICRA_FEDORA_LIVE_ADAPTER_PARTIAL);
    assert(strcmp(result.adapter_status_label, "partial") == 0);
    assert(result.os_release_readable == 0);
    assert(result.capture.snapshot_forwarded_to_classifier == 1);
    assert(result.capture.preflight.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.capture.preflight.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_NON_FEDORA_HOST);
    assert(result.host_mutation_performed == 0);
    assert(result.host_install_performed == 0);
    cleanup_fake_path(tmp_dir);
}

static void missing_local_rpm_is_forwarded_as_blocked(void)
{
    char tmp_dir[1024];
    char os_release_path[512];
    char missing_rpm_path[512];
    latticra_fedora_live_snapshot_adapter_result_t result;
    latticra_fedora_live_snapshot_adapter_request_t request;

    setup_fake_path(tmp_dir, sizeof(tmp_dir));
    join_path(os_release_path, sizeof(os_release_path), tmp_dir, "os-release");
    join_path(missing_rpm_path, sizeof(missing_rpm_path), tmp_dir, "missing.rpm");
    write_text_file(os_release_path, "ID=fedora\n");

    memset(&request, 0, sizeof(request));
    request.os_release_path = os_release_path;
    request.os_release_path_len = strlen(os_release_path);
    request.local_rpm_path = missing_rpm_path;
    request.local_rpm_path_len = strlen(missing_rpm_path);
    request.host_install_requested = 1;
    request.operator_privilege_assertion = 1;
    request.package_is_doc_only = 1;

    assert(latticra_fedora_live_snapshot_adapter_capture(&request, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.local_rpm_readable == 0);
    assert(result.capture.preflight.classification == LATTICRA_FEDORA_PREFLIGHT_BLOCKED);
    assert(result.capture.preflight.denial == LATTICRA_FEDORA_PREFLIGHT_DENIAL_LOCAL_RPM_MISSING);
    assert(result.host_mutation_performed == 0);
    assert(result.host_install_performed == 0);
    cleanup_fake_path(tmp_dir);
}

static void null_arguments_and_small_report_are_rejected(void)
{
    char tiny[8];
    latticra_fedora_live_snapshot_adapter_request_t request;
    latticra_fedora_live_snapshot_adapter_result_t result;

    memset(&request, 0, sizeof(request));
    assert(latticra_fedora_live_snapshot_adapter_capture(NULL, &result) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_live_snapshot_adapter_capture(&request, NULL) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_live_snapshot_adapter_capture(&request, &result) ==
           LATTICRA_STATUS_OK);
    assert(latticra_fedora_live_snapshot_adapter_report(NULL, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_live_snapshot_adapter_report(&result, NULL, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_live_snapshot_adapter_report(&result, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_BUFFER_TOO_SMALL);
}

int main(void)
{
    live_adapter_captures_fixture_and_forwards_to_classifier();
    unreadable_os_release_becomes_partial_and_blocked();
    missing_local_rpm_is_forwarded_as_blocked();
    null_arguments_and_small_report_are_rejected();
    return 0;
}
