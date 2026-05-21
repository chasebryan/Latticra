# Fedora Disposable VM Effect Gate Classifier Status

Status: status alignment
Date: 2026-05-21
Scope: public status record after the Fedora VM gate classifier landed on `main`.

## Summary

Latticra now has the Fedora evidence contract, the Fedora disposable VM effect gate, and a no-effect classifier for that gate.

The classifier reports:

```text
disposable_vm_effect_gate_status=eligible
disposable_vm_effect_gate_status=blocked
disposable_vm_effect_gate_status=invalid
```

This is classifier evidence only.

It does not make Latticra host-install ready, production ready, Fedora-approved, or Fedora distribution ready.

## Evidence recorded

```text
Fedora disposable VM effect gate classifier
source=PR #221
evidence_contract_present=1
vm_effect_gate_present=1
vm_gate_classifier_present=1
vm_gate_classifier_guard_present=1
vm_gate_classifier_docs_guard_present=1
eligible_state_defined=1
blocked_state_defined=1
invalid_state_defined=1
eligible_test_present=1
blocked_target_tests_present=1
blocked_package_tests_present=1
blocked_prior_evidence_tests_present=1
invalid_input_test_present=1
classifier_evidence_level=8
```

## Current readiness classification

```text
manual_host_dry_run_transcript_contract_present=1
disposable_vm_effect_gate_present=1
disposable_vm_effect_gate_classifier_present=1
disposable_vm_effect_gate_status=blocked-pending-vm-validation-lane
disposable_vm_effect_eligible=0
live_host_validation_completed=0
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Boundary statement

A synthetic eligible unit test proves classifier logic only.

It is not a completed Fedora VM validation record.

The project still needs a dedicated disposable Fedora VM local RPM validation lane before install-ready README wording is justified.

## Guard validation

The classifier is guarded by:

```sh
sh scripts/test-fedora-disposable-vm-effect-gate-classifier.sh
sh scripts/test-fedora-disposable-vm-effect-gate-classifier-docs.sh
```

This status alignment is guarded by:

```sh
sh scripts/test-fedora-vm-gate-classifier-status-alignment.sh
```

Expected output:

```text
fedora_disposable_vm_effect_gate_classifier: ok
fedora_disposable_vm_effect_gate_classifier_docs: ok
fedora_vm_gate_classifier_status_alignment: ok
```

## Next recommended Fedora lane

```text
Add disposable Fedora VM local RPM validation lane
```

That lane should remain restricted to a disposable Fedora VM target with snapshot and recovery evidence.

## README overhaul hold

The root README should not claim install readiness yet.

The README overhaul should wait until real validation evidence exists for:

```text
manual_host_dry_run_transcript_present=1
live_host_validation_completed=1
host_install_ready=1
```

## Non-claims

This status record is not production readiness, Fedora approval, or Fedora distribution readiness.
