#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel local install public entrypoint alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel local install public entrypoint alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

alignment='docs/status/LATTICRA_PANEL_LOCAL_INSTALL_PUBLIC_ENTRYPOINT_ALIGNMENT.md'
evidence='docs/status/LATTICRA_PANEL_LOCAL_INSTALL_EVIDENCE_STATUS.md'
readme='README.md'
installer_readme='installer/README.md'

require_file "$alignment"
require_file "$evidence"
require_file "$readme"
require_file "$installer_readme"
require_file installer/latticra-installer/src/ui.rs
require_file scripts/test-latticra-panel-local-install-evidence-status.sh
require_file scripts/check_latticra_panel_ui_design.py

require_contains 'Status: public entrypoint alignment' "$alignment"
require_contains 'Date: 2026-05-22' "$alignment"
require_contains 'successful Fedora Workstation user-local Latticra Panel install evidence milestone' "$alignment"
require_contains 'latticra_panel_user_local_install_verified=1' "$alignment"
require_contains 'latticra_panel_command_wrapper_present=1' "$alignment"
require_contains 'latticra_panel_desktop_entry_present=1' "$alignment"
require_contains 'latticra_panel_desktop_icon_present=1' "$alignment"
require_contains 'latticra_panel_launcher_available=1' "$alignment"
require_contains 'latticra_seal_report_generated=1' "$alignment"
require_contains 'network_authority=0' "$alignment"
require_contains 'runtime_enforcement_authority=0' "$alignment"
require_contains 'root_authority=0' "$alignment"
require_contains 'production_installer_ready=0' "$alignment"
require_contains 'root_installer_ready=0' "$alignment"
require_contains 'fedora_distribution_ready=0' "$alignment"
require_contains 'fedora_approval_claimed=0' "$alignment"
require_contains 'daily_driver_install_ready=0' "$alignment"
require_contains 'immutable_fedora_ready=0' "$alignment"
require_contains 'make -C installer local-example' "$alignment"
require_contains 'make -C installer verify-local' "$alignment"
require_contains 'This installer is user-local only. It does not use root, modify the kernel, modify systemd, change SELinux, or use network authority.' "$alignment"
require_contains 'docs/status/LATTICRA_PANEL_LOCAL_INSTALL_EVIDENCE_STATUS.md' "$alignment"
require_contains 'Latticra Panel now has Fedora Workstation user-local install evidence' "$alignment"
require_contains 'not mean Latticra Panel is a production installer' "$alignment"
require_contains '/usr/bin/latticra' "$alignment"
require_contains '/etc/latticra' "$alignment"
require_contains '/usr/lib/systemd/system/latticra.service' "$alignment"
require_contains '/usr/lib/modules' "$alignment"
require_contains '/boot/latticra' "$alignment"
require_contains 'Add status-index integration for Latticra Panel local-install evidence and public-entrypoint alignment' "$alignment"

require_contains 'Latticra Panel is the GUI-first local installer and first-run control workbench for Latticra, Lat, LIR, and Latticra Seal.' "$readme"
require_contains 'make -C installer local-example' "$readme"
require_contains 'make -C installer verify-local' "$readme"
require_contains 'It is intentionally user-local. It does not use root authority, kernel mutation, systemd mutation, SELinux mutation, or network authority.' "$readme"

require_contains 'Graphical installer and first-run control panel for Latticra, Lat, LIR, and Latticra Seal.' "$installer_readme"
require_contains 'The console in the upper-right of the panel is not a shell.' "$installer_readme"
require_contains 'External host processes are not launched from the embedded console.' "$installer_readme"
require_contains 'no root' "$installer_readme"
require_contains 'no network authority' "$installer_readme"
require_contains 'user-local prefix only' "$installer_readme"

require_contains 'Status: evidence status alignment' "$evidence"
require_contains 'latticra_panel_user_local_install_verified=1' "$evidence"
require_contains 'latticra_seal_report_generated=1' "$evidence"
require_contains 'network_authority=0' "$evidence"
require_contains 'runtime_enforcement_authority=0' "$evidence"
require_contains 'production_installer_ready=0' "$evidence"
require_contains 'root_installer_ready=0' "$evidence"

printf 'latticra_panel_local_install_public_entrypoint_alignment: ok\n'
