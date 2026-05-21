# Fedora VM CLI Payload Validation Transcript Capture

Status: manual evidence-capture preparation
Evidence level: capture preparation only
Scope: checklist for a future reviewed disposable Fedora VM CLI payload validation transcript.

## Purpose

This page prepares the next evidence step for the Fedora VM CLI payload lane.

The real validation runner already exists at:

```text
scripts/run-fedora-vm-cli-payload-validation-lane.sh
```

The runner documentation already exists at:

```text
docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md
```

This page does not run the validation lane.

This page does not create completed evidence.

This page does not claim that a disposable Fedora VM run has succeeded.

This page does not claim host install readiness for the CLI payload.

## Evidence capture rule

A future evidence PR may only mark the CLI payload validation complete after a real disposable Fedora VM run is performed, reviewed, and committed with the full transcript.

Until that reviewed transcript exists, the repository must preserve:

```text
disposable_vm_cli_validation_transcript_present=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
```

## Required reviewed evidence

The future transcript evidence PR should include:

```text
reviewed_disposable_fedora_vm_target=1
reviewed_clean_snapshot_evidence=1
reviewed_recovery_path_evidence=1
reviewed_operator_consent=1
reviewed_runner_success_marker=1
reviewed_cli_payload_present=1
reviewed_readme_payload_present=1
reviewed_cli_status_output=1
reviewed_cli_version_output=1
reviewed_cli_report_output=1
reviewed_post_removal_absence=1
reviewed_non_claims_preserved=1
```

## CI boundary

CI may validate this checklist and related documentation only.

CI must not run the manual validation runner.

## Next recommended Fedora lane

```text
Run the real disposable Fedora VM CLI payload validation lane and commit reviewed transcript evidence
```

## Non-claims

This checklist is not completed VM evidence, not CLI payload validation evidence, not host install readiness for the CLI payload, not production readiness, not Fedora approval, not Fedora distribution readiness, not daily-driver safety, not immutable Fedora readiness, and not a production installer claim.
