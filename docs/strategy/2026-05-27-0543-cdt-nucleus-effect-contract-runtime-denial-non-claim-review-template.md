# Latticra Nucleus Effect-Contract and Runtime-Denial Non-Claim Review Template

Status: draft non-claim review template
Created: 2026-05-27 05:43 CDT
Decision: review template only
Promotion decision: no Nucleus execution, runtime, task-execution, product-readiness, security, OS-base, recovery, hardware, boot, or mutation promotion recommended
Scope: non-claim review for future Nucleus effect-contract and runtime-denial workflow evidence.

## Purpose

This template defines the non-claim review required before any Nucleus effect-contract and runtime-denial workflow evidence can be used in public-entrypoint, estimate-impact, or product-readiness discussions.

It does not perform the review. It defines the review shape only.

## Source bundle

This template follows:

```text
docs/strategy/2026-05-27-0538-cdt-nucleus-effect-contract-runtime-denial-evidence-bundle-template.md
```

The source checklist remains:

```text
docs/strategy/2026-05-27-0209-cdt-nucleus-effect-contract-runtime-denial-acceptance-checklist.md
```

The target workflow remains:

```text
contract_only_nucleus_effect_request_runtime_denial_workflow
```

Rejected workflows remain:

```text
live_task_execution_prototype
runtime_effect_execution_capture
command_runner_evidence_capture
mutation_capability_probe
operator_confirmation_override_trial
```

## Review header

```text
review name:
created:
reviewer:
review status: not_started|blocked|partial|complete|rejected
workflow evidence bundle:
acceptance checklist:
evidence bundle template:
evaluated platform:
repository commit:
```

## Required review outcome

Use one outcome:

```text
claim_safe_for_current_scope
claim_safe_with_required_edits
claim_unsafe_blocked
insufficient_evidence
```

This template result:

```text
review_performed=0
claim_expansion_detected=0
product_readiness_promotion_recommended=0
estimate_change_recommended=0
public_entrypoint_change_recommended=0
reason=this file defines the future review shape only
```

## Required source checks

The reviewer must inspect:

```text
README.md
STATUS.md
docs/status/CURRENT_STATUS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/strategy/README.md
docs/strategy/2026-05-26-1702-cdt-overall-strategy-priority-map.md
docs/strategy/2026-05-26-2134-cdt-nucleus-effect-contract-runtime-denial-workflow-packet.md
docs/strategy/2026-05-27-0209-cdt-nucleus-effect-contract-runtime-denial-acceptance-checklist.md
docs/strategy/2026-05-27-0538-cdt-nucleus-effect-contract-runtime-denial-evidence-bundle-template.md
docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
docs/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT.md
docs/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT.md
docs/NUCLEUS_TASK_PLAN_IMPLEMENTATION.md
```

If any source is missing, mark the review `blocked` or `insufficient_evidence`.

## Claims that must remain false

The review must confirm the workflow does not claim:

```text
task_execution_claim=0
effect_execution_claim=0
runtime_entry_claim=0
command_execution_claim=0
lat_execution_claim=0
lir_execution_claim=0
file_io_claim=0
network_claim=0
state_mutation_claim=0
server_interaction_claim=0
self_update_claim=0
recovery_claim=0
hardware_claim=0
boot_claim=0
operator_confirmation_override_claim=0
runtime_authority_claim=0
capability_enforcement_claim=0
receipt_materialization_claim=0
signing_authority_claim=0
cryptographic_authority_claim=0
product_readiness_claim=0
production_support_claim=0
security_hardening_claim=0
security_boundary_claim=0
malware_prevention_claim=0
ransomware_prevention_claim=0
estimate_change_claim=0
public_entrypoint_change_claim=0
```

Any true value in this section blocks the review unless a separate contract, implementation plan, guard, evidence record, public-entrypoint review, estimate-impact review, and non-claim update exist.

## Nucleus effect-request wording check

Allowed wording:

```text
Nucleus effect-request contract
contract-only evaluator workflow
runtime-denial workflow
report-only task request metadata
effect request classification
task report
task plan
execution_status=not-executed
effect_status=report-only
runtime_status=not-entered
```

Blocked wording:

```text
task executed
effect executed
runtime entered
command executed
task runner
command runner
automation performed
action completed
mutation performed
```

If blocked wording appears, the review outcome must be `claim_safe_with_required_edits` or `claim_unsafe_blocked`.

## Runtime and authority wording check

Allowed wording:

```text
authority denied
no-effect policy preserved
runtime denied
runtime_status=not-entered
effect_authority_granted=0
task_execution_performed=0
runtime_entered=0
command_execution_allowed=0
file_io_allowed=0
network_allowed=0
state_mutation_allowed=0
operator_confirmation_overrides_policy=0
```

Blocked wording:

```text
runtime available
runtime active
runtime authority granted
effect authority granted
task execution available
command execution available
file access available
network access available
mutation authority available
operator can override policy
```

Any authority-bearing wording must be rejected unless it belongs to a separate contracted and evidenced lane.

## Request classification wording check

Allowed wording:

```text
allow-report
allow-preview
allow-validation
requires-future-gate
deny
unknown_request=deny
unknown_effect=deny
```

Blocked wording:

```text
allowed to execute
allowed to mutate
allowed to launch
allowed to access files
allowed to use network
allowed to recover
allowed to control hardware
allowed to boot
```

Classification language must describe review, report, preview, validation, denial, or future gates only.

## Task-plan wording check

Allowed wording:

```text
task plan metadata
sequencing metadata
classified request sequence
plan does not execute tasks
plan does not enter runtime
plan does not perform mutation
```

Blocked wording:

```text
plan executed
tasks performed from plan
plan launched commands
plan mutated state
plan entered runtime
plan read files
plan wrote files
plan used network
```

Task plans may be referenced only as sequencing and review metadata.

## Product-readiness wording check

Allowed wording:

```text
technical evaluator workflow
planning evidence
future evidence capture
non-claim review
no product-readiness promotion recommended
runtime-denial clarity
```

Blocked wording:

```text
ready for users
production ready
daily driver
operator-ready product
supported release
task execution ready
runtime ready
automation ready
```

If blocked wording appears, the review outcome must be `claim_safe_with_required_edits` or `claim_unsafe_blocked`.

## Security wording check

Allowed wording:

```text
security-conscious planning
defensive planning
non-claim review
no security boundary claimed
no security-hardening promotion recommended
denied-by-default posture
```

Blocked wording:

```text
prevents malware
prevents ransomware
secure sandbox
hardened runtime
security boundary
verified protection
runtime protection
host protection
production cryptographic trust
```

Any security-protection wording requires separate enforcement evidence before it can be considered.

## Recovery, hardware, and boot wording check

Allowed wording:

```text
recovery_action=requires-future-gate
hardware_action=requires-future-gate
boot_action=requires-future-gate
recovery_allowed=0
hardware_allowed=0
boot_allowed=0
```

Blocked wording:

```text
recovery behavior available
self-healing available
hardware control available
boot control available
OS-base execution available
machine control available
```

Recovery, hardware, and boot language must remain future-gated or denied.

## Evidence wording check

Allowed wording:

```text
template
planning packet
checklist
future evidence
missing evidence
partial evidence
evidence ready for review
```

Blocked wording:

```text
evidence complete
workflow accepted
task execution accepted
runtime accepted
product readiness improved
estimate increase justified
public posture changed
```

Blocked evidence wording may become allowed only after the evidence bundle is complete and separately reviewed.

## Required reviewer answers

```text
Does the workflow preserve no task execution? yes|no
Does the workflow preserve no effect execution? yes|no
Does the workflow preserve no runtime entry? yes|no
Does the workflow preserve no command execution? yes|no
Does the workflow preserve no Lat execution? yes|no
Does the workflow preserve no LIR execution? yes|no
Does the workflow preserve no file I/O? yes|no
Does the workflow preserve no network behavior? yes|no
Does the workflow preserve no state mutation? yes|no
Does the workflow preserve no server interaction? yes|no
Does the workflow preserve no self-update? yes|no
Does the workflow preserve no recovery behavior? yes|no
Does the workflow preserve no hardware control? yes|no
Does the workflow preserve no boot behavior? yes|no
Does the workflow preserve no operator override? yes|no
Does the workflow preserve no runtime authority? yes|no
Does the workflow preserve no security claim? yes|no
Does the workflow preserve no product-readiness promotion? yes|no
Does the workflow preserve no estimate change? yes|no
Does the workflow preserve no public-entrypoint change? yes|no
```

All answers must be `yes` for `claim_safe_for_current_scope`.

## Required edit log

If edits are required, record:

```text
source file:
claim text:
claim risk:
required replacement:
reviewer note:
```

## Review gate output

```text
non_claim_review_present=0|1
claim_expansion_detected=0|1
required_edits_present=0|1
blocking_claims_present=0|1
public_entrypoint_review_required=0|1
estimate_impact_review_required=0|1
review_outcome:
```

This template output:

```text
non_claim_review_present=0
claim_expansion_detected=0
required_edits_present=0
blocking_claims_present=0
public_entrypoint_review_required=0
estimate_impact_review_required=0
review_outcome=not_performed
```

## Recommended next planning move

Recommended next planning move:

```text
create the Nucleus effect-contract and runtime-denial public-entrypoint review template
```

Reason:

```text
the non-claim review shape is now defined; the next useful planning artifact is
the review form for deciding whether future evidence can be referenced from
public entry points without changing execution, runtime, security, product, or
estimate posture
```

## Non-claims

This template does not perform a non-claim review, validate workflow evidence, run tests, run commands, execute Nucleus tasks, enter runtime, execute Lat, execute LIR, read files, write files, scan a network, launch a host process, perform state mutation, perform server interaction, self-update, perform recovery behavior, control hardware, boot hardware, create a receipt, request a signature, sign a receipt, perform a review, update public entry points, change estimates, provide product readiness, provide Nucleus execution readiness, provide runtime authority, enforce capabilities, provide cryptographic authority, provide signing authority, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records a non-claim review form only.
