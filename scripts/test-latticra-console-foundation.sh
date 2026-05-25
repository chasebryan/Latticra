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
  src/kernel.c \
  src/latticra_console.c \
  tests/latticra_console_foundation.c \
  -o /tmp/latticra-console-foundation

/tmp/latticra-console-foundation

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/latticra_console.c \
  tools/latticra_console_report.c \
  -o /tmp/latticra-console-report

/tmp/latticra-console-report > /tmp/latticra-console-report.txt

grep -Fq 'LATTICRA CONSOLE REPORT' /tmp/latticra-console-report.txt
grep -Fq 'console_id=latticra-console' /tmp/latticra-console-report.txt
grep -Fq 'short_name=LC' /tmp/latticra-console-report.txt
grep -Fq 'component_key=latticra_console' /tmp/latticra-console-report.txt
grep -Fq 'console_status=ready-report-only' /tmp/latticra-console-report.txt
grep -Fq 'command_registry_status=seed-registry-ready' /tmp/latticra-console-report.txt
grep -Fq 'command_registry_source=c-static-table' /tmp/latticra-console-report.txt
grep -Fq 'command_registry_no_effect=1' /tmp/latticra-console-report.txt
grep -Fq 'LATTICRA CONSOLE COMMAND REGISTRY' /tmp/latticra-console-report.txt
grep -Fq 'command=lc substrate' /tmp/latticra-console-report.txt
grep -Fq 'capability=lc.substrate.inspect' /tmp/latticra-console-report.txt
grep -Fq 'launches_host_process=0' /tmp/latticra-console-report.txt
grep -Fq 'substrate_bridge_status=metadata-bound-ready' /tmp/latticra-console-report.txt
grep -Fq 'panel_installable=1' /tmp/latticra-console-report.txt
grep -Fq 'future_os_base_claim=planned_not_claimed' /tmp/latticra-console-report.txt
grep -Fq 'execution_allowed=0' /tmp/latticra-console-report.txt
grep -Fq 'network_allowed=0' /tmp/latticra-console-report.txt
grep -Fq 'boot_allowed=0' /tmp/latticra-console-report.txt

grep -Fq '[components.latticra_console]' installer/manifests/components.toml
grep -Fq 'latticra_console = true' installer/configs/default.installer.toml
grep -Fq 'latticra_console = true' installer/configs/local-prefix-example.installer.toml
grep -Fq 'pub latticra_console: bool' installer/latticra-installer/src/config.rs
grep -Fq 'Latticra Console (LC)' installer/latticra-installer/src/ui.rs
grep -Fq 'LATTICRA_CONSOLE=$(cfg latticra_console true)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'latticra-lc' installer/scripts/latticra-installer-apply.sh
grep -Fq 'Latticra Console Foundation' docs/LATTICRA_CONSOLE_FOUNDATION.md

printf 'latticra_console_foundation: ok\n'
