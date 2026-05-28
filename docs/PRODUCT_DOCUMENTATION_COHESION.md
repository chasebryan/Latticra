# Product Documentation Cohesion

Status: active product-documentation cohesion guide
Last updated: 2026-05-27 CDT
Scope: public README, documentation hub, static site pages, installer docs, package docs, security docs, status records, subsystem maps, and reader routes.

## Purpose

This guide keeps Latticra's product-facing documentation coherent without implying that Latticra is already a production product.

In this file, "product documentation" means the reader-facing surface of the project: what a user, operator, reviewer, packager, or contributor sees before they understand the full evidence trail.

The product surface should always make four things easy to find:

1. what exists now;
2. what a reader can safely run or inspect;
3. what remains intentionally blocked;
4. what evidence would be required before the claim can become stronger.

Use [`DOCUMENTATION_READER_JOURNEY_MAP.md`](DOCUMENTATION_READER_JOURNEY_MAP.md) to keep audience-specific reader paths practical, bounded, and explicit about stop signals.

Use [`DOCUMENTATION_GLOSSARY.md`](DOCUMENTATION_GLOSSARY.md) when product copy depends on shared terms such as no-effect, report-only, guarded user-local, local-only, public status, drift, demotion, or product readiness.

Use [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md) before broad product-surface changes to score findability, current status visibility, claim safety, traceability, validation, reader-route fitness, public/source consistency, and non-claim proximity.

Use [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md) before creating or refreshing subsystem landing pages so subsystem progress does not imply product readiness.

Use [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md) before changing static public pages so HTML summaries remain mirrors of source Markdown.

Use [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md) when product-facing wording disagrees with source records, status, non-claims, or public mirrors.

Use [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) when product-facing wording depends on stale, superseded, archived, planning, draft, local-only, no-effect, report-only, or blocked records.

Use [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md) when deciding whether a product-facing wording change stays local or must expand to public entries, source records, mirrors, status records, validation paths, or non-claims.

Use [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md) when product-facing copy depends on status records, status-index entries, status mirrors, estimate records, or public-entry alignment status notes.

Use [`DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md`](DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md) when product-facing pages include runnable commands, validation command lists, platform prerequisites, or install, update, reset, uninstall, and cleanup snippets.

## Cohesion Promise

All product-facing documentation should describe Latticra as:

```text
early-stage
evidence-bound
contract-first
local-first where runnable
no-effect or guarded by default
explicit about non-claims
```

Do not let a shorter product summary outgrow the evidence in status records, contracts, guard scripts, or the [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md).

Use [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) to connect public surfaces to source records, validation checks, and non-claim boundaries.

Use [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) to choose documentation validation commands and failure-handling paths.

Use [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) when product-facing wording, source records, status mirrors, non-claims, or platform posture disagree.

Use [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md) for canonical terminology, status/date style, heading shape, link style, and replacement wording.

## Product Surface Matrix

| Surface | Reader job | Must say | Must not imply |
| --- | --- | --- | --- |
| [`../README.md`](../README.md) | Understand identity, posture, quick start, and non-claims. | Early-stage, evidence-bound, current estimates, guarded local routes, and explicit non-claims. | Production platform, certified security, OS replacement, package approval, or broad installer readiness. |
| [`README.md`](README.md) | Choose the right documentation depth. | First reading paths, status sources, claim boundaries, platform lanes, and maintenance rules. | That every doc is equally authoritative or that public summaries override status records. |
| [`index.html`](index.html) | Scan the public site quickly. | Current posture, no-effect default, major records, and resource routes. | That GitHub Pages content is stronger than source Markdown records. |
| [`start.html`](start.html) and [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md) | Try safe local entry points. | Guarded user-local commands, reset/cleanup paths, and expected no-effect posture. | Root installation, daily-driver readiness, boot readiness, or broad host management. |
| [`validation.html`](validation.html) | Understand local evidence lanes. | Local-only validation, transcripts, static checks, and disposable/guarded boundaries. | Distribution approval, production installability, update safety, or recovery safety. |
| [`security.html`](security.html) and [`../SECURITY.md`](../SECURITY.md) | Report issues and understand security posture. | Safe testing, threat-model work, security non-claims, and evidence boundaries. | Malware prevention, ransomware prevention, certified security, or hardened sandboxing. |
| [`../installer/README.md`](../installer/README.md) | Use Panel and installer lanes. | User-local guarded behavior, configuration boundaries, and platform-specific prerequisites. | Root installer authority, unattended host mutation, production installer readiness, or OS-base installation. |
| Platform package docs | Review package shape and platform readiness. | Local-only drafts, static checks, prerequisites, and non-approval boundaries. | Fedora, Ubuntu, Debian, FreeBSD, OpenBSD, openSUSE, or vendor endorsement. |
| Subsystem maps | Enter a technical lane. | Contract, implementation, status, guard path, non-claims, and stop signals for the subsystem. | That subsystem progress changes overall product readiness automatically. |
| Status records | Verify current posture. | Current evidence, estimate posture, next blockers, and non-claims. | Release commitments, guarantees, or broad public claims. |

## Reader Routes

### New User

Use this route for someone trying Latticra locally. The fuller audience matrix is [`DOCUMENTATION_READER_JOURNEY_MAP.md`](DOCUMENTATION_READER_JOURNEY_MAP.md).

1. [`../README.md`](../README.md)
2. [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md)
3. [`start.html`](start.html)
4. [`../installer/README.md`](../installer/README.md)
5. [`NON_CLAIMS.md`](NON_CLAIMS.md)

The route must stay practical and bounded. It should not require reading every architecture record before a guarded user-local check, but it must keep current non-claims visible.

### Reviewer

Use this route for posture or due-diligence review:

1. [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)
2. [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md)
3. [`NON_CLAIMS.md`](NON_CLAIMS.md)
4. [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md)
5. [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md)

The route should make it easy to reject overbroad wording before it reaches public summaries.

### Contributor

Use this route for someone changing documentation or product posture:

1. [`README.md`](README.md)
2. [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md)
3. [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md)
4. [`DOCUMENTATION_GLOSSARY.md`](DOCUMENTATION_GLOSSARY.md)
5. [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md)
6. [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md)
7. [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md)
8. [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md)
9. [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md)
10. [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md)
11. [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md)
12. [`DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md`](DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md)
13. [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md)
14. The relevant subsystem contract and status record
15. The exact guard named by that record

The route should prevent documentation from getting ahead of implementation or validation evidence.

### Packager Or Platform Reviewer

Use this route for platform-specific work:

1. [`validation.html`](validation.html)
2. The platform workflow document or package README
3. [`PRODUCTION_INSTALLER_READINESS_CONTRACT.md`](PRODUCTION_INSTALLER_READINESS_CONTRACT.md)
4. [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md)
5. [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)

The route should keep every package and platform lane local-only unless official publication or distribution evidence exists.

## Product Copy Rules

Use product copy that is specific, inspectable, and bounded.

Prefer:

```text
guarded user-local workbench
no-effect report surface
local-only package draft
static validation lane
contract-first runtime boundary
report-only Seal evidence
early-stage public status
```

Avoid:

```text
secure product
agent security platform
production installer
official package
Linux replacement
OS distribution
runtime enforcement
host protection
```

## Cross-Link Requirements

Every product-facing page that describes a capability should have a path to:

1. current status;
2. non-claims;
3. relevant contract or implementation record;
4. validation or guard evidence;
5. safe user route, if the capability can be run locally;
6. blocked-claim language, if adjacent unsupported claims are likely.

## Drift Review

Run this review when public wording changes:

1. Does the public wording match [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md)?
2. Does the route from `README.md` or `index.html` reach the exact source record?
3. Does the status record use the same posture words?
4. Does the page say what is blocked?
5. Does the validation path prove the narrow claim?
6. Does [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md) identify which record wins if records disagree?
7. Does [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) identify the source record, mirror, validation, and non-claim boundary?
8. Does [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) identify the narrowest relevant checks?
9. Does [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) identify the correct narrowing or demotion path if records disagree?
10. Does [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) identify whether any stale, superseded, archived, planning, draft, local-only, no-effect, report-only, or blocked record is involved?
11. Does [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md) identify which public entries, source records, mirrors, validation paths, status records, or non-claims need review?
12. Does [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md) apply because status records, status mirrors, status-index entries, estimates, or public-entry alignment notes changed?
13. Does [`DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md`](DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md) apply because runnable commands, validation command lists, platform prerequisites, or install/update/reset/uninstall snippets changed?
14. Does the change preserve the documentation-only boundary if no implementation changed?
15. Does the wording follow [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md)?
16. Does [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md) leave every relevant dimension healthy or explicitly handled as a watch/failing item?
17. Does [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md) apply because a subsystem landing page or subsystem public summary changed?
18. Does [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md) apply because a static public HTML page changed?
19. Does the change need a [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) outcome label?

## Maintenance Boundary

Use [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md) for update process, source-of-truth mirrors, estimate handling, and validation commands.

Use this file for product-facing coherence: audience route, product wording, surface responsibilities, and cross-link expectations.
