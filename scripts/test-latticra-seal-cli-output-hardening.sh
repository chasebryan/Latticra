#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c11 -Wall -Wextra -Werror}"

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$ROOT"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-cli-output-hardening.XXXXXX")"
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

$CC $CFLAGS $OPENSSL_CFLAGS seal/latticra-seal.c $OPENSSL_LIBS -o "$tmpdir/latticra-seal"

case_root="$tmpdir/case-root"
mkdir "$case_root"
cp latticra.seal README.md LICENSE "$case_root/"

victim_reports="$tmpdir/victim-reports"
mkdir "$victim_reports"
ln -s "$victim_reports" "$case_root/reports"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-report.out" 2>&1); then
  fail "Seal CLI check must refuse a symlinked reports directory"
fi

require_contains "refusing symlink report directory" "$tmpdir/symlink-report.out"

[ ! -e "$victim_reports/latticra-seal-cli-report.txt" ] ||
  fail "Seal CLI must not write reports through a symlinked reports directory"

rm "$case_root/reports"
mkdir "$case_root/reports"

victim_lock="$tmpdir/victim-lock"
printf 'do-not-overwrite\n' > "$victim_lock"
ln -s "$victim_lock" "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/symlink-baseline.out" 2>&1); then
  fail "Seal CLI baseline must refuse a symlinked baseline path"
fi

require_contains "could not write baseline: latticra.seal.lock" "$tmpdir/symlink-baseline.out"

if [ "$(cat "$victim_lock")" != "do-not-overwrite" ]; then
  fail "Seal CLI must not overwrite a symlink target while writing the baseline"
fi

printf 'PASS: Latticra Seal CLI output hardening rejects symlink writes\n'
