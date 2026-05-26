# Ubuntu Local Deb Install Remove Evidence Contract

Status: no-effect local deb install/remove evidence contract
Scope: evidence schema for a future reviewed Ubuntu local deb install/remove transcript.

## Purpose

This contract defines the evidence required before a future local Ubuntu deb can claim install or remove behavior.

It does not run `dpkg -i`, `apt install`, `apt remove`, `dpkg -r`, `dpkg -P`, `lintian`, `dpkg-buildpackage`, `debuild`, `sbuild`, or `pbuilder`. It does not create, install, remove, publish, upload, or accept a deb package.

## Required Inputs

```text
ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1
ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript
local_deb_build_transcript_accepted=1
deb_artifact_created=1
deb_artifact_digest_recorded=1
```

## Required Evidence Before Promotion

```text
install_remove_test_environment_recorded=1
install_command_recorded=1
install_exit_status_recorded=1
installed_payload_listing_recorded=1
usr_bin_latticra_installed=1
status_command_after_install_recorded=1
remove_command_recorded=1
remove_exit_status_recorded=1
post_remove_absence_checked=1
residual_payload_reviewed=1
install_remove_findings_classified=1
host_mutation_scope_reviewed=1
ubuntu_install_remove_evidence_unblocked=1
```

## Current State

```text
ubuntu_local_deb_install_remove_evidence_contract_present=1
ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript
local_deb_build_transcript_accepted=0
deb_artifact_created=0
deb_artifact_digest_recorded=0
deb_installed_on_host=0
deb_removed_from_host=0
install_remove_test_environment_recorded=0
install_command_recorded=0
install_exit_status_recorded=0
installed_payload_listing_recorded=0
usr_bin_latticra_installed=0
status_command_after_install_recorded=0
remove_command_recorded=0
remove_exit_status_recorded=0
post_remove_absence_checked=0
residual_payload_reviewed=0
install_remove_findings_classified=0
host_mutation_scope_reviewed=0
ubuntu_install_remove_evidence_unblocked=0
ppa_claimed=0
ubuntu_archive_ready=0
production_installer_ready=0
root_installer_ready=0
```

## Relationship To Build Evidence

The Ubuntu local deb build transcript acceptance gate must be unblocked and a reviewed local deb build transcript must be accepted before this install/remove evidence contract can advance.

This contract is intentionally closed today. It records the future evidence shape without installing a package, removing a package, or mutating the host.

## Non-Claims

This contract does not claim install success, remove success, package-manager integration, Debian Policy compliance, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, daily-driver readiness, root installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-local-deb-install-remove-evidence-contract.sh
```

Expected output:

```text
ubuntu_local_deb_install_remove_evidence_contract: ok
```
