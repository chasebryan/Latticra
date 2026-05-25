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
/tmp/latticra-console-report help > /tmp/latticra-console-help.txt
/tmp/latticra-console-report man > /tmp/latticra-console-man.txt
/tmp/latticra-console-report boundary > /tmp/latticra-console-boundary.txt
/tmp/latticra-console-report host-contract > /tmp/latticra-console-host-contract.txt

grep -Fq 'LATTICRA CONSOLE REPORT' /tmp/latticra-console-report.txt
grep -Fq 'console_id=latticra-console' /tmp/latticra-console-report.txt
grep -Fq 'short_name=LC' /tmp/latticra-console-report.txt
grep -Fq 'component_key=latticra_console' /tmp/latticra-console-report.txt
grep -Fq 'console_status=ready-report-only' /tmp/latticra-console-report.txt
grep -Fq 'command_registry_status=seed-registry-ready' /tmp/latticra-console-report.txt
grep -Fq 'command_registry_source=c-static-table' /tmp/latticra-console-report.txt
grep -Fq 'command_registry_no_effect=1' /tmp/latticra-console-report.txt
grep -Fq 'runtime_boundary_bound=1' /tmp/latticra-console-report.txt
grep -Fq 'seal_capability_labels_bound=1' /tmp/latticra-console-report.txt
grep -Fq 'LATTICRA CONSOLE COMMAND REGISTRY' /tmp/latticra-console-report.txt
grep -Fq 'command=lc profiles' /tmp/latticra-console-report.txt
grep -Fq 'capability=lc.core.profiles' /tmp/latticra-console-report.txt
grep -Fq 'command=lc host-contract' /tmp/latticra-console-report.txt
grep -Fq 'capability=lc.host.contract' /tmp/latticra-console-report.txt
grep -Fq 'command=lc substrate' /tmp/latticra-console-report.txt
grep -Fq 'capability=lc.substrate.inspect' /tmp/latticra-console-report.txt
grep -Fq 'launches_host_process=0' /tmp/latticra-console-report.txt
grep -Fq 'substrate_bridge_status=metadata-bound-ready' /tmp/latticra-console-report.txt
grep -Fq 'host_embedding_contract_status=metadata-only-contract-ready' /tmp/latticra-console-report.txt
grep -Fq 'host_embedding_contract_present=1' /tmp/latticra-console-report.txt
grep -Fq 'panel_installable=1' /tmp/latticra-console-report.txt
grep -Fq 'future_os_base_claim=planned_not_claimed' /tmp/latticra-console-report.txt
grep -Fq 'execution_allowed=0' /tmp/latticra-console-report.txt
grep -Fq 'network_allowed=0' /tmp/latticra-console-report.txt
grep -Fq 'boot_allowed=0' /tmp/latticra-console-report.txt
grep -Fq 'LATTICRA CONSOLE HELP' /tmp/latticra-console-help.txt
grep -Fq 'registry_source=c-static-table' /tmp/latticra-console-help.txt
grep -Fq 'lc profiles' /tmp/latticra-console-help.txt
grep -Fq 'lc host-contract' /tmp/latticra-console-help.txt
grep -Fq 'lc substrate' /tmp/latticra-console-help.txt
grep -Fq 'capability=lc.substrate.inspect' /tmp/latticra-console-help.txt
grep -Fq 'host_process_launch_allowed=0' /tmp/latticra-console-help.txt
grep -Fq 'LATTICRA-CONSOLE(1)' /tmp/latticra-console-man.txt
grep -Fq 'COMMANDS' /tmp/latticra-console-man.txt
grep -Fq 'latticra-lc host-contract' /tmp/latticra-console-man.txt
grep -Fq 'production_os_claim=0' /tmp/latticra-console-man.txt
grep -Fq 'LATTICRA CONSOLE COMMAND BOUNDARY REPORT' /tmp/latticra-console-boundary.txt
grep -Fq 'runtime_boundary_bound=1' /tmp/latticra-console-boundary.txt
grep -Fq 'seal_capability_labels_bound=1' /tmp/latticra-console-boundary.txt
grep -Fq 'command=lc substrate' /tmp/latticra-console-boundary.txt
grep -Fq 'command=lc host-contract' /tmp/latticra-console-boundary.txt
grep -Fq 'runtime_request=authority-check' /tmp/latticra-console-boundary.txt
grep -Fq 'command=lc os' /tmp/latticra-console-boundary.txt
grep -Fq 'policy_matrix_cell=future-gated-operation' /tmp/latticra-console-boundary.txt
grep -Fq 'seal_capability=seal.capability.inspect' /tmp/latticra-console-boundary.txt
grep -Fq 'boot_allowed=0' /tmp/latticra-console-boundary.txt
grep -Fq 'LATTICRA CONSOLE HOST EMBEDDING CONTRACT' /tmp/latticra-console-host-contract.txt
grep -Fq 'contract_profile=lc-host-embedding-v0' /tmp/latticra-console-host-contract.txt
grep -Fq 'host_process_launch_allowed=0' /tmp/latticra-console-host-contract.txt
grep -Fq 'host_file_read_allowed=0' /tmp/latticra-console-host-contract.txt
grep -Fq 'promotion_gate=contract_receipt_and_read_only_host_inventory' /tmp/latticra-console-host-contract.txt

grep -Fq '[components.latticra_console]' installer/manifests/components.toml
grep -Fq 'latticra_console = true' installer/configs/default.installer.toml
grep -Fq 'latticra_console = true' installer/configs/local-prefix-example.installer.toml
grep -Fq 'pub latticra_console: bool' installer/latticra-installer/src/config.rs
grep -Fq 'pub struct LatticraConsoleConfig' installer/latticra-installer/src/config.rs
grep -Fq 'LatticraConsoleProfile::PanelEmbedded' installer/latticra-installer/src/config.rs
grep -Fq 'Latticra Console (LC)' installer/latticra-installer/src/ui.rs
grep -Fq 'WorkspaceTab::Console' installer/latticra-installer/src/ui.rs
grep -Fq 'profile = "panel_embedded"' installer/configs/default.installer.toml
grep -Fq 'command_registry_profile = "c-static-table"' installer/configs/default.installer.toml
grep -Fq 'host_embedding_contract_profile = "lc-host-embedding-v0"' installer/configs/default.installer.toml
grep -Fq 'LATTICRA_CONSOLE=$(cfg latticra_console true)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_PROFILE=$(cfg_section lc profile panel_embedded)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_HOST_EMBEDDING_CONTRACT_PROFILE=$(cfg_section lc host_embedding_contract_profile lc-host-embedding-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'profiles/hosted-reference.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'host-embedding/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'latticra-lc' installer/scripts/latticra-installer-apply.sh
grep -Fq 'render_lc_help()' installer/scripts/latticra-installer-apply.sh
grep -Fq 'render_lc_man()' installer/scripts/latticra-installer-apply.sh
grep -Fq 'render_lc_boundary()' installer/scripts/latticra-installer-apply.sh
grep -Fq 'Latticra Console Foundation' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Panel Profile Presets' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Host Embedding Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Help And Manpage Rendering' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Runtime Boundary Binding' docs/LATTICRA_CONSOLE_FOUNDATION.md

printf 'latticra_console_foundation: ok\n'
