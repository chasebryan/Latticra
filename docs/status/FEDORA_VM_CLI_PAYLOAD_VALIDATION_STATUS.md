# Fedora VM CLI Payload Validation Status

Status: status alignment
Date: 2026-05-21
Scope: public status record after the manually gated disposable Fedora VM CLI payload validation lane runner landed on `main`.

## Summary

Latticra now has a manually gated disposable Fedora VM CLI payload validation runner.

The runner is designed for validating the expanded local RPM payload:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The lane defines and ships:

```text
docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md
scripts/run-fedora-vm-cli-payload-validation-lane.sh
scripts/test-fedora-vm-cli-payload-validation-lane-docs.sh
.github/workflows/fedora-vm-cli-payload-validation-lane-docs.yml
```

This is runner-readiness evidence only.

It does not prove that a disposable Fedora VM CLI payload validation run has completed yet.

The validation runner remains manually gated and must not be auto-run by normal CI.

## Evidence recorded

```text
Fedora VM CLI payload validation lane runner
source=PR #236
validation_lane_documented=1
validation_runner_present=1
validation_lane_docs_guard_present=1
validation_lane_docs_workflow_present=1
runner_manual_only=1
ci_auto_vm_cli_validation_allowed=0
disposable_vm_target_required=1
daily_driver_block_required=1
production_host_block_required=1
immutable_fedora_block_required=1
clean_snapshot_required=1
recovery_path_required=1
operator_consent_required=1
non_root_operator_required=1
sudo_limited_to_rpm_install_removal=1
fedora_target_required=1
rpm_tooling_required=1
rpmbuild_tooling_required=1
cc_tooling_required=1
local_cli_guard_required=1
local_rpm_build_required=1
rpm_payload_listing_required=1
rpm_payload_cli_binary_required=1
rpm_payload_readme_required=1
rpm_payload_only_expected_surfaces_required=1
unexpected_runtime_surface_absent_required=1
installed_cli_binary_required=1
installed_readme_required=1
rpm_verify_required=1
cli_status_validation_required=1
cli_version_validation_required=1
cli_report_validation_required=1
cli_invalid_command_validation_required=1
post_removal_cli_absence_required=1
post_removal_readme_absence_required=1
validation_report_schema_present=1
target_evidence_level=9
current_evidence_level=8
evidence_level_9_achieved=0
```

## Current readiness classification

```text
fedora_vm_cli_transcript_contract_present=1
fedora_vm_cli_payload_validation_lane_present=1
fedora_vm_cli_payload_validation_runner_present=1
fedora_vm_cli_payload_validation_status=blocked-pending-real-vm-run
disposable_vm_cli_validation_transcript_present=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Boundary statement

This status alignment does not run the validation lane.

It does not build a release RPM artifact.

It does not install or remove an RPM.

It does not validate `/usr/bin/latticra` in a real disposable Fedora VM.

It does not mutate a disposable VM, developer host, daily-driver Fedora host, immutable Fedora host, production host, boot entry, kernel module set, service registry, SELinux policy, firmware state, or network configuration.

The docs guard may run in CI.

The CLI payload validation runner must remain manual and gated by explicit disposable-VM evidence.

## Guard validation

The validation lane documentation is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-validation-lane-docs.sh
```

This status alignment is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-validation-status-alignment.sh
```

Expected output:

```text
fedora_vm_cli_payload_validation_lane_docs: ok
fedora_vm_cli_payload_validation_status_alignment: ok
```

## Next recommended Fedora lane

```text
Capture real disposable Fedora VM CLI payload validation transcript evidence
```

That lane should record the Fedora VM identity, clean snapshot evidence, recovery path evidence, package version, RPM architecture, RPM payload listing, install transcript, CLI command transcript, invalid command transcript, removal transcript, post-removal absence proof, and emitted validation report.

## README update hold

The root README should not claim CLI payload host install readiness yet.

The README update remains blocked until real validation evidence exists for:

```text
disposable_vm_cli_validation_transcript_present=1
disposable_vm_cli_validation_completed=1
host_install_ready_for_cli_payload=1
```

## Non-claims

This status record is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, update safety, recovery safety, sandboxing, security hardening, malware prevention, ransomware prevention, OS-replacement readiness, or a production installer claim.
