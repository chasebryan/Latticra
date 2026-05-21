#ifndef LATTICRA_SEAL_REPORT_H
#define LATTICRA_SEAL_REPORT_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_PROFILE_MAX 64u
#define LATTICRA_SEAL_STATUS_MAX 64u
#define LATTICRA_SEAL_NOTE_MAX 256u
#define LATTICRA_SEAL_REPORT_MAX 2048u

typedef struct {
    char seal_profile[LATTICRA_SEAL_PROFILE_MAX];
    unsigned contract_present;
    unsigned implementation_plan_present;
    unsigned report_only_supported;
    unsigned measurement_supported;
    unsigned signing_supported;
    unsigned capability_gate_supported;
    unsigned sealed_objects_supported;
    unsigned effect_performed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    unsigned runtime_granted;
    unsigned evidence_level;
    char status[LATTICRA_SEAL_STATUS_MAX];
    char note[LATTICRA_SEAL_NOTE_MAX];
} latticra_seal_report_t;

latticra_seal_report_t latticra_seal_report_default(void);
int latticra_seal_report_is_no_effect(const latticra_seal_report_t *report);
latticra_status_t latticra_seal_report_render(
    const latticra_seal_report_t *report,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
