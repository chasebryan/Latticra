#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora production readiness evidence intake validator: %s\n' "$1" >&2
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

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_INTAKE_VALIDATOR.md'
status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-production-readiness-evidence-intake.sh'
test_script='scripts/test-fedora-production-readiness-evidence-intake-validator.sh'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
promotion_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE.md'
promotion_gate_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE_STATUS.md'
workflow='.github/workflows/fedora-production-readiness-evidence-intake-validator.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$promotion_gate" \
  "$promotion_gate_status" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect production-readiness evidence intake validator' "$doc"
require_contains 'fedora_production_readiness_evidence_intake_validator_present=1' "$doc"
require_contains 'fedora_production_readiness_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'fedora_production_readiness_filled_matrix_candidate_valid=0' "$doc"
require_contains 'fedora_production_readiness_accepted_by_intake_validator=0' "$doc"
require_contains 'fedora_production_readiness_written_by_intake_validator=0' "$doc"
require_contains 'fedora_production_readiness_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'sh scripts/fedora-production-readiness-evidence-intake.sh --matrix <path>' "$doc"
require_contains 'sh scripts/test-fedora-production-readiness-evidence-intake-validator.sh' "$doc"

require_contains 'FEDORA PRODUCTION READINESS EVIDENCE INTAKE VALIDATION' "$script"
require_contains 'intake_validation_status=ok' "$script"
require_contains 'fedora_production_readiness_filled_matrix_candidate_valid=1' "$script"
require_contains 'fedora_production_readiness_placeholder_values_absent=1' "$script"
require_contains 'fedora_production_readiness_required_markers_present=1' "$script"
require_contains 'fedora_production_readiness_value_fields_validated=1' "$script"
require_contains 'candidate_fedora_production_readiness_evidence_complete=1' "$script"
require_contains 'fedora_production_readiness_accepted_by_intake_validator=0' "$script"
require_contains 'fedora_production_readiness_written_by_intake_validator=0' "$script"
require_contains 'fedora_production_readiness_promotion_allowed_by_intake_validator_alone=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_production_readiness_evidence_intake_validator_present=1' \
  'fedora_production_readiness_evidence_intake_validation_mode=no-effect-validation' \
  'fedora_production_readiness_filled_matrix_candidate_valid=0' \
  'fedora_production_readiness_required_markers_present=0' \
  'fedora_production_readiness_placeholder_values_absent=0' \
  'fedora_production_readiness_value_fields_validated=0' \
  'fedora_production_readiness_accepted_by_intake_validator=0' \
  'fedora_production_readiness_written_by_intake_validator=0' \
  'fedora_production_readiness_promotion_allowed_by_intake_validator_alone=0' \
  'fedora_production_readiness_evidence_complete=0' \
  'fedora_production_readiness_promotion_allowed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
done

for future_field in \
  'matrix_status=complete' \
  'fedora_production_readiness_evidence_matrix_present=1' \
  'fedora_production_readiness_filled_matrix_candidate_valid=1' \
  'fedora_production_readiness_required_markers_present=1' \
  'fedora_production_readiness_placeholder_values_absent=1' \
  'fedora_production_readiness_value_fields_validated=1' \
  'fedora_production_readiness_evidence_complete=1' \
  'fedora_cli_payload_repeatability_prerequisite_complete=1' \
  'fedora_packaging_metadata_static_lane_present=1' \
  'fedora_local_rpm_static_validation_present=1' \
  'fedora_mock_build_evidence_present=1' \
  'fedora_rpmlint_evidence_present=1' \
  'fedora_package_review_ready=1' \
  'fedora_multi_vm_validation_evidence_present=1' \
  'fedora_update_safety_evidence_present=1' \
  'fedora_recovery_safety_evidence_present=1' \
  'fedora_immutable_host_evidence_present=1' \
  'fedora_daily_driver_evidence_present=1' \
  'fedora_security_hardening_evidence_present=1' \
  'fedora_production_readiness_promotion_allowed=0' \
  'production_installer_promotion_allowed=0' \
  'fedora_distribution_promotion_allowed=0' \
  'host_mutation_performed=0'
do
  require_contains "$future_field" "$doc"
  require_contains "$future_field" "$status"
  require_contains "$future_field" "$script"
done

require_contains 'Status: validator/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'It does not accept Fedora production readiness by itself' "$status"
require_contains 'It does not write production-readiness evidence' "$status"
require_contains 'Gather externally reviewed Fedora package review, mock build, rpmlint, multi-VM, update, recovery, immutable host, daily-driver, and security hardening evidence' "$status"

require_contains 'FEDORA_PRODUCTION_READINESS_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'Current Fedora production readiness evidence intake validator checkpoint' "$index"
require_contains 'Fedora production-readiness evidence intake validator is present but does not accept, write, or promote Fedora production readiness' "$index"

require_contains 'docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_INTAKE_VALIDATOR.md' "$readme"
require_contains 'docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$readme"
require_contains 'The Fedora production-readiness evidence intake validator is present' "$readme"
require_contains 'does not accept, write, or promote Fedora production readiness' "$readme"

require_contains 'FEDORA PRODUCTION READINESS EVIDENCE MATRIX' "$matrix"
require_contains 'fedora_production_readiness_evidence_complete=0' "$matrix_status"
require_contains 'FEDORA PRODUCTION READINESS EVIDENCE MATRIX' "$matrix_script"
require_contains 'promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0' "$promotion_gate"
require_contains 'production_installer_promotion_allowed=0' "$promotion_gate_status"

require_contains 'name: Fedora Production Readiness Evidence Intake Validator' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-production-readiness-evidence-intake-validator.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-production-readiness-evidence-intake.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-production-readiness-evidence-intake-validator.sh' 'Makefile'
require_contains 'fedora-production-readiness-evidence-intake-validator:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-production-readiness-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.matrix"
placeholder="$tmp/placeholder.matrix"

cat >"$valid" <<'VALID_MATRIX'
FEDORA PRODUCTION READINESS EVIDENCE MATRIX
matrix_status=complete
fedora_production_readiness_evidence_matrix_present=1
fedora_production_readiness_filled_matrix_candidate_valid=1
fedora_production_readiness_required_markers_present=1
fedora_production_readiness_placeholder_values_absent=1
fedora_production_readiness_value_fields_validated=1
fedora_production_readiness_evidence_complete=1
fedora_production_readiness_promotion_allowed=0
fedora_cli_payload_repeatability_prerequisite_complete=1
fedora_packaging_metadata_static_lane_present=1
fedora_local_rpm_static_validation_present=1
fedora_mock_build_evidence_present=1
fedora_rpmlint_evidence_present=1
fedora_package_review_ready=1
fedora_multi_vm_validation_evidence_present=1
fedora_update_safety_evidence_present=1
fedora_recovery_safety_evidence_present=1
fedora_immutable_host_evidence_present=1
fedora_daily_driver_evidence_present=1
fedora_security_hardening_evidence_present=1
production_installer_promotion_allowed=0
fedora_distribution_promotion_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
VALID_MATRIX

cat >"$placeholder" <<'PLACEHOLDER_MATRIX'
FEDORA PRODUCTION READINESS EVIDENCE MATRIX
matrix_status=complete
fedora_production_readiness_evidence_matrix_present=1
fedora_production_readiness_filled_matrix_candidate_valid=1
fedora_production_readiness_required_markers_present=1
fedora_production_readiness_placeholder_values_absent=1
fedora_production_readiness_value_fields_validated=1
fedora_production_readiness_evidence_complete=1
fedora_production_readiness_promotion_allowed=0
fedora_cli_payload_repeatability_prerequisite_complete=1
fedora_packaging_metadata_static_lane_present=1
fedora_local_rpm_static_validation_present=1
fedora_mock_build_evidence_present=1
fedora_rpmlint_evidence_present=1
fedora_package_review_ready=1
fedora_multi_vm_validation_evidence_present=1
fedora_update_safety_evidence_present=1
fedora_recovery_safety_evidence_present=1
fedora_immutable_host_evidence_present=1
fedora_daily_driver_evidence_present=1
fedora_security_hardening_evidence_present=1
production_installer_promotion_allowed=0
fedora_distribution_promotion_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
fedora_package_review_reference=<required-after-package-review>
PLACEHOLDER_MATRIX

output=$(sh "$script" --matrix "$valid")
require_output_contains "$output" 'FEDORA PRODUCTION READINESS EVIDENCE INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'fedora_production_readiness_filled_matrix_candidate_valid=1'
require_output_contains "$output" 'fedora_production_readiness_required_markers_present=1'
require_output_contains "$output" 'fedora_production_readiness_placeholder_values_absent=1'
require_output_contains "$output" 'fedora_production_readiness_value_fields_validated=1'
require_output_contains "$output" 'candidate_fedora_production_readiness_evidence_complete=1'
require_output_contains "$output" 'candidate_fedora_package_review_ready=1'
require_output_contains "$output" 'candidate_fedora_mock_build_evidence_present=1'
require_output_contains "$output" 'candidate_fedora_rpmlint_evidence_present=1'
require_output_contains "$output" 'candidate_fedora_multi_vm_validation_evidence_present=1'
require_output_contains "$output" 'candidate_fedora_update_safety_evidence_present=1'
require_output_contains "$output" 'candidate_fedora_recovery_safety_evidence_present=1'
require_output_contains "$output" 'fedora_production_readiness_accepted_by_intake_validator=0'
require_output_contains "$output" 'fedora_production_readiness_written_by_intake_validator=0'
require_output_contains "$output" 'fedora_production_readiness_promotion_allowed_by_intake_validator_alone=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'fedora_distribution_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --matrix "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder Fedora production-readiness matrix unexpectedly passed validation'
fi

printf 'fedora_production_readiness_evidence_intake_validator: ok\n'
