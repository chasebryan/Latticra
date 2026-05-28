# Fedora RPM Payload Inspection Contract Status

Status: rpm-payload-inspection/status alignment
Date: 2026-05-27
Scope: status record for the no-effect Fedora RPM payload inspection contract.

## Summary

Latticra now has a no-effect Fedora RPM payload inspection contract.

The contract records future source RPM and binary RPM payload inspection requirements.

It does not create RPM artifacts.

It does not inspect RPM artifacts.

It does not run `rpm`, `rpm2cpio`, `cpio`, `rpmbuild`, `mock`, or `dnf builddep`.

It does not install packages, publish packages, submit to Fedora, or mutate a host.

## Current classification

```text
fedora_rpm_payload_inspection_contract_present=1
fedora_rpm_artifact_naming_contract_present=1
fedora_local_mock_build_environment_contract_present=1
rpm_payload_inspection_contract_present=1
payload_inspection_contract_present=1
fedora_rpm_payload_inspection_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
fedora_rpm_artifact_naming_contract_state=specified-no-effect
fedora_mock_build_gate_state=closed-no-effect
rpm_artifact_created=0
rpm_payload_inspection_run=0
source_rpm_payload_inspection_run=0
binary_rpm_payload_inspection_run=0
rpm_payload_accepted=0
rpm_artifact_sha256_recorded=0
rpm_payload_listing_sha256_recorded=0
source_rpm_payload_listing_sha256_recorded=0
binary_rpm_payload_listing_sha256_recorded=0
fedora_mock_build_evidence_present=0
rpm_installed_on_host=0
rpm_removed_from_host=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-rpm-payload-inspection-contract.sh
```

Expected output:

```text
fedora_rpm_payload_inspection_contract: ok
```

## Next recommended lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Completed follow-on lane

```text
docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
scripts/test-fedora-rpm-install-remove-transcript-contract.sh
.github/workflows/fedora-rpm-install-remove-transcript-contract.yml
```

## Non-claims

This status record is not environment evidence, not source archive acceptance, not mock build evidence, not source RPM evidence, not binary RPM evidence, not RPM payload evidence, not rpmlint evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
