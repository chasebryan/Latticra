# Fedora RPM Removal Rollback Classifier Contract

Status: contract record
Scope: define the pure classifier required before any Fedora RPM removal or rollback action can be implemented.
Evidence level: 5 target, contract only

## Purpose

The Fedora local RPM removal and rollback plan defines how a future lane must reason about package identity, ownership verification, post-removal absence checks, and partial failure reporting.

This contract defines the next implementation boundary: a pure classifier that evaluates whether removal or rollback posture is ready, denied, partial, or invalid.

This is not a removal implementation.

The classifier must report state only. It must not request removal, install packages, validate privilege, open the network, start services, change boot entries, load kernel modules, or change host policy.

## Required classifier inputs

A future classifier must consume an explicit record containing at least:

```text
operator_removal_confirmation
package_name
package_identity_present
package_query_ready
installed_package_detected
owned_file_list_available
readme_owned_by_package
unexpected_runtime_surface_absent
post_removal_absence_check_planned
failure_report_planned
network_required
service_operation_requested
boot_operation_requested
kernel_operation_requested
policy_operation_requested
```

The classifier must fail closed when fields are missing, unknown, contradictory, or unsafe.

## Required allow conditions

The classifier may report removal-ready only when all conditions are true:

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

All other combinations must report denied, partial, or invalid.

## Required denial reasons

The classifier must report deterministic denial reasons such as:

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

## Required report fields

A future implementation should emit a report beginning with:

```text
FEDORA RPM REMOVAL ROLLBACK CLASSIFIER
```

For ready cases, required report fields include:

```text
removal_rollback_status=removal-ready
removal_allowed=1
rollback_planned=1
removal_performed=0
host_mutation_performed=0
network_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
kernel_operation_allowed=0
policy_operation_allowed=0
evidence_level=5
```

For denied cases, required report fields include:

```text
removal_rollback_status=denied
removal_allowed=0
removal_performed=0
host_mutation_performed=0
```

For partial cases, required report fields include:

```text
removal_rollback_status=partial
partial_failure_report_required=1
removal_performed=0
host_mutation_performed=0
```

## Partial state classes

The classifier should distinguish planned denial from partial host state.

Planned denial means removal should not be attempted.

Partial state means the evidence suggests a future removal/rollback execution lane must report incomplete or uncertain host state, such as:

```text
package-installed-but-ownership-unknown
owned-files-present-but-package-query-failed
runtime-surface-present-before-removal
absence-check-not-ready
unknown-host-state
```

## Relationship to the RPM gate classifier

The Fedora RPM gate classifier reports whether the future local RPM gate is allowed.

This removal/rollback classifier must exist before any host-changing local RPM execution lane is added.

The two classifiers together should prove:

```text
install gate evidence exists
removal or rollback posture exists
post-removal verification is planned
partial failure reporting is planned
```

## Implementation sequence

Recommended next order:

```text
1. Add this removal/rollback classifier contract.
2. Add a pure C removal/rollback classifier.
3. Add a focused test runner and docs guard.
4. Add status/index alignment after merge.
5. Add post-install verification contract.
6. Add command transcript contract.
7. Only then consider a tightly gated local RPM execution lane.
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-rpm-removal-rollback-classifier-contract.sh
```

Expected output:

```text
fedora_rpm_removal_rollback_classifier_contract: ok
```

## Non-claims

This contract does not implement removal, rollback, installation, host mutation, package execution, privilege validation, package build behavior, network use, service operation, boot operation, kernel module operation, Fedora approval, or production installer readiness.
