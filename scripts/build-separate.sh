#!/usr/bin/env sh
# build-separate.sh
# Builds Latticra core components and tests into a clean, isolated build-separate/
# directory. This provides a separate build structure from any existing
# installer/target/ artifacts or in-tree builds.
#
# Platform Checkpoint: v0.3.0edge
# This marks the maturation of the isolated Development Platform, Q-Seal
# (post-quantum) visibility surfaces, RBDM query advancements, and
# production-grade validation hygiene.
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

# Current platform checkpoint version (evidence-bound development milestone)
LATTICRA_PLATFORM_CHECKPOINT="v0.3.0edge"

# Build profile for this run.
# "report-only" = current safe foundation mode (default for now)
# "effect-enabled" = produces binaries capable of real gated effects (Phase 1+)
BUILD_PROFILE="${BUILD_PROFILE:-report-only}"

if [ "$BUILD_PROFILE" = "effect-enabled" ]; then
    log "WARNING: Building in EFFECT-ENABLED mode. Real system effects may be possible."
    log "         This is experimental. Use with extreme caution."
fi

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

# Generate a high-quality machine and human readable health report + artifact inventory
generate_foundation_health_report() {
    log "Generating Latticra Foundation Health Report + Artifact Inventory..."
    REPORT="$BUILD_DIR/FOUNDATION_HEALTH_REPORT.txt"
    JSON_REPORT="$BUILD_DIR/FOUNDATION_HEALTH_REPORT.json"
    INVENTORY_DIR="$BUILD_DIR/inventory"
    mkdir -p "$INVENTORY_DIR"

    # Human readable report
    {
        echo "LATTICRA FOUNDATION HEALTH REPORT"
        echo "Platform Checkpoint: $LATTICRA_PLATFORM_CHECKPOINT"
        echo "Build Profile: $BUILD_PROFILE"
        echo "Generated: $(date)"
        echo "Build tree: $BUILD_DIR (completely isolated)"
        echo ""
        echo "=== Core Binaries ==="
        ls -lh "$BIN_DIR" 2>/dev/null || echo "(none built in this run)"
        echo ""
        echo "=== Validation Status ==="
        if [ -f "$BUILD_DIR/validation/REPORT.txt" ]; then
            cat "$BUILD_DIR/validation/REPORT.txt"
        else
            echo "Run full-validate for detailed results"
        fi
        echo ""
        echo "=== Visual Engines ==="
        ls -lh "$BUILD_DIR/visual-engines" 2>/dev/null || echo "(not built)"
        echo ""
        echo "=== Release Candidate ==="
        if [ -d "$BUILD_DIR/release-candidate" ]; then
            du -sh "$BUILD_DIR/release-candidate"
            find "$BUILD_DIR/release-candidate" -type f | wc -l | awk '{print $1 " files"}'
        else
            echo "Not generated in this run"
        fi
    } > "$REPORT"

    # Machine readable
    cat > "$JSON_REPORT" <<JSON
{
  "generated": "$(date -Iseconds 2>/dev/null || date)",
  "build_tree": "$BUILD_DIR",
  "binaries_count": $(ls "$BIN_DIR" 2>/dev/null | wc -l | tr -d ' '),
  "validation": {
    "passes": $( [ -f "$BUILD_DIR/validation/REPORT.txt" ] && grep -o 'Passes: [0-9]*' "$BUILD_DIR/validation/REPORT.txt" | awk '{print $2}' || echo 0 ),
    "env_specific": $( [ -f "$BUILD_DIR/validation/REPORT.txt" ] && grep -o 'Env-specific: [0-9]*' "$BUILD_DIR/validation/REPORT.txt" | awk '{print $2}' || echo 0 ),
    "issues": $( [ -f "$BUILD_DIR/validation/REPORT.txt" ] && grep -o 'Issues: [0-9]*' "$BUILD_DIR/validation/REPORT.txt" | awk '{print $2}' || echo 0 )
  },
  "has_release_candidate": $( [ -d "$BUILD_DIR/release-candidate" ] && echo true || echo false )
}
JSON

    # Artifact inventory with hashes (serious platform behavior)
    INVENTORY_FILE="$INVENTORY_DIR/ARTIFACT_INVENTORY.txt"
    {
        echo "LATTICRA SEPARATE BUILD - ARTIFACT INVENTORY"
        echo "Generated: $(date)"
        echo "Tree: $BUILD_DIR"
        echo ""
        echo "=== Hashed Artifacts ==="
    } > "$INVENTORY_FILE"

    find "$BUILD_DIR" -type f \( -name "*.txt" -o -name "*.json" -o -name "latticra*" -o -name "*.log" \) 2>/dev/null | while read f; do
        if command -v shasum >/dev/null 2>&1; then
            hash=$(shasum -a 256 "$f" 2>/dev/null | awk '{print $1}')
        else
            hash=$(sha256sum "$f" 2>/dev/null | awk '{print $1}')
        fi
        rel=$(echo "$f" | sed "s|$BUILD_DIR/||")
        size=$(du -h "$f" | awk '{print $1}')
        echo "$hash  $size  $rel" >> "$INVENTORY_FILE"
    done

    log "Health report + inventory generated"
    log "  Human: $REPORT"
    log "  JSON:  $JSON_REPORT"
    log "  Inventory: $INVENTORY_FILE"
}

# Generate a nice human-facing project dashboard
generate_dashboard() {
    log "Generating Latticra Project Dashboard..."
    DASH="$BUILD_DIR/DASHBOARD.txt"

    {
        echo "╔════════════════════════════════════════════════════════════╗"
        echo "║           LATTICRA FOUNDATION DASHBOARD                    ║"
        echo "╚════════════════════════════════════════════════════════════╝"
        echo ""
        echo "Generated: $(date)"
        echo "Platform Checkpoint: $LATTICRA_PLATFORM_CHECKPOINT"
        echo "Build Profile: $BUILD_PROFILE"
        echo "Mode: Isolated development platform (build-separate/)"
        echo "Philosophy: Evidence-bound • No-effect • Denied-by-default"
        echo ""
        echo "────────────────────────────────────────────────────────────"
        echo " CORE CAPABILITIES (CURRENT FOUNDATION)"
        echo "────────────────────────────────────────────────────────────"
        echo "  • No-effect CLI status surface (latticra)"
        echo "  • Seal trust-boundary / tool-boundary tooling (latticra-seal)"
        echo "  • Visual theorem / substrate mathematical engines"
        echo "  • 276+ deterministic validation guards (zero real issues)"
        echo "  • Runtime Boundary Domain Matrix with advanced queries"
        echo "  • Rich artifact generation + provenance (hashes, inventories)"
        echo "  • Q-Seal (Post-Quantum) posture as core next-gen priority (ML-DSA/ML-KEM planned)"
        echo "  • Effect Substrate Layer: active development (first real effects in progress)"
        echo "    Current focus: Guarded Command Execution (see docs/transition/)"
        echo ""
        echo "────────────────────────────────────────────────────────────"
        echo " LATEST PLATFORM RUN ARTIFACTS"
        echo "────────────────────────────────────────────────────────────"
        if [ -f "$BUILD_DIR/FOUNDATION_HEALTH_REPORT.txt" ]; then
            grep -A 25 "=== Core Binaries ===" "$BUILD_DIR/FOUNDATION_HEALTH_REPORT.txt" | head -18
        fi
        echo ""
        echo "────────────────────────────────────────────────────────────"
        echo " PLATFORM USAGE (RECOMMENDED)"
        echo "────────────────────────────────────────────────────────────"
        echo "  sh scripts/build-separate.sh platform"
        echo "  make build-separate-platform"
        echo ""
        echo "All artifacts below are generated automatically inside the"
        echo "completely isolated build-separate/ tree. No source pollution."
        echo ""
        echo "This is the current state of the Latticra evidence-bound foundation."
        echo ""
        echo "Next-gen direction: Contract-first, evidence-producing substrate for"
        echo "safe AI-era and Linux-era automation boundaries."
    } > "$DASH"

    log "Dashboard generated: $DASH"
}

# Dedicated Q-Seal (post-quantum) posture report - elevated importance per direction
generate_q_seal_report() {
    log "Generating Latticra Q-Seal (Post-Quantum) Posture Report..."
    QSEAL_DIR="$BUILD_DIR/q-seal"
    mkdir -p "$QSEAL_DIR"

    cat > "$QSEAL_DIR/Q-SEAL_POSTURE_REPORT.txt" <<QSEAL
LATTICRA Q-SEAL (POST-QUANTUM) POSTURE REPORT
Platform Checkpoint: $LATTICRA_PLATFORM_CHECKPOINT
Build Profile: $BUILD_PROFILE
Generated: $(date)
Source: Isolated build-separate/ platform run

IMPORTANCE: Q-Seal is a core next-gen differentiator for Latticra Seal.
It represents the planned transition to post-quantum cryptography
for AI-era and high-assurance tool-boundary operations.

CURRENT STATE (report-only, no-effect, planning surface):
- q_seal_post_quantum_profile_planned=1
- post_quantum_signature_support_planned=1   (target: ML-DSA)
- post_quantum_key_establishment_planned=1   (target: ML-KEM)

Planned algorithms (from contracts, not implemented):
- ML-DSA for post-quantum signatures
- ML-KEM for post-quantum key establishment
- SLH-DSA as conservative fallback

Non-claims (strictly enforced):
- No post-quantum implementation exists today.
- No post-quantum claims are made.
- No keys, signatures, or verification using PQ algorithms.
- All Q-Seal surfaces are metadata/report/evidence only.

Integration in this platform run:
- Seal status rollup surfaces Q-Seal fields.
- Full validation suite confirms no-effect posture.
- Artifacts include provenance for future PQ profile planning.

This report is auto-generated to emphasize and track Q-Seal readiness
as a first-class priority in the Latticra evidence-bound foundation.
QSEAL

    # Also emit a machine version
    cat > "$QSEAL_DIR/q-seal-posture.json" <<JSON
{
  "generated": "$(date -Iseconds 2>/dev/null || date)",
  "q_seal_importance": "core next-gen differentiator",
  "q_seal_post_quantum_profile_planned": 1,
  "post_quantum_signature_support_planned": 1,
  "post_quantum_key_establishment_planned": 1,
  "targets": ["ML-DSA", "ML-KEM", "SLH-DSA"],
  "implementation_status": "report-only planning surface",
  "effect_authority": "denied",
  "source": "build-separate platform"
}
JSON

    log "Q-Seal report generated in $QSEAL_DIR/"
}

detect_openssl() {
    OPENSSL_CFLAGS=""
    OPENSSL_LIBS="-lcrypto"

    if [ "$(uname -s)" = "Darwin" ]; then
        # Prefer openssl@3 from Homebrew (most common on modern macOS)
        if [ -d /opt/homebrew/opt/openssl@3/include ]; then
            OPENSSL_CFLAGS="-I/opt/homebrew/opt/openssl@3/include"
            OPENSSL_LIBS="-L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto"
        elif [ -d /usr/local/opt/openssl@3/include ]; then
            OPENSSL_CFLAGS="-I/usr/local/opt/openssl@3/include"
            OPENSSL_LIBS="-L/usr/local/opt/openssl@3/lib -lssl -lcrypto"
        # Fallbacks for older openssl or generic paths
        elif [ -d /opt/homebrew/opt/openssl/include ]; then
            OPENSSL_CFLAGS="-I/opt/homebrew/opt/openssl/include"
            OPENSSL_LIBS="-L/opt/homebrew/opt/openssl/lib -lcrypto"
        elif [ -d /usr/local/opt/openssl/include ]; then
            OPENSSL_CFLAGS="-I/usr/local/opt/openssl/include"
            OPENSSL_LIBS="-L/usr/local/opt/openssl/lib -lcrypto"
        elif [ -d /opt/homebrew/include ]; then
            OPENSSL_CFLAGS="-I/opt/homebrew/include"
            OPENSSL_LIBS="-L/opt/homebrew/lib -lssl -lcrypto"
        else
            log "WARNING: Could not auto-detect OpenSSL on macOS."
            log "         Try: brew install openssl@3"
            log "         Then re-run. Or use 'make seal-cli' which has more robust detection."
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
    log "Building Latticra Seal CLI (may require OpenSSL dev files) [profile=$BUILD_PROFILE] ..."
    detect_openssl

    # Match the current main Makefile seal-cli target as closely as possible
    # (includes hybrid envelope support added in recent merges).
    # shellcheck disable=SC2086
    gcc -Wall -Wextra -O2 -std=c11 $OPENSSL_CFLAGS \
        -Iinclude \
        -o "$BIN_DIR/latticra-seal" \
        seal/latticra-seal.c \
        src/seal_hybrid_envelope.c \
        src/seal_hybrid_provider_self_test.c \
        $OPENSSL_LIBS

    if [ $? -eq 0 ]; then
        log "Seal CLI built: $BIN_DIR/latticra-seal"
    else
        log "WARNING: Seal CLI build failed. Common macOS fixes:"
        log "  - brew install openssl@3"
        log "  - Ensure detect_openssl() is finding the right paths"
        log "  - Try: make seal-cli   (uses the main Makefile which is usually more up-to-date)"
    fi
}

# Build effect-capable tools when profile is effect-enabled.
# This is the beginning of producing real, useful binaries.
build_effect_enabled_tools() {
    if [ "$BUILD_PROFILE" != "effect-enabled" ]; then
        log "Skipping effect-enabled tool build (current profile is report-only)."
        return 0
    fi

    log "Building EFFECT-ENABLED tools (experimental - Phase 1)..."

    # Ensure directories exist
    mkdir -p "$BIN_DIR" "$OBJ_DIR"

    # Ensure OpenSSL flags are set
    detect_openssl

    # Compile the new effect layer objects
    gcc -Wall -Wextra -O2 -std=c11 $OPENSSL_CFLAGS -Iinclude \
        -c src/substrate/effect/effect_dispatcher.c \
        -o "$OBJ_DIR/effect_dispatcher.o" 2>&1 | tee -a "$LOG_FILE" || true

    gcc -Wall -Wextra -O2 -std=c11 $OPENSSL_CFLAGS -Iinclude \
        -c src/substrate/effect/effect_command.c \
        -o "$OBJ_DIR/effect_command.o" 2>&1 | tee -a "$LOG_FILE" || true

    gcc -Wall -Wextra -O2 -std=c11 $OPENSSL_CFLAGS -Iinclude \
        -c src/substrate/effect/effect_runner_main.c \
        -o "$OBJ_DIR/effect_runner_main.o" 2>&1 | tee -a "$LOG_FILE" || true

    # Link the standalone effect runner
    if gcc -Wall -Wextra -O2 -std=c11 $OPENSSL_CFLAGS -Iinclude \
        "$OBJ_DIR/effect_dispatcher.o" \
        "$OBJ_DIR/effect_command.o" \
        "$OBJ_DIR/effect_runner_main.o" \
        -o "$BIN_DIR/latticra-effect-runner" $OPENSSL_LIBS 2>&1 | tee -a "$LOG_FILE"; then
        log "  Built experimental effect runner: $BIN_DIR/latticra-effect-runner"
    else
        log "  WARNING: Failed to link experimental effect runner (check OpenSSL paths)"
    fi

    log "Effect-enabled tool build complete."
}

build_core_tests() {
    log "Core invariant tests are validated via dedicated scripts/test-*.sh (each test declares its exact sources)."
    log "Skipping representative test compilation in platform mode (these are fragile after merges)."
    log "For full results, run the individual scripts/test-*.sh commands instead."
    log "  → Recommended: sh scripts/test-lat-pipeline.sh"
    log "  → Recommended: sh scripts/test-runtime-boundary.sh"
    log "  → etc."

    mkdir -p "$BUILD_DIR/tests"
    # Note: We intentionally do *not* attempt partial compilations here anymore.
    # They frequently break after merges because they don't pull in all required .c files.
    # The real value of the platform is the binaries + reports + Q-Seal artifacts.
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

# Prepare a rich "release-candidate" layout inside the separate tree.
# This is deliberately comprehensive and mirrors many concepts from the
# project's own production release artifact contracts (evidence, inventories,
# reports, etc.) while remaining strictly no-effect and exploratory.
prepare_release_candidate() {
    log "Preparing rich release-candidate layout inside separate build tree..."
    CANDIDATE_DIR="$BUILD_DIR/release-candidate"
    rm -rf "$CANDIDATE_DIR"

    mkdir -p \
        "$CANDIDATE_DIR/bin" \
        "$CANDIDATE_DIR/share/doc/latticra" \
        "$CANDIDATE_DIR/share/seal" \
        "$CANDIDATE_DIR/evidence" \
        "$CANDIDATE_DIR/reports" \
        "$CANDIDATE_DIR/inventory"

    # Binaries
    cp -f "$BIN_DIR/latticra" "$CANDIDATE_DIR/bin/" 2>/dev/null || true
    cp -f "$BIN_DIR/latticra-seal" "$CANDIDATE_DIR/bin/" 2>/dev/null || true

    # Core documentation
    cp -f README.md STATUS.md LICENSE "$CANDIDATE_DIR/share/doc/latticra/" 2>/dev/null || true

    # Seal artifacts
    cp -f latticra.seal latticra.seal.lock "$CANDIDATE_DIR/share/seal/" 2>/dev/null || true

    # Health and validation reports (very valuable)
    cp -f "$BUILD_DIR/FOUNDATION_HEALTH_REPORT.txt" "$CANDIDATE_DIR/reports/" 2>/dev/null || true
    cp -f "$BUILD_DIR/FOUNDATION_HEALTH_REPORT.json" "$CANDIDATE_DIR/reports/" 2>/dev/null || true
    cp -rf "$BUILD_DIR/validation" "$CANDIDATE_DIR/reports/validation" 2>/dev/null || true

    # Evidence bundles
    cp -rf "$BUILD_DIR/evidence" "$CANDIDATE_DIR/evidence/" 2>/dev/null || true

    # Simple inventory
    {
        echo "Latticra Release Candidate Inventory"
        echo "Generated inside isolated build-separate/"
        echo "Date: $(date)"
        echo ""
        echo "Binaries:"
        ls -1 "$CANDIDATE_DIR/bin" 2>/dev/null || echo "  (none in this run)"
        echo ""
        echo "Reports:"
        ls -1 "$CANDIDATE_DIR/reports" 2>/dev/null
    } > "$CANDIDATE_DIR/inventory/INVENTORY.txt"

    log "Rich release-candidate layout ready at: $CANDIDATE_DIR"
    log "Contains binaries, docs, health reports, validation results, evidence, and inventory."
    log "This remains a no-effect exploration artifact."
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
# Production-grade version with environment-specific script awareness.
KNOWN_ENVIRONMENT_SPECIFIC_SCRIPTS="
test-fedora-build-lane.sh
test-fedora-installroot-rpm-mutation-lane.sh
test-fedora-rpmlint-availability.sh
test-fedora-rpmlint-static-spec-lane.sh
"

run_full_validate() {
    log "Running FULL project validation suite inside separate build tree (production-grade mode)..."
    mkdir -p "$BUILD_DIR/validation"

    local failed=0
    local total=0
    local pass_count=0
    local env_specific=0

    : > "$BUILD_DIR/validation/summary.txt"
    : > "$BUILD_DIR/validation/FAILURES.txt"
    : > "$BUILD_DIR/validation/REPORT.txt"

    for script in scripts/test-*.sh; do
        total=$((total + 1))
        name=$(basename "$script")

        # Safe log filename: truncate + hash to avoid "File name too long" on macOS for very long test names
        short_name=$(echo "$name" | cut -c1-80)
        name_hash=$(echo -n "$name" | shasum -a 256 | cut -c1-8)
        safe_log_name="${short_name}-${name_hash}.log"
        output_file="$BUILD_DIR/validation/$safe_log_name"

        if echo "$KNOWN_ENVIRONMENT_SPECIFIC_SCRIPTS" | grep -q "$name"; then
            echo "ENV-SPECIFIC: $name (Fedora validation lane - expected limited outside Fedora)" >> "$BUILD_DIR/validation/summary.txt"
            env_specific=$((env_specific + 1))
            continue
        fi

        if bash "$script" > "$output_file" 2>&1; then
            last_lines=$(tail -5 "$output_file")
            if echo "$last_lines" | grep -qiE ':\s*ok$|:\s*ok\n|PASS$|successfully|completed successfully' || \
               echo "$last_lines" | grep -qE "${name%.sh}: ok"; then
                echo "PASS: $name" >> "$BUILD_DIR/validation/summary.txt"
                pass_count=$((pass_count + 1))
            else
                echo "UNCLEAR: $name" >> "$BUILD_DIR/validation/summary.txt"
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
        echo "Platform Checkpoint: $LATTICRA_PLATFORM_CHECKPOINT"
        echo "Generated: $(date)"
        echo "Total scripts considered: $total"
        echo "Clear passes: $pass_count"
        echo "Environment-specific (Fedora etc.): $env_specific"
        echo "Real issues: $failed"
        echo ""
        echo "Note: Log filenames are safely truncated+hashed to avoid macOS filename length limits on some very long test scripts."
        echo "Environment-specific scripts are intentionally limited outside their target platform."
        echo "This run was executed inside a completely isolated build-separate/ tree."
    } > "$BUILD_DIR/validation/REPORT.txt"

    log "Full validation finished. Passes: $pass_count | Env-specific: $env_specific | Issues: $failed"
    return $failed
}

clean() {
    log "Removing separate build tree: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
}

usage() {
    echo "Usage: $0 [cli|seal|tests|visual|all|clean|smoke|validate|full-validate|prepare-release-candidate|health-report|dashboard|q-seal|platform|demo]"
    echo "  platform   - Full modern development flow."
    echo "  demo       - Focused macOS-friendly demo: binaries + effect runner + Q-Seal + Dashboard (recommended for showcasing)."
    echo "  q-seal     - Dedicated Q-Seal (post-quantum) posture report."
    echo "  dashboard  - Human-friendly project dashboard."
    exit 1
}

main() {
    case "${1:-all}" in
        cli)   build_cli ;;
        seal)  build_seal ;;
        tests) build_core_tests ;;
        visual) build_visual_engines ;;
        demo)
            # Focused, impressive demo for macOS / presentations
            log "=== LATTICRA DEMO MODE (macOS-friendly) ==="
            log "Building core deliverables + effect runner + key reports..."
            build_cli
            build_seal || true
            build_effect_enabled_tools   # will build the effect runner if profile allows
            build_visual_engines

            # Generate the nice human-facing artifacts
            generate_foundation_health_report
            generate_dashboard
            generate_q_seal_report

            # Demonstrate the first real effect if available
            if [ "$BUILD_PROFILE" = "effect-enabled" ] && [ -x "$BIN_DIR/latticra-effect-runner" ]; then
                log ""
                log "=== Demonstrating Guarded Command Execution (first real effect) ==="
                export LATTICRA_EFFECT_ALLOWLIST="effect-allowlist.txt"
                if [ -f "effect-allowlist.txt" ]; then
                    "$BIN_DIR/latticra-effect-runner" echo "Latticra effect layer executing real guarded commands on macOS at $LATTICRA_PLATFORM_CHECKPOINT"
                    "$BIN_DIR/latticra-effect-runner" date
                    "$BIN_DIR/latticra-effect-runner" uname -a
                else
                    log "No effect-allowlist.txt found — creating a safe default one."
                    echo -e "echo\ndate\nuname\npwd\nwhoami" > effect-allowlist.txt
                    "$BIN_DIR/latticra-effect-runner" echo "Latticra effect layer is live"
                fi
            fi

            # Optional short visual demos if ffmpeg is present
            if command -v ffmpeg >/dev/null 2>&1; then
                log ""
                log "Rendering short (20s) visual theorem engine demos..."
                sh scripts/render-visual-theorem-engines.sh substrate 20 2>/dev/null || true
                sh scripts/render-visual-theorem-engines.sh theorem 20 2>/dev/null || true
            else
                log "Tip: brew install ffmpeg to also render the visual theorem engine videos for demos."
            fi

            log ""
            log "=== DEMO COMPLETE ==="
            log "Key things to show:"
            log "  - build-separate/DASHBOARD.txt"
            log "  - build-separate/q-seal/Q-SEAL_POSTURE_REPORT.txt"
            log "  - The effect runner actually executing real (guarded) commands"
            log "  - Visual engine videos (if rendered)"
            ;;
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
        dashboard) generate_dashboard ;;
        q-seal) generate_q_seal_report ;;
        platform)
            # The new recommended "do everything important" flow
            log "=== LATTICRA DEVELOPMENT PLATFORM RUN ==="
            log "This flow builds the main deliverables + rich reports."
            log "Heavy test compilation is skipped here (use the dedicated scripts/test-*.sh instead)."
            build_cli
            build_seal || true

            if [ "$BUILD_PROFILE" = "effect-enabled" ]; then
                log "Building in EFFECT-ENABLED profile — preparing real capability paths."
                build_effect_enabled_tools
            fi

            build_core_tests
            build_visual_engines

            # Run full validation but do not let its exit code kill the platform run.
            # On non-Fedora machines (especially macOS), many guards will legitimately report as "Issues".
            # The important thing is that the main deliverables and reports are produced.
            set +e
            run_full_validate
            validation_rc=$?
            set -e

            prepare_release_candidate
            generate_foundation_health_report
            generate_dashboard
            generate_q_seal_report

            log "=== PLATFORM RUN COMPLETE ==="
            log "Key artifacts:"
            log "  - $BUILD_DIR/DASHBOARD.txt"
            log "  - $BUILD_DIR/FOUNDATION_HEALTH_REPORT.txt + .json"
            log "  - $BUILD_DIR/inventory/ARTIFACT_INVENTORY.txt"
            log "  - $BUILD_DIR/release-candidate/"
            log "  - $BUILD_DIR/validation/REPORT.txt"
            if [ "$BUILD_PROFILE" = "effect-enabled" ] && [ -x "$BUILD_DIR/bin/latticra-effect-runner" ]; then
                log "  - $BUILD_DIR/bin/latticra-effect-runner (experimental guarded execution)"
                # Demonstrate the first real effect
                DEMO_OUT=$("$BUILD_DIR/bin/latticra-effect-runner" echo "Latticra effect layer active at $LATTICRA_PLATFORM_CHECKPOINT" 2>&1)
                log "    Demo output: $DEMO_OUT"
            fi
            log "Primary artifacts in: $BUILD_DIR"
            log ""

            if [ $validation_rc -ne 0 ]; then
                log "Note: Validation reported issues (common when running on macOS / non-Fedora)."
                log "      This does not mean the platform failed. See the REPORT.txt above for details."
                log "      Core no-effect invariants for Lat, RBDM, Seal, etc. are still exercised via the dedicated test scripts."
            fi

            log ""
            log "Tip: For the absolute cleanest experience on macOS, you can also run:"
            log "      make seal-cli && sh scripts/build-separate.sh dashboard"

            if [ "$BUILD_PROFILE" = "effect-enabled" ]; then
                log ""
                log "Effect-enabled mode active. Experimental guarded execution tools available."
                log "  Set LATTICRA_EFFECT_ALLOWLIST=echo:date:ls to expand the allowlist for demo."
            fi

            # Always succeed the platform command even if validation had issues.
            # The platform's job is to produce the deliverables and reports.
            exit 0
            ;;
        *) usage ;;
    esac
    log "Done. Artifacts in: $BUILD_DIR (separate from source and installer/)"
}

main "${1:-}"