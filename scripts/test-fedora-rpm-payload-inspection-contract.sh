#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpm payload inspection contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
status='docs/status/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-rpm-payload-inspection-contract.sh'
workflow='.github/workflows/fedora-rpm-payload-inspection-contract.yml'
artifact_doc='docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md'
artifact_status='docs/status/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT_STATUS.md'
environment_doc='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
gate_doc='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
handoff_doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$packaging_readme" \
  "$test_script" \
  "$workflow" \
  "$artifact_doc" \
  "$artifact_status" \
  "$environment_doc" \
  "$gate_doc" \
  "$handoff_doc" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: no-effect RPM payload inspection contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$doc"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$doc"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$doc"
require_contains 'rpm_payload_inspection_contract_present=1' "$doc"
require_contains 'payload_inspection_contract_present=1' "$doc"
require_contains 'fedora_rpm_payload_inspection_contract_state=specified-no-effect' "$doc"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_rpm_artifact_naming_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'rpm_artifact_created=0' "$doc"
require_contains 'rpm_payload_inspection_run=0' "$doc"
require_contains 'source_rpm_payload_inspection_run=0' "$doc"
require_contains 'binary_rpm_payload_inspection_run=0' "$doc"
require_contains 'rpm_payload_accepted=0' "$doc"
require_contains 'rpm_artifact_sha256_recorded=0' "$doc"
require_contains 'rpm_payload_listing_sha256_recorded=0' "$doc"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$doc"
require_contains 'fedora_rpm_payload_inspection_contract: ok' "$doc"

for current_field in \
  'fedora_rpm_payload_inspection_contract_present=1' \
  'fedora_rpm_artifact_naming_contract_present=1' \
  'fedora_local_mock_build_environment_contract_present=1' \
  'rpm_payload_inspection_contract_present=1' \
  'payload_inspection_contract_present=1' \
  'fedora_rpm_payload_inspection_contract_state=specified-no-effect' \
  'payload_inspection_contract_state=specified-no-effect' \
  'fedora_rpm_artifact_naming_contract_state=specified-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'rpm_artifact_created=0' \
  'rpm_payload_inspection_run=0' \
  'source_rpm_payload_inspection_run=0' \
  'binary_rpm_payload_inspection_run=0' \
  'rpm_payload_accepted=0' \
  'rpm_artifact_sha256_recorded=0' \
  'rpm_payload_listing_sha256_recorded=0' \
  'source_rpm_payload_listing_sha256_recorded=0' \
  'binary_rpm_payload_listing_sha256_recorded=0' \
  'fedora_mock_build_evidence_present=0' \
  'rpm_installed_on_host=0' \
  'rpm_removed_from_host=0' \
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

for payload_field in \
  'rpm_payload_cli_path_required=1' \
  'rpm_payload_doc_readme_required=1' \
  'rpm_payload_service_files_allowed=0' \
  'rpm_payload_systemd_units_allowed=0' \
  'rpm_payload_init_files_allowed=0' \
  'rpm_payload_kernel_files_allowed=0' \
  'rpm_payload_privileged_helper_allowed=0' \
  'rpm_payload_network_authority_allowed=0' \
  'rpm_payload_host_mutation_hooks_allowed=0' \
  'rpm_payload_scriptlets_allowed=0' \
  'source_rpm_expected_spec=packaging/fedora/latticra.spec' \
  'source_rpm_expected_source_archive=latticra-0.0.0.tar.gz' \
  'source_rpm_payload_listing_required=1' \
  'source_rpm_metadata_inspection_required=1' \
  'source_rpm_unexpected_archive_count=0' \
  'source_rpm_unexpected_patch_count=0' \
  'rpm_payload_expected_bin=/usr/bin/latticra' \
  'rpm_payload_expected_doc=/usr/share/doc/latticra/README.md' \
  'rpm_payload_listing_required=1' \
  'rpm_metadata_inspection_required=1' \
  'rpm_scriptlet_absence_required=1' \
  'rpm_systemd_unit_absence_required=1' \
  'rpm_init_script_absence_required=1' \
  'rpm_privileged_helper_absence_required=1' \
  'rpm_kernel_file_absence_required=1' \
  'rpm_network_authority_absence_required=1' \
  'rpm_host_mutation_hook_absence_required=1' \
  'rpm_payload_unexpected_file_count=0'
do
  require_contains "$payload_field" "$doc"
done

for transcript_field in \
  'rpm_artifact_name' \
  'payload_listing_sha256' \
  'expected_payload_paths_present' \
  'unexpected_payload_paths_absent' \
  'service_files_absent' \
  'systemd_units_absent' \
  'scriptlets_absent' \
  'kernel_files_absent' \
  'privileged_helpers_absent' \
  'network_authority_absent' \
  'host_mutation_hooks_absent' \
  'fedora_target_distribution' \
  'fedora_dist_tag' \
  'rpm_arch' \
  'environment_identifier' \
  'operator_authorization_reference'
do
  require_contains "$transcript_field" "$doc"
done

require_contains 'Status: rpm-payload-inspection/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not create RPM artifacts' "$status"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$status"

require_contains 'FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora RPM payload inspection contract checkpoint' "$index"
require_contains 'The Fedora RPM payload inspection contract is present but inspects no RPM artifacts' "$index"

require_contains 'docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora RPM payload inspection contract is present' "$readme"

require_contains 'docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-rpm-payload-inspection-contract.sh' "$packaging_readme"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$packaging_readme"
require_contains 'fedora_rpm_payload_inspection_contract_state=specified-no-effect' "$packaging_readme"

require_contains 'docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md' "$artifact_doc"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$artifact_status"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$environment_doc"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$gate_doc"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$handoff_doc"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$rpmlint_classification"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$matrix_script"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$matrix_status"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$matrix_test"

require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' "$spec"
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' "$spec"
require_contains '%{_bindir}/latticra' "$spec"
require_contains '%doc %{_docdir}/%{name}/README.md' "$spec"

require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora RPM Payload Inspection Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpm-payload-inspection-contract.sh' "$workflow"
require_absent 'rpm -qlp' "$workflow"
require_absent 'rpm2cpio' "$workflow"
require_absent 'cpio' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"
require_absent 'dnf ' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpm-payload-inspection-contract.sh' 'Makefile'
require_contains 'fedora-rpm-payload-inspection-contract:' 'Makefile'

printf 'fedora_rpm_payload_inspection_contract: ok\n'
