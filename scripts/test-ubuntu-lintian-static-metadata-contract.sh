#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu lintian static metadata contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu lintian static metadata contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
availability='docs/UBUNTU_LINTIAN_AVAILABILITY.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
license_gate='docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md'
build_transcript_contract='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md'
acceptance_gate='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-lintian-static-metadata-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$availability"
require_file "$static_validation"
require_file "$license_gate"
require_file "$build_transcript_contract"
require_file "$acceptance_gate"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/control
require_file packaging/ubuntu/debian/rules
require_file packaging/ubuntu/debian/changelog
require_file packaging/ubuntu/debian/copyright
require_file packaging/ubuntu/debian/install
require_file packaging/ubuntu/debian/source/format

require_contains 'Status: no-effect lintian static metadata contract' "$contract"
require_contains 'ubuntu_lintian_availability_present=1' "$contract"
require_contains 'ubuntu_local_deb_static_validation_present=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_status=blocked-pending-package-license-prerequisites' "$contract"
require_contains 'debian_control_present=1' "$contract"
require_contains 'debian_rules_present=1' "$contract"
require_contains 'debian_changelog_present=1' "$contract"
require_contains 'debian_copyright_present=1' "$contract"
require_contains 'debian_install_present=1' "$contract"
require_contains 'debian_source_format_present=1' "$contract"
require_contains 'rules_requires_root_no=1' "$contract"
require_contains 'license_expression_reviewed=1' "$contract"
require_contains 'license_expression_unresolved=0' "$contract"
require_contains 'packaging_license_expression_updated=1' "$contract"
require_contains 'lintian_command_recorded=1' "$contract"
require_contains 'lintian_static_metadata_findings_classified=1' "$contract"
require_contains 'lintian_expected_draft_findings_classified=1' "$contract"
require_contains 'lintian_unexpected_findings_classified=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion' "$contract"
require_contains 'lintian_static_metadata_run=0' "$contract"
require_contains 'lintian_command_recorded=0' "$contract"
require_contains 'lintian_static_metadata_findings_classified=0' "$contract"
require_contains 'lintian_expected_draft_findings_classified=0' "$contract"
require_contains 'lintian_unexpected_findings_classified=0' "$contract"
require_contains 'license_expression_reviewed=0' "$contract"
require_contains 'license_expression_unresolved=1' "$contract"
require_contains 'packaging_license_expression_updated=0' "$contract"
require_contains 'deb_artifact_created=0' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$contract"
require_contains 'ubuntu_lintian_static_metadata_contract: ok' "$contract"

require_contains 'Status: active tool availability lane' "$availability"
require_contains 'does not lint the Latticra deb draft yet' "$availability"
require_contains 'Status: active static validation lane' "$static_validation"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$license_gate"
require_contains 'LicenseRef-Latticra-TBD' packaging/ubuntu/debian/copyright
require_contains 'Rules-Requires-Root: no' packaging/ubuntu/debian/control
require_contains 'build/latticra usr/bin' packaging/ubuntu/debian/install
require_contains '3.0 (quilt)' packaging/ubuntu/debian/source/format

require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$status"
require_contains 'ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion' "$status"
require_contains 'lintian_static_metadata_run=0' "$status"
require_contains 'lintian_static_metadata_findings_classified=0' "$status"
require_contains 'lintian_expected_draft_findings_classified=0' "$status"
require_contains 'lintian_unexpected_findings_classified=0' "$status"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$status"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$status"
require_contains 'docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-lintian-static-metadata-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-lintian-static-metadata-contract.yml' "$status"

require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$build_transcript_contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$acceptance_gate"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$readiness"
require_contains 'docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-lintian-static-metadata-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-lintian-static-metadata-contract.sh' "$workflow"

printf 'ubuntu_lintian_static_metadata_contract: ok\n'
