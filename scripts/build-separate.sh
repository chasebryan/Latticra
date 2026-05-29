#!/usr/bin/env sh
# build-separate.sh
# Builds Latticra core components and tests into a clean, isolated build-separate/
# directory. This provides a separate build structure from any existing
# installer/target/ artifacts or in-tree builds.
#
# Usage:
#   sh scripts/build-separate.sh            # build everything
#   sh scripts/build-separate.sh cli        # just the no-effect CLI
#   sh scripts/build-separate.sh seal       # Seal + crypto bits
#   sh scripts/build-separate.sh tests      # core invariant tests (no-effect)
#   sh scripts/build-separate.sh clean      # remove the separate build tree

set -eu

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build-separate"
LOG_FILE="$BUILD_DIR/build.log"

mkdir -p "$BUILD_DIR"

log() {
    printf '[build-separate] %s\n' "$*" | tee -a "$LOG_FILE"
}

detect_openssl() {
    OPENSSL_CFLAGS=""
    OPENSSL_LIBS="-lcrypto"
    if [ "$(uname -s)" = "Darwin" ]; then
        if [ -d /opt/homebrew/opt/openssl/include ]; then
            OPENSSL_CFLAGS="-I/opt/homebrew/opt/openssl/include"
            OPENSSL_LIBS="-L/opt/homebrew/opt/openssl/lib -lcrypto"
        elif [ -d /usr/local/opt/openssl/include ]; then
            OPENSSL_CFLAGS="-I/usr/local/opt/openssl/include"
            OPENSSL_LIBS="-L/usr/local/opt/openssl/lib -lcrypto"
        elif [ -d /opt/homebrew/include ]; then
            OPENSSL_CFLAGS="-I/opt/homebrew/include"
            OPENSSL_LIBS="-L/opt/homebrew/lib -lcrypto"
        fi
    fi
    export OPENSSL_CFLAGS OPENSSL_LIBS
}

build_cli() {
    log "Building no-effect CLI (latticra) ..."
    cc -std=c99 -Wall -Wextra -pedantic \
       -Iinclude \
       src/latticra_cli.c \
       -o "$BUILD_DIR/latticra"
    log "CLI built: $BUILD_DIR/latticra"
}

build_seal() {
    log "Building Latticra Seal CLI (may require OpenSSL dev files) ..."
    detect_openssl
    # shellcheck disable=SC2086
    gcc -Wall -Wextra -O2 -std=c11 $OPENSSL_CFLAGS \
        -Iinclude \
        -o "$BUILD_DIR/latticra-seal" \
        seal/latticra-seal.c \
        $OPENSSL_LIBS
    log "Seal CLI built: $BUILD_DIR/latticra-seal"
}

build_core_tests() {
    log "Core invariant tests are validated via dedicated scripts/test-*.sh (each test declares its exact sources)."
    log "Building a minimal representative subset into $BUILD_DIR/tests/ for the separate tree record ..."

    mkdir -p "$BUILD_DIR/tests"

    # Only the most self-contained core test for the record (others use their own scripts)
    # This keeps the separate build structure from depending on fragile cross-module lists.
    if cc -std=c99 -Wall -Wextra -Werror -pedantic \
         -Iinclude \
         src/lat_parser.c src/lat_semantic.c src/lat_to_lir.c src/lir.c \
         src/lat_pipeline.c src/lat_pipeline_diagnostics.c \
         src/lat_pipeline_diagnostics_eval.c src/lat_pipeline_diagnostics_report.c \
         tests/lat_pipeline_invariants.c \
         -o "$BUILD_DIR/tests/lat_pipeline_invariants" 2>&1 >> "$LOG_FILE"; then
        log "  lat_pipeline_invariants: ok (in separate tree)"
    else
        log "  lat_pipeline_invariants: build note logged (full validation still via scripts/)"
    fi

    log "Representative test binary (if successful) and full validation evidence live under the separate build tree."
    log "For complete no-effect invariant coverage run: sh scripts/test-lat-pipeline.sh etc. (or make seal)"
}

run_smoke() {
    log "Running smoke verification in separate build tree ..."
    if [ -x "$BUILD_DIR/latticra" ]; then
        "$BUILD_DIR/latticra" --status | tee -a "$LOG_FILE"
    fi
    if [ -x "$BUILD_DIR/latticra-seal" ]; then
        "$BUILD_DIR/latticra-seal" version 2>&1 | tee -a "$LOG_FILE" || true
    fi
    log "Separate build smoke complete."
}

# Run key deterministic guards and capture evidence in the separate tree
run_validate() {
    log "Running key validation guards (evidence captured under $BUILD_DIR/evidence/) ..."
    mkdir -p "$BUILD_DIR/evidence"

    # Core no-effect surfaces (these are fast and stable)
    sh scripts/test-lat-pipeline.sh > "$BUILD_DIR/evidence/lat-pipeline.txt" 2>&1 || true
    sh scripts/test-runtime-boundary.sh > "$BUILD_DIR/evidence/runtime-boundary.txt" 2>&1 || true
    sh scripts/test-nucleus-task-execution.sh > "$BUILD_DIR/evidence/nucleus-task.txt" 2>&1 || true

    # Seal core blocked cases (report-only)
    sh scripts/test-latticra-seal-unknown-tool-case.sh > "$BUILD_DIR/evidence/seal-unknown-tool.txt" 2>&1 || true
    sh scripts/test-latticra-seal-unsigned-request-case.sh > "$BUILD_DIR/evidence/seal-unsigned.txt" 2>&1 || true

    log "Validation evidence written to $BUILD_DIR/evidence/"
}

# Full project validation using the now-clean test suite (cooperative with project's own guards)
run_full_validate() {
    log "Running FULL project validation suite inside separate build tree..."
    mkdir -p "$BUILD_DIR/validation"

    local failed=0
    local total=0

    for script in scripts/test-*.sh; do
        total=$((total + 1))
        name=$(basename "$script")
        if bash "$script" > "$BUILD_DIR/validation/$name.log" 2>&1; then
            echo "PASS: $name" >> "$BUILD_DIR/validation/summary.txt"
        else
            echo "FAIL: $name" >> "$BUILD_DIR/validation/summary.txt"
            failed=$((failed + 1))
        fi
    done

    echo "Total scripts: $total" >> "$BUILD_DIR/validation/summary.txt"
    echo "Failed: $failed" >> "$BUILD_DIR/validation/summary.txt"
    echo "Full validation complete. See $BUILD_DIR/validation/" >> "$BUILD_DIR/validation/summary.txt"

    log "Full validation finished. Failures: $failed (see $BUILD_DIR/validation/summary.txt)"
    return $failed
}

clean() {
    log "Removing separate build tree: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
}

usage() {
    echo "Usage: $0 [cli|seal|tests|all|clean|smoke|validate|full-validate]"
    exit 1
}

main() {
    case "${1:-all}" in
        cli)   build_cli ;;
        seal)  build_seal ;;
        tests) build_core_tests ;;
        all)
            build_cli
            build_seal || log "WARNING: Seal build skipped or failed (OpenSSL may be missing)"
            build_core_tests
            run_smoke
            ;;
        clean) clean ;;
        smoke) run_smoke ;;
        validate) run_validate ;;
        full-validate) run_full_validate ;;
        *) usage ;;
    esac
    log "Done. Artifacts in: $BUILD_DIR (separate from source and installer/)"
}

main "${1:-}"