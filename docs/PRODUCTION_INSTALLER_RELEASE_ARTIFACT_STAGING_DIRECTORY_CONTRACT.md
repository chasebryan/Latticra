# Production Installer Release Artifact Staging Directory Contract

Status: no-effect release-artifact staging directory contract
Evidence level: 10 target, staging path only
Scope: tracked workspace directory for a future production-installer release artifact candidate without creating, signing, verifying, publishing, installing, invoking build tools, or accepting evidence.

## Purpose

The release-artifact candidate preflight reports the intended artifact parent directory. Before this contract, the default path `artifacts/release/latticra-production-installer.rpm` had no tracked parent directory in the repository.

This contract closes only that repository-side staging gap. It makes the parent path explicit while keeping release artifact creation, checksum recording, signing, verification, evidence writes, promotion, package-manager execution, and production readiness closed.

## Required tracked file

```text
artifacts/release/README.md
```

## Current classification

```text
release_artifact_staging_directory_present=1
release_artifact_staging_directory_path=artifacts/release
release_artifact_staging_directory_no_effect=1
release_artifact_candidate_parent_dir_exists=1
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
release_artifact_created=0
release_artifact_present=0
source_archive_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
signature_created=0
checksum_recorded=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
host_mutation_performed=0
```

## Forbidden staged outputs

Until the release-artifact candidate lane has explicit reviewed authority, the staging directory must not contain:

```text
*.rpm
*.src.rpm
*.tar
*.tar.gz
*.tgz
*.sig
*.asc
*.sha256
*.evidence
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-release-artifact-staging-directory-contract.sh
```

Expected output:

```text
production_installer_release_artifact_staging_directory_contract: ok
```

## Next implementation lane

```text
Satisfy the remaining release-artifact candidate preflight inputs: clean tracked worktree, RPM build/query tooling, checksum tooling, GPG visibility, and an explicit signing identity reference.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This contract is not a generated release artifact.

It is not a source archive, not an RPM build, not a checksum, not a signature, not signature verification, not a public signing-key record, not artifact evidence, not artifact promotion, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not host mutation, and not production installer readiness.
