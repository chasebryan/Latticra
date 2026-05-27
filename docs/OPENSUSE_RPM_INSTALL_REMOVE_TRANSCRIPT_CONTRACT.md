# openSUSE RPM Install/Remove Transcript Contract

Status: active RPM install/remove transcript contract
Scope: define future disposable openSUSE RPM install/remove evidence without installing or removing RPM packages.

## Purpose

This contract records the install/remove transcript evidence required before any future openSUSE binary RPM artifact can be accepted as installable validation evidence.

The goal is narrow: a future RPM install/remove transcript must prove that installation happens only inside a disposable openSUSE validation environment, the expected no-effect CLI payload appears after install, the package can be removed cleanly, and no host-level service, systemd, kernel, privileged-helper, or network authority is introduced.

This contract is documentation-only and static. It does not run `zypper`, run `rpm`, install packages, remove packages, create RPM artifacts, inspect RPM artifacts, publish packages, create an Open Build Service project, submit Latticra to openSUSE, or claim package readiness.

## Current Install/Remove State

```text
opensuse_rpm_install_remove_transcript_contract_present=1
opensuse_obs_publication_non_claim_review_contract_present=1
rpm_install_remove_transcript_contract_present=1
install_remove_transcript_contract_present=1
obs_publication_non_claim_review_present=1
publication_non_claim_review_present=1
opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
opensuse_rpm_build_gate_state=closed-no-effect
payload_inspection_contract_state=specified-no-effect
rpm_install_remove_disposable_environment_required=1
rpm_install_remove_transcript_present=0
rpm_package_install_run=0
rpm_package_remove_run=0
rpm_zypper_install_run=0
rpm_zypper_remove_run=0
rpm_cli_install_run=0
rpm_cli_remove_run=0
rpm_installed_on_host=0
rpm_removed_from_host=0
host_install_allowed=0
host_remove_allowed=0
host_mutation_allowed=0
service_state_change_allowed=0
rpm_artifact_created=0
rpm_payload_accepted=0
rpm_validation_result_promoted=0
package_readiness_claimed=0
```

## Required Future Evidence

Future openSUSE RPM install/remove validation must run only in a disposable openSUSE environment.

Required transcript evidence:

```text
rpm_install_remove_transcript_required=1
rpm_install_remove_transcript_present=0
rpm_payload_post_install_check_required=1
rpm_payload_post_remove_absence_check_required=1
rpm_service_state_change_allowed=0
rpm_systemd_unit_enable_allowed=0
rpm_scriptlet_effect_allowed=0
rpm_kernel_file_allowed=0
rpm_network_authority_allowed=0
rpm_privileged_helper_allowed=0
```

The future transcript must bind install/remove evidence to:

```text
rpm_binary_package_name_pattern=latticra-0.0.0-0.local.${RPM_ARCH}.rpm
rpm_binary_artifact_sha256
rpm_payload_expected_bin=/usr/bin/latticra
rpm_payload_expected_doc=/usr/share/doc/packages/latticra/README.md
```

## Transcript Requirements

A future openSUSE RPM install/remove transcript must record:

```text
environment_identifier
opensuse_target_distribution
operator_authorization_reference
rpm_artifact_name
rpm_artifact_sha256
pre_install_package_state
install_command
install_exit_code
post_install_payload_listing
post_install_cli_no_effect_output
rpm_query_after_install
service_state_after_install
remove_command
remove_exit_code
post_remove_absence_report
post_remove_package_state
scriptlet_effect_review
host_mutation_review
```

The transcript must be reviewed before an RPM artifact can be accepted as install/remove-valid.

## Current Blockers

RPM install/remove acceptance remains blocked because the current repository still has:

```text
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
environment_transcript_present=0
explicit_operator_build_authorization=0
obs_publication_non_claim_review_present=1
```

## Command Boundary

This contract does not:

```text
run zypper install
run zypper remove
run rpm -i
run rpm -U
run rpm -e
install Latticra on a host
remove Latticra from a host
change service state
enable a systemd unit
create package artifacts
inspect package artifacts
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
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
```

The local RPM build gate remains closed. This install/remove transcript contract only defines the evidence future disposable validation environments must produce after RPM artifacts exist and payload inspection evidence is accepted.

## Next Slice

Completed follow-on OBS publication non-claim review contract:

```text
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
.github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
```

That lane records Open Build Service, submit-request, official-package, and SUSE endorsement non-claims without publishing packages.

Completed follow-on RPM validation promotion blocker matrix contract:

```text
docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
scripts/test-opensuse-rpm-validation-promotion-blocker-matrix-contract.sh
.github/workflows/opensuse-rpm-validation-promotion-blocker-matrix-contract.yml
```

That lane ties source, `rpmlint`, environment, artifact, payload, install/remove, and OBS non-claim columns together while keeping build evidence intake and readiness blocked.

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial contract before any local build lane can open.
```

That future lane should define how build evidence intake is refused until the blocker matrix opens, while keeping RPM builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
```

Expected output:

```text
opensuse_rpm_install_remove_transcript_contract: ok
```
