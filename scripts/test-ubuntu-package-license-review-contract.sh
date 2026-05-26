#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu package license review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu package license review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'

require_file "$contract"
require_file "$status"
require_file docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md
require_file docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md
require_file docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md
require_file LICENSE
require_file docs/LICENSE_POLICY.md
require_file docs/LICENSE_MIGRATION_PLAN.md
require_file packaging/ubuntu/debian/copyright
require_file src/latticra_cli.c
require_file README.md

require_contains 'Status: no-effect package license review contract' "$contract"
require_contains 'root_license_current=Apache-2.0' "$contract"
require_contains 'new_software_direction=AGPL-3.0-or-later' "$contract"
require_contains 'no_silent_relicensing=1' "$contract"
require_contains 'documentation_license_decision_present=0' "$contract"
require_contains 'cli_payload_source=src/latticra_cli.c' "$contract"
require_contains 'cli_payload_spdx=AGPL-3.0-or-later' "$contract"
require_contains 'doc_payload_source=README.md' "$contract"
require_contains 'doc_payload_license_reviewed=0' "$contract"
require_contains 'candidate_binary_payload_license=AGPL-3.0-or-later' "$contract"
require_contains 'candidate_doc_payload_license=Apache-2.0-or-docs-decision-pending' "$contract"
require_contains 'candidate_source_package_license=AGPL-3.0-or-later AND Apache-2.0' "$contract"
require_contains 'candidate_expression_applied_to_packaging=0' "$contract"
require_contains 'candidate_expression_accepted=1' "$contract"
require_contains 'packaging_license_expression_updated=1' "$contract"
require_contains 'ubuntu_package_license_review_status=blocked-pending-formal-review' "$contract"
require_contains 'ubuntu_package_notice_inventory_present=1' "$contract"
require_contains 'ubuntu_package_notice_inventory_report_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision' "$contract"
require_contains 'ubuntu_third_party_material_review_contract_present=1' "$contract"
require_contains 'ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review' "$contract"
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' "$contract"
require_contains 'ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' "$contract"
require_contains 'ubuntu_package_notice_review_contract_present=1' "$contract"
require_contains 'ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review' "$contract"
require_contains 'ubuntu_package_license_review_unblocked=0' "$contract"
require_contains 'license_expression_reviewed=0' "$contract"
require_contains 'license_expression_unresolved=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$contract"
require_contains 'ubuntu_package_license_review_contract: ok' "$contract"

require_contains 'Apache License' LICENSE
require_contains 'Apache-2.0' docs/LICENSE_POLICY.md
require_contains 'AGPL-3.0-or-later' docs/LICENSE_POLICY.md
require_contains 'No silent relicensing' docs/LICENSE_POLICY.md
require_contains 'Documentation license remains undecided' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'SPDX-License-Identifier: AGPL-3.0-or-later' src/latticra_cli.c
require_contains 'LicenseRef-Latticra-TBD' packaging/ubuntu/debian/copyright

require_contains 'ubuntu_package_license_review_contract_present=1' "$status"
require_contains 'ubuntu_package_license_review_status=blocked-pending-formal-review' "$status"
require_contains 'ubuntu_package_notice_inventory_present=1' "$status"
require_contains 'ubuntu_package_notice_inventory_report_present=1' "$status"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$status"
require_contains 'ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision' "$status"
require_contains 'ubuntu_third_party_material_review_contract_present=1' "$status"
require_contains 'ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review' "$status"
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' "$status"
require_contains 'ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' "$status"
require_contains 'ubuntu_package_notice_review_contract_present=1' "$status"
require_contains 'ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review' "$status"
require_contains 'license_expression_candidate_recorded=1' "$status"
require_contains 'ubuntu_package_license_review_unblocked=0' "$status"
require_contains 'packaging_license_expression_updated=0' "$status"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$status"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$status"

printf 'ubuntu_package_license_review_contract: ok\n'
