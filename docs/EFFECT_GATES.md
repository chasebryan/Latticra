# Latticra Effect Gates

Status: initial effect-gate model
Scope: effect classes, gate rules, request classification, and non-claims.

## Purpose

Latticra must classify effects before it handles any request.

A system that can update itself, interact with servers, handle hardware targets, or eventually perform recovery work must never hide effects behind friendly names.

## Effect classes

| Effect class | Meaning | Initial status |
| --- | --- | --- |
| `none` | No mutation, no host action, no external action. | Allowed for fixtures and reports. |
| `read` | Read-only inspection of local approved state. | Allowed after source contract. |
| `local_mutation` | Changes Latticra-owned local state. | Planned, gated. |
| `host_mutation` | Changes host files, processes, services, or settings. | Blocked until explicit gates. |
| `network` | Sends or receives network data. | Blocked until server model and trust policy. |
| `hardware` | Touches hardware state or device interfaces. | Blocked until hardware profile and evidence. |
| `boot` | Affects boot path, boot artifacts, or boot configuration. | Blocked until boot contract and evidence. |
| `recovery` | Performs recovery behavior or rollback beyond local preview. | Blocked until recovery contract and evidence. |
| `external` | Affects systems outside the local Latticra boundary. | Blocked until explicit deployment policy. |

## Classification rule

Every request must be classified before handling.

If classification fails, the request is denied.

```text
unknown effect -> deny
ambiguous effect -> deny
unclassified effect -> deny
```

## Gate states

Each gate may be in one of these states:

```text
disabled
planned
available
armed
executed
failed
blocked
```

Only `executed` may imply a real action happened.

## Request record

Every request should eventually produce a record shaped like:

```text
request_id:
source:
requested_effect:
allowed_effect:
gate:
policy_result:
reason:
operator_confirmation:
result:
rollback_state:
evidence_level:
```

## Default policy

Default policy is conservative:

```text
none -> allowed
read -> allowed only for approved local state
local_mutation -> planned, explicit gate required
host_mutation -> blocked
network -> blocked
hardware -> blocked
boot -> blocked
recovery -> blocked
external -> blocked
```

## Operator visibility

Effect state must always be visible to the operator.

Reports should show:

```text
host_effect
external_effect
network_effect
hardware_effect
boot_effect
recovery_effect
```

## Relationship to Nucleus

Nucleus must consult the Effect Gate before any task is carried out.

The Effect Gate does not decide all policy. It decides whether the effect class is known, allowed, gated, blocked, or failed.

## Relationship to Lat

Lat documents must declare intended effects.

If a Lat document omits an effect declaration, the default is:

```text
effect = none
```

If the document attempts to exceed its declared effect, it must be rejected.

## Relationship to L-UI

L-UI should be effect-free by default.

A UI surface may request reports or display state, but it must not perform hidden mutation.

## Server and update effects

Server interaction is `network` plus optional `local_mutation` when writing downloaded artifacts or evidence records.

Self-update is at least:

```text
network
local_mutation
update_stage
```

and may eventually involve boot or recovery effects depending on deployment profile.

## First implementation target

The first implementation target should support only:

```text
effect = none
```

and possibly read-only report classification.

## Non-claims

This document does not implement effect gates.

It defines the gate vocabulary and default-deny policy before implementation begins.