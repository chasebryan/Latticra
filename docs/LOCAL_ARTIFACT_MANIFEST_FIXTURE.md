# Local Artifact Manifest Fixture

Status: fixture record
Scope: repository fixture for the local Latticra artifact manifest lane.

## Purpose

This slice adds the first committed manifest fixture for the local no-effect CLI RPM artifact.

The fixture gives the existing manifest contract a concrete, reviewable sample without creating a generated artifact, publishing a package, or changing host behavior.

## Fixture path

```text
fixtures/artifact/local-artifact-manifest.txt
```

## Guard path

```text
scripts/test-local-artifact-manifest-fixture.sh
```

Expected output:

```text
local_artifact_manifest_fixture: ok
```

## Fixture boundary

The fixture records metadata for the current local no-effect CLI RPM payload:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

It keeps the readiness boundary explicit:

```text
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

The checksum, signature, and SBOM fields remain fixture placeholders or absent evidence fields:

```text
artifact_checksum_recorded=0
artifact_signature_recorded=0
artifact_sbom_recorded=0
```

## Relationship to the contract

This fixture follows:

```text
docs/LOCAL_INSTALLER_ARTIFACT_MANIFEST_CONTRACT.md
```

It satisfies the next implementation lane named by that contract:

```text
Add installer artifact manifest fixture
```

## Non-claims

This fixture is not a generated release artifact.

It is not a production package.

It is not Fedora approval or Fedora distribution readiness.

It is not daily-driver or immutable-Fedora readiness.

It does not change boot, service, kernel, SELinux, network, install, uninstall, upgrade, rollback, or host state.
