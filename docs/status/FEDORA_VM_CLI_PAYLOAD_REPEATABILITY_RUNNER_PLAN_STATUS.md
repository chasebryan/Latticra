# Fedora VM CLI Payload Repeatability Runner Plan Status

Status: plan/status alignment
Date: 2026-05-26
Scope: status record for the Fedora VM CLI payload repeatability runner plan and manual runner implementation.

## Summary

Latticra now has a plan and manually gated runner for disposable Fedora VM CLI payload repeatability validation.

The plan maps the repeatability transcript contract into a runner shape, and the runner is present as a manual-only script.

The plan now explicitly carries the installed prevention research, boundary, and method surfaces through repeatability validation.

The runner remains gated by:

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

## Current classification

```text
fedora_vm_cli_payload_repeatability_transcript_contract_present=1
fedora_vm_cli_payload_repeatability_runner_plan_present=1
fedora_vm_cli_payload_repeatability_runner_present=1
repeatability_runner_manual_only=1
ci_auto_repeatability_validation_allowed=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
cli_prevention_research_repeatability_planned=1
cli_prevention_boundary_repeatability_planned=1
cli_prevention_method_repeatability_planned=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-runner-plan.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_runner_plan: ok
```

## Next recommended lane

```text
Capture reviewed Fedora VM CLI payload repeatability transcript evidence
```

## Non-claims

This status record is not RPM install evidence, not a second disposable Fedora VM validation run, not host mutation, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, and not a production installer claim.
