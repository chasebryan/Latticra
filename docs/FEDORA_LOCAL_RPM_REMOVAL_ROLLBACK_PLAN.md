# Fedora Local RPM Removal and Rollback Plan

Status: planning record
Scope: define removal, rollback, and post-removal verification requirements before any Fedora local RPM execution lane is added.

## Purpose

The Fedora RPM gate classifier can now report whether a future local RPM gate is allowed or denied.

Before any host-changing execution lane exists, Latticra needs a removal and rollback plan.

This plan defines how a future lane must identify an installed local RPM package, verify ownership, request removal, verify absence, and report partial failure without hiding host state.

This is planning only. It does not remove or install anything.

## Removal boundary

A future removal lane must be explicit and operator-directed.

It must never infer that host changes are safe merely because a package name exists.

The removal lane must require:

```text
operator_removal_confirmation=1
package_name=latticra
package_query_ready=1
installed_package_detected=1
owned_file_list_available=1
post_removal_absence_check_planned=1
failure_report_planned=1
```

If any field is missing, false, unknown, or contradictory, the removal lane must deny execution.

## Package identification

A future implementation must identify the package using a bounded package identity record:

```text
package_name
package_epoch
package_version
package_release
package_arch
package_origin=local-rpm
```

The package name must be exact. Partial matching, fuzzy matching, glob matching, or substring matching must not be used for removal decisions.

## Ownership verification

Before removal can be allowed, a future lane must prove the package owns the expected files.

For the current documentation-oriented package posture, expected evidence includes:

```text
package_query_ready=1
owned_file_list_available=1
readme_owned_by_package=1
unexpected_runtime_surface_absent=1
```

The future lane must not assume ownership from file existence alone.

## Current package posture

The current Fedora package path remains documentation/package-shape oriented.

A future removal plan should expect documentation ownership evidence first, not runtime service ownership.

The following runtime surfaces should still be absent unless a later package posture intentionally changes them:

```text
/usr/bin/latticra
/etc/latticra
systemd service surface
kernel module surface
boot entry surface
SELinux policy surface
```

## Removal request boundary

A future implementation may only request removal after the explicit removal gate allows it.

The removal request must be local-only and must not open the network, build packages, alter boot entries, start or stop services, load kernel modules, or change policy.

The removal action, when eventually implemented, must produce a transcript boundary and deterministic report fields before and after the request.

## Post-removal verification

A future removal lane must check and report:

```text
package_absent_after_removal
owned_files_absent_or_reclassified
readme_absent_or_no_longer_owned
runtime_surface_absent
service_surface_absent
kernel_surface_absent
boot_surface_absent
policy_surface_absent
```

If post-removal verification fails, the lane must report partial state explicitly.

## Partial failure reporting

A future implementation must not hide partial failures.

Required partial-failure labels include:

```text
removal-request-failed
package-still-installed
owned-files-remain
ownership-query-failed
absence-check-failed
unknown-host-state
operator-aborted
```

## Rollback meaning

For the local RPM lane, rollback means returning to a clearly reported host state after a failed install or removal attempt.

At this stage, rollback does not mean automatic system recovery, rpm-ostree rollback, boot rollback, filesystem snapshot rollback, service restart, or kernel recovery.

Those require separate contracts.

## Future report fields

A future removal/rollback classifier may report fields such as:

```text
FEDORA LOCAL RPM REMOVAL ROLLBACK PLAN
removal_plan_status=planned
operator_removal_confirmation_required=1
package_identity_required=1
ownership_verification_required=1
post_removal_absence_required=1
partial_failure_report_required=1
network_allowed=0
package_build_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
kernel_operation_allowed=0
policy_operation_allowed=0
host_mutation_performed=0
```

## Relationship to the RPM gate classifier

The RPM gate classifier can report that the future local RPM gate is allowed.

That is not enough to execute host changes.

Before execution, the project must also have:

```text
removal_or_rollback_plan_present=1
post_install_verification_plan_present=1
operator_execution_confirmation=1
clear command transcript boundary
```

## Implementation sequence

Recommended order:

```text
1. Add this removal and rollback plan.
2. Add a removal/rollback classifier contract.
3. Add a pure removal/rollback classifier implementation.
4. Add a post-install verification contract.
5. Add a command transcript contract.
6. Only then consider a tightly gated local RPM execution lane.
```

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-local-rpm-removal-rollback-plan.sh
```

Expected output:

```text
fedora_local_rpm_removal_rollback_plan: ok
```

## Non-claims

This plan does not implement removal, rollback, installation, host mutation, package execution, privilege validation, package build behavior, network use, service operation, boot operation, kernel module operation, Fedora approval, or production installer readiness.
