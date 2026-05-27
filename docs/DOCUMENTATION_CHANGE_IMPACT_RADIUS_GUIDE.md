# Documentation Change Impact Radius Guide

Status: active documentation change-impact guide
Last updated: 2026-05-27 CDT
Scope: documentation-only changes that may affect public entry points, source records, mirrors, status records, estimate records, subsystem pages, platform docs, security docs, review packets, static HTML pages, and documentation governance records.

## Purpose

This guide defines how far a documentation change should ripple through the project.

Latticra documentation is intentionally layered. A small typo should not trigger a full public-entry review, and a status or claim change should not stop at one file. This guide helps reviewers choose the right review radius.

Use it with [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md), [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md), [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md), [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This guide does not promote claims. It decides which documentation surfaces need review before a change is considered coherent.

## Impact Radius Rule

Review the smallest set of documentation surfaces that can reasonably change the reader's understanding of:

```text
current status
claim posture
source authority
non-claims
validation evidence
reader route
public mirror
platform, installer, package, security, runtime, or subsystem boundary
```

If none of those change, keep the radius narrow.

If any of those change, expand the radius until every public surface that could mislead a reader has been checked.

## Radius Levels

| Radius | Use when | Review surfaces | Minimum validation |
| --- | --- | --- | --- |
| Local edit | Typo, formatting, link text, table cleanup, or local wording that does not change meaning. | Touched file only. | `git diff --check` and trailing-whitespace check. |
| Linked record | A local link, source pointer, validation pointer, or glossary term changes. | Touched file plus linked source or target record. | Local Markdown link check over touched files. |
| Source record | A contract, implementation record, validation record, status record, package record, security record, or subsystem record changes meaning. | Source record, status mirror, related non-claim, validation path, and any public summary that names the claim. | Exact source guard when applicable plus documentation hygiene. |
| Public entry | Root README, docs hub, status shortcut, public map, public HTML, quick start, or product copy changes reader posture. | Public entry point, source record, current status, non-claims, claims ledger, traceability row, and public mirrors. | Public-entry guard plus link or href checks. |
| Estimate mirror | Completion estimate, planning percentage, roadmap estimate, or estimate wording changes. | Estimate source record, `README.md`, `STATUS.md`, `docs/status/CURRENT_STATUS.md`, and static HTML pages that display the value. | Estimate source-alignment guard. |
| Platform, installer, package, or security posture | Platform readiness, package status, installer authority, security wording, runtime authority, or cryptographic posture changes. | Source record, status record, non-claim, public entry point, static HTML mirror, platform README, and exact guard named by the record. | Exact platform, installer, security, or subsystem guard plus public-entry checks. |
| Subsystem landing page | A subsystem README, subsystem public page, status record, evidence spine, or stop signal changes. | Landing page, source record, status record, validation, non-claim, docs hub, map, Foundation Index, and public mirror if present. | Exact subsystem guard plus local link check and public-entry guard. |
| Governance layer | Documentation maintenance, traceability, validation, drift response, freshness, source authority, health, style, impact radius, public-site, or subsystem governance changes. | Governance record, docs hub, Foundation Index, map, public index, and any governance files that call the rule. | Documentation hygiene, local link check, href check when static HTML changes, and public-entry guard. |

## Change-Class Checklist

| Change class | Must check | Usually does not require |
| --- | --- | --- |
| Wording cleanup | Touched file, style guide if terminology changes. | Status mirrors or public HTML when meaning is unchanged. |
| New public route | Docs hub or public HTML, target record, source authority, link checks. | Estimate guard unless estimates changed. |
| Claim narrowing | Source authority, claims ledger, non-claims, drift response, affected mirrors. | Implementation changes. |
| Claim strengthening | Stop unless source record, implementation evidence, validation, status, non-claims, public-entry alignment, and review packet all support it. | A wording-only merge. |
| Status update | Current status source, root status mirror, public entry points, estimates when values changed. | Platform guards unless platform posture changed. |
| Static HTML edit | Source Markdown, public-site mirror standard, href check, public-entry guard. | Markdown source changes unless the source was wrong. |
| Platform or package edit | Platform README, package source record, local-only non-claim, exact guard, public summaries. | Security guard unless security wording changed. |
| Security edit | Security source record, security non-claims, safe-testing route, exact security guard, public summaries. | Platform guard unless package or installer posture changed. |
| Governance edit | Docs hub, Foundation Index, public map/index, related governance records. | Product status mirrors unless public posture changed. |

## Expansion Triggers

Expand the review radius when:

- a public reader could infer a stronger capability;
- a status or estimate value changed;
- a source record and mirror disagree;
- a non-claim moved farther away from the constrained claim;
- a static HTML page summarizes a changed Markdown source;
- a subsystem landing page changes posture, evidence, validation, non-claims, or stop signals;
- platform, installer, package, runtime, security, or AI wording changes;
- a stale, superseded, archived, planning, draft, local-only, no-effect, report-only, or blocked record is involved;
- validation commands or expected guard outcomes changed.

## Containment Rules

Keep the radius contained when:

- the change is spelling, grammar, or formatting only;
- the route changes but the claim does not;
- the source record, status, validation, and non-claims remain unchanged;
- the public HTML page does not summarize the changed text;
- the changed record is historical context with a clear lifecycle boundary.

Containment is not a shortcut. If a contained change touches links, run link checks for the touched files.

## Review Packet Fields

When using [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), include:

```text
impact_radius:
radius_reason:
surfaces_reviewed:
surfaces_intentionally_not_reviewed:
expansion_triggers_checked:
containment_reason:
```

Use `accepted_navigation_only` when the radius is route-only and no claim changes.

Use `accepted_wording_only` when the radius is local or linked-record level and current claim posture is unchanged.

Use `blocked_public_entry_drift`, `blocked_claim_promotion`, or `blocked_stale_public_source` when the required radius reveals unsupported public wording.

## Boundary

This guide governs documentation review scope only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.
