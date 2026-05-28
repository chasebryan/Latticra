# Production Installer Release Toolchain Availability Audit Contract

Status: no-effect release toolchain availability audit contract
Evidence level: 10 target, command visibility audit only
Scope: report visible local command availability for a future production-installer release artifact candidate without installing tools, invoking build or query tools, signing artifacts, verifying signatures, publishing artifacts, using network access, invoking package managers, or mutating the host.

## Purpose

The release-artifact candidate preflight requires local archive, checksum, RPM build/query, GPG, and Git command visibility before a future release artifact candidate can pass.

This contract records a no-effect audit for that blocker. It checks command visibility only and keeps tool installation, package-manager execution, build execution, signing, verification, publication, and host mutation closed.

It does not prove the tools are configured correctly, run any build, or create release evidence.

## Command

```sh
sh scripts/production-installer-release-toolchain-availability-audit.sh --tag v0.2.0edge
```

## Current classification

```text
release_toolchain_availability_audit_present=1
release_toolchain_availability_audit_mode=no-effect-command-visibility-report
release_toolchain_required_for_release_candidate=1
release_toolchain_availability_audit_passed=0
release_toolchain_ready=0
git_available=<observed>
tar_available=<observed>
gzip_available=<observed>
rpmbuild_available=0
release_artifact_build_tool_available=0
rpm_available=0
release_artifact_query_tool_available=0
gpg_available=<observed>
sha256_tool_available=<observed>
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
release_artifact_promotion_gate_passed=0
release_artifact_created=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted=0
production_installer_ready=0
host_mutation_performed=0
source_archive_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
signature_created=0
artifact_signed=0
signature_verified=0
artifact_published=0
package_manager_invoked=0
network_allowed=0
```

## Required source records

The audit binds the current release-candidate toolchain posture:

```text
production_installer_ready=0
release_artifact_candidate_preflight_present=1
release_artifact_build_tool_available=0
release_artifact_query_tool_available=0
rpmbuild_available=1
rpm_available=1
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-release-toolchain-availability-audit-contract.sh
```

Expected output:

```text
production_installer_release_toolchain_availability_audit_contract: ok
```

## Next implementation lane

```text
Provide reviewed disposable build/query toolchain evidence for the intended release environment before creating a tagged production-installer release artifact candidate.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This audit is not a release toolchain.

It is not tool installation, not a build, not an RPM query, not a generated release artifact, not a release checksum, not artifact signing, not signature verification, not artifact publication, not artifact promotion, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not host mutation, and not production installer readiness.
