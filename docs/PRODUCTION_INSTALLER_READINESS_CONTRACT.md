# Production Installer Readiness Contract

Status: contract record
Evidence level: 10 target, contract only
Scope: requirements that must be satisfied before Latticra can claim a production installer that others should use.

## Purpose

Latticra now has disposable Fedora VM evidence for a local no-effect CLI RPM payload.

That is not the same as production installer readiness.

This contract defines the minimum evidence required before the project may claim:

```text
production_installer_ready=1
```

Until every required gate is satisfied, the project must preserve:

```text
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Current evidence that may be used as prerequisites

The current evidence-backed base is limited to disposable Fedora VM validation:

```text
disposable_vm_local_rpm_validation_completed=1
disposable_vm_cli_validation_completed=1
host_install_ready=1
host_install_ready_for_cli_payload=1
```

Validated disposable Fedora VM CLI payload:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

## Production installer readiness gates

A production installer claim requires all of the following gates to be complete and reviewed.

```text
installer_contract_present=1
installer_artifact_format_declared=1
installer_artifact_built_from_tag=1
installer_artifact_reproducible=1
installer_artifact_checksum_recorded=1
installer_artifact_signature_recorded=1
installer_public_key_documented=1
installer_sbom_recorded=1
installer_license_metadata_recorded=1
installer_supported_targets_declared=1
installer_unsupported_targets_declared=1
installer_daily_driver_warning_present=1
installer_production_host_warning_present=1
installer_immutable_fedora_warning_present=1
installer_preflight_guard_present=1
installer_preflight_blocks_unsupported_targets=1
installer_install_plan_preview_present=1
installer_requires_operator_consent=1
installer_install_transcript_recorded=1
installer_uninstall_transcript_recorded=1
installer_post_removal_absence_verified=1
installer_upgrade_path_validated=1
installer_downgrade_or_rollback_path_validated=1
installer_reinstall_idempotence_validated=1
installer_no_network_requirement_documented=1
installer_no_service_activation_without_consent=1
installer_no_boot_change_without_consent=1
installer_no_kernel_module_without_consent=1
installer_no_selinux_policy_without_consent=1
installer_effect_authority_documented=1
installer_failure_mode_documented=1
installer_recovery_runbook_present=1
installer_multi_vm_validation_completed=1
installer_fresh_vm_validation_completed=1
installer_existing_install_validation_completed=1
installer_non_root_cli_validation_completed=1
installer_root_boundary_validation_completed=1
installer_security_non_claims_preserved=1
installer_release_notes_present=1
installer_readme_install_instructions_present=1
installer_status_alignment_present=1
```

## Minimum validation matrix

Before claiming production installer readiness, validation must include at least:

```text
fresh_disposable_fedora_vm_validation=1
repeat_disposable_fedora_vm_validation=1
existing_install_upgrade_validation=1
remove_and_reinstall_validation=1
post_removal_absence_validation=1
unsupported_target_block_validation=1
non_root_cli_use_validation=1
package_signature_verification_validation=1
checksum_verification_validation=1
```

## Required production installer report

A future readiness report must include:

```text
PRODUCTION INSTALLER READINESS REPORT
validation_status=ok
installer_artifact_name=<recorded>
installer_artifact_version=<recorded>
installer_artifact_arch=<recorded>
installer_artifact_checksum_recorded=1
installer_artifact_signature_recorded=1
installer_supported_targets_declared=1
installer_preflight_guard_present=1
installer_install_validation_completed=1
installer_uninstall_validation_completed=1
installer_upgrade_validation_completed=1
installer_rollback_validation_completed=1
installer_multi_vm_validation_completed=1
production_installer_ready=1
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=10
```

Fedora distribution readiness and Fedora approval remain separate claims and must stay `0` until separate review and acceptance evidence exists.

## Current readiness classification

```text
production_installer_contract_present=1
production_installer_ready=0
installer_artifact_reproducible=0
installer_artifact_signature_recorded=0
installer_sbom_recorded=0
installer_preflight_guard_present=0
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_upgrade_path_validated=0
installer_rollback_path_validated=0
installer_multi_vm_validation_completed=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Next implementation lanes

Recommended sequence:

```text
1. Add local installer artifact manifest contract.
2. Add installer preflight classifier for supported and blocked targets.
3. Add signed artifact/checksum status contract.
4. Add installer preview-only plan renderer.
5. Add disposable Fedora VM production-installer dry-run lane.
6. Add uninstall and rollback transcript contract.
7. Add upgrade/reinstall validation contract.
8. Add multi-VM production-installer evidence status.
9. Only then consider production_installer_ready=1.
```

## Non-claims

This contract is not a production installer.

It does not build, sign, publish, install, uninstall, upgrade, rollback, or distribute an installer.

It is not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, not security hardening, not malware prevention, not ransomware prevention, not OS-replacement readiness, and not a production installer claim.
