#include "latticra/q_seal_ml_kem_secret_ops.h"

#include <limits.h>
#include <stdint.h>

latticra_q_seal_status_t latticra_q_seal_ml_kem_secure_zero(
    void *buffer,
    size_t buffer_len) {
    volatile unsigned char *cursor;

    if (buffer == NULL) {
        return buffer_len == 0u ? LATTICRA_Q_SEAL_STATUS_OK : LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    cursor = (volatile unsigned char *)buffer;
    while (buffer_len > 0u) {
        *cursor = 0u;
        cursor++;
        buffer_len--;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}

static unsigned nonzero_to_one(unsigned value) {
    unsigned bits = (unsigned)(sizeof(unsigned) * CHAR_BIT);

    return ((value | (0u - value)) >> (bits - 1u)) & 1u;
}

static int range_end_overflows(uintptr_t start, size_t buffer_len) {
    return buffer_len > (size_t)(UINTPTR_MAX - start);
}

static int byte_ranges_overlap(
    const unsigned char *left,
    const unsigned char *right,
    size_t buffer_len) {
    uintptr_t left_start;
    uintptr_t left_end;
    uintptr_t right_start;
    uintptr_t right_end;

    if (buffer_len == 0u || left == right) {
        return 0;
    }

    left_start = (uintptr_t)left;
    right_start = (uintptr_t)right;
    if (range_end_overflows(left_start, buffer_len) ||
        range_end_overflows(right_start, buffer_len)) {
        return 1;
    }

    left_end = left_start + (uintptr_t)buffer_len;
    right_end = right_start + (uintptr_t)buffer_len;
    return left_start < right_end && right_start < left_end;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_equal(
    const unsigned char *left,
    const unsigned char *right,
    size_t buffer_len,
    unsigned *equal) {
    unsigned char diff = 0u;
    size_t index;

    if (equal == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }
    *equal = 0u;

    if (buffer_len == 0u) {
        *equal = 1u;
        return LATTICRA_Q_SEAL_STATUS_OK;
    }
    if (left == NULL || right == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    for (index = 0u; index < buffer_len; index++) {
        diff = (unsigned char)(diff | (unsigned char)(left[index] ^ right[index]));
    }

    *equal = nonzero_to_one((unsigned)diff) ^ 1u;
    return LATTICRA_Q_SEAL_STATUS_OK;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_select(
    unsigned char *out,
    const unsigned char *if_nonzero,
    const unsigned char *if_zero,
    size_t buffer_len,
    unsigned select) {
    unsigned char mask;
    size_t index;

    if (buffer_len == 0u) {
        return LATTICRA_Q_SEAL_STATUS_OK;
    }
    if (out == NULL || if_nonzero == NULL || if_zero == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }
    if (byte_ranges_overlap(out, if_nonzero, buffer_len) ||
        byte_ranges_overlap(out, if_zero, buffer_len)) {
        return LATTICRA_Q_SEAL_STATUS_INVALID_ARGUMENT;
    }

    mask = (unsigned char)(0u - nonzero_to_one(select));
    for (index = 0u; index < buffer_len; index++) {
        unsigned char nonzero_byte = if_nonzero[index];
        unsigned char zero_byte = if_zero[index];

        out[index] = (unsigned char)((nonzero_byte & mask) | (zero_byte & (unsigned char)~mask));
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
