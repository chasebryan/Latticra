# Fedora RPM Install/Remove Transcript Contract

Status: no-effect RPM install/remove transcript contract
Scope: define future disposable Fedora RPM install/remove evidence without installing or removing RPM packages.

## Purpose

This contract records the install/remove transcript evidence required before any future Fedora binary RPM artifact can be accepted as installable validation evidence.

The goal is narrow: a future Fedora RPM install/remove transcript must prove that installation happens only inside a disposable Fedora validation environment, the expected no-effect CLI payload appears after install, the package can be removed cleanly, and no host-level service, systemd, kernel, privileged-helper, or network authority is introduced.

This contract is documentation-only and static.

It does not run `dnf`.

It does not run `rpm`.

It does not install packages.

It does not remove packages.

It does not create RPM artifacts.

It does not inspect RPM artifacts.

It does not publish packages.

It does not submit Latticra to Fedora.

It does not mutate a host.

```text
fedora_rpm_install_remove_transcript_contract_present=1
fedora_rpm_payload_inspection_contract_present=1
rpm_install_remove_transcript_contract_present=1
install_remove_transcript_contract_present=1
fedora_rpm_install_remove_transcript_contract_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
fedora_rpm_payload_inspection_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
fedora_mock_build_gate_state=closed-no-effect
rpm_install_remove_disposable_environment_required=1
rpm_install_remove_transcript_present=0
rpm_package_install_run=0
rpm_package_remove_run=0
rpm_dnf_install_run=0
rpm_dnf_remove_run=0
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
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Required Future Evidence

Future Fedora RPM install/remove validation must run only in a disposable Fedora environment.

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
rpm_binary_package_name_pattern=latticra-0.0.0-0.1.local${FEDORA_DIST}.${RPM_ARCH}.rpm
rpm_binary_artifact_sha256
rpm_payload_expected_bin=/usr/bin/latticra
rpm_payload_expected_doc=/usr/share/doc/latticra/README.md
fedora_target_distribution
fedora_dist_tag
rpm_arch
environment_identifier
```

## Transcript Requirements

A future Fedora RPM install/remove transcript must record:

```text
environment_identifier
fedora_target_distribution
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
fedora_mock_build_evidence_present=0
```

## Command Boundary

This contract does not:

```text
run dnf install
run dnf remove
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
submit Latticra to Fedora
claim official Fedora package status
claim Fedora endorsement
claim package readiness
claim Fedora distribution readiness
claim production readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md
docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md
docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md
docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
packaging/fedora/latticra.spec
```

The local mock-build gate remains closed. This install/remove transcript contract only defines the evidence future disposable validation environments must produce after RPM artifacts exist and payload inspection evidence is accepted.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-rpm-install-remove-transcript-contract.sh
```

Expected output:

```text
fedora_rpm_install_remove_transcript_contract: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not RPM artifact evidence, not RPM payload evidence, not install evidence, not remove evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
