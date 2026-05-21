# Local Installer Artifact Manifest Contract

Status: contract record
Evidence level: 10 target, manifest contract only
Scope: required metadata for any future local installer artifact before it can be considered for production-installer readiness.

## Purpose

The production-installer readiness contract requires an installer artifact manifest before any installer can be recommended for general use.

This contract defines the minimum manifest fields that must exist before the project can evaluate installer artifacts.

This is not an installer.

This does not build, sign, publish, distribute, install, uninstall, upgrade, or rollback an installer.

This does not claim production installer readiness.

## Current readiness boundary

The current project state remains:

```text
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

The current evidence-backed prerequisite is limited to disposable Fedora VM validation of the local no-effect CLI RPM payload:

```text
host_install_ready_for_cli_payload=1
validated_payload_cli=/usr/bin/latticra
validated_payload_readme=/usr/share/doc/latticra/README.md
```

## Required manifest file

A future installer artifact must include a manifest file at a stable path such as:

```text
artifacts/<artifact-name>/manifest.txt
```

The manifest must be plain text, line-oriented, deterministic, and reviewable.

## Required manifest fields

A complete artifact manifest must include:

```text
LATTICRA INSTALLER ARTIFACT MANIFEST
manifest_version=1
artifact_name=<recorded>
artifact_version=<recorded>
artifact_arch=<recorded>
artifact_format=<recorded>
artifact_filename=<recorded>
artifact_size_bytes=<recorded>
artifact_sha256=<recorded>
artifact_signature=<recorded-or-none>
artifact_signing_key_id=<recorded-or-none>
artifact_sbom_path=<recorded-or-none>
artifact_license_metadata_path=<recorded>
source_repository=Bryforge/Latticra
source_commit=<recorded>
source_tag=<recorded-or-none>
build_environment=<recorded>
build_command_recorded=1
build_reproducible=<0-or-1>
supported_target_family=<recorded>
supported_target_versions=<recorded>
supported_target_arches=<recorded>
unsupported_targets_declared=1
requires_operator_consent=1
preflight_guard_required=1
install_plan_preview_required=1
uninstall_path_required=1
rollback_or_recovery_path_required=1
network_required=0
service_activation_default=0
boot_change_default=0
kernel_module_default=0
selinux_policy_default=0
payload_listing_recorded=1
payload_contains_cli_binary=<0-or-1>
payload_contains_readme=<0-or-1>
payload_contains_service=<0-or-1>
payload_contains_kernel_module=<0-or-1>
payload_contains_boot_change=<0-or-1>
payload_contains_selinux_policy=<0-or-1>
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Required payload declaration

Every manifest must declare the artifact payload explicitly.

For the current no-effect CLI RPM payload, the known validated payload baseline is:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

A future installer artifact may not add runtime surfaces silently.

Any added service, kernel, boot, SELinux, networking, or policy surface must be separately declared, reviewed, and validated before readiness language changes.

## Required checksum and signature boundary

At this stage, signature fields may be `none` only for local experimental artifacts.

A production installer readiness claim requires:

```text
artifact_sha256_recorded=1
artifact_signature_recorded=1
artifact_signing_key_documented=1
signature_verification_documented=1
```

Until those are present and validated, the project must preserve:

```text
production_installer_ready=0
```

## Required SBOM boundary

A production installer readiness claim requires an SBOM path in the manifest:

```text
artifact_sbom_path=<recorded>
sbom_present=1
sbom_reviewed=1
```

Until SBOM evidence exists, the project must preserve:

```text
installer_sbom_recorded=0
production_installer_ready=0
```

## Required target boundary

A manifest must distinguish supported and unsupported targets.

At minimum, it must preserve:

```text
daily_driver_install_ready=0
immutable_fedora_ready=0
production_host_ready=0
```

until separate evidence validates those target classes.

## Required non-claims

Every manifest review must preserve:

```text
not_production_readiness=1
not_fedora_approval=1
not_fedora_distribution_readiness=1
not_daily_driver_readiness=1
not_immutable_fedora_readiness=1
not_security_hardening_claim=1
not_malware_prevention_claim=1
not_ransomware_prevention_claim=1
not_os_replacement_claim=1
```

## Current status

```text
installer_artifact_manifest_contract_present=1
installer_artifact_manifest_present=0
installer_artifact_manifest_validated=0
installer_artifact_checksum_recorded=0
installer_artifact_signature_recorded=0
installer_sbom_recorded=0
installer_supported_targets_declared=0
installer_unsupported_targets_declared=0
production_installer_ready=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-local-installer-artifact-manifest-contract.sh
```

Expected output:

```text
local_installer_artifact_manifest_contract: ok
```

## Next implementation lane

```text
Add installer artifact manifest fixture
```

That lane should add a non-production fixture manifest for the current local no-effect CLI RPM artifact and keep all production readiness flags set to `0`.

## Non-claims

This contract is not an installer artifact, not a production installer, not a distribution package, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not update safety, not recovery safety, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
