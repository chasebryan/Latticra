#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
cd "$ROOT"

MANIFEST="latticra.seal"
REPORT_DIR="reports"
REPORT="$REPORT_DIR/latticra-seal-report.txt"
HASH_LIST="$REPORT_DIR/latticra-seal-file-hashes.txt"

mkdir -p "$REPORT_DIR"
: > "$REPORT"

fail=0
warn=0

log() {
  printf '%s\n' "$*" | tee -a "$REPORT"
}

section() {
  printf '\n== %s ==\n' "$1" | tee -a "$REPORT"
}

pass() {
  log "PASS: $*"
}

warning() {
  warn=$((warn + 1))
  log "WARN: $*"
}

failure() {
  fail=$((fail + 1))
  log "FAIL: $*"
}

log "Latticra Seal Smoke Report"
log "Generated: $(date -u +%Y-%m-%dT%H:%M:%SZ)"
log "Root: $ROOT"

section "Manifest presence"

if [[ -f "$MANIFEST" ]]; then
  pass "$MANIFEST exists"
else
  failure "$MANIFEST is missing"
fi

section "Manifest shape"

if [[ -f "$MANIFEST" ]]; then
  grep -Fq 'schema = "latticra.seal/v0.1"' "$MANIFEST" \
    && pass "schema is latticra.seal/v0.1" \
    || failure "schema is missing or incorrect"

  grep -Fq 'format = "toml"' "$MANIFEST" \
    && pass "format is TOML-compatible" \
    || failure "format field is missing"

  grep -Fq 'kind = "local-integrity-manifest"' "$MANIFEST" \
    && pass "kind is local-integrity-manifest" \
    || failure "kind field is missing"

  grep -Fq 'algorithm = "sha256"' "$MANIFEST" \
    && pass "hash algorithm is sha256" \
    || failure "sha256 algorithm field is missing"
fi

section "Required project files"

for required in README.md LICENSE; do
  if [[ -f "$required" ]]; then
    pass "$required exists"
  else
    failure "$required is missing"
  fi
done

section "Secret filename scan"

secret_filename_hits="$(
  find . \
    -path './.git' -prune -o \
    -path './target' -prune -o \
    -path './build' -prune -o \
    -path './dist' -prune -o \
    -path './node_modules' -prune -o \
    -path './.venv' -prune -o \
    -type f \( \
      -name '.env' -o \
      -name 'id_rsa' -o \
      -name 'id_ed25519' -o \
      -name '*.pem' -o \
      -name '*.key' \
    \) -print
)"

if [[ -n "$secret_filename_hits" ]]; then
  failure "possible secret-bearing filenames found:"
  printf '%s\n' "$secret_filename_hits" | tee -a "$REPORT"
else
  pass "no obvious secret-bearing filenames found"
fi

section "Secret content marker scan"

secret_content_hits="$(
  grep -RIlE \
    --exclude-dir=.git \
    --exclude-dir=target \
    --exclude-dir=build \
    --exclude-dir=dist \
    --exclude-dir=node_modules \
    --exclude-dir=.venv \
    --exclude='latticra.seal' \
    --exclude='latticra-seal-smoke.sh' \
    'BEGIN PRIVATE KEY|BEGIN RSA PRIVATE KEY|BEGIN OPENSSH PRIVATE KEY|OPENAI_API_KEY=|GITHUB_TOKEN=|AWS_SECRET_ACCESS_KEY=' \
    . 2>/dev/null || true
)"

if [[ -n "$secret_content_hits" ]]; then
  failure "possible secret content markers found:"
  printf '%s\n' "$secret_content_hits" | tee -a "$REPORT"
else
  pass "no obvious secret content markers found"
fi

section "Digest summary"

if command -v sha256sum >/dev/null 2>&1; then
  manifest_digest="$(sha256sum "$MANIFEST" | awk '{print $1}')"
  log "manifest_sha256: $manifest_digest"

  find . \
    -path './.git' -prune -o \
    -path './target' -prune -o \
    -path './build' -prune -o \
    -path './dist' -prune -o \
    -path './node_modules' -prune -o \
    -path './.venv' -prune -o \
    -path './reports' -prune -o \
    -type f -print0 \
    | sort -z \
    | xargs -0 -r sha256sum > "$HASH_LIST"

  file_count="$(wc -l < "$HASH_LIST" | tr -d ' ')"
  root_digest="$(sha256sum "$HASH_LIST" | awk '{print $1}')"

  log "hashed_files: $file_count"
  log "hash_list: $HASH_LIST"
  log "root_digest_v0_1: $root_digest"
else
  warning "sha256sum is not available; digest summary skipped"
fi

section "Result"

if [[ "$fail" -eq 0 ]]; then
  log "STATUS: PASS"
  log "Warnings: $warn"
  log "Report written to: $REPORT"
  exit 0
else
  log "STATUS: FAIL"
  log "Failures: $fail"
  log "Warnings: $warn"
  log "Report written to: $REPORT"
  exit 1
fi
