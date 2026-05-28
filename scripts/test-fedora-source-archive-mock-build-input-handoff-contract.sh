#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora source archive mock build input handoff contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
status='docs/status/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
test_script='scripts/test-fedora-source-archive-mock-build-input-handoff-contract.sh'
accepted_evidence_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md'
accepted_evidence_gate_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE_STATUS.md'
accepted_evidence_gate_script='scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh'
accepted_evidence_gate_test='scripts/test-fedora-source-archive-accepted-evidence-acceptance-gate.sh'
review_validator='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
template='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md'
acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md'
contract='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'
workflow='.github/workflows/fedora-source-archive-mock-build-input-handoff-contract.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$test_script" \
  "$accepted_evidence_gate" \
  "$accepted_evidence_gate_status" \
  "$accepted_evidence_gate_script" \
  "$accepted_evidence_gate_test" \
  "$review_validator" \
  "$template" \
  "$acceptance_gate" \
  "$contract" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: no-effect mock-build input handoff contract' "$doc"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$doc"
require_contains 'source_archive_mock_build_input_handoff_contract_state=closed-no-effect' "$doc"
require_contains 'mock_build_input_handoff_allowed=0' "$doc"
require_contains 'source_archive_handoff_to_rpmbuild_allowed=0' "$doc"
require_contains 'source_archive_handoff_to_mock_allowed=0' "$doc"
require_contains 'fedora_rpm_input_layout_documented=1' "$doc"
require_contains 'fedora-rpm-input/SOURCES/latticra-0.0.0.tar.gz' "$doc"
require_contains 'fedora-rpm-input/SPECS/latticra.spec' "$doc"
require_contains 'rpmbuild_allowed=0' "$doc"
require_contains 'mock_build_allowed=0' "$doc"
require_contains 'fedora_mock_build_input_opened_by_handoff_contract=0' "$doc"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$doc"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract: ok' "$doc"

for current_field in \
  'fedora_source_archive_mock_build_input_handoff_contract_present=1' \
  'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' \
  'source_archive_mock_build_input_handoff_contract_state=closed-no-effect' \
  'mock_build_input_handoff_allowed=0' \
  'source_archive_accepted_evidence_acceptance_gate_report_valid=0' \
  'source_archive_accepted_evidence_acceptance_gate_reviewed=0' \
  'source_archive_accepted_for_build_candidate_valid=0' \
  'candidate_source_archive_accepted_for_build=0' \
  'candidate_fedora_mock_build_input_opened=0' \
  'source_archive_handoff_to_rpmbuild_allowed=0' \
  'source_archive_handoff_to_mock_allowed=0' \
  'source_archive_handoff_written_by_contract=0' \
  'fedora_rpm_input_layout_documented=1' \
  'fedora_rpmbuild_sources_archive_staged=0' \
  'fedora_rpmbuild_specs_spec_staged=0' \
  'fedora_mock_build_input_opened_by_handoff_contract=0' \
  'rpmbuild_allowed=0' \
  'mock_build_allowed=0' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
  'source_rpm_artifact_created=0' \
  'binary_rpm_artifact_created=0' \
  'rpm_artifact_created=0' \
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
  'source_archive_accepted_evidence_acceptance_gate_report_valid=1' \
  'source_archive_accepted_evidence_acceptance_gate_reviewed=1' \
  'source_archive_accepted_evidence_status_written=1' \
  'source_archive_accepted_evidence_present=1' \
  'source_archive_accepted=1' \
  'source_archive_accepted_for_build=1' \
  'fedora_mock_build_input_opened=1' \
  'source_archive_sha256_recorded=1' \
  'source_archive_reproducible=1' \
  'source_archive_path_safety_checked=1' \
  'source_archive_symlink_policy_checked=1' \
  'accepted_rpmlint_transcript_present=1' \
  'license_expression_reviewed=1' \
  'package_notice_obligations_reviewed=1' \
  'disposable_validation_environment=1' \
  'explicit_operator_build_authorization=1'
do
  require_contains "$future_field" "$doc"
done

require_contains 'Status: mock-build-input-handoff-contract/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not stage a source archive under `SOURCES/`' "$status"
require_contains 'does not run `rpmbuild` or `mock`' "$status"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$status"

require_contains 'FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora source archive mock build input handoff contract checkpoint' "$index"
require_contains 'The Fedora source archive mock build input handoff contract is present but keeps rpmbuild and mock input closed' "$index"

require_contains 'docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora source archive mock build input handoff contract is present' "$readme"

require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_gate"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_gate_status"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_gate_script"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate: ok' "$accepted_evidence_gate_test"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$review_validator"
require_contains 'source_archive_accepted_evidence_status_written=1' "$template"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$acceptance_gate"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$contract"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$rpmlint_classification"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$matrix_script"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$matrix_status"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$matrix_test"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"
require_contains '%autosetup -n %{name}-%{version}' "$spec"

require_contains 'name: Fedora Source Archive Mock Build Input Handoff Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-source-archive-mock-build-input-handoff-contract.sh' "$workflow"
require_absent 'rpmbuild' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-source-archive-mock-build-input-handoff-contract.sh' 'Makefile'
require_contains 'fedora-source-archive-mock-build-input-handoff-contract:' 'Makefile'

printf 'fedora_source_archive_mock_build_input_handoff_contract: ok\n'
