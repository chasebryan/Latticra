#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'kernel_scheduler: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

require_file docs/KERNEL_SCHEDULER_SEED.md
require_file .github/workflows/kernel-scheduler.yml
require_file scripts/test-kernel-scheduler-report-runner.sh

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-scheduler.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra-kernel-scheduler"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/kernel_subsystem_registry.c \
  src/kernel_scheduler.c \
  tests/kernel_scheduler.c \
  -o "$bin"

"$bin"
