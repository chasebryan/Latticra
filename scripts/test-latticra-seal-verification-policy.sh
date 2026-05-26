#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-verification-policy.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_verification_policy.c \
  tests/seal_verification_policy_invariants.c \
  -o "$tmpdir/latticra-seal-verification-policy-invariants"

"$tmpdir/latticra-seal-verification-policy-invariants"
