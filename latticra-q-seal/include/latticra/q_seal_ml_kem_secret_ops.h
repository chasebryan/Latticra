#ifndef LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS_H
#define LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS_H

#include "latticra/q_seal.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

latticra_q_seal_status_t latticra_q_seal_ml_kem_secure_zero(
    void *buffer,
    size_t buffer_len);
latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_equal(
    const unsigned char *left,
    const unsigned char *right,
    size_t buffer_len,
    unsigned *equal);
latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_select(
    unsigned char *out,
    const unsigned char *if_nonzero,
    const unsigned char *if_zero,
    size_t buffer_len,
    unsigned select);

#ifdef __cplusplus
}
#endif

#endif
