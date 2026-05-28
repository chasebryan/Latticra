#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer transcript evidence intake validator contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
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
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
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

doc='docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
script='scripts/production-installer-transcript-evidence-intake.sh'
test_script='scripts/test-production-installer-transcript-evidence-intake-validator-contract.sh'
transcript_status='docs/PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
promotion_gate='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
workflow='.github/workflows/production-installer-transcript-evidence-intake-validator.yml'
installer_page='docs/installer.html'

for file in "$doc" "$status" "$script" "$test_script" "$transcript_status" "$readiness" "$promotion_gate" "$ledger" "$index" "$workflow" "$installer_page" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect transcript evidence intake validator contract' "$doc"
require_contains 'transcript_evidence_intake_validator_present=1' "$doc"
require_contains 'transcript_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'transcript_evidence_candidate_valid=0' "$doc"
require_contains 'install_transcript_file_present=0' "$doc"
require_contains 'uninstall_transcript_file_present=0' "$doc"
require_contains 'post_removal_absence_transcript_file_present=0' "$doc"
require_contains 'transcript_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'transcript_evidence_written_by_intake_validator=0' "$doc"
require_contains 'installer_transcript_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'installer_install_transcript_recorded=0' "$doc"
require_contains 'installer_uninstall_transcript_recorded=0' "$doc"
require_contains 'installer_post_removal_absence_verified=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-transcript-evidence-intake.sh \' "$doc"
require_contains 'sh scripts/test-production-installer-transcript-evidence-intake-validator-contract.sh' "$doc"

require_contains 'LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE INTAKE VALIDATION' "$script"
require_contains 'transcript_evidence_intake_validation_mode=no-effect-validation' "$script"
require_contains 'transcript_evidence_candidate_valid=1' "$script"
require_contains 'candidate_installer_install_transcript_recorded=1' "$script"
require_contains 'candidate_installer_uninstall_transcript_recorded=1' "$script"
require_contains 'candidate_installer_post_removal_absence_verified=1' "$script"
require_contains 'transcript_evidence_accepted_by_intake_validator=0' "$script"
require_contains 'transcript_evidence_written_by_intake_validator=0' "$script"
require_contains 'installer_transcript_promotion_allowed_by_intake_validator_alone=0' "$script"
require_contains 'release_artifact_promotion_gate_passed=0' "$script"
require_contains 'install_performed=0' "$script"
require_contains 'uninstall_performed=0' "$script"
require_contains 'package_manager_invoked=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'placeholder value is not acceptable in transcript evidence' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'rpm -' "$script"
require_absent 'rpmbuild' "$script"
require_absent 'mock ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'transcript_evidence_intake_validator_present=1' \
  'transcript_evidence_intake_validation_mode=no-effect-validation' \
  'transcript_evidence_candidate_valid=0' \
  'install_transcript_file_present=0' \
  'uninstall_transcript_file_present=0' \
  'post_removal_absence_transcript_file_present=0' \
  'install_transcript_sha256_recorded=0' \
  'uninstall_transcript_sha256_recorded=0' \
  'post_removal_absence_transcript_sha256_recorded=0' \
  'install_transcript_review_present=0' \
  'uninstall_transcript_review_present=0' \
  'post_removal_absence_review_present=0' \
  'transcript_evidence_accepted_by_intake_validator=0' \
  'transcript_evidence_written_by_intake_validator=0' \
  'installer_transcript_promotion_allowed_by_intake_validator_alone=0' \
  'release_artifact_promotion_gate_passed=0' \
  'installer_install_transcript_recorded=0' \
  'installer_uninstall_transcript_recorded=0' \
  'installer_post_removal_absence_verified=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
done

for future_field in \
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
  require_contains "$future_field" "$doc"
  require_contains "$future_field" "$status"
  require_contains "$future_field" "$script"
done

require_contains 'PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'transcript_evidence_intake_validator_present=1' "$readiness"
require_contains 'transcript_evidence_intake_validation_mode=no-effect-validation' "$readiness"
require_contains 'transcript_evidence_candidate_valid=0' "$readiness"
require_contains 'transcript_evidence_accepted_by_intake_validator=0' "$readiness"
require_contains 'transcript_evidence_intake_validator_present=1' "$ledger"
require_contains 'transcript_evidence_intake_validator_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' README.md
require_contains 'transcript_evidence_intake_validator' "$installer_page"

require_contains 'production-installer-transcript-evidence-intake-validator-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-transcript-evidence-intake-validator-contract.sh' Makefile
require_contains 'name: Production Installer Transcript Evidence Intake Validator' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-transcript-evidence-intake-validator-contract.sh' "$workflow"
require_absent 'sh scripts/production-installer-transcript-evidence-intake.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-transcript-evidence-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

install="$tmp/install-transcript.txt"
uninstall="$tmp/uninstall-transcript.txt"
absence="$tmp/post-removal-absence.txt"
bad_install="$tmp/bad-install-transcript.txt"
install_review="$tmp/install-review.txt"
uninstall_review="$tmp/uninstall-review.txt"
absence_review="$tmp/absence-review.txt"
valid_evidence="$tmp/transcript-evidence.txt"
bad_hash_evidence="$tmp/transcript-bad-hash-evidence.txt"
placeholder_evidence="$tmp/transcript-placeholder-evidence.txt"

cat >"$install" <<'INSTALL_TRANSCRIPT'
LATTICRA PRODUCTION INSTALLER DRY RUN INSTALL TRANSCRIPT
production_installer_dry_run_performed=1
install_transcript_present=1
install_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
INSTALL_TRANSCRIPT

cat >"$uninstall" <<'UNINSTALL_TRANSCRIPT'
LATTICRA PRODUCTION INSTALLER DRY RUN UNINSTALL TRANSCRIPT
production_installer_dry_run_performed=1
uninstall_transcript_present=1
uninstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
UNINSTALL_TRANSCRIPT

cat >"$absence" <<'ABSENCE_TRANSCRIPT'
LATTICRA PRODUCTION INSTALLER DRY RUN POST-REMOVAL ABSENCE TRANSCRIPT
production_installer_dry_run_performed=1
post_removal_absence_transcript_present=1
post_removal_absence_check_performed=1
post_removal_absence_verified=1
host_mutation_performed=0
network_allowed=0
ABSENCE_TRANSCRIPT

printf 'missing required transcript markers\n' >"$bad_install"
printf 'install transcript review fixture\n' >"$install_review"
printf 'uninstall transcript review fixture\n' >"$uninstall_review"
printf 'post-removal absence review fixture\n' >"$absence_review"

install_sha="$(sha256_file "$install")"
uninstall_sha="$(sha256_file "$uninstall")"
absence_sha="$(sha256_file "$absence")"
install_review_sha="$(sha256_file "$install_review")"
uninstall_review_sha="$(sha256_file "$uninstall_review")"
absence_review_sha="$(sha256_file "$absence_review")"

cat >"$valid_evidence" <<VALID_EVIDENCE
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
install_transcript_sha256=$install_sha
uninstall_transcript_sha256=$uninstall_sha
post_removal_absence_transcript_sha256=$absence_sha
install_transcript_review_sha256=$install_review_sha
uninstall_transcript_review_sha256=$uninstall_review_sha
post_removal_absence_review_sha256=$absence_review_sha
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
VALID_EVIDENCE

sed "s/$install_sha/0000000000000000000000000000000000000000000000000000000000000000/" "$valid_evidence" >"$bad_hash_evidence"
cp "$valid_evidence" "$placeholder_evidence"
printf '%s\n' 'install_transcript_review_reference=<required-review-id>' >>"$placeholder_evidence"

output="$(sh "$script" \
  --install "$install" \
  --uninstall "$uninstall" \
  --absence "$absence" \
  --install-review "$install_review" \
  --uninstall-review "$uninstall_review" \
  --absence-review "$absence_review" \
  --evidence "$valid_evidence")"

require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'transcript_evidence_intake_validator_present=1'
require_output_contains "$output" 'transcript_evidence_candidate_valid=1'
require_output_contains "$output" "candidate_install_transcript_sha256=$install_sha"
require_output_contains "$output" "candidate_uninstall_transcript_sha256=$uninstall_sha"
require_output_contains "$output" "candidate_post_removal_absence_transcript_sha256=$absence_sha"
require_output_contains "$output" "candidate_install_transcript_review_sha256=$install_review_sha"
require_output_contains "$output" "candidate_uninstall_transcript_review_sha256=$uninstall_review_sha"
require_output_contains "$output" "candidate_post_removal_absence_review_sha256=$absence_review_sha"
require_output_contains "$output" 'transcript_evidence_accepted_by_intake_validator=0'
require_output_contains "$output" 'transcript_evidence_written_by_intake_validator=0'
require_output_contains "$output" 'installer_transcript_promotion_allowed_by_intake_validator_alone=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'installer_install_transcript_recorded=0'
require_output_contains "$output" 'installer_uninstall_transcript_recorded=0'
require_output_contains "$output" 'installer_post_removal_absence_verified=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" \
  --install "$bad_install" \
  --uninstall "$uninstall" \
  --absence "$absence" \
  --install-review "$install_review" \
  --uninstall-review "$uninstall_review" \
  --absence-review "$absence_review" \
  --evidence "$valid_evidence" >/dev/null 2>&1; then
  fail 'bad install transcript evidence unexpectedly passed validation'
fi

if sh "$script" \
  --install "$install" \
  --uninstall "$uninstall" \
  --absence "$absence" \
  --install-review "$install_review" \
  --uninstall-review "$uninstall_review" \
  --absence-review "$absence_review" \
  --evidence "$bad_hash_evidence" >/dev/null 2>&1; then
  fail 'bad-hash transcript evidence unexpectedly passed validation'
fi

if sh "$script" \
  --install "$install" \
  --uninstall "$uninstall" \
  --absence "$absence" \
  --install-review "$install_review" \
  --uninstall-review "$uninstall_review" \
  --absence-review "$absence_review" \
  --evidence "$placeholder_evidence" >/dev/null 2>&1; then
  fail 'placeholder transcript evidence unexpectedly passed validation'
fi

printf 'production_installer_transcript_evidence_intake_validator_contract: ok\n'
