# Fedora VM CLI Payload Repeatability Runner Plan

Status: planning record
Scope: plan a future manual disposable Fedora VM repeatability runner for the no-effect CLI RPM payload without implementing or running it.

## Purpose

This plan follows the Fedora VM CLI payload repeatability transcript contract.

The future runner should prove repeatability for the already accepted no-effect CLI payload evidence.

This plan does not add the runner.

It does not execute RPM commands.

It does not install or remove an RPM.

It does not mutate a host.

It does not widen host install readiness beyond the accepted no-effect CLI payload boundary.

## Future runner path

A future implementation may add:

```text
scripts/run-fedora-vm-cli-payload-repeatability-lane.sh
```

That script must remain manual-only and must not be called by normal CI.

Any CI workflow for this plan may only run the static guard:

```text
scripts/test-fedora-vm-cli-payload-repeatability-runner-plan.sh
```

## Required source records

The future runner must require these records before doing anything else:

```text
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md
docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md
docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
packaging/fedora/latticra.spec
src/latticra_cli.c
scripts/test-latticra-no-effect-cli-status-surface.sh
scripts/run-fedora-vm-cli-payload-validation-lane.sh
```

## Required hard gate

The future runner must refuse to proceed unless all of the following are true:

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
ID=fedora
operator_is_non_root=1
rpm_present=1
rpmbuild_present=1
cc_present=1
sudo_present=1
```

The future runner must use `sudo` only for RPM install and RPM removal.

## Required command availability

The future runner must require:

```text
awk
cat
cc
find
grep
gzip
id
mktemp
rpm
rpmbuild
sha256sum
sort
sudo
tar
uname
```

If `sha256sum` is unavailable on a Fedora target, the runner must fail closed rather than silently omitting checksum evidence.

## Planned repeatability sequence

The future runner should perform this sequence only after the hard gate passes:

```text
1. Verify disposable Fedora VM target evidence.
2. Verify accepted prior CLI payload evidence records.
3. Verify repeatability transcript contract fields.
4. Run the no-effect CLI status-surface guard.
5. Capture source tree revision.
6. Capture Fedora os-release and kernel version.
7. Capture packaging/fedora/latticra.spec checksum.
8. Build a temporary source archive from the current tree.
9. Capture source archive checksum.
10. Build the local binary RPM with rpmbuild.
11. Capture RPM NEVRA, path, arch, and metadata.
12. Capture RPM payload listing.
13. Confirm expected CLI payload surfaces.
14. Confirm forbidden payload surfaces are absent.
15. Confirm package is absent before install.
16. Install the RPM into the disposable Fedora VM.
17. Query installed package state and payload.
18. Run rpm -V for the installed package.
19. Execute latticra --status without root.
20. Execute latticra --version without root.
21. Execute latticra --report without root.
22. Verify invalid CLI usage exits with code 2.
23. Remove the RPM from the disposable Fedora VM.
24. Confirm package, CLI, and README absence after removal.
25. Emit the repeatability transcript and deterministic report.
```

## Expected payload

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The RPM payload may include:

```text
/usr/share/doc/latticra
```

## Forbidden payload surfaces

```text
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
/usr/share/selinux
/usr/sbin/latticra
```

## Required report fields

A future successful repeatability runner should emit:

```text
FEDORA VM CLI PAYLOAD REPEATABILITY LANE
validation_status=ok
repeatability_validation_status=ok
transcript_kind=disposable-vm-cli-payload-repeatability
prior_cli_payload_evidence_recorded=1
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
validated_cli_mode_still_no_effect=1
validated_runtime_behavior_still_disabled=1
validated_non_claims_preserved=1
rpm_verify_completed=1
removal_validation_performed=1
post_removal_absence_verified=1
second_disposable_vm_cli_validation_completed=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
```

## Current project state

```text
fedora_vm_cli_payload_repeatability_transcript_contract_present=1
fedora_vm_cli_payload_repeatability_runner_plan_present=1
fedora_vm_cli_payload_repeatability_runner_present=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Boundary

This plan is not a runner.

It does not add `scripts/run-fedora-vm-cli-payload-repeatability-lane.sh`.

It does not run `rpmbuild`.

It does not run `rpm`.

It does not install Latticra.

It does not remove Latticra.

It does not mutate a host.

It does not publish artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora approval, Fedora distribution readiness, production installer readiness, daily-driver safety, immutable Fedora readiness, security hardening, sandboxing, update safety, recovery safety, malware prevention, ransomware prevention, or OS-replacement readiness.

## Next recommended lane

```text
Implement manually gated Fedora VM CLI payload repeatability runner
```

That future implementation must remain manual-only, must require explicit operator consent, and must preserve all non-claims.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-repeatability-runner-plan.sh
```

Expected output:

```text
fedora_vm_cli_payload_repeatability_runner_plan: ok
```
