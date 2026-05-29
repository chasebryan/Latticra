#include "latticra/q_seal_ml_kem_secret_ops.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int all_bytes_equal(const unsigned char *buffer, size_t buffer_len, unsigned char value) {
    size_t index;

    for (index = 0u; index < buffer_len; index++) {
        if (buffer[index] != value) {
            return 0;
        }
    }

    return 1;
}

static int secure_zero_wipes_public_test_buffer(void) {
    unsigned char buffer[32];

    memset(buffer, 0xa5, sizeof(buffer));
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secure_zero(buffer, sizeof(buffer)) == LATTICRA_Q_SEAL_STATUS_OK,
        "secure zero status");
    EXPECT_TRUE(all_bytes_equal(buffer, sizeof(buffer), 0u) == 1, "secure zero cleared");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secure_zero(0, 0u) == LATTICRA_Q_SEAL_STATUS_OK,
        "secure zero null empty");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secure_zero(0, sizeof(buffer)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "secure zero null nonempty");
    return 0;
}

static int constant_time_equal_reports_equality_without_early_secret_exit(void) {
    unsigned char left[16];
    unsigned char right[16];
    unsigned equal = 99u;
    size_t index;

    for (index = 0u; index < sizeof(left); index++) {
        left[index] = (unsigned char)(index + 1u);
        right[index] = left[index];
    }

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_equal(left, right, sizeof(left), &equal) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "equal status");
    EXPECT_TRUE(equal == 1u, "equal true");

    right[sizeof(right) - 1u] ^= 0x80u;
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_equal(left, right, sizeof(left), &equal) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "not equal status");
    EXPECT_TRUE(equal == 0u, "equal false");

    equal = 99u;
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_equal(0, 0, 0u, &equal) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "equal null empty status");
    EXPECT_TRUE(equal == 1u, "equal null empty true");

    equal = 99u;
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_equal(0, right, sizeof(right), &equal) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "equal null nonempty status");
    EXPECT_TRUE(equal == 0u, "equal null clears result");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_equal(left, right, sizeof(left), 0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "equal null output");
    return 0;
}

static int constant_time_select_chooses_without_secret_branching(void) {
    unsigned char if_nonzero[16];
    unsigned char if_zero[16];
    unsigned char out[16];
    unsigned char overlap[17];
    size_t index;

    for (index = 0u; index < sizeof(out); index++) {
        if_nonzero[index] = (unsigned char)(0xa0u + index);
        if_zero[index] = (unsigned char)(0x10u + index);
        out[index] = 0u;
        overlap[index] = (unsigned char)(0x70u + index);
    }
    overlap[sizeof(overlap) - 1u] = 0xf0u;

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(
            out,
            if_nonzero,
            if_zero,
            sizeof(out),
            0u) == LATTICRA_Q_SEAL_STATUS_OK,
        "select zero status");
    EXPECT_TRUE(memcmp(out, if_zero, sizeof(out)) == 0, "select zero");

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(
            out,
            if_nonzero,
            if_zero,
            sizeof(out),
            1u) == LATTICRA_Q_SEAL_STATUS_OK,
        "select one status");
    EXPECT_TRUE(memcmp(out, if_nonzero, sizeof(out)) == 0, "select one");

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(
            out,
            if_nonzero,
            if_zero,
            sizeof(out),
            7u) == LATTICRA_Q_SEAL_STATUS_OK,
        "select nonzero status");
    EXPECT_TRUE(memcmp(out, if_nonzero, sizeof(out)) == 0, "select nonzero");

    memcpy(out, if_nonzero, sizeof(out));
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(
            out,
            out,
            if_zero,
            sizeof(out),
            0u) == LATTICRA_Q_SEAL_STATUS_OK,
        "select alias status");
    EXPECT_TRUE(memcmp(out, if_zero, sizeof(out)) == 0, "select alias");

    memcpy(out, if_zero, sizeof(out));
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(
            out,
            if_nonzero,
            out,
            sizeof(out),
            1u) == LATTICRA_Q_SEAL_STATUS_OK,
        "select zero alias status");
    EXPECT_TRUE(memcmp(out, if_nonzero, sizeof(out)) == 0, "select zero alias");

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(
            overlap + 1u,
            overlap,
            if_zero,
            sizeof(out),
            1u) == LATTICRA_Q_SEAL_STATUS_INVALID_ARGUMENT,
        "select rejects partial nonzero overlap");
    for (index = 0u; index < sizeof(overlap); index++) {
        unsigned char expected = (unsigned char)(index == sizeof(overlap) - 1u
            ? 0xf0u
            : 0x70u + index);

        EXPECT_TRUE(overlap[index] == expected,
            "select partial nonzero overlap leaves output untouched");
    }

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(
            overlap,
            if_nonzero,
            overlap + 1u,
            sizeof(out),
            0u) == LATTICRA_Q_SEAL_STATUS_INVALID_ARGUMENT,
        "select rejects partial zero overlap");

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(0, 0, 0, 0u, 1u) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "select empty null");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_select(0, if_nonzero, if_zero, sizeof(out), 1u) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "select null output");
    return 0;
}

int main(void) {
    if (secure_zero_wipes_public_test_buffer() != 0) {
        return 1;
    }
    if (constant_time_equal_reports_equality_without_early_secret_exit() != 0) {
        return 1;
    }
    if (constant_time_select_chooses_without_secret_branching() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem secret ops invariants: ok\n");
    return 0;
}
