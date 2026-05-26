#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu package license promotion gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu package license promotion gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
license_contract='docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md'
notice_gate_contract='docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md'
build_transcript_contract='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-package-license-promotion-gate-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$license_contract"
require_file "$notice_gate_contract"
require_file docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md
require_file "$build_transcript_contract"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file docs/LICENSE_POLICY.md
require_file docs/LICENSE_MIGRATION_PLAN.md
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/copyright

require_contains 'Status: no-effect package license promotion gate contract' "$contract"
require_contains 'license_policy_present=1' "$contract"
require_contains 'license_migration_plan_present=1' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_notice_review_contract_present=1' "$contract"
require_contains 'ubuntu_package_license_review_contract_present=1' "$contract"
require_contains 'root_license_state_reviewed=1' "$contract"
require_contains 'cli_payload_spdx_reviewed=1' "$contract"
require_contains 'doc_payload_license_reviewed=1' "$contract"
require_contains 'documentation_license_decision_present=1' "$contract"
require_contains 'third_party_notice_reviewed=1' "$contract"
require_contains 'debian_copyright_format_reviewed=1' "$contract"
require_contains 'candidate_expression_accepted=1' "$contract"
require_contains 'packaging_license_expression_updated=1' "$contract"
require_contains 'license_expression_reviewed=1' "$contract"
require_contains 'license_expression_unresolved=0' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$contract"
require_contains 'ubuntu_package_license_review_status=resolved-license-expression-recorded' "$contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion' "$contract"
require_contains 'ubuntu_package_notice_review_unblocked=0' "$contract"
require_contains 'ubuntu_package_license_review_unblocked=1' "$contract"
require_contains 'license_expression_candidate_recorded=1' "$contract"
require_contains 'license_expression_reviewed=1' "$contract"
require_contains 'license_expression_unresolved=0' "$contract"
require_contains 'packaging_license_expression_updated=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_contract: ok' "$contract"

require_contains 'License: AGPL-3.0-or-later' packaging/ubuntu/debian/copyright
require_contains 'Documentation license is decided' docs/LICENSE_MIGRATION_PLAN.md

require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$status"
require_contains 'ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$status"
require_contains 'license_expression_reviewed=1' "$status"
require_contains 'license_expression_unresolved=0' "$status"
require_contains 'packaging_license_expression_updated=1' "$status"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$status"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$status"
require_contains 'docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-package-license-promotion-gate-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-package-license-promotion-gate-contract.yml' "$status"

require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$license_contract"
require_contains 'ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$license_contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$notice_gate_contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$build_transcript_contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md
require_contains 'package_license_promotion_gate_contract_present=1' "$static_validation"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$readiness"
require_contains 'docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-package-license-promotion-gate-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-package-license-promotion-gate-contract.sh' "$workflow"

printf 'ubuntu_package_license_promotion_gate_contract: ok\n'
