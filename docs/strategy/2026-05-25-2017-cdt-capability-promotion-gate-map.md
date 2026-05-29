# Latticra Capability Promotion Gate Map

Status: strategy gate map
Created: 2026-05-25 20:17 CDT
Scope: strategic promotion criteria for future capability-posture changes.

## Purpose

This record translates the evidence ladder, precursor promotion rule, real-system contract, and current strategy posture into concrete promotion gates for Latticra's major work lanes.

It is an organizing record only. It does not authorize implementation expansion or change any current estimate.

## Source rules

Promotion remains governed by:

```text
docs/EVIDENCE_LADDER.md
docs/PRECURSOR_PROMOTION_RULE.md
docs/REAL_SYSTEM_CONTRACT.md
docs/strategy/2026-05-25-1951-cdt-strategy-posture-refresh.md
```

The controlling principle is:

```text
No public capability posture change without evidence that matches the next claimed level.
```

## Promotion classes

Use these classes before changing public language, estimates, or next-priority posture.

```text
maintenance_alignment
  Status, README, index, announcement-review, or source-map cleanup.
  Does not change capability posture.

metadata_capability
  A bounded no-effect implementation, fixture, parser, report, diagnostic,
  classifier, validator, or metadata path exists and is guarded.

preview_capability
  A capability is wired into a runtime or workflow model but remains
  preview-only, denied-by-default, and non-mutating.

guarded_local_capability
  A narrow local operation is possible only through explicit opt-in gates,
  audit output, failure handling, and rollback or reset boundaries.

real_system_capability
  A repeated, supported, documented capability with tests, release boundary,
  operator-facing status, and safety review.
```

## Estimate-change rule

Estimate changes should be considered only when a lane moves from one promotion class to another.

Do not adjust estimates for:

```text
index updates
README wording alignment
status-only publication
announcement-review decisions
source-of-truth cleanup
historical strategy records
non-claim restatement
```

Do consider estimate review for:

```text
new guarded implementation evidence
new test-backed capability class
new user-facing workflow evidence
new runtime preview integration
new enforcement or authority evidence
new security-hardening evidence
new product-readiness evidence
```

## Gate A: Runtime Behavior Expansion

Current posture:

```text
report-only
disabled-by-default
denied-by-default
no runtime authority
```

Promotion target:

```text
preview_capability before guarded_local_capability
```

Required before promotion:

```text
runtime behavior expansion contract
runtime behavior implementation plan
specific request family and effect family
authority prerequisite matrix
denial and failure fixtures
operator-visible report fields
rollback or non-mutation boundary
focused guard
aggregate guard
non-claim review
estimate-impact review
```

Forbidden shortcut:

```text
No direct move from report-only metadata to local mutation.
```

## Gate B: Nucleus Effect Contract

Current posture:

```text
report-only task boundary
classification-only execution labels
no effect-performing task execution
```

Promotion target:

```text
preview_capability for a single named effect family
```

Required before promotion:

```text
named effect family
effect contract
task authority prerequisites
Runtime Boundary dependency statement
Seal dependency statement when trust evidence is involved
denied-case fixtures
failure-state report
operator-visible status
guard coverage
non-claim review
estimate-impact review
```

Forbidden shortcut:

```text
No generic task execution umbrella before a narrow effect family is reviewed.
```

## Gate C: Seal Cryptographic Authority

Current posture:

```text
trust-boundary planning
bounded key metadata
verification metadata and result surfaces
no capability authorization from cryptographic result alone
no signing authority
no runtime authority
```

Promotion target:

```text
metadata_capability or preview_capability before any authority-bearing gate
```

Required before promotion:

```text
cryptographic authority contract
provider and algorithm boundary
public-key parsing evidence
negative verification fixtures
verified receipt semantics
capability-gate separation proof
effect-decision separation proof
key-material non-claim review
signing non-claim review
guard coverage
estimate-impact review
```

Forbidden shortcut:

```text
No verified cryptographic result may imply capability enforcement, signing authority,
effect execution, runtime handoff, host behavior, network behavior, or production trust.
```

## Gate D: Panel User-Facing Workflow Readiness

Current posture:

```text
local control surface direction
guarded user-local posture
early product readiness
```

Promotion target:

```text
guarded_local_capability for a named local workflow
```

Required before promotion:

```text
named user workflow
no-root boundary
network boundary
dry-run transcript
local path plan
failure and reset path
operator-visible status
accessibility and usability review
guarded install or no-effect proof
non-claim review
estimate-impact review
```

Forbidden shortcut:

```text
No public product-readiness promotion from architecture documentation alone.
```

## Gate E: Nadia Offline Inference Readiness

Current posture:

```text
offline AI foundation planning
context and tokenizer contracts
no prompt evaluation
no model loading
no inference
no tool execution
```

Promotion target:

```text
preview_capability before guarded local inference
```

Required before promotion:

```text
offline inference readiness contract
local model identity boundary
tokenizer artifact evidence
prompt materialization evidence
context-window assembly evidence
runtime invocation non-claim review
tool authority non-claim review
protective safety boundary check
guard coverage
operator-visible report
estimate-impact review
```

Forbidden shortcut:

```text
No dialogue, inference, tool authority, or source mutation before the offline
runtime and safety gates are independently evidenced.
```

## Gate F: Security-Hardening Evidence

Current posture:

```text
security-conscious design
defensive threat model records
early security-hardening implementation
no production security boundary
```

Promotion target:

```text
metadata_capability for security evidence before any protection claim
```

Required before promotion:

```text
threat model mapping
abuse-case fixtures
negative tests
external-source checkpoint when relevant
manual review record
residual-risk statement
non-claim review
estimate-impact review
```

Forbidden shortcut:

```text
No malware-prevention, ransomware-prevention, sandbox, hardening, or security
boundary claim without tested enforcement evidence.
```

## Gate G: Public Product Readiness

Current posture:

```text
early product readiness
strong documentation posture
no deployed platform
no production product claim
```

Promotion target:

```text
guarded_local_capability with a coherent user-facing workflow
```

Required before promotion:

```text
named target user
named workflow
installation or no-install path
first-run success criteria
failure and uninstall/reset criteria
support boundary
known limitations
operator-facing evidence
release note or readiness note
non-claim review
estimate-impact review
```

Forbidden shortcut:

```text
No product-readiness promotion from internal implementation evidence unless a
target user can complete a bounded workflow and understand its limitations.
```

## Strategic next-use rule

When the project wants to move beyond maintenance alignment, choose exactly one gate and write a promotion packet before implementation work starts.

The packet should include:

```text
gate:
target promotion class:
current evidence level:
target evidence level:
named capability:
allowed behavior:
forbidden behavior:
required fixtures:
required tests or guards:
operator-visible report:
non-claims:
estimate-impact question:
public-entrypoint question:
```

## Non-claims

This record does not implement runtime behavior, effect execution, capability enforcement, cryptographic authority, signing authority, host behavior, network behavior, model execution, tool execution, shell execution, product readiness, security hardening, malware prevention, ransomware prevention, sandboxing, or operating-system behavior.

It records strategy and promotion criteria only.
