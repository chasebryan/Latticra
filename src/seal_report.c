#include "latticra/seal_report.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

latticra_seal_report_t latticra_seal_report_default(void) {
    latticra_seal_report_t report;
    memset(&report, 0, sizeof(report));

    copy_literal(report.seal_profile, sizeof(report.seal_profile), "latticra-seal/0.1-report");
    report.contract_present = 1u;
    report.implementation_plan_present = 1u;
    report.report_only_supported = 1u;
    report.measurement_supported = 0u;
    report.signing_supported = 0u;
    report.capability_gate_supported = 0u;
    report.sealed_objects_supported = 0u;
    report.effect_performed = 0u;
    report.host_read_performed = 0u;
    report.host_write_performed = 0u;
    report.network_performed = 0u;
    report.runtime_granted = 0u;
    report.evidence_level = 2u;
    copy_literal(report.status, sizeof(report.status), "report-only");
    copy_literal(
        report.note,
        sizeof(report.note),
        "no measurement, no signing, no sealing, no runtime authority");

    return report;
}

int latticra_seal_report_is_no_effect(const latticra_seal_report_t *report) {
    if (report == NULL) {
        return 0;
    }

    return report->effect_performed == 0u &&
           report->host_read_performed == 0u &&
           report->host_write_performed == 0u &&
           report->network_performed == 0u &&
           report->runtime_granted == 0u;
}

latticra_status_t latticra_seal_report_render(
    const latticra_seal_report_t *report,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (report == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL REPORT\n"
        "seal_profile=%s\n"
        "contract_present=%u\n"
        "implementation_plan_present=%u\n"
        "report_only_supported=%u\n"
        "measurement_supported=%u\n"
        "signing_supported=%u\n"
        "capability_gate_supported=%u\n"
        "sealed_objects_supported=%u\n"
        "effect_performed=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "runtime_granted=%u\n"
        "evidence_level=%u\n"
        "status=%s\n"
        "note=%s\n",
        report->seal_profile,
        report->contract_present,
        report->implementation_plan_present,
        report->report_only_supported,
        report->measurement_supported,
        report->signing_supported,
        report->capability_gate_supported,
        report->sealed_objects_supported,
        report->effect_performed,
        report->host_read_performed,
        report->host_write_performed,
        report->network_performed,
        report->runtime_granted,
        report->evidence_level,
        report->status,
        report->note);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
