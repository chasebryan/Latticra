#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora local mock build gate contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
status='docs/status/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-local-mock-build-gate-contract.sh'
workflow='.github/workflows/fedora-local-mock-build-gate-contract.yml'
handoff_doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
handoff_status='docs/status/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT_STATUS.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
environment_contract='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
spec='packaging/fedora/latticra.spec'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$packaging_readme" \
  "$test_script" \
  "$workflow" \
  "$handoff_doc" \
  "$handoff_status" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$environment_contract" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: no-effect local mock-build gate contract' "$doc"
require_contains 'documentation-only' "$doc"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$doc"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_open=0' "$doc"
require_contains 'fedora_mock_build_gate_opened_by_contract=0' "$doc"
require_contains 'rpmbuild_bs_allowed=0' "$doc"
require_contains 'rpmbuild_ba_allowed=0' "$doc"
require_contains 'rpmbuild_bb_allowed=0' "$doc"
require_contains 'mock_buildsrpm_allowed=0' "$doc"
require_contains 'dnf_builddep_allowed=0' "$doc"
require_contains 'fedora_mock_config_written=0' "$doc"
require_contains 'fedora_mock_chroot_initialized=0' "$doc"
require_contains 'fedora_mock_chroot_mutated=0' "$doc"
require_contains 'mock --buildsrpm' "$doc"
require_contains 'mock -r' "$doc"
require_contains 'dnf builddep' "$doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$doc"
require_contains 'fedora_local_mock_build_gate_contract: ok' "$doc"

for current_field in \
  'fedora_local_mock_build_gate_contract_present=1' \
  'fedora_source_archive_mock_build_input_handoff_contract_present=1' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'fedora_mock_build_gate_open=0' \
  'fedora_mock_build_gate_opened_by_contract=0' \
  'mock_build_input_handoff_allowed=0' \
  'source_archive_handoff_to_rpmbuild_allowed=0' \
  'source_archive_handoff_to_mock_allowed=0' \
  'fedora_rpmbuild_sources_archive_staged=0' \
  'fedora_rpmbuild_specs_spec_staged=0' \
  'fedora_mock_config_written=0' \
  'fedora_mock_chroot_initialized=0' \
  'fedora_mock_chroot_mutated=0' \
  'rpmbuild_allowed=0' \
  'rpmbuild_bs_allowed=0' \
  'rpmbuild_ba_allowed=0' \
  'rpmbuild_bb_allowed=0' \
  'mock_build_allowed=0' \
  'mock_buildsrpm_allowed=0' \
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

for future_field in \
  'source_archive_handoff_to_rpmbuild_allowed=1' \
  'source_archive_handoff_to_mock_allowed=1' \
  'source_archive_accepted_for_build=1' \
  'source_archive_sha256_recorded=1' \
  'source_archive_reproducible=1' \
  'fedora_rpmbuild_sources_archive_staged=1' \
  'fedora_rpmbuild_specs_spec_staged=1' \
  'accepted_rpmlint_transcript_present=1' \
  'unexpected_findings_count=0' \
  'license_expression_reviewed=1' \
  'package_notice_obligations_reviewed=1' \
  'buildrequires_reviewed=1' \
  'fedora_clean_build_environment_documented=1' \
  'fedora_mock_target_documented=1' \
  'rpmbuild_toolchain_versions_recorded=1' \
  'mock_toolchain_versions_recorded=1' \
  'disposable_validation_environment=1' \
  'explicit_operator_build_authorization=1'
do
  require_contains "$future_field" "$doc"
done

require_contains 'Status: local-mock-build-gate/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not run `rpmbuild` or `mock`' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$status"

require_contains 'FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora local mock-build gate contract checkpoint' "$index"
require_contains 'The Fedora local mock-build gate contract is present but keeps rpmbuild, mock, and dnf builddep closed' "$index"

require_contains 'docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora local mock-build gate contract is present' "$readme"

require_contains 'docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-local-mock-build-gate-contract.sh' "$packaging_readme"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$packaging_readme"

require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$handoff_doc"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$handoff_status"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$rpmlint_classification"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$matrix_script"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$matrix_status"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$matrix_test"
require_contains 'docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md' "$doc"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$environment_contract"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"
require_contains '%autosetup -n %{name}-%{version}' "$spec"

require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora Local Mock Build Gate Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-local-mock-build-gate-contract.sh' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"
require_absent 'dnf ' "$workflow"

require_contains 'sh ./scripts/test-fedora-local-mock-build-gate-contract.sh' 'Makefile'
require_contains 'fedora-local-mock-build-gate-contract:' 'Makefile'

printf 'fedora_local_mock_build_gate_contract: ok\n'
