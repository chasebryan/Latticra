# Fedora Manual Host RC Decision Classifier Status

Status: status alignment
Date: 2026-05-21
Scope: public status record after the no-effect Fedora manual host RC decision classifier landed on `main`.

## Summary

Latticra now has a no-effect Fedora manual host release-candidate decision classifier.

The classifier consumes explicit checklist-style evidence and reports one of:

```text
manual_host_rc_status=candidate
manual_host_rc_status=blocked
manual_host_rc_status=invalid
```

This is decision evidence only.

It does not perform host changes, live validation, Fedora QA, Fedora approval, Fedora distribution readiness, or production readiness.

## Evidence recorded

```text
Fedora manual host RC decision classifier
source=PR #217
decision_classifier_present=1
decision_classifier_guard_present=1
decision_classifier_docs_guard_present=1
candidate_state_defined=1
blocked_state_defined=1
invalid_state_defined=1
synthetic_candidate_test_present=1
blocked_target_tests_present=1
blocked_evidence_tests_present=1
blocked_boundary_tests_present=1
invalid_input_test_present=1
classifier_evidence_level=7
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

## Current readiness classification

```text
manual_host_rc_checklist_present=1
manual_host_rc_decision_classifier_present=1
manual_host_rc_status=blocked-pending-real-transcript
manual_host_release_candidate_ready=0
manual_host_dry_run_transcript_present=0
live_host_validation_completed=0
host_install_ready=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
```

## Candidate boundary

The classifier can report `candidate` only when explicit evidence says all required conditions are satisfied.

A synthetic unit-test candidate is not a real Fedora host validation candidate.

A real candidate still requires a concrete reviewed transcript from a disposable Fedora VM target.

## Guard validation

The classifier is guarded by:

```sh
sh scripts/test-fedora-manual-host-rc-decision-classifier.sh
sh scripts/test-fedora-manual-host-rc-decision-classifier-docs.sh
```

This status alignment is guarded by:

```sh
sh scripts/test-fedora-manual-host-rc-decision-status-alignment.sh
```

Expected output:

```text
fedora_manual_host_rc_decision_classifier: ok
fedora_manual_host_rc_decision_classifier_docs: ok
fedora_manual_host_rc_decision_status_alignment: ok
```

## Honest public wording

After this status alignment lands, the project may say:

```text
Latticra has controlled Fedora installroot RPM lifecycle evidence.
Latticra has a manual Fedora host RC checklist.
Latticra has a no-effect decision classifier for manual Fedora host RC evidence.
Latticra is preparing the dry-run transcript layer required before live host validation.
```

The project must not say:

```text
Latticra has completed live Fedora host validation.
Latticra is production ready.
Latticra is Fedora-approved.
Latticra is ready for Fedora distribution.
```

## Next recommended Fedora lane

```text
Add manual Fedora host dry-run transcript contract
```

That contract should define the transcript evidence required before any future disposable Fedora VM validation attempt.

## README overhaul hold

The root README overhaul should wait until the repository has real validation evidence for the host path.

Until then, root README wording should remain evidence-bound and avoid readiness claims.

## Non-claims

This status record does not perform host changes, live validation, Fedora QA approval, Fedora distribution readiness, or production readiness.
