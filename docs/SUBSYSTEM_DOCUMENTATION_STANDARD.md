# Subsystem Documentation Standard

Status: active subsystem documentation standard
Last updated: 2026-05-27 CDT
Scope: subsystem landing pages, subsystem status records, subsystem source records, public HTML subsystem pages, package and installer lane summaries, and any reader route that presents subsystem progress.

## Purpose

This standard keeps subsystem documentation consistent across Latticra.

A subsystem landing page should let a reader answer five questions without reading the full repository:

1. what exists now;
2. what the subsystem explicitly does not claim;
3. which source records make the current wording true;
4. which validation or guard proves the narrow claim;
5. which public pages or status records mirror the posture.

Use this standard with [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md), [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This standard does not make a subsystem more complete. It only makes the documented posture easier to verify.

## Required Landing Page Shape

| Section | Required content | Failure signal |
| --- | --- | --- |
| Status block | Current status, last updated date, scope, and explicit posture words such as no-effect, report-only, guarded user-local, local-only, or metadata-only. | The page starts with aspirational feature copy before current posture. |
| Current capability | A short list of what exists today, scoped to evidence already present. | The page describes planned or desired behavior as if it already exists. |
| Non-claims | Adjacent blocked claims that readers are likely to infer. | Security, installer, package, runtime, AI, OS, or platform claims appear without nearby limits. |
| Evidence spine | Links to contract, implementation plan if applicable, implementation record, status record, guard script, and public mirror. | A claim has no source record or no status/validation route. |
| Safe local route | Runnable commands only when they are guarded, no-effect, dry-run, user-local, or otherwise bounded. | A command appears before effect boundaries or cleanup/reset expectations. |
| Validation | Exact guard names plus documentation hygiene checks for public-facing changes. | The page says "validated" without naming a guard or review path. |
| Reader stop signals | Conditions that tell a reader not to promote the claim. | Subsystem progress is allowed to imply product readiness. |
| Mirrors | Public HTML, README, status, package, installer, or subsystem maps that may need alignment. | Public pages can drift from the subsystem source record. |
| Maintenance triggers | Events that require updating the page. | Implementation, status, guard, estimate, platform, or claim changes do not update the landing page. |
| Boundary | A final statement that the page does not change implementation, authority, package approval, security posture, or product readiness. | The page sounds like an authority grant. |

## Minimum Template

Use this shape for a new or refreshed subsystem landing page:

```text
# <Subsystem Name>

Status:
Last updated:
Scope:

## Current Posture

What exists now:

What remains blocked:

## Evidence Spine

- Contract:
- Implementation plan:
- Implementation record:
- Status record:
- Guard or validation:
- Public mirror:

## Safe Local Route

Runnable path:
Effect boundary:
Cleanup or reset path:

## Non-Claims

This subsystem does not claim:

## Reader Stop Signals

Stop if:

## Maintenance Triggers

Update this page when:

## Boundary

This page is documentation posture only.
```

If a field does not apply, say `not applicable` and explain why. Do not omit it when omission could be read as hidden readiness.

## Evidence Spine Rule

A subsystem claim should follow this route:

```text
subsystem landing page -> contract -> implementation or report record -> status record -> guard or validation -> public mirror -> non-claim boundary
```

If the route breaks, narrow the public wording or mark the claim blocked in a review packet.

## Subsystem Posture Examples

| Subsystem type | Safe posture wording | Blocked adjacent wording |
| --- | --- | --- |
| Report surface | Report-only metadata surface with deterministic validation. | Runtime enforcement or host protection. |
| Installer lane | Guarded user-local or dry-run installer path. | Root installer, unattended mutation, or production installer. |
| Package lane | Local-only package or port draft. | Official package, archive readiness, or vendor approval. |
| Runtime boundary | Denied-by-default classification or no-effect boundary report. | Process isolation, sandboxing, or effect-performing execution. |
| Security baseline | Defensive planning baseline with source-tracked controls. | Protection guarantee, certification, hardening, malware prevention, or ransomware prevention. |
| AI or automation lane | Contract-only, prompt/report-only, or no model execution posture. | Inference, dialogue generation, tool execution, or autonomous control. |

## Validation

For subsystem landing-page changes, select checks from [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).

Minimum documentation checks:

```sh
git diff --check
sh scripts/test-project-strategy-status-framework.sh
```

Add the exact subsystem guard named by the changed source record. If the subsystem is Seal-facing, also run:

```sh
sh scripts/test-latticra-seal-docs.sh
```

Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when public wording, mirrors, status, platform posture, security wording, non-claims, or reader routes change.

## Boundary

This standard is documentation governance only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.
