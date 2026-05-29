# Latticra Release Artifact Staging Directory

Status: tracked no-effect staging directory
Scope: future production-installer release artifact candidate staging path.

This directory exists so release-artifact preflight checks can resolve the intended parent path before any real artifact is created.

Current state:

```text
release_artifact_staging_directory_present=1
release_artifact_staging_directory_path=artifacts/release
release_artifact_staging_directory_no_effect=1
release_artifact_candidate_parent_dir_exists=1
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

Do not place generated RPMs, source archives, signatures, checksums, public keys, or accepted evidence here unless the corresponding release-artifact candidate lane has explicit reviewed authority.

This directory is not a release artifact, not release evidence, not signing evidence, not publication, not promotion, and not production installer readiness.
