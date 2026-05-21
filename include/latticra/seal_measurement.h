#ifndef LATTICRA_SEAL_MEASUREMENT_H
#define LATTICRA_SEAL_MEASUREMENT_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_MEASUREMENT_PROFILE_MAX 64u
#define LATTICRA_SEAL_MEASUREMENT_ALGORITHM_MAX 16u
#define LATTICRA_SEAL_MEASUREMENT_LABEL_MAX 128u
#define LATTICRA_SEAL_MEASUREMENT_DIGEST_HEX_MAX 65u
#define LATTICRA_SEAL_MEASUREMENT_STATUS_MAX 64u
#define LATTICRA_SEAL_MEASUREMENT_REPORT_MAX 2048u

typedef enum {
    LATTICRA_SEAL_MEASUREMENT_OK = 0,
    LATTICRA_SEAL_MEASUREMENT_INVALID_INPUT = 1,
    LATTICRA_SEAL_MEASUREMENT_NOT_REGULAR = 2,
    LATTICRA_SEAL_MEASUREMENT_OPEN_FAILED = 3,
    LATTICRA_SEAL_MEASUREMENT_READ_FAILED = 4
} latticra_seal_measurement_error_t;

typedef struct {
    char measurement_profile[LATTICRA_SEAL_MEASUREMENT_PROFILE_MAX];
    char algorithm[LATTICRA_SEAL_MEASUREMENT_ALGORITHM_MAX];
    char artifact_label[LATTICRA_SEAL_MEASUREMENT_LABEL_MAX];
    unsigned long artifact_size_bytes;
    char digest_hex[LATTICRA_SEAL_MEASUREMENT_DIGEST_HEX_MAX];
    unsigned read_performed;
    unsigned write_performed;
    unsigned network_performed;
    unsigned runtime_granted;
    latticra_seal_measurement_error_t error;
    char status[LATTICRA_SEAL_MEASUREMENT_STATUS_MAX];
} latticra_seal_measurement_t;

const char *latticra_seal_measurement_error_label(latticra_seal_measurement_error_t error);
latticra_status_t latticra_seal_measure_file(
    const char *path,
    latticra_seal_measurement_t *out);
int latticra_seal_measurement_is_read_only(const latticra_seal_measurement_t *measurement);
latticra_status_t latticra_seal_measurement_report(
    const latticra_seal_measurement_t *measurement,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
