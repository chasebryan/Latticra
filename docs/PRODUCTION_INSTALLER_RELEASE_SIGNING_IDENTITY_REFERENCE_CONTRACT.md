# Production Installer Release Signing Identity Reference Contract

Status: no-effect release signing identity reference contract
Evidence level: 10 target, reference validation only
Scope: validate the shape of a future release signing identity reference without listing secret keys, reading key material, signing artifacts, creating signatures, verifying signatures, publishing artifacts, accepting evidence, or mutating a host.

## Purpose

The release-artifact candidate preflight requires an explicit signing identity reference before a future production-installer release artifact candidate can pass.

This contract defines the safe reference shape for that lane: a 40-hex OpenPGP-style fingerprint or a 64-hex long-form fingerprint, with optional public label and future public-key path metadata.

It does not prove that a secret key exists, that the operator controls the key, that an artifact has been signed, or that any signature has been verified.

## Command

```sh
sh scripts/production-installer-release-signing-identity-reference.sh \
  --fingerprint none \
  --identity-label none \
  --public-key-path none
```

## Current classification

```text
release_signing_identity_reference_validator_present=1
release_signing_identity_reference_mode=no-secret-inspection-reference-validation
release_signing_identity_reference_no_effect=1
release_signing_identity_reference_valid=0
release_signing_identity_reference_present=0
release_signing_identity_reference_fingerprint_format_valid=0
release_signing_identity_reference_label_present=0
release_signing_identity_reference_public_key_path_recorded=0
release_artifact_signing_identity_reference_present=0
release_artifact_signing_identity_reference_format_valid=0
secret_key_inspection_performed=0
secret_key_material_read=0
secret_key_material_written=0
signing_performed=0
signature_created=0
signature_verified=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
host_mutation_performed=0
```

## Reference requirements

A future signing identity reference may be treated as syntactically present only when:

```text
release_signing_identity_reference_fingerprint_format_valid=1
release_signing_identity_reference_present=1
release_artifact_signing_identity_reference_format_valid=1
release_artifact_signing_identity_reference_present=1
```

Accepted fingerprint shapes:

```text
40 uppercase or lowercase hexadecimal characters
64 uppercase or lowercase hexadecimal characters
```

Whitespace may be removed before validation.

## Required source records

This validator binds the current blocked production-installer posture:

```text
production_installer_ready=0
release_artifact_signing_identity_reference_present=0
release_artifact_promotion_gate_passed=0
release_artifact_candidate_preflight_present=1
release_artifact_staging_directory_present=1
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-release-signing-identity-reference-contract.sh
```

Expected output:

```text
production_installer_release_signing_identity_reference_contract: ok
```

## Next implementation lane

```text
Run the release-artifact candidate preflight with a reviewed release signing identity fingerprint reference after the tracked worktree and RPM build/query tooling blockers are resolved.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This contract is not a signing key, not secret-key custody, not key ownership proof, not a public-key publication record, not artifact signing, not signature verification, not release artifact evidence, not artifact promotion, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not host mutation, and not production installer readiness.
