#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpmlint findings classification: %s\n' "$1" >&2
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

doc='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
status='docs/status/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION_STATUS.md'
index='docs/status/README.md'
readme='README.md'
static_lane='docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md'
availability='docs/FEDORA_RPMLINT_AVAILABILITY.md'
static_validation='docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md'
source_archive='docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md'
source_archive_contract='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'
workflow='.github/workflows/fedora-rpmlint-findings-classification.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$static_lane" \
  "$availability" \
  "$static_validation" \
  "$source_archive" \
  "$source_archive_contract" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec" \
  "$workflow"
do
  require_file "$file"
done

sh -n scripts/test-fedora-rpmlint-findings-classification.sh

require_contains 'Status: active findings classification record' "$doc"
require_contains 'Expected Draft Finding Classes' "$doc"
require_contains 'placeholder_version_or_release' "$doc"
require_contains 'local_only_release_marker' "$doc"
require_contains 'license_expression_review_pending' "$doc"
require_contains 'missing_real_source_archive' "$doc"
require_contains 'Unexpected Finding Classes' "$doc"
require_contains 'service_installation' "$doc"
require_contains 'network_fetch_during_build' "$doc"
require_contains 'fedora_official_status_claim' "$doc"
require_contains 'fedora_distribution_claim' "$doc"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$doc"
require_contains 'fedora_rpmlint_static_spec_lane_present=1' "$doc"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$doc"
require_contains 'accepted_rpmlint_transcript_present=0' "$doc"
require_contains 'classification_decision=blocked-pending-reviewed-rpmlint-output' "$doc"
require_contains 'fedora_rpmlint_evidence_present=0' "$doc"
require_contains 'mock_build_run=0' "$doc"
require_contains 'fedora_package_review_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'Add a Fedora source archive transcript review validator' "$doc"
require_contains 'fedora_rpmlint_findings_classification: ok' "$doc"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$source_archive_contract"

for current_field in \
  'fedora_rpmlint_findings_classification_present=1' \
  'fedora_rpmlint_static_spec_lane_present=1' \
  'fedora_source_archive_reproducibility_contract_present=1' \
  'expected_draft_finding_classes_recorded=1' \
  'unexpected_finding_classes_recorded=1' \
  'accepted_rpmlint_transcript_present=0' \
  'expected_draft_findings_count_recorded=0' \
  'unexpected_findings_count_recorded=0' \
  'classification_decision=blocked-pending-reviewed-rpmlint-output' \
  'fedora_rpmlint_evidence_present=0' \
  'package_artifact_created=0' \
  'rpm_build_run=0' \
  'mock_build_run=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
  'production_installer_ready=0'
do
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
  require_contains "$current_field" "$matrix"
done

require_contains 'docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md' "$static_lane"
require_contains 'docs/status/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION_STATUS.md' "$readme"
require_contains 'The Fedora rpmlint findings classification record is present' "$readme"
require_contains 'Current Fedora rpmlint findings classification checkpoint' "$index"
require_contains 'The Fedora rpmlint findings classification record is present but does not accept rpmlint evidence' "$index"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$matrix_script"
require_contains 'fedora_rpmlint_evidence_present=0' "$matrix_script"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$matrix_status"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$matrix_test"
require_contains 'LOCAL-ONLY DRAFT' "$spec"
require_contains 'License:        AGPL-3.0-or-later AND CC-BY-4.0' "$spec"

require_contains 'name: Fedora rpmlint Findings Classification' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpmlint-findings-classification.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpmlint-findings-classification.sh' 'Makefile'
require_contains 'fedora-rpmlint-findings-classification:' 'Makefile'

printf 'fedora_rpmlint_findings_classification: ok\n'
