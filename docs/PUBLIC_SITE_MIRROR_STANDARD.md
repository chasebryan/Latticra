# Public Site Mirror Standard

Status: active public-site mirror standard
Last updated: 2026-05-27 CDT
Scope: static HTML pages under `docs/`, public dashboard pages, public maps, quick-start pages, subsystem public pages, validation pages, security pages, packaging pages, status pages, roadmap pages, and any public site page that summarizes source Markdown.

## Purpose

This standard keeps Latticra's static public site aligned with source documentation.

Public HTML pages are reader-facing mirrors and route maps. They may summarize, organize, and make source records easier to scan, but they must not become stronger than the Markdown records, status records, contracts, or guard scripts they point to.

Use this standard with [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md), [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This standard does not promote claims. It limits how public HTML may mirror claims.

## Mirror Rule

Every public site statement should follow this route:

```text
public HTML summary -> source Markdown record -> status or validation record -> non-claim boundary
```

If the source Markdown is narrower than the HTML, narrow the HTML.

If the source Markdown is missing, remove the HTML claim or mark it blocked in a review packet.

If the HTML page is only navigation, keep the wording navigational and avoid capability language.

## Public Page Types

| Page type | Examples | Must do | Must not do |
| --- | --- | --- | --- |
| Front door | [`index.html`](index.html) | Summarize current posture, route to status, route to source records. | Replace README, status records, or contracts as source of truth. |
| Map | [`map.html`](map.html) | Organize reader paths and evidence routes. | Treat a route as evidence of capability. |
| Status and roadmap | [`status.html`](status.html), [`roadmap.html`](roadmap.html) | Mirror current status and planning estimates from source records. | Add release promises or stronger readiness language. |
| Start and examples | [`start.html`](start.html), [`examples.html`](examples.html) | Keep runnable paths guarded, no-effect, dry-run, or user-local with cleanup context. | Hide effect boundaries behind friendly copy. |
| Evidence and validation | [`evidence.html`](evidence.html), [`validation.html`](validation.html) | Point to exact source records and guards. | Treat local static validation as production readiness. |
| Security | [`security.html`](security.html) | Preserve security non-claims and safe reporting boundaries. | Claim protection, prevention, certification, hardening, or monitoring service status. |
| Platform and installer | [`packaging.html`](packaging.html), [`installer.html`](installer.html) | Preserve local-only, no-effect, draft, or guarded status. | Claim official package status, archive readiness, root install authority, or production installer readiness. |
| Subsystem pages | `seal.html`, `runtime.html`, `language.html`, `kernel.html`, `nadia.html`, `panel.html` | Link to subsystem source records, status, guards, and non-claims. | Let subsystem progress imply product readiness. |

## Required Page Contract

Every public HTML page should have:

1. a clear current posture statement;
2. links to source Markdown records;
3. a route to current status when the page describes progress;
4. non-claims near risky product, security, installer, package, runtime, platform, or AI wording;
5. validation or guard names when evidence matters;
6. no claim stronger than its source Markdown;
7. no estimate value that differs from the estimate source records;
8. no standalone source-of-truth role unless the page is explicitly a navigation index.

## HTML Wording Rules

Prefer short public-site wording that points back to source records:

```text
current status record
local-only validation lane
guarded user-local route
report-only evidence surface
source Markdown record
non-claim boundary
planning estimate
```

Avoid public-site wording that sounds stronger than the source:

```text
ready
secure
approved
certified
production
official package
installer support
runtime enforcement
host protection
```

## Update Triggers

Review affected public HTML pages when any of these change:

- root [`README.md`](../README.md);
- [`STATUS.md`](../STATUS.md);
- [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md);
- status records governed by [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md);
- estimate source records;
- [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md);
- [`NON_CLAIMS.md`](NON_CLAIMS.md);
- subsystem landing pages or status records;
- platform/package/installer posture;
- security posture;
- validation or guard outcomes;
- documentation freshness, lifecycle state, stale-review, supersession, or archive boundaries;
- impact-radius review says the changed source, status, route, validation path, or non-claim reaches static HTML;
- documentation routing in [`README.md`](README.md) or [`map.html`](map.html).

Do not update every HTML file mechanically. Update only pages whose reader-facing claim, route, mirror, or source link changes.

## Validation

For public site mirror changes, run documentation hygiene and public-entry checks from [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).

Minimum checks:

```sh
git diff --check
sh scripts/test-project-strategy-status-framework.sh
```

Add local Markdown link checks for touched Markdown.

Add an HTML `href` existence check for touched static pages.

Add estimate, platform, Seal, security, installer, or subsystem guards when the page mirrors those claims.

## Stop Conditions

Stop and demote the public HTML wording when:

- HTML is stronger than source Markdown;
- a page has no source link for a capability claim;
- a status or estimate value differs from the source record;
- a public page omits nearby non-claims for risky wording;
- a public page presents local validation as approval, support, or production readiness;
- a public page describes planned work as existing behavior;
- public navigation makes a subsystem, platform, or security lane sound ready.

## Review Record Fields

When using [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), include:

```text
public_site_mirror_standard_checked:
public_html_pages_touched:
source_markdown_records:
status_or_estimate_sources:
html_not_stronger_than_source:
href_check:
```

## Boundary

This standard governs public-site documentation mirrors only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.
