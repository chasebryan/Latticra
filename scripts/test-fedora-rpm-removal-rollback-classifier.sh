#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-fedora-rpm-removal-rollback-classifier.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/fedora_rpm_removal_rollback.c \
  tests/fedora_rpm_removal_rollback.c \
  -o "$tmpdir/latticra-fedora-rpm-removal-rollback"

"$tmpdir/latticra-fedora-rpm-removal-rollback"

printf 'fedora_rpm_removal_rollback_classifier: ok\n'
