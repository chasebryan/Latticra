#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer lifecycle evidence intake validator contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
script='scripts/production-installer-lifecycle-evidence-intake.sh'
test_script='scripts/test-production-installer-lifecycle-evidence-intake-validator-contract.sh'
lifecycle_status='docs/PRODUCTION_INSTALLER_LIFECYCLE_VALIDATION_STATUS_CONTRACT.md'
transcript_intake='docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
promotion_gate='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
workflow='.github/workflows/production-installer-lifecycle-evidence-intake-validator.yml'
installer_page='docs/installer.html'

for file in "$doc" "$status" "$script" "$test_script" "$lifecycle_status" "$transcript_intake" "$readiness" "$promotion_gate" "$ledger" "$index" "$workflow" "$installer_page" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect lifecycle evidence intake validator contract' "$doc"
require_contains 'lifecycle_evidence_intake_validator_present=1' "$doc"
require_contains 'lifecycle_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'lifecycle_evidence_candidate_valid=0' "$doc"
require_contains 'upgrade_transcript_file_present=0' "$doc"
require_contains 'rollback_transcript_file_present=0' "$doc"
require_contains 'reinstall_transcript_file_present=0' "$doc"
require_contains 'lifecycle_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'lifecycle_evidence_written_by_intake_validator=0' "$doc"
require_contains 'installer_lifecycle_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'installer_upgrade_path_validated=0' "$doc"
require_contains 'installer_rollback_path_validated=0' "$doc"
require_contains 'installer_downgrade_or_rollback_path_validated=0' "$doc"
require_contains 'installer_reinstall_idempotence_validated=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-lifecycle-evidence-intake.sh \' "$doc"
require_contains 'sh scripts/test-production-installer-lifecycle-evidence-intake-validator-contract.sh' "$doc"

require_contains 'LATTICRA PRODUCTION INSTALLER LIFECYCLE EVIDENCE INTAKE VALIDATION' "$script"
require_contains 'lifecycle_evidence_intake_validation_mode=no-effect-validation' "$script"
require_contains 'lifecycle_evidence_candidate_valid=1' "$script"
require_contains 'candidate_installer_upgrade_path_validated=1' "$script"
require_contains 'candidate_installer_rollback_path_validated=1' "$script"
require_contains 'candidate_installer_reinstall_idempotence_validated=1' "$script"
require_contains 'lifecycle_evidence_accepted_by_intake_validator=0' "$script"
require_contains 'lifecycle_evidence_written_by_intake_validator=0' "$script"
require_contains 'installer_lifecycle_promotion_allowed_by_intake_validator_alone=0' "$script"
require_contains 'release_artifact_promotion_gate_passed=0' "$script"
require_contains 'upgrade_performed=0' "$script"
require_contains 'rollback_performed=0' "$script"
require_contains 'reinstall_performed=0' "$script"
require_contains 'package_manager_invoked=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'placeholder value is not acceptable in lifecycle evidence' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'rpm -' "$script"
require_absent 'rpmbuild' "$script"
require_absent 'mock ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'lifecycle_evidence_intake_validator_present=1' \
  'lifecycle_evidence_intake_validation_mode=no-effect-validation' \
  'lifecycle_evidence_candidate_valid=0' \
  'upgrade_transcript_file_present=0' \
  'rollback_transcript_file_present=0' \
  'reinstall_transcript_file_present=0' \
  'upgrade_transcript_sha256_recorded=0' \
  'rollback_transcript_sha256_recorded=0' \
  'reinstall_transcript_sha256_recorded=0' \
  'upgrade_transcript_review_present=0' \
  'rollback_transcript_review_present=0' \
  'reinstall_transcript_review_present=0' \
  'lifecycle_evidence_accepted_by_intake_validator=0' \
  'lifecycle_evidence_written_by_intake_validator=0' \
  'installer_lifecycle_promotion_allowed_by_intake_validator_alone=0' \
  'release_artifact_promotion_gate_passed=0' \
  'installer_upgrade_path_validated=0' \
  'installer_rollback_path_validated=0' \
  'installer_downgrade_or_rollback_path_validated=0' \
  'installer_reinstall_idempotence_validated=0' \
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
  'lifecycle_evidence_status=complete' \
  'production_installer_lifecycle_validation_performed=1' \
  'installer_upgrade_candidate_present=1' \
  'installer_rollback_candidate_present=1' \
  'installer_reinstall_candidate_present=1' \
  'upgrade_transcript_present=1' \
  'rollback_transcript_present=1' \
  'reinstall_transcript_present=1' \
  'upgrade_transcript_reviewed=1' \
  'rollback_transcript_reviewed=1' \
  'reinstall_transcript_reviewed=1' \
  'installer_upgrade_path_validated=1' \
  'installer_rollback_path_validated=1' \
  'installer_downgrade_or_rollback_path_validated=1' \
  'installer_reinstall_idempotence_validated=1' \
  'upgrade_performed=0' \
  'rollback_performed=0' \
  'reinstall_performed=0' \
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

require_contains 'PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'lifecycle_evidence_intake_validator_present=1' "$readiness"
require_contains 'lifecycle_evidence_intake_validation_mode=no-effect-validation' "$readiness"
require_contains 'lifecycle_evidence_candidate_valid=0' "$readiness"
require_contains 'lifecycle_evidence_accepted_by_intake_validator=0' "$readiness"
require_contains 'lifecycle_evidence_intake_validator_present=1' "$ledger"
require_contains 'lifecycle_evidence_intake_validator_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' README.md
require_contains 'lifecycle_evidence_intake_validator' "$installer_page"

require_contains 'production-installer-lifecycle-evidence-intake-validator-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-lifecycle-evidence-intake-validator-contract.sh' Makefile
require_contains 'name: Production Installer Lifecycle Evidence Intake Validator' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-lifecycle-evidence-intake-validator-contract.sh' "$workflow"
require_absent 'sh scripts/production-installer-lifecycle-evidence-intake.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-lifecycle-evidence-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

upgrade="$tmp/upgrade-transcript.txt"
rollback="$tmp/rollback-transcript.txt"
reinstall="$tmp/reinstall-transcript.txt"
bad_upgrade="$tmp/bad-upgrade-transcript.txt"
upgrade_review="$tmp/upgrade-review.txt"
rollback_review="$tmp/rollback-review.txt"
reinstall_review="$tmp/reinstall-review.txt"
valid_evidence="$tmp/lifecycle-evidence.txt"
bad_hash_evidence="$tmp/lifecycle-bad-hash-evidence.txt"
placeholder_evidence="$tmp/lifecycle-placeholder-evidence.txt"

cat >"$upgrade" <<'UPGRADE_TRANSCRIPT'
LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN UPGRADE TRANSCRIPT
production_installer_lifecycle_validation_performed=1
upgrade_transcript_present=1
upgrade_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
UPGRADE_TRANSCRIPT

cat >"$rollback" <<'ROLLBACK_TRANSCRIPT'
LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN ROLLBACK TRANSCRIPT
production_installer_lifecycle_validation_performed=1
rollback_transcript_present=1
rollback_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
ROLLBACK_TRANSCRIPT

cat >"$reinstall" <<'REINSTALL_TRANSCRIPT'
LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN REINSTALL TRANSCRIPT
production_installer_lifecycle_validation_performed=1
reinstall_transcript_present=1
reinstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
REINSTALL_TRANSCRIPT

printf 'missing required lifecycle markers\n' >"$bad_upgrade"
printf 'upgrade transcript review fixture\n' >"$upgrade_review"
printf 'rollback transcript review fixture\n' >"$rollback_review"
printf 'reinstall transcript review fixture\n' >"$reinstall_review"

upgrade_sha="$(sha256_file "$upgrade")"
rollback_sha="$(sha256_file "$rollback")"
reinstall_sha="$(sha256_file "$reinstall")"
upgrade_review_sha="$(sha256_file "$upgrade_review")"
rollback_review_sha="$(sha256_file "$rollback_review")"
reinstall_review_sha="$(sha256_file "$reinstall_review")"

cat >"$valid_evidence" <<VALID_EVIDENCE
LATTICRA PRODUCTION INSTALLER LIFECYCLE EVIDENCE
lifecycle_evidence_status=complete
production_installer_lifecycle_validation_performed=1
installer_upgrade_candidate_present=1
installer_rollback_candidate_present=1
installer_reinstall_candidate_present=1
upgrade_transcript_present=1
rollback_transcript_present=1
reinstall_transcript_present=1
upgrade_transcript_reviewed=1
rollback_transcript_reviewed=1
reinstall_transcript_reviewed=1
installer_upgrade_path_validated=1
installer_rollback_path_validated=1
installer_downgrade_or_rollback_path_validated=1
installer_reinstall_idempotence_validated=1
upgrade_transcript_sha256=$upgrade_sha
rollback_transcript_sha256=$rollback_sha
reinstall_transcript_sha256=$reinstall_sha
upgrade_transcript_review_sha256=$upgrade_review_sha
rollback_transcript_review_sha256=$rollback_review_sha
reinstall_transcript_review_sha256=$reinstall_review_sha
upgrade_performed=0
rollback_performed=0
reinstall_performed=0
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

sed "s/$upgrade_sha/0000000000000000000000000000000000000000000000000000000000000000/" "$valid_evidence" >"$bad_hash_evidence"
cp "$valid_evidence" "$placeholder_evidence"
printf '%s\n' 'upgrade_transcript_review_reference=<required-review-id>' >>"$placeholder_evidence"

output="$(sh "$script" \
  --upgrade "$upgrade" \
  --rollback "$rollback" \
  --reinstall "$reinstall" \
  --upgrade-review "$upgrade_review" \
  --rollback-review "$rollback_review" \
  --reinstall-review "$reinstall_review" \
  --evidence "$valid_evidence")"

require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER LIFECYCLE EVIDENCE INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'lifecycle_evidence_intake_validator_present=1'
require_output_contains "$output" 'lifecycle_evidence_candidate_valid=1'
require_output_contains "$output" "candidate_upgrade_transcript_sha256=$upgrade_sha"
require_output_contains "$output" "candidate_rollback_transcript_sha256=$rollback_sha"
require_output_contains "$output" "candidate_reinstall_transcript_sha256=$reinstall_sha"
require_output_contains "$output" "candidate_upgrade_transcript_review_sha256=$upgrade_review_sha"
require_output_contains "$output" "candidate_rollback_transcript_review_sha256=$rollback_review_sha"
require_output_contains "$output" "candidate_reinstall_transcript_review_sha256=$reinstall_review_sha"
require_output_contains "$output" 'lifecycle_evidence_accepted_by_intake_validator=0'
require_output_contains "$output" 'lifecycle_evidence_written_by_intake_validator=0'
require_output_contains "$output" 'installer_lifecycle_promotion_allowed_by_intake_validator_alone=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'installer_upgrade_path_validated=0'
require_output_contains "$output" 'installer_rollback_path_validated=0'
require_output_contains "$output" 'installer_downgrade_or_rollback_path_validated=0'
require_output_contains "$output" 'installer_reinstall_idempotence_validated=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" \
  --upgrade "$bad_upgrade" \
  --rollback "$rollback" \
  --reinstall "$reinstall" \
  --upgrade-review "$upgrade_review" \
  --rollback-review "$rollback_review" \
  --reinstall-review "$reinstall_review" \
  --evidence "$valid_evidence" >/dev/null 2>&1; then
  fail 'bad upgrade transcript evidence unexpectedly passed validation'
fi

if sh "$script" \
  --upgrade "$upgrade" \
  --rollback "$rollback" \
  --reinstall "$reinstall" \
  --upgrade-review "$upgrade_review" \
  --rollback-review "$rollback_review" \
  --reinstall-review "$reinstall_review" \
  --evidence "$bad_hash_evidence" >/dev/null 2>&1; then
  fail 'bad-hash lifecycle evidence unexpectedly passed validation'
fi

if sh "$script" \
  --upgrade "$upgrade" \
  --rollback "$rollback" \
  --reinstall "$reinstall" \
  --upgrade-review "$upgrade_review" \
  --rollback-review "$rollback_review" \
  --reinstall-review "$reinstall_review" \
  --evidence "$placeholder_evidence" >/dev/null 2>&1; then
  fail 'placeholder lifecycle evidence unexpectedly passed validation'
fi

printf 'production_installer_lifecycle_evidence_intake_validator_contract: ok\n'
