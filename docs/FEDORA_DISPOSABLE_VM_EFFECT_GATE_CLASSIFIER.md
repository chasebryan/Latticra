# Fedora Disposable VM Effect Gate Classifier

Status: implementation record
Evidence level: 8
Scope: pure classifier for disposable Fedora VM effect-gate evidence.

## Purpose

This classifier consumes explicit evidence fields from the Fedora disposable VM effect gate and reports one of:

```text
disposable_vm_effect_gate_status=eligible
disposable_vm_effect_gate_status=blocked
disposable_vm_effect_gate_status=invalid
```

The classifier is no-effect.

It does not add runtime behavior.

## API surface

```text
include/latticra/fedora_disposable_vm_effect_gate.h
src/fedora_disposable_vm_effect_gate.c
tests/fedora_disposable_vm_effect_gate.c
```

Public functions:

```text
latticra_fedora_disposable_vm_effect_gate_classify
latticra_fedora_disposable_vm_effect_gate_report
latticra_fedora_disposable_vm_effect_gate_status_label
latticra_fedora_disposable_vm_effect_gate_denial_label
```

## Eligible evidence

```text
target_is_disposable_fedora_vm=1
target_is_daily_driver=0
target_is_production_host=0
target_is_immutable_fedora=0
target_has_clean_snapshot=1
target_has_recovery_path=1
operator_consent_recorded=1
local_rpm_built_from_current_tree=1
rpm_name_is_latticra=1
rpm_version_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
installroot_lifecycle_evidence_present=1
post_removal_absence_evidence_present=1
manual_host_dry_run_transcript_contract_present=1
manual_host_rc_decision_classifier_present=1
rpm_gate_allowed=1
removal_rollback_ready=1
```

## Eligible output boundary

```text
disposable_vm_effect_gate_status=eligible
disposable_vm_effect_gate_denial=none
disposable_vm_effect_eligible=1
effect_gate_present=1
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_allowed=0
production_host_allowed=0
immutable_host_allowed=0
evidence_level=8
```

## Blocked denial labels

```text
not-disposable-fedora-vm
daily-driver-target
production-target
immutable-fedora-target
snapshot-missing
recovery-path-missing
operator-consent-missing
local-rpm-not-current-tree
rpm-name-mismatch
rpm-version-missing
rpm-payload-listing-missing
rpm-payload-not-documentation-only
unexpected-runtime-surface
installroot-evidence-missing
post-removal-evidence-missing
transcript-contract-missing
decision-classifier-missing
rpm-gate-not-allowed
removal-rollback-not-ready
```

## Invalid input

Malformed non-binary evidence reports:

```text
disposable_vm_effect_gate_status=invalid
disposable_vm_effect_gate_denial=invalid-classifier-input
disposable_vm_effect_eligible=0
```

## Report header

```text
FEDORA DISPOSABLE VM EFFECT GATE CLASSIFIER
```

Required report fields include:

```text
classifier_evaluated=1
effect_gate_present=1
disposable_vm_effect_eligible=1
disposable_vm_effect_eligible=0
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_allowed=0
production_host_allowed=0
immutable_host_allowed=0
evidence_level=8
```

## Validation

Classifier guard:

```sh
sh scripts/test-fedora-disposable-vm-effect-gate-classifier.sh
```

Docs guard:

```sh
sh scripts/test-fedora-disposable-vm-effect-gate-classifier-docs.sh
```

Expected output:

```text
fedora_disposable_vm_effect_gate_classifier: ok
fedora_disposable_vm_effect_gate_classifier_docs: ok
```

## Next recommended Fedora lane

```text
Align Fedora disposable VM effect gate classifier status
```

After that status alignment, the next safe progression is a disposable Fedora VM local RPM validation lane.

## Non-claims

This classifier is not production readiness, Fedora approval, or Fedora distribution readiness.
