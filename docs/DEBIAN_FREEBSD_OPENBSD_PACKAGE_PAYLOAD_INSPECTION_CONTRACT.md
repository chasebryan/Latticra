# Debian, FreeBSD, and OpenBSD Package Payload Inspection Contract

Status: active package payload inspection contract
Scope: define future Debian, FreeBSD, and OpenBSD package payload inspection evidence without creating or inspecting package artifacts.

## Purpose

This contract records the package payload inspection evidence required before any future Debian, FreeBSD, or OpenBSD package artifact can be accepted as validation evidence.

The goal is narrow: a future package artifact must prove that it contains only the intended no-effect CLI payload and documentation payload, with no services, privileged helpers, init files, kernel files, network authority, or host mutation hooks.

This contract is documentation-only and static. It does not run package build tools, create package artifacts, inspect package artifacts, install Latticra, write FreeBSD or OpenBSD `distinfo` files, publish packages, or claim package readiness.

## Current Payload Inspection State

```text
debian_freebsd_openbsd_package_payload_inspection_contract_present=1
payload_inspection_contract_present=1
payload_inspection_contract_state=specified-no-effect
package_build_gate_state=closed-no-effect
artifact_naming_contract_state=specified-no-effect
package_artifact_created=0
package_payload_inspection_run=0
debian_payload_inspection_run=0
freebsd_payload_inspection_run=0
openbsd_payload_inspection_run=0
package_payload_accepted=0
package_artifact_sha256_recorded=0
install_on_host_run=0
package_readiness_claimed=0
```

## Expected Payload

All future Debian, FreeBSD, and OpenBSD package artifacts must preserve the current intentionally narrow payload:

```text
payload_cli_path_required=1
payload_doc_readme_required=1
payload_service_files_allowed=0
payload_init_files_allowed=0
payload_kernel_files_allowed=0
payload_privileged_helper_allowed=0
payload_network_authority_allowed=0
payload_host_mutation_hooks_allowed=0
```

The no-effect CLI payload must remain the only executable payload.

## Debian Payload Inspection

Future Debian payload inspection must verify:

```text
debian_payload_expected_bin=usr/bin/latticra
debian_payload_expected_doc=usr/share/doc/latticra/README.md
debian_payload_listing_required=1
debian_control_metadata_inspection_required=1
debian_maintainer_script_absence_required=1
debian_systemd_unit_absence_required=1
debian_init_script_absence_required=1
debian_privileged_helper_absence_required=1
debian_payload_unexpected_file_count=0
debian_payload_inspection_run=0
dpkg_deb_contents_inspection_run=0
dpkg_deb_metadata_inspection_run=0
```

The future Debian inspection transcript must bind the payload listing to:

```text
debian_binary_package_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.deb
debian_package_artifact_sha256
debian_payload_listing_sha256
```

## FreeBSD Payload Inspection

Future FreeBSD payload inspection must verify:

```text
freebsd_payload_expected_bin=bin/latticra
freebsd_payload_expected_doc=%%DOCSDIR%%/README.md
freebsd_payload_listing_required=1
freebsd_manifest_inspection_required=1
freebsd_rc_script_absence_required=1
freebsd_periodic_script_absence_required=1
freebsd_privileged_helper_absence_required=1
freebsd_payload_unexpected_file_count=0
freebsd_payload_inspection_run=0
freebsd_pkg_info_inspection_run=0
freebsd_pkg_manifest_inspection_run=0
```

The future FreeBSD inspection transcript must bind the payload listing to:

```text
freebsd_package_name=latticra-0.0.0.pkg
freebsd_package_artifact_sha256
freebsd_payload_listing_sha256
```

## OpenBSD Payload Inspection

Future OpenBSD payload inspection must verify:

```text
openbsd_payload_expected_bin=bin/latticra
openbsd_payload_expected_doc=share/doc/latticra/README.md
openbsd_payload_listing_required=1
openbsd_pkg_info_inspection_required=1
openbsd_rc_script_absence_required=1
openbsd_privileged_helper_absence_required=1
openbsd_payload_unexpected_file_count=0
openbsd_payload_inspection_run=0
openbsd_pkg_info_list_run=0
openbsd_package_tar_listing_run=0
```

The future OpenBSD inspection transcript must bind the payload listing to:

```text
openbsd_package_name=latticra-0.0.0.tgz
openbsd_package_artifact_sha256
openbsd_payload_listing_sha256
```

## Inspection Transcript Requirements

A future payload inspection transcript must record:

```text
package_artifact_name
package_artifact_sha256
package_artifact_size_bytes
payload_listing_command
payload_listing_sha256
expected_payload_paths_present
unexpected_payload_paths_absent
service_files_absent
privileged_helpers_absent
host_mutation_hooks_absent
environment_identifier
operator_authorization_reference
```

The transcript must be reviewed before a package artifact can be accepted as payload-correct.

## Current Blockers

Package payload acceptance remains blocked because the current repository still has:

```text
package_artifact_created=0
package_artifact_sha256_recorded=0
environment_transcript_present=0
explicit_operator_build_authorization=0
install_remove_transcript_contract_present=0
publication_non_claim_review_present=0
```

## Command Boundary

This contract does not:

```text
run dpkg-deb --contents
run dpkg-deb --info
run FreeBSD pkg info
run FreeBSD pkg manifest inspection
run OpenBSD pkg_info
run package tar listing
create package artifacts
install Latticra on a host
publish package artifacts
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
```

The package-build gate remains closed. This payload inspection contract only defines the evidence future package artifacts must provide after they exist in a disposable validation environment.

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package install/remove transcript contract before any package install can be accepted.
```

That future lane should define disposable install/remove evidence while keeping host installs and package readiness blocked.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-payload-inspection-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_payload_inspection_contract: ok
```
