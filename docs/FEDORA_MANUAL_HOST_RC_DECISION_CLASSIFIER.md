# Fedora Manual Host RC Decision Classifier

Status: implementation record
Evidence level: 7
Scope: pure no-effect classifier for manual Fedora host release-candidate decision evidence.

## Purpose

This classifier consumes explicit manual-host checklist evidence and reports whether a future Fedora manual host validation step remains blocked or may be treated as an internal Latticra release-candidate decision.

It is the implementation follow-up to the Fedora manual host release-candidate checklist.

It does not install Latticra.

It does not run host commands.

It does not perform Fedora QA, claim Fedora approval, or produce Fedora distribution readiness.

## API surface

```text
include/latticra/fedora_manual_host_rc_decision.h
src/fedora_manual_host_rc_decision.c
tests/fedora_manual_host_rc_decision.c
```

Public functions:

```text
latticra_fedora_manual_host_rc_decision_classify
latticra_fedora_manual_host_rc_decision_report
latticra_fedora_manual_host_rc_decision_status_label
latticra_fedora_manual_host_rc_decision_denial_label
```

## Candidate evidence

A candidate report requires all of the following input evidence:

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
host_preflight_ready_local_rpm=1
rpm_gate_allowed=1
removal_rollback_ready=1
network_requirement_detected=0
service_boundary_detected=0
boot_boundary_detected=0
kernel_boundary_detected=0
policy_boundary_detected=0
```

Candidate output remains no-effect:

```text
manual_host_rc_status=candidate
manual_host_rc_denial=none
manual_host_release_candidate_ready=1
live_host_validation_completed=0
host_change_performed=0
sudo_invoked=0
rpm_invoked=0
dnf_invoked=0
network_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
kernel_operation_allowed=0
policy_operation_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
evidence_level=7
```

## Blocked states

The classifier reports `manual_host_rc_status=blocked` when any required evidence is missing or any hard-stop boundary is detected.

Denial labels include:

```text
not-disposable-fedora-vm
daily-driver-target
production-target
immutable-fedora-target
snapshot-missing
recovery-path-missing
operator-consent-missing
local-rpm-not-current-tree
rpm-payload-listing-missing
rpm-payload-not-documentation-only
unexpected-runtime-surface
installroot-evidence-missing
post-removal-evidence-missing
preflight-not-ready
rpm-gate-not-allowed
removal-rollback-not-ready
network-required
service-boundary
boot-boundary
kernel-boundary
policy-boundary
```

Blocked output preserves:

```text
manual_host_release_candidate_ready=0
live_host_validation_completed=0
host_change_performed=0
sudo_invoked=0
rpm_invoked=0
dnf_invoked=0
network_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
kernel_operation_allowed=0
policy_operation_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Invalid input

The classifier expects explicit binary evidence values.

Malformed non-binary evidence reports:

```text
manual_host_rc_status=invalid
manual_host_rc_denial=invalid-classifier-input
manual_host_release_candidate_ready=0
```

## Report header

Reports begin with:

```text
FEDORA MANUAL HOST RC DECISION CLASSIFIER
```

Required report fields include:

```text
manual_host_rc_status=candidate
manual_host_rc_status=blocked
manual_host_rc_status=invalid
manual_host_rc_denial=none
manual_host_rc_denial=invalid-classifier-input
classifier_evaluated=1
manual_host_release_candidate_ready=1
manual_host_release_candidate_ready=0
live_host_validation_completed=0
host_change_performed=0
sudo_invoked=0
rpm_invoked=0
dnf_invoked=0
network_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
kernel_operation_allowed=0
policy_operation_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
evidence_level=7
```

## Validation

Classifier guard:

```sh
sh scripts/test-fedora-manual-host-rc-decision-classifier.sh
```

Docs guard:

```sh
sh scripts/test-fedora-manual-host-rc-decision-classifier-docs.sh
```

Expected output:

```text
fedora_manual_host_rc_decision_classifier: ok
fedora_manual_host_rc_decision_classifier_docs: ok
```

## Next recommended Fedora lane

```text
Align Fedora manual host RC decision classifier status
```

After status alignment, the next safe progression is a manual Fedora host dry-run transcript contract.

## Non-claims

This classifier does not implement installation, live host validation, host mutation, privilege escalation, package execution, package removal, service changes, boot changes, kernel changes, policy changes, network access, Fedora QA approval, Fedora distribution readiness, or production installer readiness.
