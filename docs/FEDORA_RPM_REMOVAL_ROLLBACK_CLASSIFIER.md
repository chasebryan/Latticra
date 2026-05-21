# Fedora RPM Removal Rollback Classifier

Status: implementation record
Scope: pure Fedora RPM removal/rollback posture classification before any host-changing Fedora RPM removal behavior.
Evidence level: 5

## Purpose

This implementation turns the Fedora RPM removal rollback classifier contract into a pure C classifier.

The classifier evaluates explicit evidence and reports whether the Latticra RPM removal posture is `removal-ready`, `denied`, `partial`, or `invalid`.

This is install-preparation work: it proves that the project can reason about removal and rollback posture before a future local RPM execution lane performs any host-changing install or removal action.

This implementation does not implement removal, rollback execution, installation, privilege validation, package build behavior, network use, service operation, boot operation, kernel module operation, host policy changes, Fedora approval, or production installer readiness.

## Public API

Primary header:

```text
include/latticra/fedora_rpm_removal_rollback.h
```

Primary source:

```text
src/fedora_rpm_removal_rollback.c
```

The main entry points are:

```text
latticra_fedora_rpm_removal_rollback_classify
latticra_fedora_rpm_removal_rollback_report
latticra_fedora_rpm_removal_rollback_status_label
latticra_fedora_rpm_removal_rollback_denial_label
latticra_fedora_rpm_removal_rollback_partial_label
```

## Ready evidence

The classifier reports `removal-ready` only when every required fact is present:

```text
operator_removal_confirmation=1
package_name=latticra
package_identity_present=1
package_query_ready=1
installed_package_detected=1
owned_file_list_available=1
readme_owned_by_package=1
unexpected_runtime_surface_absent=1
post_removal_absence_check_planned=1
failure_report_planned=1
network_required=0
service_operation_requested=0
boot_operation_requested=0
kernel_operation_requested=0
policy_operation_requested=0
```

All other states fail closed into `denied`, `partial`, or `invalid`.

## Status classes

The classifier can report:

```text
removal-ready
denied
partial
invalid
```

`removal-ready` means removal posture is allowed by evidence, but removal is still not performed.

`denied` means planned removal should not be attempted.

`partial` means the input indicates incomplete or uncertain host/package state that a future execution lane would have to report and roll back around.

`invalid` means the classifier input itself is missing, unknown, or outside the expected 0/1 evidence model.

## Deterministic denial reasons

The classifier reports deterministic reason labels including:

```text
operator-confirmation-missing
package-name-mismatch
package-identity-missing
package-query-not-ready
package-not-installed
owned-file-list-missing
readme-ownership-missing
unexpected-runtime-surface-present
post-removal-check-missing
failure-report-missing
network-required
service-operation-requested
boot-operation-requested
kernel-operation-requested
policy-operation-requested
invalid-classifier-input
```

## Partial state labels

Partial states are reported separately from the denial reason:

```text
partial_state=package-installed-but-ownership-unknown
partial_state=owned-files-present-but-package-query-failed
partial_state=runtime-surface-present-before-removal
partial_state=absence-check-not-ready
partial_state=unknown-host-state
```

## Report surface

The report begins with:

```text
FEDORA RPM REMOVAL ROLLBACK CLASSIFIER
```

Ready reports include:

```text
removal_rollback_status=removal-ready
removal_rollback_denial=none
partial_state=none
package_name=latticra
removal_allowed=1
rollback_planned=1
partial_failure_report_required=0
removal_performed=0
host_mutation_performed=0
network_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
kernel_operation_allowed=0
policy_operation_allowed=0
evidence_level=5
```

Denied reports preserve:

```text
removal_rollback_status=denied
removal_allowed=0
removal_performed=0
host_mutation_performed=0
```

Partial reports preserve:

```text
removal_rollback_status=partial
partial_failure_report_required=1
removal_allowed=0
removal_performed=0
host_mutation_performed=0
```

Invalid reports preserve:

```text
removal_rollback_status=invalid
removal_rollback_denial=invalid-classifier-input
removal_allowed=0
removal_performed=0
host_mutation_performed=0
```

## Install-preparation meaning

This classifier closes the removal/rollback side of the local RPM gate posture.

The install-preparation sequence after this implementation should remain evidence-bound:

```text
1. Merge the pure removal/rollback classifier.
2. Add status/index alignment.
3. Add a post-install verification contract.
4. Add a command transcript contract.
5. Add a tightly gated local RPM execution lane only after install, removal, rollback, and post-install verification posture are all represented.
```

## Validation

Classifier guard:

```sh
sh scripts/test-fedora-rpm-removal-rollback-classifier.sh
```

Expected output:

```text
fedora_rpm_removal_rollback_classifier: ok
```

Docs guard:

```sh
sh scripts/test-fedora-rpm-removal-rollback-classifier-docs.sh
```

Expected output:

```text
fedora_rpm_removal_rollback_classifier_docs: ok
```

## Boundary

This implementation is a classifier only.

It does not remove packages, roll back packages, install packages, validate sudo, create RPM artifacts, run `rpm`, run `dnf`, open the network, start services, change boot entries, load kernel modules, change host policy, claim Fedora approval, or claim production installer readiness.
