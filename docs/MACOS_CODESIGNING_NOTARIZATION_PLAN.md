# macOS Codesigning and Notarization Plan

Status: no-effect macOS codesigning and notarization plan
Date: 2026-05-29 CDT
Scope: planning-only contract for the future macOS signing and notarization review lane after user-local app bundle evidence exists.

## Purpose

This document defines the bounded planning lane for future macOS codesigning and notarization work.

It is plan-only. It does not create an app bundle, invoke `codesign`, submit notarization, staple a ticket, mutate host state, read secret key material, request Apple account access, or claim a signed or notarized macOS app.

The lane exists so the current macOS transferability path can record exact prerequisites and non-claims before any future signing authority is considered.

## Command

```sh
sh scripts/macos-codesigning-notarization-plan.sh
```

The command writes only a deterministic plan report to stdout.

## Current Decision

The current planning posture is:

```text
macos_codesigning_notarization_plan_present=1
macos_codesigning_notarization_plan_state=defined-no-effect
macos_codesigning_notarization_plan_decision=plan-defined-evidence-not-present
macos_codesigned_app_evidence_present=0
macos_notarized_app_evidence_present=0
macos_verification_transcript_evidence_present=0
commit_user_local_managed_artifacts=0
```

## Required Inputs Before Any Future Signing Run

Any future signing/notarization execution must remain blocked until all of the following are present:

```text
managed_app_bundle_present_required=1
macos_install_verified_required=1
verification_transcript_evidence_present_required=1
receipt_manifest_present_required=1
candidate_asset_probe_present_required=1
commit_gate_state_closed_until_evidence_required=1
release_signing_identity_reference_contract_present_required=1
release_signing_identity_reference_status_present_required=1
release_artifact_candidate_preflight_contract_present_required=1
operator_signing_intent_review_required=1
operator_notarization_intent_review_required=1
reviewed_apple_account_boundary_required=1
reviewed_network_boundary_required=1
reviewed_staple_boundary_required=1
```

## Planned Review Topics

The plan requires future review of:

```text
developer_id_application_identity_reference=planned
codesign_entitlements_scope=planned
info_plist_identifier_reuse=planned
hardened_runtime_boundary=planned
timestamp_service_dependency=planned
notarytool_submission_materials=planned
notarytool_keychain_profile_or_api_key_boundary=planned
ticket_stapling_boundary=planned
offline_verification_fallback_boundary=planned
receipt_and_transcript_redaction_boundary=planned
```

## Planned Evidence Shape

Before any future status may say `macos_codesigned_app_evidence_present=1` or `macos_notarized_app_evidence_present=1`, evidence must show all of:

```text
app_bundle_path_recorded_required=1
bundle_identifier_recorded_required=1
bundle_executable_recorded_required=1
signing_identity_reference_recorded_required=1
entitlements_path_recorded_required=1
codesign_command_transcript_required=1
codesign_verification_transcript_required=1
notary_submission_identifier_recorded_required=1
notary_status_recorded_required=1
staple_transcript_required=1
spctl_assessment_transcript_required=1
authority_denial_fields_required=1
review_signoff_required=1
```

## Authority Boundary

This plan preserves:

```text
codesign_invocation_performed=0
notary_submission_performed=0
ticket_staple_performed=0
keychain_profile_read_performed=0
secret_key_material_read_performed=0
apple_account_auth_performed=0
network_performed=0
host_mutation_performed=0
root_authority=0
keychain_authority=0
tcc_bypass_authority=0
runtime_authority_granted=0
production_installer_ready=0
```

## Validation

This plan is guarded by:

```sh
sh scripts/test-macos-codesigning-notarization-plan.sh
```

Expected output:

```text
macos_codesigning_notarization_plan: ok
```

## Non-Claims

This planning surface is not app-bundle evidence, signed-app evidence, notarization evidence, staple evidence, Apple account approval, App Store readiness, launchd integration, Keychain integration, Secure Enclave integration, Endpoint Security integration, privileged-helper approval, or production readiness.
