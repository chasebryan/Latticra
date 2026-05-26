# openSUSE RPM Artifact Naming Contract

Status: active RPM artifact naming contract
Scope: define future openSUSE source RPM and binary RPM artifact names and output boundaries without creating RPM artifacts.

## Purpose

This contract records the artifact names, output-directory rules, checksum binding, retention requirements, and Open Build Service non-claims required before any future openSUSE local RPM build can create source RPM or binary RPM files.

The goal is narrow: RPM artifacts must have predictable names, be written only inside a disposable validation environment, bind back to the source archive digest, and remain non-published review outputs until separate payload inspection, install/remove, and OBS publication review contracts exist.

This contract is documentation-only and static. It does not run `rpmbuild`, run `osc build`, run `spec-cleaner`, create RPM artifacts, install Latticra, publish packages, create an Open Build Service project, submit Latticra to openSUSE, or claim package readiness.

## Current Artifact Naming State

```text
opensuse_rpm_artifact_naming_contract_present=1
rpm_artifact_naming_contract_present=1
opensuse_rpm_artifact_naming_contract_state=specified-no-effect
opensuse_rpm_build_gate_state=closed-no-effect
opensuse_rpm_build_environment_contract_state=specified-no-effect
rpm_artifact_output_directory_required_under_disposable_environment=1
rpm_artifact_output_directory_created=0
repository_rpm_artifact_write_allowed=0
publication_directory_write_allowed=0
rpm_artifact_created=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_artifact_published=0
rpm_installed_on_host=0
package_readiness_claimed=0
```

## Source RPM Artifact Name

Future source RPM artifact names must be derived from the current openSUSE spec `Name`, `Version`, and `Release` values.

```text
rpm_source_package_name=latticra-0.0.0-0.local.src.rpm
rpm_source_archive_name=latticra-0.0.0.tar.gz
rpm_source_artifact_name_pattern_recorded=1
rpmbuild_bs_run=0
source_rpm_artifact_created=0
```

The source RPM name is a future local validation artifact only. It is not an accepted source package, Open Build Service source, submit-request record, or publication claim.

## Binary RPM Artifact Name

Future binary RPM artifact names must be derived from the current openSUSE spec `Name`, `Version`, `Release`, and the build environment architecture.

```text
rpm_binary_package_name_pattern=latticra-0.0.0-0.local.${RPM_ARCH}.rpm
rpm_binary_arch_token_required=1
rpm_binary_artifact_name_pattern_recorded=1
rpmbuild_ba_run=0
rpmbuild_bb_run=0
binary_rpm_artifact_created=0
```

The `${RPM_ARCH}` token must be resolved from the disposable openSUSE environment transcript before any binary RPM artifact can be accepted.

## Output Boundary

Future RPM artifacts must be written only under a disposable RPM topdir inside a disposable validation environment. The repository itself remains a no-artifact workspace.

```text
artifact_output_root_under_disposable_rpmtop=1
rpm_source_artifact_output_directory=rpmtop/SRPMS/
rpm_binary_artifact_output_directory_pattern=rpmtop/RPMS/${RPM_ARCH}/
repository_rpm_artifact_write_allowed=0
root_workspace_rpm_artifact_write_allowed=0
publication_directory_write_allowed=0
artifact_retention_policy_required=1
artifact_cleanup_policy_required=1
```

Any future RPM artifact transcript must bind each package file to:

```text
source_archive_sha256
rpm_input_archive_sha256
rpm_artifact_sha256
artifact_size_bytes
artifact_output_directory
artifact_generation_command
environment_identifier
operator_authorization_reference
```

## Current Blockers

RPM artifact creation remains blocked because the current repository still has:

```text
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
license_expression_reviewed=1
package_notice_obligations_reviewed=0
buildrequires_reviewed=0
explicit_operator_build_authorization=0
environment_transcript_present=0
rpm_payload_inspection_contract_present=0
rpm_install_remove_transcript_contract_present=0
obs_publication_non_claim_review_present=0
```

## Command Boundary

This contract does not:

```text
run rpmbuild
run rpmbuild -ba
run rpmbuild -bb
run rpmbuild -bs
run osc build
run osc commit
run spec-cleaner
create .src.rpm artifacts
create binary .rpm artifacts
install Latticra on a host
publish package artifacts
create an Open Build Service project
submit Latticra to openSUSE
claim official openSUSE package status
claim SUSE endorsement
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
```

The local RPM build gate remains closed. This artifact naming contract only records the names and output boundaries future validation artifacts must use after separate source, lint, license, notice, BuildRequires, environment, authorization, payload inspection, install/remove, and OBS non-claim evidence exists.

## Next Slice

Recommended next slice:

```text
Add openSUSE RPM payload inspection contract before any RPM artifact can be accepted.
```

That future lane should define how source RPM and binary RPM payloads are inspected after creation while keeping `opensuse_rpm_build_gate_state=closed-no-effect` until the remaining prerequisites are satisfied.

## Validation

Run:

```sh
sh scripts/test-opensuse-rpm-artifact-naming-contract.sh
```

Expected output:

```text
opensuse_rpm_artifact_naming_contract: ok
```
