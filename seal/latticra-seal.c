#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define MANIFEST_PATH "latticra.seal"
#define REPORT_DIR "reports"
#define REPORT_PATH "reports/latticra-seal-cli-report.txt"

typedef struct {
    int failures;
    int warnings;
    FILE *report;
} SealRun;

static bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }

    long size = ftell(f);
    if (size < 0) {
        fclose(f);
        return NULL;
    }

    rewind(f);

    char *buf = calloc((size_t)size + 1, 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }

    size_t read_count = fread(buf, 1, (size_t)size, f);
    fclose(f);

    if (read_count != (size_t)size) {
        free(buf);
        return NULL;
    }

    buf[size] = '\0';
    return buf;
}

static void emit(SealRun *run, const char *line) {
    puts(line);

    if (run->report) {
        fputs(line, run->report);
        fputc('\n', run->report);
    }
}

static void section(SealRun *run, const char *name) {
    char line[256];
    snprintf(line, sizeof(line), "\n== %s ==", name);
    emit(run, line);
}

static void pass(SealRun *run, const char *msg) {
    char line[512];
    snprintf(line, sizeof(line), "PASS: %s", msg);
    emit(run, line);
}

static void warn(SealRun *run, const char *msg) {
    char line[512];
    run->warnings++;
    snprintf(line, sizeof(line), "WARN: %s", msg);
    emit(run, line);
}

static void fail(SealRun *run, const char *msg) {
    char line[512];
    run->failures++;
    snprintf(line, sizeof(line), "FAIL: %s", msg);
    emit(run, line);
}

static void require_manifest_field(
    SealRun *run,
    const char *manifest,
    const char *needle,
    const char *label
) {
    if (strstr(manifest, needle)) {
        pass(run, label);
    } else {
        fail(run, label);
    }
}

static void check_manifest_shape(SealRun *run, const char *manifest) {
    section(run, "Manifest shape");

    require_manifest_field(
        run,
        manifest,
        "schema = \"latticra.seal/v0.1\"",
        "schema is latticra.seal/v0.1"
    );

    require_manifest_field(
        run,
        manifest,
        "format = \"toml\"",
        "format is TOML-compatible"
    );

    require_manifest_field(
        run,
        manifest,
        "kind = \"local-integrity-manifest\"",
        "kind is local-integrity-manifest"
    );

    require_manifest_field(
        run,
        manifest,
        "algorithm = \"sha256\"",
        "hash algorithm is sha256"
    );

    require_manifest_field(
        run,
        manifest,
        "trust_boundary = \"project-root\"",
        "trust boundary is project-root"
    );
}

static void check_policy_shape(SealRun *run, const char *manifest) {
    section(run, "Policy shape");

    require_manifest_field(
        run,
        manifest,
        "require_readme = true",
        "policy requires README"
    );

    require_manifest_field(
        run,
        manifest,
        "require_license = true",
        "policy requires LICENSE"
    );

    require_manifest_field(
        run,
        manifest,
        "deny_private_keys = true",
        "policy denies private keys"
    );

    require_manifest_field(
        run,
        manifest,
        "deny_env_files = true",
        "policy denies .env files"
    );

    require_manifest_field(
        run,
        manifest,
        "deny_obvious_tokens = true",
        "policy denies obvious token markers"
    );
}

static void check_required_files(SealRun *run) {
    section(run, "Required project files");

    if (file_exists("README.md")) {
        pass(run, "README.md exists");
    } else {
        fail(run, "README.md is missing");
    }

    if (file_exists("LICENSE")) {
        pass(run, "LICENSE exists");
    } else {
        fail(run, "LICENSE is missing");
    }
}

static void write_header(SealRun *run) {
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);
    char stamp[64];

    if (utc) {
        strftime(stamp, sizeof(stamp), "%Y-%m-%dT%H:%M:%SZ", utc);
    } else {
        snprintf(stamp, sizeof(stamp), "unknown-time");
    }

    emit(run, "Latticra Seal CLI Report");
    emit(run, "Version: v0.1");
    emit(run, "Mode: local-integrity");
    emit(run, stamp);
}

static int finish(SealRun *run) {
    section(run, "Result");

    if (run->failures == 0) {
        emit(run, "STATUS: PASS");
    } else {
        emit(run, "STATUS: FAIL");
    }

    char summary[128];
    snprintf(
        summary,
        sizeof(summary),
        "Failures: %d | Warnings: %d",
        run->failures,
        run->warnings
    );

    emit(run, summary);
    emit(run, "Report written to: " REPORT_PATH);

    return run->failures == 0 ? 0 : 1;
}

int main(void) {
    mkdir(REPORT_DIR, 0755);

    SealRun run;
    run.failures = 0;
    run.warnings = 0;
    run.report = fopen(REPORT_PATH, "w");

    if (!run.report) {
        fprintf(stderr, "Could not open report: %s\n", REPORT_PATH);
        return 2;
    }

    write_header(&run);

    section(&run, "Manifest presence");

    if (!file_exists(MANIFEST_PATH)) {
        fail(&run, "latticra.seal is missing");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    pass(&run, "latticra.seal exists");

    char *manifest = read_file(MANIFEST_PATH);
    if (!manifest) {
        fail(&run, "could not read latticra.seal");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    check_manifest_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_required_files(&run);

    free(manifest);

    int code = finish(&run);
    fclose(run.report);
    return code;
}
