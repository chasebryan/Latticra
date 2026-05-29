#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
TMP_DIR="$(mktemp -d)"
: "${CC:=cc}"
: "${CFLAGS:=-std=c11 -Wall -Wextra -Werror}"

OPENSSL_CFLAGS="${OPENSSL_CFLAGS:-}"
OPENSSL_LIBS="${OPENSSL_LIBS:-}"

if [[ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ]] && command -v pkg-config >/dev/null 2>&1; then
  if pkg-config --exists openssl; then
    OPENSSL_CFLAGS="$(pkg-config --cflags openssl)"
    OPENSSL_LIBS="$(pkg-config --libs openssl)"
  fi
fi

if [[ -z "$OPENSSL_LIBS" ]]; then
  OPENSSL_LIBS="-lcrypto"
fi

cleanup() {
  rm -rf "$TMP_DIR"
}

trap cleanup EXIT

fail() {
  printf 'FAIL: %s\n' "$1" >&2
  exit 1
}

pass() {
  printf 'PASS: %s\n' "$1"
}

NATIVE_SEAL="$TMP_DIR/latticra-seal"
"$CC" $CFLAGS $OPENSSL_CFLAGS -I"$ROOT/include" \
  "$ROOT/seal/latticra-seal.c" \
  "$ROOT/src/seal_hybrid_envelope.c" \
  "$ROOT/src/seal_hybrid_provider_self_test.c" \
  $OPENSSL_LIBS \
  -o "$NATIVE_SEAL"

copy_minimal_workspace() {
  dest="$1"
  mkdir -p "$dest/scripts"
  cp "$ROOT/README.md" "$dest/README.md"
  cp "$ROOT/LICENSE" "$dest/LICENSE"
  cp "$ROOT/latticra.seal" "$dest/latticra.seal"
  cp "$ROOT/scripts/latticra-seal-smoke.sh" "$dest/scripts/latticra-seal-smoke.sh"
}

expect_smoke_pass() {
  name="$1"
  dir="$2"
  if (cd "$dir" && bash scripts/latticra-seal-smoke.sh > smoke.out 2>&1); then
    pass "$name passed as expected"
  else
    cat "$dir/smoke.out" >&2 || true
    fail "$name should have passed"
  fi
}

expect_smoke_fail() {
  name="$1"
  dir="$2"
  if (cd "$dir" && bash scripts/latticra-seal-smoke.sh > smoke.out 2>&1); then
    cat "$dir/smoke.out" >&2 || true
    fail "$name should have failed"
  fi

  if grep -Fq 'STATUS: FAIL' "$dir/reports/latticra-seal-report.txt"; then
    pass "$name failed closed as expected"
  else
    cat "$dir/smoke.out" >&2 || true
    fail "$name failed without a STATUS: FAIL report"
  fi
}

expect_native_pass() {
  name="$1"
  dir="$2"
  if (cd "$dir" && "$NATIVE_SEAL" check > native.out 2>&1); then
    pass "$name native check passed as expected"
  else
    cat "$dir/native.out" >&2 || true
    fail "$name native check should have passed"
  fi
}

expect_native_fail() {
  name="$1"
  dir="$2"
  if (cd "$dir" && "$NATIVE_SEAL" check > native.out 2>&1); then
    cat "$dir/native.out" >&2 || true
    fail "$name native check should have failed"
  fi

  if grep -Fq 'STATUS: FAIL' "$dir/reports/latticra-seal-cli-report.txt"; then
    pass "$name native check failed closed as expected"
  else
    cat "$dir/native.out" >&2 || true
    fail "$name native check failed without a STATUS: FAIL report"
  fi
}

clean_case="$TMP_DIR/clean"
mkdir -p "$clean_case"
copy_minimal_workspace "$clean_case"
expect_smoke_pass "clean minimal Seal workspace" "$clean_case"
expect_native_pass "clean minimal Seal workspace" "$clean_case"

env_case="$TMP_DIR/env-denial"
mkdir -p "$env_case"
copy_minimal_workspace "$env_case"
printf '%s%s\n' 'OPENAI' '_API_KEY=dummy-value' > "$env_case/.env"
expect_smoke_fail "env file denial" "$env_case"
expect_native_fail "env file denial" "$env_case"

grep -Fq 'possible secret-bearing filenames found' "$env_case/reports/latticra-seal-report.txt" \
  || fail "env denial did not report secret-bearing filename evidence"
pass "env denial reported filename evidence"

grep -Fq 'possible secret-bearing filename: .env' "$env_case/reports/latticra-seal-cli-report.txt" \
  || fail "native env denial did not report secret-bearing filename evidence"
pass "native env denial reported filename evidence"

grep -Fq 'hash list not written because earlier checks failed' "$env_case/reports/latticra-seal-cli-report.txt" \
  || fail "native env denial did not block hash-list promotion after policy failure"
[[ ! -e "$env_case/reports/latticra-seal-cli-hashes.txt" ]] \
  || fail "native env denial promoted a hash list after policy failure"
pass "native env denial blocked hash-list promotion"

marker_case="$TMP_DIR/content-denial"
mkdir -p "$marker_case"
copy_minimal_workspace "$marker_case"
printf '%s%s%s\n' 'BEGIN ' 'PRIVATE' ' KEY' > "$marker_case/notes.txt"
expect_smoke_fail "content marker denial" "$marker_case"
expect_native_fail "content marker denial" "$marker_case"

grep -Fq 'possible secret content markers found' "$marker_case/reports/latticra-seal-report.txt" \
  || fail "content denial did not report content-marker evidence"
pass "content denial reported content-marker evidence"

grep -Fq 'possible secret content marker in: notes.txt' "$marker_case/reports/latticra-seal-cli-report.txt" \
  || fail "native content denial did not report content-marker evidence"
pass "native content denial reported content-marker evidence"

grep -Fq 'hash list not written because earlier checks failed' "$marker_case/reports/latticra-seal-cli-report.txt" \
  || fail "native content denial did not block hash-list promotion after policy failure"
[[ ! -e "$marker_case/reports/latticra-seal-cli-hashes.txt" ]] \
  || fail "native content denial promoted a hash list after policy failure"
pass "native content denial blocked hash-list promotion"

printf 'latticra_seal_policy_denials: ok\n'
