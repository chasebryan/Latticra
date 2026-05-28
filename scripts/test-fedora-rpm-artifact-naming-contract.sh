#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpm artifact naming contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md'
status='docs/status/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-rpm-artifact-naming-contract.sh'
workflow='.github/workflows/fedora-rpm-artifact-naming-contract.yml'
environment_doc='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
environment_status='docs/status/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT_STATUS.md'
gate_doc='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
handoff_doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
payload_contract='docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
spec='packaging/fedora/latticra.spec'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$packaging_readme" \
  "$test_script" \
  "$workflow" \
  "$environment_doc" \
  "$environment_status" \
  "$gate_doc" \
  "$handoff_doc" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$payload_contract" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: no-effect RPM artifact naming contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$doc"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$doc"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$doc"
require_contains 'rpm_artifact_naming_contract_present=1' "$doc"
require_contains 'fedora_rpm_artifact_naming_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_mock_build_environment_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'rpm_artifact_output_directory_required_under_disposable_environment=1' "$doc"
require_contains 'rpm_artifact_output_directory_created=0' "$doc"
require_contains 'repository_rpm_artifact_write_allowed=0' "$doc"
require_contains 'root_workspace_rpm_artifact_write_allowed=0' "$doc"
require_contains 'publication_directory_write_allowed=0' "$doc"
require_contains 'rpm_source_artifact_name_pattern_recorded=1' "$doc"
require_contains 'rpm_binary_artifact_name_pattern_recorded=1' "$doc"
require_contains 'rpm_dist_tag_token_required=1' "$doc"
require_contains 'rpm_binary_arch_token_required=1' "$doc"
require_contains 'rpm_artifact_created=0' "$doc"
require_contains 'source_rpm_artifact_created=0' "$doc"
require_contains 'binary_rpm_artifact_created=0' "$doc"
require_contains 'rpm_artifact_sha256_recorded=0' "$doc"
require_contains 'rpm_artifact_published=0' "$doc"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$doc"
require_contains 'fedora_rpm_artifact_naming_contract: ok' "$doc"

for current_field in \
  'fedora_rpm_artifact_naming_contract_present=1' \
  'fedora_local_mock_build_environment_contract_present=1' \
  'fedora_local_mock_build_gate_contract_present=1' \
  'rpm_artifact_naming_contract_present=1' \
  'fedora_rpm_artifact_naming_contract_state=specified-no-effect' \
  'fedora_mock_build_environment_contract_state=specified-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'rpm_artifact_output_directory_required_under_disposable_environment=1' \
  'rpm_artifact_output_directory_created=0' \
  'repository_rpm_artifact_write_allowed=0' \
  'root_workspace_rpm_artifact_write_allowed=0' \
  'publication_directory_write_allowed=0' \
  'rpm_source_artifact_name_pattern_recorded=1' \
  'rpm_binary_artifact_name_pattern_recorded=1' \
  'rpm_dist_tag_token_required=1' \
  'rpm_binary_arch_token_required=1' \
  'rpm_artifact_created=0' \
  'source_rpm_artifact_created=0' \
  'binary_rpm_artifact_created=0' \
  'rpm_artifact_sha256_recorded=0' \
  'rpm_artifact_published=0' \
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

for naming_field in \
  'rpm_source_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.src.rpm' \
  'rpm_source_archive_name=latticra-0.0.0.tar.gz' \
  'rpm_spec_name=latticra.spec' \
  'rpm_name_value=latticra' \
  'rpm_version_value=0.0.0' \
  'rpm_release_template=0.1.local%{?dist}' \
  'rpm_binary_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.${RPM_ARCH}.rpm' \
  'rpm_source_artifact_output_directory=fedora-rpm-input/SRPMS/' \
  'rpm_binary_artifact_output_directory_pattern=fedora-rpm-input/RPMS/${RPM_ARCH}/' \
  'mock_result_artifact_output_directory=mock-result/' \
  'artifact_retention_policy_required=1' \
  'artifact_cleanup_policy_required=1'
do
  require_contains "$naming_field" "$doc"
done

for transcript_field in \
  'source_archive_sha256' \
  'rpm_input_archive_sha256' \
  'rpm_artifact_sha256' \
  'artifact_size_bytes' \
  'artifact_generation_command' \
  'fedora_target_distribution' \
  'fedora_dist_tag' \
  'rpm_arch' \
  'environment_identifier' \
  'operator_authorization_reference'
do
  require_contains "$transcript_field" "$doc"
done

require_contains 'Status: rpm-artifact-naming/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not create RPM artifacts' "$status"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$status"

require_contains 'FEDORA_RPM_ARTIFACT_NAMING_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora RPM artifact naming contract checkpoint' "$index"
require_contains 'The Fedora RPM artifact naming contract is present but creates no RPM artifacts' "$index"

require_contains 'docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora RPM artifact naming contract is present' "$readme"

require_contains 'docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-rpm-artifact-naming-contract.sh' "$packaging_readme"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$packaging_readme"
require_contains 'fedora_rpm_artifact_naming_contract_state=specified-no-effect' "$packaging_readme"

require_contains 'docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md' "$environment_doc"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$environment_status"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$gate_doc"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$handoff_doc"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$rpmlint_classification"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$matrix_script"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$matrix_status"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$matrix_test"
require_contains 'docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md' "$doc"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$payload_contract"

require_contains 'Name:           latticra' "$spec"
require_contains 'Version:        0.0.0' "$spec"
require_contains 'Release:        0.1.local%{?dist}' "$spec"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"
require_contains '%autosetup -n %{name}-%{version}' "$spec"

require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora RPM Artifact Naming Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpm-artifact-naming-contract.sh' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"
require_absent 'dnf ' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpm-artifact-naming-contract.sh' 'Makefile'
require_contains 'fedora-rpm-artifact-naming-contract:' 'Makefile'

printf 'fedora_rpm_artifact_naming_contract: ok\n'
