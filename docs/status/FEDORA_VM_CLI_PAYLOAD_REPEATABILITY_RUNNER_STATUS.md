# Fedora VM CLI Payload Repeatability Runner Status

Status: runner/status alignment
Date: 2026-05-26
Scope: status record for the manually gated Fedora VM CLI payload repeatability runner.

## Summary

Latticra now has a manual-only disposable Fedora VM CLI payload repeatability runner.

The runner is present at:

```text
scripts/run-fedora-vm-cli-payload-repeatability-lane.sh
```

It is gated by both disposable-VM RPM validation consent and CLI payload repeatability consent.

It must not be called by normal CI.

## Current classification

```text
fedora_vm_cli_payload_repeatability_transcript_contract_present=1
fedora_vm_cli_payload_repeatability_runner_plan_present=1
fedora_vm_cli_payload_repeatability_runner_present=1
repeatability_runner_manual_only=1
ci_auto_repeatability_validation_allowed=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Required gates

```text
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1
LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION=1
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1
LATTICRA_TARGET_IS_DAILY_DRIVER=0
LATTICRA_TARGET_IS_PRODUCTION_HOST=0
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1
LATTICRA_TARGET_HAS_RECOVERY_PATH=1
LATTICRA_OPERATOR_CONSENT_RECORDED=1
```

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-runner.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_runner: ok
```

## Next recommended lane

```text
Capture reviewed Fedora VM CLI payload repeatability transcript evidence
```

## Non-claims

This status record is not a completed repeatability transcript, not RPM install evidence, not a second disposable Fedora VM validation run, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
