#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c11 -Wall -Wextra -Werror}"

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$ROOT"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-stdout-errors.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

fail() {
  printf 'FAIL: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

OPENSSL_CFLAGS="${OPENSSL_CFLAGS:-}"
OPENSSL_LIBS="${OPENSSL_LIBS:-}"

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v pkg-config >/dev/null 2>&1; then
  if pkg-config --exists openssl; then
    OPENSSL_CFLAGS="$(pkg-config --cflags openssl)"
    OPENSSL_LIBS="$(pkg-config --libs openssl)"
  fi
fi

if [ -z "$OPENSSL_LIBS" ]; then
  OPENSSL_LIBS="-lcrypto"
fi

$CC $CFLAGS $OPENSSL_CFLAGS -Iinclude \
  seal/latticra-seal.c \
  src/seal_hybrid_envelope.c \
  src/seal_hybrid_provider_self_test.c \
  $OPENSSL_LIBS \
  -o "$tmpdir/latticra-seal"

case_root="$tmpdir/case-root"
mkdir "$case_root"
cp latticra.seal README.md LICENSE "$case_root/"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/check.out" 2>&1); then
  cat "$tmpdir/check.out" >&2 || true
  fail "Seal CLI check must prepare report and hash artifacts"
fi

if ! (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/baseline.out" 2>&1); then
  cat "$tmpdir/baseline.out" >&2 || true
  fail "Seal CLI baseline must prepare a local hash baseline"
fi

require_contains "Baseline written to: latticra.seal.lock" "$tmpdir/baseline.out"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/verify.out" 2>&1); then
  cat "$tmpdir/verify.out" >&2 || true
  fail "Seal CLI verify must compare a matching hash baseline"
fi

require_contains "STATUS: PASS" "$tmpdir/verify.out"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" report > "$tmpdir/report.out" 2> "$tmpdir/report.err"); then
  cat "$tmpdir/report.err" >&2 || true
  fail "Seal CLI report command must stream an existing report"
fi

require_contains "Latticra Seal CLI Report" "$tmpdir/report.out"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/hashes.out" 2> "$tmpdir/hashes.err"); then
  cat "$tmpdir/hashes.err" >&2 || true
  fail "Seal CLI hashes command must stream an existing hash list"
fi

require_contains "latticra.seal" "$tmpdir/hashes.out"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" manifest > "$tmpdir/manifest.out" 2> "$tmpdir/manifest.err"); then
  cat "$tmpdir/manifest.err" >&2 || true
  fail "Seal CLI manifest command must stream a valid manifest summary"
fi

require_contains "Latticra Seal Manifest Summary" "$tmpdir/manifest.out"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" hybrid > "$tmpdir/hybrid.out" 2> "$tmpdir/hybrid.err"); then
  cat "$tmpdir/hybrid.err" >&2 || true
  fail "Seal CLI hybrid command must stream a valid self-check report"
fi

require_contains "LATTICRA SEAL HYBRID ENVELOPE SELF-CHECK" "$tmpdir/hybrid.out"
require_contains "secret_material_output=redacted" "$tmpdir/hybrid.out"
require_contains "salt_output=redacted" "$tmpdir/hybrid.out"
require_contains "nonce_output=redacted" "$tmpdir/hybrid.out"
require_contains "record_output=redacted" "$tmpdir/hybrid.out"
require_contains "record_header_authenticated=1" "$tmpdir/hybrid.out"
require_contains "attached_record_sealed=1" "$tmpdir/hybrid.out"
require_contains "attached_record_opened=1" "$tmpdir/hybrid.out"
require_contains "hybrid_envelope_self_check=pass" "$tmpdir/hybrid.out"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" hybrid-provider-self-test > "$tmpdir/hybrid-provider-self-test.out" 2> "$tmpdir/hybrid-provider-self-test.err"); then
  cat "$tmpdir/hybrid-provider-self-test.err" >&2 || true
  fail "Seal CLI hybrid-provider-self-test command must stream a valid provider self-test report"
fi

require_contains "LATTICRA SEAL HYBRID PROVIDER SELF-TEST" "$tmpdir/hybrid-provider-self-test.out"
require_contains "provider_runtime_used=1" "$tmpdir/hybrid-provider-self-test.out"
require_contains "ml_kem_parameter_sets_tested=3" "$tmpdir/hybrid-provider-self-test.out"
require_contains "hybrid_envelope_authenticated=1" "$tmpdir/hybrid-provider-self-test.out"
require_contains "runtime_authority_granted=0" "$tmpdir/hybrid-provider-self-test.out"
require_contains "hybrid_provider_self_test=pass" "$tmpdir/hybrid-provider-self-test.out"

if ! "$tmpdir/latticra-seal" version > "$tmpdir/version.out" 2> "$tmpdir/version.err"; then
  cat "$tmpdir/version.err" >&2 || true
  fail "Seal CLI version command must stream version output"
fi

require_contains "latticra-seal v" "$tmpdir/version.out"

if ! "$tmpdir/latticra-seal" help > "$tmpdir/help.out" 2> "$tmpdir/help.err"; then
  cat "$tmpdir/help.err" >&2 || true
  fail "Seal CLI help command must stream help output"
fi

require_contains "Usage:" "$tmpdir/help.out"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" check) 2> "$tmpdir/check-closed-stdout.err"; then
  fail "Seal CLI check command must fail when stdout cannot be written"
fi

require_contains "could not write check report to stdout" "$tmpdir/check-closed-stdout.err"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" verify) 2> "$tmpdir/verify-closed-stdout.err"; then
  fail "Seal CLI verify command must fail when stdout cannot be written"
fi

require_contains "could not write verify report to stdout" "$tmpdir/verify-closed-stdout.err"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" baseline) 2> "$tmpdir/baseline-closed-stdout.err"; then
  fail "Seal CLI baseline command must fail when stdout cannot be written"
fi

require_contains "could not write check report to stdout" "$tmpdir/baseline-closed-stdout.err"
require_contains "baseline refused because check did not pass" "$tmpdir/baseline-closed-stdout.err"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" report) 2> "$tmpdir/report-closed-stdout.err"; then
  fail "Seal CLI report command must fail when stdout cannot be written"
fi

require_contains "could not write reports/latticra-seal-cli-report.txt to stdout" "$tmpdir/report-closed-stdout.err"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" hashes) 2> "$tmpdir/hashes-closed-stdout.err"; then
  fail "Seal CLI hashes command must fail when stdout cannot be written"
fi

require_contains "could not write reports/latticra-seal-cli-hashes.txt to stdout" "$tmpdir/hashes-closed-stdout.err"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" manifest) 2> "$tmpdir/manifest-closed-stdout.err"; then
  fail "Seal CLI manifest command must fail when stdout cannot be written"
fi

require_contains "could not write manifest summary to stdout" "$tmpdir/manifest-closed-stdout.err"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" hybrid) 2> "$tmpdir/hybrid-closed-stdout.err"; then
  fail "Seal CLI hybrid command must fail when stdout cannot be written"
fi

require_contains "could not write hybrid envelope" "$tmpdir/hybrid-closed-stdout.err"

if (cd "$case_root" && exec 1>&- && "$tmpdir/latticra-seal" hybrid-provider-self-test) 2> "$tmpdir/hybrid-provider-self-test-closed-stdout.err"; then
  fail "Seal CLI hybrid-provider-self-test command must fail when stdout cannot be written"
fi

require_contains "could not write hybrid provider self-test report to stdout" "$tmpdir/hybrid-provider-self-test-closed-stdout.err"

if (exec 1>&- && "$tmpdir/latticra-seal" version) 2> "$tmpdir/version-closed-stdout.err"; then
  fail "Seal CLI version command must fail when stdout cannot be written"
fi

require_contains "could not write version to stdout" "$tmpdir/version-closed-stdout.err"

if (exec 1>&- && "$tmpdir/latticra-seal" help) 2> "$tmpdir/help-closed-stdout.err"; then
  fail "Seal CLI help command must fail when stdout cannot be written"
fi

require_contains "could not write help to stdout" "$tmpdir/help-closed-stdout.err"

printf 'PASS: Latticra Seal stdout-writing commands fail on stdout write errors\n'
