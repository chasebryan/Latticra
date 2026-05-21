# Fedora Local RPM Execution Lane

Status: active execution lane
Scope: tightly gated local RPM install/remove mutation inside disposable Fedora CI only.
Evidence level: 6

## Purpose

This lane is the first intentionally mutating Fedora RPM lane for Latticra.

It builds the local-only Latticra RPM, installs it into a disposable Fedora CI container, verifies the installed package state, removes it from that same container, and verifies post-removal absence.

This is the first lane where Latticra intentionally records:

```text
install_mutation_performed=1
removal_mutation_performed=1
container_filesystem_mutated=1
container_rpmdb_mutated=1
```

The mutation is restricted to a throwaway Fedora CI container.

## Hard gate

The execution script refuses to run unless all of the following are true:

```text
LATTICRA_ALLOW_DISPOSABLE_RPM_MUTATION=1
ID=fedora
GITHUB_ACTIONS=true
running_as_root=1
rpmbuild_present=1
rpm_present=1
```

If any condition is absent, the lane exits before installing or removing the package.

## What mutates

The lane mutates only the disposable Fedora container:

```text
rpm_database=mutated
/usr/share/doc/latticra/README.md=installed_then_removed
```

It does not mutate a developer workstation, laptop, VM host, boot entry, kernel module set, service registry, SELinux policy, network configuration, or firmware state.

## Execution sequence

The guard performs this sequence:

```text
1. Verify the disposable Fedora CI mutation gate.
2. Build a temporary Source0 archive from the checked-out tree.
3. Run rpmbuild -bb against packaging/fedora/latticra.spec.
4. Locate the produced local latticra RPM.
5. Inspect package metadata and payload.
6. Install the local RPM with rpm -Uvh.
7. Query installed package state with rpm -q and rpm -ql.
8. Verify package files with rpm -V.
9. Confirm README payload exists under /usr/share/doc/latticra/README.md.
10. Confirm premature runtime surfaces are absent.
11. Remove the package with rpm -e.
12. Confirm rpm -q latticra fails after removal.
13. Confirm README payload is absent after removal.
14. Emit a deterministic execution report.
```

## Required report fields

The lane emits:

```text
FEDORA LOCAL RPM EXECUTION LANE
execution_status=ok
install_mutation_allowed=1
install_mutation_performed=1
removal_mutation_allowed=1
removal_mutation_performed=1
container_filesystem_mutated=1
container_rpmdb_mutated=1
developer_host_mutation_performed=0
boot_operation_performed=0
kernel_operation_performed=0
service_operation_performed=0
policy_operation_performed=0
network_allowed_during_rpm_execution=0
post_removal_absence_verified=1
rollback_planned=1
partial_failure_report_required=1
evidence_level=6
```

## Package truth preserved

The current RPM remains a documentation-only local package.

Expected installed payload:

```text
/usr/share/doc/latticra/README.md
```

The lane rejects premature runtime surfaces such as:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
```

## Relationship to previous gates

This lane follows the Fedora RPM gate classifier and the Fedora RPM removal rollback classifier.

The RPM gate proves install posture.

The removal rollback classifier proves removal/rollback posture.

This execution lane is where the disposable container actually mutates.

## Validation

Execution guard:

```sh
LATTICRA_ALLOW_DISPOSABLE_RPM_MUTATION=1 sh scripts/test-fedora-local-rpm-execution-lane.sh
```

Expected output:

```text
fedora_local_rpm_execution_lane: ok
```

Docs guard:

```sh
sh scripts/test-fedora-local-rpm-execution-lane-docs.sh
```

Expected output:

```text
fedora_local_rpm_execution_lane_docs: ok
```

## Non-claims

This lane does not install Latticra on a developer host, daily-driver Fedora system, immutable Fedora host, VM host, production host, or user workstation.

It does not publish artifacts, submit to Fedora, claim Fedora approval, claim production installer readiness, validate sudo on a user host, start services, change boot entries, load kernel modules, modify SELinux policy, open runtime network access, or assert that Latticra is ready as a system installer.
