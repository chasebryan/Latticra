# Fedora VM CLI Transcript Contract

Status: contract record
Evidence level: 9 target, contract only
Scope: transcript schema for future disposable Fedora VM validation of the expanded local RPM payload that includes the no-effect `latticra` CLI.

## Purpose

The local Fedora RPM spec now packages the no-effect CLI as `%{_bindir}/latticra`.

This document defines the evidence required before that expanded payload can be treated as validated in a disposable Fedora VM.

This is a contract only.

It does not run the validation lane.

It does not build a release RPM.

It does not install or remove an RPM.

It does not validate `/usr/bin/latticra`.

It does not claim host install readiness for the CLI payload.

## Required transcript header

```text
FEDORA VM CLI PAYLOAD VALIDATION TRANSCRIPT
transcript_kind=disposable-vm-cli-payload-validation
transcript_version=1
operator_review_required=1
validation_transcript_recorded_after_real_run=1
```

## Required target evidence

```text
target_is_disposable_fedora_vm=1
target_is_daily_driver=0
target_is_production_host=0
target_is_immutable_fedora=0
target_has_clean_snapshot=1
target_has_recovery_path=1
operator_consent_recorded=1
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
rpm_tooling_recorded=1
rpmbuild_tooling_recorded=1
```

## Required spec evidence

```text
fedora_spec_updated_for_cli=1
rpm_payload_expansion_performed=1
rpm_contains_compiled_c_binary=1
buildarch_noarch_removed=1
cli_status_surface_implemented=1
cli_status_surface_guarded_before_packaging=1
local_cli_guard_passed=1
local_rpm_built_from_current_tree=1
```

Required source and guard references:

```text
src/latticra_cli.c
scripts/test-latticra-no-effect-cli-status-surface.sh
packaging/fedora/latticra.spec
scripts/test-latticra-no-effect-cli-packaging-contract-alignment.sh
scripts/test-latticra-no-effect-cli-rpm-spec-update-status.sh
```

## Required runner gate evidence

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
```

## Required package evidence

```text
rpm_build_command_recorded=1
rpm_name_is_latticra=1
rpm_version_recorded=1
rpm_arch_recorded=1
rpm_path_recorded=1
rpm_metadata_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_contains_cli_binary=1
rpm_payload_contains_readme=1
rpm_payload_contains_only_expected_surfaces=1
unexpected_runtime_surface_absent=1
```

Expected payload:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

Forbidden payload surfaces:

```text
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
/usr/share/selinux
```

## Required install and CLI evidence

```text
install_command_recorded=1
install_result_recorded=1
rpm_query_after_install_recorded=1
installed_payload_listing_recorded=1
installed_cli_binary_present=1
installed_readme_present=1
rpm_verify_completed=1
cli_status_command_recorded=1
cli_version_command_recorded=1
cli_report_command_recorded=1
cli_invalid_command_recorded=1
cli_no_root_required=1
cli_no_host_mutation_observed=1
cli_no_network_observed=1
cli_no_service_operation_observed=1
cli_no_kernel_operation_observed=1
cli_no_boot_operation_observed=1
cli_no_selinux_policy_operation_observed=1
```

Required `latticra --status` and `latticra --report` output fields:

```text
LATTICRA STATUS REPORT
project=latticra
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

Required `latticra --version` output fields:

```text
latticra 0.0.0
mode=no-effect
runtime_behavior=disabled
```

## Required removal evidence

```text
removal_command_recorded=1
removal_result_recorded=1
post_removal_query_recorded=1
post_removal_absence_verified=1
cli_removed_after_rpm_removal=1
readme_removed_after_rpm_removal=1
post_removal_cli_absence_verified=1
post_removal_readme_absence_verified=1
```

## Required final report

A future runner should emit:

```text
FEDORA VM CLI PAYLOAD VALIDATION LANE
validation_status=ok
package_name=latticra
package_version_recorded=1
package_arch_recorded=1
disposable_vm_target_verified=1
snapshot_evidence_present=1
recovery_evidence_present=1
operator_consent_recorded=1
rpm_payload_contains_cli_binary=1
rpm_payload_contains_readme=1
unexpected_runtime_surface_absent=1
install_validation_performed=1
cli_status_validation_performed=1
cli_version_validation_performed=1
cli_report_validation_performed=1
removal_validation_performed=1
post_removal_absence_verified=1
disposable_vm_cli_validation_completed=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
```

## Current project state until real evidence exists

```text
fedora_spec_updated_for_cli=1
rpm_payload_expansion_performed=1
rpm_payload_validated=0
disposable_vm_cli_validation_transcript_present=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Validation

```sh
sh scripts/test-fedora-vm-cli-transcript-contract.sh
```

Expected output:

```text
fedora_vm_cli_transcript_contract: ok
```

## Next recommended lane

```text
Add disposable Fedora VM CLI payload validation lane runner
```

## Non-claims

This contract is not a completed validation transcript, not RPM install evidence, not disposable Fedora VM validation of the CLI payload, and not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, update safety, recovery safety, sandboxing, or a production installer claim.
