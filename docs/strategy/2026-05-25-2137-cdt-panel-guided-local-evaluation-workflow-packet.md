# Latticra Panel-Guided Local Evaluation Workflow Packet

Status: draft workflow packet
Created: 2026-05-25 21:37 CDT
Decision: selected as first public-readiness workflow planning path
Promotion decision: no product-readiness promotion recommended
Scope: bounded Panel-guided local evaluation workflow for technical evaluators.

## Purpose

This packet selects the first public-readiness workflow planning path:

```text
Panel-guided local evaluation
```

It narrows the public product-readiness promotion packet into one candidate user journey. It does not authorize implementation expansion, public product-readiness promotion, runtime authority, or estimate changes.

## Source packet

This workflow packet follows:

```text
docs/strategy/2026-05-25-2114-cdt-public-product-readiness-promotion-packet.md
```

Current strategy remains:

```text
Continue small guarded report/status alignment only when drift appears.
```

## Target evaluator

Primary evaluator:

```text
technical evaluator
```

Secondary evaluators:

```text
security researcher
systems engineer
infrastructure maintainer
```

This workflow is not for nontechnical end users, production operators, daily-driver use, or security reliance.

## Workflow statement

Named workflow:

```text
Evaluate Latticra locally through Latticra Panel without granting runtime authority.
```

Workflow purpose:

```text
let a technical evaluator inspect Latticra's current local workbench, dry-run posture,
visible authority boundaries, plan/evidence surfaces, and reset boundaries without
claiming production readiness
```

## Current evidence

Existing README-supported Panel flow:

```text
open Guided Workbench
keep dry-run mode enabled
generate and inspect the plan
run Dry-Install to validate and write a receipt
review the embedded console, plan, and engine log
enable guarded local-prefix writes only after dry-run evidence looks correct
```

Existing command surface:

```text
make -C installer gui
make -C installer dry-run
make -C installer verify-local
make -C installer reset-dry-run
make -C installer reset-local
make -C installer uninstall-local
make -C installer uninstall-dry-run
```

Current estimate posture:

```text
Latticra Panel / local control surface: 28%
Public product readiness: 8%
```

## Workflow boundary

The first public-readiness workflow should remain:

```text
local
operator-visible
dry-run-first
no-root by default
no-network by default
reset-aware
receipt-aware
non-production
```

The workflow should not depend on runtime execution, effect execution, capability enforcement, cryptographic authority, model execution, tool execution, or network behavior.

## Proposed user journey

The future workflow record should describe exactly this path:

1. Read the current status and non-claims.
2. Confirm local prerequisites.
3. Launch Latticra Panel from source or documented local entry point.
4. Enter Guided Workbench.
5. Confirm dry-run mode is enabled.
6. Generate the local plan.
7. Inspect the plan before any local write.
8. Run the dry-run validation path.
9. Inspect the receipt, embedded console, plan, and engine log.
10. Confirm denied authority and non-claims remain visible.
11. Run reset or uninstall dry-run path when appropriate.
12. Exit with a clear statement of what happened and what did not happen.

## Required acceptance evidence

Before this workflow can support any product-readiness estimate change, require:

```text
workflow acceptance checklist
platform prerequisite checklist
dry-run transcript
plan output example
receipt or receipt-like evidence example
engine log example
embedded console status example
reset or uninstall transcript
failure-state examples
known limitations note
support boundary note
non-claim review
guard or test that covers the documented path
estimate-impact review
public-entrypoint review
```

## Required operator-visible labels

The workflow should expose:

```text
dry_run_enabled
runtime_authority_granted=0
effect_execution_performed=0
network_authority_granted=0
root_authority_required=0
local_write_planned=0|1
local_write_performed=0|1
receipt_available=0|1
reset_available=0|1
manual_review_required=1
production_ready=0
```

If local writes are part of a future guarded path, the workflow must distinguish:

```text
dry-run artifacts
user-local artifacts
runtime effects
host effects
external effects
```

## Failure model

Minimum failure states:

```text
missing_rust_toolchain
missing_gui_dependency
unsupported_platform
panel_launch_failed
plan_generation_failed
dry_run_failed
receipt_missing
log_missing
reset_failed
operator_cancelled
manual_review_blocked
```

Every failure state should preserve:

```text
no runtime authority
no network authority
no hidden mutation
visible remediation or manual-review note
```

## Out-of-scope behavior

This workflow packet does not permit:

```text
production installer claim
signed release claim
notarized app claim
Fedora approval claim
Ubuntu package readiness claim
macOS app readiness claim
daily-driver claim
root install claim
runtime authority
effect execution
capability enforcement
cryptographic authority
signing authority
network behavior
model execution
tool execution
shell execution outside documented local commands
security protection claim
malware-prevention claim
ransomware-prevention claim
operating-system replacement claim
```

## Estimate-impact answer

```text
Does this packet move public product readiness to a new promotion class? no
Does it add a completed user-facing workflow? no
Does it add runtime behavior? no
Does it add effect execution? no
Does it add authority? no
Does it add security-hardening evidence? no
Estimate change recommended: no
Reason: this packet selects and scopes the first workflow path only.
```

## Public-entrypoint answer

```text
Does this packet change public capability wording? no
Does it require README update? no
Does it require STATUS.md update? no
Does it require docs/status/CURRENT_STATUS.md update? no
Does it require docs/project_notes/CURRENT_DIRECTION.md update? no
Does it require docs/project_notes/UPCOMING_WORK.md update? no
Does it require announcement review? no
Public entrypoint change recommended: no
Reason: no capability posture changes.
```

## Next planning action

The next planning action is:

```text
draft the Panel-guided local evaluation acceptance checklist
```

That checklist should remain a planning artifact until it is tied to a real guard, transcript, or workflow evidence record.

## Non-claims

This packet does not implement product readiness, Panel readiness, installer readiness, runtime behavior, effect execution, capability enforcement, cryptographic authority, signing authority, host behavior, network behavior, model execution, tool execution, shell execution, security hardening, malware prevention, ransomware prevention, sandboxing, operating-system behavior, or production support.

It records workflow planning criteria only.
