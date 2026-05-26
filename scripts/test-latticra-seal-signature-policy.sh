#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signature-policy.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_signature_policy.c \
  tests/seal_signature_policy_invariants.c \
  -o "$tmpdir/latticra-seal-signature-policy-invariants"

"$tmpdir/latticra-seal-signature-policy-invariants"
