#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu package notice inventory: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu package notice inventory: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
review_contract='docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md'
workflow='.github/workflows/ubuntu-package-notice-inventory.yml'

require_file "$doc"
require_file "$status"
require_file "$review_contract"
require_file "$workflow"
require_file scripts/ubuntu-package-notice-inventory.sh
require_file packaging/ubuntu/debian/copyright
require_file src/latticra_cli.c
require_file README.md

require_contains 'Status: no-effect package notice inventory' "$doc"
require_contains 'package_scope=local-deb-draft' "$doc"
require_contains 'binary_payload=usr/bin/latticra' "$doc"
require_contains 'binary_payload_source=src/latticra_cli.c' "$doc"
require_contains 'binary_payload_spdx=AGPL-3.0-or-later' "$doc"
require_contains 'doc_payload=usr/share/doc/latticra/README.md' "$doc"
require_contains 'doc_payload_source=README.md' "$doc"
require_contains 'ubuntu_package_notice_inventory_present=1' "$doc"
require_contains 'ubuntu_package_notice_inventory_report_present=1' "$doc"
require_contains 'third_party_material_inventory_recorded=1' "$doc"
require_contains 'third_party_material_inventory_reviewed=0' "$doc"
require_contains 'generated_artifact_notice_reviewed=0' "$doc"
require_contains 'ubuntu_package_notice_review_unblocked=0' "$doc"
require_contains 'sh scripts/ubuntu-package-notice-inventory.sh' "$doc"
require_contains 'ubuntu_package_notice_inventory: ok' "$doc"

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
report="$tmpdir/ubuntu-package-notice-inventory.txt"
sh scripts/ubuntu-package-notice-inventory.sh >"$report"

require_contains 'UBUNTU PACKAGE NOTICE INVENTORY' "$report"
require_contains 'inventory_status=ok' "$report"
require_contains 'inventory_mode=no-effect' "$report"
require_contains 'binary_payload_source_present=1' "$report"
require_contains 'binary_payload_spdx_present=1' "$report"
require_contains 'doc_payload_source_present=1' "$report"
require_contains 'root_license_present=1' "$report"
require_contains 'notice_file_present=0' "$report"
require_contains 'third_party_material_inventory_recorded=1' "$report"
require_contains 'third_party_material_inventory_reviewed=0' "$report"
require_contains 'debian_copyright_present=1' "$report"
require_contains 'debian_copyright_license_ref_tbd=1' "$report"
require_contains 'ubuntu_package_notice_inventory_present=1' "$report"
require_contains 'ubuntu_package_notice_review_unblocked=0' "$report"
require_contains 'host_mutation=0' "$report"
require_contains 'package_build_performed=0' "$report"

require_contains 'ubuntu_package_notice_inventory_present=1' "$status"
require_contains 'ubuntu_package_notice_inventory_report_present=1' "$status"
require_contains 'third_party_material_inventory_recorded=1' "$status"
require_contains 'third_party_material_inventory_reviewed=0' "$status"
require_contains 'ubuntu_package_notice_inventory_present=1' "$review_contract"
require_contains 'docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md' "$status"
require_contains 'scripts/test-ubuntu-package-notice-inventory.sh' "$status"
require_contains '.github/workflows/ubuntu-package-notice-inventory.yml' "$status"
require_contains 'sh scripts/test-ubuntu-package-notice-inventory.sh' "$workflow"

printf 'ubuntu_package_notice_inventory: ok\n'
