# Documentation Freshness Lifecycle Policy

Status: active documentation freshness lifecycle policy
Last updated: 2026-05-27 CDT
Scope: public Markdown, static HTML mirrors, status records, estimate records, source records, subsystem landing pages, platform and package docs, security docs, review packets, and strategy or project notes.

## Purpose

This policy defines how Latticra treats documentation freshness, lifecycle states, stale evidence, superseded records, archive boundaries, and review dates.

Use it with [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md), [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md), [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This policy does not promote claims. It decides whether a documentation record is current enough to guide public wording, review, routing, or mirror updates.

## Freshness Rule

A documentation record is fresh only when its current posture is still supported by source records, status records, validation records, and non-claims.

A recent date by itself is not freshness.

Do not update `Last updated` merely to make a record look current. Change that date only after a substantive wording, routing, source-link, status, mirror, or lifecycle review.

## Lifecycle States

Use these states when a documentation record needs an explicit lifecycle boundary.

| State | Meaning | Required handling | Must not imply |
| --- | --- | --- | --- |
| active | The record currently governs wording, routing, validation, or source posture. | Keep source links, status, validation, and non-claims current. | Product readiness by itself. |
| current status | The record mirrors current public posture, estimates, or next work. | Align public mirrors when the status source changes. | Release promise or readiness guarantee. |
| planning | The record describes future direction, proposed sequencing, or design intent. | Keep dates concrete and route readers to current status before action. | Existing behavior or implementation evidence. |
| draft | The record is intentionally incomplete or local-only review material. | Mark blocked claims and avoid public claim promotion. | Public readiness or approval. |
| local-only | The record is valid only for local development or guarded local validation. | Preserve local-only and no-effect boundaries near runnable text. | Distribution approval, production installability, or host authority. |
| no-effect | The record describes checks, reports, fixtures, or dry-runs without external effects. | Keep effect boundaries visible and link validation records. | Runtime authority, protection, or mutation. |
| report-only | The record emits or describes metadata without enforcement. | Keep report-only wording near any policy, security, runtime, or Seal claim. | Enforcement, prevention, or control. |
| superseded | A newer named record replaces this record for current decisions. | Add a supersession block and route readers to the replacement. | Current source authority. |
| stale-review-required | The record may still contain useful context, but current status or evidence may have moved beyond it. | Do not use it for public claims until reviewed against current authority. | Current truth without review. |
| archived | The record is historical context only. | Keep an archive boundary and current reader route. | Active posture, readiness, or validation evidence. |
| blocked | The record names a claim or route that cannot move without missing evidence. | Preserve the blocker and source of missing evidence. | Accepted claim or pending release. |

## Freshness Tiers

| Tier | Examples | Review when | Freshness test |
| --- | --- | --- | --- |
| Public entry points | [`../README.md`](../README.md), [`README.md`](README.md), [`../STATUS.md`](../STATUS.md), [`index.html`](index.html), [`map.html`](map.html) | Public posture, status, estimate, non-claim, route, or source-link wording changes. | Public wording does not exceed source records or non-claims. |
| Current status and estimates | [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), estimate source records, status mirrors | Current posture, estimate values, next priorities, or status mirror rules change. | Values and posture match current status authority. |
| Source records | Contracts, implementation records, validation records, package records, security baselines | Implementation evidence, guard behavior, validation status, or capability posture changes. | Record still matches the narrow validated behavior. |
| Static HTML mirrors | Public HTML pages under `docs/` | Source Markdown, status, estimate, validation, or non-claim wording changes. | HTML is not stronger than the source Markdown. |
| Subsystem landing pages | Seal, Panel, Runtime, Nadia, language, packaging, security, and kernel entry points | Subsystem status, guard, non-claim, source record, or public summary changes. | Landing page exposes posture, evidence, validation, non-claims, and stop signals. |
| Platform, package, installer, and security docs | Platform README files, installer docs, security pages, package validation records | Platform approval posture, installer authority, package status, security wording, or validation evidence changes. | Boundaries remain local-only, no-effect, report-only, or blocked unless source evidence says otherwise. |
| Strategy and project notes | `docs/strategy/`, `docs/project_notes/`, review context records | Notes are used to guide public wording or current decisions. | Dated context does not override current status or source authority. |
| Historical or superseded docs | Archived plans, old review packets, replaced status records | A reader could mistake the record for current posture. | Record names its replacement, boundary, or historical role. |

## Review Triggers

Review freshness and lifecycle when any of these change:

- implementation behavior, guard output, or generated report evidence;
- current status, estimate values, or next priorities;
- public claim wording, public route order, or product copy;
- non-claims or blocked adjacent claims;
- platform, package, installer, or security posture;
- static HTML public pages;
- subsystem landing pages or subsystem public summaries;
- source authority conflicts;
- stale evidence, superseded records, or archive boundaries.

## Supersession Block

Use this block when a record should remain in the repository but no longer controls current decisions:

```text
Superseded by:
Superseded on:
Reason:
Current reader route:
Boundary:
```

The replacement link must point to a real record. The boundary should say whether the old record is historical context, draft context, planning context, or blocked context.

## Stale Handling

When a record looks stale:

1. Identify the current source authority with [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md).
2. Compare the record against current status, source records, validation, and non-claims.
3. Mark the record `stale-review-required`, demote the wording, or add a supersession block.
4. Update only public mirrors whose reader-facing claim changed.
5. Run the checks selected with [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).

Do not delete historical records simply to hide drift. Preserve useful context with a clear lifecycle boundary.

## Date Rules

`Last updated` means the record received a substantive review or change.

Substantive changes include:

- claim wording;
- status or estimate posture;
- lifecycle state;
- source links;
- validation paths;
- mirror requirements;
- non-claim boundaries;
- reader routes.

Formatting-only changes may leave the date unchanged unless the file's local convention updates dates for every edit.

If a change only updates a mirror link, static route, or index entry, say that in the review packet rather than implying a full source-record review.

## Boundary

This policy governs documentation freshness only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.
