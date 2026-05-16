# Latticra Server Interaction Model

Status: initial server interaction model
Scope: optional server connectivity, signed artifacts, evidence sync, package/update interactions, and boundaries.

## Purpose

Latticra should design server interaction from the beginning.

Server connectivity must be explicit, signed where relevant, inspectable, and optional unless a deployment profile requires it.

## Core rule

Latticra must remain locally operable by default.

Server interaction is a gated capability, not a hidden dependency.

## Server roles

| Server role | Purpose | Initial status |
| --- | --- | --- |
| Update server | Signed update manifests and version metadata. | Planned. |
| Evidence server | Validation reports, evidence bundles, hardware profile records. | Planned. |
| Package server | Lat, L-UI, and supervisor module packages. | Planned. |
| Support server | Diagnostic report submission and support guidance. | Planned. |
| Trust metadata server | Keys, revocation metadata, trust roots, and policy bundles. | Planned. |

## Network effect boundary

Any server interaction is at least:

```text
effect = network
```

If server interaction writes local artifacts, it is also:

```text
effect = local_mutation
```

If it changes boot, recovery, hardware, or supervisor behavior, additional gates are required.

## Required server request record

Every server request should eventually record:

```text
request_id
server_role
endpoint_identity
method
network_effect
local_write_effect
signature_required
signature_result
operator_confirmation
result
failure_reason
```

## Trust requirements

Server-provided artifacts must not be accepted as trusted merely because they downloaded successfully.

Future artifact acceptance should require:

- manifest identity;
- signature verification;
- hash verification;
- channel policy;
- version policy;
- rollback compatibility;
- evidence record.

## Local-first operation

The following must work without server access:

- local state reports;
- no-effect fixtures;
- local validation;
- local evidence review;
- local non-claims review;
- local architecture documentation.

## Server gateway

Nucleus should eventually route all server interaction through a Server Gateway.

No component should bypass the Server Gateway for network behavior.

## Failure behavior

Server failure must be visible and non-destructive by default.

Failure states:

```text
unavailable
signature_failed
hash_mismatch
policy_denied
channel_denied
rollback_incompatible
operator_denied
unknown_failure
```

## Initial implementation target

No server interaction should be implemented first.

The first server-related implementation should be a static server interaction contract fixture and validation test.

## Non-claims

This document does not implement networking, package downloads, update servers, support servers, or trust servers.

It defines the server interaction model before implementation begins.