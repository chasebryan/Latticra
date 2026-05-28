# Production Installer Multi-VM Evidence Intake Validator Contract

Status: no-effect multi-VM evidence intake validator contract
Evidence level: 10 target, evidence intake validator only
Scope: validate a future production-installer multi-VM evidence bundle without running VMs, installing, uninstalling, upgrading, rolling back, invoking a package manager, accepting evidence, passing promotion, or mutating a host.

## Purpose

The production-installer multi-VM validation status is present and blocked because no reviewed fresh VM, repeat VM, existing-install upgrade, remove-and-reinstall, unsupported-target block, non-root CLI, root-boundary, checksum verification, or package-signature verification evidence exists for a tagged release artifact candidate.

This contract adds a no-effect intake validator for that future multi-VM evidence bundle. The validator checks local evidence markers, review evidence, and hash consistency between the supplied files and the evidence manifest.

It does not accept the evidence, write status, pass the release-artifact promotion gate, or claim production installer readiness.

## Command

```sh
sh scripts/production-installer-multi-vm-evidence-intake.sh \
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
```

## Current classification

```text
multi_vm_evidence_intake_validator_present=1
multi_vm_evidence_intake_validation_mode=no-effect-validation
multi_vm_evidence_candidate_valid=0
fresh_vm_validation_file_present=0
repeat_vm_validation_file_present=0
existing_install_validation_file_present=0
remove_reinstall_validation_file_present=0
unsupported_target_validation_file_present=0
non_root_cli_validation_file_present=0
root_boundary_validation_file_present=0
checksum_verification_file_present=0
package_signature_verification_file_present=0
fresh_vm_validation_sha256_recorded=0
repeat_vm_validation_sha256_recorded=0
existing_install_validation_sha256_recorded=0
remove_reinstall_validation_sha256_recorded=0
unsupported_target_validation_sha256_recorded=0
non_root_cli_validation_sha256_recorded=0
root_boundary_validation_sha256_recorded=0
checksum_verification_sha256_recorded=0
package_signature_verification_sha256_recorded=0
fresh_vm_validation_review_present=0
repeat_vm_validation_review_present=0
existing_install_validation_review_present=0
remove_reinstall_validation_review_present=0
unsupported_target_validation_review_present=0
non_root_cli_validation_review_present=0
root_boundary_validation_review_present=0
checksum_verification_review_present=0
package_signature_verification_review_present=0
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
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Required source records

The validator binds the current blocked multi-VM posture:

```text
production_installer_ready=0
release_artifact_promotion_gate_passed=0
production_installer_multi_vm_validation_status_present=1
installer_multi_vm_validation_status_no_effect=1
fresh_vm_validation_evidence_present=0
repeat_vm_validation_evidence_present=0
existing_install_validation_evidence_present=0
remove_reinstall_validation_evidence_present=0
unsupported_target_validation_evidence_present=0
non_root_cli_validation_evidence_present=0
root_boundary_validation_evidence_present=0
checksum_verification_evidence_present=0
package_signature_verification_evidence_present=0
fresh_vm_validation_reviewed=0
repeat_vm_validation_reviewed=0
existing_install_validation_reviewed=0
remove_reinstall_validation_reviewed=0
unsupported_target_validation_reviewed=0
non_root_cli_validation_reviewed=0
root_boundary_validation_reviewed=0
checksum_verification_reviewed=0
package_signature_verification_reviewed=0
installer_multi_vm_validation_completed=0
installer_fresh_vm_validation_completed=0
installer_repeat_vm_validation_completed=0
installer_existing_install_validation_completed=0
installer_non_root_cli_validation_completed=0
installer_root_boundary_validation_completed=0
```

It reads these local records:

```text
docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
docs/PRODUCTION_INSTALLER_MULTI_VM_VALIDATION_STATUS_CONTRACT.md
docs/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
scripts/production-installer-multi-vm-validation-status.sh
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
README.md
```

## Candidate requirements

A candidate evidence bundle must include all of the following, and the hash fields must match the supplied local files:

```text
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
fresh_vm_validation_sha256=<actual-fresh-vm-validation-sha256>
repeat_vm_validation_sha256=<actual-repeat-vm-validation-sha256>
existing_install_validation_sha256=<actual-existing-install-validation-sha256>
remove_reinstall_validation_sha256=<actual-remove-reinstall-validation-sha256>
unsupported_target_validation_sha256=<actual-unsupported-target-validation-sha256>
non_root_cli_validation_sha256=<actual-non-root-cli-validation-sha256>
root_boundary_validation_sha256=<actual-root-boundary-validation-sha256>
checksum_verification_sha256=<actual-checksum-verification-sha256>
package_signature_verification_sha256=<actual-package-signature-verification-sha256>
fresh_vm_validation_review_sha256=<actual-fresh-vm-review-sha256>
repeat_vm_validation_review_sha256=<actual-repeat-vm-review-sha256>
existing_install_validation_review_sha256=<actual-existing-install-review-sha256>
remove_reinstall_validation_review_sha256=<actual-remove-reinstall-review-sha256>
unsupported_target_validation_review_sha256=<actual-unsupported-target-review-sha256>
non_root_cli_validation_review_sha256=<actual-non-root-cli-review-sha256>
root_boundary_validation_review_sha256=<actual-root-boundary-review-sha256>
checksum_verification_review_sha256=<actual-checksum-verification-review-sha256>
package_signature_verification_review_sha256=<actual-package-signature-verification-review-sha256>
vm_invocation_performed=0
install_performed=0
uninstall_performed=0
upgrade_performed=0
rollback_performed=0
package_manager_invoked=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
network_allowed=0
```

The candidate must not contain placeholder values.

The candidate must not claim multi-VM evidence acceptance, multi-VM promotion, release-artifact promotion, production installer readiness, Fedora distribution readiness, Fedora approval, daily-driver readiness, immutable Fedora readiness, VM invocation, install execution, uninstall execution, upgrade execution, rollback execution, package-manager invocation, network access, or host mutation.

## Validator output

For a valid candidate, the no-effect validator prints:

```text
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
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-multi-vm-evidence-intake-validator-contract.sh
```

Expected output:

```text
production_installer_multi_vm_evidence_intake_validator_contract: ok
```

## Next implementation lane

```text
Attach reviewed fresh VM, repeat VM, existing-install upgrade, remove-and-reinstall, unsupported-target block, non-root CLI, root-boundary, checksum verification, and package-signature verification evidence from disposable production-installer validation, then validate the bundle with the multi-VM evidence intake validator before any promotion review.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This validator is not a production installer.

It is not multi-VM evidence acceptance, not install evidence acceptance, not uninstall evidence acceptance, not upgrade evidence acceptance, not rollback evidence acceptance, not checksum or signature acceptance, not package-manager execution, not host mutation, not release artifact evidence, not SBOM review, not artifact promotion, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
