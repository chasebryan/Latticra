# Documentation Visual Asset Standard

Status: active documentation visual-asset standard
Last updated: 2026-05-28 CDT
Scope: screenshots, figures, diagrams, public HTML images, Markdown images, social/review cards, presentation visuals, generated media, public-site assets under `docs/assets/`, and documentation images that summarize product, validation, status, security, platform, installer, runtime, or subsystem posture.

## Purpose

This standard defines how Latticra documentation should use visual assets.

Images can make documentation clearer, but they can also imply maturity, readiness, product polish, security posture, or release status beyond the source records. This standard keeps visual assets inspectable, accessible, current, and bounded by the same evidence rules as text.

Use it with [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This standard does not approve a visual for publication by itself. It defines the minimum documentation review expected before visuals appear in public surfaces.

## Visual Asset Rule

Every visual asset used in documentation should have:

```text
clear purpose
source or capture context
current posture boundary
alt text or accessible equivalent
nearby source record or status route when it implies a claim
non-claim boundary when it touches risky product, security, installer, package, runtime, AI, crypto, or platform posture
```

If a visual cannot meet those requirements, keep it in draft, review, or strategy context rather than a public product surface.

## Asset Classes

| Asset class | Required context | Must not imply |
| --- | --- | --- |
| Product screenshot | Product surface, current status, capture context, and whether it is prototype, demo, no-effect, report-only, local-only, or current UI. | Production readiness, feature completeness, hosted service, or support guarantee. |
| Terminal screenshot | Command or guard source, expected output meaning, no-effect or report-only boundary, and timestamp or source record when relevant. | Runtime authority, security protection, or validation beyond the shown command. |
| Diagram | Source record, scope, and whether the diagram is conceptual, planned, implemented, or report-only. | Implementation evidence by itself. |
| Public HTML image | Source Markdown or status route, alt text, and public/source consistency review. | Stronger public claim than source Markdown. |
| Social or review card | Review status, publication status, and non-claim boundary when shared externally. | Endorsement, approval, certification, official package status, or production product status. |
| Generated visual | Prompt or generation context when retained, review status, and source-record boundary. | Evidence, implementation, screenshot, or real product state unless explicitly captured from the real surface. |
| Presentation visual | Audience, source record, and current status route. | Current public posture if the presentation is older or superseded. |

## Alt Text Rule

Every meaningful image in public HTML or Markdown should have alt text or an accessible text equivalent.

Alt text should describe what the reader needs to know, not decorate the page.

Prefer:

```text
Terminal output showing Latticra Seal runtime dry-run report-only default-deny metadata.
```

Avoid:

```text
cool screenshot
image
logo
secure dashboard
```

Decorative images may use empty alt text only when the surrounding text already carries the same meaning and the image does not communicate product posture.

## Freshness And Source

Visuals should be reviewed when:

- the UI, command output, status, estimate, validation result, or non-claim changes;
- a visual moves from strategy or review context to a public surface;
- a public image summarizes a subsystem, platform, installer, security, runtime, AI, or crypto claim;
- a visual no longer matches the source record;
- alt text describes stronger posture than the source record;
- a generated or illustrative asset could be mistaken for a real screenshot.

Use [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) when a visual is stale, superseded, archived, planning-only, draft, or review-only.

## Public Site Rules

Public HTML images should:

1. point to a real asset path;
2. include useful alt text unless decorative;
3. be no stronger than source Markdown or status records;
4. avoid implying production readiness, security protection, package approval, runtime authority, or OS replacement;
5. keep captions or nearby text aligned with current non-claims;
6. be checked with an HTML href/src existence check when the page changes.

## Review Triggers

Use this standard when a change touches:

- `docs/assets/`;
- image references in public HTML;
- Markdown image references;
- screenshots in quick-start, validation, installer, package, security, runtime, Seal, Panel, Nadia, or platform docs;
- generated visual assets;
- presentation images;
- social or review cards.

Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when a visual changes public posture, claim meaning, current status, validation meaning, publication status, or non-claim placement.

## Boundary

This standard governs documentation visual assets only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, visual design approval, public estimates, or product readiness.
