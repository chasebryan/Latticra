# Latticra Nucleus Preview Classification

Status: initial implementation contract
Scope: request classification, effect policy, no-execution flags, operator-visible reports, and preview-only boundaries.

## Purpose

Nucleus Preview Classification is the third Latticra implementation unit.

It introduces the first Nucleus-adjacent classifier and operator-visible report surface without task execution, mutation, server interaction, recovery execution, hardware access, or update behavior.

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

The classifier and report surface must always preserve:

```text
executed=0
mutation_allowed=0
server_interaction_allowed=0
recovery_allowed=0
hardware_allowed=0
```

This preserves the preview-only boundary.

## Operator-visible report

The preview report renders classifier output as deterministic text.

Required report fields:

```text
LATTICRA NUCLEUS PREVIEW
request=<request-kind>
requested_effect=<effect>
policy=<policy-result>
reason=<policy-reason>
executed=0
mutation_allowed=0
server_interaction_allowed=0
recovery_allowed=0
hardware_allowed=0
```

The report must handle both allowed previews and denied previews without changing policy state or performing work.

## Public API

Initial API:

```text
latticra_request_kind_label
latticra_policy_result_label
latticra_policy_reason_label
latticra_nucleus_classify_preview
latticra_nucleus_preview_report
```

## Test command

Run:

```sh
sh scripts/test-nucleus-preview.sh
```

The main C workflow runs state-lattice, tri-plane transition, and Nucleus preview tests.

## Current evidence level

This implementation is an L2 tested model for request/effect classification and operator-visible preview reporting.

It is not live Nucleus orchestration, task execution, server interaction, self-update, recovery behavior, hardware behavior, boot behavior, or a security boundary.

## Next implementation step

The next implementation candidate after this model is:

```text
L-UI static report fixture
```

That future work should define terminal-facing layout fixtures for these reports while still avoiding live mutation.

## Non-claims

This document and implementation do not claim live Nucleus execution, live movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
