#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse developer workflow: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse developer workflow: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_file docs/OPENSUSE_READINESS_PLAN.md
require_file docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_file docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_file docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file README.md
require_file installer/README.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file scripts/test-opensuse-rpmlint-osc-availability.sh
require_file scripts/test-opensuse-rpmlint-static-spec-lane.sh
require_file scripts/test-opensuse-rpmlint-findings-classification.sh
require_file scripts/test-opensuse-source-archive-reproducibility-contract.sh
require_file scripts/test-opensuse-source-archive-fixture-lane.sh
require_file scripts/test-opensuse-rpm-topdir-handoff-lane.sh
require_file .github/workflows/opensuse-developer-workflow.yml
require_file .github/workflows/opensuse-rpmlint-osc-availability.yml
require_file .github/workflows/opensuse-rpmlint-static-spec-lane.yml
require_file .github/workflows/opensuse-rpmlint-findings-classification.yml
require_file .github/workflows/opensuse-source-archive-reproducibility-contract.yml
require_file .github/workflows/opensuse-source-archive-fixture-lane.yml
require_file .github/workflows/opensuse-rpm-topdir-handoff-lane.yml

require_contains 'Status: developer workflow record' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'local openSUSE Linux commands for productive Latticra development' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'same guards as the Fedora and Ubuntu tracks' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'sudo zypper refresh' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'sudo zypper install -y git gcc make coreutils findutils diffutils grep pkgconf' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'sudo zypper install -y rust cargo make gcc pkgconf' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'sh scripts/test-opensuse-local-rpm-static-validation.sh' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'opensuse_developer_workflow: ok' docs/OPENSUSE_DEVELOPER_WORKFLOW.md

require_contains 'Status: planning and maintenance record' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'same purpose as the Fedora and Ubuntu tracks' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'openSUSE integration and maintenance' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_developer_workflow_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_panel_prerequisites_documented=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_local_rpm_draft_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_local_rpm_static_validation_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_changes_file_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_rpmlint_osc_availability_lane_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_rpmlint_static_spec_lane_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_rpmlint_findings_classification_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_source_archive_reproducibility_contract_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_obs_publication_claimed=0' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'opensuse_official_package_claimed=0' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'suse_endorsement_claimed=0' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'Status: active tool availability lane' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'rpmlint installs' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'osc installs' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'Status: active static spec lint lane' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'rpmlint can inspect packaging/opensuse/latticra.spec' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'Status: active findings classification record' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'Expected Draft Finding Classes' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'Status: active source archive reproducibility contract' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_name=latticra-0.0.0.tar.gz' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'Status: active fixture lane' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'source_archive_repeated_sha256_match=1' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'Status: active temporary RPM topdir handoff lane' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'temporary_rpm_sources_archive_staged=1' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md

require_contains 'openSUSE prerequisites' README.md
require_contains '## openSUSE integration and maintenance' README.md
require_contains 'docs/OPENSUSE_DEVELOPER_WORKFLOW.md' README.md
require_contains 'docs/OPENSUSE_READINESS_PLAN.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md' README.md
require_contains 'docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md' README.md
require_contains 'docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md' README.md
require_contains 'docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md' README.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' README.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' README.md
require_contains 'packaging/opensuse/README.md' README.md
require_contains 'sh scripts/test-opensuse-developer-workflow.sh' README.md
require_contains 'sh scripts/test-opensuse-local-rpm-static-validation.sh' README.md
require_contains 'sh scripts/test-opensuse-rpmlint-osc-availability.sh' README.md
require_contains 'sh scripts/test-opensuse-rpmlint-static-spec-lane.sh' README.md
require_contains 'sh scripts/test-opensuse-rpmlint-findings-classification.sh' README.md
require_contains 'sh scripts/test-opensuse-source-archive-reproducibility-contract.sh' README.md
require_contains 'sh scripts/test-opensuse-source-archive-fixture-lane.sh' README.md
require_contains 'sh scripts/test-opensuse-rpm-topdir-handoff-lane.sh' README.md

require_contains 'openSUSE prerequisites:' docs/QUICK_START_CHEATSHEET.md
require_contains 'sudo zypper install -y rust cargo make gcc pkgconf' docs/QUICK_START_CHEATSHEET.md
require_contains 'openSUSE:' installer/README.md

require_contains 'Status: local-only packaging draft' packaging/opensuse/README.md
require_contains 'not an official openSUSE package' packaging/opensuse/README.md
require_contains 'not Open Build Service publication evidence' packaging/opensuse/README.md

printf 'opensuse_developer_workflow: ok\n'
