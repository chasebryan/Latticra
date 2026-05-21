# Fedora Manual Host Release-Candidate Checklist

Status: release-candidate checklist
Scope: define go/no-go evidence before any manual Fedora host validation milestone.
Evidence level: 7 target, checklist only

## Purpose

Latticra has controlled Fedora installroot RPM lifecycle evidence.

This checklist defines the evidence required before the project may call a real Fedora host validation step a release candidate.

This document does not perform host changes.

It does not add an execution path.

## Current readiness statement

```text
controlled_installroot_lifecycle_ready=1
manual_host_release_candidate_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Required environment evidence

A future manual host release-candidate step requires:

```text
target_is_disposable_fedora_vm=1
target_is_daily_driver=0
target_is_production_host=0
target_is_immutable_fedora=0
target_has_clean_snapshot=1
target_has_recovery_path=1
operator_consent_recorded=1
```

Any primary workstation, production machine, immutable image, or unclear target must remain blocked.

## Required package evidence

The local RPM candidate must have:

```text
local_rpm_built_from_current_tree=1
rpm_name_is_latticra=1
rpm_version_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
installroot_lifecycle_evidence_present=1
post_removal_absence_evidence_present=1
```

## Required project evidence

The following project evidence must exist:

```text
host_preflight_classification=ready-local-rpm
rpm_gate_status=allowed
removal_rollback_status=removal-ready
controlled_installroot_lifecycle_ready=1
manual_host_release_candidate_ready=0
```

The final value is intentionally still zero. This checklist is the bridge to a future narrowly scoped candidate state.

## Hard stop conditions

The release-candidate step must remain blocked if any of the following are true:

```text
daily_driver_detected=1
production_host_detected=1
immutable_fedora_detected=1
snapshot_missing=1
recovery_path_missing=1
operator_consent_missing=1
unexpected_runtime_surface_present=1
installroot_lifecycle_evidence_missing=1
removal_rollback_evidence_missing=1
network_requirement_detected=1
service_boundary_detected=1
boot_boundary_detected=1
kernel_boundary_detected=1
policy_boundary_detected=1
```

## Release-candidate decision output

Current expected output:

```text
FEDORA MANUAL HOST RC CHECKLIST
manual_host_rc_status=blocked
manual_host_release_candidate_ready=0
host_change_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

Future candidate output, only after all evidence is satisfied:

```text
manual_host_rc_status=candidate
manual_host_release_candidate_ready=1
host_change_performed=0
```

Any future host-changing step must remain separate from this checklist.

## Honest public wording

After this checklist lands, the project may say:

```text
Latticra has controlled Fedora installroot RPM lifecycle evidence.
Latticra has a manual Fedora host release-candidate checklist.
Latticra is preparing for a tightly controlled host validation candidate.
```

The project must not say:

```text
Latticra is production installer ready.
Latticra is Fedora-approved.
Latticra is safe for daily-driver installation.
Latticra has completed live host validation.
```

## Validation

This checklist is guarded by:

```sh
sh scripts/test-fedora-manual-host-rc-checklist.sh
```

Expected output:

```text
fedora_manual_host_rc_checklist: ok
```

## Non-claims

This checklist does not perform host changes, publish artifacts, submit to Fedora, claim Fedora approval, claim production installer readiness, start services, change boot entries, load kernel modules, change host policy, or open runtime network access.
