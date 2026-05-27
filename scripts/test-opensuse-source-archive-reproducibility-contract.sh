#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse source archive reproducibility contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse source archive reproducibility contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
require_file docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
require_file docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
require_file docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file README.md

require_contains 'Status: active source archive reproducibility contract' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'Source0:        %{name}-%{version}.tar.gz' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains '%autosetup -n %{name}-%{version}' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_name=latticra-0.0.0.tar.gz' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_root=latticra-0.0.0/' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_generated_twice' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_repeated_sha256_match' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_excludes_git_dir' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_excludes_nested_archives' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_symlink_policy_checked' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_source_archive_reproducibility_contract_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_created=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_reproducible=1' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_accepted_for_build=0' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'scripts/test-opensuse-rpm-install-remove-transcript-contract.sh' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'Add openSUSE RPM build-evidence intake denial contract' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_source_archive_reproducibility_contract: ok' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md

require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'opensuse_source_archive_reproducibility_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_source_archive_reproducibility_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' packaging/opensuse/README.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' README.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' README.md

require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/opensuse/latticra.spec
require_contains '%autosetup -n %{name}-%{version}' packaging/opensuse/latticra.spec

printf 'opensuse_source_archive_reproducibility_contract: ok\n'
