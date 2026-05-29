#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora local mock build environment contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    fail "unexpected RPM artifact under $dir"
  fi
}

doc='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
status='docs/status/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-local-mock-build-environment-contract.sh'
workflow='.github/workflows/fedora-local-mock-build-environment-contract.yml'
gate_doc='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
gate_status='docs/status/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT_STATUS.md'
handoff_doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
artifact_contract='docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md'
spec='packaging/fedora/latticra.spec'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$packaging_readme" \
  "$test_script" \
  "$workflow" \
  "$gate_doc" \
  "$gate_status" \
  "$handoff_doc" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$artifact_contract" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: no-effect local mock-build environment contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$doc"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$doc"
require_contains 'fedora_mock_build_environment_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'fedora_clean_build_environment_documented=1' "$doc"
require_contains 'fedora_mock_target_documented=1' "$doc"
require_contains 'fedora_target_distribution_documented=1' "$doc"
require_contains 'fedora_build_environment_provisioned=0' "$doc"
require_contains 'fedora_mock_build_environment_provisioned=0' "$doc"
require_contains 'explicit_operator_build_authorization=0' "$doc"
require_contains 'disposable_validation_environment_required=1' "$doc"
require_contains 'environment_transcript_present=0' "$doc"
require_contains 'toolchain_version_capture_required=1' "$doc"
require_contains 'rpm_input_digest_binding_required=1' "$doc"
require_contains 'mock_chroot_lifecycle_documented=1' "$doc"
require_contains 'mock_network_policy_documented=1' "$doc"
require_contains 'mock_result_directory_documented=1' "$doc"
require_contains 'source_rpm_output_path_documented=1' "$doc"
require_contains 'binary_rpm_output_path_documented=1' "$doc"
require_contains 'transcript_retention_path_documented=1' "$doc"
require_contains 'rpmbuild_command_allowed=0' "$doc"
require_contains 'mock_build_command_allowed=0' "$doc"
require_contains 'dnf_builddep_command_allowed=0' "$doc"
require_contains 'rpmbuild_run=0' "$doc"
require_contains 'mock_build_run=0' "$doc"
require_contains 'dnf_builddep_run=0' "$doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$doc"
require_contains 'fedora_local_mock_build_environment_contract: ok' "$doc"

for current_field in \
  'fedora_local_mock_build_environment_contract_present=1' \
  'fedora_local_mock_build_gate_contract_present=1' \
  'fedora_mock_build_environment_contract_state=specified-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'fedora_clean_build_environment_documented=1' \
  'fedora_mock_target_documented=1' \
  'fedora_target_distribution_documented=1' \
  'fedora_build_environment_provisioned=0' \
  'fedora_mock_build_environment_provisioned=0' \
  'explicit_operator_build_authorization=0' \
  'disposable_validation_environment_required=1' \
  'disposable_validation_environment_provisioned=0' \
  'environment_transcript_present=0' \
  'toolchain_version_capture_required=1' \
  'rpm_input_digest_binding_required=1' \
  'mock_chroot_lifecycle_documented=1' \
  'mock_network_policy_documented=1' \
  'mock_result_directory_documented=1' \
  'source_rpm_output_path_documented=1' \
  'binary_rpm_output_path_documented=1' \
  'transcript_retention_path_documented=1' \
  'rpmbuild_command_allowed=0' \
  'mock_build_command_allowed=0' \
  'dnf_builddep_command_allowed=0' \
  'rpmbuild_allowed=0' \
  'mock_build_allowed=0' \
  'dnf_builddep_allowed=0' \
  'rpmbuild_run=0' \
  'rpmbuild_bs_run=0' \
  'rpmbuild_ba_run=0' \
  'rpmbuild_bb_run=0' \
  'mock_build_run=0' \
  'mock_buildsrpm_run=0' \
  'dnf_builddep_run=0' \
  'source_rpm_artifact_created=0' \
  'binary_rpm_artifact_created=0' \
  'rpm_artifact_created=0' \
  'fedora_mock_build_evidence_present=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
  'production_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
  require_contains "$current_field" "$matrix"
done

for required_field in \
  'fedora_container_or_vm_required=1' \
  'fedora_target_distribution_record_required=1' \
  'fedora_architecture_record_required=1' \
  'fedora_repository_state_record_required=1' \
  'fedora_build_dependency_resolution_transcript_required=1' \
  'rpmbuild_toolchain_versions_required=1' \
  'mock_toolchain_versions_required=1' \
  'source_archive_digest_required=1' \
  'rpm_input_path_required=1' \
  'mock_target_record_required=1' \
  'mock_config_scope_record_required=1' \
  'mock_chroot_policy_required=1' \
  'mock_network_policy_required=1' \
  'mock_result_directory_required=1'
do
  require_contains "$required_field" "$doc"
done

for transcript_field in \
  'environment_identifier' \
  'fedora_target_distribution' \
  'toolchain_versions' \
  'rpmbuild_version' \
  'mock_version' \
  'source_archive_sha256' \
  'mock_target' \
  'mock_config_scope' \
  'mock_result_directory' \
  'operator_authorization_reference'
do
  require_contains "$transcript_field" "$doc"
done

require_contains 'Status: local-mock-build-environment/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not run `rpmbuild`, `mock`, or `dnf builddep`' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$status"

require_contains 'FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora local mock-build environment contract checkpoint' "$index"
require_contains 'The Fedora local mock-build environment contract is present but does not provision Fedora build environments' "$index"

require_contains 'docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora local mock-build environment contract is present' "$readme"

require_contains 'docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-local-mock-build-environment-contract.sh' "$packaging_readme"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$packaging_readme"
require_contains 'fedora_mock_build_environment_contract_state=specified-no-effect' "$packaging_readme"

require_contains 'docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md' "$gate_doc"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$gate_status"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$handoff_doc"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$rpmlint_classification"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$matrix_script"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$matrix_status"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$matrix_test"
require_contains 'docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md' "$doc"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$artifact_contract"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"
require_contains '%autosetup -n %{name}-%{version}' "$spec"

require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora Local Mock Build Environment Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-local-mock-build-environment-contract.sh' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"
require_absent 'dnf ' "$workflow"

require_contains 'sh ./scripts/test-fedora-local-mock-build-environment-contract.sh' 'Makefile'
require_contains 'fedora-local-mock-build-environment-contract:' 'Makefile'

printf 'fedora_local_mock_build_environment_contract: ok\n'
