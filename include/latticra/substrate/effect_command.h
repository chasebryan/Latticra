#ifndef LATTICRA_SUBSTRATE_EFFECT_COMMAND_H
#define LATTICRA_SUBSTRATE_EFFECT_COMMAND_H

#include "latticra/substrate/effect.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_EFFECT_COMMAND_MAX 256
#define LATTICRA_EFFECT_ARGS_MAX 32
#define LATTICRA_EFFECT_ARG_LEN 128
#define LATTICRA_EFFECT_ENV_MAX 64
#define LATTICRA_EFFECT_ENV_LEN 256

typedef struct {
    char command[LATTICRA_EFFECT_COMMAND_MAX];
    char args[LATTICRA_EFFECT_ARGS_MAX][LATTICRA_EFFECT_ARG_LEN];
    size_t arg_count;
    char env[LATTICRA_EFFECT_ENV_MAX][LATTICRA_EFFECT_ENV_LEN];
    size_t env_count;
    char cwd[512];
    int capture_stdout;
    int capture_stderr;
    size_t stdout_limit;
    size_t stderr_limit;
} latticra_effect_command_request_t;

typedef struct {
    int exit_code;
    int timed_out;
    char stdout[4096];
    size_t stdout_len;
    char stderr[4096];
    size_t stderr_len;
    long duration_ms;
} latticra_effect_command_result_t;

/**
 * Execute a command under full contract and boundary control.
 * This is the first real effect we are making effectful.
 */
latticra_status_t latticra_substrate_execute_command(
    const latticra_effect_context_t *ctx,
    const latticra_effect_command_request_t *request,
    latticra_effect_command_result_t *result
);

#ifdef __cplusplus
}
#endif

#endif /* LATTICRA_SUBSTRATE_EFFECT_COMMAND_H */
