# Fedora Disposable VM Local RPM Validation Transcript Contract

Status: contract record
Evidence level: 9 target, contract only
Scope: transcript schema for a future real disposable Fedora VM local RPM validation run.

## Purpose

Latticra now has a gated disposable Fedora VM local RPM validation lane and a status record for that lane.

This contract defines the transcript fields required before a real disposable Fedora VM validation run can be reviewed as evidence.

This is an evidence schema only.

It does not execute the validation runner.

It does not install or remove an RPM.

It does not capture real validation evidence by itself.

## Required transcript header

```text
LATTICRA FEDORA DISPOSABLE VM LOCAL RPM VALIDATION TRANSCRIPT
transcript_kind=disposable-vm-local-rpm-validation
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
local_rpm_built_from_current_tree=1
rpm_build_command_recorded=1
rpm_name_is_latticra=1
rpm_version_recorded=1
rpm_path_recorded=1
rpm_metadata_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
```

Expected package payload remains:

```text
/usr/share/doc/latticra/README.md
```

Forbidden payload surfaces remain:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
```

## Required validation transcript evidence

```text
install_command_recorded=1
install_result_recorded=1
rpm_query_after_install_recorded=1
installed_payload_listing_recorded=1
installed_readme_present=1
rpm_verify_completed=1
removal_command_recorded=1
removal_result_recorded=1
post_removal_query_recorded=1
post_removal_absence_verified=1
```

## Required emitted validation report

The transcript must include the deterministic report emitted by the validation lane:

```text
FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE
validation_status=ok
package_name=latticra
package_version_recorded=1
disposable_vm_target_verified=1
snapshot_evidence_present=1
recovery_evidence_present=1
operator_consent_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
vm_rpmdb_mutated=1
vm_filesystem_mutated=1
install_validation_performed=1
removal_validation_performed=1
post_removal_absence_verified=1
live_host_validation_completed=1
host_install_ready=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
evidence_level=9
```

## Required artifact references

A reviewed transcript should reference or embed:

```text
fedora-os-release.txt
fedora-kernel-version.txt
rpm-version.txt
rpmbuild-version.txt
rpm-package-metadata.txt
rpm-payload.list
rpm-installed-payload.list
vm-validation.report
post-removal-absence-proof.txt
```

## Required review sections

```text
TARGET REVIEW
RUNNER GATE REVIEW
PACKAGE REVIEW
INSTALL VALIDATION REVIEW
REMOVAL VALIDATION REVIEW
POST-REMOVAL ABSENCE REVIEW
BOUNDARY REVIEW
OPERATOR SIGNOFF
NEXT ACTION REVIEW
```

## Transcript decision states

```text
disposable_vm_validation_transcript_status=accepted-for-review
disposable_vm_validation_transcript_status=blocked
disposable_vm_validation_transcript_status=invalid
```

`accepted-for-review` means the transcript is complete enough for review.

It does not mean Latticra is production ready, Fedora approved, Fedora distribution ready, or daily-driver safe.

## Current project state until real evidence exists

Until the real disposable VM run is performed and reviewed, the project remains at:

```text
disposable_vm_validation_transcript_present=0
disposable_vm_validation_completed=0
live_host_validation_completed=0
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Validation

```sh
sh scripts/test-fedora-disposable-vm-local-rpm-validation-transcript-contract.sh
```

Expected output:

```text
fedora_disposable_vm_local_rpm_validation_transcript_contract: ok
```

## Next recommended Fedora lane

```text
Capture real disposable Fedora VM local RPM validation transcript evidence
```

That lane should run the already-gated validation runner only inside a disposable Fedora VM target with clean snapshot evidence, recovery evidence, and explicit operator consent.

## README overhaul hold

The root README should not claim install readiness until real validation evidence exists for:

```text
disposable_vm_validation_transcript_present=1
disposable_vm_validation_completed=1
live_host_validation_completed=1
host_install_ready=1
```

## Non-claims

This contract is not a completed validation transcript.

It is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, or a production installer claim.
