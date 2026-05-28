#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-transcript-evidence-intake.sh \
    --install <path> \
    --uninstall <path> \
    --absence <path> \
    --install-review <path> \
    --uninstall-review <path> \
    --absence-review <path> \
    --evidence <path>

Validates a future production-installer dry-run transcript evidence bundle.
It checks local file presence, transcript markers, review evidence hashes,
required evidence fields, and placeholder absence. It does not install,
uninstall, invoke a package manager, accept evidence, pass promotion, or mutate
the host.
USAGE
}

fail() {
  printf 'production installer transcript evidence intake: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file" 66
}

require_nonempty_file() {
  file="$1"
  require_file "$file"
  [ -s "$file" ] || fail "empty file: $file"
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
    fail "placeholder value is not acceptable in transcript evidence"
  fi
}

sha256_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    set -- $(sha256sum "$file")
    printf '%s\n' "$1" | tr 'A-F' 'a-f'
  elif command -v shasum >/dev/null 2>&1; then
    set -- $(shasum -a 256 "$file")
    printf '%s\n' "$1" | tr 'A-F' 'a-f'
  else
    fail 'missing sha256 tool'
  fi
}

require_digest() {
  digest="$1"
  label="$2"
  printf '%s\n' "$digest" | grep -Eq '^[0-9a-f]{64}$' ||
    fail "invalid sha256 digest for $label"
}

INSTALL=''
UNINSTALL=''
ABSENCE=''
INSTALL_REVIEW=''
UNINSTALL_REVIEW=''
ABSENCE_REVIEW=''
EVIDENCE=''

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

[ -n "$INSTALL" ] || fail 'missing --install path' 64
[ -n "$UNINSTALL" ] || fail 'missing --uninstall path' 64
[ -n "$ABSENCE" ] || fail 'missing --absence path' 64
[ -n "$INSTALL_REVIEW" ] || fail 'missing --install-review path' 64
[ -n "$UNINSTALL_REVIEW" ] || fail 'missing --uninstall-review path' 64
[ -n "$ABSENCE_REVIEW" ] || fail 'missing --absence-review path' 64
[ -n "$EVIDENCE" ] || fail 'missing --evidence path' 64

for file in "$INSTALL" "$UNINSTALL" "$ABSENCE" "$INSTALL_REVIEW" "$UNINSTALL_REVIEW" "$ABSENCE_REVIEW" "$EVIDENCE"
do
  require_nonempty_file "$file"
done

require_file docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_file scripts/production-installer-transcript-status.sh
require_file docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_file README.md

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'production_installer_transcript_status_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_transcript_status_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_install_transcript_recorded=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_uninstall_transcript_recorded=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_post_removal_absence_verified=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'Status: no-effect installer transcript status contract' docs/PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

require_contains 'LATTICRA PRODUCTION INSTALLER DRY RUN INSTALL TRANSCRIPT' "$INSTALL"
require_contains 'production_installer_dry_run_performed=1' "$INSTALL"
require_contains 'install_transcript_present=1' "$INSTALL"
require_contains 'install_performed=0' "$INSTALL"
require_contains 'package_manager_invoked=0' "$INSTALL"
require_contains 'host_mutation_performed=0' "$INSTALL"
require_contains 'network_allowed=0' "$INSTALL"

require_contains 'LATTICRA PRODUCTION INSTALLER DRY RUN UNINSTALL TRANSCRIPT' "$UNINSTALL"
require_contains 'production_installer_dry_run_performed=1' "$UNINSTALL"
require_contains 'uninstall_transcript_present=1' "$UNINSTALL"
require_contains 'uninstall_performed=0' "$UNINSTALL"
require_contains 'package_manager_invoked=0' "$UNINSTALL"
require_contains 'host_mutation_performed=0' "$UNINSTALL"
require_contains 'network_allowed=0' "$UNINSTALL"

require_contains 'LATTICRA PRODUCTION INSTALLER DRY RUN POST-REMOVAL ABSENCE TRANSCRIPT' "$ABSENCE"
require_contains 'production_installer_dry_run_performed=1' "$ABSENCE"
require_contains 'post_removal_absence_transcript_present=1' "$ABSENCE"
require_contains 'post_removal_absence_check_performed=1' "$ABSENCE"
require_contains 'post_removal_absence_verified=1' "$ABSENCE"
require_contains 'host_mutation_performed=0' "$ABSENCE"
require_contains 'network_allowed=0' "$ABSENCE"

install_sha256="$(sha256_file "$INSTALL")"
uninstall_sha256="$(sha256_file "$UNINSTALL")"
absence_sha256="$(sha256_file "$ABSENCE")"
install_review_sha256="$(sha256_file "$INSTALL_REVIEW")"
uninstall_review_sha256="$(sha256_file "$UNINSTALL_REVIEW")"
absence_review_sha256="$(sha256_file "$ABSENCE_REVIEW")"

require_digest "$install_sha256" 'install transcript'
require_digest "$uninstall_sha256" 'uninstall transcript'
require_digest "$absence_sha256" 'post-removal absence transcript'
require_digest "$install_review_sha256" 'install transcript review'
require_digest "$uninstall_review_sha256" 'uninstall transcript review'
require_digest "$absence_review_sha256" 'post-removal absence review'

for marker in \
  'LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE' \
  'transcript_evidence_status=complete' \
  'production_installer_dry_run_performed=1' \
  'install_transcript_present=1' \
  'uninstall_transcript_present=1' \
  'post_removal_absence_transcript_present=1' \
  'install_transcript_reviewed=1' \
  'uninstall_transcript_reviewed=1' \
  'post_removal_absence_reviewed=1' \
  'installer_install_transcript_recorded=1' \
  'installer_uninstall_transcript_recorded=1' \
  'installer_post_removal_absence_verified=1' \
  "install_transcript_sha256=$install_sha256" \
  "uninstall_transcript_sha256=$uninstall_sha256" \
  "post_removal_absence_transcript_sha256=$absence_sha256" \
  "install_transcript_review_sha256=$install_review_sha256" \
  "uninstall_transcript_review_sha256=$uninstall_review_sha256" \
  "post_removal_absence_review_sha256=$absence_review_sha256" \
  'install_performed=0' \
  'uninstall_performed=0' \
  'package_manager_invoked=0' \
  'release_artifact_promotion_gate_passed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0' \
  'network_allowed=0'
do
  require_contains "$marker" "$EVIDENCE"
done

reject_placeholders "$EVIDENCE"

for forbidden_claim in \
  'transcript_evidence_accepted_by_intake_validator=1' \
  'transcript_evidence_written_by_intake_validator=1' \
  'installer_transcript_promotion_allowed_by_intake_validator_alone=1' \
  'release_artifact_promotion_gate_passed=1' \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'install_performed=1' \
  'uninstall_performed=1' \
  'package_manager_invoked=1' \
  'host_mutation_performed=1' \
  'network_allowed=1'
do
  require_absent "$forbidden_claim" "$EVIDENCE"
done

cat <<REPORT
LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
transcript_evidence_intake_validator_present=1
transcript_evidence_intake_validation_mode=no-effect-validation
transcript_evidence_candidate_valid=1
install_transcript_file_present=1
uninstall_transcript_file_present=1
post_removal_absence_transcript_file_present=1
install_transcript_sha256_recorded=1
uninstall_transcript_sha256_recorded=1
post_removal_absence_transcript_sha256_recorded=1
candidate_install_transcript_sha256=$install_sha256
candidate_uninstall_transcript_sha256=$uninstall_sha256
candidate_post_removal_absence_transcript_sha256=$absence_sha256
candidate_install_transcript_review_sha256=$install_review_sha256
candidate_uninstall_transcript_review_sha256=$uninstall_review_sha256
candidate_post_removal_absence_review_sha256=$absence_review_sha256
candidate_production_installer_dry_run_performed=1
candidate_install_transcript_reviewed=1
candidate_uninstall_transcript_reviewed=1
candidate_post_removal_absence_reviewed=1
candidate_installer_install_transcript_recorded=1
candidate_installer_uninstall_transcript_recorded=1
candidate_installer_post_removal_absence_verified=1
transcript_evidence_accepted_by_intake_validator=0
transcript_evidence_written_by_intake_validator=0
installer_transcript_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_post_removal_absence_verified=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
install_performed=0
uninstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
REPORT
