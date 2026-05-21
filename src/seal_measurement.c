#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include "latticra/seal_measurement.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
#include <io.h>
#include <sys/stat.h>
#define file_no _fileno
#define fstat_fn _fstat
#define stat_t struct _stat
#define is_regular_file(mode) (((mode) & _S_IFREG) != 0)
#else
#include <sys/stat.h>
#include <unistd.h>
#define file_no fileno
#define fstat_fn fstat
#define stat_t struct stat
#define is_regular_file(mode) S_ISREG(mode)
#endif

typedef struct {
    uint32_t state[8];
    uint64_t bit_len;
    unsigned char data[64];
    size_t data_len;
} sha256_ctx_t;

static const uint32_t sha256_k[64] = {
    0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u,
    0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
    0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u,
    0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
    0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu,
    0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
    0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u,
    0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
    0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u,
    0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
    0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u,
    0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
    0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u,
    0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
    0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u,
    0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u
};

static uint32_t rotr32(uint32_t value, unsigned shift) {
    return (value >> shift) | (value << (32u - shift));
}

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

static void hex_lower(const unsigned char *input, size_t input_len, char *out, size_t out_len) {
    static const char hex[] = "0123456789abcdef";
    size_t i;

    if (out_len == 0u) {
        return;
    }
    if (out_len < (input_len * 2u + 1u)) {
        out[0] = '\0';
        return;
    }

    for (i = 0u; i < input_len; ++i) {
        out[i * 2u] = hex[(input[i] >> 4u) & 0x0fu];
        out[i * 2u + 1u] = hex[input[i] & 0x0fu];
    }
    out[input_len * 2u] = '\0';
}

static void sha256_transform(sha256_ctx_t *ctx, const unsigned char block[64]) {
    uint32_t m[64];
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint32_t t1;
    uint32_t t2;
    size_t i;

    for (i = 0u; i < 16u; ++i) {
        m[i] = ((uint32_t)block[i * 4u] << 24u) |
               ((uint32_t)block[i * 4u + 1u] << 16u) |
               ((uint32_t)block[i * 4u + 2u] << 8u) |
               ((uint32_t)block[i * 4u + 3u]);
    }

    for (i = 16u; i < 64u; ++i) {
        uint32_t s0 = rotr32(m[i - 15u], 7u) ^ rotr32(m[i - 15u], 18u) ^ (m[i - 15u] >> 3u);
        uint32_t s1 = rotr32(m[i - 2u], 17u) ^ rotr32(m[i - 2u], 19u) ^ (m[i - 2u] >> 10u);
        m[i] = m[i - 16u] + s0 + m[i - 7u] + s1;
    }

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0u; i < 64u; ++i) {
        uint32_t s1 = rotr32(e, 6u) ^ rotr32(e, 11u) ^ rotr32(e, 25u);
        uint32_t ch = (e & f) ^ ((~e) & g);
        uint32_t s0 = rotr32(a, 2u) ^ rotr32(a, 13u) ^ rotr32(a, 22u);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        t1 = h + s1 + ch + sha256_k[i] + m[i];
        t2 = s0 + maj;
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

static void sha256_init(sha256_ctx_t *ctx) {
    memset(ctx, 0, sizeof(*ctx));
    ctx->state[0] = 0x6a09e667u;
    ctx->state[1] = 0xbb67ae85u;
    ctx->state[2] = 0x3c6ef372u;
    ctx->state[3] = 0xa54ff53au;
    ctx->state[4] = 0x510e527fu;
    ctx->state[5] = 0x9b05688cu;
    ctx->state[6] = 0x1f83d9abu;
    ctx->state[7] = 0x5be0cd19u;
}

static void sha256_update(sha256_ctx_t *ctx, const unsigned char *data, size_t len) {
    size_t i;

    for (i = 0u; i < len; ++i) {
        ctx->data[ctx->data_len] = data[i];
        ctx->data_len++;
        if (ctx->data_len == 64u) {
            sha256_transform(ctx, ctx->data);
            ctx->bit_len += 512u;
            ctx->data_len = 0u;
        }
    }
}

static void sha256_final(sha256_ctx_t *ctx, unsigned char hash[32]) {
    size_t i = ctx->data_len;
    size_t j;

    ctx->data[i++] = 0x80u;

    if (i > 56u) {
        while (i < 64u) {
            ctx->data[i++] = 0u;
        }
        sha256_transform(ctx, ctx->data);
        memset(ctx->data, 0, 56u);
    } else {
        while (i < 56u) {
            ctx->data[i++] = 0u;
        }
    }

    ctx->bit_len += (uint64_t)ctx->data_len * 8u;
    ctx->data[63] = (unsigned char)(ctx->bit_len);
    ctx->data[62] = (unsigned char)(ctx->bit_len >> 8u);
    ctx->data[61] = (unsigned char)(ctx->bit_len >> 16u);
    ctx->data[60] = (unsigned char)(ctx->bit_len >> 24u);
    ctx->data[59] = (unsigned char)(ctx->bit_len >> 32u);
    ctx->data[58] = (unsigned char)(ctx->bit_len >> 40u);
    ctx->data[57] = (unsigned char)(ctx->bit_len >> 48u);
    ctx->data[56] = (unsigned char)(ctx->bit_len >> 56u);
    sha256_transform(ctx, ctx->data);

    for (j = 0u; j < 4u; ++j) {
        hash[j] = (unsigned char)((ctx->state[0] >> (24u - j * 8u)) & 0x000000ffu);
        hash[j + 4u] = (unsigned char)((ctx->state[1] >> (24u - j * 8u)) & 0x000000ffu);
        hash[j + 8u] = (unsigned char)((ctx->state[2] >> (24u - j * 8u)) & 0x000000ffu);
        hash[j + 12u] = (unsigned char)((ctx->state[3] >> (24u - j * 8u)) & 0x000000ffu);
        hash[j + 16u] = (unsigned char)((ctx->state[4] >> (24u - j * 8u)) & 0x000000ffu);
        hash[j + 20u] = (unsigned char)((ctx->state[5] >> (24u - j * 8u)) & 0x000000ffu);
        hash[j + 24u] = (unsigned char)((ctx->state[6] >> (24u - j * 8u)) & 0x000000ffu);
        hash[j + 28u] = (unsigned char)((ctx->state[7] >> (24u - j * 8u)) & 0x000000ffu);
    }
}

const char *latticra_seal_measurement_error_label(latticra_seal_measurement_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_MEASUREMENT_OK:
        return "ok";
    case LATTICRA_SEAL_MEASUREMENT_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_MEASUREMENT_NOT_REGULAR:
        return "not-regular";
    case LATTICRA_SEAL_MEASUREMENT_OPEN_FAILED:
        return "open-failed";
    case LATTICRA_SEAL_MEASUREMENT_READ_FAILED:
        return "read-failed";
    default:
        return "unknown";
    }
}

static void measurement_init(latticra_seal_measurement_t *measurement, const char *path) {
    memset(measurement, 0, sizeof(*measurement));
    copy_literal(measurement->measurement_profile, sizeof(measurement->measurement_profile), "latticra-seal-measurement/0.1");
    copy_literal(measurement->algorithm, sizeof(measurement->algorithm), "SHA-256");
    copy_literal(measurement->artifact_label, sizeof(measurement->artifact_label), path != NULL ? path : "");
    copy_literal(measurement->status, sizeof(measurement->status), "not-measured");
    measurement->error = LATTICRA_SEAL_MEASUREMENT_INVALID_INPUT;
}

latticra_status_t latticra_seal_measure_file(
    const char *path,
    latticra_seal_measurement_t *out) {
    stat_t info;
    FILE *file;
    sha256_ctx_t ctx;
    unsigned char buffer[4096];
    unsigned char digest[32];
    size_t read_count;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    measurement_init(out, path);

    if (path == NULL || path[0] == '\0') {
        copy_literal(out->status, sizeof(out->status), "invalid-input");
        return LATTICRA_STATUS_OK;
    }

    file = fopen(path, "rb");
    if (file == NULL) {
        out->error = LATTICRA_SEAL_MEASUREMENT_OPEN_FAILED;
        copy_literal(out->status, sizeof(out->status), "open-failed");
        return LATTICRA_STATUS_OK;
    }

    if (fstat_fn(file_no(file), &info) != 0 || !is_regular_file(info.st_mode)) {
        (void)fclose(file);
        out->error = LATTICRA_SEAL_MEASUREMENT_NOT_REGULAR;
        copy_literal(out->status, sizeof(out->status), "not-regular");
        return LATTICRA_STATUS_OK;
    }

    sha256_init(&ctx);
    out->read_performed = 1u;

    while ((read_count = fread(buffer, 1u, sizeof(buffer), file)) > 0u) {
        sha256_update(&ctx, buffer, read_count);
        out->artifact_size_bytes += (unsigned long)read_count;
    }

    if (ferror(file) != 0) {
        (void)fclose(file);
        out->error = LATTICRA_SEAL_MEASUREMENT_READ_FAILED;
        copy_literal(out->status, sizeof(out->status), "read-failed");
        return LATTICRA_STATUS_OK;
    }

    (void)fclose(file);
    sha256_final(&ctx, digest);
    hex_lower(digest, sizeof(digest), out->digest_hex, sizeof(out->digest_hex));
    out->error = LATTICRA_SEAL_MEASUREMENT_OK;
    copy_literal(out->status, sizeof(out->status), "measured");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_measurement_is_read_only(const latticra_seal_measurement_t *measurement) {
    if (measurement == NULL) {
        return 0;
    }

    return measurement->write_performed == 0u &&
           measurement->network_performed == 0u &&
           measurement->runtime_granted == 0u;
}

latticra_status_t latticra_seal_measurement_report(
    const latticra_seal_measurement_t *measurement,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (measurement == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL MEASUREMENT\n"
        "measurement_profile=%s\n"
        "algorithm=%s\n"
        "artifact_label=%s\n"
        "artifact_size_bytes=%lu\n"
        "digest_hex=%s\n"
        "read_performed=%u\n"
        "write_performed=%u\n"
        "network_performed=%u\n"
        "runtime_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        measurement->measurement_profile,
        measurement->algorithm,
        measurement->artifact_label,
        measurement->artifact_size_bytes,
        measurement->digest_hex,
        measurement->read_performed,
        measurement->write_performed,
        measurement->network_performed,
        measurement->runtime_granted,
        latticra_seal_measurement_error_label(measurement->error),
        measurement->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
