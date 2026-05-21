# Fedora VM CLI Payload Validation Transcript Capture

Status: manual evidence-capture preparation
Evidence level: 9 target, capture template only
Scope: manual transcript template and guard for a future real disposable Fedora VM CLI payload validation run.

## Purpose

The next evidence target is a real disposable Fedora VM transcript for the expanded CLI RPM payload:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

This page prepares the capture process and points to the transcript template.

It does not create completed evidence by itself.

It does not run the validation lane.

It does not claim that a disposable Fedora VM run has succeeded.

It does not claim host install readiness for the CLI payload.

## Capture boundary

The real validation lane remains the existing gated runner:

```text
scripts/run-fedora-vm-cli-payload-validation-lane.sh
```

The transcript template is:

```text
docs/templates/FEDORA_VM_CLI_PAYLOAD_VALIDATION_TRANSCRIPT_TEMPLATE.md
```

The template is not completed evidence until a real disposable Fedora VM run is performed, reviewed, and committed through a follow-up evidence PR.

## Required manual gate

The real run must refuse to proceed unless all of the following are true:

```text
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1
LATTICRA_TARGET_IS_DAILY_DRIVER=0
LATTICRA_TARGET_IS_PRODUCTION_HOST=0
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1
LATTICRA_TARGET_HAS_RECOVERY_PATH=1
LATTICRA_OPERATOR_CONSENT_RECORDED=1
```

The runner also verifies:

```text
ID=fedora
rpm_present=1
rpmbuild_present=1
cc_present=1
sudo_present=1
non_root_operator_required=1
sudo_limited_to_rpm_install_removal=1
```

## Manual run command

From inside a disposable Fedora VM with a clean snapshot and recovery path:

```sh
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1 \
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1 \
LATTICRA_TARGET_IS_DAILY_DRIVER=0 \
LATTICRA_TARGET_IS_PRODUCTION_HOST=0 \
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0 \
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1 \
LATTICRA_TARGET_HAS_RECOVERY_PATH=1 \
LATTICRA_OPERATOR_CONSENT_RECORDED=1 \
sh scripts/run-fedora-vm-cli-payload-validation-lane.sh 2>&1 | tee fedora-vm-cli-payload-validation-transcript.txt
```

Expected runner marker after a successful real run:

```text
fedora_vm_cli_payload_validation_lane: ok
```

## Transcript header required in evidence PR

A reviewed evidence PR should preserve a transcript with:

```text
FEDORA VM CLI PAYLOAD VALIDATION TRANSCRIPT
transcript_kind=disposable-vm-cli-payload-validation
transcript_version=1
operator_review_required=1
validation_transcript_recorded_after_real_run=1
```

## Required successful runner report inside transcript

The transcript must include the existing runner report:

```text
FEDORA VM CLI PAYLOAD VALIDATION LANE
validation_status=ok
rpm_payload_contains_cli_binary=1
rpm_payload_contains_readme=1
rpm_payload_contains_only_expected_surfaces=1
unexpected_runtime_surface_absent=1
installed_cli_binary_present=1
installed_readme_present=1
cli_status_validation_performed=1
cli_version_validation_performed=1
cli_report_validation_performed=1
post_removal_cli_absence_verified=1
post_removal_readme_absence_verified=1
disposable_vm_cli_validation_completed=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
```

## Current project state until reviewed evidence is committed

```text
transcript_capture_template_present=1
runner_manual_only=1
ci_auto_vm_cli_validation_allowed=0
disposable_vm_cli_validation_transcript_present=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## CI boundary

CI only validates the capture documentation and transcript template shape:

```sh
sh scripts/test-fedora-vm-cli-payload-transcript-capture.sh
```

Expected output:

```text
fedora_vm_cli_payload_transcript_capture_docs: ok
```

CI must not run:

```text
scripts/run-fedora-vm-cli-payload-validation-lane.sh
```

## Next recommended Fedora lane

```text
Run the real disposable Fedora VM CLI payload validation lane and commit reviewed transcript evidence
```

## Non-claims

This capture template is not completed VM evidence, not RPM install evidence, not CLI payload validation evidence, not host install readiness for the CLI payload, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, not update safety, not recovery safety, not sandboxing, not security hardening, and not a production installer claim.
