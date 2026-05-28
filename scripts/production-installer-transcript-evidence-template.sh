#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-transcript-evidence-template.sh \
    [--install <path>] \
    [--uninstall <path>] \
    [--absence <path>] \
    [--install-review <path>] \
    [--uninstall-review <path>] \
    [--absence-review <path>] \
    [--evidence <path>]

Prints a no-effect template for a future production-installer dry-run
transcript evidence bundle. It does not install, uninstall, invoke package
managers, calculate transcript hashes, write evidence files, accept evidence,
pass promotion, use network access, or mutate the host.
USAGE
}

fail() {
  printf 'production installer transcript evidence template: %s\n' "$1" >&2
  exit "${2:-1}"
}

presence() {
  if [ -f "$1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern" 65
}

INSTALL='artifacts/release/latticra-production-installer-dry-run-install-transcript.txt'
UNINSTALL='artifacts/release/latticra-production-installer-dry-run-uninstall-transcript.txt'
ABSENCE='artifacts/release/latticra-production-installer-dry-run-post-removal-absence-transcript.txt'
INSTALL_REVIEW='artifacts/release/latticra-production-installer-install-transcript-review.txt'
UNINSTALL_REVIEW='artifacts/release/latticra-production-installer-uninstall-transcript-review.txt'
ABSENCE_REVIEW='artifacts/release/latticra-production-installer-post-removal-absence-review.txt'
EVIDENCE='artifacts/release/latticra-production-installer-transcript-evidence.txt'

while [ "$#" -gt 0 ]; do
  case "$1" in
    --install)
      [ "$#" -ge 2 ] || fail 'missing value for --install' 64
      INSTALL="$2"
      shift 2
      ;;
    --uninstall)
      [ "$#" -ge 2 ] || fail 'missing value for --uninstall' 64
      UNINSTALL="$2"
      shift 2
      ;;
    --absence)
      [ "$#" -ge 2 ] || fail 'missing value for --absence' 64
      ABSENCE="$2"
      shift 2
      ;;
    --install-review)
      [ "$#" -ge 2 ] || fail 'missing value for --install-review' 64
      INSTALL_REVIEW="$2"
      shift 2
      ;;
    --uninstall-review)
      [ "$#" -ge 2 ] || fail 'missing value for --uninstall-review' 64
      UNINSTALL_REVIEW="$2"
      shift 2
      ;;
    --absence-review)
      [ "$#" -ge 2 ] || fail 'missing value for --absence-review' 64
      ABSENCE_REVIEW="$2"
      shift 2
      ;;
    --evidence)
      [ "$#" -ge 2 ] || fail 'missing value for --evidence' 64
      EVIDENCE="$2"
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

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'transcript_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'transcript_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'transcript_evidence_status=complete' docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'Production quality blocker ledger' README.md

cat <<TEMPLATE
LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE TEMPLATE
template_status=ok
transcript_evidence_template_present=1
transcript_evidence_template_mode=no-effect-template
transcript_evidence_template_decision=blocked-template-only-no-evidence-write
transcript_evidence_template_complete=0
transcript_evidence_intake_validator_present=1
transcript_evidence_intake_validation_mode=no-effect-validation
transcript_evidence_path=$EVIDENCE
install_transcript_path=$INSTALL
uninstall_transcript_path=$UNINSTALL
post_removal_absence_transcript_path=$ABSENCE
install_transcript_review_path=$INSTALL_REVIEW
uninstall_transcript_review_path=$UNINSTALL_REVIEW
post_removal_absence_review_path=$ABSENCE_REVIEW
install_transcript_file_present=$(presence "$INSTALL")
uninstall_transcript_file_present=$(presence "$UNINSTALL")
post_removal_absence_transcript_file_present=$(presence "$ABSENCE")
install_transcript_review_file_present=$(presence "$INSTALL_REVIEW")
uninstall_transcript_review_file_present=$(presence "$UNINSTALL_REVIEW")
post_removal_absence_review_file_present=$(presence "$ABSENCE_REVIEW")

[required_transcript_markers]
LATTICRA PRODUCTION INSTALLER DRY RUN INSTALL TRANSCRIPT
production_installer_dry_run_performed=1
install_transcript_present=1
install_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0

LATTICRA PRODUCTION INSTALLER DRY RUN UNINSTALL TRANSCRIPT
production_installer_dry_run_performed=1
uninstall_transcript_present=1
uninstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0

LATTICRA PRODUCTION INSTALLER DRY RUN POST-REMOVAL ABSENCE TRANSCRIPT
production_installer_dry_run_performed=1
post_removal_absence_transcript_present=1
post_removal_absence_check_performed=1
post_removal_absence_verified=1
host_mutation_performed=0
network_allowed=0

[required_evidence_fields]
LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE
transcript_evidence_status=complete
production_installer_dry_run_performed=1
install_transcript_present=1
uninstall_transcript_present=1
post_removal_absence_transcript_present=1
install_transcript_reviewed=1
uninstall_transcript_reviewed=1
post_removal_absence_reviewed=1
installer_install_transcript_recorded=1
installer_uninstall_transcript_recorded=1
installer_post_removal_absence_verified=1
install_transcript_sha256=<required-install-transcript-sha256>
uninstall_transcript_sha256=<required-uninstall-transcript-sha256>
post_removal_absence_transcript_sha256=<required-absence-transcript-sha256>
install_transcript_review_sha256=<required-install-review-sha256>
uninstall_transcript_review_sha256=<required-uninstall-review-sha256>
post_removal_absence_review_sha256=<required-absence-review-sha256>
install_performed=0
uninstall_performed=0
package_manager_invoked=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
network_allowed=0

[template_non_effects]
transcripts_created_by_template=0
transcript_hashes_calculated_by_template=0
transcript_evidence_written_by_template=0
transcript_evidence_accepted_by_template=0
transcript_evidence_accepted_by_intake_validator=0
transcript_evidence_written_by_intake_validator=0
installer_transcript_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_post_removal_absence_verified=0
install_performed=0
uninstall_performed=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
production_installer_ready=0
TEMPLATE
