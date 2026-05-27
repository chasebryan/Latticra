#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse rpmlint findings classification: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse rpmlint findings classification: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
require_file docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
require_file docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
require_file docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
require_file docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_file docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file scripts/test-opensuse-rpmlint-static-spec-lane.sh
require_file scripts/test-opensuse-local-rpm-build-gate-contract.sh
require_file scripts/test-opensuse-local-rpm-build-environment-contract.sh
require_file scripts/test-opensuse-rpm-artifact-naming-contract.sh
require_file scripts/test-opensuse-rpm-payload-inspection-contract.sh
require_file scripts/test-opensuse-rpm-install-remove-transcript-contract.sh

require_contains 'Status: active findings classification record' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'Expected Draft Finding Classes' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'placeholder_version_or_release' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'placeholder_license_expression' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'missing_real_source_archive' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'Unexpected Finding Classes' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'service_installation' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'network_fetch_during_build' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'opensuse_official_status_claim' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'obs_publication_claim' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'opensuse_rpmlint_findings_classification_present=1' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'classification_decision=blocked-pending-reviewed-rpmlint-output' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'accepted_rpmlint_transcript_present=1' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'unexpected_findings_count=0' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'does not' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'scripts/test-opensuse-rpm-install-remove-transcript-contract.sh' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'Add openSUSE RPM validation promotion blocker matrix' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'opensuse_rpmlint_findings_classification: ok' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md

require_contains 'docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'opensuse_source_archive_reproducibility_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpmlint_findings_classification_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpmlint_findings_classification_present=1' packaging/opensuse/README.md
require_contains 'opensuse_source_archive_reproducibility_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' packaging/opensuse/README.md
require_contains 'docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md' README.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' README.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' README.md

require_contains 'LOCAL-ONLY openSUSE DRAFT' packaging/opensuse/latticra.spec
require_contains 'License:        AGPL-3.0-or-later AND CC-BY-4.0' packaging/opensuse/latticra.spec
require_contains 'Open Build Service publication' packaging/opensuse/latticra.changes

printf 'opensuse_rpmlint_findings_classification: ok\n'
