# Latticra Self-Update Model

Status: Panel-owned local-checkout updater policy active; signed updater delivery gate closed
Scope: signed staged updates, channels, rollback, operator confirmation, and non-claims.

## Purpose

Latticra should be designed for safe self-update capability from the beginning, but self-update must never be silent or magical.

Self-update is a real-system capability and therefore requires contracts, effect gates, verification, rollback, and operator visibility.

## Core rule

No silent self-updates.

Every update path must be inspectable, signed, staged, and reversible where possible.

## Current Panel-Owned Updater Surface

Panel-owned local-checkout updater policy is active.

The current implemented updater surface is the Latticra Panel updater. It is limited to a reviewed local checkout and a guarded local-prefix reinstall flow:

```text
updater_current_source_strategy=current-source-checkout
updater_current_apply_mode=guarded-local-prefix-reinstall
network_self_update_ready=0
remote_update_repository_trust=0
signed_update_delivery_ready=0
```

The signed delivery gate is still closed:

```text
signed_updater_delivery_gate_state=closed
signed_update_delivery_ready=0
network_self_update_ready=0
remote_update_repository_trust=0
signed_manifest_required=1
signed_manifest_present=0
manifest_signature_verified=0
artifact_hash_verified=0
artifact_signature_verified=0
rollback_plan_required=1
rollback_plan_present=0
operator_confirmation_required=1
operator_confirmation_observed=0
signed_update_apply_allowed=0
signed_updater_denial_transcript_present=1
signed_updater_denial_decision=deny-signed-update-delivery
signed_updater_denial_transcript_stdout_only=1
signed_updater_denial_transcript_file_write_enabled=0
signed_updater_manifest_fixture_contract_present=1
signed_updater_manifest_fixture_present=1
signed_updater_manifest_fixture_validation_present=1
signed_updater_manifest_fixture_validated=1
signed_updater_state_fixture_contract_present=1
signed_updater_state_fixture_present=1
signed_updater_state_fixture_validation_present=1
signed_updater_state_fixture_validated=1
signed_updater_state_fixture_valid_for_transition=0
signed_updater_state_fixture_valid_for_apply=0
signed_updater_state_transition_denial_transcript_present=1
signed_updater_state_transition_denial_decision=deny-state-transition
signed_updater_state_transition_denial_transcript_stdout_only=1
signed_updater_state_transition_denial_transcript_file_write_enabled=0
signed_updater_state_transition_denial_review_present=1
signed_updater_state_transition_denial_review_decision=uphold-deny-state-transition
signed_updater_state_transition_denial_review_stdout_only=1
signed_updater_state_transition_denial_review_file_write_enabled=0
signed_updater_state_transition_denial_disposition_present=1
signed_updater_state_transition_denial_disposition_decision=retain-blocked-state
signed_updater_state_transition_denial_disposition_stdout_only=1
signed_updater_state_transition_denial_disposition_file_write_enabled=0
signed_updater_state_transition_denial_disposition_review_present=1
signed_updater_state_transition_denial_disposition_review_decision=uphold-retain-blocked-state
signed_updater_state_transition_denial_disposition_review_stdout_only=1
signed_updater_state_transition_denial_disposition_review_file_write_enabled=0
current_update_state=blocked
state_transition_execution_allowed=0
state_transition_execution_performed=0
manifest_fixture_trusted_for_apply=0
signed_updater_manifest_fixture_valid_for_apply=0
trusted_signed_manifest_present=0
```

The local signed updater manifest fixture validation only checks shape and closed-authority fields. The local signed updater state fixture validation only checks the state catalog and closed transition fields without making the blocked fixture executable. The local signed updater state transition denial transcript records the blocked decision to stdout only, without transcript file writes or execution. The local signed updater state transition denial review upholds the denial without review file writes or execution. The local signed updater state transition denial disposition retains the blocked state without disposition file writes or execution. The local signed updater state transition denial disposition review upholds that retained blocked state without review file writes or execution. This is not a signed updater, not a remote update client, not a network self-update path, not update state execution, and not production update readiness.

## Update channels

Initial planned channels:

```text
stable
candidate
edge
lab
```

Channel meanings:

| Channel | Meaning |
| --- | --- |
| `stable` | Promoted, evidence-backed release path. |
| `candidate` | Release candidate path after validation. |
| `edge` | Active development path with explicit risk. |
| `lab` | Local or experimental path, never default. |

## Update states

```text
available
downloaded
verified
staged
armed
applied
rolled_back
failed
blocked
```

Only `applied` may imply the update changed the running or installed system.

## Required update record

Every update should eventually produce:

```text
update_id
current_version
target_version
channel
manifest_hash
artifact_hash
signature_result
compatibility_result
rollback_available
operator_confirmation
state
failure_reason
post_update_validation
```

## Effect classes

Self-update may involve multiple effect classes:

```text
network
local_mutation
host_mutation
boot
recovery
external
```

The early update model must support only documentation and fixture-level planning.

## Signed manifest rule

An update must be described by a signed manifest before any artifact is trusted.

Manifest should include:

- version;
- channel;
- artifact hash;
- compatibility constraints;
- architecture target;
- rollback compatibility;
- required gates;
- post-update validation commands.

## Staging rule

Update artifacts should be staged before activation.

Staging does not imply activation.

```text
downloaded != verified
verified != staged
staged != armed
armed != applied
```

## Rollback rule

Update design must include rollback state before real update execution exists.

Rollback states:

```text
unavailable
available
armed
executed
failed
blocked
```

## Operator confirmation

A future update that changes local system state must require explicit operator confirmation.

A future update that changes boot or recovery state must require a stronger confirmation profile.

## Server relationship

Update server interaction must pass through the Server Gateway.

No component should perform direct update network behavior outside the signed update model.

## First implementation target

The current Panel implementation target is a local-checkout updater policy surface, not signed or networked self-update.

It installs and reports:

```text
etc/latticra/updater.toml
share/latticra/updater/policy.toml
latticra updater status
updater dry-run
updater apply
```

The Panel updater reuses the guarded installer engine for a local-prefix reinstall from the current reviewed checkout. It has no network fetch, root, system mutation, boot, or recovery authority. `latticra updater status` reports the configured source strategy, channel, preview/apply commands, receipt setting, guarded apply mode, and disabled authority posture without launching the GUI.

The signed staged update model still needs:

```text
update manifest fixture
update state fixture
no-effect signed updater denial transcript
local signed updater manifest fixture contract
local signed updater manifest fixture validation
local signed updater state fixture contract
local signed updater state fixture validation
local signed updater state transition denial transcript
local signed updater state transition denial review
local signed updater state transition denial disposition
local signed updater state transition denial disposition review
signature-required marker
rollback visibility marker
validation test
```

## Non-claims

This document does not implement signed or networked self-update.

The Panel updater does not claim secure update delivery, rollback success, boot update safety, recovery behavior, network fetch authority, root authority, system mutation authority, or production release readiness.
