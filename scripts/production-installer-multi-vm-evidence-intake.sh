#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-multi-vm-evidence-intake.sh \
    --fresh-vm <path> \
    --repeat-vm <path> \
    --existing-install <path> \
    --remove-reinstall <path> \
    --unsupported-target <path> \
    --non-root-cli <path> \
    --root-boundary <path> \
    --checksum-verification <path> \
    --package-signature-verification <path> \
    --fresh-vm-review <path> \
    --repeat-vm-review <path> \
    --existing-install-review <path> \
    --remove-reinstall-review <path> \
    --unsupported-target-review <path> \
    --non-root-cli-review <path> \
    --root-boundary-review <path> \
    --checksum-verification-review <path> \
    --package-signature-verification-review <path> \
    --evidence <path>

Validates a future production-installer multi-VM evidence bundle.
It checks local file presence, multi-VM evidence markers, review hashes,
required evidence fields, and placeholder absence. It does not run VMs,
install, uninstall, upgrade, rollback, invoke a package manager, accept
evidence, pass promotion, or mutate the host.
USAGE
}

fail() {
  printf 'production installer multi-VM evidence intake: %s\n' "$1" >&2
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
    fail "placeholder value is not acceptable in multi-VM evidence"
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

FRESH_VM=''
REPEAT_VM=''
EXISTING_INSTALL=''
REMOVE_REINSTALL=''
UNSUPPORTED_TARGET=''
NON_ROOT_CLI=''
ROOT_BOUNDARY=''
CHECKSUM_VERIFICATION=''
PACKAGE_SIGNATURE_VERIFICATION=''
FRESH_VM_REVIEW=''
REPEAT_VM_REVIEW=''
EXISTING_INSTALL_REVIEW=''
REMOVE_REINSTALL_REVIEW=''
UNSUPPORTED_TARGET_REVIEW=''
NON_ROOT_CLI_REVIEW=''
ROOT_BOUNDARY_REVIEW=''
CHECKSUM_VERIFICATION_REVIEW=''
PACKAGE_SIGNATURE_VERIFICATION_REVIEW=''
EVIDENCE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --fresh-vm)
      [ "$#" -ge 2 ] || fail 'missing value for --fresh-vm' 64
      FRESH_VM="$2"
      shift 2
      ;;
    --repeat-vm)
      [ "$#" -ge 2 ] || fail 'missing value for --repeat-vm' 64
      REPEAT_VM="$2"
      shift 2
      ;;
    --existing-install)
      [ "$#" -ge 2 ] || fail 'missing value for --existing-install' 64
      EXISTING_INSTALL="$2"
      shift 2
      ;;
    --remove-reinstall)
      [ "$#" -ge 2 ] || fail 'missing value for --remove-reinstall' 64
      REMOVE_REINSTALL="$2"
      shift 2
      ;;
    --unsupported-target)
      [ "$#" -ge 2 ] || fail 'missing value for --unsupported-target' 64
      UNSUPPORTED_TARGET="$2"
      shift 2
      ;;
    --non-root-cli)
      [ "$#" -ge 2 ] || fail 'missing value for --non-root-cli' 64
      NON_ROOT_CLI="$2"
      shift 2
      ;;
    --root-boundary)
      [ "$#" -ge 2 ] || fail 'missing value for --root-boundary' 64
      ROOT_BOUNDARY="$2"
      shift 2
      ;;
    --checksum-verification)
      [ "$#" -ge 2 ] || fail 'missing value for --checksum-verification' 64
      CHECKSUM_VERIFICATION="$2"
      shift 2
      ;;
    --package-signature-verification)
      [ "$#" -ge 2 ] || fail 'missing value for --package-signature-verification' 64
      PACKAGE_SIGNATURE_VERIFICATION="$2"
      shift 2
      ;;
    --fresh-vm-review)
      [ "$#" -ge 2 ] || fail 'missing value for --fresh-vm-review' 64
      FRESH_VM_REVIEW="$2"
      shift 2
      ;;
    --repeat-vm-review)
      [ "$#" -ge 2 ] || fail 'missing value for --repeat-vm-review' 64
      REPEAT_VM_REVIEW="$2"
      shift 2
      ;;
    --existing-install-review)
      [ "$#" -ge 2 ] || fail 'missing value for --existing-install-review' 64
      EXISTING_INSTALL_REVIEW="$2"
      shift 2
      ;;
    --remove-reinstall-review)
      [ "$#" -ge 2 ] || fail 'missing value for --remove-reinstall-review' 64
      REMOVE_REINSTALL_REVIEW="$2"
      shift 2
      ;;
    --unsupported-target-review)
      [ "$#" -ge 2 ] || fail 'missing value for --unsupported-target-review' 64
      UNSUPPORTED_TARGET_REVIEW="$2"
      shift 2
      ;;
    --non-root-cli-review)
      [ "$#" -ge 2 ] || fail 'missing value for --non-root-cli-review' 64
      NON_ROOT_CLI_REVIEW="$2"
      shift 2
      ;;
    --root-boundary-review)
      [ "$#" -ge 2 ] || fail 'missing value for --root-boundary-review' 64
      ROOT_BOUNDARY_REVIEW="$2"
      shift 2
      ;;
    --checksum-verification-review)
      [ "$#" -ge 2 ] || fail 'missing value for --checksum-verification-review' 64
      CHECKSUM_VERIFICATION_REVIEW="$2"
      shift 2
      ;;
    --package-signature-verification-review)
      [ "$#" -ge 2 ] || fail 'missing value for --package-signature-verification-review' 64
      PACKAGE_SIGNATURE_VERIFICATION_REVIEW="$2"
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

[ -n "$FRESH_VM" ] || fail 'missing --fresh-vm path' 64
[ -n "$REPEAT_VM" ] || fail 'missing --repeat-vm path' 64
[ -n "$EXISTING_INSTALL" ] || fail 'missing --existing-install path' 64
[ -n "$REMOVE_REINSTALL" ] || fail 'missing --remove-reinstall path' 64
[ -n "$UNSUPPORTED_TARGET" ] || fail 'missing --unsupported-target path' 64
[ -n "$NON_ROOT_CLI" ] || fail 'missing --non-root-cli path' 64
[ -n "$ROOT_BOUNDARY" ] || fail 'missing --root-boundary path' 64
[ -n "$CHECKSUM_VERIFICATION" ] || fail 'missing --checksum-verification path' 64
[ -n "$PACKAGE_SIGNATURE_VERIFICATION" ] || fail 'missing --package-signature-verification path' 64
[ -n "$FRESH_VM_REVIEW" ] || fail 'missing --fresh-vm-review path' 64
[ -n "$REPEAT_VM_REVIEW" ] || fail 'missing --repeat-vm-review path' 64
[ -n "$EXISTING_INSTALL_REVIEW" ] || fail 'missing --existing-install-review path' 64
[ -n "$REMOVE_REINSTALL_REVIEW" ] || fail 'missing --remove-reinstall-review path' 64
[ -n "$UNSUPPORTED_TARGET_REVIEW" ] || fail 'missing --unsupported-target-review path' 64
[ -n "$NON_ROOT_CLI_REVIEW" ] || fail 'missing --non-root-cli-review path' 64
[ -n "$ROOT_BOUNDARY_REVIEW" ] || fail 'missing --root-boundary-review path' 64
[ -n "$CHECKSUM_VERIFICATION_REVIEW" ] || fail 'missing --checksum-verification-review path' 64
[ -n "$PACKAGE_SIGNATURE_VERIFICATION_REVIEW" ] || fail 'missing --package-signature-verification-review path' 64
[ -n "$EVIDENCE" ] || fail 'missing --evidence path' 64

for file in "$FRESH_VM" "$REPEAT_VM" "$EXISTING_INSTALL" "$REMOVE_REINSTALL" "$UNSUPPORTED_TARGET" "$NON_ROOT_CLI" "$ROOT_BOUNDARY" "$CHECKSUM_VERIFICATION" "$PACKAGE_SIGNATURE_VERIFICATION" "$FRESH_VM_REVIEW" "$REPEAT_VM_REVIEW" "$EXISTING_INSTALL_REVIEW" "$REMOVE_REINSTALL_REVIEW" "$UNSUPPORTED_TARGET_REVIEW" "$NON_ROOT_CLI_REVIEW" "$ROOT_BOUNDARY_REVIEW" "$CHECKSUM_VERIFICATION_REVIEW" "$PACKAGE_SIGNATURE_VERIFICATION_REVIEW" "$EVIDENCE"
do
  require_nonempty_file "$file"
done

require_file docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_MULTI_VM_VALIDATION_STATUS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_file scripts/production-installer-multi-vm-validation-status.sh
require_file docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_file README.md

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'production_installer_multi_vm_validation_status_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_multi_vm_validation_status_no_effect=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'fresh_vm_validation_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'repeat_vm_validation_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'existing_install_validation_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'remove_reinstall_validation_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'unsupported_target_validation_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'non_root_cli_validation_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'root_boundary_validation_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'checksum_verification_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'package_signature_verification_evidence_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'fresh_vm_validation_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'repeat_vm_validation_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'existing_install_validation_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'remove_reinstall_validation_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'unsupported_target_validation_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'non_root_cli_validation_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'root_boundary_validation_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'checksum_verification_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'package_signature_verification_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_multi_vm_validation_completed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'Status: no-effect installer multi-VM validation status contract' docs/PRODUCTION_INSTALLER_MULTI_VM_VALIDATION_STATUS_CONTRACT.md
require_contains 'recovery_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'lifecycle_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

require_contains 'LATTICRA PRODUCTION INSTALLER FRESH VM VALIDATION EVIDENCE' "$FRESH_VM"
require_contains 'fresh_vm_validation_evidence_present=1' "$FRESH_VM"
require_contains 'fresh_disposable_fedora_vm_validation=1' "$FRESH_VM"
require_contains 'installer_fresh_vm_validation_completed=1' "$FRESH_VM"

require_contains 'LATTICRA PRODUCTION INSTALLER REPEAT VM VALIDATION EVIDENCE' "$REPEAT_VM"
require_contains 'repeat_vm_validation_evidence_present=1' "$REPEAT_VM"
require_contains 'repeat_disposable_fedora_vm_validation=1' "$REPEAT_VM"
require_contains 'installer_repeat_vm_validation_completed=1' "$REPEAT_VM"

require_contains 'LATTICRA PRODUCTION INSTALLER EXISTING INSTALL VALIDATION EVIDENCE' "$EXISTING_INSTALL"
require_contains 'existing_install_validation_evidence_present=1' "$EXISTING_INSTALL"
require_contains 'existing_install_upgrade_validation=1' "$EXISTING_INSTALL"
require_contains 'installer_existing_install_validation_completed=1' "$EXISTING_INSTALL"

require_contains 'LATTICRA PRODUCTION INSTALLER REMOVE AND REINSTALL VALIDATION EVIDENCE' "$REMOVE_REINSTALL"
require_contains 'remove_reinstall_validation_evidence_present=1' "$REMOVE_REINSTALL"
require_contains 'remove_and_reinstall_validation=1' "$REMOVE_REINSTALL"

require_contains 'LATTICRA PRODUCTION INSTALLER UNSUPPORTED TARGET VALIDATION EVIDENCE' "$UNSUPPORTED_TARGET"
require_contains 'unsupported_target_validation_evidence_present=1' "$UNSUPPORTED_TARGET"
require_contains 'unsupported_target_block_validation=1' "$UNSUPPORTED_TARGET"

require_contains 'LATTICRA PRODUCTION INSTALLER NON-ROOT CLI VALIDATION EVIDENCE' "$NON_ROOT_CLI"
require_contains 'non_root_cli_validation_evidence_present=1' "$NON_ROOT_CLI"
require_contains 'non_root_cli_use_validation=1' "$NON_ROOT_CLI"
require_contains 'installer_non_root_cli_validation_completed=1' "$NON_ROOT_CLI"

require_contains 'LATTICRA PRODUCTION INSTALLER ROOT BOUNDARY VALIDATION EVIDENCE' "$ROOT_BOUNDARY"
require_contains 'root_boundary_validation_evidence_present=1' "$ROOT_BOUNDARY"
require_contains 'root_boundary_validation=1' "$ROOT_BOUNDARY"
require_contains 'installer_root_boundary_validation_completed=1' "$ROOT_BOUNDARY"

require_contains 'LATTICRA PRODUCTION INSTALLER CHECKSUM VERIFICATION EVIDENCE' "$CHECKSUM_VERIFICATION"
require_contains 'checksum_verification_evidence_present=1' "$CHECKSUM_VERIFICATION"
require_contains 'checksum_verification_validation=1' "$CHECKSUM_VERIFICATION"

require_contains 'LATTICRA PRODUCTION INSTALLER PACKAGE SIGNATURE VERIFICATION EVIDENCE' "$PACKAGE_SIGNATURE_VERIFICATION"
require_contains 'package_signature_verification_evidence_present=1' "$PACKAGE_SIGNATURE_VERIFICATION"
require_contains 'package_signature_verification_validation=1' "$PACKAGE_SIGNATURE_VERIFICATION"

for evidence_file in "$FRESH_VM" "$REPEAT_VM" "$EXISTING_INSTALL" "$REMOVE_REINSTALL" "$UNSUPPORTED_TARGET" "$NON_ROOT_CLI" "$ROOT_BOUNDARY" "$CHECKSUM_VERIFICATION" "$PACKAGE_SIGNATURE_VERIFICATION"
do
  require_contains 'vm_invocation_performed=0' "$evidence_file"
  require_contains 'package_manager_invoked=0' "$evidence_file"
  require_contains 'host_mutation_performed=0' "$evidence_file"
  require_contains 'network_allowed=0' "$evidence_file"
done

fresh_vm_sha256="$(sha256_file "$FRESH_VM")"
repeat_vm_sha256="$(sha256_file "$REPEAT_VM")"
existing_install_sha256="$(sha256_file "$EXISTING_INSTALL")"
remove_reinstall_sha256="$(sha256_file "$REMOVE_REINSTALL")"
unsupported_target_sha256="$(sha256_file "$UNSUPPORTED_TARGET")"
non_root_cli_sha256="$(sha256_file "$NON_ROOT_CLI")"
root_boundary_sha256="$(sha256_file "$ROOT_BOUNDARY")"
checksum_verification_sha256="$(sha256_file "$CHECKSUM_VERIFICATION")"
package_signature_verification_sha256="$(sha256_file "$PACKAGE_SIGNATURE_VERIFICATION")"
fresh_vm_review_sha256="$(sha256_file "$FRESH_VM_REVIEW")"
repeat_vm_review_sha256="$(sha256_file "$REPEAT_VM_REVIEW")"
existing_install_review_sha256="$(sha256_file "$EXISTING_INSTALL_REVIEW")"
remove_reinstall_review_sha256="$(sha256_file "$REMOVE_REINSTALL_REVIEW")"
unsupported_target_review_sha256="$(sha256_file "$UNSUPPORTED_TARGET_REVIEW")"
non_root_cli_review_sha256="$(sha256_file "$NON_ROOT_CLI_REVIEW")"
root_boundary_review_sha256="$(sha256_file "$ROOT_BOUNDARY_REVIEW")"
checksum_verification_review_sha256="$(sha256_file "$CHECKSUM_VERIFICATION_REVIEW")"
package_signature_verification_review_sha256="$(sha256_file "$PACKAGE_SIGNATURE_VERIFICATION_REVIEW")"

require_digest "$fresh_vm_sha256" 'fresh VM validation evidence'
require_digest "$repeat_vm_sha256" 'repeat VM validation evidence'
require_digest "$existing_install_sha256" 'existing-install validation evidence'
require_digest "$remove_reinstall_sha256" 'remove-reinstall validation evidence'
require_digest "$unsupported_target_sha256" 'unsupported-target validation evidence'
require_digest "$non_root_cli_sha256" 'non-root CLI validation evidence'
require_digest "$root_boundary_sha256" 'root-boundary validation evidence'
require_digest "$checksum_verification_sha256" 'checksum verification evidence'
require_digest "$package_signature_verification_sha256" 'package-signature verification evidence'
require_digest "$fresh_vm_review_sha256" 'fresh VM review'
require_digest "$repeat_vm_review_sha256" 'repeat VM review'
require_digest "$existing_install_review_sha256" 'existing-install review'
require_digest "$remove_reinstall_review_sha256" 'remove-reinstall review'
require_digest "$unsupported_target_review_sha256" 'unsupported-target review'
require_digest "$non_root_cli_review_sha256" 'non-root CLI review'
require_digest "$root_boundary_review_sha256" 'root-boundary review'
require_digest "$checksum_verification_review_sha256" 'checksum verification review'
require_digest "$package_signature_verification_review_sha256" 'package-signature verification review'

for marker in \
  'LATTICRA PRODUCTION INSTALLER MULTI-VM EVIDENCE' \
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
  "fresh_vm_validation_sha256=$fresh_vm_sha256" \
  "repeat_vm_validation_sha256=$repeat_vm_sha256" \
  "existing_install_validation_sha256=$existing_install_sha256" \
  "remove_reinstall_validation_sha256=$remove_reinstall_sha256" \
  "unsupported_target_validation_sha256=$unsupported_target_sha256" \
  "non_root_cli_validation_sha256=$non_root_cli_sha256" \
  "root_boundary_validation_sha256=$root_boundary_sha256" \
  "checksum_verification_sha256=$checksum_verification_sha256" \
  "package_signature_verification_sha256=$package_signature_verification_sha256" \
  "fresh_vm_validation_review_sha256=$fresh_vm_review_sha256" \
  "repeat_vm_validation_review_sha256=$repeat_vm_review_sha256" \
  "existing_install_validation_review_sha256=$existing_install_review_sha256" \
  "remove_reinstall_validation_review_sha256=$remove_reinstall_review_sha256" \
  "unsupported_target_validation_review_sha256=$unsupported_target_review_sha256" \
  "non_root_cli_validation_review_sha256=$non_root_cli_review_sha256" \
  "root_boundary_validation_review_sha256=$root_boundary_review_sha256" \
  "checksum_verification_review_sha256=$checksum_verification_review_sha256" \
  "package_signature_verification_review_sha256=$package_signature_verification_review_sha256" \
  'vm_invocation_performed=0' \
  'install_performed=0' \
  'uninstall_performed=0' \
  'upgrade_performed=0' \
  'rollback_performed=0' \
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

for file in "$FRESH_VM" "$REPEAT_VM" "$EXISTING_INSTALL" "$REMOVE_REINSTALL" "$UNSUPPORTED_TARGET" "$NON_ROOT_CLI" "$ROOT_BOUNDARY" "$CHECKSUM_VERIFICATION" "$PACKAGE_SIGNATURE_VERIFICATION" "$FRESH_VM_REVIEW" "$REPEAT_VM_REVIEW" "$EXISTING_INSTALL_REVIEW" "$REMOVE_REINSTALL_REVIEW" "$UNSUPPORTED_TARGET_REVIEW" "$NON_ROOT_CLI_REVIEW" "$ROOT_BOUNDARY_REVIEW" "$CHECKSUM_VERIFICATION_REVIEW" "$PACKAGE_SIGNATURE_VERIFICATION_REVIEW" "$EVIDENCE"
do
  reject_placeholders "$file"
done

for forbidden_claim in \
  'multi_vm_evidence_accepted_by_intake_validator=1' \
  'multi_vm_evidence_written_by_intake_validator=1' \
  'installer_multi_vm_promotion_allowed_by_intake_validator_alone=1' \
  'release_artifact_promotion_gate_passed=1' \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'vm_invocation_performed=1' \
  'install_performed=1' \
  'uninstall_performed=1' \
  'upgrade_performed=1' \
  'rollback_performed=1' \
  'package_manager_invoked=1' \
  'host_mutation_performed=1' \
  'network_allowed=1'
do
  for file in "$FRESH_VM" "$REPEAT_VM" "$EXISTING_INSTALL" "$REMOVE_REINSTALL" "$UNSUPPORTED_TARGET" "$NON_ROOT_CLI" "$ROOT_BOUNDARY" "$CHECKSUM_VERIFICATION" "$PACKAGE_SIGNATURE_VERIFICATION" "$FRESH_VM_REVIEW" "$REPEAT_VM_REVIEW" "$EXISTING_INSTALL_REVIEW" "$REMOVE_REINSTALL_REVIEW" "$UNSUPPORTED_TARGET_REVIEW" "$NON_ROOT_CLI_REVIEW" "$ROOT_BOUNDARY_REVIEW" "$CHECKSUM_VERIFICATION_REVIEW" "$PACKAGE_SIGNATURE_VERIFICATION_REVIEW" "$EVIDENCE"
  do
    require_absent "$forbidden_claim" "$file"
  done
done

cat <<REPORT
LATTICRA PRODUCTION INSTALLER MULTI-VM EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
multi_vm_evidence_intake_validator_present=1
multi_vm_evidence_intake_validation_mode=no-effect-validation
multi_vm_evidence_candidate_valid=1
fresh_vm_validation_file_present=1
repeat_vm_validation_file_present=1
existing_install_validation_file_present=1
remove_reinstall_validation_file_present=1
unsupported_target_validation_file_present=1
non_root_cli_validation_file_present=1
root_boundary_validation_file_present=1
checksum_verification_file_present=1
package_signature_verification_file_present=1
fresh_vm_validation_sha256_recorded=1
repeat_vm_validation_sha256_recorded=1
existing_install_validation_sha256_recorded=1
remove_reinstall_validation_sha256_recorded=1
unsupported_target_validation_sha256_recorded=1
non_root_cli_validation_sha256_recorded=1
root_boundary_validation_sha256_recorded=1
checksum_verification_sha256_recorded=1
package_signature_verification_sha256_recorded=1
candidate_fresh_vm_validation_sha256=$fresh_vm_sha256
candidate_repeat_vm_validation_sha256=$repeat_vm_sha256
candidate_existing_install_validation_sha256=$existing_install_sha256
candidate_remove_reinstall_validation_sha256=$remove_reinstall_sha256
candidate_unsupported_target_validation_sha256=$unsupported_target_sha256
candidate_non_root_cli_validation_sha256=$non_root_cli_sha256
candidate_root_boundary_validation_sha256=$root_boundary_sha256
candidate_checksum_verification_sha256=$checksum_verification_sha256
candidate_package_signature_verification_sha256=$package_signature_verification_sha256
candidate_fresh_vm_validation_review_sha256=$fresh_vm_review_sha256
candidate_repeat_vm_validation_review_sha256=$repeat_vm_review_sha256
candidate_existing_install_validation_review_sha256=$existing_install_review_sha256
candidate_remove_reinstall_validation_review_sha256=$remove_reinstall_review_sha256
candidate_unsupported_target_validation_review_sha256=$unsupported_target_review_sha256
candidate_non_root_cli_validation_review_sha256=$non_root_cli_review_sha256
candidate_root_boundary_validation_review_sha256=$root_boundary_review_sha256
candidate_checksum_verification_review_sha256=$checksum_verification_review_sha256
candidate_package_signature_verification_review_sha256=$package_signature_verification_review_sha256
candidate_fresh_vm_validation_reviewed=1
candidate_repeat_vm_validation_reviewed=1
candidate_existing_install_validation_reviewed=1
candidate_remove_reinstall_validation_reviewed=1
candidate_unsupported_target_validation_reviewed=1
candidate_non_root_cli_validation_reviewed=1
candidate_root_boundary_validation_reviewed=1
candidate_checksum_verification_reviewed=1
candidate_package_signature_verification_reviewed=1
candidate_installer_multi_vm_validation_completed=1
candidate_installer_fresh_vm_validation_completed=1
candidate_installer_repeat_vm_validation_completed=1
candidate_installer_existing_install_validation_completed=1
candidate_installer_non_root_cli_validation_completed=1
candidate_installer_root_boundary_validation_completed=1
multi_vm_evidence_accepted_by_intake_validator=0
multi_vm_evidence_written_by_intake_validator=0
installer_multi_vm_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_multi_vm_validation_completed=0
installer_fresh_vm_validation_completed=0
installer_repeat_vm_validation_completed=0
installer_existing_install_validation_completed=0
installer_non_root_cli_validation_completed=0
installer_root_boundary_validation_completed=0
vm_invocation_performed=0
install_performed=0
uninstall_performed=0
upgrade_performed=0
rollback_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
