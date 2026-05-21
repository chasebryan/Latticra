# Fedora Disposable VM Local RPM Validation Lane

Status: gated validation lane
Evidence level: 9 target
Scope: local RPM validation on a disposable Fedora VM target only.

## Purpose

This lane defines the first host-facing Fedora RPM validation path for Latticra.

The lane is restricted to a disposable Fedora VM with a clean snapshot, a recovery path, and explicit operator consent.

It is not for a daily-driver system, production host, immutable Fedora image, or unclear target.

## Hard gate

The validation script must refuse unless all of the following are true:

```text
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1
LATTICRA_TARGET_IS_DAILY_DRIVER=0
LATTICRA_TARGET_IS_PRODUCTION_HOST=0
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1
LATTICRA_TARGET_HAS_RECOVERY_PATH=1
LATTICRA_OPERATOR_CONSENT_RECORDED=1
ID=fedora
rpm_present=1
rpmbuild_present=1
```

## Required package checks

Before any package operation, the lane must verify:

```text
rpm_name_is_latticra=1
rpm_version_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
```

Expected package payload remains:

```text
/usr/share/doc/latticra/README.md
```

Forbidden payload surfaces include:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
```

## Validation sequence

The guarded lane is expected to:

```text
1. Verify disposable Fedora VM evidence.
2. Build the local RPM from the current tree.
3. Inspect package metadata.
4. Inspect package payload.
5. Validate the package payload remains documentation-only.
6. Apply the local RPM to the disposable Fedora VM target.
7. Query the installed package state.
8. Verify the README payload exists.
9. Verify the package files.
10. Remove the package.
11. Confirm the package is absent.
12. Confirm the README payload is absent.
13. Emit a deterministic validation report.
```

## Required report fields

```text
FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE
validation_status=ok
package_name=latticra
package_version_recorded=1
disposable_vm_target_verified=1
snapshot_evidence_present=1
recovery_evidence_present=1
operator_consent_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
vm_rpmdb_mutated=1
vm_filesystem_mutated=1
install_validation_performed=1
removal_validation_performed=1
post_removal_absence_verified=1
live_host_validation_completed=1
host_install_ready=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
evidence_level=9
```

## Non-claims

This lane does not make Latticra production ready.

It does not claim Fedora approval.

It does not claim Fedora distribution readiness.

It does not make daily-driver installation eligible.

## Validation guard

```sh
sh scripts/test-fedora-disposable-vm-local-rpm-validation-lane-docs.sh
```

Expected output:

```text
fedora_disposable_vm_local_rpm_validation_lane_docs: ok
```

## Next recommended Fedora lane

```text
Add disposable Fedora VM local RPM validation status alignment
```

After real validation evidence exists, the root README can be overhauled to describe the disposable Fedora VM validation path without claiming production or Fedora distribution readiness.
