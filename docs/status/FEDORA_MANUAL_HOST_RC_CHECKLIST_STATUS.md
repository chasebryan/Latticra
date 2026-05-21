# Fedora Manual Host RC Checklist Status

Status: status alignment
Date: 2026-05-21
Scope: public status record after the Fedora manual host release-candidate checklist landed on `main`.

## Summary

Latticra now has a Fedora manual host release-candidate checklist.

The checklist defines the evidence required before any future manual Fedora host validation milestone may be called a release candidate.

This is checklist and status evidence only.

It does not make Latticra ready for live host installation, production installation, Fedora distribution, or Fedora approval.

## Fedora terminology boundary

In this record, `manual host RC` means an internal Latticra manual-host validation candidate.

It does not mean a Fedora release candidate compose, Fedora QA validation event, Fedora Go/No-Go result, Fedora acceptance, Fedora package approval, or Fedora distribution readiness.

## Evidence recorded

```text
Fedora manual host RC checklist
source=PR #215
checklist_documented=1
checklist_guard_present=1
controlled_installroot_lifecycle_ready=1
manual_host_rc_status=blocked
manual_host_release_candidate_ready=0
live_host_validation_completed=0
host_change_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
fedora_candidate_compose_claimed=0
fedora_go_no_go_claimed=0
checklist_target_evidence_level=7
current_evidence_level=6
evidence_level_7_achieved=0
```

## Required evidence before candidate state

The checklist keeps the manual-host candidate state blocked until the project records all of the following:

```text
target_is_disposable_fedora_vm=1
target_is_daily_driver=0
target_is_production_host=0
target_is_immutable_fedora=0
target_has_clean_snapshot=1
target_has_recovery_path=1
operator_consent_recorded=1
local_rpm_built_from_current_tree=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
installroot_lifecycle_evidence_present=1
post_removal_absence_evidence_present=1
host_preflight_classification=ready-local-rpm
rpm_gate_status=allowed
removal_rollback_status=removal-ready
```

## Current readiness classification

```text
manual_host_rc_checklist_present=1
manual_host_rc_guard_present=1
manual_host_rc_status=blocked
manual_host_release_candidate_ready=0
live_host_validation_completed=0
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Guard validation

The checklist is currently guarded by:

```sh
sh scripts/test-fedora-manual-host-rc-checklist.sh
```

This status alignment is guarded by:

```sh
sh scripts/test-fedora-manual-host-rc-checklist-status-alignment.sh
```

Expected output:

```text
fedora_manual_host_rc_checklist: ok
fedora_manual_host_rc_checklist_status_alignment: ok
```

## Honest public wording

After this status alignment lands, the project may say:

```text
Latticra has controlled Fedora installroot RPM lifecycle evidence.
Latticra has a manual Fedora host release-candidate checklist.
Latticra has status alignment that keeps manual host RC readiness blocked until explicit evidence is recorded.
```

The project must not say:

```text
Latticra has completed live Fedora host validation.
Latticra is safe for daily-driver installation.
Latticra is production installer ready.
Latticra is Fedora-approved.
Latticra is ready for Fedora distribution.
```

## Next recommended Fedora lane

```text
Add no-effect Fedora manual host RC decision classifier
```

That classifier should consume explicit checklist evidence and report `blocked` or `candidate` without running `sudo`, `rpm`, `dnf`, service operations, boot operations, kernel operations, policy operations, network operations, or host mutation.

## Non-claims

This status record does not perform host changes, install Latticra on a developer host, validate a daily-driver Fedora system, publish artifacts, submit to Fedora, claim Fedora approval, claim Fedora distribution readiness, claim production installer readiness, start services, change boot entries, load kernel modules, change host policy, or open runtime network access.
