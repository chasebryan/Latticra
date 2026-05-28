#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpm install/remove transcript contract: %s\n' "$1" >&2
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

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    fail "unexpected file exists: $file"
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    fail "unexpected RPM artifact under $dir"
  fi
}

doc='docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
status='docs/status/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT_STATUS.md'
index='docs/status/README.md'
docs_readme='docs/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-rpm-install-remove-transcript-contract.sh'
workflow='.github/workflows/fedora-rpm-install-remove-transcript-contract.yml'
payload_doc='docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
payload_status='docs/status/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT_STATUS.md'
artifact_doc='docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md'
environment_doc='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
gate_doc='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
handoff_doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
package_review_doc='docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md'
spec='packaging/fedora/latticra.spec'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$docs_readme" \
  "$readme" \
  "$packaging_readme" \
  "$test_script" \
  "$workflow" \
  "$payload_doc" \
  "$payload_status" \
  "$artifact_doc" \
  "$environment_doc" \
  "$gate_doc" \
  "$handoff_doc" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$package_review_doc" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: no-effect RPM install/remove transcript contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$doc"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$doc"
require_contains 'rpm_install_remove_transcript_contract_present=1' "$doc"
require_contains 'install_remove_transcript_contract_present=1' "$doc"
require_contains 'fedora_rpm_install_remove_transcript_contract_state=specified-no-effect' "$doc"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_rpm_payload_inspection_contract_state=specified-no-effect' "$doc"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'rpm_install_remove_disposable_environment_required=1' "$doc"
require_contains 'rpm_install_remove_transcript_present=0' "$doc"
require_contains 'rpm_package_install_run=0' "$doc"
require_contains 'rpm_package_remove_run=0' "$doc"
require_contains 'rpm_dnf_install_run=0' "$doc"
require_contains 'rpm_dnf_remove_run=0' "$doc"
require_contains 'rpm_cli_install_run=0' "$doc"
require_contains 'rpm_cli_remove_run=0' "$doc"
require_contains 'rpm_installed_on_host=0' "$doc"
require_contains 'rpm_removed_from_host=0' "$doc"
require_contains 'host_install_allowed=0' "$doc"
require_contains 'host_remove_allowed=0' "$doc"
require_contains 'host_mutation_allowed=0' "$doc"
require_contains 'service_state_change_allowed=0' "$doc"
require_contains 'rpm_artifact_created=0' "$doc"
require_contains 'rpm_payload_accepted=0' "$doc"
require_contains 'rpm_validation_result_promoted=0' "$doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$doc"
require_contains 'fedora_rpm_install_remove_transcript_contract: ok' "$doc"

for current_field in \
  'fedora_rpm_install_remove_transcript_contract_present=1' \
  'fedora_rpm_payload_inspection_contract_present=1' \
  'rpm_install_remove_transcript_contract_present=1' \
  'install_remove_transcript_contract_present=1' \
  'fedora_rpm_install_remove_transcript_contract_state=specified-no-effect' \
  'install_remove_transcript_contract_state=specified-no-effect' \
  'fedora_rpm_payload_inspection_contract_state=specified-no-effect' \
  'payload_inspection_contract_state=specified-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'rpm_install_remove_disposable_environment_required=1' \
  'rpm_install_remove_transcript_present=0' \
  'rpm_package_install_run=0' \
  'rpm_package_remove_run=0' \
  'rpm_dnf_install_run=0' \
  'rpm_dnf_remove_run=0' \
  'rpm_cli_install_run=0' \
  'rpm_cli_remove_run=0' \
  'rpm_installed_on_host=0' \
  'rpm_removed_from_host=0' \
  'host_install_allowed=0' \
  'host_remove_allowed=0' \
  'host_mutation_allowed=0' \
  'service_state_change_allowed=0' \
  'rpm_artifact_created=0' \
  'rpm_payload_accepted=0' \
  'rpm_validation_result_promoted=0' \
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

for evidence_field in \
  'rpm_install_remove_transcript_required=1' \
  'rpm_payload_post_install_check_required=1' \
  'rpm_payload_post_remove_absence_check_required=1' \
  'rpm_service_state_change_allowed=0' \
  'rpm_systemd_unit_enable_allowed=0' \
  'rpm_scriptlet_effect_allowed=0' \
  'rpm_kernel_file_allowed=0' \
  'rpm_network_authority_allowed=0' \
  'rpm_privileged_helper_allowed=0' \
  'rpm_binary_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.${RPM_ARCH}.rpm' \
  'rpm_binary_artifact_sha256' \
  'rpm_payload_expected_bin=/usr/bin/latticra' \
  'rpm_payload_expected_doc=/usr/share/doc/latticra/README.md' \
  'fedora_target_distribution' \
  'fedora_dist_tag' \
  'rpm_arch' \
  'environment_identifier'
do
  require_contains "$evidence_field" "$doc"
done

for transcript_field in \
  'environment_identifier' \
  'fedora_target_distribution' \
  'operator_authorization_reference' \
  'rpm_artifact_name' \
  'rpm_artifact_sha256' \
  'pre_install_package_state' \
  'install_command' \
  'install_exit_code' \
  'post_install_payload_listing' \
  'post_install_cli_no_effect_output' \
  'rpm_query_after_install' \
  'service_state_after_install' \
  'remove_command' \
  'remove_exit_code' \
  'post_remove_absence_report' \
  'post_remove_package_state' \
  'scriptlet_effect_review' \
  'host_mutation_review'
do
  require_contains "$transcript_field" "$doc"
done

require_contains 'Status: rpm-install-remove-transcript/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not create RPM artifacts' "$status"
require_contains 'does not install packages, remove packages' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$status"
require_contains "$package_review_doc" "$status"

require_contains 'FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora RPM install/remove transcript contract checkpoint' "$index"
require_contains 'The Fedora RPM install/remove transcript contract is present but installs no RPM artifacts' "$index"

require_contains 'FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' "$docs_readme"
require_contains 'docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora RPM install/remove transcript contract is present' "$readme"

require_contains 'docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-rpm-install-remove-transcript-contract.sh' "$packaging_readme"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$packaging_readme"
require_contains 'fedora_rpm_install_remove_transcript_contract_state=specified-no-effect' "$packaging_readme"

require_contains "$doc" "$payload_doc"
require_contains "$doc" "$payload_status"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$package_review_doc"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$matrix_script"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$matrix_status"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$matrix_test"

require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' "$spec"
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' "$spec"
require_contains '%{_bindir}/latticra' "$spec"
require_contains '%doc %{_docdir}/%{name}/README.md' "$spec"

require_absent_file packaging/fedora/latticra.service
require_absent_file packaging/fedora/latticra.init
require_absent_file packaging/fedora/latticra.tmpfiles
require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora RPM Install Remove Transcript Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpm-install-remove-transcript-contract.sh' "$workflow"
require_absent 'dnf install' "$workflow"
require_absent 'dnf remove' "$workflow"
require_absent 'rpm -i' "$workflow"
require_absent 'rpm -U' "$workflow"
require_absent 'rpm -e' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpm-install-remove-transcript-contract.sh' 'Makefile'
require_contains 'fedora-rpm-install-remove-transcript-contract:' 'Makefile'

printf 'fedora_rpm_install_remove_transcript_contract: ok\n'
