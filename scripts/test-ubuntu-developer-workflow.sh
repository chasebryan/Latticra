#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu developer workflow: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu developer workflow: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_file docs/UBUNTU_READINESS_PLAN.md
require_file docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_file docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md
require_file docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md
require_file docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file README.md
require_file installer/README.md
require_file packaging/ubuntu/README.md
require_file scripts/test-ubuntu-build-lane.sh
require_file .github/workflows/ubuntu-build-lane.yml
require_file .github/workflows/ubuntu-developer-workflow.yml

require_contains 'Status: developer workflow record' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'local Ubuntu Linux commands for productive Latticra development' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'sudo apt-get update' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'sudo apt-get install -y git build-essential make gcc pkg-config' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'sudo apt-get install -y rustc cargo make gcc pkg-config' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'sh scripts/test-ubuntu-build-lane.sh' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'ubuntu_build_lane: ok' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'make -C installer dry-run' docs/UBUNTU_DEVELOPER_WORKFLOW.md
require_contains 'ubuntu_developer_workflow: ok' docs/UBUNTU_DEVELOPER_WORKFLOW.md

require_contains 'Status: planning and compatibility record' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_build_lane_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_local_deb_draft_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_lintian_availability_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_package_notice_inventory_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_package_notice_inventory_report_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_third_party_material_review_contract_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_package_notice_review_contract_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_package_license_review_contract_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_package_license_review_status=blocked-pending-formal-review' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_local_deb_build_transcript_contract_present=1' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ppa_claimed=0' docs/UBUNTU_READINESS_PLAN.md
require_contains 'ubuntu_archive_ready=0' docs/UBUNTU_READINESS_PLAN.md

require_contains '### Ubuntu prerequisites' README.md
require_contains '## Ubuntu and local deb work' README.md
require_contains 'docs/UBUNTU_DEVELOPER_WORKFLOW.md' README.md
require_contains 'packaging/ubuntu/README.md' README.md
require_contains 'sh scripts/test-ubuntu-build-lane.sh' README.md
require_contains 'docs/UBUNTU_LINTIAN_AVAILABILITY.md' README.md
require_contains 'docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md' README.md
require_contains 'docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md' README.md

require_contains 'Ubuntu prerequisites:' docs/QUICK_START_CHEATSHEET.md
require_contains 'sudo apt-get install -y rustc cargo make gcc pkg-config' docs/QUICK_START_CHEATSHEET.md
require_contains 'Ubuntu:' installer/README.md

require_contains 'Status: local-only packaging draft' packaging/ubuntu/README.md

printf 'ubuntu_developer_workflow: ok\n'
