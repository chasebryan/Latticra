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
latticra_panel_updater_present=1
latticra_panel_updater_owned=1
updater_current_source_strategy=current-source-checkout
updater_current_update_channel=local-checkout
updater_current_apply_mode=guarded-local-prefix-reinstall
updater_network_fetch_enabled=0
network_fetch_authority=0
root_authority=0
system_mutation_authority=0
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
```

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

## Current Implementation Target

The current implementation target is not signed or network-delivered update execution.

It is:

```text
Panel updater local-checkout policy
non-launching updater status report
closed signed updater delivery gate
signature-required marker
rollback-required marker
validation guard
```

## Non-claims

This document does not implement self-update.

It does not claim signed update delivery, network self-update, safe update execution, secure update delivery, rollback success, boot update safety, or production release readiness.
