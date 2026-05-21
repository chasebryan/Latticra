#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/fedora_rpm_removal_rollback.c \
  tests/fedora_rpm_removal_rollback.c \
  -o /tmp/latticra-fedora-rpm-removal-rollback

/tmp/latticra-fedora-rpm-removal-rollback

printf 'fedora_rpm_removal_rollback_classifier: ok\n'
