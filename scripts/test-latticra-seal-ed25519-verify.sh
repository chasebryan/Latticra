#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-ed25519-verify.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

OPENSSL_CFLAGS="${OPENSSL_CFLAGS:-}"
OPENSSL_LIBS="${OPENSSL_LIBS:-}"

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v pkg-config >/dev/null 2>&1; then
  if pkg-config --exists openssl; then
    OPENSSL_CFLAGS="$(pkg-config --cflags openssl)"
    OPENSSL_LIBS="$(pkg-config --libs openssl)"
  fi
fi

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v brew >/dev/null 2>&1; then
  openssl_prefix="$(brew --prefix openssl@3 2>/dev/null || brew --prefix openssl 2>/dev/null || true)"
  if [ -n "$openssl_prefix" ]; then
    OPENSSL_CFLAGS="-I$openssl_prefix/include"
    OPENSSL_LIBS="-L$openssl_prefix/lib -lcrypto"
  fi
fi

if [ -z "$OPENSSL_LIBS" ]; then
  OPENSSL_LIBS="-lcrypto"
fi

cc $CFLAGS $OPENSSL_CFLAGS -Iinclude src/seal_ed25519_verify.c tests/seal_ed25519_verify_invariants.c $OPENSSL_LIBS -o "$tmpdir/latticra-seal-ed25519-verify-invariants"
"$tmpdir/latticra-seal-ed25519-verify-invariants"
