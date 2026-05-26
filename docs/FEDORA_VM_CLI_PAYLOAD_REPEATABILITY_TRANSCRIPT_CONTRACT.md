# Fedora VM CLI Payload Repeatability Transcript Contract

Status: contract record
Evidence level: 9 repeatability target, contract only
Scope: transcript schema for a future second disposable Fedora VM validation run of the no-effect CLI RPM payload.

## Purpose

This contract defines the repeatability transcript required before a second disposable Fedora VM CLI payload validation run can be reviewed as repeatability evidence.

This is a contract only.

It does not run a validation lane.

It does not add a runner.

It does not run RPM tooling.

It does not install or remove an RPM.

It does not mutate a host.

## Required transcript header

```text
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_version=1
operator_review_required=1
repeatability_transcript_recorded_after_real_run=1
prior_cli_payload_evidence_recorded=1
```

## Required prior evidence

```text
prior_validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm
prior_validated_payload=/usr/bin/latticra
prior_validated_payload=/usr/share/doc/latticra/README.md
prior_disposable_vm_cli_validation_completed=1
prior_host_install_ready_for_cli_payload=1
prior_evidence_level=9
```

## Required repeatability fields

```text
source_tree_revision_recorded=1
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
spec_checksum_recorded=1
source_archive_checksum_recorded=1
rpm_nevra_recorded=1
rpm_payload_matches_expected_cli_surfaces=1
validated_cli_mode_still_no_effect=1
validated_runtime_behavior_still_disabled=1
validated_non_claims_preserved=1
rpm_verify_completed=1
removal_validation_performed=1
post_removal_absence_verified=1
second_disposable_vm_cli_validation_completed=1
cli_payload_repeatability_evidence_present=1
```

## Current project state

```text
fedora_vm_cli_payload_next_validation_lane_plan_present=1
fedora_vm_cli_payload_repeatability_transcript_contract_present=1
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Validation

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-contract.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_transcript_contract: ok
```

## Next recommended lane

```text
Add Fedora VM CLI payload repeatability runner plan
```

## Non-claims

This contract is not a completed repeatability transcript, not RPM install evidence, not a second disposable Fedora VM validation run, not a runner, not host mutation, and not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, or a production installer claim.
