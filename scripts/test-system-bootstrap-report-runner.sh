#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  tools/system_bootstrap_report.c \
  -o /tmp/latticra-system-bootstrap-report

/tmp/latticra-system-bootstrap-report > /tmp/latticra-system-bootstrap-report.txt

grep -Fq 'LATTICRA SYSTEM BOOTSTRAP REPORT' /tmp/latticra-system-bootstrap-report.txt
grep -Fq 'bootstrap_id=latticra-system-bootstrap' /tmp/latticra-system-bootstrap-report.txt
grep -Fq 'system_status=startup-report-ready' /tmp/latticra-system-bootstrap-report.txt
grep -Fq 'effect_boundary=no-effect' /tmp/latticra-system-bootstrap-report.txt
grep -Fq 'runtime_entry_status=not-entered' /tmp/latticra-system-bootstrap-report.txt
grep -Fq 'no_effect=1' /tmp/latticra-system-bootstrap-report.txt

printf 'system_bootstrap_report_runner: ok\n'
