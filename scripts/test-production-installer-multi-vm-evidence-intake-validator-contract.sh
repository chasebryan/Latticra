#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer multi-VM evidence intake validator contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
script='scripts/production-installer-multi-vm-evidence-intake.sh'
test_script='scripts/test-production-installer-multi-vm-evidence-intake-validator-contract.sh'
multi_vm_status='docs/PRODUCTION_INSTALLER_MULTI_VM_VALIDATION_STATUS_CONTRACT.md'
recovery_intake='docs/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
lifecycle_intake='docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
promotion_gate='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
workflow='.github/workflows/production-installer-multi-vm-evidence-intake-validator.yml'
installer_page='docs/installer.html'

for file in "$doc" "$status" "$script" "$test_script" "$multi_vm_status" "$recovery_intake" "$lifecycle_intake" "$readiness" "$promotion_gate" "$ledger" "$index" "$workflow" "$installer_page" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect multi-VM evidence intake validator contract' "$doc"
require_contains 'multi_vm_evidence_intake_validator_present=1' "$doc"
require_contains 'multi_vm_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'multi_vm_evidence_candidate_valid=0' "$doc"
require_contains 'fresh_vm_validation_file_present=0' "$doc"
require_contains 'repeat_vm_validation_file_present=0' "$doc"
require_contains 'existing_install_validation_file_present=0' "$doc"
require_contains 'remove_reinstall_validation_file_present=0' "$doc"
require_contains 'unsupported_target_validation_file_present=0' "$doc"
require_contains 'non_root_cli_validation_file_present=0' "$doc"
require_contains 'root_boundary_validation_file_present=0' "$doc"
require_contains 'checksum_verification_file_present=0' "$doc"
require_contains 'package_signature_verification_file_present=0' "$doc"
require_contains 'multi_vm_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'multi_vm_evidence_written_by_intake_validator=0' "$doc"
require_contains 'installer_multi_vm_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'installer_multi_vm_validation_completed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-multi-vm-evidence-intake.sh \' "$doc"
require_contains 'sh scripts/test-production-installer-multi-vm-evidence-intake-validator-contract.sh' "$doc"

require_contains 'LATTICRA PRODUCTION INSTALLER MULTI-VM EVIDENCE INTAKE VALIDATION' "$script"
require_contains 'multi_vm_evidence_intake_validation_mode=no-effect-validation' "$script"
require_contains 'multi_vm_evidence_candidate_valid=1' "$script"
require_contains 'candidate_installer_multi_vm_validation_completed=1' "$script"
require_contains 'candidate_installer_fresh_vm_validation_completed=1' "$script"
require_contains 'candidate_installer_repeat_vm_validation_completed=1' "$script"
require_contains 'candidate_installer_existing_install_validation_completed=1' "$script"
require_contains 'candidate_installer_non_root_cli_validation_completed=1' "$script"
require_contains 'candidate_installer_root_boundary_validation_completed=1' "$script"
require_contains 'multi_vm_evidence_accepted_by_intake_validator=0' "$script"
require_contains 'multi_vm_evidence_written_by_intake_validator=0' "$script"
require_contains 'installer_multi_vm_promotion_allowed_by_intake_validator_alone=0' "$script"
require_contains 'release_artifact_promotion_gate_passed=0' "$script"
require_contains 'vm_invocation_performed=0' "$script"
require_contains 'package_manager_invoked=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'placeholder value is not acceptable in multi-VM evidence' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'rpm -' "$script"
require_absent 'rpmbuild' "$script"
require_absent 'mock ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'multi_vm_evidence_intake_validator_present=1' \
  'multi_vm_evidence_intake_validation_mode=no-effect-validation' \
  'multi_vm_evidence_candidate_valid=0' \
  'fresh_vm_validation_file_present=0' \
  'repeat_vm_validation_file_present=0' \
  'existing_install_validation_file_present=0' \
  'remove_reinstall_validation_file_present=0' \
  'unsupported_target_validation_file_present=0' \
  'non_root_cli_validation_file_present=0' \
  'root_boundary_validation_file_present=0' \
  'checksum_verification_file_present=0' \
  'package_signature_verification_file_present=0' \
  'fresh_vm_validation_sha256_recorded=0' \
  'repeat_vm_validation_sha256_recorded=0' \
  'existing_install_validation_sha256_recorded=0' \
  'remove_reinstall_validation_sha256_recorded=0' \
  'unsupported_target_validation_sha256_recorded=0' \
  'non_root_cli_validation_sha256_recorded=0' \
  'root_boundary_validation_sha256_recorded=0' \
  'checksum_verification_sha256_recorded=0' \
  'package_signature_verification_sha256_recorded=0' \
  'fresh_vm_validation_review_present=0' \
  'repeat_vm_validation_review_present=0' \
  'existing_install_validation_review_present=0' \
  'remove_reinstall_validation_review_present=0' \
  'unsupported_target_validation_review_present=0' \
  'non_root_cli_validation_review_present=0' \
  'root_boundary_validation_review_present=0' \
  'checksum_verification_review_present=0' \
  'package_signature_verification_review_present=0' \
  'multi_vm_evidence_accepted_by_intake_validator=0' \
  'multi_vm_evidence_written_by_intake_validator=0' \
  'installer_multi_vm_promotion_allowed_by_intake_validator_alone=0' \
  'release_artifact_promotion_gate_passed=0' \
  'installer_multi_vm_validation_completed=0' \
  'installer_fresh_vm_validation_completed=0' \
  'installer_repeat_vm_validation_completed=0' \
  'installer_existing_install_validation_completed=0' \
  'installer_non_root_cli_validation_completed=0' \
  'installer_root_boundary_validation_completed=0' \
  'vm_invocation_performed=0' \
  'host_mutation_performed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$multi_vm_status"
done

for future_field in \
  'multi_vm_evidence_status=complete' \
  'fresh_vm_validation_evidence_present=1' \
  'repeat_vm_validation_evidence_present=1' \
  'existing_install_validation_evidence_present=1' \
  'remove_reinstall_validation_evidence_present=1' \
  'unsupported_target_validation_evidence_present=1' \
  'non_root_cli_validation_evidence_present=1' \
  'root_boundary_validation_evidence_present=1' \
  'checksum_verification_evidence_present=1' \
  'package_signature_verification_evidence_present=1' \
  'fresh_vm_validation_reviewed=1' \
  'repeat_vm_validation_reviewed=1' \
  'existing_install_validation_reviewed=1' \
  'remove_reinstall_validation_reviewed=1' \
  'unsupported_target_validation_reviewed=1' \
  'non_root_cli_validation_reviewed=1' \
  'root_boundary_validation_reviewed=1' \
  'checksum_verification_reviewed=1' \
  'package_signature_verification_reviewed=1' \
  'fresh_disposable_fedora_vm_validation=1' \
  'repeat_disposable_fedora_vm_validation=1' \
  'existing_install_upgrade_validation=1' \
  'remove_and_reinstall_validation=1' \
  'unsupported_target_block_validation=1' \
  'non_root_cli_use_validation=1' \
  'root_boundary_validation=1' \
  'checksum_verification_validation=1' \
  'package_signature_verification_validation=1' \
  'installer_multi_vm_validation_completed=1' \
  'installer_fresh_vm_validation_completed=1' \
  'installer_repeat_vm_validation_completed=1' \
  'installer_existing_install_validation_completed=1' \
  'installer_non_root_cli_validation_completed=1' \
  'installer_root_boundary_validation_completed=1' \
  'vm_invocation_performed=0' \
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

require_contains 'PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'multi_vm_evidence_intake_validator_present=1' "$readiness"
require_contains 'multi_vm_evidence_intake_validation_mode=no-effect-validation' "$readiness"
require_contains 'multi_vm_evidence_candidate_valid=0' "$readiness"
require_contains 'multi_vm_evidence_accepted_by_intake_validator=0' "$readiness"
require_contains 'multi_vm_evidence_intake_validator_present=1' "$ledger"
require_contains 'multi_vm_evidence_intake_validator_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' README.md
require_contains 'multi_vm_evidence_intake_validator' "$installer_page"

require_contains 'production-installer-multi-vm-evidence-intake-validator-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-multi-vm-evidence-intake-validator-contract.sh' Makefile
require_contains 'name: Production Installer Multi-VM Evidence Intake Validator' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-multi-vm-evidence-intake-validator-contract.sh' "$workflow"
require_absent 'sh scripts/production-installer-multi-vm-evidence-intake.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-multi-vm-evidence-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

fresh_vm="$tmp/fresh-vm-validation.txt"
repeat_vm="$tmp/repeat-vm-validation.txt"
existing_install="$tmp/existing-install-validation.txt"
remove_reinstall="$tmp/remove-reinstall-validation.txt"
unsupported_target="$tmp/unsupported-target-validation.txt"
non_root_cli="$tmp/non-root-cli-validation.txt"
root_boundary="$tmp/root-boundary-validation.txt"
checksum_verification="$tmp/checksum-verification.txt"
package_signature_verification="$tmp/package-signature-verification.txt"
bad_fresh_vm="$tmp/bad-fresh-vm-validation.txt"
fresh_vm_review="$tmp/fresh-vm-review.txt"
repeat_vm_review="$tmp/repeat-vm-review.txt"
existing_install_review="$tmp/existing-install-review.txt"
remove_reinstall_review="$tmp/remove-reinstall-review.txt"
unsupported_target_review="$tmp/unsupported-target-review.txt"
non_root_cli_review="$tmp/non-root-cli-review.txt"
root_boundary_review="$tmp/root-boundary-review.txt"
checksum_verification_review="$tmp/checksum-verification-review.txt"
package_signature_verification_review="$tmp/package-signature-verification-review.txt"
valid_evidence="$tmp/multi-vm-evidence.txt"
bad_hash_evidence="$tmp/multi-vm-bad-hash-evidence.txt"
placeholder_evidence="$tmp/multi-vm-placeholder-evidence.txt"

cat >"$fresh_vm" <<'FRESH_VM'
LATTICRA PRODUCTION INSTALLER FRESH VM VALIDATION EVIDENCE
fresh_vm_validation_evidence_present=1
fresh_disposable_fedora_vm_validation=1
installer_fresh_vm_validation_completed=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
FRESH_VM

cat >"$repeat_vm" <<'REPEAT_VM'
LATTICRA PRODUCTION INSTALLER REPEAT VM VALIDATION EVIDENCE
repeat_vm_validation_evidence_present=1
repeat_disposable_fedora_vm_validation=1
installer_repeat_vm_validation_completed=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
REPEAT_VM

cat >"$existing_install" <<'EXISTING_INSTALL'
LATTICRA PRODUCTION INSTALLER EXISTING INSTALL VALIDATION EVIDENCE
existing_install_validation_evidence_present=1
existing_install_upgrade_validation=1
installer_existing_install_validation_completed=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
EXISTING_INSTALL

cat >"$remove_reinstall" <<'REMOVE_REINSTALL'
LATTICRA PRODUCTION INSTALLER REMOVE AND REINSTALL VALIDATION EVIDENCE
remove_reinstall_validation_evidence_present=1
remove_and_reinstall_validation=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
REMOVE_REINSTALL

cat >"$unsupported_target" <<'UNSUPPORTED_TARGET'
LATTICRA PRODUCTION INSTALLER UNSUPPORTED TARGET VALIDATION EVIDENCE
unsupported_target_validation_evidence_present=1
unsupported_target_block_validation=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
UNSUPPORTED_TARGET

cat >"$non_root_cli" <<'NON_ROOT_CLI'
LATTICRA PRODUCTION INSTALLER NON-ROOT CLI VALIDATION EVIDENCE
non_root_cli_validation_evidence_present=1
non_root_cli_use_validation=1
installer_non_root_cli_validation_completed=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
NON_ROOT_CLI

cat >"$root_boundary" <<'ROOT_BOUNDARY'
LATTICRA PRODUCTION INSTALLER ROOT BOUNDARY VALIDATION EVIDENCE
root_boundary_validation_evidence_present=1
root_boundary_validation=1
installer_root_boundary_validation_completed=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
ROOT_BOUNDARY

cat >"$checksum_verification" <<'CHECKSUM_VERIFICATION'
LATTICRA PRODUCTION INSTALLER CHECKSUM VERIFICATION EVIDENCE
checksum_verification_evidence_present=1
checksum_verification_validation=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
CHECKSUM_VERIFICATION

cat >"$package_signature_verification" <<'PACKAGE_SIGNATURE_VERIFICATION'
LATTICRA PRODUCTION INSTALLER PACKAGE SIGNATURE VERIFICATION EVIDENCE
package_signature_verification_evidence_present=1
package_signature_verification_validation=1
vm_invocation_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
PACKAGE_SIGNATURE_VERIFICATION

printf 'missing required multi-VM markers\n' >"$bad_fresh_vm"
printf 'fresh VM review fixture\n' >"$fresh_vm_review"
printf 'repeat VM review fixture\n' >"$repeat_vm_review"
printf 'existing install review fixture\n' >"$existing_install_review"
printf 'remove reinstall review fixture\n' >"$remove_reinstall_review"
printf 'unsupported target review fixture\n' >"$unsupported_target_review"
printf 'non-root CLI review fixture\n' >"$non_root_cli_review"
printf 'root boundary review fixture\n' >"$root_boundary_review"
printf 'checksum verification review fixture\n' >"$checksum_verification_review"
printf 'package signature verification review fixture\n' >"$package_signature_verification_review"

fresh_vm_sha="$(sha256_file "$fresh_vm")"
repeat_vm_sha="$(sha256_file "$repeat_vm")"
existing_install_sha="$(sha256_file "$existing_install")"
remove_reinstall_sha="$(sha256_file "$remove_reinstall")"
unsupported_target_sha="$(sha256_file "$unsupported_target")"
non_root_cli_sha="$(sha256_file "$non_root_cli")"
root_boundary_sha="$(sha256_file "$root_boundary")"
checksum_verification_sha="$(sha256_file "$checksum_verification")"
package_signature_verification_sha="$(sha256_file "$package_signature_verification")"
fresh_vm_review_sha="$(sha256_file "$fresh_vm_review")"
repeat_vm_review_sha="$(sha256_file "$repeat_vm_review")"
existing_install_review_sha="$(sha256_file "$existing_install_review")"
remove_reinstall_review_sha="$(sha256_file "$remove_reinstall_review")"
unsupported_target_review_sha="$(sha256_file "$unsupported_target_review")"
non_root_cli_review_sha="$(sha256_file "$non_root_cli_review")"
root_boundary_review_sha="$(sha256_file "$root_boundary_review")"
checksum_verification_review_sha="$(sha256_file "$checksum_verification_review")"
package_signature_verification_review_sha="$(sha256_file "$package_signature_verification_review")"

cat >"$valid_evidence" <<VALID_EVIDENCE
LATTICRA PRODUCTION INSTALLER MULTI-VM EVIDENCE
multi_vm_evidence_status=complete
fresh_vm_validation_evidence_present=1
repeat_vm_validation_evidence_present=1
existing_install_validation_evidence_present=1
remove_reinstall_validation_evidence_present=1
unsupported_target_validation_evidence_present=1
non_root_cli_validation_evidence_present=1
root_boundary_validation_evidence_present=1
checksum_verification_evidence_present=1
package_signature_verification_evidence_present=1
fresh_vm_validation_reviewed=1
repeat_vm_validation_reviewed=1
existing_install_validation_reviewed=1
remove_reinstall_validation_reviewed=1
unsupported_target_validation_reviewed=1
non_root_cli_validation_reviewed=1
root_boundary_validation_reviewed=1
checksum_verification_reviewed=1
package_signature_verification_reviewed=1
fresh_disposable_fedora_vm_validation=1
repeat_disposable_fedora_vm_validation=1
existing_install_upgrade_validation=1
remove_and_reinstall_validation=1
unsupported_target_block_validation=1
non_root_cli_use_validation=1
root_boundary_validation=1
checksum_verification_validation=1
package_signature_verification_validation=1
installer_multi_vm_validation_completed=1
installer_fresh_vm_validation_completed=1
installer_repeat_vm_validation_completed=1
installer_existing_install_validation_completed=1
installer_non_root_cli_validation_completed=1
installer_root_boundary_validation_completed=1
fresh_vm_validation_sha256=$fresh_vm_sha
repeat_vm_validation_sha256=$repeat_vm_sha
existing_install_validation_sha256=$existing_install_sha
remove_reinstall_validation_sha256=$remove_reinstall_sha
unsupported_target_validation_sha256=$unsupported_target_sha
non_root_cli_validation_sha256=$non_root_cli_sha
root_boundary_validation_sha256=$root_boundary_sha
checksum_verification_sha256=$checksum_verification_sha
package_signature_verification_sha256=$package_signature_verification_sha
fresh_vm_validation_review_sha256=$fresh_vm_review_sha
repeat_vm_validation_review_sha256=$repeat_vm_review_sha
existing_install_validation_review_sha256=$existing_install_review_sha
remove_reinstall_validation_review_sha256=$remove_reinstall_review_sha
unsupported_target_validation_review_sha256=$unsupported_target_review_sha
non_root_cli_validation_review_sha256=$non_root_cli_review_sha
root_boundary_validation_review_sha256=$root_boundary_review_sha
checksum_verification_review_sha256=$checksum_verification_review_sha
package_signature_verification_review_sha256=$package_signature_verification_review_sha
vm_invocation_performed=0
install_performed=0
uninstall_performed=0
upgrade_performed=0
rollback_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
VALID_EVIDENCE

sed "s/$fresh_vm_sha/0000000000000000000000000000000000000000000000000000000000000000/" "$valid_evidence" >"$bad_hash_evidence"
cp "$valid_evidence" "$placeholder_evidence"
printf '%s\n' 'fresh_vm_validation_review_reference=<required-review-id>' >>"$placeholder_evidence"

output="$(sh "$script" \
  --fresh-vm "$fresh_vm" \
  --repeat-vm "$repeat_vm" \
  --existing-install "$existing_install" \
  --remove-reinstall "$remove_reinstall" \
  --unsupported-target "$unsupported_target" \
  --non-root-cli "$non_root_cli" \
  --root-boundary "$root_boundary" \
  --checksum-verification "$checksum_verification" \
  --package-signature-verification "$package_signature_verification" \
  --fresh-vm-review "$fresh_vm_review" \
  --repeat-vm-review "$repeat_vm_review" \
  --existing-install-review "$existing_install_review" \
  --remove-reinstall-review "$remove_reinstall_review" \
  --unsupported-target-review "$unsupported_target_review" \
  --non-root-cli-review "$non_root_cli_review" \
  --root-boundary-review "$root_boundary_review" \
  --checksum-verification-review "$checksum_verification_review" \
  --package-signature-verification-review "$package_signature_verification_review" \
  --evidence "$valid_evidence")"

require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER MULTI-VM EVIDENCE INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'multi_vm_evidence_intake_validator_present=1'
require_output_contains "$output" 'multi_vm_evidence_candidate_valid=1'
require_output_contains "$output" "candidate_fresh_vm_validation_sha256=$fresh_vm_sha"
require_output_contains "$output" "candidate_repeat_vm_validation_sha256=$repeat_vm_sha"
require_output_contains "$output" "candidate_existing_install_validation_sha256=$existing_install_sha"
require_output_contains "$output" "candidate_remove_reinstall_validation_sha256=$remove_reinstall_sha"
require_output_contains "$output" "candidate_unsupported_target_validation_sha256=$unsupported_target_sha"
require_output_contains "$output" "candidate_non_root_cli_validation_sha256=$non_root_cli_sha"
require_output_contains "$output" "candidate_root_boundary_validation_sha256=$root_boundary_sha"
require_output_contains "$output" "candidate_checksum_verification_sha256=$checksum_verification_sha"
require_output_contains "$output" "candidate_package_signature_verification_sha256=$package_signature_verification_sha"
require_output_contains "$output" "candidate_fresh_vm_validation_review_sha256=$fresh_vm_review_sha"
require_output_contains "$output" "candidate_package_signature_verification_review_sha256=$package_signature_verification_review_sha"
require_output_contains "$output" 'multi_vm_evidence_accepted_by_intake_validator=0'
require_output_contains "$output" 'multi_vm_evidence_written_by_intake_validator=0'
require_output_contains "$output" 'installer_multi_vm_promotion_allowed_by_intake_validator_alone=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'installer_multi_vm_validation_completed=0'
require_output_contains "$output" 'installer_fresh_vm_validation_completed=0'
require_output_contains "$output" 'installer_root_boundary_validation_completed=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" \
  --fresh-vm "$bad_fresh_vm" \
  --repeat-vm "$repeat_vm" \
  --existing-install "$existing_install" \
  --remove-reinstall "$remove_reinstall" \
  --unsupported-target "$unsupported_target" \
  --non-root-cli "$non_root_cli" \
  --root-boundary "$root_boundary" \
  --checksum-verification "$checksum_verification" \
  --package-signature-verification "$package_signature_verification" \
  --fresh-vm-review "$fresh_vm_review" \
  --repeat-vm-review "$repeat_vm_review" \
  --existing-install-review "$existing_install_review" \
  --remove-reinstall-review "$remove_reinstall_review" \
  --unsupported-target-review "$unsupported_target_review" \
  --non-root-cli-review "$non_root_cli_review" \
  --root-boundary-review "$root_boundary_review" \
  --checksum-verification-review "$checksum_verification_review" \
  --package-signature-verification-review "$package_signature_verification_review" \
  --evidence "$valid_evidence" >/dev/null 2>&1; then
  fail 'bad fresh VM validation evidence unexpectedly passed validation'
fi

if sh "$script" \
  --fresh-vm "$fresh_vm" \
  --repeat-vm "$repeat_vm" \
  --existing-install "$existing_install" \
  --remove-reinstall "$remove_reinstall" \
  --unsupported-target "$unsupported_target" \
  --non-root-cli "$non_root_cli" \
  --root-boundary "$root_boundary" \
  --checksum-verification "$checksum_verification" \
  --package-signature-verification "$package_signature_verification" \
  --fresh-vm-review "$fresh_vm_review" \
  --repeat-vm-review "$repeat_vm_review" \
  --existing-install-review "$existing_install_review" \
  --remove-reinstall-review "$remove_reinstall_review" \
  --unsupported-target-review "$unsupported_target_review" \
  --non-root-cli-review "$non_root_cli_review" \
  --root-boundary-review "$root_boundary_review" \
  --checksum-verification-review "$checksum_verification_review" \
  --package-signature-verification-review "$package_signature_verification_review" \
  --evidence "$bad_hash_evidence" >/dev/null 2>&1; then
  fail 'bad-hash multi-VM evidence unexpectedly passed validation'
fi

if sh "$script" \
  --fresh-vm "$fresh_vm" \
  --repeat-vm "$repeat_vm" \
  --existing-install "$existing_install" \
  --remove-reinstall "$remove_reinstall" \
  --unsupported-target "$unsupported_target" \
  --non-root-cli "$non_root_cli" \
  --root-boundary "$root_boundary" \
  --checksum-verification "$checksum_verification" \
  --package-signature-verification "$package_signature_verification" \
  --fresh-vm-review "$fresh_vm_review" \
  --repeat-vm-review "$repeat_vm_review" \
  --existing-install-review "$existing_install_review" \
  --remove-reinstall-review "$remove_reinstall_review" \
  --unsupported-target-review "$unsupported_target_review" \
  --non-root-cli-review "$non_root_cli_review" \
  --root-boundary-review "$root_boundary_review" \
  --checksum-verification-review "$checksum_verification_review" \
  --package-signature-verification-review "$package_signature_verification_review" \
  --evidence "$placeholder_evidence" >/dev/null 2>&1; then
  fail 'placeholder multi-VM evidence unexpectedly passed validation'
fi

printf 'production_installer_multi_vm_evidence_intake_validator_contract: ok\n'
