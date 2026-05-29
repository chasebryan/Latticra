#include "latticra/substrate/effect_command.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

/* Very early, conservative implementation of guarded command execution.
 *
 * Rules for this initial version:
 * - Only allowed if effects are explicitly enabled in the build profile.
 * - Command must be in a tiny hardcoded allowlist (for safety during development).
 * - Full evidence is captured.
 * - This will later be driven by real contracts from the Nucleus layer.
 */

static int is_command_allowed(const char *cmd) {
    /* Extremely strict allowlist for the very first effectful capability.
     * This will be replaced by contract-driven allowlists.
     */
    const char *allowed[] = {
        "echo",
        "true",
        "false",
        "date",
        "uname",
        NULL
    };

    for (int i = 0; allowed[i]; i++) {
        if (strcmp(cmd, allowed[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

latticra_status_t latticra_substrate_execute_command(
    const latticra_effect_context_t *ctx,
    const latticra_effect_command_request_t *request,
    latticra_effect_command_result_t *result
) {
    if (result == NULL) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(result, 0, sizeof(*result));

    if (!latticra_substrate_effects_enabled()) {
        result->exit_code = 126;
        snprintf(result->stderr, sizeof(result->stderr),
                 "Effects are disabled in current build profile (report-only mode)");
        return LATTICRA_STATUS_OK;
    }

    if (ctx == NULL || request == NULL || request->command[0] == '\0') {
        result->exit_code = 127;
        snprintf(result->stderr, sizeof(result->stderr), "Invalid command request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (!is_command_allowed(request->command)) {
        result->exit_code = 126;
        snprintf(result->stderr, sizeof(result->stderr),
                 "Command '%s' is not in the current development allowlist", request->command);
        return LATTICRA_STATUS_OK;
    }

    /* === Real execution path (still very locked down) === */
    int pipe_stdout[2];
    int pipe_stderr[2];
    if (pipe(pipe_stdout) < 0 || pipe(pipe_stderr) < 0) {
        result->exit_code = 1;
        snprintf(result->stderr, sizeof(result->stderr), "Failed to create pipes: %s", strerror(errno));
        return LATTICRA_STATUS_OK;
    }

    pid_t pid = fork();
    if (pid < 0) {
        result->exit_code = 1;
        snprintf(result->stderr, sizeof(result->stderr), "fork failed: %s", strerror(errno));
        return LATTICRA_STATUS_OK;
    }

    if (pid == 0) {
        /* Child process */
        close(pipe_stdout[0]);
        close(pipe_stderr[0]);
        dup2(pipe_stdout[1], STDOUT_FILENO);
        dup2(pipe_stderr[1], STDERR_FILENO);
        close(pipe_stdout[1]);
        close(pipe_stderr[1]);

        char *argv[LATTICRA_EFFECT_ARGS_MAX + 2];
        argv[0] = (char *)request->command;
        for (size_t i = 0; i < request->arg_count && i < LATTICRA_EFFECT_ARGS_MAX; i++) {
            argv[i + 1] = (char *)request->args[i];
        }
        argv[request->arg_count + 1] = NULL;

        execvp(request->command, argv);
        _exit(127); /* exec failed */
    }

    /* Parent */
    close(pipe_stdout[1]);
    close(pipe_stderr[1]);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    /* Simple read (bounded) */
    result->stdout_len = read(pipe_stdout[0], result->stdout, sizeof(result->stdout) - 1);
    result->stderr_len = read(pipe_stderr[0], result->stderr, sizeof(result->stderr) - 1);

    close(pipe_stdout[0]);
    close(pipe_stderr[0]);

    int status;
    waitpid(pid, &status, 0);

    clock_gettime(CLOCK_MONOTONIC, &end);
    result->duration_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

    if (WIFEXITED(status)) {
        result->exit_code = WEXITSTATUS(status);
    } else {
        result->exit_code = 128;
    }

    result->stdout[result->stdout_len] = '\0';
    result->stderr[result->stderr_len] = '\0';

    /* Evidence is implicitly captured in the result struct for now.
     * Later this will go through a proper evidence recorder.
     */

    return LATTICRA_STATUS_OK;
}
