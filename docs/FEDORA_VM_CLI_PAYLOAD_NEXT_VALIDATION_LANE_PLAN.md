# Fedora VM CLI Payload Next Validation Lane Plan

Status: planning record
Scope: define the next manual disposable Fedora VM validation lane for the no-effect CLI payload without adding a runner or widening readiness claims.

## Purpose

This plan follows the accepted disposable Fedora VM CLI payload validation evidence.

The next Fedora CLI payload lane should test repeatability, not broaden authority.

The goal is conservative: define the evidence required for a future second disposable Fedora VM CLI payload validation run, compare it against the accepted CLI payload evidence, and keep the package local-only and no-effect.

This plan does not run RPM tooling, install a package, mutate a host, create artifacts, publish artifacts, submit to Fedora, or claim production readiness.

## Current evidence basis

The accepted CLI payload evidence records:

```text
disposable_vm_cli_validation_completed=1
host_install_ready_for_cli_payload=1
validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm
validated_payload=/usr/bin/latticra
validated_payload=/usr/share/doc/latticra/README.md
evidence_level=9
```

The accepted payload remains no-effect:

```text
mode=no-effect
runtime_behavior=disabled
host_mutation=0
network=0
kernel_operation=0
service_operation=0
package_manager_operation=0
boot_operation=0
selinux_policy_operation=0
effect_authority=denied
```

## Required hard gate

A future next-validation runner must remain manual and must refuse to proceed unless all of the following are true:

```text
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1
LATTICRA_TARGET_IS_DAILY_DRIVER=0
LATTICRA_TARGET_IS_PRODUCTION_HOST=0
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1
LATTICRA_TARGET_HAS_RECOVERY_PATH=1
LATTICRA_OPERATOR_CONSENT_RECORDED=1
ID=fedora
rpm_present=1
rpmbuild_present=1
cc_present=1
sudo_present=1
```

The lane must not run automatically in CI.

The lane must not run on a developer daily-driver host, production host, immutable Fedora target, non-Fedora host, or unclear target.

## Required repeatability evidence

The future lane should record these repeatability fields:

```text
source_tree_revision_recorded=1
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
spec_checksum_recorded=1
source_archive_checksum_recorded=1
rpm_nevra_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_matches_expected_cli_surfaces=1
unexpected_runtime_surface_absent=1
cli_status_output_recorded=1
cli_version_output_recorded=1
cli_report_output_recorded=1
cli_invalid_command_exit_recorded=1
rpm_verify_completed=1
removal_validation_performed=1
post_removal_absence_verified=1
```

The lane should compare the new evidence against the accepted CLI payload evidence:

```text
validated_payload_still_contains_cli=1
validated_payload_still_contains_readme=1
validated_cli_mode_still_no_effect=1
validated_runtime_behavior_still_disabled=1
validated_non_claims_preserved=1
```

## Success classification

A future successful run may record:

```text
second_disposable_vm_cli_validation_completed=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

This classification is still bounded to the no-effect CLI payload in a disposable Fedora VM validation path.

## Boundary

This plan does not implement a runner.

It does not execute RPM commands.

It does not install Latticra.

It does not remove Latticra.

It does not mutate a host.

It does not change services, boot entries, kernel modules, SELinux policy, firmware, networking, package repositories, or system configuration.

It does not publish package artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora approval, Fedora distribution readiness, production installer readiness, daily-driver safety, immutable Fedora readiness, security hardening, sandboxing, update safety, recovery safety, malware prevention, ransomware prevention, or OS-replacement readiness.

## Next slice

Recommended next slice:

```text
Add Fedora VM CLI payload repeatability transcript contract
```

That future slice should define the transcript schema for the second disposable Fedora VM CLI payload validation run without adding the runner or performing host mutation.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-next-validation-lane-plan.sh
```

Expected output:

```text
fedora_vm_cli_payload_next_validation_lane_plan: ok
```
