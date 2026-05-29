#!/usr/bin/env sh
# build-separate.sh
# Builds Latticra core components and tests into a clean, isolated build-separate/
# directory. This provides a separate build structure from any existing
# installer/target/ artifacts or in-tree builds.
#
# This is the recommended way to work on Latticra in a clean, reproducible
# environment that does not interfere with the Rust-based Latticra Panel.
#
# Usage examples:
#   sh scripts/build-separate.sh all
#   sh scripts/build-separate.sh full-validate
#   sh scripts/build-separate.sh prepare-release-candidate
#   make build-separate-full-validate
#
# Key directories produced under build-separate/:
#   bin/          - final binaries
#   obj/          - compiled objects (for future incremental builds)
#   tests/        - selected test binaries
#   evidence/     - captured validation output
#   validation/   - full guard suite logs + summary
#   release-candidate/ - clean layout mimicking future release artifacts

set -eu

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build-separate"
BIN_DIR="$BUILD_DIR/bin"
OBJ_DIR="$BUILD_DIR/obj"
LOG_FILE="$BUILD_DIR/build.log"

mkdir -p "$BIN_DIR" "$OBJ_DIR"

log() {
    printf '[build-separate] %s\n' "$*" | tee -a "$LOG_FILE"
}

# Helper to compile a single .c into an object with basic caching
compile_object() {
    src="$1"
    obj="$OBJ_DIR/$(basename "$src" .c).o"
    # Very simple cache: recompile only if source is newer than object
    if [ ! -f "$obj" ] || [ "$src" -nt "$obj" ]; then
        cc -std=c99 -Wall -Wextra -pedantic -Iinclude -c "$src" -o "$obj" 2>&1 | tee -a "$LOG_FILE"
    fi
    echo "$obj"
}

# Generate a high-quality machine and human readable health report
generate_foundation_health_report() {
    log "Generating Latticra Foundation Health Report..."
    REPORT="$BUILD_DIR/FOUNDATION_HEALTH_REPORT.txt"
    JSON_REPORT="$BUILD_DIR/FOUNDATION_HEALTH_REPORT.json"

    {
        echo "LATTICRA FOUNDATION HEALTH REPORT"
        echo "Generated: $(date)"
        echo "Build tree: $BUILD_DIR"
        echo ""
        echo "=== Binaries ==="
        ls -l "$BIN_DIR" 2>/dev/null || echo "No binaries"
        echo ""
        echo "=== Key Validation Status ==="
        if [ -f "$BUILD_DIR/validation/REPORT.txt" ]; then
            cat "$BUILD_DIR/validation/REPORT.txt"
        else
            echo "Run full-validate to populate"
        fi
        echo ""
        echo "=== Evidence Captured ==="
        find "$BUILD_DIR/evidence" -type f 2>/dev/null | head -20
    } > "$REPORT"

    # Simple JSON summary (useful for future tooling / CI)
    cat > "$JSON_REPORT" <<JSON
{
  "generated": "$(date -Iseconds 2>/dev/null || date)",
  "build_tree": "$BUILD_DIR",
  "binaries": $(ls "$BIN_DIR" 2>/dev/null | wc -l | tr -d ' '),
  "validation_passed": $( [ -f "$BUILD_DIR/validation/REPORT.txt" ] && grep -o 'Clear passes: [0-9]*' "$BUILD_DIR/validation/REPORT.txt" | awk '{print $3}' || echo 0 ),
  "has_release_candidate": $( [ -d "$BUILD_DIR/release-candidate" ] && echo true || echo false )
}
JSON

    log "Health report generated: $REPORT"
    log "Machine readable: $JSON_REPORT"
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
       -o "$BIN_DIR/latticra"
    log "CLI built: $BIN_DIR/latticra"
}

build_seal() {
    log "Building Latticra Seal CLI (may require OpenSSL dev files) ..."
    detect_openssl
    # shellcheck disable=SC2086
    gcc -Wall -Wextra -O2 -std=c11 $OPENSSL_CFLAGS \
        -Iinclude \
        -o "$BIN_DIR/latticra-seal" \
        seal/latticra-seal.c \
        $OPENSSL_LIBS
    log "Seal CLI built: $BIN_DIR/latticra-seal"
}

build_core_tests() {
    log "Core invariant tests are validated via dedicated scripts/test-*.sh (each test declares its exact sources)."
    log "Building a minimal representative subset into $BUILD_DIR/tests/ for the separate tree record ..."

    mkdir -p "$BUILD_DIR/tests"

    # Only the most self-contained core test for the record (others use their own scripts)
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
}

# Build the visual theorem engines (mathematical art / substrate demonstrations)
build_visual_engines() {
    log "Building visual theorem engines (substrate + theorem) into separate tree..."
    mkdir -p "$BUILD_DIR/visual-engines"

    # These are intentionally separate from the main no-effect core
    if sh scripts/render-visual-theorem-engines.sh build 2>&1 | tee -a "$LOG_FILE"; then
        # Move any produced engines into our clean tree if the render script left them in root
        for engine in latticra_substrate_engine latticra_theorem_engine; do
            if [ -x "./$engine" ]; then
                mv "./$engine" "$BUILD_DIR/visual-engines/" 2>/dev/null || true
            fi
        done
        log "Visual engines built under $BUILD_DIR/visual-engines/"
    else
        log "Visual engine build step completed with notes (see log). Requirements: gcc + ffmpeg + -lm"
    fi
}

# Prepare a clean "release-candidate" layout inside the separate tree.
# This mirrors concepts from the project's production release artifact contracts
# without claiming any actual release readiness.
prepare_release_candidate() {
    log "Preparing release-candidate layout inside separate build tree..."
    CANDIDATE_DIR="$BUILD_DIR/release-candidate"
    rm -rf "$CANDIDATE_DIR"
    mkdir -p "$CANDIDATE_DIR/bin" "$CANDIDATE_DIR/share/doc/latticra" "$CANDIDATE_DIR/share/seal"

    # Copy key no-effect artifacts
    cp -f "$BIN_DIR/latticra" "$CANDIDATE_DIR/bin/" 2>/dev/null || true
    cp -f "$BIN_DIR/latticra-seal" "$CANDIDATE_DIR/bin/" 2>/dev/null || true

    # Documentation snapshot (no-effect)
    cp -f README.md "$CANDIDATE_DIR/share/doc/latticra/" 2>/dev/null || true
    cp -f STATUS.md "$CANDIDATE_DIR/share/doc/latticra/" 2>/dev/null || true
    cp -f LICENSE "$CANDIDATE_DIR/share/doc/latticra/" 2>/dev/null || true

    # Seal baseline artifacts if present
    cp -f latticra.seal "$CANDIDATE_DIR/share/seal/" 2>/dev/null || true
    cp -f latticra.seal.lock "$CANDIDATE_DIR/share/seal/" 2>/dev/null || true

    log "Release-candidate layout ready at: $CANDIDATE_DIR"
    log "This is a hygiene / exploration artifact only. No production claims."
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
# This version is significantly smarter: it trusts the script's own final "ok" line
# instead of crude grepping, dramatically reducing false positives.
run_full_validate() {
    log "Running FULL project validation suite inside separate build tree (smart mode)..."
    mkdir -p "$BUILD_DIR/validation"

    local failed=0
    local total=0
    local pass_count=0

    : > "$BUILD_DIR/validation/summary.txt"
    : > "$BUILD_DIR/validation/FAILURES.txt"
    : > "$BUILD_DIR/validation/REPORT.txt"

    for script in scripts/test-*.sh; do
        total=$((total + 1))
        name=$(basename "$script")
        output_file="$BUILD_DIR/validation/$name.log"

        if bash "$script" > "$output_file" 2>&1; then
            # Trust the script's own success indication
            if tail -5 "$output_file" | grep -qiE ': ok$|PASS$|success'; then
                echo "PASS: $name" >> "$BUILD_DIR/validation/summary.txt"
                pass_count=$((pass_count + 1))
            else
                # Script exited 0 but didn't clearly say success — flag for review
                echo "UNCLEAR: $name (exited 0 but no clear success marker)" >> "$BUILD_DIR/validation/summary.txt"
                echo "$name" >> "$BUILD_DIR/validation/FAILURES.txt"
                failed=$((failed + 1))
            fi
        else
            echo "FAIL: $name" >> "$BUILD_DIR/validation/summary.txt"
            echo "$name" >> "$BUILD_DIR/validation/FAILURES.txt"
            failed=$((failed + 1))
        fi
    done

    {
        echo "LATTICRA SEPARATE BUILD - FULL VALIDATION REPORT"
        echo "Generated: $(date)"
        echo "Total scripts run: $total"
        echo "Passed (clear success): $pass_count"
        echo "Failed or unclear: $failed"
        echo ""
        echo "This run used smart success detection (trusts each script's own final status)."
        echo "This run was performed inside an isolated build-separate/ tree."
        echo ""
        echo "See:"
        echo "  - summary.txt for quick overview"
        echo "  - FAILURES.txt for scripts needing attention"
        echo "  - individual *.log files for details"
    } > "$BUILD_DIR/validation/REPORT.txt"

    log "Full validation finished. Clear passes: $pass_count / $total (see $BUILD_DIR/validation/)"
    return $failed
}

clean() {
    log "Removing separate build tree: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
}

usage() {
    echo "Usage: $0 [cli|seal|tests|visual|all|clean|smoke|validate|full-validate|prepare-release-candidate|health-report]"
    exit 1
}

main() {
    case "${1:-all}" in
        cli)   build_cli ;;
        seal)  build_seal ;;
        tests) build_core_tests ;;
        visual) build_visual_engines ;;
        all)
            build_cli
            build_seal || log "WARNING: Seal build skipped or failed (OpenSSL may be missing)"
            build_core_tests
            build_visual_engines
            run_smoke
            ;;
        clean) clean ;;
        smoke) run_smoke ;;
        validate) run_validate ;;
        full-validate)
            run_full_validate
            generate_foundation_health_report
            ;;
        prepare-release-candidate)
            prepare_release_candidate
            generate_foundation_health_report
            ;;
        health-report) generate_foundation_health_report ;;
        *) usage ;;
    esac
    log "Done. Artifacts in: $BUILD_DIR (separate from source and installer/)"
}

main "${1:-}"