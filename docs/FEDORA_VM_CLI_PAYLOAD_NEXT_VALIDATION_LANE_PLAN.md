# Fedora VM CLI Payload Next Validation Lane Plan

Status: planning record
Scope: define the next manual disposable Fedora VM validation lane for the no-effect CLI payload without adding a runner or widening readiness claims.

## Purpose

This plan follows the accepted disposable Fedora VM CLI payload validation evidence.

The next Fedora CLI payload lane should test repeatability, not broaden authority.

This plan does not run RPM tooling, install a package, mutate a host, create artifacts, publish artifacts, submit to Fedora, or claim production readiness.

## Current evidence basis

```text
disposable_vm_cli_validation_completed=1
host_install_ready_for_cli_payload=1
validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm
validated_payload=/usr/bin/latticra
validated_payload=/usr/share/doc/latticra/README.md
evidence_level=9
```

## Required repeatability evidence

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

## Success classification

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

## Boundary

This plan does not implement a runner.

It does not execute RPM commands.

It does not mutate a host.

## Next slice

```text
Add Fedora VM CLI payload repeatability transcript contract
```

## Validation

```sh
sh scripts/test-fedora-vm-cli-payload-next-validation-lane-plan.sh
```

Expected output:

```text
fedora_vm_cli_payload_next_validation_lane_plan: ok
```
