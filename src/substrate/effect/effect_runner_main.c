#include "latticra/substrate/effect_command.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: latticra-effect-runner <command> [args...]\n");
        printf("  (Very limited allowlist in this early build)\n");
        return 1;
    }

    latticra_effect_context_t ctx = {0};
    ctx.require_evidence = 1;

    latticra_effect_command_request_t req = {0};
    strncpy(req.command, argv[1], sizeof(req.command)-1);

    for (int i = 2; i < argc && req.arg_count < LATTICRA_EFFECT_ARGS_MAX; i++) {
        strncpy(req.args[req.arg_count], argv[i], LATTICRA_EFFECT_ARG_LEN-1);
        req.arg_count++;
    }

    latticra_effect_command_result_t res = {0};

    latticra_status_t st = latticra_substrate_execute_command(&ctx, &req, &res);

    printf("exit_code=%d\n", res.exit_code);
    printf("duration_ms=%ld\n", res.duration_ms);
    printf("stdout_len=%zu\n", res.stdout_len);
    printf("stderr_len=%zu\n", res.stderr_len);
    if (res.stdout_len > 0) printf("--- stdout ---\n%s\n", res.stdout);
    if (res.stderr_len > 0) printf("--- stderr ---\n%s\n", res.stderr);

    return (st == LATTICRA_STATUS_OK && res.exit_code == 0) ? 0 : 1;
}
