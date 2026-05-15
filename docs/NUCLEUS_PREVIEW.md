# Latticra Nucleus Preview Classification

Status: initial implementation contract
Scope: request classification, effect policy, no-execution flags, and preview-only boundaries.

## Purpose

Nucleus Preview Classification is the third Latticra implementation unit.

It introduces the first Nucleus-adjacent classifier without task execution, mutation, server interaction, recovery execution, hardware access, or update behavior.

## Implementation files

```text
include/latticra/nucleus_preview.h
src/nucleus_preview.c
tests/nucleus_preview_invariants.c
scripts/test-nucleus-preview.sh
```

## Request kinds

Initial request kinds:

```text
state-report
transition-preview
server-interaction
self-update
recovery-action
hardware-action
unknown
```

## Policy results

Initial policy results:

```text
allow-preview
deny
```

Initial policy reasons:

```text
ok
null-argument
unknown-request
effect-blocked
effect-requires-future-gate
```

## Allowed preview requests

Only these are allowed in the initial implementation:

```text
state-report with effect=none
state-report with effect=read
transition-preview with effect=none
transition-preview with effect=read
```

## Future-gated requests

These request kinds are classified but denied:

```text
server-interaction
self-update
recovery-action
hardware-action
```

They require future contracts, gates, evidence, and tests before any stronger behavior.

## Blocked effects

The initial classifier denies:

```text
local_mutation
host_mutation
network
hardware
boot
recovery
external
```

for preview-allowed request kinds.

## No-execution boundary

The classifier must always return:

```text
executed=0
mutation_allowed=0
server_interaction_allowed=0
recovery_allowed=0
hardware_allowed=0
```

This preserves the preview-only boundary.

## Public API

Initial API:

```text
latticra_request_kind_label
latticra_policy_result_label
latticra_policy_reason_label
latticra_nucleus_classify_preview
```

## Test command

Run:

```sh
sh scripts/test-nucleus-preview.sh
```

The main C workflow runs state-lattice, tri-plane transition, and Nucleus preview tests.

## Current evidence level

This implementation is an L2 tested model for request/effect classification.

It is not live Nucleus orchestration, task execution, server interaction, self-update, recovery behavior, hardware behavior, boot behavior, or a security boundary.

## Next implementation step

The next implementation candidate after this model is:

```text
operator-visible Nucleus preview report
```

That future work should render classifier results but still avoid live mutation.

## Non-claims

This document and implementation do not claim live Nucleus execution, live movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
