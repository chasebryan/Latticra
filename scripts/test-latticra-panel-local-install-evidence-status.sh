#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel local install evidence status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel local install evidence status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/LATTICRA_PANEL_LOCAL_INSTALL_EVIDENCE_STATUS.md'
index='docs/status/README.md'

require_file "$status"
require_file "$index"
require_file README.md
require_file installer/README.md
require_file installer/Makefile
require_file installer/scripts/latticra-installer-apply.sh
require_file installer/scripts/latticra-installer-verify.sh
require_file .github/workflows/latticra-panel-installer.yml

require_contains 'Status: evidence status alignment' "$status"
require_contains 'Date: 2026-05-22' "$status"
require_contains 'Fedora Workstation user-local Latticra Panel install verification completed successfully' "$status"
require_contains 'source=operator Fedora Workstation transcript' "$status"
require_contains 'host_os=Fedora Linux 44 (Workstation Edition)' "$status"
require_contains 'kernel=Linux 7.0.9-205.fc44.x86_64 x86_64 GNU/Linux' "$status"
require_contains 'install_prefix=/home/ckbryan/.local/share/latticra' "$status"
require_contains 'user_bin=/home/ckbryan/.local/bin' "$status"
require_contains 'which_latticra=/home/ckbryan/.local/bin/latticra' "$status"
require_contains 'which_lat=/home/ckbryan/.local/bin/lat' "$status"
require_contains 'which_latticra_seal=/home/ckbryan/.local/bin/latticra-seal' "$status"
require_contains 'which_latticra_panel=/home/ckbryan/.local/bin/latticra-panel' "$status"
require_contains 'Latticra local install verification: ok' "$status"
require_contains 'ok: desktop entry -> /home/ckbryan/.local/share/applications/latticra-panel.desktop' "$status"
require_contains 'ok: desktop icon -> /home/ckbryan/.local/share/icons/hicolor/256x256/apps/latticra-panel.png' "$status"
require_contains 'ok: latticra-seal report generated' "$status"
require_contains 'ok: Latticra Panel launcher is available' "$status"
require_contains 'mode=report-only' "$status"
require_contains 'network_authority=0' "$status"
require_contains 'runtime_enforcement_authority=0' "$status"
require_contains 'developer-cli-helpers.installed' "$status"
require_contains 'docs-and-examples.installed' "$status"
require_contains 'latticra-seal.installed' "$status"
require_contains 'lat-tooling.installed' "$status"
require_contains 'lir-contracts.installed' "$status"
require_contains 'latticra_panel_user_local_install_verified=1' "$status"
require_contains 'latticra_panel_desktop_entry_present=1' "$status"
require_contains 'latticra_panel_desktop_icon_present=1' "$status"
require_contains 'latticra_seal_report_generated=1' "$status"
require_contains 'root_authority=0' "$status"
require_contains 'kernel_modification_performed=0' "$status"
require_contains 'systemd_modification_performed=0' "$status"
require_contains 'selinux_modification_performed=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'root_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'daily_driver_install_ready=0' "$status"
require_contains 'immutable_fedora_ready=0' "$status"
require_contains '/usr/bin/latticra' "$status"
require_contains '/etc/latticra' "$status"
require_contains '/usr/lib/systemd/system/latticra.service' "$status"
require_contains '/usr/lib/modules' "$status"
require_contains '/boot/latticra' "$status"
require_contains 'Add public README/status wording limited to Fedora user-local Latticra Panel installation evidence' "$status"
require_contains 'not production installer readiness' "$status"

require_contains 'LATTICRA_PANEL_LOCAL_INSTALL_EVIDENCE_STATUS.md' "$index"
require_contains 'Current Latticra Panel local install evidence checkpoint' "$index"
require_contains 'latticra_panel_user_local_install_verified=1' "$index"
require_contains 'latticra_panel_desktop_entry_present=1' "$index"
require_contains 'latticra_panel_desktop_icon_present=1' "$index"
require_contains 'latticra_seal_report_generated=1' "$index"
require_contains 'network_authority=0' "$index"
require_contains 'runtime_enforcement_authority=0' "$index"
require_contains 'production_installer_ready=0' "$index"
require_contains 'root_installer_ready=0' "$index"
require_contains 'Add public README/status wording limited to Fedora user-local Latticra Panel installation evidence' "$index"

printf 'latticra_panel_local_install_evidence_status: ok\n'
