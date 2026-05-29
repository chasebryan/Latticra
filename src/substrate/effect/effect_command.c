#include "latticra/substrate/effect_command.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

/* Guarded command execution implementation.
 *
 * Current rules (v0.3.0edge+):
 * - Effects must be enabled via BUILD_PROFILE=effect-enabled at build time.
 * - Command must be in the built-in safe list OR in LATTICRA_EFFECT_ALLOWLIST
 *   (colon-separated, or path to a file with one command per line).
 * - Full evidence (stdout, stderr, timing, exit code) is always captured.
 */

static int command_in_list(const char *cmd, const char *list) {
    if (!list || !cmd) return 0;
    char *copy = strdup(list);
    if (!copy) return 0;

    char *token = strtok(copy, ":");
    while (token) {
        if (strcmp(cmd, token) == 0) {
            free(copy);
            return 1;
        }
        token = strtok(NULL, ":");
    }
    free(copy);
    return 0;
}

static int command_in_file(const char *cmd, const char *path) {
    if (!path || !cmd) return 0;
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0; // strip newline
        if (strcmp(cmd, line) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

static int is_command_allowed(const char *cmd) {
    /* Built-in safe list for development */
    const char *builtin[] = {"echo", "true", "false", "date", "uname", "whoami", "pwd", NULL};
    for (int i = 0; builtin[i]; i++) {
        if (strcmp(cmd, builtin[i]) == 0) return 1;
    }

    /* Check environment variable for additional allowlist */
    const char *env_list = getenv("LATTICRA_EFFECT_ALLOWLIST");
    if (env_list && command_in_list(cmd, env_list)) return 1;

    /* Check if env var points to a file */
    if (env_list && access(env_list, R_OK) == 0) {
        if (command_in_file(cmd, env_list)) return 1;
    }

    /* Also check a default file next to the binary if present */
    char default_file[512];
    if (readlink("/proc/self/exe", default_file, sizeof(default_file)-1) > 0 ||
        realpath(".", default_file)) {
        // crude: look for allowlist.txt next to cwd for demo convenience
        if (command_in_file(cmd, "effect-allowlist.txt")) return 1;
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
                 "Effects are disabled in current build profile (report-only mode). "
                 "Rebuild with BUILD_PROFILE=effect-enabled.");
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
                 "Command '%s' is not allowed by current policy/allowlist", request->command);
        return LATTICRA_STATUS_OK;
    }

    /* === Actual guarded execution === */
    int pipe_out[2], pipe_err[2];
    if (pipe(pipe_out) < 0 || pipe(pipe_err) < 0) {
        result->exit_code = 1;
        snprintf(result->stderr, sizeof(result->stderr), "pipe failed: %s", strerror(errno));
        return LATTICRA_STATUS_OK;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork();
    if (pid < 0) {
        result->exit_code = 1;
        snprintf(result->stderr, sizeof(result->stderr), "fork failed: %s", strerror(errno));
        return LATTICRA_STATUS_OK;
    }

    if (pid == 0) {
        close(pipe_out[0]); close(pipe_err[0]);
        dup2(pipe_out[1], STDOUT_FILENO);
        dup2(pipe_err[1], STDERR_FILENO);
        close(pipe_out[1]); close(pipe_err[1]);

        char *argv[64] = {0};
        argv[0] = (char*)request->command;
        for (size_t i = 0; i < request->arg_count && i < 62; i++) {
            argv[i+1] = (char*)request->args[i];
        }

        execvp(request->command, argv);
        _exit(127);
    }

    close(pipe_out[1]); close(pipe_err[1]);

    result->stdout_len = read(pipe_out[0], result->stdout, sizeof(result->stdout)-1);
    result->stderr_len = read(pipe_err[0], result->stderr, sizeof(result->stderr)-1);
    close(pipe_out[0]); close(pipe_err[0]);

    int status;
    waitpid(pid, &status, 0);

    clock_gettime(CLOCK_MONOTONIC, &end);
    result->duration_ms = ((end.tv_sec - start.tv_sec) * 1000) +
                          ((end.tv_nsec - start.tv_nsec) / 1000000);

    if (WIFEXITED(status)) result->exit_code = WEXITSTATUS(status);
    else result->exit_code = 128;

    result->stdout[result->stdout_len] = 0;
    result->stderr[result->stderr_len] = 0;

    return LATTICRA_STATUS_OK;
}
