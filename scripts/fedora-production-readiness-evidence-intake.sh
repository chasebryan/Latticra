#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-production-readiness-evidence-intake.sh --matrix <path>

Validates a supplied Fedora production-readiness evidence matrix candidate.
It reads the provided file, rejects missing required markers and placeholder
values, and prints a no-effect intake validation report. It does not run
Fedora VM validation, build an RPM, install an RPM, remove an RPM, write
production-readiness evidence, accept production readiness, allow promotion
by itself, submit to Fedora, or mutate the host.
USAGE
}

fail() {
  printf 'fedora production readiness evidence intake: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file" 66
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern"
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

reject_placeholders() {
  file="$1"
  if grep -Eq -- '<required|<placeholder>|TODO|TBD' "$file"; then
    fail "placeholder value is not acceptable in matrix candidate"
  fi
}

MATRIX_CANDIDATE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --matrix)
      [ "$#" -ge 2 ] || fail "missing value for --matrix" 64
      MATRIX_CANDIDATE="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

[ -n "$MATRIX_CANDIDATE" ] || fail 'missing --matrix path' 64
require_file "$MATRIX_CANDIDATE"
require_file docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_file docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md
require_file scripts/fedora-production-readiness-evidence-matrix.sh
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE_STATUS.md
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'FEDORA PRODUCTION READINESS EVIDENCE MATRIX' docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_contains 'fedora_production_readiness_evidence_complete=0' docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md
require_contains 'FEDORA PRODUCTION READINESS EVIDENCE MATRIX' scripts/fedora-production-readiness-evidence-matrix.sh
require_contains 'promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE.md
require_contains 'production_installer_promotion_allowed=0' docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE_STATUS.md
require_contains 'Fedora production-readiness evidence matrix is present' README.md

for marker in \
  'FEDORA PRODUCTION READINESS EVIDENCE MATRIX' \
  'matrix_status=complete' \
  'fedora_production_readiness_evidence_matrix_present=1' \
  'fedora_production_readiness_filled_matrix_candidate_valid=1' \
  'fedora_production_readiness_required_markers_present=1' \
  'fedora_production_readiness_placeholder_values_absent=1' \
  'fedora_production_readiness_value_fields_validated=1' \
  'fedora_production_readiness_evidence_complete=1' \
  'fedora_production_readiness_promotion_allowed=0' \
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
  'production_installer_promotion_allowed=0' \
  'fedora_distribution_promotion_allowed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$marker" "$MATRIX_CANDIDATE"
done

reject_placeholders "$MATRIX_CANDIDATE"

for forbidden_claim in \
  'fedora_production_readiness_promotion_allowed=1' \
  'production_installer_promotion_allowed=1' \
  'fedora_distribution_promotion_allowed=1' \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'host_mutation_performed=1'
do
  require_absent "$forbidden_claim" "$MATRIX_CANDIDATE"
done

cat <<'REPORT'
FEDORA PRODUCTION READINESS EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
fedora_production_readiness_evidence_intake_validator_present=1
fedora_production_readiness_evidence_intake_validation_mode=no-effect-validation
fedora_production_readiness_filled_matrix_candidate_valid=1
fedora_production_readiness_required_markers_present=1
fedora_production_readiness_placeholder_values_absent=1
fedora_production_readiness_value_fields_validated=1
candidate_fedora_production_readiness_evidence_complete=1
candidate_fedora_cli_payload_repeatability_prerequisite_complete=1
candidate_fedora_package_review_ready=1
candidate_fedora_mock_build_evidence_present=1
candidate_fedora_rpmlint_evidence_present=1
candidate_fedora_multi_vm_validation_evidence_present=1
candidate_fedora_update_safety_evidence_present=1
candidate_fedora_recovery_safety_evidence_present=1
candidate_fedora_immutable_host_evidence_present=1
candidate_fedora_daily_driver_evidence_present=1
candidate_fedora_security_hardening_evidence_present=1
fedora_production_readiness_accepted_by_intake_validator=0
fedora_production_readiness_written_by_intake_validator=0
fedora_production_readiness_promotion_allowed_by_intake_validator_alone=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
REPORT
